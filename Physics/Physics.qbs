import qbs
import qbs.FileInfo

Product {
    Depends { name: "phcg" }

    name: "Physics"
    type: ["generated_glob", "generated_item"]

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
        name: "Global templates"
        files: [
            "include/ph/FwdDecl.hpp.template",
            "include/ph/Literals.hpp.template",
            "include/ph/_IncludeAll.hpp.template",
        ]
        fileTags: ["glob_template"]
    }

    Group {
        name: "Item templates"
        files: [
            "include/ph/Item.hpp.template",
        ]
        fileTags: ["item_template"]
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
