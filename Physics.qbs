import qbs 1.0

Project {

    references: [
        "Physics/Physics.qbs",
        "QPhysics/QPhysics.qbs",
        "QPhysicsUI/QPhysicsUI.qbs",
        "QPhysicsDesigner/QPhysicsDesigner.qbs",

        "tests/tests.qbs"
    ]

    qbsSearchPaths: ["."]

    Product {
        // product to make the files available in QtCreator

        name: "CodeGen"

        files: [
            "PhysicsCodeGen.py",
            "PhysicsData.json"
        ]
    }
}
