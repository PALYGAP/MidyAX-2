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

#include "prefs.h"
#include "ui_prefs.h"

#include "midyax.h"

extern bool g_sliderColored;
extern bool g_displayBlownUp;
extern bool g_autoConnect;
extern int g_MIDIdataInterval_NumberInterval;
extern double g_MIDIdataInterval_Interval;
extern bool g_MIDIdataInterval;

Prefs::Prefs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prefs),
    m_autoConnect_seton(false)
{
    ui->setupUi(this);
    m_pMidyAXDlgInstance = qobject_cast<MidyAX*>(this->parent());

    init();
}

Prefs::~Prefs()
{
    delete ui;
}

void Prefs::init( void)
{
    ui->cbxColoredSliders->setChecked( g_sliderColored );
    ui->cbxDisplayBlownUp->setChecked( g_displayBlownUp );
    ui->cbxAutoConnect->setChecked( g_autoConnect );
    ui->spnChanNumb->setValue( m_pMidyAXDlgInstance->m_AXEFXChanNumb);
    ui->cbxMIDIdataInterval->setChecked( g_MIDIdataInterval );
    ui->spnNumberInterval->setValue( g_MIDIdataInterval_NumberInterval );
    displayInterval();
//    g_MIDIdataInterval_Interval = g_MIDIdataInterval_NumberInterval * 0.05;
//    ui->ledInterval->setText( QString::number( g_MIDIdataInterval_Interval, 'g', 2 ) );

}

void Prefs::on_buttonBox_accepted()
{
    if( m_autoConnect_seton)
    {
        m_pMidyAXDlgInstance->autoConnect();
        m_pMidyAXDlgInstance->refreshConnections();
    }
    m_pMidyAXDlgInstance->getMidiMappingParamValues( false );
    return;
}

void Prefs::on_cbxColoredSliders_toggled(bool checked)
{
    g_sliderColored = checked;
}

void Prefs::on_cbxDisplayBlownUp_toggled(bool checked)  {       g_displayBlownUp = checked; }

void Prefs::on_cbxAutoConnect_toggled(bool checked)
{
    g_autoConnect = checked;
    if( checked) m_autoConnect_seton = true;
    else m_autoConnect_seton = false;
}

void Prefs::on_spnChanNumb_valueChanged(int arg1)
{
    MidyAX *m_pMidyAXDlgInstance = qobject_cast<MidyAX*>(this->parent());

    m_pMidyAXDlgInstance->m_AXEFXChanNumb = arg1;
}

void Prefs::on_cbxColoredSliders_clicked(bool checked)
{
    g_sliderColored = checked;
}

void Prefs::on_spnNumberInterval_valueChanged(int arg1)
{
    g_MIDIdataInterval_NumberInterval = arg1;
    g_MIDIdataInterval_Interval = arg1 * 0.05;
    displayInterval();
}

void Prefs::on_cbxMIDIdataInterval_toggled(bool checked)
{
    g_MIDIdataInterval = checked;
    displayInterval();
}

void Prefs::displayInterval()
{
    if( ui->cbxMIDIdataInterval->isChecked() )
    {
        g_MIDIdataInterval_Interval = g_MIDIdataInterval_NumberInterval * 0.05;
        ui->ledInterval->setText( QString::number( g_MIDIdataInterval_Interval, 'g', 2 ) );
    }
    else{
        ui->ledInterval->setText( QString::number( 0 ) );
    }
}






void Prefs::on_Prefs_accepted()
{

}
