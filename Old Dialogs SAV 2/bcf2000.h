#ifndef BCF2000_H
#define BCF2000_H

#include <QDialog>
#include <QMainWindow>
#include <QElapsedTimer>
#include <QComboBox>
#include <QLabel>
#include <QAction>
#include <QSettings>
#include <QMessageBox>
#include <QVector>
#include <QList>
#include <QElapsedTimer>

#include "ui_bcf2000.h"
#include "qlineeditmod1.h"
#include "qslidermod1.h"
#include "types.h"
#include "parammapping.h"

#define NUMofSLIDDERS 8

namespace Ui {
class BCF2000;
}

class MidyAX;

class BCF2000 : public QDialog
{
    Q_OBJECT

public:
    struct mappingTable m_BCF2000MappingTable[NUMofSLIDDERS];

    explicit BCF2000(QWidget *parent = 0);
    ~BCF2000();

    void init( void);
    void setSliderValue( int slideIndex, double value);
    void setValueIfMapped( unsigned char effectBlockID, unsigned char effectParameterID, double paramDispValue);
    void storeGeom(void);

private slots:
    void onSliderValueChanged( int value );
    void onLineEditEditingFinished( void );
    void updateBCF2000Mapping( int qcomboIndex );
    void onVerticalSliderCustomContextMenuRequested( const QPoint &pos );
    void midiLearnIt(void);
    void setParameterMapping(void);
    void updateWithLearnedMapping( unsigned char learnedChannel, int learnedCC );
    void accept();
    void reject();

protected:
    void closeEvent(QCloseEvent * event);

private:
    Ui::BCF2000 *ui;
    MidyAX* m_pInstance;

    QAction *midiLearn;
    QAction *setParamMapping;

    QList<QComboBox*> m_TheComboBoxs;
    QList<QLineEditMod1*> m_TheLineEdits;
    QList<QSliderMod1*> m_TheSliders;
    QList<QLabel*> m_TheBlockLabels;
    QList<QLabel*> m_TheParamLabels;
    QList<QLabel*> m_TheMinLabels;
    QList<QLabel*> m_TheMaxLabels;

    int m_currentSliderForContextMenu;
    bool m_setup;
    QElapsedTimer m_timeLastValueChanged;
    bool m_initMode;
    QElapsedTimer m_initMode_timer;
    bool m_firstDisplay;

    ParamMapping *m_dlgParamMapping;

    QPalette m_slidderPalette;
    void colorSlider( int sliderIndex );
    void fillComboBox( void );
};

#endif // BCF2000_H
