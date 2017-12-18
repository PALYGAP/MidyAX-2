#ifndef PARAMMAPPING_H
#define PARAMMAPPING_H

#include <QDialog>

#include "axefx.h"
#include "MidyAX_types.h"

namespace Ui {
class ParamMapping;
}

class ParamMapping : public QDialog
{
    Q_OBJECT

public:
    explicit ParamMapping(QWidget *parent = 0);
    ~ParamMapping();

    void init( struct mappingTable *mappingTableElement );
    //void get_paramMapping( unsigned char *effectBlockID, unsigned char *effectParamID);
    void get_paramMapping( struct mappingTable *mappingTableElement );
    void loadEffectBlocks();
    void loadParameters( int effectBlockNum );

private slots:
    void on_cboEffectBlock_currentIndexChanged(int index);
    void on_cboParameter_currentIndexChanged(int index);
    void on_buttonBox_accepted();


private:
    Ui::ParamMapping *ui;

    unsigned char m_selectedBlockID;
    unsigned char m_selectedParamID;
    int m_selectedChanNumb;
    unsigned char m_selectedCCID;

    int m_sizeIndexToParam;
    struct mappingTable m_indexToParam[ 300 ];

    int m_prevChanNumb;
    int m_prevCCID;

};

#endif // PARAMMAPPING_H
