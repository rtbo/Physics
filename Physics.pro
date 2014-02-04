
TEMPLATE = subdirs

SUBDIRS += \
    QPhysics \
    QPhysicsUI \
    QPhysicsDesigner \
    tests


HEADERS = \
    include/ph/*.hpp

OTHER_FILES = \
    *.txt \
    PhysicsData.json \
    PhysicsGenerator.py \
    templates/*.template \
    templates/QPhysics/*.template \
    templates/QPhysicsUI/*.template \
    templates/QPhysicsDesigner/*.template
