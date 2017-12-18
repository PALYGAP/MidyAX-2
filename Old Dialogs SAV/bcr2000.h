#ifndef BCR2000_H
#define BCR2000_H

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

#include <QKeyEvent>


#include "ui_bcr2000.h"
#include "qlineeditmod1.h"
#include "qslidermod1.h"
#include "types.h"
#include "parammapping.h"

#define NUMofKNOBS 32

namespace Ui {
class BCR2000;
}

class MidyAX;

class BCR2000 : public QDialog
{
    Q_OBJECT

public:
    struct mappingTable m_BCR2000MappingTable[NUMofKNOBS];

    explicit BCR2000(QWidget *parent = 0);
    ~BCR2000();

    void init( void);
    void setSliderValue( int slideIndex, double value);
    void setValueIfMapped( unsigned char effectBlockID, unsigned char effectParameterID, double paramDispValue);
    void storeGeom(void);

    friend class ParamMapping;

signals:
        void updateBlownUpParamDisplay( int slidderIndex, struct mappingTable *m_BCR2000MappingTable, double paramValue );

private slots:
    void keyPressEvent(QKeyEvent *e);
    void onSliderValueChanged( int value );
    void onLineEditEditingFinished();
    void updateBCR2000Mapping( int qcomboIndex );
    void onVerticalSliderCustomContextMenuRequested( const QPoint &pos );
    void midiLearnIt(void);
    void setParameterMapping( void);
    void updateWithLearnedMapping( unsigned char learnedChannel, int learnedCC );
    void accept();
    void reject();

protected:
    void closeEvent(QCloseEvent * event);

private:
    Ui::BCR2000 *ui;
    MidyAX* m_pInstance;

    QAction *midiLearn;
    QAction *setParamMapping;

    QList<QComboBox*> m_TheComboBoxs;
    QList<QLineEditMod1 *> m_TheLineEdits;
    QList<QLabel*> m_TheBlockLabels;
    QList<QLabel*> m_TheParamLabels;
    QList<QSliderMod1*> m_TheSliders;

    int m_currentSliderForContextMenu;
    bool m_setup;
    QElapsedTimer m_timeLastValueChanged;
    bool m_initMode;
    QElapsedTimer m_initMode_timer;


    ParamMapping *m_dlgParamMapping;

    QPalette m_slidderPalette;
    void colorSlider( int sliderIndex );
    void fillComboBox( void );
};

#endif // BCR2000_H
