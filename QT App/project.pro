QT += widgets
TARGET = pszeudoveletlen_szakdolgozat
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
    rc4window.cpp \
    ../AdditiveConstruction/AdditiveConstruction.cpp \
    additivewindow.cpp \
    ../ChaCha20/ChaCha20Construction.cpp \
    chachawindow.cpp \
    measurewindow.cpp \
    ../Measurements/measure.cpp \
    vernamwindow.cpp

HEADERS += \
    qwindow.h \
    legendrewindow.h \
    mainwindow.h \
    ../GeneralPRNG/SeedGenerator.h  \
    ../Arithmetics/ModArithmetic.h \
    ../Arithmetics/PrimeArithmetic.h \
    ../LegendreConstruction/LegendreConstruction.h \
    rc4window.h \
    ../RC4/RC4_PRG.h \
    ../AdditiveConstruction/AdditiveConstruction.h \
    additivewindow.h \
    ../ChaCha20/ChaCha20Construction.h \
    chachawindow.h \
    measurewindow.h \
    ../Measurements/measure.h \
    vernamwindow.h

DISTFILES += \
    dictionary
