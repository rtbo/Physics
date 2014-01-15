
TEMPLATE = subdirs

SUBDIRS += \
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
    templates/QPhysicsDesigner/*.template
