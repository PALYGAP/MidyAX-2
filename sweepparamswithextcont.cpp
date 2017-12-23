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

#include "sweepparamswithextcont.h"
#include "ui_sweepparamswithextcont.h"


/*

  Maps to the External controllers --> By default number 12 on the AXE-FX --> Correspond to CC 27 in default setting of the AXE-FX
  Add the possibility to choose which External Controller it is mapped to --> Ext Contre 1 to 12
  Load/Save SweepParam mapping files and manage assignement to one of the 12 Ext Contr.

  Allow the change of up to 8 parameters (from different blocks) at the same time. Only allow parameters with modifiers to be sweeped. Forbid on/off and modal param?

  Pb. is in the preset thesweeped parameters are not present

  Graphically define the limits by setting the Min Max values on the slidders.

  Set "EXTERNAL CONTROLLER INITIAL VALUE 1–12," ??? see AXE-FX Docs

*/



sweepParamsWithExtCont::sweepParamsWithExtCont(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sweepParamsWithExtCont)
{
    ui->setupUi(this);
}

sweepParamsWithExtCont::~sweepParamsWithExtCont()
{
    delete ui;
}
