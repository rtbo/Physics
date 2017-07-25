import qbs
import qbs.FileInfo
import qbs.TextFile

import 'phcgfuncs.js' as PhCgFuncs

Module {

    property path script: "PhysicsCodeGen.py"
    property path data: "PhysicsData.json"

    Rule {
        inputs: ["glob_hpp_template"]
        Artifact {
            filePath: {
                var rp = PhCgFuncs.getSrcRelativePath(product, FileInfo.path(input.filePath));
                var of = FileInfo.joinPaths(rp, input.completeBaseName);
                return of;
            }
            fileTags: ["generated_glob_hpp", "hpp"]
        }

        prepare: {
            var script = product.moduleProperty("phcg", "script");
            var data = product.moduleProperty("phcg", "data");
            var cmd = new Command("python", [
                script, "--mode", "glob", "--datafile", data,
                "--input", input.filePath, "--output", output.filePath
            ]);
            cmd.highlight = "codegen";
            cmd.description = "generating "+output.fileName;
            return cmd;
        }
    }

    Rule {
        inputs: ["glob_cpp_template"]
        Artifact {
            filePath: {
                var rp = PhCgFuncs.getSrcRelativePath(product, FileInfo.path(input.filePath));
                var of = FileInfo.joinPaths(rp, input.completeBaseName);
                return of;
            }
            fileTags: ["generated_glob_cpp", "cpp"]
        }

        prepare: {
            var script = product.moduleProperty("phcg", "script");
            var data = product.moduleProperty("phcg", "data");
            var cmd = new Command("python", [
                script, "--mode", "glob", "--datafile", data,
                "--input", input.filePath, "--output", output.filePath
            ]);
            cmd.highlight = "codegen";
            cmd.description = "generating "+output.fileName;
            return cmd;
        }
    }

    Rule {
        inputs: ["item_hpp_template"]
        outputFileTags: ["generated_item_hpp", "hpp"]
        outputArtifacts: {
            var dp = product.moduleProperty("phcg", "data");
            var items = PhCgFuncs.getItems(dp);
            var oa = [];
            for (var i=0; i<items.length; ++i) {
                var item = items[i];
                var of = PhCgFuncs.outputItemPath(product, input, item);
                oa.push({
                    filePath: of
                });
            }
            return oa;
        }

        prepare: {
            var script = product.moduleProperty("phcg", "script");
            var dataPath = product.moduleProperty("phcg", "data");
            var items = PhCgFuncs.getItems(dataPath);
            var cmds = [];
            for (var i=0; i<items.length; ++i) {
                var item = items[i];
                var of = PhCgFuncs.outputItemPath(product, input, item);
                var cmd = new Command("python", [ script, "--help"]);
                var cmd = new Command("python", [
                    script, "--mode", "item", "--datafile", dataPath, "--item", item.name,
                    "--input", input.filePath,
                    "--output", FileInfo.joinPaths(product.buildDirectory, of)
                ]);
                cmd.highlight = "codegen";
                cmd.description = "generating "+FileInfo.fileName(of);
                cmds.push(cmd);
            }
            return cmds;
        }
    }

    Rule {
        inputs: ["item_cpp_template"]
        outputFileTags: ["generated_item_cpp", "cpp"]
        outputArtifacts: {
            var dp = product.moduleProperty("phcg", "data");
            var items = PhCgFuncs.getItems(dp);
            var oa = [];
            for (var i=0; i<items.length; ++i) {
                var item = items[i];
                var of = PhCgFuncs.outputItemPath(product, input, item);
                oa.push({
                    filePath: of
                });
            }
            return oa;
        }

        prepare: {
            var script = product.moduleProperty("phcg", "script");
            var dataPath = product.moduleProperty("phcg", "data");
            var items = PhCgFuncs.getItems(dataPath);
            var cmds = [];
            for (var i=0; i<items.length; ++i) {
                var item = items[i];
                var of = PhCgFuncs.outputItemPath(product, input, item);
                var cmd = new Command("python", [ script, "--help"]);
                var cmd = new Command("python", [
                    script, "--mode", "item", "--datafile", dataPath, "--item", item.name,
                    "--input", input.filePath,
                    "--output", FileInfo.joinPaths(product.buildDirectory, of)
                ]);
                cmd.highlight = "codegen";
                cmd.description = "generating "+FileInfo.fileName(of);
                cmds.push(cmd);
            }
            return cmds;
        }
    }
}
