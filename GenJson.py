# Python script that opens "Dimensions.ods" document, reads content and prints "Dimensions.json".
# Two ways to use this:
#   - from within the document, just press the "Generate JSON" button
#   - from a python interpreter: ensure libreoffice is started as server before running:
#     $ libreoffice --invisible --accept="socket,host=localhost,port=2002;urp;StarOffice.ServiceManager"
# If modifying this program, please think about running "UpdateUnoScript.py" to load a copy in the
# document.

import os

from enum import IntEnum

class Col(IntEnum):
    SKIP        = 0
    NAME        = 1
    M           = 2
    L           = 3
    T           = 4
    I           = 5
    TH          = 6
    N           = 7
    J           = 8

class UnitCol(IntEnum):
    SKIP        = 0
    DIM         = 1
    NAME        = 2
    SYM         = 3
    UNICODE     = 4
    FACTOR      = 5
    OFFSET      = 6
    PI_EXP      = 7
    PREFIX      = 8
    DEF_PREF    = 9
    FOREIGN     = 10

class AliasCol(IntEnum):
    SKIP        = 0
    DIM         = 1
    NAME        = 2

class UnitDef:
    def __init__(self):
        self.name = ""
        self.symbol = ""
        self.unicode = ""
        self.factor = ""
        self.offset = ""
        self.pi_exp = ""
        self.prefixes = []

class Dimension:
    def __init__(self, name):
        self.name = name
        self.M = 0
        self.L = 0
        self.T = 0
        self.I = 0
        self.Th = 0
        self.N = 0
        self.J = 0
        self.units = []
        self.foreign_units = []
        self.aliases = []

def completeUnits(ws, dim):
    for row in range(1, 10000):
        dim_name = ws.getCellByPosition(UnitCol.DIM, row).String
        if dim_name == "":
            break
        elif dim_name == dim.name and ws.getCellByPosition(UnitCol.SKIP, row).String != "1":
            name = ws.getCellByPosition(UnitCol.NAME, row).String
            foreign = ws.getCellByPosition(UnitCol.FOREIGN, row).String
            if name != "":
                unit = UnitDef()
                unit.name = name
                unit.symbol = ws.getCellByPosition(UnitCol.SYM, row).String
                unit.unicode = ws.getCellByPosition(UnitCol.UNICODE, row).String
                unit.factor = ws.getCellByPosition(UnitCol.FACTOR, row).String
                unit.offset = ws.getCellByPosition(UnitCol.OFFSET, row).String
                unit.pi_exp = ws.getCellByPosition(UnitCol.PI_EXP, row).String
                unit.def_pref = ws.getCellByPosition(UnitCol.DEF_PREF, row).String
                prefixes = ws.getCellByPosition(UnitCol.PREFIX, row).String
                if prefixes != "":
                    unit.prefixes = prefixes.split(", ")
                dim.units.append(unit)
            else:
                assert foreign != ""
                dim.foreign_units.append(foreign)

def completeAliases(ws, dim):
    for row in range(1, 10000):
        dimName = ws.getCellByPosition(AliasCol.DIM, row).String
        if dimName == "":
            break
        elif dimName == dim.name and ws.getCellByPosition(AliasCol.SKIP, row).Value != 1:
            dim.aliases.append(
                ws.getCellByPosition(AliasCol.NAME, row).String
            )

def readDimensions(calc):
    ws = calc.Sheets.getByName("DimTable")
    unitWs = calc.Sheets.getByName("Units")
    aliasWs = calc.Sheets.getByName("Aliases")
    dims = []
    for row in range(1, 10000):
        name = ws.getCellByPosition(Col.NAME, row).String
        if name == "":
            break
        elif ws.getCellByPosition(Col.SKIP, row).Value != 1:
            dim = Dimension(name)
            dim.M = int(ws.getCellByPosition(Col.M, row).Value)
            dim.L = int(ws.getCellByPosition(Col.L, row).Value)
            dim.T = int(ws.getCellByPosition(Col.T, row).Value)
            dim.I = int(ws.getCellByPosition(Col.I, row).Value)
            dim.Th = int(ws.getCellByPosition(Col.TH, row).Value)
            dim.N = int(ws.getCellByPosition(Col.N, row).Value)
            dim.J = int(ws.getCellByPosition(Col.J, row).Value)
            completeUnits(unitWs, dim)
            completeAliases(aliasWs, dim)
            dims.append(dim)
    return dims

