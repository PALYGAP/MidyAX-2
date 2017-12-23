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

#include <QCloseEvent>

#include "XTouchMini.h"


XTouchMini::XTouchMini(QWidget *parent) :
    //After MOD1 ---- MIDIControllerGenericDialog(parent, QString("X-TOUCH"), XTOUCHMINI_MC, 8, 0, 8, 16), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    MIDIControllerGenericDialogMOD1(parent, QString("X-TOUCH"), XTOUCHMINI_MC, 8, 0, 8, 16), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::XTouchMini)
{
    ui->setupUi(this);
    init();
}

XTouchMini::~XTouchMini()
{
    delete ui;
}

void XTouchMini::init( void)
{
    m_initMode = true;
    m_initMode_timer.start();

    //After MOD1 ---- MIDIControllerGenericDialog::init( );
    MIDIControllerGenericDialogMOD1::init( );

    constructWidgetLists( &ui->gridLayoutWidget );

    connectWidgetOnDialog();

    // Initiate the KNOBS elements
    //after MOD1 ---- fillComboBox();
    updateKnobsDisplay();

    m_initMode = false;
    this->update();
}
