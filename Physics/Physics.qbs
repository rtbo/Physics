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
        name: "Templates"
        files: [
            "include/ph/FwdDecl.hpp.ph_gt",
            "include/ph/Literals.hpp.ph_gt",
            "include/ph/_IncludeAll.hpp.ph_gt",
            "include/ph/Item.hpp.ph_it",
        ]
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
