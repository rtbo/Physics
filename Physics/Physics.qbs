import qbs
import qbs.FileInfo

Product {
    Depends { name: "phcg" }

    type: ["generated_hpp"]
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
            "../templates/Item.hpp.template",
        ]
        fileTags: ["item_templates"]
    }




    Export {
        Depends {name: "cpp"}
        cpp.includePaths: "include"

        cpp.cxxLanguageVersion: "c++14"
    }
}
