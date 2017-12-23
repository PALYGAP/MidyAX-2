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

#ifndef QUNEO_H
#define QUNEO_H

#include "ui_QuNeo.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class QuNeo;
}


class QuNeo : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit QuNeo(QWidget *parent = 0);
    ~QuNeo();

    void init( void);

private:
    Ui::QuNeo *ui;
};

#endif // QUNEO_H
