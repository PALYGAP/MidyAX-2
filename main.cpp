/////////////////////////////////////////////////////////////////////////////////////////////////////
// PROGRAM:     MidyAX 2 - MIDI communications orchestrator - MIDI controllers to AXE-FX           //
// AIM:         Provide enhanced usability of the AXE-FX by making it possible to set the          //
//              AXE-FX parameters with a hardware interface (knobs/switches of a MIDI controller   //
//              like : BCR2000 /BCF2000, XTouch Mini, BeatStep, Guitar Wing ... )                  //
// CREATOR:     Eric FEUILLEAUBOIS                                                                 //
// PROG ENV:    Qt v5.6 or above, RTMIDI library (https://github.com/thestk/rtmidi)                //
// HARDWARE:    Tested on RPi / PC / MAC / Linux Box / Pipo X8                                     //
// LICENSE:     GNU GPL v3 - That means OPEN SOFWARE, COPYLEFT and hope it's useful to you         //
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include "midyax.h"
#include <QApplication>
#include "constants.h"
#include <QFontDatabase>

quint8 CCtoAXE[16][128][3];

MidyAX* g_pMidyAXDlgInstance;

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QSTR_ORGNAME);
    QCoreApplication::setOrganizationDomain(QSTR_DOMAIN);
    QCoreApplication::setApplicationName(QSTR_APPNAME);

    QApplication a(argc, argv);

    MidyAX w;
    g_pMidyAXDlgInstance = &w;

    // Load the embedded font.
    QString fontPath = ":/font/arial.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font("MyFont");
        a.setFont(font);
    }

    QString iconPath = ":/new/icon/MidyAX.icns";
    QApplication::setWindowIcon(QIcon(iconPath));

    w.show();

    return a.exec();

}

