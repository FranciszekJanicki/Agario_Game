TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        collision.cpp \
        customball.cpp \
        enemyball.cpp \
        foodball.cpp \
        main.cpp \
        playerball.cpp

HEADERS += \
    collision.h \
    customball.h \
    enemyball.h \
    foodball.h \
    playerball.h

    INCLUDEPATH += "C:/SFML-2.5.1/include"

    LIBS += -L"C:/SFML-2.5.1/lib"
    CONFIG(debug, debug|release){
        LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
    } else {
        LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
    }

