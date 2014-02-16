import qbs

Project {

    references: [
        "Physics/Physics.qbs",
        "QPhysics/QPhysics.qbs",
        "QPhysicsUI/QPhysicsUI.qbs",
        "QPhysicsDesigner/QPhysicsDesigner.qbs",

        "tests/tests.qbs"
    ]


    Product {
        name: "CodeGen"



    }
}
