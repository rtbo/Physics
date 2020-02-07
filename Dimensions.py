
import sys
import os
import argparse
import json
from jinja2 import Environment

class Conversion:
    def __init__(self, fact, offset, pi_exp):
        self.fact = Conversion._num_den(fact, (1, 1))
        self.offset = Conversion._num_den(offset, (0, 1))
        self.pi_exp = pi_exp if pi_exp != "" else 0
        self.norm()

    def norm(self):
        def _norm(num, den):
            if num % den == 0:
                num = num / den
                den = 1
            return (int(num), int(den))
        self.fact = _norm(self.fact[0], self.fact[1])
        self.offset = _norm(self.offset[0], self.offset[1])
        self.pi_exp = int(self.pi_exp)

    @staticmethod
    def _num_den(numstr, default):
        if numstr == "":
            return default
        if "." in numstr:
            splt = numstr.split(".")
            return (int(splt[0] + splt[1]), 10 ** len(splt[1]))
        elif "/" in numstr:
            splt = numstr.split("/")
            return (int(splt[0]), int(splt[1]))
        else:
            return (int(numstr), 1)

    @property
    def cpp(self):
        return "conversion<std::ratio<{}, {}>, std::ratio<{}, {}>, {}>".format(
            self.fact[0], self.fact[1], self.offset[0], self.offset[1], self.pi_exp
        )

    @property
    def is_default(self):
        return self.conv(1) == 1

    @property
    def f_fact(self):
        return self.fact[0] / self.fact[1]

    @property
    def f_offset(self):
        return self.offset[0] / self.offset[1]

    def conv(self, val):
        from math import pi
        return self.f_fact * val * (pi ** self.pi_exp) + self.f_offset


class Prefix:
    def __init__(self, name, symbol, unicode, pow10):
        self.name = name
        self.symbol = symbol
        self.unicode = unicode
        self.pow10 = pow10

    def adapt_conv(self, conv):
        if self.pow10 > 0:
            conv.fact = (conv.fact[0] * (10 ** self.pow10), conv.fact[1])
        else:
            conv.fact = (conv.fact[0], conv.fact[1] * (10 ** (-self.pow10)))
        conv.norm()

prefixes = {
    #"y": Prefix("yocto", "y", "y", -24),
    #"z": Prefix("zepto", "z", "z", -21),
    "a": Prefix("atto", "a", "a", -18),
    "f": Prefix("femto", "f", "f", -15),
    "p": Prefix("pico", "p", "p", -12),
    "n": Prefix("nano", "n", "n", -9),
    "u": Prefix("micro", "u", "\\u00B5", -6),
    "m": Prefix("milli", "m", "m", -3),
    "c": Prefix("centi", "c", "c", -2),
    "d": Prefix("deci", "d", "d", -1),
    "da": Prefix("deca", "da", "da", 1),
    "h": Prefix("hecto", "h", "h", 2),
    "k": Prefix("kilo", "k", "k", 3),
    "M": Prefix("mega", "M", "M", 6),
    "G": Prefix("giga", "G", "G", 9),
    "T": Prefix("tera", "T", "T", 12),
    "P": Prefix("peta", "P", "P", 15),
    "E": Prefix("exa", "E", "E", 18),
    #"Z": Prefix("zetta", "Z", "Z", 21),
    #"Y": Prefix("yotta", "Y", "Y", 24),
}

class Dim:
    def has_no_dim(self):
        return self.M==0 and self.L==0 and self.T==0 and self.I==0 and self.Th==0 and self.N==0 and self.J==0

    @staticmethod
    def build_from_dict(dim_dict):
        dim = Dim()
        dim.M = dim_dict["M"]
        dim.L = dim_dict["L"]
        dim.T = dim_dict["T"]
        dim.I = dim_dict["I"]
        dim.Th = dim_dict["Th"]
        dim.N = dim_dict["N"]
        dim.J = dim_dict["J"]
        return dim

    @staticmethod
    def subtract(lhs, rhs):
        dim = Dim()
        dim.M = lhs.M - rhs.M
        dim.L = lhs.L - rhs.L
        dim.T = lhs.T - rhs.T
        dim.I = lhs.I - rhs.I
        dim.Th = lhs.Th - rhs.Th
        dim.N = lhs.N - rhs.N
        dim.J = lhs.J - rhs.J
        return dim

