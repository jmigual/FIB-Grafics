TARGET     = $$qtLibraryTarget(shadowmap)  # Nom del plugin 

QMAKE_CXXFLAGS += -std=c++11

include(../common.pro)

RESOURCES += \
    res.qrc

