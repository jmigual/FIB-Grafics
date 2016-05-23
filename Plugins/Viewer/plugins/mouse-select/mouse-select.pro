TARGET     = $$qtLibraryTarget(mouse-select)  # Nom del plugin 
include(../common.pro)
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc

OTHER_FILES += \
    color.frag \
    color.vert
