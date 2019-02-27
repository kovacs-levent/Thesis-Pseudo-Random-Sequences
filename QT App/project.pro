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
    ../LegendreConstruction/LegendreConstruction.cpp

HEADERS += \
    qwindow.h \
    legendrewindow.h \
    mainwindow.h \
    ../GeneralPRNG/SeedGenerator.h  \
    ../Arithmetics/ModArithmetic.h \
    ../Arithmetics/PrimeArithmetic.h \
    ../LegendreConstruction/LegendreConstruction.h
