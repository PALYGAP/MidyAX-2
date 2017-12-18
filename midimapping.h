#ifndef MIDIMAPPING_H
#define MIDIMAPPING_H

#include "ui_midimapping.h"
#include <QDialog>
#include "MidyAX_types.h"

class MidyAX;

class MidiMapping : public QDialog
{
    Q_OBJECT

public:
    explicit MidiMapping(QWidget *parent = 0);
    ~MidiMapping();

    void loadEffectBlocks();
    void loadParameters( int effectBlockNum );
    void init( );
    void initialization();
    void setPsbAddState(void);

private slots:
    void on_cboEffectBlock_currentIndexChanged(int index);
    void on_psbAdd_clicked();
    void on_psbDel_clicked();
    void on_buttonBox_accepted();
    void on_tableMidiMapping_doubleClicked(const QModelIndex &index);
    void on_cboParameter_currentIndexChanged(int index);

    void on_psbUP_clicked();

    void on_psbDOWN_clicked();

    void on_MidiMapping_accepted();

private:
    Ui::MidiMapping ui;

    MidyAX* m_pMidyAXDlgInstance;

    int m_sizeIndexToParam;
    struct mappingTable m_indexToParam[ 300 ];

    void createRow( int index);
};

#endif // MIDIMAPPING_H
