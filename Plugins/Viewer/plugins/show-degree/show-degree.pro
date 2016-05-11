TARGET     = $$qtLibraryTarget(show-degree)

include(../common.pro)

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc

OTHER_FILES += \
    show-degree.frag \
    show-degree.vert
