TARGET     = $$qtLibraryTarget(resaltar-seleccio)  # Nom del plugin 
include(../common.pro)
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc
