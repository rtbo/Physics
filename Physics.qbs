import qbs 1.0

Project {

    references: [
        "Physics/Physics.qbs",
        "QPhysics/QPhysics.qbs",
        "QPhysicsUI/QPhysicsUI.qbs",
        "QPhysicsDesigner/QPhysicsDesigner.qbs",

        //"tests/tests.qbs"
    ]

    qbsSearchPaths: ["."]

    Product {
        // product to make the files available in QtCreator

        name: "CodeGen"

        Group {
            name: "script"
            files: [
                "PhysicsGenerator.py",
                "PhysicsCodeGen.py"
            ]
            fileTags: ["cg_script"]
        }

        Group {
            name: "data"
            files: [
                "PhysicsData.json"
            ]
            fileTags: ["cg_data"]
        }


    }
}
