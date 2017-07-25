
var TextFile = require("qbs.TextFile");
var FileInfo = require("qbs.FileInfo");

function getItems(dataPath)
{
    var df = new TextFile(dataPath, TextFile.ReadOnly);
    var items = JSON.parse(df.readAll());
    df.close();
    return items;
}

function itemTitleName(item)
{
    return item.name.charAt(0).toUpperCase() + item.name.slice(1);
}

function getSrcRelativePath(product, path)
{
    return FileInfo.relativePath(product.sourceDirectory, path);
}

function outputItemPath(product, input, item)
{
    var rp = getSrcRelativePath(product, FileInfo.path(input.filePath));
    return FileInfo.joinPaths(rp, input.completeBaseName)
            .replace("Item", itemTitleName(item));
}
