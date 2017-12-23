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

#ifndef PREFS_H
#define PREFS_H

#include <QDialog>
#include "midyax.h"

namespace Ui {
class Prefs;
}

class Prefs : public QDialog
{
    Q_OBJECT

public:
    explicit Prefs(QWidget *parent = 0);
    ~Prefs();
    void init(void);

private slots:
    void on_buttonBox_accepted();

    void on_cbxColoredSliders_toggled(bool checked);
    void on_cbxDisplayBlownUp_toggled(bool checked);
    void on_cbxAutoConnect_toggled(bool checked);

    void on_spnChanNumb_valueChanged(int arg1);

    void on_cbxColoredSliders_clicked(bool checked);

    void on_Prefs_accepted();

    void on_spnNumberInterval_valueChanged(int arg1);

    void on_cbxMIDIdataInterval_toggled(bool checked);


private:
    Ui::Prefs *ui;
    MidyAX* m_pMidyAXDlgInstance;
    bool m_autoConnect_seton;

    void displayInterval();
};

#endif // PREFS_H
