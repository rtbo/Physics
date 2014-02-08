
TEMPLATE = subdirs
CONFIG += ordered

INCLUDEPATH += include

SUBDIRS += \
    Physics \
    QPhysics \
    QPhysicsUI \
    QPhysicsDesigner \
    tests


OTHER_FILES = \
    *.txt \
    PhysicsData.json \
    PhysicsGenerator.py \
    templates/*.template \
    templates/QPhysics/*.template \
    templates/QPhysicsUI/*.template \
    templates/QPhysicsDesigner/*.template
