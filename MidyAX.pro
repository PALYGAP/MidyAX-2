#-------------------------------------------------
#
# Project created by QtCreator 2014-07-06T06:29:55
#
#-------------------------------------------------

QT       += core gui uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MidyAX
TEMPLATE = app

VERSION_MAJOR = 0
VERSION_MINOR = 8
VERSION_BUILD = 2

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}


contains(QT_VERSION, ^4\\.[0-7]\\..*) {
    message("Cannot build program with Qt $${QT_VERSION}")
    error("Use Qt 4.8 or newer")
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += VERSION=$$VERSION


linux*:!simulator {
    DEFINES += __LINUX_ALSA__
    DEFINES += __LINUX_ALSASEQ__
    DEFINES += __RTMIDI_DEBUG__   #WILL ISSUE RTMIDI DEBUG WARNINGs
    DEFINES += AVOID_TIMESTAMPING
    DEFINES += RAWKBD_SUPPORT
    CONFIG += link_pkgconfig x11

#    LIBS += -lpthread -lasound
    LIBS += -lasound
    jack_midi {
        PKGCONFIG += jack
        DEFINES += __LINUX_JACK__
    }
    #QMAKE_CXXFLAGS = -fpermissive -lstdc++ -x c++
}

macx {
    CONFIG += x86 static
    DEFINES += __MACOSX_CORE__
    DEFINES += RAWKBD_SUPPORT
    QMAKE_BUNDLE_DATA += BUNDLE_RES
    LIBS += -framework \
        CoreMidi \
        -framework \
        CoreAudio \
        -framework \
        CoreFoundation \
        -framework \
        Carbon
    LIBS += -stdlib=libc++
    QMAKE_CXXFLAGS = -fpermissive -stdlib=libc++ -std=c++11
}

win32 {
    DEFINES += __WINDOWS_MM__
    LIBS += -lwinmm
    LIBS += -lws2_32
}

win32:!simulator {
    DEFINES += RAWKBD_SUPPORT
}

debug:DEFINES += __RTMIDI_DEBUG__
INCLUDEPATH += src




SOURCES += main.cpp\
        midyax.cpp \
    RtMidi.cpp \
    midisetup.cpp \
    midimapping.cpp \
    bcf2000.cpp \
    qlineeditmod1.cpp \
    qslidermod1.cpp \
    parammapping.cpp \
    blownupparamdisplay.cpp \
    sweepparamswithextcont.cpp \
    ampsguts.cpp \
    aboutmidyax.cpp \
    prefs.cpp \
    bcr2000.cpp \
    midicontrollergenericdialog.cpp \
    XTouchMini.cpp \
#    customdial.cpp \
    BeatStep.cpp \
    fcb1010.cpp \
    midicontrollergenericdialogmod1.cpp \
#    midiknob.cpp
    qsynthDialClassicStyle.cpp \
    qsynthKnob.cpp \
    parammappingMOD1.cpp \
    GuitarWing.cpp \
    QuNeo.cpp \
    CCmapping.cpp \
    QuNeoVR.cpp

HEADERS  += midyax.h \
    RtMidi.h \
    constants.h \
    mididefs.h \
    midisetup.h \
    events.h \
    midimapping.h \
    axefx.h \
    axefxparam.h \
    bcf2000.h \
    qlineeditmod1.h \
    qslidermod1.h \
    parammapping.h \
    blownupparamdisplay.h \
    sweepparamswithextcont.h \
    ampsguts.h \
    aboutmidyax.h \
    prefs.h \
    bcr2000.h \
    midicontrollergenericdialog.h \
    XTouchMini.h \
 #   customdial.h \
 #   CustomDial.hpp \
    BeatStep.h \
    fcb1010.h \
    MidyAX_types.h \
    midicontrollergenericdialogmod1.h \
#    midiknob.h
    qsynthDialClassicStyle.h \
    qsynthKnob.h \
    parammappingMOD1.h \
    GuitarWing.h \
    QuNeo.h \
    CCmapping.h \
    QuNeoVR.h

FORMS    += midyax.ui \
    midisetup.ui \
    midimapping.ui \
    bcf2000.ui \
    parammapping.ui \
    blownupparamdisplay.ui \
    sweepparamswithextcont.ui \
    ampsguts.ui \
    aboutmidyax.ui \
    prefs.ui \
    bcr2000.ui \
    XTouchMini.ui \
    BeatStep.ui \
    fcb1010.ui \
    parammappingMOD1.ui \
    GuitarWing.ui \
    QuNeo.ui \
    CCmapping.ui \
    QuNeoVR.ui

include(updateqm.pri)

RESOURCES += \
    CCtoAX.qrc
