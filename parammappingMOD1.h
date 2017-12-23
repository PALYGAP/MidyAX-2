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

#ifndef PARAMMAPPINGMOD1_H
#define PARAMMAPPINGMOD1_H

#include <QDialog>

#include "axefx.h"
#include "MidyAX_types.h"

namespace Ui {
class ParamMappingMOD1;
}

class ParamMappingMOD1 : public QDialog
{
    Q_OBJECT

public:
    explicit ParamMappingMOD1(QWidget *parent = 0);
    ~ParamMappingMOD1();

    void init( struct pageMappingTable *mappingTableElement );
    //void get_paramMapping( unsigned char *effectBlockID, unsigned char *effectParamID);
    void get_paramMapping( struct pageMappingTable *mappingTableElement );
    void loadEffectBlocks();
    void loadParameters( int effectBlockNum );

private slots:
    void on_cboEffectBlock_currentIndexChanged(int index);
    void on_cboParameter_currentIndexChanged(int index);
    void on_buttonBox_accepted();


private:
    Ui::ParamMappingMOD1 *ui;
    QPalette localpalette;

    unsigned char m_selectedBlockID;
    unsigned char m_selectedParamID;

    int m_sizeIndexToParam;
    struct mappingTable m_indexToParam[ 300 ];

    int m_prevChanNumb;
    int m_prevCCID;

};

#endif // PARAMMAPPING_H
