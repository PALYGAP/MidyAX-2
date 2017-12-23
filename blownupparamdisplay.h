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

#ifndef BLOWNUPPARAMDISPLAY_H
#define BLOWNUPPARAMDISPLAY_H

#include <QDialog>
#include "MidyAX_types.h"

namespace Ui {
class BlownUpParamDisplay;
}

class BlownUpParamDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit BlownUpParamDisplay(QWidget *parent = 0);
    ~BlownUpParamDisplay();

//private slots:
    void updateBlownUpParamDisplay( int posi, struct mappingTable theMappingTable[], double paramValue );
    void updateBlownUpParamDisplayMOD1( int posi, struct pageMappingTable pageMappingTable[], double paramValue, QString *controllerName );
    void updateBlownUpParamDisplayMOD1( int posi, struct CCpageMappingTable pageMappingTable[], int MIDIVal, QString *controllerName );

private:
    Ui::BlownUpParamDisplay *ui;

    QPalette m_slidderPalette;
    QByteArray m_geom;

    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);


};

#endif // BLOWNUPPARAMDISPLAY_H
