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
    SKIP    = 0
    NAME    = 1
    M       = 2
    L       = 3
    T       = 4
    I       = 5
    TH      = 6
    N       = 7
    J       = 8
    UNIT    = 9

class AliasCol(IntEnum):
    SKIP    = 0
    FROM    = 1
    NAME    = 2
    UNIT    = 3
    FACTOR  = 8
    OFFSET  = 9
    PI_EXP  = 10

class NonSiCol(IntEnum):
    SKIP    = 0
    NAME    = 1
    UNIT    = 2
    SYM     = 3
    UNICODE = 4
    FACTOR  = 5
    OFFSET  = 6
    PI_EXP  = 7

class UnitCol(IntEnum):
    NAME    = 0
    SYM     = 1
    UNICODE = 2
    PREFIX  = 3
    FOREIGN = 4

class UnitDef:
    def __init__(self, name):
        self.name = name
        self.symbol = ""
        self.unicode = ""
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
        self.aliases = []
        self.units = []
        self.foreign_units = []

def completeUnitDef(ws, col, row, dim):
    name = ws.getCellByPosition(col + UnitCol.NAME, row).String
    foreign = ws.getCellByPosition(col + UnitCol.FOREIGN, row).String
    if name != "":
        unit = UnitDef(name)
        unit.symbol = ws.getCellByPosition(col + UnitCol.SYM, row).String
        unit.unicode = ws.getCellByPosition(col + UnitCol.UNICODE, row).String
        prefixes = ws.getCellByPosition(col + UnitCol.PREFIX, row).String
        if prefixes != "":
            unit.prefixes = prefixes.split(", ")
        dim.units.append(unit)
    elif foreign != "":
        dim.foreign_units.append(foreign)

def completeAliases(ws, dim):
    for row in range(1, 10000):
        dimName = ws.getCellByPosition(AliasCol.FROM, row).String
        if dimName == "":
            break
        elif dimName == dim.name and ws.getCellByPosition(AliasCol.SKIP, row).Value != 1:
            dim.aliases.append(
                ws.getCellByPosition(AliasCol.NAME, row).String
            )
            completeUnitDef(ws, AliasCol.UNIT, row, dim)

def readDimensions(calc):
    ws = calc.Sheets.getByName("DimTable")
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
            completeUnitDef(ws, Col.UNIT, row, dim)
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
            for i, alias in enumerate(dim.aliases):
                f.write('"{}"'.format(alias))
                if i < len(dim.aliases)-1:
                    f.write(', ')
            f.write('],\n')

            f.write('    "units": [')
            for i, unit in enumerate(dim.units):
                if i == 0:
                    f.write('\n')
                f.write('      {\n')
                f.write('        "name": "{}",\n'.format(unit.name))
                f.write('        "symbol": "{}",\n'.format(unit.symbol))
                f.write('        "unicode": "{}",\n'.format(unit.unicode))
                f.write('        "prefixes": [')
                for i, prefix in enumerate(unit.prefixes):
                    f.write('"{}"'.format(prefix))
                    if i < len(unit.prefixes)-1:
                        f.write(', ')
                f.write(']\n')

                if i < len(dim.units)-1:
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


