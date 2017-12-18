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