# a single unit definition such as meter or volt
class UnitDef:
    @staticmethod
    def build_from_dict(dict, dim):
        ud = UnitDef()
        ud.dim = dim
        ud.name = dict["name"]
        ud.symbol = dict["symbol"]
        ud.unicode = dict["unicode"]
        ud.factor = dict["factor"]
        ud.offset = dict["offset"]
        ud.pi_exp = dict["pi_exp"]
        ud.prefixes = list(map(lambda p: prefixes[p], dict["prefixes"]))
        ud.def_pref = dict["def_pref"]
        return ud

    @staticmethod
    def build_default_from_def_and_prefix(unit_def, prefix):
        # used to build kilogram from gram
        ud = UnitDef()
        ud.dim = dim
        ud.name = prefix.name + unit_def.name
        ud.symbol = prefix.symbol + unit_def.symbol
        ud.unicode = prefix.unicode + unit_def.unicode
        ud.factor = ""
        ud.offset = ""
        ud.pi_exp = ""
        ud.def_pref = ""
        return ud

unit_defs = {}
colliding_names = [ "pascal" ]

def unicode_repr(s):
    res = ''
    i = 0
    while i < len(s):
        if s[i] == '\\':
            point = int(s[i+2:i+6], base=16)
            res += chr(point)
            i += 6
        else:
            res += s[i]
            i += 1
    return res

# a unit instance definition such as millimeter, volt,
# or joule per mole.kelvin
class Unit:

    class Comp:
        def __init__(self, order, unit_def, prefix=None):
            self.order = order
            self.unit_def = unit_def
            self.prefix = prefix

    def __init__(self):
        self.pos_comps = []
        self.neg_comps = []
        self.name = ""
        self.symbol = ""
        self.unicode = ""
        self.conv = None

    def check_add_comp(self, order, name):
        if order > 0:
            self.pos_comps.append(self.Comp(order, unit_defs[name]))
        elif order < 0:
            self.neg_comps.append(self.Comp(order, unit_defs[name]))

    def add_dim_comps(self, dim):
        self.check_add_comp(dim.M, "kilogram")
        self.check_add_comp(dim.L, "meter")
        self.check_add_comp(dim.T, "second")
        self.check_add_comp(dim.I, "ampere")
        self.check_add_comp(dim.N, "mole")      # moles placed before kelvin
        self.check_add_comp(dim.Th, "kelvin")
        self.check_add_comp(dim.J, "candela")

    def compose(self):

        def add_order(order):
            if order < 0:
                self.unicode += "\\u207B" # exp minus
            if abs(order) == 3:
                self.name += "3"
                self.symbol += "3"
                self.unicode += "\\u00B3" # exp 3
            elif abs(order) == 2:
                self.name += "2"
                self.symbol += "2"
                self.unicode += "\\u00B2" # exp 2
            elif order == -1:
                self.unicode += "\\u00B9" # exp minus 1

        def add_comp(comp):
            if len(self.name):
                self.name += "_"
                self.unicode += "."
            self.name += comp.unit_def.name
            self.symbol += comp.unit_def.symbol
            self.unicode += comp.unit_def.unicode
            add_order(comp.order)

        for c in self.pos_comps:
            add_comp(c)
        if len(self.neg_comps):
            if len(self.pos_comps):
                self.name += "_"
                self.symbol += "_"
            self.name += "per"
            self.symbol += "p_"
        for c in self.neg_comps:
            add_comp(c)
        if self.name == "":
            self.name = "coef"

    @property
    def cppname(self):
        return self.name + "_" if self.name in colliding_names else self.name

    @property
    def is_default(self):
        return self.conv and self.conv.is_default

    @property
    def unicode_cpp(self):
        return '"{}{}"'.format(' ' if len(self.unicode)>0 else '', self.unicode)

    @property
    def u8_len(self):
        return len(unicode_repr(self.unicode).encode('utf-8'))

    @property
    def u16_len(self):
        return len(unicode_repr(self.unicode).encode('utf-16-le')) // 2

    @property
    def conv1(self):
        return self.conv.conv(1) if self.conv else 0

    @staticmethod
    def build_from_def(unit_def, prefix=None):
        unit = Unit()
        unit.name = unit_def.name
        unit.symbol = unit_def.symbol
        unit.unicode = unit_def.unicode
        unit.conv = Conversion(unit_def.factor, unit_def.offset, unit_def.pi_exp)
        unit.pos_comps.append(Unit.Comp(1, unit_def, prefix))
        if prefix:
            unit.name = prefix.name + unit.name
            unit.symbol = prefix.symbol + unit.symbol
            unit.unicode = prefix.unicode + unit.unicode
            prefix.adapt_conv(unit.conv)
        return unit

    @staticmethod
    def build_from_dim(dim):
        unit = Unit()
        unit.add_dim_comps(dim)
        unit.compose()
        unit.conv = Conversion("", "", "")
        return unit

    @staticmethod
    def build_from_dim_and_foreign(dim, foreign):
        unit = Unit()
        unit.check_add_comp(1, foreign)
        foreign_def = unit_defs[foreign]
        dim = Dim.subtract(dim, foreign_def.dim)
        unit.add_dim_comps(dim)
        unit.compose()
        unit.conv = Conversion(foreign_def.factor, foreign_def.offset, foreign_def.pi_exp)
        return unit

