import qbs
import qbs.FileInfo

Module {

    property path script: "PhysicsCodeGen.py"
    property path data: "PhysicsData.json"

    Rule {
        inputs: ["glob_hpp_template"]
        Artifact {
            filePath: {
                var rp = FileInfo.relativePath(product.sourceDirectory, FileInfo.path(input.filePath));
                var of = FileInfo.joinPaths(rp, input.completeBaseName);
                return of;
            }
            fileTags: ["generated_hpp"]
        }

//        outputFileTags: ["generated_headers"]
//        outputArtifacts: {
//            var i, infile;
//            var oa = [];
//            for (i=0; i<inputs.ph_globs.length; ++i) {
//                infile = inputs.ph_globs[i];
//                oa.push({
//                    filePath: FileInfo.joinPaths(
//                        "include/ph", FileInfo.completeBaseName(infile)
//                    ),
//                    fileTags: ["hpp"],
//                    cgInput: infile,
//                });
//            }
//            return oa;
//        }

        prepare: {
            var script = product.moduleProperty("phcg", "script");
            var data = product.moduleProperty("phcg", "data");
            var cmd = new Command("python", [
                script, "--mode", "glob", "--datafile", data,
                "--input", input.filePath, "--output", output.filePath
            ]);
            cmd.highlight = "codegen";
            cmd.description = input.filePath + " -> " + output.filePath
            return cmd;
        }

    }

}