def printDimensionsJson(dims, path):
    with open(path, "w") as f:
        f.write('[\n')
        for di, dim in enumerate(dims):
            f.write('  {\n')
            f.write('    "name": "{}",\n'.format(dim.name))

            f.write('    "aliases": [')
            for ai, alias in enumerate(dim.aliases):
                f.write('"{}"'.format(alias))
                if ai < len(dim.aliases)-1:
                    f.write(', ')
            f.write('],\n')

            f.write('    "units": [')
            for ui, unit in enumerate(dim.units):
                if ui == 0:
                    f.write('\n')
                f.write('      {\n')
                f.write('        "name": "{}",\n'.format(unit.name))
                f.write('        "symbol": "{}",\n'.format(unit.symbol))
                f.write('        "unicode": "{}",\n'.format(unit.unicode.replace(r'\u', r'\\u')))
                f.write('        "factor": "{}",\n'.format(unit.factor))
                f.write('        "offset": "{}",\n'.format(unit.offset))
                f.write('        "pi_exp": "{}",\n'.format(unit.pi_exp))
                f.write('        "def_pref": "{}",\n'.format(unit.def_pref))

                f.write('        "prefixes": [')
                for pi, prefix in enumerate(unit.prefixes):
                    f.write('"{}"'.format(prefix))
                    if pi < len(unit.prefixes)-1:
                        f.write(', ')
                f.write(']\n')

                if ui < len(dim.units)-1:
                    f.write('      },\n')
                else:
                    f.write('      }\n')
                    f.write('    ')
            f.write('],\n')

            f.write('    "foreign_units": [')
            for i, foreign in enumerate(dim.foreign_units):
                f.write('"{}"'.format(foreign))
                if i < len(dim.foreign_units)-1:
                    f.write(', ')
            f.write('],\n')

            f.write('    "M": {},\n'.format(dim.M))
            f.write('    "L": {},\n'.format(dim.L))
            f.write('    "T": {},\n'.format(dim.T))
            f.write('    "I": {},\n'.format(dim.I))
            f.write('    "Th": {},\n'.format(dim.Th))
            f.write('    "N": {},\n'.format(dim.N))
            f.write('    "J": {}\n'.format(dim.J))

            if di < len(dims)-1:
                f.write('  },\n')
            else:
                f.write('  }\n')
        f.write(']\n')


def driver(calc, jsonPath):
    dims = readDimensions(calc)
    printDimensionsJson(dims, jsonPath)

def gen_json(event):
    import uno
    calc = XSCRIPTCONTEXT.getDocument()
    srcDir = os.path.dirname(uno.fileUrlToSystemPath(calc.URL))
    jsonPath = os.path.join(srcDir, "Dimensions.json")
    driver(calc, jsonPath)

if __name__ == "__main__":
    import uno
    from com.sun.star.beans import PropertyValue

    localCtx = uno.getComponentContext()
    conn = localCtx.ServiceManager.createInstanceWithContext(
        "com.sun.star.bridge.UnoUrlResolver", localCtx
    )
    ctx = conn.resolve("uno:socket,host=localhost,port=2002;urp;StarOffice.ComponentContext")
    desktop = ctx.ServiceManager.createInstanceWithContext("com.sun.star.frame.Desktop", ctx)

    hidden = PropertyValue()
    hidden.Name = "Hidden"
    hidden.Value = True

    srcDir = os.path.dirname(os.path.realpath(__file__))
    calcPath = os.path.join(srcDir, "Dimensions.ods")
    calc = desktop.loadComponentFromURL(
        uno.systemPathToFileUrl(calcPath), "_blank", 0, [hidden]
    )

    jsonPath = os.path.join(srcDir, "Dimensions.json")
    driver(calc, jsonPath)

    calc.dispose()
    desktop.dispose()


