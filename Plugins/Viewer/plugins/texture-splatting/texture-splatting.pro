TARGET     = $$qtLibraryTarget(texture-splatting)  # Nom del plugin 
include(../common.pro)
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc

OTHER_FILES += \
    splat.vert \
    splat.frag
