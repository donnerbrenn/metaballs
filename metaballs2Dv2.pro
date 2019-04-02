TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=  -lsfml-graphics \
        -lsfml-system \
        -lsfml-window

SOURCES += \
        main.cpp \
    metaballs.cpp

HEADERS += \
    metaballs.h

DISTFILES += \
    metaball_fShader.glsl \
    metaball_vShader.glsl
