
TEMPLATE = subdirs

SUBDIRS += \
    QPhysics \
    QPhysicsUI \
    QPhysicsDesigner \
	tests


HEADERS = \
	include/physics/*.hpp

OTHER_FILES = \
    *.txt \
	PhysicsGenerator.py \
    templates/*.template \
    templates/QPhysics/*.template \
    templates/QPhysicsUI/*.template \
    templates/QPhysicsDesigner/*.template
