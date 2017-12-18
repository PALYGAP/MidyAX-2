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
