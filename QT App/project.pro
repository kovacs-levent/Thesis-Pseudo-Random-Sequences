QT += widgets
CONFIG += c++11
SOURCES += \
    qwindow.cpp \
    main.cpp \
    legendrewindow.cpp \
    mainwindow.cpp \
    ../Arithmetics/ModArithmetic.cpp \
    ../Arithmetics/PrimeArithmetic.cpp \
    ../GeneralPRNG/SeedGenerator.cpp \
    ../LegendreConstruction/LegendreConstruction.cpp \
    ../RC4/RC4_PRG.cpp \
    rc4window.cpp

HEADERS += \
    qwindow.h \
    legendrewindow.h \
    mainwindow.h \
    ../GeneralPRNG/SeedGenerator.h  \
    ../Arithmetics/ModArithmetic.h \
    ../Arithmetics/PrimeArithmetic.h \
    ../LegendreConstruction/LegendreConstruction.h \
    rc4window.h \
    ../RC4/RC4_PRG.h
