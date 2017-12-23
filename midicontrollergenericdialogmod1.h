#ifndef MIDICONTROLLERGENERICDIALOGMOD1_H
#define MIDICONTROLLERGENERICDIALOGMOD1_H

#include <QDialog>
#include <QMainWindow>
#include <QList>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFile>
#include <QStringList>
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

#include <QDebug>
#include <QTimer>


#include "midyax.h"
#include "qlineeditmod1.h"
#include "qslidermod1.h"
#include "MidyAX_types.h"
#include "axefx.h"
#include "parammappingMOD1.h"
#include "CCmapping.h"
#include "constants.h"
#include "blownupparamdisplay.h"

extern void delay( int millisecondsToWait );

class MIDIControllerGenericDialogMOD1 : public QDialog
{
    Q_OBJECT

    friend class ParamMapping;
    friend class MidyAX;

public:
    MidyAX* m_pMidyAXDlgInstance;
    int m_numberOfKnobs, m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons;
    QList<QLineEditMod1 *> m_TheLineEdits;
    QList<QLabel *> m_TheBlockLabels;
    QList<QLabel *> m_TheParamLabels;
    QList<QSliderMod1*> m_TheSliders;
    QList<QLabel *> m_TheMinLabels;
    QList<QLabel *> m_TheMaxLabels;
    QList<QPushButton *> m_TheParameterPushButtons;
    QList<QPushButton *> m_ThePageSelectPushButtons;
    QButtonGroup* m_PageSelectPBGroup;

    // struct mappingTable *m_TheMIDIMappingTable; // In floating CC mode - Contains the local Mapping
    struct pageMappingTable *m_ThePagesMIDIMappingTable; // In fixed CC mode - Contain the mapping specific to one MIDI Controller
    struct CCpageMappingTable *m_TheCCPagesMIDIMappingTable;
    QElapsedTimer m_timeLastValueChanged;
    int m_controlNumberForContextMenu;
    bool m_setup;
    bool m_initMode;
    QElapsedTimer m_initMode_timer;
    bool m_firstDisplay;

    void init( );
    void setValue( quint8 page, quint8 elementNumber, double paramDispValue);
    void setValueIfMapped( int sliderIndex, int MIDIValue );
    void storeGeom(void);
    void setMappedMIDIDevice(int MIDIDevice);

    void processCC( int chanNumb, int CCID, int MIDIValue );
    void processPageChangeRequest( int CCID, int MIDIValue);

    QString QSettings_visible;

    int m_currentPage;

    unsigned char m_fixedParamControlMIDIChannel; // Used to send the parameter control in a fixed mapping set-up. Set MIDI channel 1 by default
    unsigned char m_fixedEffectBlockOBControlMIDIChannel;
    unsigned char m_fixedPageControlMIDIChannel;
    unsigned char m_fixedAXEFXMIDIChannel;

public slots:
    void onSliderValueChanged( int value );
    void onLineEditEditingFinished( void );
    void onCustomContextMenuRequested( const QPoint &pos );
    void setParameterMapping(void);
    void setAXEFXCCMapping(void);
    void clearMapping(void);
    void onPushButtonToggled(bool);
    void onButtonGroupButtonPushed(int id, bool checked);
    void showEvent(QShowEvent * event);

private slots:
    void accept();
    void reject();

    void closeDlgBlownUpParamDisplay( void );
    void setQEditVal(int value);

protected: //DATA
    QString QSettings_win_geom_group_name;
    QString QSettings_win_geom;
    QString QSettings_group;
    QPalette m_slidderPalette;

protected: //FUNCTION
    void closeEvent(QCloseEvent * event);
    void customEvent( QEvent *event );

protected: //FUNCTIONS
    explicit MIDIControllerGenericDialogMOD1(QWidget *parent, QString MIDIControllerDialogName, int MIDIControllerNumber, int numberOfKnobs,  int numberOfSlidders, int numberOfParameterButtons, int numberOfPageSelectButtons);
    ~MIDIControllerGenericDialogMOD1();
    template <class T> void fillWidgetList( QList<T *> *dialogWidgetList, QWidget **gridLayoutWidget, QString *widgetName );
//    template <class T> void fillWidgetList( QList<T *> *dialogWidgetList, QObject *theDialog, QString *widgetName );
    void constructWidgetLists( QWidget **gridLayoutWidget );
//    void constructWidgetLists( QObject *theDialog );
    void connectWidgetOnDialog( void );
    void setSliderValue( int sliderIndex, double value );
    void setSliderValue( int sliderIndex, int MIDIValue );
    void colorSlider( int sliderIndex, int MIDIValue );
    void updateKnobsDisplay(void);

private:
    QAction *setParamMapping;
    QAction *dispParamInfo;
    QAction *setCCMapping;
    QAction *clearMap;
    ParamMappingMOD1 *m_dlgParamMappingMOD1;
    CCMapping *m_dlgCCMapping;

    QString m_MIDIControllerDialogName;
    int m_MIDIControllerNumber;

    QPoint m_CurrentPosition;

    static BlownUpParamDisplay *m_dlgBlownUpParamDisplay;
    QTimer m_timerDlgBlownUpParamDisplay;
    void startDlgBlownUpParamDisplayTimer(void);
};


template <class T> void MIDIControllerGenericDialogMOD1::fillWidgetList( QList<T *> *dialogWidgetList, QWidget **gridLayoutWidget, QString *widgetName )
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


//template <class T> void MIDIControllerGenericDialogMOD1::fillWidgetList( QList<T *> *dialogWidgetList, QObject *theDialog, QString *widgetName )
//{
//    QString QCBName;
//    for(int i=1;; i++ )
//    {
//        QCBName = *widgetName + QString::number(i);
//        if( theDialog->findChild<T *>( QCBName ) != NULL )
//        {
//            dialogWidgetList->append( theDialog->findChild<T *>( QCBName ) );
//        }
//        else {
//            break;
//        }
//    }
//}



#endif // MIDICONTROLLERGENERICDIALOGMOD1_H
