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

#include "aboutmidyax.h"
#include "ui_aboutmidyax.h"

AboutMidyAX::AboutMidyAX(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMidyAX)
{
    ui->setupUi(this);
    ui->lblPALYGAPWebLink->setOpenExternalLinks(true);
    ui->lblNewsWebLink->setOpenExternalLinks(true);
    ui->lblCompileDate->setText(__DATE__);
    //ui->lblVersionID->setText("0.7.3");
    QString TheVersion = QString::number(VERSION_MAJOR)+"."+QString::number(VERSION_MINOR)+"."+QString::number(VERSION_BUILD);
    ui->lblVersionID->setText( TheVersion );
    //ui->lblVersionID->setText(VERSION); //TODO : use version from file MidyAX.pro
}

AboutMidyAX::~AboutMidyAX()
{
    delete ui;
}
