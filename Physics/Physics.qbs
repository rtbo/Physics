import qbs
import qbs.FileInfo
import qbs.TextFile

Product {
    Depends { name: "phcg" }
    Depends { name: "cpp" }

    name: "Physics"
    type: ["hpp"]

    phcg.script: "../PhysicsCodeGen.py"
    phcg.data: "../PhysicsData.json"

    Group {
        name: "Hand-written"
        files: [
            "include/ph/Operators.hpp",
            "include/ph/Physics.hpp",
            "include/ph/Constants.hpp",
            "include/ph/Zero.hpp",
        ]
    }

    Group {
        name: "Templates"
        files: [
            "include/ph/FwdDecl.hpp.ph_gt",
            "include/ph/Literals.hpp.ph_gt",
            "include/ph/_IncludeAll.hpp.ph_gt",
            "include/ph/Item.hpp.ph_it",

            "include/ph/Version.hpp.in",
        ]
    }

    FileTagger {
        patterns: ["*.in"]
        fileTags: ["version_template"]
    }

    Rule {
        inputs: ["version_template"]
        Artifact {
            fileTags: ["hpp"]
            filePath: "include/ph/Version.hpp"
        }
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.highlight = "codegen";
            cmd.description = "generating Version.hpp";
            cmd.sourceCode = function() {
                var inf = new TextFile(input.filePath, TextFile.ReadOnly);
                var content = inf.readAll();
                inf.close();

                content = content.replace("##VERSION_MAJ##", project.phVersionMaj);
                content = content.replace("##VERSION_MIN##", project.phVersionMin);
                content = content.replace("##VERSION_MIC##", project.phVersionMic);
                content = content.replace("##VERSION_STR##", project.phVersionStr);

                var outf = new TextFile(output.filePath, TextFile.WriteOnly);
                outf.write(content);
                outf.close();
            };
            return cmd;
        }
    }

    Export {
        Depends {name: "cpp"}

        cpp.includePaths: [
            "include",
            FileInfo.joinPaths(product.buildDirectory, "include")
        ]

        cpp.cxxLanguageVersion: "c++14"
    }
}
