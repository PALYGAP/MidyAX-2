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

#include "fcb1010.h"
#include "ui_fcb1010.h"


FCB1010::FCB1010(QWidget *parent) :
    MIDIControllerGenericDialogMOD1(parent, QString("FCB1010"), FCB1010_MC, 2, 0, 10, 10), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::FCB1010)
{
    ui->setupUi(this);
    init();
}

FCB1010::~FCB1010()
{
    delete ui;
}

void FCB1010::init( void)
{
    m_initMode = true;
    m_initMode_timer.start();

    MIDIControllerGenericDialogMOD1::init();

    constructWidgetLists( &ui->gridLayoutWidget );

    MIDIControllerGenericDialogMOD1::connectWidgetOnDialog(); //TODO : Check why use base class fuction --> nees to overload it ?

   // Initiate the KNOBS elements
   updateKnobsDisplay();

   m_initMode = false;
   this->repaint();
}
