import qbs 1.0

Project {

    property string phVersionMaj: "1"
    property string phVersionMin: "1"
    property string phVersionMic: "1"
    property string phVersionStr: {
        return phVersionMaj + "." + phVersionMin + "." + phVersionMic;
    }

    qbsSearchPaths: ["."]


    references: [
        "Physics/Physics.qbs",
        "QPhysics/QPhysics.qbs",
        "QPhysicsUI/QPhysicsUI.qbs",
        "QPhysicsDesigner/QPhysicsDesigner.qbs",

        "tests/tests.qbs"
    ]

    Product {
        // product to make the files available in QtCreator

        name: "CodeGen"

        files: [
            "PhysicsCodeGen.py",
            "PhysicsData.json"
        ]
    }
}
