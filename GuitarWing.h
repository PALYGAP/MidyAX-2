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

#ifndef GUITARWING_H
#define GUITARWING_H

#include "ui_GuitarWing.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class GuitarWing;
}


class GuitarWing : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit GuitarWing(QWidget *parent = 0);
    ~GuitarWing();

    void init( void);

private:
    Ui::GuitarWing *ui;
};

#endif // GUITARWING_H
