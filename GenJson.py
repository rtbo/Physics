# Python script that opens "Dimensions.ods" document, reads content and prints "Dimensions.json".
# Two ways to use this:
#   - from within the document, just press the "Generate JSON" button
#   - from a python interpreter: ensure libreoffice is started as server before running:
#     $ libreoffice --invisible --accept="socket,host=localhost,port=2002;urp;StarOffice.ServiceManager"
# If modifying this program, please think about running "UpdateUnoScript.py" to load a copy in the
# document.

import os

SkipCol = 0
NameCol = 1
MCol = 2
LCol = 3
TCol = 4
ICol = 5
ThCol = 6
NCol = 7
JCol = 8
UnitCol = 9

SkipAliasCol = 0
FromAliasCol = 1
NameAliasCol = 2
UnitAliasCol = 3

class UnitDef:
    def __init__(self, name):
        self.name = name
        self.symbol = ""
        self.unicode = ""

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
    name = ws.getCellByPosition(col, row).String
    foreign = ws.getCellByPosition(col+3, row).String
    if name != "":
        unit = UnitDef(name)
        unit.symbol = ws.getCellByPosition(col+1, row).String
        unit.unicode = ws.getCellByPosition(col+2, row).String
        dim.units.append(unit)
    elif foreign != "":
        dim.foreign_units.append(foreign)

def completeAliases(ws, dim):
    for row in range(1, 10000):
        dimName = ws.getCellByPosition(FromAliasCol, row).String
        if dimName == "":
            break
        elif dimName == dim.name and ws.getCellByPosition(SkipCol, row).Value != 1:
            dim.aliases.append(
                ws.getCellByPosition(NameAliasCol, row).String
            )
            completeUnitDef(ws, UnitAliasCol, row, dim)

def readDimensions(calc):
    ws = calc.Sheets.getByName("DimTable")
    aliasWs = calc.Sheets.getByName("Aliases")
    dims = []
    for row in range(1, 10000):
        name = ws.getCellByPosition(NameCol, row).String
        if name == "":
            break
        elif ws.getCellByPosition(SkipCol, row).Value != 1:
            dim = Dimension(name)
            dim.M = int(ws.getCellByPosition(MCol, row).Value)
            dim.L = int(ws.getCellByPosition(LCol, row).Value)
            dim.T = int(ws.getCellByPosition(TCol, row).Value)
            dim.I = int(ws.getCellByPosition(ICol, row).Value)
            dim.Th = int(ws.getCellByPosition(ThCol, row).Value)
            dim.N = int(ws.getCellByPosition(NCol, row).Value)
            dim.J = int(ws.getCellByPosition(JCol, row).Value)
            completeUnitDef(ws, UnitCol, row, dim)
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
                f.write('        "unicode": "{}"\n'.format(unit.unicode))
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
    calc = XSCRIPTCONTEXT.getDocument()
    cell = calc.Sheets[0]['O8']
    srcDir = os.path.dirname(calc.URL.replace("file://", ""))
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