def check_unit_def(dim_dict):
    if len(dim_dict["units"]) > 0:
        dim = Dim.build_from_dict(dim_dict)
        for unit_dict in dim_dict["units"]:
            ud = UnitDef.build_from_dict(unit_dict, dim)
            unit_defs[ud.name] = ud
            if ud.def_pref != "":
                p = prefixes[ud.def_pref]
                def_ud = UnitDef.build_default_from_def_and_prefix(ud, p)
                unit_defs[def_ud.name] = def_ud

def snake_name(camel_name):
    return camel_name[0].lower() + camel_name[1:]

def complete_dim(dim_dict):
    units = []
    dim = Dim.build_from_dict(dim_dict)

    name = dim_dict["name"]
    dim_dict["snake_name"] = snake_name(name)
    dim_dict["cppns"] = name.lower()

    for unit_dict in dim_dict["units"]:
        if unit_dict["name"] == "":
            units.append(Unit.build_from_dim(dim))
        else:
            unit_def = unit_defs[unit_dict["name"]]
            unit = Unit.build_from_def(unit_def)
            units.append( unit )
            for p in unit_dict["prefixes"]:
                prefix = prefixes[p]
                units.append(Unit.build_from_def(unit_def, prefix))

    for foreign in dim_dict["foreign_units"]:
        unit = Unit.build_from_dim_and_foreign( dim, foreign )
        units.append( unit )

    if len(units) == 0:
        units.append(Unit.build_from_dim(dim))

    dim_dict["default_unit"] = next(u for u in units if u.is_default)
    dim_dict["units"] = units

    from itertools import groupby
    conv1 = lambda u: u.conv1
    dim_dict["unit_set"] = [ next(g) for k, g in groupby(sorted(units, key=conv1), key=conv1) ]

def filter_dims(dims, included_dims, excluded_base_dims, excluded_dims):
    if included_dims:
        includes = included_dims.split(':')
    else:
        includes = list(map(lambda d: d["name"], dims))
    excludes = []
    if excluded_dims:
        with open(excluded_dims, 'r') as f:
            for line in [line.strip() for line in f]:
                if not line.startswith("#"):
                    excludes.append(line)
    base_excludes = excluded_base_dims.split(':') if excluded_base_dims else []
    for d in filter(lambda d: d["name"] in includes and not d["name"] in excludes, dims):
        found = False
        for e in base_excludes:
            if d[e] != 0:
                found = True
                break
        if not found:
            yield d

if __name__ == '__main__':

    ap = argparse.ArgumentParser(description="Physics dimensions code generator")
    ap.add_argument("--input", nargs='?', type=argparse.FileType('r'),
            default=sys.stdin, help="Input template to be used")
    ap.add_argument("--output", nargs='?', type=argparse.FileType('w'),
            default=sys.stdout, help="Output file")
    ap.add_argument("--print-dims", dest="print_dims", action="store_true", default=False,
            help="print the list of dimensions (one per line) and exit")
    ap.add_argument("--excluded-base-dims", dest="excluded_base_dims", default=None,
            help='":" separated list of base dimension exclusion.')
    ap.add_argument("--excluded-dims", dest="excluded_dims", default=None,
            help='file containing list of dimensions to exclude.')
    ap.add_argument("--dims", dest="dims", default=None,
            help='list of dimensions to include.')
    ap.add_argument("--dim", dest="dim", default=None,
            help="The dimension to generate code for. Toggles to single dimension mode.")
    args = ap.parse_args()

    dir_path = os.path.dirname(os.path.realpath(__file__))
    datafile = os.path.join(dir_path, "Dimensions.json")

    with open(datafile, "r") as df:
        dims = json.load(df)

    for dim in dims:
        check_unit_def(dim)

    if args.dim:
        tplt = Environment(trim_blocks=True).from_string(args.input.read())
        dim = next(filter(lambda d: d["name"] == args.dim, dims))
        complete_dim(dim)
        args.output.write(tplt.render(dim=dim))

    else:
        dims = list(filter_dims(dims, args.dims, args.excluded_base_dims, args.excluded_dims))

        if args.print_dims:
            for dim in dims:
                args.output.write(dim["name"] + ":")
            sys.exit(0)

        tplt = Environment(trim_blocks=True).from_string(args.input.read())

        for dim in dims:
            complete_dim(dim)
        args.output.write(tplt.render(dims=dims))
