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

#ifndef BEATSTEP_H
#define BEATSTEP_H

#include "ui_BeatStep.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class BeatStep;
}


class BeatStep : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit BeatStep(QWidget *parent = 0);
    ~BeatStep();

    void init( void);

private:
    Ui::BeatStep *ui;
};

#endif // BEATSTEP_H
