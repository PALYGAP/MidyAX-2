#ifndef MIDICONTROLLERGENERICDIALOG_H
#define MIDICONTROLLERGENERICDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QList>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QCloseEvent>

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

#include "midyax.h"
#include "qlineeditmod1.h"
#include "qslidermod1.h"
#include "MidyAX_types.h"
#include "axefx.h"
#include "parammapping.h"
#include "constants.h"

extern void delay( int millisecondsToWait );

class MIDIControllerGenericDialog : public QDialog
{
    Q_OBJECT

    friend class ParamMapping;
    friend class MidyAX;

public:
    MidyAX* m_pMidyAXDlgInstance;
    int m_numberOfKnobs, m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons;
    QList<QComboBox *> m_TheComboBoxs;
    QList<QLineEditMod1 *> m_TheLineEdits;
    QList<QLabel *> m_TheBlockLabels;
    QList<QLabel *> m_TheParamLabels;
    QList<QSliderMod1*> m_TheSliders;
    QList<QLabel *> m_TheMinLabels;
    QList<QLabel *> m_TheMaxLabels;
    QList<QPushButton *> m_TheParameterPushButtons;
    QList<QPushButton *> m_ThePageSelectPushButtons;
    QButtonGroup* m_PageSelectPBGroup;

    struct mappingTable *m_TheMIDIMappingTable;
    struct mappingTable *m_ThePagesMIDIMappingTable;
    QElapsedTimer m_timeLastValueChanged;
    int m_currentSliderForContextMenu;
    bool m_setup;
    bool m_initMode;
    QElapsedTimer m_initMode_timer;
    bool m_firstDisplay;

    void setValueIfMapped( unsigned char effectBlockID, unsigned char effectParameterID, double paramDispValue );
    void storeGeom(void);
    void setMappedMIDIDevice(int MIDIDevice);

    void processCC( int chanNumb, int CCID, int MIDIValue );
    void processPageChangeRequest( int CCID, int MIDIValue);

    QString QSettings_visible;

    int m_currentPage;

public slots:
    void onSliderValueChanged( int value );
    void onLineEditEditingFinished( void );
    void updateMIDIMapping( int qcomboIndex );
    void onVerticalSliderCustomContextMenuRequested( const QPoint &pos );
    void midiLearnIt(void);
    void setParameterMapping(void);
    void updateWithLearnedMapping( unsigned char learnedChannel, int learnedCC );
    void onPushButtonClicked(void);
    void onButtonGroupButtonPushed(int id, bool checked);
    void showEvent(QShowEvent * event);

private slots:
    void accept();
    void reject();

protected: //DATA
    QString QSettings_win_geom_group_name;
    QString QSettings_win_geom;
    QString QSettings_group;
    QPalette m_slidderPalette;

protected: //FUNCTION
    void closeEvent(QCloseEvent * event);

protected: //FUNCTIONS
    explicit MIDIControllerGenericDialog(QWidget *parent, QString MIDIControllerDialogName, int MIDIControllerNumber, int numberOfKnobs,  int numberOfSlidders, int numberOfParameterButtons, int numberOfPageSelectButtons);
    ~MIDIControllerGenericDialog();
    template <class T> void fillWidgetList( QList<T *> *dialogWidgetList, QWidget **gridLayoutWidget, QString *widgetName );
    void constructWidgetLists( QWidget **gridLayoutWidget );
    void init( );
    void fillComboBox(void);
    void connectWidgetOnDialog( void );
    void setSliderValue( int sliderIndex, double value );
    void colorSlider( int sliderIndex );
    void updateKnobsDisplay(void);

private:
    QAction *midiLearn;
    QAction *setParamMapping;
    ParamMapping *m_dlgParamMapping;


    QString m_MIDIControllerDialogName;
    int m_MIDIControllerNumber;

};


template <class T> void MIDIControllerGenericDialog::fillWidgetList( QList<T *> *dialogWidgetList, QWidget **gridLayoutWidget, QString *widgetName )
{
    QString QCBName;
    for(int i=1;; i++ )
    {
        QCBName = *widgetName + QString::number(i);
        if( (*gridLayoutWidget)->findChild<T *>( QCBName ) != NULL )
        {
            dialogWidgetList->append( (*gridLayoutWidget)->findChild<T *>( QCBName ) );
        }
        else {
            break;
        }
    }
}

#endif // MIDICONTROLLERGENERICDIALOG_H
