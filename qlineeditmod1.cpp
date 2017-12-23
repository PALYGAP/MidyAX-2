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

#include "qlineeditmod1.h"

QLineEditMod1::QLineEditMod1( QWidget * parent ) : QLineEdit(parent)
{
}

void QLineEditMod1::setTextFromInt(int value)
{
    double dVal = value;
    dVal /= double(1000);
    if( dVal < 100)    QLineEdit::setText( QString::number( dVal, 'f', 2 ) );
    else QLineEdit::setText( QString::number( dVal, 'f', 0 ) );
}
