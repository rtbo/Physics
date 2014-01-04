
TEMPLATE = subdirs

SUBDIRS += \
    QPhysics \
    QPhysicsDesigner \
	tests


HEADERS = \
	include/physics/*.hpp

OTHER_FILES = \
    *.txt \
	PhysicsGenerator.py \
    templates/*.template \
    templates/QPhysics/*.template \
    templates/QPhysicsDesigner/*.template
