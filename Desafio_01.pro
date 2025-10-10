TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
    algoritmos.cpp \
    main.cpp

HEADERS += \
    algoritmos.h

# Configuración para copiar la carpeta de dataset al directorio de compilación
DESTDIR = $$OUT_PWD
dataset.path = $$OUT_PWD/dataset_encriptado_4
dataset.files = $$PWD/dataset_encriptado_4/*
COPIES += dataset
