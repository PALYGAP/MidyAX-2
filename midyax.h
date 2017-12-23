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

#ifndef MIDYAX_H
#define MIDYAX_H

#include <QMainWindow>
#include <QElapsedTimer>
#include <QTimer>
#include <QSettings>
#include <QMessageBox>
#include <QEvent>
#include <QDebug>
#include <QSettings>
#include <QCloseEvent>
#include <QElapsedTimer>
#include <QStringList>
#include <math.h>

#include "ui_midyax.h"
#include "RtMidi.h"
#include "midimapping.h"
#include "MidyAX_types.h"
#include "blownupparamdisplay.h"
#include "aboutmidyax.h"
#include "prefs.h"
#include "mididefs.h"
#include "constants.h"
#include "events.h"
#include "midicontrollergenericdialog.h"
#include "midicontrollergenericdialogmod1.h"

class MidiSetup;
class MidiMapping;
class BCF2000;
class BCR2000;
class XTouchMini;
class BeatStep;
class GuitarWing;
class QuNeo;
class FCB1010;
class Prefs;


void delay( int millisecondsToWait );

// GLOBAL functions
void midiCallback_AXEFX( double /*deltatime*/,  std::vector< unsigned char > *message,  void *userData );
void midiCallback_1( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_2( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_3( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_4( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_5( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_6( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_7( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_8( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_9( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_VirtualIN( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
void midiCallback_processing( std::vector< unsigned char > *message,  void *userData,  int device, int mappingMode );

extern quint8 CCtoAXE[16][128][3];

// CONSTANTS
#define START_GET_AXEFX_PARAMETERS_INFO 1
#define CONTINUE_GET_AXEFX_PARAMETERS_INFO 2
#define ERROR_GET_AXEFX_PARAMETERS_INFO 3

namespace Ui {
class MidyAX;
}



class MidyAX : public QMainWindow
{
    Q_OBJECT

    friend class MIDIControllerGenericDialog;
    friend class MIDIControllerGenericDialogMOD1;
    friend class MidiMapping;
    friend class ParamMapping;
    friend class ParamMappingMOD1;
    friend class Prefs;
    friend void midiCallback_AXEFX( double /*deltatime*/,  std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_processing( std::vector< unsigned char > *message, void *userData, int device, int mappingMode );
    friend void midiCallback_1( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_2( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_3( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_4( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_5( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_6( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_7( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_8( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_9( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );
    friend void midiCallback_VirtualIN( double /*deltatime*/,   std::vector< unsigned char > *message,  void *userData );

public:
    bool m_initPhase; //true when doing 1st init

    explicit MidyAX( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
    ~MidyAX();

    int processSYSEXReceivedFromAXEFX( quint8 *data);
    void sendSYSEXtoAXEFX(unsigned char axefxSYSEXmessageID, unsigned char blockID = 255, unsigned char paramID = 255, int CCID = 0, int CCval = 0);
    int getAXEFXParametersInfo( int startContinue );
    void fillCCtoAXE( void );
    void sendCCtoMIDIout( int chanNumb, unsigned char CCID, int paramValue, int device );

signals:
        void learnedMapping( unsigned char learnedChannel, int learnedCC );

protected Q_SLOTS:
    //void slotPreferences();
    void slotPrefs();
    void slotMidiSetup();
    void slotMidiMapping();
    void slotBCR2000();
    void slotBCF2000();
    void slotXTouchMini();
    void slotBeatStep();
    void slotFCB1010();
    void slotGuitarWing();
    void slotQuNeo();
    void slotSYSEXQueryVersion();
    void slotAboutMidyAXMenu();
    void slotActivateResync();
    void slotSYSEXQueryName();
    void slotgetAXEFXParametersInfo();
    void slotWhoAmI();
    void redisplay();
// BLOWNUP relocation
//    void closeDlgBlownUpParamDisplay();

protected:
    void closeEvent ( QCloseEvent *event );
    void customEvent ( QEvent *event );
    void showEvent( QShowEvent* event );

private slots:
    void on_pbSyncWithAXEFX_clicked();
    void on_pbClear_clicked();
    void on_rbnActivateLog_toggled(bool checked);
    void on_actionEXIT_triggered();

private:
    QString m_midiDriver;
    bool m_initialized;
    // The transmission channel is
    // initialized to MIDI channel 1 (value 0)

    //
    Prefs *m_dlgPrefs;
    MidiSetup *m_dlgMidiSetup;
    MidiMapping *m_dlgMidiMapping;
    BCR2000 *m_dlgBCR2000;
    BCF2000 *m_dlgBCF2000;
    XTouchMini *m_dlgXTouchMini;
    BeatStep *m_dlgBeatStep;
    GuitarWing *m_dlgGuitarWing;
    QuNeo *m_dlgQuNeo;
    FCB1010 *m_dlgFCB1010;

// BLOWNUP relocation
//    BlownUpParamDisplay *m_dlgBlownUpParamDisplay;
    AboutMidyAX *m_dlgAboutMidyAX;

    Prefs *dlgPrefs();
    MidiSetup *dlgMidiSetup();
    MidiMapping *dlgMidiMapping();
    BCR2000 *dlgBCR2000();
    BCF2000 *dlgBCF2000();
    XTouchMini *dlgXTouchMini();
    BeatStep *dlgBeatStep();
    GuitarWing *dlgGuitarWing();
    QuNeo *dlgQuNeo();
    FCB1010 *dlgFCB1010();
    AboutMidyAX *dlgAboutMidyAX();

// BLOWNUP relocation
//    QTimer *timerDlgBlownUpParamDisplay;
//    void startDlgBlownUpParamDisplayTimer();

    bool gettingAXEFXParametersInfo;

    void init();
    void refreshConnections();
    bool initMidi();
    void readSettings();
    void applySavedConnectionSettings( void );
    void autoConnect(void);
    void applyConnections( void );
    void readMidiControllerSettings();
    void writeSettings();
    void getMidiMappingParamValues( bool firstTime);
    void updateDisplayedConnectState(void);

    // static methods
    static RtMidiOut *MIDIOutDriverFactory(const QString driver, const QString portName);
    static RtMidiIn *MIDIInDriverFactory(const QString driver, const QString portName);

    //AXE-FX
    int m_numberOfEffectBlocks;

    int m_numbOfMappings;
    struct mappingTable m_theMappingTable[500];
    struct MIDI_CONTROLLER m_theMIDIControllers[MAX_NUMBER_MIDI_CONTROLLERS];
    struct FIXED_CC_MIDI_CONTROLLER m_theFMMIDIControllers[MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS];
    RtMidiIn *m_The_VirtualMIDI_IN;
    RtMidiOut *m_The_VirtualMIDI_OUT;
    //QStringList MIDI_Known_Controllers;

    QElapsedTimer m_MIDIIN_timer;

    Ui::MidyAX ui;

    QSettings settings;

    //Preferenceces
    bool m_logEnabled;
    //bool m_CCoutLogEnabled;
    int m_AXEFXChanNumb;

    QTimer *IHMupdate;

    unsigned char m_sysex_header[5];

    quint8 MIDIContActMap[ MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS -1 ] // -1 due to first element = AXE-FX
                                [ AXEFX_NumberOf_EffectBlocks_DEFINE ]
                                [ AXEFX_MAX_NumberOf_ParamPerBlock_DEFINE ]
                                [2][AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE]; // Used for fast determination of mapped param
};

#endif // MIDYAX_H
