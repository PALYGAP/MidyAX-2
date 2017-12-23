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

#ifndef CCMAPPINGMOD1_H
#define CCMAPPINGMOD1_H

#include <QDialog>

#include "axefx.h"
#include "MidyAX_types.h"

namespace Ui {
class CCMapping;
}

class CCMapping : public QDialog
{
    Q_OBJECT

public:
    explicit CCMapping(QWidget *parent = 0);
    ~CCMapping();

    void init( struct CCpageMappingTable *mappingTableElement );
    void get_paramMapping( struct CCpageMappingTable *mappingTableElement );
    void loadCCList(void);

private slots:
    void on_buttonBox_accepted();
    void on_cboControlName_currentIndexChanged(int index);

private:
    Ui::CCMapping *ui;
    QPalette localpalette;

    int m_sizeIndexToParam;
    struct mappingTable m_indexToParam[ 300 ];

    int m_prevChanNumb;
    int m_prevCCID;

    int m_selectedControlNumber;
    int m_selectedControlCC;
};

#endif // CCMAPPING_H
