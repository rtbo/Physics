import qbs
import qbs.FileInfo

Product {
    Depends { name: "phcg" }

    type: ["generated_glob_hpp", "generated_item_hpp"]
    name: "Physics"

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
        fileTags: ["glob_hpp_template"]
    }

    Group {
        name: "Item templates"
        files: [
            "include/ph/Item.hpp.template",
        ]
        fileTags: ["item_hpp_template"]
    }




    Export {
        Depends {name: "cpp"}
        cpp.includePaths: "include"

        cpp.cxxLanguageVersion: "c++14"
    }
}
