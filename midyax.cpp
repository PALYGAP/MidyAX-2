#include "midyax.h"
#include "ui_midyax.h"

#include "midisetup.h"
#include "bcf2000.h"
#include "bcr2000.h"
#include "XTouchMini.h"
#include "BeatStep.h"
#include "GuitarWing.h"
#include "QuNeo.h"
#include "fcb1010.h"
#include "axefx.h"
#include "axefxparam.h"

extern QStringList AXE_effect_CC_Label;
extern MidyAX* g_pMidyAXDlgInstance;

// Learn Mode
bool g_learnMode;
unsigned char g_learnModeChan;
unsigned char g_learnModeCC;
int g_learnModeCount;
double g_learn_paramDispValue;
unsigned char g_learn_MIDIValue;
int g_learn_callingDialog = 0; // 0 = nothing, 1=BCF2000, 2 = BCR2000;
QWidget *gp_learn_callingDialog;
bool g_sliderColored = true;
bool g_displayBlownUp = true;
bool g_autoConnect = true;
int g_MIDIdataInterval_NumberInterval = 2;
double g_MIDIdataInterval_Interval = 0.1;
bool g_MIDIdataInterval = true;


QStringList MIDI_Known_Controllers;
QStringList MIDI_Known_Controllers_Interface_Name;

MidyAX::MidyAX( QWidget * parent, Qt::WindowFlags flags )
    : QMainWindow(parent, flags),
    m_initPhase(true),
    m_initialized(false),
    m_dlgPrefs(0),
    m_dlgMidiSetup(0),
    m_dlgMidiMapping(0),
    m_dlgBCR2000(0),
    m_dlgXTouchMini(0),
    m_dlgBeatStep(0),
    m_dlgFCB1010(0),
    m_numberOfEffectBlocks(AXEFX_NUMBER_EFFECTS_BLOCK),
    m_logEnabled(false),
    m_AXEFXChanNumb(1)
{
    ui.setupUi(this);

#ifndef QT_DEBUG
    ui.menuTest_SYSEX->menuAction()->setVisible(false);
#endif

    m_sysex_header[0] = 0xF0;
    m_sysex_header[1] = 0x00;
    m_sysex_header[2] = 0x01;
    m_sysex_header[3] = 0x74;
    m_sysex_header[4] = 0x03;


    // Timer is invalid till first started
    m_MIDIIN_timer.invalidate();

    connect(ui.actionPreferences_2, SIGNAL(triggered()), SLOT(slotPrefs()));
    connect(ui.actionMidiSetup, SIGNAL(triggered()), SLOT(slotMidiSetup()));
    connect(ui.actionMidiMapping, SIGNAL(triggered()), SLOT(slotMidiMapping()));
    connect(ui.actionMidyAX_2, SIGNAL(triggered()), SLOT(slotAboutMidyAXMenu()));
    connect(ui.actionBCR2000, SIGNAL(triggered()), SLOT(slotBCR2000()));
    connect(ui.actionBCF2000, SIGNAL(triggered()), SLOT(slotBCF2000()));
    connect(ui.actionX_Touch_Mini, SIGNAL(triggered()), SLOT(slotXTouchMini()));
    connect(ui.actionBeatStep, SIGNAL(triggered()), SLOT(slotBeatStep()));
    connect(ui.actionGuitar_Wing, SIGNAL(triggered()), SLOT(slotGuitarWing()));
    connect(ui.actionQuNeo, SIGNAL(triggered()), SLOT(slotQuNeo()));
    connect(ui.actionFCB1010, SIGNAL(triggered()), SLOT(slotFCB1010()));

    connect(ui.actionSYSEX_QUERY_VERSION, SIGNAL(triggered()), SLOT(slotSYSEXQueryVersion()));
    connect(ui.actionSYSEX_QUERY_NAME, SIGNAL(triggered()), SLOT(slotSYSEXQueryName()));
    connect(ui.actionActivate_Resync, SIGNAL(triggered()), SLOT(slotActivateResync()));

    connect(ui.actionGETAXEFXPARAMETERINFO, SIGNAL(triggered()), SLOT(slotgetAXEFXParametersInfo()));
    connect(ui.actionWHO_AM_I, SIGNAL(triggered()), SLOT(slotWhoAmI()));

    // Initialize the BLOWN-UP DISPLAY dialog
// BLOWNUP relocation
//    m_dlgBlownUpParamDisplay = new BlownUpParamDisplay;
//    timerDlgBlownUpParamDisplay = new QTimer(this);
//    connect( timerDlgBlownUpParamDisplay, SIGNAL(timeout()), this, SLOT(closeDlgBlownUpParamDisplay()) );


//    IHMupdate = new QTimer(this);
//    connect( IHMupdate, SIGNAL(timeout()), this, SLOT( redisplay()) );
//    IHMupdate->setSingleShot(true);
//    if(m_initPhase) IHMupdate->start(5000);

    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        for(int j=0; j < AXEFX_NumberOf_EffectBlocks_DEFINE; j++)
        {
            for(int k=0; k < AXEFX_MAX_NumberOf_ParamPerBlock_DEFINE; k++)
            {
                for(int l=0; l < AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE; l++)
                {
                    MIDIContActMap[ i-1 ][ j ] [ k ][ 0 ][ l ] = 255;
                    MIDIContActMap[ i-1 ][ j ] [ k ][ 1 ][ l ] = 255;
                }
            }
        }
    }

    init();
}

void MidyAX::init()
{
    MIDI_Known_Controllers << "AXE-FX" << "BCR2000" << "BCF2000" << "X-TOUCH" << "BEATSTEP" << "GUITAR WING" << "QUNEO" <<  "FCB1010" << "OTHER1" << "OTHER2" << "" << "";
    MIDI_Known_Controllers_Interface_Name << "AXEFX" << "BCR2000" << "BCF2000" << "XTOUCH" << "BEATSTEP" << "GUITARWING" << "QUNEO" << "FCB1010" << "OTHER1" << "OTHER2" << "" << "";
    //<< "LAUNCHPAD" << "AXIOM 61";


    AXE_effect_CC_Label <<
            "Input Vol"<<
            "Out 1 Vol"<<
            "Out 2 Vol"	<<
            "Bypass"	<<
            "Tempo"	<<
            "Tuner"	<<
            "ExtCont 1"	<<
            "ExtCont 2"	<<
            "ExtCont 3"	<<
            "ExtCont 4"	<<
            "ExtCont 5"	<<
            "ExtCont 6"	<<
            "ExtCont 7"	<<
            "ExtCont 8"	<<
            "ExtCont 9"	<<
            "ExtCont 10"	<<
            "ExtCont 11"	<<
            "ExtCont 12"	<<
            "Looper Record"	<<
            "Looper Play"	<<
            "Looper Once"	<<
            "Looper Dub"	<<
            "Looper Rev"	<<
            "Looper Bypass"	<<
            "Looper Half"	<<
            "Looper Undo"	<<
            "Metronome"	<<
            "Scene Sel"	<<
            "Scene Inc"	<<
            "Scene Dec"	<<
            "Volume Inc"	<<
            "Volume Dec"	<<
            "Amp1 Bypass"	<<
            "Amp2 Bypass"	<<
            "Cab1 Bypass"	<<
            "Cab2 Bypass"	<<
            "Cho1 Bypass"	<<
            "Cho2 Bypass"	<<
            "Comp1 Bypass"	<<
            "Comp2 Bypass"	<<
            "Cross1 Bypass"	<<
            "Cross2 Bypass"	<<
            "Delay1 Bypass"	<<
            "Delay2 Bypass"	<<
            "Drive 1 Bypass"	<<
            "Drive 2 Bypass"	<<
            "Enhancer Bypass"	<<
            "Filter 1 Bypass"	<<
            "Filter 2 Bypass"	<<
            "Filter 3 Bypass"	<<
            "Filter 4 Bypass"	<<
            "Flanger 1 Bypass"	<<
            "Flanger 2 Bypass"	<<
            "Formant 1 Bypass"	<<
            "FX Loop Bypass"	<<
            "Gate/Exp1 Bypass"	<<
            "Gate/Exp2 Bypass"	<<
            "GrapEQ1 Bypass"	<<
            "GrapEQ2 Bypass"	<<
            "GrapEQ3 Bypass"	<<
            "GrapEQ4 Bypass"	<<
            "Megatap Delay Bypass"	<<
            "Multiband Comp 1 Bypass"	<<
            "Multiband Comp 2 Bypass"	<<
            "Multi-Delay 2 Bypass"	<<
            "Multi-Delay 2 Bypass"	<<
            "Parametric EQ 1 Bypass"	<<
            "Parametric EQ 2 Bypass"	<<
            "Parametric EQ 3 Bypass"	<<
            "Parametric EQ 4 Bypass"	<<
            "Phaser 1 Bypass"	<<
            "Phaser 2 Bypass"	<<
            "Pitch Shifter 1 Bypass"	<<
            "Pitch Shifter 2 Bypass"	<<
            "Quad Chorus 1 Bypass"	<<
            "Quad Chorus 2 Bypass"	<<
            "Resonator 1 Bypass"	<<
            "Resonator 2 Bypass"	<<
            "Reverb 1 Bypass"	<<
            "Reverb 2 Bypass"	<<
            "Ring Modulator Bypass"	<<
            "Rotary 1 Bypass"	<<
            "Rotary 2 Bypass"	<<
            "Synth 1 Bypass"	<<
            "Synth 2 Bypass"	<<
            "Tone Matching"	<<
            "Tremolo 1 Bypass"	<<
            "Tremolo 2 Bypass"	<<
            "Vocoder Bypass"	<<
            "Volume/Pan 1 Bypass"	<<
            "Volume/Pan 2 Bypass"	<<
            "Volume/Pan 3 Bypass"	<<
            "Volume/Pan 4 Bypass"	<<
            "Wahwah 1 Bypass"	<<
            "Wahwah 2 Bypass"	<<
            "Amp 1 X/Y"	<<
            "Amp 2 X/Y"	<<
            "Cab 1 X/Y"	<<
            "Cab 2 X/Y"	<<
            "Chorus 1 X/Y"	<<
            "Chorus 2 X/Y"	<<
            "Delay 1 X/Y"	<<
            "Delay 2 X/Y"	<<
            "Drive 1 X/Y"	<<
            "Drive 2 X/Y"	<<
            "Flanger 1 X/Y"	<<
            "Flanger 2 X/Y"	<<
            "Phaser 1 X/Y"	<<
            "Phaser 2 X/Y"	<<
            "Pitch 1 X/Y"	<<
            "Pitch 2 X/Y"	<<
            "Reverb 1 X/Y"	<<
            "Reverb 2 X/Y"	<<
            "Wahwah 1 X/Y"	<<
            "Wahwah 2 X/Y"	<<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            ""    <<
            "";



    for(int i=0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS;i++)
    {
        m_theFMMIDIControllers[i].controllerName = MIDI_Known_Controllers[i] ;
        m_theFMMIDIControllers[i].The_MIDI_IN_Name = QString("MIDYAX_IN_%1").arg(i, 2, 10, QChar('0'));
        m_theFMMIDIControllers[i].The_MIDI_OUT_Name = QString("MIDYAX_OUT_%1").arg(i, 2, 10, QChar('0'));
        m_theFMMIDIControllers[i].controllerConnected = false;
    }

    //Item 0 is for the AXE-FX
    m_theFMMIDIControllers[0].MidiCallbackFunctions = &midiCallback_AXEFX;
    m_theFMMIDIControllers[1].MidiCallbackFunctions = &midiCallback_1;
    m_theFMMIDIControllers[2].MidiCallbackFunctions = &midiCallback_2;
    m_theFMMIDIControllers[3].MidiCallbackFunctions = &midiCallback_3;
    m_theFMMIDIControllers[4].MidiCallbackFunctions = &midiCallback_4;
    m_theFMMIDIControllers[5].MidiCallbackFunctions = &midiCallback_5;
    m_theFMMIDIControllers[6].MidiCallbackFunctions = &midiCallback_6;
    m_theFMMIDIControllers[7].MidiCallbackFunctions = &midiCallback_7;
    m_theFMMIDIControllers[8].MidiCallbackFunctions = &midiCallback_8;
    m_theFMMIDIControllers[9].MidiCallbackFunctions = &midiCallback_9;


    readSettings();

    m_theFMMIDIControllers[0].fixedPageControlMIDIChannel = 255;
    m_theFMMIDIControllers[0].fixedEffectBlockOBControlMIDIChannel = 255;
    m_theFMMIDIControllers[0].fixedAXEFXMIDIChannel =  255;
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++ )
    {
        m_theFMMIDIControllers[i].fixedPageControlMIDIChannel = 16;  /* MIDI channel 16 */
        m_theFMMIDIControllers[i].fixedEffectBlockOBControlMIDIChannel = 15;  /* MIDI channel 15 */
        m_theFMMIDIControllers[i].fixedAXEFXMIDIChannel =  14; /* MIDI channel 14 */
    }


    if ((m_initialized = initMidi())) {
        refreshConnections();
        if(g_autoConnect == true) autoConnect();
        else applySavedConnectionSettings();
        //applyConnections();
        updateDisplayedConnectState();
        activateWindow();
    }
    else {
        exit(0);
    }

    // Connect the MIDI Contollers with their dialog
    m_theFMMIDIControllers[0].dlgObject = NULL; // NO dialog for AXE-FX
    m_theFMMIDIControllers[1].dlgObject = dlgBCR2000();
    m_theFMMIDIControllers[2].dlgObject = dlgBCF2000();
    m_theFMMIDIControllers[3].dlgObject = dlgXTouchMini();
    m_theFMMIDIControllers[4].dlgObject = dlgBeatStep();
    m_theFMMIDIControllers[5].dlgObject = dlgGuitarWing();
    m_theFMMIDIControllers[6].dlgObject = dlgQuNeo();
    m_theFMMIDIControllers[7].dlgObject = dlgFCB1010();
    m_theFMMIDIControllers[8].dlgObject = NULL;
    m_theFMMIDIControllers[9].dlgObject = NULL;
//    m_theFMMIDIControllers[6].dlgObject = dlgOther1();
//    m_theFMMIDIControllers[7].dlgObject = dlgOther2();

    m_initPhase = false;

    //sendSYSEXtoAXEFX( AXEFX_SYSEX_GET_MIDI_CHANNEL );
    sendSYSEXtoAXEFX( AXEFX_SYSEX_QUERY_VERSION );
    getMidiMappingParamValues( true );

    // Needed to make sure the control surfaces receive the initial values for their page 1
    for(int i=0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        if(   m_theFMMIDIControllers[i].dlgObject != NULL
           && m_theFMMIDIControllers[i].controllerConnected == true )
        m_theFMMIDIControllers[i].dlgObject->onButtonGroupButtonPushed( 0, true);
    }

#ifndef __MACOSX_CORE__
    delay(300);
#endif
}



bool MidyAX::initMidi()
{

    try {
        m_midiDriver = ""; //QSTR_DRIVERDEFAULT;  // Set the MIDI DRIVER type to the default for the Operating System

        // Fabricates the MIDI_IN and MIDI_OUT RT MIDI ports
        for(int i=0; i< MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS;i++)
        {
            m_theFMMIDIControllers[i].The_MIDI_IN = MIDIInDriverFactory( m_midiDriver, m_theFMMIDIControllers[i].The_MIDI_IN_Name );
            m_theFMMIDIControllers[i].The_MIDI_OUT = MIDIOutDriverFactory( m_midiDriver, m_theFMMIDIControllers[i].The_MIDI_OUT_Name );
            if( m_theFMMIDIControllers[i].The_MIDI_IN == NULL || m_theFMMIDIControllers[i].The_MIDI_OUT == NULL )
            {
                QMessageBox::critical( this, tr("MIDI Error"), tr("Cannot create one of the RTMIDI ports") );
                return false;
            }
        }

        // Get number of OUT and IN RTMIDI ports
        int nOutPorts = m_theFMMIDIControllers[0].The_MIDI_OUT->getPortCount();
        if (nOutPorts == 0) {
            // If no MIDI OUT port no initialization of ports
            QMessageBox::critical( this, tr("MIDI Error"),
                tr("No MIDI output port is available. Connect MIDI device(s) and restart the program") );
            return false;
        }
        int nInPorts = m_theFMMIDIControllers[0].The_MIDI_IN->getPortCount();
        if (nInPorts == 0) {
            QMessageBox::critical( this, tr("MIDI Error"),
                tr("No MIDI input port is available. Connect MIDI device(s) and restart the program") );
            return false;
        }


        //AXE-FX set-up
        m_theFMMIDIControllers[0].The_MIDI_IN->ignoreTypes(false,true,true);
        m_theFMMIDIControllers[0].The_MIDI_IN->setCallback( m_theFMMIDIControllers[0].MidiCallbackFunctions, this );

        // MIDI CONTROLLERs setup (Other than AXE-FX)
        for(int i=1; i< MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS;i++)
        {
            m_theFMMIDIControllers[i].The_MIDI_IN->ignoreTypes(true,true,true);
            m_theFMMIDIControllers[i].The_MIDI_IN->setCallback( m_theFMMIDIControllers[i].MidiCallbackFunctions, this );
        }


#if defined(__LINUX_ALSASEQ__)
    m_midiDriver = QSTR_DRIVERNAMEALSA;
#endif
#if defined(__MACOSX_CORE__)
    m_midiDriver = QSTR_DRIVERNAMEMACOSX;
#endif
#if defined(__IRIX_MD__)
    m_midiDriver = QSTR_DRIVERNAMEIRIX;
#endif
#if defined(__WINDOWS_MM__)
    m_midiDriver = QSTR_DRIVERNAMEWINMM;
#endif
#if defined(NETWORK_MIDI)
    m_midiDriver = QSTR_DRIVERNAMENET;
#endif
        //Add a virtual port
        if (m_midiDriver == QSTR_DRIVERNAMEALSA || m_midiDriver == QSTR_DRIVERNAMEMACOSX || m_midiDriver == QSTR_DRIVERNAMEJACK)
        {
            m_The_VirtualMIDI_IN = MIDIInDriverFactory( m_midiDriver, QSTR_MIDYAX_VIRTUAL_INPUT);
            m_The_VirtualMIDI_OUT = MIDIOutDriverFactory( m_midiDriver, QSTR_MIDYAX_VIRTUAL_OUTPUT );
            if( m_The_VirtualMIDI_IN != 0 )
            {
                m_The_VirtualMIDI_IN->openVirtualPort(QSTR_MIDYAX_VIRTUAL_INPUT.toStdString());
                m_The_VirtualMIDI_IN->ignoreTypes(true,true,true);
                m_The_VirtualMIDI_IN->setCallback( &midiCallback_VirtualIN, this );
                //m_inputActive = true;
            }
            if( m_The_VirtualMIDI_OUT != 0 ) m_The_VirtualMIDI_OUT->openVirtualPort(QSTR_MIDYAX_VIRTUAL_OUTPUT.toStdString());

        }


    } catch (RtMidiError& err) {
        QMessageBox::critical( this, tr("Error. Aborting"),
                               QString::fromStdString(err.getMessage()));
        return false;
    }
    return true;
}




void MidyAX::showEvent( QShowEvent* event )
{
    // Update the Visible Dialog on display (show) of the main MidyAX window
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        if( m_theFMMIDIControllers[i].dlgObject != NULL && settings.value( m_theFMMIDIControllers[i].dlgObject->QSettings_visible ).toBool() )
        {
            m_theFMMIDIControllers[i].dlgObject->init();
            m_theFMMIDIControllers[i].dlgObject->update();
            m_theFMMIDIControllers[i].dlgObject->setModal(false);
            m_theFMMIDIControllers[i].dlgObject->show();
        }
    }
    QMainWindow::showEvent( event );
}


void MidyAX::redisplay( void )
{
    // Update the Visible Dialog on display (show) of the main MidyAX window
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        if( m_theFMMIDIControllers[i].dlgObject != NULL && m_theFMMIDIControllers[i].dlgObject->isVisible() )
        {
            m_theFMMIDIControllers[i].dlgObject->init();
            m_theFMMIDIControllers[i].dlgObject->update();
            m_theFMMIDIControllers[i].dlgObject->setModal(false);
            m_theFMMIDIControllers[i].dlgObject->show();
        }
    }
}



MidyAX::~MidyAX()
{
    //delete ui;
    sendSYSEXtoAXEFX( AXEFX_SYSEX_ACT_RESYNC ); // This actually stops the RESYNC messages
}

// BLOWNUP relocation
//void MidyAX::closeDlgBlownUpParamDisplay()
//{
//    m_dlgBlownUpParamDisplay->hide();

//}

//void MidyAX::startDlgBlownUpParamDisplayTimer()
//{
//    timerDlgBlownUpParamDisplay->setSingleShot(true);
//    timerDlgBlownUpParamDisplay->start(1500);
//}



RtMidiOut * MidyAX::MIDIOutDriverFactory(const QString driverName, const QString clientName)
{
    RtMidiOut *driver = 0;
#if defined(__LINUX_ALSA__)
    if (driverName == QSTR_DRIVERNAMEALSA)
        driver = new RtMidiOut(RtMidi::LINUX_ALSA, clientName.toStdString());
#endif
#if defined(__LINUX_JACK__)
    if (driverName == QSTR_DRIVERNAMEJACK)
        driver = new RtMidiOut(RtMidi::UNIX_JACK, clientName.toStdString());
#endif
#if defined(__IRIX_MD__)
    if (driverName == QSTR_DRIVERNAMEIRIX)
        driver = new RtMidiOutIrix(clientName.toStdString());
#endif
#if defined(__MACOSX_CORE__)
    if (driverName == QSTR_DRIVERNAMEMACOSX)
        driver = new RtMidiOut(RtMidi::MACOSX_CORE, clientName.toStdString());
#endif
#if defined(__WINDOWS_MM__)
    if (driverName == QSTR_DRIVERNAMEWINMM)
        driver = new RtMidiOut(RtMidi::WINDOWS_MM, clientName.toStdString());
#endif
#if defined(NETWORK_MIDI)
    if (driverName == QSTR_DRIVERNAMENET)
        driver = new NetMidiOut(clientName.toStdString());
#endif
    if (driver == 0 && driverName != QSTR_DRIVERDEFAULT)
        driver = MIDIOutDriverFactory(QSTR_DRIVERDEFAULT, clientName);
    return driver;
}

RtMidiIn *  MidyAX::MIDIInDriverFactory(const QString driverName, const QString clientName)
{
    RtMidiIn *driver = 0;
#if defined(__LINUX_ALSA__)
    if (driverName == QSTR_DRIVERNAMEALSA)
        driver = new RtMidiIn(RtMidi::LINUX_ALSA, clientName.toStdString());
#endif
#if defined(__LINUX_JACK__)
    if (driverName == QSTR_DRIVERNAMEJACK)
        driver = new RtMidiIn(RtMidi::UNIX_JACK, clientName.toStdString());
#endif
#if defined(__IRIX_MD__)
    if (driverName == QSTR_DRIVERNAMEIRIX)
        driver = new RtMidiInIrix(clientName.toStdString());
#endif
#if defined(__MACOSX_CORE__)
    if (driverName == QSTR_DRIVERNAMEMACOSX)
        driver = new RtMidiIn(RtMidi::MACOSX_CORE, clientName.toStdString());
#endif
#if defined(__WINDOWS_MM__)
    if (driverName == QSTR_DRIVERNAMEWINMM)
        driver = new RtMidiIn(RtMidi::WINDOWS_MM, clientName.toStdString());
#endif
#if defined(NETWORK_MIDI)
    if (driverName == QSTR_DRIVERNAMENET)
        driver = new NetMidiIn(clientName.toStdString());
#endif
    if (driver == 0 && driverName != QSTR_DRIVERDEFAULT)
        driver = MIDIInDriverFactory(QSTR_DRIVERDEFAULT, clientName);
    return driver;
}

MidiSetup* MidyAX::dlgMidiSetup()
{
    if (m_dlgMidiSetup == 0) {
        m_dlgMidiSetup = new MidiSetup(this);
    }
    return m_dlgMidiSetup;
}

Prefs* MidyAX::dlgPrefs()
{
    if (m_dlgPrefs == 0) {
        m_dlgPrefs = new Prefs(this);
    }
    return m_dlgPrefs;
}

MidiMapping* MidyAX::dlgMidiMapping()
{
    if (m_dlgMidiMapping == 0) {
        m_dlgMidiMapping = new MidiMapping(this);
    }
    return m_dlgMidiMapping;
}

BCR2000* MidyAX::dlgBCR2000()
{
    if (m_dlgBCR2000 == 0) {
        m_dlgBCR2000 = new BCR2000(this);
        //getMidiMappingParamValues();
    }
    return m_dlgBCR2000;
}

BCF2000* MidyAX::dlgBCF2000()
{
    if (m_dlgBCF2000 == 0) {
        m_dlgBCF2000 = new BCF2000(this);
    }
    return m_dlgBCF2000;
}

XTouchMini* MidyAX::dlgXTouchMini()
{
    if (m_dlgXTouchMini == 0) {
        m_dlgXTouchMini = new XTouchMini(this);
    }
    return m_dlgXTouchMini;
}

BeatStep* MidyAX::dlgBeatStep()
{
    if (m_dlgBeatStep == 0) {
        m_dlgBeatStep = new BeatStep(this);
    }
    return m_dlgBeatStep;
}

FCB1010* MidyAX::dlgFCB1010()
{
    if (m_dlgFCB1010 == 0) {
        m_dlgFCB1010 = new FCB1010(this);
    }
    return m_dlgFCB1010;
}

GuitarWing* MidyAX::dlgGuitarWing()
{
    if (m_dlgGuitarWing == 0) {
        m_dlgGuitarWing = new GuitarWing(this);
    }
    return m_dlgGuitarWing;
}

QuNeo* MidyAX::dlgQuNeo()
{
    if (m_dlgQuNeo== 0) {
        m_dlgQuNeo = new QuNeo(this);
    }
    return m_dlgQuNeo;
}


AboutMidyAX* MidyAX::dlgAboutMidyAX()
{
    if (m_dlgAboutMidyAX == 0) {
        m_dlgAboutMidyAX = new AboutMidyAX(this);
    }
    return m_dlgAboutMidyAX;
}




///////////////////////////////////////////////////////////////////////////////////////
////////////////////// MIDI CALLBACK FUNCTION for AXEFX MIDI IN ///////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void midiCallback_AXEFX( double /*deltatime*/,
                   std::vector< unsigned char > *message,
                   void *userData )
{
    QEvent* ev = 0;
    MidyAX* m_pMidyAXDlgInstance = static_cast<MidyAX*>(userData);

    if( m_pMidyAXDlgInstance->m_initPhase == true ) return;

    unsigned char status = message->at(0) & MASK_STATUS;

    // EFE 2016-01-03 - Only CC and SYSEX are accepted . CC can be on any MIDI Channel of the port (1 to 16)
    switch( status ) {
        case STATUS_SYSEX: {
                // Process SYSEX (Received from AXE-FX)
                if( m_pMidyAXDlgInstance->processSYSEXReceivedFromAXEFX( message->data() ) < 0 ) {return;}
                //                int AXE_SYSEXerror = m_pMidyAXDlgInstance->processSYSEXReceivedFromAXEFX( message->data(), int(message->size()) );
                //                if( AXE_SYSEXerror < 0 ) {return;}

                // Sending SYSEX event to MidyAX UI
                if( m_pMidyAXDlgInstance->m_logEnabled == true)
                {
                    std::vector<unsigned char> SEvector (*message);
                    ev = new SysExEvent( 0 /*AXE-FX*/, SEvector);
                    QApplication::postEvent(m_pMidyAXDlgInstance, ev);
                }
            } break;
        case STATUS_CTLCHG: {
                // Process CC (Received from AXE-FX)
                unsigned char channel = message->at(0) & MASK_CHANNEL;
                unsigned char ctl = message->at(1);
                unsigned char val = message->at(2);
                // Sending CC event to MidyAX UI
                if( g_pMidyAXDlgInstance->m_logEnabled == true)
                {
                    ev = new ControlChangeEvent( 0 /*AXE-FX*/, channel, ctl, val, IN);
                    QApplication::postEvent(m_pMidyAXDlgInstance, ev);
                }
                //TODO : process the incoming CC from AXE-FX --> MFC101, Footpedal
            } break;
        //        case STATUS_PROGRAM: {
        //                unsigned char value = message->at(1);
        //                ev = new ProgramChangeEvent(value);
        //            }
        //        } break;

    }
}

// MIDI callBack for BCR2000
void midiCallback_1 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{   midiCallback_processing( message, userData, 1, FIXED_CC_MAPPING);}

// MIDI callBack for BCF2000
void midiCallback_2 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{   midiCallback_processing( message, userData, 2, FIXED_CC_MAPPING);}

// MIDI callBack for X-TOUCH
void midiCallback_3 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{   midiCallback_processing( message, userData, 3, FIXED_CC_MAPPING);}

// MIDI callBack for BEATSTEP
void midiCallback_4 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{   midiCallback_processing( message, userData, 4, FIXED_CC_MAPPING);}

// MIDI callBack for GUITAR WING
void midiCallback_5 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{    midiCallback_processing( message, userData, 5, FIXED_CC_MAPPING);}

// MIDI callBack for QUNEO
void midiCallback_6 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{    midiCallback_processing( message, userData, 6, FIXED_CC_MAPPING);}

// MIDI callBack for FCB1010
void midiCallback_7 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{    midiCallback_processing( message, userData, 7, FIXED_CC_MAPPING);}

// MIDI callBack for OTHER1
void midiCallback_8 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{    midiCallback_processing( message, userData, 8, FIXED_CC_MAPPING);}

// MIDI callBack for OTHER2
void midiCallback_9 ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{    midiCallback_processing( message, userData, 9, FIXED_CC_MAPPING);}

// MIDI callBack for Virtual MIDI IN port
void midiCallback_VirtualIN ( double /*deltatime*/, std::vector< unsigned char > *message, void *userData )
{
    // SEND durect to AXE-FX --> Later offer possibility of mapping.
    //TODO finish treatment.
    midiCallback_processing( message, userData, 10, FIXED_CC_MAPPING);}


void midiCallback_processing(std::vector< unsigned char > *message,  void *userData, int MIDIController_Number, int mappingMode )
{
    static int last_MIDIController_Number;
    QEvent *ev1 = 0, *ev2 = 0;
    //MidyAX* m_pMidyAXDlgInstance = static_cast<MidyAX*>(userData); --> Use g_pMidyAXDlgInstance avoid cast

    // NO CCs reception from the MIDI controllers during the init phase
    // Avoid crash due to dialog elements not initialized
    if(      g_pMidyAXDlgInstance->m_initPhase == true
         ||     (    g_MIDIdataInterval == true
                  && g_pMidyAXDlgInstance->m_MIDIIN_timer.elapsed() < g_MIDIdataInterval_Interval
                  && last_MIDIController_Number == MIDIController_Number) ) return;

    last_MIDIController_Number = MIDIController_Number;

    unsigned char channel = message->at(0) & MASK_CHANNEL;
    unsigned char status = message->at(0) & MASK_STATUS;    

    // Not used for now global mapping is inactive TODO: re-activate
//    // FOR GLOBAL MAPPING - Re-Route CC MIDI messages on the AXE-FX channel
//    // A controller can still pilot the CC exposed by the AXE-FX (no CC to SYSEX convertion needed)
//    if ( channel+1 == g_pMidyAXDlgInstance->m_AXEFXChanNumb && status == STATUS_CTLCHG && mappingMode == GLOBAL_MAPPING )
//    {
//        int receivedCtlCC = message->at(1);
//        int receivedCCVal = message->at(2);

//        try {
//            g_pMidyAXDlgInstance->m_theFMMIDIControllers[0].The_MIDI_OUT->sendMessage( message );
//        } catch (RtMidiError& err) {
//            qWarning() << QString::fromStdString(err.getMessage());
//        }
//        if( g_pMidyAXDlgInstance->m_logEnabled == true)
//        {
//            ev2 = new ControlChangeEvent( 0, g_pMidyAXDlgInstance->m_AXEFXChanNumb ,
//                                         receivedCtlCC, receivedCCVal, OUT );
//            QApplication::postEvent(g_pMidyAXDlgInstance, ev2);
//        }
//        return;
//    }


    // EFE 2016-01-03 - CC can be on any MIDI Channel of the port (1 to 16) #######apart from the AXE-FX MIDI channel (processed in the step abobe)
    // For now it is not g_pMidyAXDlgInstance specifc to one RTMidiIn CLASS
        //    if( status == STATUS_CTLCHG || status == STATUS_SYSEX ) //TODO : TEMPO. Remove when Programme Change will be processed
        //    {
    switch( status ) {
    case STATUS_CTLCHG: {
            // Process CCs coming from the MIDI controllers
            int receivedCtlCC = message->at(1);
            int receivedCCVal = message->at(2);
            int blockID, paramID, curDlgPage, posi;

            MIDIControllerGenericDialogMOD1 *curDlg = g_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIController_Number].dlgObject;

            posi = receivedCtlCC-1 + ( ( curDlg->m_numberOfSlidders
                                      + curDlg->m_numberOfKnobs
                                      + curDlg->m_numberOfParameterButtons)
                                      * curDlg->m_PageSelectPBGroup->checkedId()  );

            // MIDI controller specific processing
            switch( MIDIController_Number)
            {
                case BEATSTEP_MC:
                    // Special processing for BeatStep
                    if( channel+1 == curDlg->m_fixedParamControlMIDIChannel )
                    {
                        if( curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID  != 255 )
                        {
                            // TODO: Add a speed up fonction if decrease/increase CC are received very fast
                            if( receivedCCVal == 63 ) receivedCCVal = curDlg->m_ThePagesMIDIMappingTable[posi].MIDIValue - 2;
                            else if ( receivedCCVal == 65 ) receivedCCVal = curDlg->m_ThePagesMIDIMappingTable[posi].MIDIValue + 3;
                            else break;
                        }
                        else if( curDlg->m_TheCCPagesMIDIMappingTable[posi].number  != 255 )
                        {
                            // TODO: Add a speed up fonction if decrease/increase CC are received very fast
                            if( receivedCCVal == 63 ) receivedCCVal = curDlg->m_TheCCPagesMIDIMappingTable[posi].MIDIValue - 2;
                            else if ( receivedCCVal == 65 ) receivedCCVal = curDlg->m_TheCCPagesMIDIMappingTable[posi].MIDIValue + 3;
                            else break;
                        }
                    }
                    break;
                case FCB1010_MC:
                    // Special processing for FCB1010
                    if( channel+1 == curDlg->m_fixedParamControlMIDIChannel && receivedCtlCC > 2 ) // CC 1 and 2 are the pedals
                    {
                        if( curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID  != 255 )
                        {
                            if( curDlg->m_ThePagesMIDIMappingTable[posi].MIDIValue ==  127 )
                            {
                                curDlg->m_ThePagesMIDIMappingTable[posi].MIDIValue =  0;
                                receivedCCVal = 0;
                            }
                            else {
                                curDlg->m_ThePagesMIDIMappingTable[posi].MIDIValue =  127;
                                receivedCCVal = 127;
                            }
                        }
                        else if( curDlg->m_TheCCPagesMIDIMappingTable[posi].number  != 255 )
                        {
                            if( curDlg->m_TheCCPagesMIDIMappingTable[posi].MIDIValue == 127 )
                            {
                                curDlg->m_TheCCPagesMIDIMappingTable[posi].MIDIValue = 0 ;
                                receivedCCVal = 0;
                            }
                            else {
                                curDlg->m_TheCCPagesMIDIMappingTable[posi].MIDIValue = 127;
                                receivedCCVal = 127;
                            }
                        }

                    }
                    break;
                case GUITARWING_MC:
                    // Special processing for GUITAR WING
                    if( channel+1 == curDlg->m_fixedPageControlMIDIChannel  )
                    {
                        // Reprocess page change toggle buttons into just ON buttons.
                        if( receivedCtlCC <= curDlg->m_numberOfPageSelectButtons && receivedCCVal == 0 ) receivedCCVal = 127;
                    }
                    break;
            }

            if( mappingMode == FIXED_CC_MAPPING )
            {
                if( channel+1 == g_pMidyAXDlgInstance->m_theFMMIDIControllers[ MIDIController_Number ].fixedCCMIDIChannel /* MIDI channel of bcr2000 */ && status == STATUS_CTLCHG )
                {
                    //Case : mapping to AXE-FX param exists
                    if( curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID  != 255 )
                    {
                        blockID = curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID;
                        paramID = curDlg->m_ThePagesMIDIMappingTable[posi].effectParameterID;

                        // SENDS Received CC value to AXE-FX to control the mapped AXE-FX parameter
                        g_pMidyAXDlgInstance->sendSYSEXtoAXEFX(
                                    AXEFX_SYSEX_PARAM_SET_S,
                                    curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID,
                                    curDlg->m_ThePagesMIDIMappingTable[posi].effectParameterID,
                                    curDlg->m_ThePagesMIDIMappingTable[posi].effectParameterType,
                                    receivedCCVal);

                        // Look if mapped param is mapped to other connected MIDI controller and sends CC value update
                        for(int h=1; h < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS && h!=MIDIController_Number; h++)
                        {
                            if( g_pMidyAXDlgInstance->m_theFMMIDIControllers[h].controllerConnected != true ) continue;

                            blockID = blockID - 100;
                            if( g_pMidyAXDlgInstance->MIDIContActMap[ h-1 ][ blockID ][ paramID ][ 0 ][ 0 ] != 255 )
                            {
                                MIDIControllerGenericDialogMOD1 *tarDlg = (MIDIControllerGenericDialogMOD1 *) g_pMidyAXDlgInstance->m_theFMMIDIControllers[h].dlgObject;
                                for(int a=0; a < AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE; a++)
                                {
                                    curDlgPage = g_pMidyAXDlgInstance->MIDIContActMap[h-1][blockID][paramID][0][a];
                                    if( curDlgPage == 255) break; //Stops as soon as one element has "empty" value
                                    if( curDlgPage != tarDlg->m_currentPage ) continue;

                                    g_pMidyAXDlgInstance->sendCCtoMIDIout( tarDlg->m_fixedParamControlMIDIChannel,
                                                                           g_pMidyAXDlgInstance->MIDIContActMap[h-1][blockID][paramID][1][a] + 1,
                                                                           receivedCCVal,
                                                                           h );
                                    //NOTE: Update the dialog of the MIDI controller is done on receiption of the SYSEX answer

                                    if( g_pMidyAXDlgInstance->m_logEnabled == true)
                                    {
                                        ev2 = new ControlChangeEvent( h,
                                                                     tarDlg->m_fixedParamControlMIDIChannel - 1,
                                                                     g_pMidyAXDlgInstance->MIDIContActMap[h-1][blockID][paramID][1][a] + 1,
                                                                     receivedCCVal,
                                                                     OUT );
                                        QApplication::postEvent(g_pMidyAXDlgInstance, ev2);
                                    }
                                }
                            }
                        }
                    }

                    //Case : mapping to AXE-FX CC exists
                    else if( curDlg->m_TheCCPagesMIDIMappingTable[posi].number  != 255)
                    {
                        // Send converted CC message to AXE-FX
                        g_pMidyAXDlgInstance->sendCCtoMIDIout(
                                                    g_pMidyAXDlgInstance->m_AXEFXChanNumb,
                                                    curDlg->m_TheCCPagesMIDIMappingTable[posi].AXE_CC,
                                                    receivedCCVal,
                                                    0 /* AXE-FX */);
                        // Store new AXE-FX CC MIDI value
                        curDlg->m_TheCCPagesMIDIMappingTable[posi].MIDIValue = receivedCCVal;

                        // Update slidder display
                        // Sends the value to the MIDI Controller's dialogs if NOT in INI phase
                        if( g_pMidyAXDlgInstance->m_initPhase == false )
                        {
                            for(int j=1; j < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; j++)
                            {
                                if( g_pMidyAXDlgInstance->m_theFMMIDIControllers[j].controllerConnected == true)  //&& m_theFMMIDIControllers[j].dlgObject->isVisible() == true
                                {
                                    MIDIControllerGenericDialogMOD1 *tempo = (MIDIControllerGenericDialogMOD1 *) g_pMidyAXDlgInstance->m_theFMMIDIControllers[j].dlgObject;
                                    tempo->setValueIfMapped( curDlg->m_TheCCPagesMIDIMappingTable[posi].number, receivedCCVal);
                                }
                            }
                        }

                        //TODO: Checks if the AXE-FX CC changed is mapped on other MIDI controllers and sends CC

                        // LOG AXE-FX CC event
                        if( g_pMidyAXDlgInstance->m_logEnabled == true)
                        {
                            ev2 = new ControlChangeEvent( 0,
                                                         g_pMidyAXDlgInstance->m_AXEFXChanNumb,
                                                         curDlg->m_TheCCPagesMIDIMappingTable[posi].AXE_CC,
                                                         receivedCCVal,
                                                         OUT );
                            QApplication::postEvent(g_pMidyAXDlgInstance, ev2);
                        }
                    }
                }
                else if( channel+1 ==  g_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIController_Number].fixedAXEFXMIDIChannel )
                {
                    try {
                        g_pMidyAXDlgInstance->m_theFMMIDIControllers[0].The_MIDI_OUT->sendMessage( message );
                    } catch (RtMidiError& err) {
                        qWarning() << QString::fromStdString(err.getMessage());
                    }
                    if( g_pMidyAXDlgInstance->m_logEnabled == true)
                    {
                        ev2 = new ControlChangeEvent( 0, g_pMidyAXDlgInstance->m_AXEFXChanNumb ,
                                                 receivedCtlCC, receivedCCVal, OUT );
                        QApplication::postEvent(g_pMidyAXDlgInstance, ev2);
                    }
                    return;
                }
                // Process page change and effectBlock On/Bypass requests
                else if(    channel+1 == g_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIController_Number].fixedPageControlMIDIChannel )
                {
                    //g_pMidyAXDlgInstance->m_theFMMIDIControllers[ MIDIController_Number ].dlgObject->processCC( channel, receivedCtlCC, receivedCCVal );
                    ev1 = new MIDIContDialPageChangeEvent( MIDIController_Number, receivedCtlCC, receivedCCVal );
                    if (ev1 != 0) QApplication::postEvent( g_pMidyAXDlgInstance, ev1 );
                }
                else if(    channel+1 == g_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIController_Number].fixedEffectBlockOBControlMIDIChannel)
                {

                }

                // Put the dialog of the sending MIDI controller on top of the display (even if the CC message is not accepted/processed)
                if( g_displayBlownUp == false )
                {
                    curDlg->raise();
                    curDlg->init();
                    curDlg->update();
                }

            } //End of case FIXED CC MAPPING



            else { //Case GLOBAL MAPPING
                // TODO : put it in a special callback function
                // If in LEARN MODE --> special process and CC not sent to AXE-FX
                if( g_learnMode == true )
                {
                    if(    g_learnModeChan == channel
                        && g_learnModeCC == receivedCtlCC )
                    {
                        g_learnModeCount ++;

                        // TODO : Does not work properly --> to be fixed
                        if (g_learnModeCount > 5) return;
                        if( g_learnModeCount == 5)
                        {
                            if(  ( g_pMidyAXDlgInstance->m_dlgBCF2000 && g_learn_callingDialog == 1 ) ||
                                 ( g_pMidyAXDlgInstance->m_dlgBCR2000 && g_learn_callingDialog == 2 ) ||
                                 ( g_pMidyAXDlgInstance->m_dlgXTouchMini && gp_learn_callingDialog == (QWidget *) g_pMidyAXDlgInstance->dlgXTouchMini() ) ||
                                 ( g_pMidyAXDlgInstance->m_dlgBeatStep && gp_learn_callingDialog == (QWidget *) g_pMidyAXDlgInstance->dlgBeatStep() ) ||
                                 ( g_pMidyAXDlgInstance->m_dlgFCB1010 && gp_learn_callingDialog == (QWidget *) g_pMidyAXDlgInstance->dlgFCB1010() )            )
                            {
                                emit g_pMidyAXDlgInstance->learnedMapping( channel, receivedCtlCC );
                            }
                        }
                    }
                    else {
                        g_learnModeChan = channel;
                        g_learnModeCC = receivedCtlCC;
                        g_learnModeCount = 0;
                        //g_learn_callingDialog = 0;
                    }
                    return;
                }
                // non-FIXED CC case : Send SYSEX to AXE-FX
                if( CCtoAXE[channel][receivedCtlCC][0] != 255 )
                g_pMidyAXDlgInstance->sendSYSEXtoAXEFX(AXEFX_SYSEX_PARAM_SET_S,
                                           CCtoAXE[channel][receivedCtlCC][0],
                                           CCtoAXE[channel][receivedCtlCC][1],
                                           CCtoAXE[channel][receivedCtlCC][2], receivedCCVal);

                //TODO : Check functionning - One has to check if the Channel/CC is mapped to other BlockID/ParamID
                // non-FIXED CC case : Send SYSEX to AXE-FX
                //Check if there are sereval MidiMapping for the same BlockID/ParamID
                for(int i = 0; i < g_pMidyAXDlgInstance->m_numbOfMappings ; i++)
                {
                    if(  g_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockID == CCtoAXE[channel][receivedCtlCC][0]
                      && g_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterID == CCtoAXE[channel][receivedCtlCC][1]
                      && (   g_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb != channel + 1
                          || g_pMidyAXDlgInstance->m_theMappingTable[i].CCID != receivedCtlCC )  )
                    {
                        for( int j = 1; j < MAX_NUMBER_MIDI_CONTROLLERS; j++)
                        {
                            if ( g_pMidyAXDlgInstance->m_theMIDIControllers[j].controllerConnected == true )
                            {
                                g_pMidyAXDlgInstance->sendCCtoMIDIout(
                                                            g_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb,
                                                            g_pMidyAXDlgInstance->m_theMappingTable[i].CCID,
                                                            g_pMidyAXDlgInstance->m_theMappingTable[i].MIDIValue,
                                                            j);
                                if( g_pMidyAXDlgInstance->m_logEnabled == true)
                                {
                                    ev2 = new ControlChangeEvent(  j,
                                                                  g_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb,
                                                                  g_pMidyAXDlgInstance->m_theMappingTable[i].CCID,
                                                                  g_pMidyAXDlgInstance->m_theMappingTable[i].MIDIValue,
                                                                  OUT );
                                    QApplication::postEvent(g_pMidyAXDlgInstance, ev2);
                                }
                            }
                        }
                    }
                }

            } // End of case GLOBAL MAPPING



            // Sending CC event to MidyAX UI to log
            ev2 = new ControlChangeEvent( MIDIController_Number, channel+1, receivedCtlCC, receivedCCVal, IN );

            // Start timer MIDI IN input active
            g_pMidyAXDlgInstance->m_MIDIIN_timer.start();


         } break;
    case STATUS_SYSEX: {
            // This case correspond to SYSEX answer from the controllers to the SYSEX config commands
            std::vector<unsigned char> SEvector( *message );
            // Sending SYSEX event to MidyAX UI
            ev2 = new SysExEvent( MIDIController_Number , SEvector );
        } break;
    case STATUS_PROGRAM: {
            unsigned char value = message->at(1);
            ev2 = new ProgramChangeEvent(value);
        } break;
    }

    if (ev2 != 0) QApplication::postEvent(g_pMidyAXDlgInstance, ev2);
}


void MidyAX::slotMidiSetup()
{
    dlgMidiSetup()->update();

    // Set current MIDI channels value in the dialog
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        dlgMidiSetup()->setFixedCCMIDIChannel( i, m_theFMMIDIControllers[i].fixedCCMIDIChannel);
        dlgMidiSetup()->setAXEFXMIDIChannel( i, m_theFMMIDIControllers[i].fixedAXEFXMIDIChannel);
        dlgMidiSetup()->setFixedEffectBlockOBControlMIDIChannel( i, m_theFMMIDIControllers[i].fixedEffectBlockOBControlMIDIChannel);
        dlgMidiSetup()->setFixedPageControlMIDIChannel( i, m_theFMMIDIControllers[i].fixedPageControlMIDIChannel);
    }

    dlgMidiSetup()->update();

    if (dlgMidiSetup()->exec() == QDialog::Accepted)
    {
        applyConnections();

        // Set current MIDI channels value from the dialog
        for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
        {
            m_theFMMIDIControllers[i].fixedCCMIDIChannel  = dlgMidiSetup()->getFixedCCMIDIChannel( i );
            m_theFMMIDIControllers[i].fixedPageControlMIDIChannel = dlgMidiSetup()->getFixedPageControlMIDIChannel( i );
            m_theFMMIDIControllers[i].fixedAXEFXMIDIChannel = dlgMidiSetup()->getAXEFXMIDIChannel( i );
            m_theFMMIDIControllers[i].fixedEffectBlockOBControlMIDIChannel = dlgMidiSetup()->getFixedEffectBlockOBControlMIDIChannel( i );

            if( m_theFMMIDIControllers[i].dlgObject != NULL)
            {
                m_theFMMIDIControllers[i].dlgObject->m_fixedParamControlMIDIChannel  = dlgMidiSetup()->getFixedCCMIDIChannel( i );
                m_theFMMIDIControllers[i].dlgObject->m_fixedPageControlMIDIChannel = dlgMidiSetup()->getFixedPageControlMIDIChannel( i );
                m_theFMMIDIControllers[i].dlgObject->m_fixedAXEFXMIDIChannel = dlgMidiSetup()->getAXEFXMIDIChannel( i );
                m_theFMMIDIControllers[i].dlgObject->m_fixedEffectBlockOBControlMIDIChannel = dlgMidiSetup()->getFixedEffectBlockOBControlMIDIChannel( i );
            }
        }

        getMidiMappingParamValues( false );
    }
    updateDisplayedConnectState();


}

void MidyAX::slotPrefs()
{
    if( dlgPrefs()->exec() == QDialog::Accepted)
    {
        // Update the dialogues if visible so that color option is taken into account
        for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
        {
            if( m_theFMMIDIControllers[i].controllerConnected == true && settings.value( m_theFMMIDIControllers[i].dlgObject->QSettings_visible ).toBool() )
            {
                m_theFMMIDIControllers[i].dlgObject->init();
            }
        }
        //TODO : add code for non-FIXED CC dialog
    }
    redisplay();
}


void MidyAX::slotMidiMapping()
{
    dlgMidiMapping()->init();
    if (dlgMidiMapping()->exec() == QDialog::Accepted)
    {
        fillCCtoAXE();
        getMidiMappingParamValues( false );

        // Update the LOCAL mappings with the changes in the GLOBAL mapping
        // Update the dialogues if visible so that color option is taken into account

        //TODO: to fix when proper non_FIXED mapping is in place
        for(int i=1; i < MAX_NUMBER_MIDI_CONTROLLERS; i++)
        {
            if( m_theMIDIControllers[i].dlgObject != NULL )
            {
                m_theMIDIControllers[i].dlgObject->init();
                //TODO: Add it again for the part porcessing the MIDI controller with non fixed CC ---- m_theFMMIDIControllers[i].dlgObject->fillComboBox();
                m_theMIDIControllers[i].dlgObject->updateKnobsDisplay();
                m_theMIDIControllers[i].dlgObject->update();
            }
        }
    }
}


void MidyAX::slotBCR2000()
{
    dlgBCR2000()->init();
    dlgBCR2000()->setModal(false);
    if( !dlgBCR2000()->isVisible() ) getMidiMappingParamValues(false);
    dlgBCR2000()->show();
}

void MidyAX::slotBCF2000()
{
    dlgBCF2000()->init();
    dlgBCF2000()->setModal(false);
    if( !dlgBCF2000()->isVisible() ) getMidiMappingParamValues(false);
    dlgBCF2000()->show();
}

void MidyAX::slotXTouchMini()
{
    dlgXTouchMini()->init();
    dlgXTouchMini()->setModal(false);
    if( !dlgXTouchMini()->isVisible() ) getMidiMappingParamValues(false);
    dlgXTouchMini()->show();
}

void MidyAX::slotBeatStep()
{
    dlgBeatStep()->init();
    dlgBeatStep()->setModal(false);
    if( !dlgBeatStep()->isVisible() ) getMidiMappingParamValues(false);
    dlgBeatStep()->show();
}

void MidyAX::slotFCB1010()
{
    dlgFCB1010()->init();
    dlgFCB1010()->setModal(false);
    if( !dlgFCB1010()->isVisible() ) getMidiMappingParamValues(false);
    dlgFCB1010()->show();
}

void MidyAX::slotGuitarWing()
{
    dlgGuitarWing()->init();
    dlgGuitarWing()->setModal(false);
    if( !dlgGuitarWing()->isVisible() ) getMidiMappingParamValues(false);
    dlgGuitarWing()->show();
}

void MidyAX::slotQuNeo()
{
    dlgQuNeo()->init();
    dlgQuNeo()->setModal(false);
    if( !dlgQuNeo()->isVisible() ) getMidiMappingParamValues(false);
    dlgQuNeo()->show();
}

void MidyAX::slotAboutMidyAXMenu()
{
    dlgAboutMidyAX()->exec();
}

void MidyAX::fillCCtoAXE( void )
{
    int MIDIchannel, MIDICC;

    // init CCtoAXE
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 128; j++)
        {
            CCtoAXE[i][j][0] = 255;
            CCtoAXE[i][j][1] = 0;
            CCtoAXE[i][j][2] = 0;
        }
    }
    // Fill it with the current mapping
    for(int i = 0; i < m_numbOfMappings; i++)
    {
        MIDIchannel = m_theMappingTable[i].chanNumb - 1; // Displayed MIDI channel 1 to 16 but coded as 0 to 15
        MIDICC = m_theMappingTable[i].CCID;
        CCtoAXE[ MIDIchannel ] [ MIDICC ] [0] = m_theMappingTable[i].effectBlockID;
        CCtoAXE[ MIDIchannel ] [ MIDICC ] [1] = m_theMappingTable[i].effectParameterID;
        CCtoAXE[ MIDIchannel ] [ MIDICC ] [2] = m_theMappingTable[i].effectParameterType;
    }
}


void MidyAX::slotSYSEXQueryVersion()
{
    sendSYSEXtoAXEFX( AXEFX_SYSEX_QUERY_VERSION );
}

void MidyAX::slotSYSEXQueryName()
{
    sendSYSEXtoAXEFX( AXEFX_SYSEX_QUERY_NAME );
}

void MidyAX::slotActivateResync()
{
    sendSYSEXtoAXEFX( AXEFX_SYSEX_ACT_RESYNC );
}

void MidyAX::slotWhoAmI()
{
    sendSYSEXtoAXEFX( AXEFX_SYSEX_WHO_AM_I );
}


void MidyAX::slotgetAXEFXParametersInfo()
{
    getAXEFXParametersInfo( START_GET_AXEFX_PARAMETERS_INFO );
}


unsigned char Calculate_CheckSum( std::vector<unsigned char>  *cur_sysex, int cur_size)
{
    unsigned char result = 0xF0;
    for(int i=1; i < cur_size ; i++)
    {
        result = result ^ cur_sysex->at(i);
    }
    result = result & 0x7F;
    return result;
}


void MidyAX::sendSYSEXtoAXEFX(unsigned char axefxSYSEXmessageID, unsigned char blockID, unsigned char paramID, int paramType, int CCvalue)
{
    bool SYSEXtoSend = false;
    std::vector<unsigned char> *message;

    switch( axefxSYSEXmessageID )
    {
    case AXEFX_SYSEX_PARAM_SET_S: // Message SYSEX_PARAM_SET
    case AXEFX_SYSEX_PARAM_SET_Q:
    case AXEFX_SYSEX_PARAM_SET_D:
        {
            message = new std::vector<unsigned char>(16);
            message->assign( m_sysex_header, m_sysex_header+5 );
            message->push_back(AXEFX_SYSEX_PARAM_SET); // 6th position in SYSEX message

            if ( blockID < 0x80 )
            {
                message->push_back(blockID);  // 7th position in SYSEX message
                message->push_back(0x00);      // 8th position in SYSEX message
            }
            else {
                message->push_back(blockID - 0x80); // 7th position in SYSEX message
                message->push_back(0x01);            // 8th position in SYSEX message
            }
            if ( paramID < 0x80 )
            {
                message->push_back(paramID);  // 9th position in SYSEX message
                message->push_back(0x00);      // 10th position in SYSEX message
            }
            else {
                message->push_back(paramID - 0x80); // 9th position in SYSEX message
                message->push_back(0x01);            // 10th position in SYSEX message
            }

            int OutputValue,tempo;
            unsigned char HB,MB,LB;
            float ratio;

            if( axefxSYSEXmessageID == AXEFX_SYSEX_PARAM_SET_S )
            {
                if( paramType == AXEFX_INT_Parameter_Type_DEFINE
                 || paramType == AXEFX_INTXL_Parameter_Type_DEFINE  ) // Test NOT type = INT or INTXL --> Modal
                {
                    // MODAL value
                    HB = 0x00;
                    MB = 0x00;
                    LB = CCvalue;  // Currently the BCR2000 is set to send CCs with values up to 127.
                                    // TODO : allow higher values, useful for AMP TYPE param
                }
                else {
                    //Process value
                    ratio = (float) CCvalue /127;
                    OutputValue = ratio*65536;
                    //OutputValue = (CCvalue+1)*512;
                    tempo = OutputValue / 16384; // (128 * 128)
                    HB = (unsigned char) tempo;

                    OutputValue = OutputValue - (HB * 16384);
                    tempo = OutputValue / 128;
                    MB = (unsigned char) tempo;

                    OutputValue = OutputValue - (MB * 128 );
                    LB = OutputValue ;
                }
                message->push_back(LB);            // 11th position in SYSEX message
                message->push_back(MB);            // 12th position in SYSEX message
                message->push_back(HB);            // 13th position in SYSEX message
                message->push_back(0x01);            // 14th position in SYSEX message //0xdd query(0) or set(1) value
                message->push_back( Calculate_CheckSum( message, message->size()) );            // 15th position in SYSEX message
                message->push_back(0xF7);            // 16th position in SYSEX messag
            }
            else {
                message->push_back(0x00);            // 11th position in SYSEX message
                message->push_back(0x00);            // 12th position in SYSEX message
                message->push_back(0x00);            // 13th position in SYSEX message
                if( axefxSYSEXmessageID == AXEFX_SYSEX_PARAM_SET_Q ) message->push_back(0x00);  // 14th position in SYSEX message //0xdd query(0) or set(1) value
                else message->push_back(0x02);       //case AXEFX_SYSEX_PARAM_SET_D
                message->push_back( Calculate_CheckSum( message, message->size() ) );           // 15th position in SYSEX message
                message->push_back(0xF7);            // 16th position in SYSEX messag
            }
            SYSEXtoSend = true;
        } break;
    case AXEFX_SYSEX_QUERY_VERSION: // Message SYSEX_QUERY_VERSION
        {
            //F0 00 01 74 03 08 0E F7
            message = new std::vector<unsigned char>(8);
            message->assign( m_sysex_header, m_sysex_header+5 );
            message->push_back(AXEFX_SYSEX_QUERY_VERSION);
            message->push_back( 0x0E); // TODO : replace with checksum calculation
            message->push_back( 0xF7);
            SYSEXtoSend = true;
        } break;
    case AXEFX_SYSEX_SET_NAME: // Message SYSEX_SET_NAME
        {
            // Device will respond with SYSEX_STATUS_MSG indicating either success (0) or an error code.

         } break;

    case AXEFX_SYSEX_WHO_AM_I :
        {
            message = new std::vector<unsigned char>(8);
            message->assign( m_sysex_header, m_sysex_header+4 );
            message->push_back( 0x7F);
            message->push_back(AXEFX_SYSEX_WHO_AM_I);
            message->push_back( Calculate_CheckSum( message, message->size() ) );
            message->push_back( 0xF7);
            SYSEXtoSend = true;
        } break;
    case AXEFX_SYSEX_QUERY_NAME: // Message SYSEX_QUERY_NAME
        {
            //F0 00 01 74 03 0F 09 F7
            // The device will respond with a SYSEX_QUERY_NAME message type containing the name.
            message = new std::vector<unsigned char>(8);
            unsigned char myucs[] = {0xF0, 0x00, 0x01, 0x74, 0x03, 0x0F, 0x09, 0xF7};
            message->assign( myucs, myucs+8 );
            SYSEXtoSend = true;
        } break;

    case AXEFX_SYSEX_GET_ALL_PARAMS: // Message SYSEX_GET_ALL_PARAMS
        {
            message = new std::vector<unsigned char>(10);
            message->assign( m_sysex_header, m_sysex_header+5 );
            message->push_back(AXEFX_SYSEX_GET_ALL_PARAMS); // 6th position in SYSEX message
            if ( blockID < 0x80 )
            {
                message->push_back(blockID);  // 7th position in SYSEX message
                message->push_back(0x00);      // 8th position in SYSEX message
            }
            else {
                message->push_back(blockID - 0x80); // 7th position in SYSEX message
                message->push_back(0x01);            // 8th position in SYSEX message
            }
            message->push_back( Calculate_CheckSum( message, message->size()) ); // 9th position in SYSEX message
            message->push_back( 0xF7);
            SYSEXtoSend = true;
        } break;

    case AXEFX_SYSEX_GET_PARAM_INFO: // Message SYSEX_GET_PARAM_INFO
        {
            message = new std::vector<unsigned char>(12);
            message->assign( m_sysex_header, m_sysex_header+5 );
            message->push_back(AXEFX_SYSEX_GET_PARAM_INFO); // 6th position in SYSEX message
            if ( blockID < 0x80 )
            {
                message->push_back(blockID);  // 7th position in SYSEX message
                message->push_back(0x00);      // 8th position in SYSEX message
            }
            else {
                message->push_back(blockID - 0x80); // 7th position in SYSEX message
                message->push_back(0x01);            // 8th position in SYSEX message
            }
            if ( paramID < 0x80 )
            {
                message->push_back(paramID);  // 9th position in SYSEX message
                message->push_back(0x00);      // 10th position in SYSEX message
            }
            else {
                message->push_back(paramID - 0x80); // 9th position in SYSEX message
                message->push_back(0x01);            // 10th position in SYSEX message
            }
            message->push_back( Calculate_CheckSum( message, message->size()) ); // 11th position in SYSEX message
            message->push_back( 0xF7);
            SYSEXtoSend = true;
        } break;

//    case AXEFX_SYSEX_ACT_RESYNC: // Message Ctivate RESYNC ???
//        {
//            //F0 00 01 74 03 42 44 09 F7
//            // The device will respond with a SYSEX_QUERY_NAME message type containing the name.
//            message = new std::vector<unsigned char>(8);
//            unsigned char myucs[] = {0xF0, 0x00, 0x01, 0x74, 0x03, 0x42, 0x44, 0xF7};
//            message->assign( myucs, myucs+8 );
//            SYSEXtoSend = true;
//        } break;

        case AXEFX_SYSEX_GET_MIDI_CHANNEL: // Message Ctivate RESYNC ???
            {
                //F0 00 01 74 03 17 11 F7
                // The device will respond with a SYSEX_QUERY_NAME message type containing the name.
                message = new std::vector<unsigned char>(8);
                unsigned char myucs[] = {0xF0, 0x00, 0x01, 0x74, 0x03, 0x17, 0x11, 0xF7};
                message->assign( myucs, myucs+8 );
                SYSEXtoSend = true;
            } break;

    default:
        break;
    }




    if (m_theFMMIDIControllers[0].The_MIDI_OUT != 0 && SYSEXtoSend )
    {
        try {
            m_theFMMIDIControllers[0].The_MIDI_OUT->sendMessage( message );
        } catch (RtMidiError& err) {
            qWarning() << QString::fromStdString(err.getMessage());
        }
        std::vector<unsigned char> SEvector (*message);
        // Sending SYSEX event to MidyAX UI
        QEvent* ev = new LogSentSysExEvent( 0 /*AXE-FX*/ , SEvector);
        if (ev != 0) QApplication::postEvent(this, ev);
    }
}

void MidyAX::getMidiMappingParamValues( bool firstTime)
{
    bool isportopen = m_theFMMIDIControllers[0].The_MIDI_OUT->isPortOpen();


    // TEMPO MOD1
    if( isportopen  == true )
    {
        sendSYSEXtoAXEFX( AXEFX_SYSEX_GET_MIDI_CHANNEL );
        int posi, totalNumberParam;
        for(int h=1; h < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; h++)
        {
            MIDIControllerGenericDialogMOD1 *curDlg = (MIDIControllerGenericDialogMOD1 *) m_theFMMIDIControllers[h].dlgObject;
            if( curDlg != NULL && m_theFMMIDIControllers[h].controllerConnected == true )
            {
                for( int i=0; i < curDlg->m_numberOfPageSelectButtons; i++)
                {
                    totalNumberParam = curDlg->m_numberOfKnobs + curDlg->m_numberOfSlidders + curDlg->m_numberOfParameterButtons;
                    for( int j=0; j < totalNumberParam; j++)
                    {
                        posi = j + ( totalNumberParam * i  );

                        if( curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID != 255 )
                        {
                            sendSYSEXtoAXEFX(   AXEFX_SYSEX_PARAM_SET_Q,
                                                curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID,
                                                curDlg->m_ThePagesMIDIMappingTable[posi].effectParameterID  );
#ifndef __MACOSX_CORE__
                            delay(10);
#endif
                        }
                    }
                }
            }
        }

        //if( firstTime )delay(100); //TODO: Check if useful


        for(int i = 0; i < m_numbOfMappings ; i++)
        {
            sendSYSEXtoAXEFX( AXEFX_SYSEX_PARAM_SET_Q,
                                              m_theMappingTable[i].effectBlockID,
                                              m_theMappingTable[i].effectParameterID  );
#ifndef __MACOSX_CORE__
            delay(10);
#endif
            if( firstTime ) delay(10); //TODO: Check if useful
        }
    }
}


int MidyAX::getAXEFXParametersInfo( int startContinue )
{
    static int blockID;
    static int paramID;
    switch( startContinue )
    {
    case START_GET_AXEFX_PARAMETERS_INFO:
        {
            blockID = 100;
            paramID = 0;
            gettingAXEFXParametersInfo  = true;
            sendSYSEXtoAXEFX(AXEFX_SYSEX_GET_ALL_PARAMS, The_AXE_Effects[blockID-100].effect_id_hex, paramID);
        } break;
    case CONTINUE_GET_AXEFX_PARAMETERS_INFO:
        {
            if( blockID < (100 + AXEFX_NUMBER_EFFECTS_BLOCK)
                    && TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters != NULL
                    && paramID < TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].numOfParameters )
            {
                sendSYSEXtoAXEFX(AXEFX_SYSEX_GET_PARAM_INFO, The_AXE_Effects[blockID-100].effect_id_hex, paramID);
                paramID++;
            }
            else{
                // Finished getting AXEFX paremeter info for all
                gettingAXEFXParametersInfo  = false;
            }
        } break;
    case ERROR_GET_AXEFX_PARAMETERS_INFO:
        {

        } break;
    default :
        break;
    } // end of switch  statement
    return 0;
}



void MidyAX::refreshConnections()
{
    // Refresh the list of available MIDI port IN an OUT in the MIDI setup dialog

    int i = 0, nInPorts = 0, nOutPorts = 0;
    try {
        dlgMidiSetup()->clearCombos();

        // inputs
        if (m_theFMMIDIControllers[0].The_MIDI_IN != 0)
        {
//#if !defined(__LINUX_ALSA__) && !defined(__MACOSX_CORE__) && !defined(__WINDOWS_DS__)
//            dlgMidiSetup()->setInputEnabled(m_currentIn != -1);
//#endif
            dlgMidiSetup()->addInputPortName(QString::null, -1);
            nInPorts = m_theFMMIDIControllers[0].The_MIDI_IN->getPortCount();
            for ( i = 0; i < nInPorts; i++ ) {
                QString name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_IN->getPortName(i) );
                if ( !name.startsWith( QSTR_MIDYAX ) )
                    dlgMidiSetup()->addInputPortName( name, i );
            }
        }

        // outputs
        dlgMidiSetup()->addOutputPortName(QString::null, -1);
        nOutPorts = m_theFMMIDIControllers[0].The_MIDI_OUT->getPortCount();
        for ( i = 0; i < nOutPorts; i++ ) {
            QString name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_OUT->getPortName(i) );
            if ( !name.startsWith( QSTR_MIDYAX ) )
                dlgMidiSetup()->addOutputPortName( name, i );
        }
    } catch (RtMidiError& err) {
        ui.statusBar->showMessage( QString::fromStdString( err.getMessage() ) );
    }


}



void MidyAX::autoConnect( void )
{
    // Connectect the MIDI ports according to what has been selected in the MIDI setup dialog
    int i, nInPorts = 0, nOutPorts = 0;
    bool found = false;
    QString fractProdName;

    try {
        nOutPorts = m_theFMMIDIControllers[0].The_MIDI_OUT->getPortCount();
        nInPorts = m_theFMMIDIControllers[0].The_MIDI_IN->getPortCount();

        if( g_autoConnect )
        {

            //LOOK for connected FRACTAL products and set SYSEX header accordingly
            m_sysex_header[0] = 0xF0;
            m_sysex_header[1] = 0x00;
            m_sysex_header[2] = 0x01;
            m_sysex_header[3] = 0x74;

            for( i = 0; i < nOutPorts; i++ )
            {
                QString name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_OUT->getPortName( i ) );
                if( name.contains("AXE-FX", Qt::CaseInsensitive) )
                {
                    fractProdName = "AXE-FX";
                    m_sysex_header[4] = 0x03;
                    break;
                }
                else if ( name.contains("FX8", Qt::CaseInsensitive) )
                {
                    fractProdName = "FX8";
                    m_sysex_header[4] = 0x05;
                    break;
                }
                else if ( name.contains("AXE XL", Qt::CaseInsensitive) )
                {
                    fractProdName = "AXE XL";
                    m_sysex_header[4] = 0x06;
                    break;
                }
                else if ( name.contains("AXE XL+", Qt::CaseInsensitive) )
                {
                    fractProdName = "AXE XL+";
                    m_sysex_header[4] = 0x07;
                    break;
                }
                else if ( name.contains("AX8", Qt::CaseInsensitive) )
                {
                    fractProdName = "AX8";
                    m_sysex_header[4] = 0x08;
                    break;
                }
            }
            dlgMidiSetup()->setFractProdName( fractProdName );
            ui.lbFractProd->setText( fractProdName );



            // Set-up AXE-FX port
            for( i = 0; i < nOutPorts; i++ )
            {
                QString name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_OUT->getPortName( i ) );
                if ( name.contains( fractProdName, Qt::CaseInsensitive) )
                {
                    m_theFMMIDIControllers[0].The_MIDI_OUT->openPort( i );
                    m_theFMMIDIControllers[0].RTMIDI_OUT_Port_Name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_OUT->getPortName( i ) );
                    m_theFMMIDIControllers[0].RTMIDI_OUT_Port_Number = i;
                    dlgMidiSetup()->setCurrentOutputIndexByPortOutputPortNumber( 0, i );
                    //TODO: update display
                    found = true;
                    break;
                }
            }
            for ( i = 0; i < nInPorts; i++ )
            {
                QString name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_IN->getPortName(i) );
                if ( name.contains("AXE-FX", Qt::CaseInsensitive) )
                {
                    m_theFMMIDIControllers[0].The_MIDI_IN->openPort( i );
                    m_theFMMIDIControllers[0].RTMIDI_IN_Port_Name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_IN->getPortName( i ) );
                    m_theFMMIDIControllers[0].RTMIDI_IN_Port_Number = i;
                    dlgMidiSetup()->setCurrentInputIndexByPortOutputPortNumber( 0, i );
                    if(found == true) //Need 2 found : Out and In
                    {
                        found = true;
                        m_theFMMIDIControllers[0].controllerConnected = true;
                    }
                    break;
                }
            }
            // If no Output connection to the AXE-FX --> ask if continue anyway.
            if( found != true )
            {
                QMessageBox* msgBox 	= new QMessageBox();
                msgBox->setWindowTitle("From MidyAX");
                msgBox->setText("No AXE-FX Connected ! Continue anyway ?" );
                msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox->setDefaultButton(QMessageBox::No);
                msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
                int ret = msgBox->exec();
                if( ret == QMessageBox::No ) exit(0);
            }


            bool found1, found2;
            for(int j=1; j< MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS;j++)
            {
                // This code suppose that the portNumber is the same for In and Out

                found1 = false;
                found2 = false;
                for( int k = 0; k < nOutPorts; k++ )
                {
                    QString name = QString::fromStdString( m_theFMMIDIControllers[j].The_MIDI_OUT->getPortName( k ) );
                    if ( name.contains( MIDI_Known_Controllers[j], Qt::CaseInsensitive)
                         || ( j == 7 && name.contains( QString("UM-2"), Qt::CaseInsensitive) ) )
                    {
                        m_theFMMIDIControllers[j].The_MIDI_OUT->openPort( k );
                        m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_OUT->getPortName( k ) );
                        m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Number = k;
                        dlgMidiSetup()->setCurrentOutputIndexByPortOutputPortNumber( j, k );
                        //TODO: update display
                        found1 = true;
                        break;
                    }
                }

                for( int k = 0; k < nInPorts; k++ )
                {
                    QString name = QString::fromStdString( m_theFMMIDIControllers[j].The_MIDI_IN->getPortName( k ) );
                    if ( name.contains( MIDI_Known_Controllers[j] , Qt::CaseInsensitive)
                         || ( j == 7 && name.contains( QString("UM-2"), Qt::CaseInsensitive) ) )
                    {
                        m_theFMMIDIControllers[j].The_MIDI_IN->openPort( k );
                        m_theFMMIDIControllers[j].RTMIDI_IN_Port_Name = QString::fromStdString( m_theFMMIDIControllers[0].The_MIDI_IN->getPortName( k ) );
                        m_theFMMIDIControllers[j].RTMIDI_IN_Port_Number = k;
                        dlgMidiSetup()->setCurrentInputIndexByPortOutputPortNumber( j, k );
                        found2 = true;
                        if( found1 == true ) m_theFMMIDIControllers[j].controllerConnected = true;
                        break;
                    }
                }

                if( (found1 == true and found2 == false) || (found1 == false && found2 == true) )
                {
                    QMessageBox* msgBox 	= new QMessageBox();
                    msgBox->setWindowTitle("From MidyAX");
                    msgBox->setText("Pb of matching IN/OUt ports! Continue anyway ?" );
                    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                    msgBox->setDefaultButton(QMessageBox::No);
                    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
                    int ret = msgBox->exec();
                    if( ret == QMessageBox::No ) exit(0);
                }
            }
        return;
        }
        /////////////////////////////
        /// END OF AUTO-CONNECT
        /////////////////////////////
    } catch (RtMidiError& err) {
        ui.statusBar->showMessage(QString::fromStdString(err.getMessage()));
    }
}

void MidyAX::applyConnections( void )
{
    //TODO : update when proper management of non-fixed mapping MIDI controllers
    int index, curIndex, nInPorts = 0, nOutPorts = 0, selectedINPortNumber, selectedOUTPortNumber;
    int j;



    try
    {
        //TODO : for now only checking Fixed Mapping list --> Do it for Global Mapping
        nOutPorts = m_theFMMIDIControllers[0].The_MIDI_OUT->getPortCount();
        nInPorts = m_theFMMIDIControllers[0].The_MIDI_IN->getPortCount();

        for( j=0; j< MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; j++ )
        {
            selectedINPortNumber = -1;
            selectedOUTPortNumber = -1;
            if( m_theFMMIDIControllers[ j ].The_MIDI_OUT != NULL )
            {
                index = dlgMidiSetup()->getSelectedOutputIndex( j );
                curIndex = dlgMidiSetup()->getCurrentOutputIndex( j );
                if( index > 0  &&  index < nOutPorts  && index != curIndex )
                {
                    // Open the new selected OUT port and close old one if necessary
                    if( m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Number != -1)
                    {
                        m_theFMMIDIControllers[j].The_MIDI_OUT->closePort();
                    }
                    selectedOUTPortNumber = dlgMidiSetup()->getSelectedOutputPortNumber( j );
                    QString OUTportName = QString::fromStdString( m_theFMMIDIControllers[j].The_MIDI_OUT->getPortName( selectedOUTPortNumber ) );
                    m_theFMMIDIControllers[j].The_MIDI_OUT->openPort( selectedOUTPortNumber );
                    m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Number = selectedOUTPortNumber;
                    m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Name = OUTportName;

                    dlgMidiSetup()->setCurrentOutputIndexByPortOutputPortNumber( j, selectedOUTPortNumber );
                }
                else if( index == 0 && m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Number != -1)
                {
                    // If new value is no OUT port, where there was one before --> close connection
                    selectedOUTPortNumber = -1;
                    m_theFMMIDIControllers[j].controllerConnected = false;
                    m_theFMMIDIControllers[j].The_MIDI_OUT->closePort();
                    m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Number = -1;
                    m_theFMMIDIControllers[j].RTMIDI_OUT_Port_Name = QString( "" );

                    dlgMidiSetup()->setCurrentOutputIndexByPortOutputPortNumber( j, selectedOUTPortNumber );
                }
            }

            if( m_theFMMIDIControllers[j].The_MIDI_IN != NULL )
            {
                index = dlgMidiSetup()->getSelectedInputIndex( j );
                curIndex = dlgMidiSetup()->getCurrentInputIndex( j );

                // Open the new selected IN port and close old one if necessary
                if( index != dlgMidiSetup()->getCurrentInputIndex( j ) && m_theFMMIDIControllers[j].controllerConnected && m_theFMMIDIControllers[j].RTMIDI_IN_Port_Number != -1)
                {
                    m_theFMMIDIControllers[j].The_MIDI_IN->cancelCallback();
                    m_theFMMIDIControllers[j].controllerConnected = false;
                    m_theFMMIDIControllers[j].The_MIDI_IN->closePort();
                    m_theFMMIDIControllers[j].RTMIDI_IN_Port_Number = -1;
                    m_theFMMIDIControllers[j].RTMIDI_IN_Port_Name = QString("");
                    delete m_theFMMIDIControllers[j].The_MIDI_IN;

                    selectedINPortNumber = -1;
                    dlgMidiSetup()->setCurrentInputIndexByPortOutputPortNumber( j, selectedINPortNumber );
                }
                else if( index == 0 && m_theFMMIDIControllers[j].RTMIDI_IN_Port_Number != -1)
                {
                    // If new value is "no IN port", where there was one before --> close connection
                    selectedINPortNumber = -1;
                    m_theFMMIDIControllers[j].controllerConnected = false;
                    m_theFMMIDIControllers[j].The_MIDI_IN->closePort();
                    m_theFMMIDIControllers[j].RTMIDI_IN_Port_Number = -1;
                    m_theFMMIDIControllers[j].RTMIDI_IN_Port_Name = QString( "" );
                    //delete m_theFMMIDIControllers[j].The_MIDI_IN;

                    dlgMidiSetup()->setCurrentInputIndexByPortOutputPortNumber( j, selectedINPortNumber );
                }

                if( index > 0 && index < nInPorts && index != dlgMidiSetup()->getCurrentInputIndex( j ) )
                {
                    // The RTMIDIIN object is connected to a new MIDI port
                    //delete m_theFMMIDIControllers[j].The_MIDI_IN;
                    m_theFMMIDIControllers[j].The_MIDI_IN = MIDIInDriverFactory( m_midiDriver, m_theFMMIDIControllers[j].The_MIDI_IN_Name );

                    selectedINPortNumber = dlgMidiSetup()->getSelectedInputPortNumber( j );
                    QString INportName = QString::fromStdString( m_theFMMIDIControllers[j].The_MIDI_IN->getPortName( selectedINPortNumber ) );
                    m_theFMMIDIControllers[j].controllerConnected = true;


                    m_theFMMIDIControllers[j].The_MIDI_IN->openPort( selectedINPortNumber );
                    m_theFMMIDIControllers[j].The_MIDI_IN->setCallback( m_theFMMIDIControllers[j].MidiCallbackFunctions, this );
                    m_theFMMIDIControllers[j].RTMIDI_IN_Port_Number = selectedINPortNumber;
                    m_theFMMIDIControllers[j].RTMIDI_IN_Port_Name = INportName;

                    dlgMidiSetup()->setCurrentInputIndexByPortOutputPortNumber( j, selectedINPortNumber );
                }
            }
        }
    } catch (RtMidiError& err) {
        ui.statusBar->showMessage(QString::fromStdString(err.getMessage()));
    }
}



void MidyAX::customEvent ( QEvent *event )
{
    //QString MIDI_Message = QString("Message Received" );
    //ui.logMIDI->append(MIDI_Message);
    //qDebug() << "customEvent:" << event->type();

    // *********************
    // Process SYSEX EVENTS
    // *********************

    // MIDIContDialSetValEventType) {
    if( event->type() ==  MIDIContDialSetValEventType) {
        MIDIContDialSetValEvent *ev = static_cast<MIDIContDialSetValEvent *>(event);
        m_theFMMIDIControllers[ ev->getMIDIContNumb() ].dlgObject->setValue( ev->getPageNumb(), ev->getElemNumb(), ev->getDispValue() );

//        QEvent *ev1;
//        ev1 = new IHMSetValEvent( ev->getPageNumb(),  ev->getElemNumb(), ev->getDispValue() );
//        MIDIControllerGenericDialogMOD1 *tempo1 = m_theFMMIDIControllers[ ev->getMIDIContNumb() ].dlgObject;
//        QObject *itit = (QObject *) tempo1;
//        if (ev1 != 0) QApplication::postEvent( tempo1,  ev1, Qt::HighEventPriority  );

        event->accept();
    }
    else if( event->type() ==  MIDIContDialPageChangeEventType) {
        MIDIContDialPageChangeEvent *ev = static_cast<MIDIContDialPageChangeEvent *>(event);
        m_theFMMIDIControllers[ ev->getMIDIContNumb() ].dlgObject->processPageChangeRequest( ev->getReceivedCC(), ev->getReceivedVal() );
        event->accept();
    }
    else if( event->type() ==  AXEFXMIDIChannelEventType )
    {
        AXEFXMIDIChannelEvent *ev = static_cast<AXEFXMIDIChannelEvent *>(event);
        int receivedChannel = ev->getAXEFXChannel();
        // If the current AXE-FX MIDI Channel is different than the stored one --> display change dialog
        if( receivedChannel != ( m_AXEFXChanNumb - 1 ) )
        {
            if( m_AXEFXChanNumb != -1)
            {
                QMessageBox* msgBox 	= new QMessageBox();
                msgBox->setWindowTitle("From MidyAX");
                msgBox->setText("Current AXE-FX channel different than the channel stored on the MIDYAX!\n Set MIDYAX stored channel to current AXE-FX channel " + QString::number(ev->getAXEFXChannel()+1) + " ?" );
                msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox->setDefaultButton(QMessageBox::Yes);
                msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
                int ret  =msgBox->exec();
                if( ret == QMessageBox::Yes ) m_AXEFXChanNumb = receivedChannel +1;
            }
            else {
                // If first run, no Qsettings exit --> m_AXEFXChanNumb = -1 on the value received from the AXE-FX is used
                m_AXEFXChanNumb = receivedChannel +1;
            }
        }
    }
    else if( event->type() ==  SysExEventType) {
        SysExEvent *ev = static_cast<SysExEvent *>(event);
        std::vector<unsigned char> *SysExVect = ev->getSysEx();

        if( ev->getDevice() == 0 /*AXE-FX*/ )
        {
            // Process SYSEX (Received from AXE-FX)
            //quint8 *sysexData = SysExVect->data();
            //int AXE_SYSEXerror = processSYSEXReceivedFromAXEFX( sysexData, int(SysExVect->size()) );
            //if( AXE_SYSEXerror < 0 ) {return;}

            // Log message in logMIDI MessageBox (QTextEdit)

            if( m_logEnabled )
            {
                QString MIDI_Message = QString("AXE_FX IN = ");
                for (std::vector<unsigned char>::iterator it = SysExVect->begin(); it != SysExVect->end(); ++it)
                {
                    MIDI_Message.append( QString::number(*it,16).toUpper().rightJustified(2,'0'));
                    //MIDI_Message.append(  QString::sprintf("%02X", *it) );
                    MIDI_Message.append( " " );
                }
                ui.logMIDI->append(MIDI_Message);
            }
        }
        event->accept();
    }
    else if( event->type() ==  ControlChangeEventType ) {
        // *********************
        // Process CC EVENTS
        // *********************
        ControlChangeEvent *ev = static_cast<ControlChangeEvent*>(event);

        bool found;
        for( int i=1; i <MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
        {
            if( ev->getDevice() == i && m_theFMMIDIControllers[i].controllerConnected)
            {
                found = true;
                break;
            }
        }

        if( found == true )
        {
            int channel = ev->getChannel();
            int ctl = ev->getController();
            int val = ev->getValue();
            int direction = ev->getDirection();
            QString SDir;

            if( m_logEnabled )
            {
                if( direction == IN ) SDir = QString("IN");
                else SDir = QString("OUT");

                QString MIDI_Message = QString("%1 CC %2: Channel = %3, Control = %4. Value = %5")
                        .arg( MIDI_Known_Controllers[ ev->getDevice() ], SDir, QString::number(channel), QString::number(ctl), QString::number(val));
                ui.logMIDI->append(MIDI_Message);
            }
        }
        event->accept();
    }
    else if ( event->type() ==  LogSentSysExEventType) {
        // *********************
        // Process Loging events
        // *********************
        LogSentSysExEvent *ev = static_cast<LogSentSysExEvent *>(event);
        std::vector<unsigned char> *SysExVect = ev->getSysEx();

        if( m_logEnabled )
        {
            QString MIDI_Message = QString("OUT = ");
            for (std::vector<unsigned char>::iterator it = SysExVect->begin(); it != SysExVect->end(); ++it)
            {
                MIDI_Message.append( QString::number(*it,16).toUpper().rightJustified(2,'0'));
                MIDI_Message.append( " " );
            }
            ui.logMIDI->append(MIDI_Message);
        }
        event->accept();
    }
    else {
        event->ignore();
    }
//  else if ( event->type() ==  ProgramChangeEventType) {
    // *********************
    // Process PC events
    // *********************
 //        ProgramChangeEvent *ev = static_cast<ProgramChangeEvent*>(event);
//        int val = ev->getValue();

//        QString MIDI_Message = QString("PROGRAM Change : Control = %1").arg( QString::number(val));
//        ui.logMIDI->append(MIDI_Message);

//        ////updateProgramChange(val);
//#ifdef ENABLE_DBUS
//        emit event_programchange(val);
//#endif
//    }

}


void delay( int millisecondsToWait )
{
    QElapsedTimer timer;
    timer.start();
    while( timer.elapsed() < millisecondsToWait )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void MidyAX::sendCCtoMIDIout( int chanNumb, unsigned char CCID, int paramValue, int MIDIController_Number )
{
    std::vector<unsigned char> *message;
    message = new std::vector<unsigned char>;
    //chanNumb--;

    unsigned char status = 0xB0 | ( ((unsigned char) ( chanNumb -1 ) )& 0x0F);
    message->push_back( status );      // 1th position in CC message
    message->push_back( CCID );        // 2th position in CC message
    message->push_back( (unsigned char) paramValue );  // 3th position in CC message
    try {
        m_theFMMIDIControllers[MIDIController_Number].The_MIDI_OUT->sendMessage( message );

    } catch (RtMidiError& err) {
        qWarning() << QString::fromStdString(err.getMessage());
    }
    message->resize(0);
    delete message;
}





int /*Error code*/ MidyAX::processSYSEXReceivedFromAXEFX( quint8 *sysexData )
{   
    double convertedValue;
    QEvent *ev1 = 0, *ev2 = 0;

    // Check SYSEX message header
    // TODO: improve test
//    int size_sysex = sysexData->size();
//    if ( sysexData[0] != 0xF0 || sysexData[1] != 0x00 || sysexData[2] != 0x01 || sysexData[3] != 0x74 || sysexData[4] != 0x03 || size_sysex < 5)
//    {
//        QString MIDI_Message = QString("Rejected ill-formed AXE-FX SYSEX message");
//        ui.logMIDI->append(MIDI_Message);
//        return -1;
//    }

    switch( sysexData[5])
    {
        case AXEFX_SYSEX_PARAM_SET: // Message SYSEX_PARAM_SET
        {
            int blockID = sysexData[6] + 0x80 * sysexData[7]-100;
            int paramID = sysexData[8] + 0x80 * sysexData[9];

            int posi, totalNumberOfParam, curDlgPage; // curDlgElem;

            // TODO: improve search efficiency
            // Search for matching MAPPING in all the active/connected MIDI controller dialog
            for(int h=1; h < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; h++)
            {
                // if blockID/ParamID not mapped or MIDI controller not connected --> pass to next MIDI controller
                if( MIDIContActMap[h-1][blockID][paramID][0][0] == 255 || m_theFMMIDIControllers[h].controllerConnected == false) continue;

                MIDIControllerGenericDialogMOD1 *curDlg = m_theFMMIDIControllers[h].dlgObject;

                totalNumberOfParam = curDlg->m_numberOfKnobs + curDlg->m_numberOfSlidders + curDlg->m_numberOfParameterButtons;

                // Iterates on the number of mapping for a same BlockID/paramID pair on the curDlg --> allow for multiple mapping of a param on a MIDII Controller
                for(int a=0; a < AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE; a++)
                {
                    curDlgPage = MIDIContActMap[h-1][blockID][paramID][0][a];
                    if( curDlgPage == 255) break; //Stops as soon as one element has "empty" value
                    posi = MIDIContActMap[h-1][blockID][paramID][1][a] + (  totalNumberOfParam *  curDlgPage);
                    pageMappingTable *curMapping = &(curDlg->m_ThePagesMIDIMappingTable[posi]);

                    curMapping->paramValue = sysexData[10] + sysexData[11] * 128 + sysexData[12] * 16384;
                    curMapping->MIDIValue = sysexData[13];
                    // TODO: decode and store the value string at the end of the message

                    // Convert the MIDI value to the displayed the value
                    convertedValue = curMapping->MIDIValue;
                    if( curMapping->effectParameterType != AXEFX_LOG_Parameter_Type_DEFINE )
                    {
                        convertedValue /= 127;
                        convertedValue *= ( curMapping->maxDispValue
                                            - curMapping->minDispValue );
                        convertedValue += curMapping->minDispValue;
                    }
                    else {
                        double R0 = 0.0101034, R1 = 4.6412;
                        convertedValue = R0*(exp( convertedValue/127*R1)-1);
                        convertedValue = convertedValue * (curMapping->maxDispValue
                                          - curMapping->minDispValue) ;
                        convertedValue += curMapping->minDispValue;
                    }
                    curMapping->paramDispValue = convertedValue;

                    // Sends the value to the MIDI Controller's dialogs if NOT in INI phase
                    if( m_initPhase == false )
                    {
                        //m_theFMMIDIControllers[h].dlgObject->setValue( curDlgPage, MIDIContActMap[h-1][blockID-100][paramID][1][a], convertedValue);
                        ev1 = new MIDIContDialSetValEvent( h, curDlgPage,  MIDIContActMap[h-1][blockID][paramID][1][a], convertedValue );

                        if (ev1 != 0)
                        {
                            QApplication::removePostedEvents(this, MIDIContDialSetValEventType);
                            //QApplication::sendPostedEvents(this, MIDIContDialSetValEventType);
                            QApplication::postEvent(this, ev1, Qt::HighEventPriority );
                        }
                    }


                    // Send messages to MIDI controler's MIDI OUTs (not to AXEFX) !!!Only for the current active page !!!
                    if( (    m_MIDIIN_timer.elapsed() > 3000 // Handles the case where the a MIDI COntroller has sent CCs --> no need to sent it back to it
                         || !m_MIDIIN_timer.isValid() ) // Handles the initial reception of the param values from the AXEFX --> initialize the values on the MIDI Controllers
                         &&  curDlg->m_currentPage  == curDlgPage )  // MIDI controller update only if param on current page

                    {
                        sendCCtoMIDIout(  curDlg->m_fixedParamControlMIDIChannel,
                                          MIDIContActMap[h-1][blockID][paramID][1][a] + 1,
                                          curMapping->MIDIValue,
                                          h);
                        //LOG CC OUT event
                        if( m_logEnabled == true)
                        {
                            ev2 = new ControlChangeEvent( h,
                                                         curDlg->m_fixedParamControlMIDIChannel,
                                                         curDlgPage + 1,
                                                         curMapping->MIDIValue,
                                                         OUT );
                            if (ev2 != 0) QApplication::postEvent(this, ev2);
                        }
                    }
                }
            }


            blockID = sysexData[6] + 0x80 * sysexData[7];
            // GLOBAL MAPPING case
            // Check if Block-ID and Param-ID match one of the MIDI mappings
            for(int i = 0; i < m_numbOfMappings ; i++)
            {
                if(  m_theMappingTable[i].effectBlockID == blockID
                 && m_theMappingTable[i].effectParameterID == paramID )
                {
                    // Convert the received SYSEX values and store them in parameterValue and knobValue
                    // TODO : include knobValue convetion for LOG case
                    if(    m_theMappingTable[i].effectParameterType == AXEFX_INT_Parameter_Type_DEFINE
                        || m_theMappingTable[i].effectParameterType == AXEFX_INTXL_Parameter_Type_DEFINE  ) // test not type = INT --> Modal
                    {
                        m_theMappingTable[i].paramValue = sysexData[10] + sysexData[11] * 128 ;
                        m_theMappingTable[i].MIDIValue = sysexData[13];
                    }
                    else {
                        m_theMappingTable[i].paramValue = sysexData[10] + sysexData[11] * 128 + sysexData[12] * 16384;
                        m_theMappingTable[i].MIDIValue = sysexData[13];
                    }

                    // Send messages to MIDI controler's MIDI OUTs (not to AXEFX)
                    if(     m_MIDIIN_timer.elapsed() > 3000 // Handles the case where the a MIDI COntroller as sent CCs --> no need to sent it back to it
                         || !m_MIDIIN_timer.isValid() )  // Handles the initial reception of the param values from the AXEFX --> initialize the values on the MIDI Controllers
                    {
                        for(int j = 1; j < MAX_NUMBER_MIDI_CONTROLLERS; j++)
                        {
                            //TODO: Fix when proper non-fixed CC MIDI controllers are set-up properly
                            if( m_theMIDIControllers[i].controllerConnected == true )
                            sendCCtoMIDIout(  m_theMappingTable[i].chanNumb,
                                              m_theMappingTable[i].CCID,
                                              m_theMappingTable[i].MIDIValue,
                                              j);

                            if( m_logEnabled == true)
                            {
                                ev2 = new ControlChangeEvent( j,
                                                             m_theMappingTable[i].chanNumb,
                                                             m_theMappingTable[i].CCID,
                                                             m_theMappingTable[i].MIDIValue,
                                                             OUT );
                                if (ev2 != 0) QApplication::postEvent(this, ev2);
                            }
                        }
                    }
                    // Display the value
                    double convertedValue;
                    /*if(m_theMappingTable[i].effectParameterType == AXEFX_LIN_Parameter_Type_DEFINE)
                    {
                        if( m_theMappingTable[i].MIDIValue <= 62) convertedValue = m_theMappingTable[i].MIDIValue +1;
                        if( m_theMappingTable[i].MIDIValue >= 63) convertedValue = m_theMappingTable[i].MIDIValue -1;
                    }*/
                    convertedValue = m_theMappingTable[i].MIDIValue;
                    convertedValue /= 127;
                    convertedValue *= ( m_theMappingTable[i].maxDispValue - m_theMappingTable[i].minDispValue );
                    convertedValue += m_theMappingTable[i].minDispValue;
                    //convertedValue += 0.5;
                    //convertedValue = floor(convertedValue);
                    //m_theMappingTable[i].paramDispValue = int( convertedValue );
                    m_theMappingTable[i].paramDispValue = convertedValue;

                    // Sends the value to the MIDI Controller's dialogs if in INI phase
                    if( m_initPhase == false )
                    {
                        for(int j=1; j < MAX_NUMBER_MIDI_CONTROLLERS; j++)
                        {
                            //TODO: Fix when proper non-fixed CC MIDI controllers are set-up properly
                            if( m_theMIDIControllers[j].controllerConnected == true ) //&& m_theMIDIControllers[j].dlgObject->isVisible() == true)
                            {
                               m_theMIDIControllers[j].dlgObject->setValueIfMapped( m_theMappingTable[i].effectBlockID,
                                                                                  m_theMappingTable[i].effectParameterID,
                                                                                  m_theMappingTable[i].paramDispValue);
                            }
                        }
                    }
                }
            }


        } break;
        case AXEFX_SYSEX_QUERY_VERSION: // Message SYSEX_QUERY_VERSION
        {
             // Device will respond with SYSEX_QUERY_VERSION message containing the current firmware version as #defined in the project.
             //Product info = sysexData[10];
             //Hardware Revision = sysexData[11];
        } break;
        case AXEFX_SYSEX_SET_NAME: // Message SYSEX_SET_NAME
        {
             // Device will respond with SYSEX_STATUS_MSG indicating either success (0) or an error code.

        } break;
        case AXEFX_SYSEX_QUERY_NAME: // Message SYSEX_QUERY_NAME
        {
             // The device will respond with a SYSEX_QUERY_NAME message type containing the name.

        } break;


        case AXEFX_SYSEX_EFFECT_START:  // Message SYSEX_EFFECT_START
                                        // Received after sending SYSEX_GET_ALL_PARAMS message
        {
            int blockID, numberOfParam;
            if ( sysexData[7] == 0x00 ) { blockID = sysexData[6]; }
                                   else { blockID = sysexData[6] + 0x80;}
            if ( sysexData[9] == 0x00 ) { numberOfParam = sysexData[8]; }
                                   else { numberOfParam = sysexData[8] + 0x80;}

//            sysexData[10] contains :
//            General Effect Data Byte - 1 MIDI byte
//            Bit 0: number of alt settings
//            Bit 1: current alt setting
//            Bit 2: bypassed
//            Bit 3: reserved
//            Bit 4-7: global block reference

            if( gettingAXEFXParametersInfo )
            {
                TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].numOfParameters = numberOfParam;
                //TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters = NULL;
                //TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters =  static_cast <struct AXEFX_Parameter (*) []> (malloc(sizeof(struct AXEFX_Parameter) * numberOfParam));
                if(  TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters != NULL )
                {
                    //sendSYSEX(AXEFX_SYSEX_GET_PARAM_INFO, blockID, 0);
                    getAXEFXParametersInfo( CONTINUE_GET_AXEFX_PARAMETERS_INFO );
                }
                else { getAXEFXParametersInfo( ERROR_GET_AXEFX_PARAMETERS_INFO ); }
            }
        } break;


        case AXEFX_SYSEX_GET_PARAM_INFO:  // Message SYSEX_GET_PARAM_INFO
        {
            /*
            //int blockID, paramID;
            quint32 paramType, paramLowLimit, paramHighLimit, paramMultiplier, paramResolution;
//            if ( sysexData[7] == 0x01 ) { blockID = sysexData[6]; }
//                                   else { blockID = sysexData[6] + 0x80;}
//            if ( sysexData[9] == 0x01 ) { paramID = sysexData[8]; }
//                                   else { paramID = sysexData[8] + 0x80;}

            paramType = sysexData[6] + (sysexData[7] * 0x80) + (sysexData[8] * (0x80 ^ 2)) + (sysexData[9] * (0x80 ^ 3)) + (sysexData[10] * (0x80 ^ 4));
            paramLowLimit = sysexData[11] + (sysexData[12] * 0x80) + (sysexData[13] * (0x80 ^ 2)) + (sysexData[14] * (0x80 ^ 3)) + (sysexData[15] * (0x80 ^ 4));
            paramHighLimit = sysexData[16] + (sysexData[17] * 0x80) + (sysexData[18] * (0x80 ^ 2)) + (sysexData[19] * (0x80 ^ 3)) + (sysexData[20] * (0x80 ^ 4));
            paramMultiplier = sysexData[21] + (sysexData[22] * 0x80) + (sysexData[23] * (0x80 ^ 2)) + (sysexData[24] * (0x80 ^ 3)) + (sysexData[25] * (0x80 ^ 4));
            paramResolution = sysexData[26] + (sysexData[27] * 0x80) + (sysexData[28] * (0x80 ^ 2)) + (sysexData[29] * (0x80 ^ 3)) + (sysexData[30] * (0x80 ^ 4));

//            TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters[paramID].paramType = paramType;
//            TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters[paramID].paramLowLimit = paramLowLimit;
//            TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters[paramID].paramHighLimit = paramHighLimit;
//            TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters[paramID].paramMultiplier = paramMultiplier;
//            TheEffectTypes[ AXEFX_Effect_Block_ID_to_Effect_Type_ID[ blockID-100 ] ].TheParameters[paramID].paramResolution = paramResolution;

            if( gettingAXEFXParametersInfo )
            {
                //delay(50);
                getAXEFXParametersInfo( CONTINUE_GET_AXEFX_PARAMETERS_INFO );
            }
            */
        } break;


        case AXEFX_SYSEX_RESYNC: // Message SYSEX_RESYNC
            //TODO: Determine if resync is due to changes mmapped parameter value. Feasible ???
        case AXEFX_SYSEX_PATCHNUM :
        {
             getMidiMappingParamValues( false );
             // Update the dialogues if visible so that the drop down list is updated
             for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
             {
                 if(     m_theFMMIDIControllers[i].controllerConnected == true
                      && settings.value( m_theFMMIDIControllers[i].dlgObject->QSettings_visible ).toBool() )
                 {
                     m_theFMMIDIControllers[i].dlgObject->init();
                     m_theFMMIDIControllers[i].dlgObject->updateKnobsDisplay();
                     m_theFMMIDIControllers[i].dlgObject->update();
                 }
             }
        } break;


        case AXEFX_SYSEX_GET_MIDI_CHANNEL :
        {
            ev1 = new AXEFXMIDIChannelEvent( sysexData[6] );
            if (ev1 != 0) QApplication::postEvent(this, ev1);

//            // If the current AXE-FX MIDI Channel is different than the stored one --> display change dialog
//            if( sysexData[6] != ( m_AXEFXChanNumb - 1 ) )
//                {
//                    if( m_AXEFXChanNumb != -1)
//                    {
//                    QMessageBox* msgBox 	= new QMessageBox();
//                    msgBox->setWindowTitle("From MidyAX");
//                    msgBox->setText("Current AXE-FX channel different than the channel stored on the MIDYAX!\n Set MIDYAX stored channel to current AXE-FX channel " + QString::number(sysexData[6]+1) + " ?" );
//                    msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
//                    msgBox->setDefaultButton(QMessageBox::Yes);
//                    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
//                    int ret  =msgBox->exec();
//                    if( ret == QMessageBox::Yes ) m_AXEFXChanNumb = sysexData[ 6 ] +1;
//                    }
//                    else {
//                        // If first run, no Qsettings exit --> m_AXEFXChanNumb = -1 on the value received from the AXE-FX is used
//                        m_AXEFXChanNumb = sysexData[ 6 ] +1;
//                    }
//                }
        } break;


        default:
        {
            //TODO : Put default case
        } break;
    }
    return 0;
}



void MidyAX::readSettings()
{

    // Load the Preferences
    settings.beginGroup("Preferences");
        m_logEnabled = settings.value( QSTR_PREFS_EVENT_LOG_ENABLED ).toBool();
        g_sliderColored  = settings.value( QSTR_PREFS_COLORED_SLIDERS ).toBool();
        g_displayBlownUp = settings.value( QSTR_PREFS_DISPLAY_BLOWN_UP ).toBool();
        g_autoConnect = settings.value( QSTR_PREFS_AUTO_CONNECT ).toBool();
        g_MIDIdataInterval = settings.value( QSTR_PREFS_MIDI_DATA_INTERVAL ).toBool();
        g_MIDIdataInterval_NumberInterval = settings.value( QSTR_PREFS_MIDI_DATA_INTERVAL_NUMBER ).toInt();
        m_AXEFXChanNumb  = settings.value( QSTR_PREFS_AXEFX_CHAN_NUMB, -1 ).toInt();
        ui.rbnActivateLog->setChecked( m_logEnabled );
    settings.endGroup();

    // Restore the geometry of the main windows
    settings.beginGroup(QSTR_WINDOW);
    restoreGeometry(settings.value(QSTR_GEOMETRY).toByteArray());
    restoreState(settings.value(QSTR_STATE).toByteArray());
    settings.endGroup();

    // Load the last MIDI Mapping
    m_numbOfMappings  = 0;
    m_numbOfMappings  =  settings.value( QSTR_NUM_OF_MAPPINGS ).toInt();


    // Read fixed MIDI channels for the fixed mapping controllers
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        QString group = m_theFMMIDIControllers[i].controllerName + QString("_FIXED_CC_MIDI_CONFIG");
        settings.beginGroup(group);
            m_theFMMIDIControllers[i].fixedCCMIDIChannel= settings.value( "paramMIDIchannel", 0 ).toInt();
            m_theFMMIDIControllers[i].fixedAXEFXMIDIChannel = settings.value( "AXEFXCCMIDIchannel", 14 ).toInt();
            m_theFMMIDIControllers[i].fixedEffectBlockOBControlMIDIChannel = settings.value( "OBcontrolMIDIchannel", 15 ).toInt();
            m_theFMMIDIControllers[i].fixedPageControlMIDIChannel = settings.value( "pageMIDIchannel", 16 ).toInt();
        settings.endGroup();
    }


    // Case when no global mapping present
    if( m_numbOfMappings == 0) return;

    for(int i = 0; i < m_numbOfMappings ; i++)
    {
        QString group = QSTR_MIDI_MAPPING + QString("%1").arg(i+1, 3, 10, QChar('0'));
        settings.beginGroup(group);

        m_theMappingTable[i].chanNumb = settings.value( QSTR_CHAN_NUMB ).toInt();
        m_theMappingTable[i].CCID = settings.value( QSTR_CCID ).toInt();
        m_theMappingTable[i].effectBlockID = settings.value( QSTR_EFFECT_BLOCK_ID ).toInt();
        m_theMappingTable[i].effectParameterID = settings.value( QSTR_EFFECT_PARAMETER_ID ).toInt();

        int j;
        // Fill the m_theMappingTable with the Block, Param label and Param Type
        for( j = 0; j < AXEFX_NUMBER_EFFECTS_BLOCK ; j++)
        {
            if( m_theMappingTable[i].effectBlockID == EffectBlock__ID[j] ) break;
        }
        //TODO: display a message instead of exit(0)
        if( j == AXEFX_NUMBER_EFFECTS_BLOCK )
        {
            QMessageBox* msgBox 	= new QMessageBox();
            msgBox->setWindowTitle("From MidyAX");
            msgBox->setText("Wrong block ID in the INI file! Exiting." );
            msgBox->setStandardButtons(QMessageBox::Ok);
            msgBox->setDefaultButton(QMessageBox::No);
            msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
            msgBox->exec();
            exit(0);
        }

        strncpy( m_theMappingTable[i].effectBlockLabel, EffectBlock__names[ j ], 30);
        // Calculate the possition in the parameter arrays
        int pos =0;
        int posEffectType = AXEFX_Effect_Block_ID_to_Effect_Type_ID[ m_theMappingTable[i].effectBlockID - 100 ] - 2;
        for(int k = 0; k < posEffectType ; k++)
        {
            pos += EffectType__numOfParameters[ k ];
        }
        pos = pos + m_theMappingTable[i].effectParameterID;
        strncpy( m_theMappingTable[i].effectParameterLabel, Parameter__labels[ pos], 30);
        m_theMappingTable[i].effectParameterType = Parameter__types[ pos ];
        m_theMappingTable[i].minDispValue = Parameter__minDispValue[ pos ];
        m_theMappingTable[i].maxDispValue = Parameter__maxDispValue[ pos ];
        strncpy( m_theMappingTable[i].unit, Parameter__unitModalValues[ Parameter__unit[ pos ] ], 7);

        settings.endGroup();
    }

    fillCCtoAXE();
}


void MidyAX::applySavedConnectionSettings(void)
{
    QString  devicePortName, SVal, name;
    int nInPorts, nOutPorts;

    settings.beginGroup(QSTR_CONNECTIONS);
    if (m_midiDriver != QSTR_DRIVERNAMENET)
    {
        for(int i=0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
        {
            try
            {
                //Re-connect IN ports saved in QSettings
                SVal = QString("%1_IN").arg( m_theFMMIDIControllers[i].controllerName );
                if( settings.value(SVal).isNull() ) continue;
                devicePortName = settings.value(SVal).toString();
                if( devicePortName.isEmpty() ) continue;


                nInPorts = m_theFMMIDIControllers[i].The_MIDI_IN->getPortCount();

                for ( int j = 0; j < nInPorts; j++ )
                {
                    name = QString::fromStdString( m_theFMMIDIControllers[i].The_MIDI_IN->getPortName(j) );
                    if ( name.contains( devicePortName, Qt::CaseInsensitive) )
                    {
                        m_theFMMIDIControllers[i].The_MIDI_IN->openPort( j );
                        m_theFMMIDIControllers[i].RTMIDI_IN_Port_Name = QString::fromStdString( m_theFMMIDIControllers[i].The_MIDI_IN->getPortName( j ) );
                        m_theFMMIDIControllers[i].RTMIDI_IN_Port_Number = j;
                        dlgMidiSetup()->setCurrentInputIndexByPortOutputPortNumber( i, j );
                        m_theFMMIDIControllers[i].controllerConnected = true;
                        break;
                    }
                }

                //Re-connect OUT ports saved in QSettings
                SVal = QString("%1_OUT").arg( m_theFMMIDIControllers[i].controllerName );
                devicePortName = settings.value(SVal).toString();

                nOutPorts = m_theFMMIDIControllers[i].The_MIDI_OUT->getPortCount();

                for ( int j = 0; j < nOutPorts; j++ )
                {
                    name = QString::fromStdString( m_theFMMIDIControllers[i].The_MIDI_OUT->getPortName(j) );
                    if ( name.contains( devicePortName, Qt::CaseInsensitive) )
                    {
                        m_theFMMIDIControllers[i].The_MIDI_OUT->openPort( j );
                        m_theFMMIDIControllers[i].RTMIDI_OUT_Port_Name = QString::fromStdString( m_theFMMIDIControllers[i].The_MIDI_OUT->getPortName( j ) );
                        m_theFMMIDIControllers[i].RTMIDI_OUT_Port_Number = j;
                        dlgMidiSetup()->setCurrentOutputIndexByPortOutputPortNumber( i, j );
                        m_theFMMIDIControllers[i].controllerConnected = true;
                        break;
                    }
                }

            } catch (RtMidiError& err) {
                ui.statusBar->showMessage(QString::fromStdString(err.getMessage()));
            }
        }
    }
    settings.endGroup();
}


void MidyAX::writeSettings()
{
    int posi, totalNumberOfParam;
    settings.beginGroup(QSTR_WINDOW);
    settings.setValue(QSTR_GEOMETRY, saveGeometry());
    settings.setValue(QSTR_STATE, saveState());
    settings.endGroup();

    // Store if a MIDI controller dialog is displayed (to open on startup)
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        if( m_theFMMIDIControllers[i].dlgObject != NULL )
        {
            if( m_theFMMIDIControllers[i].dlgObject->isVisible() == true )
            {
                m_theFMMIDIControllers[i].dlgObject->storeGeom();
                settings.setValue( m_theFMMIDIControllers[i].dlgObject->QSettings_visible, true);
            }
            else settings.setValue( m_theFMMIDIControllers[i].dlgObject->QSettings_visible, false);
        }
    }

    // Write fixed MIDI channels for the fixed mapping controllers
    for(int i=1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        QString group = m_theFMMIDIControllers[i].controllerName + QString("_FIXED_CC_MIDI_CONFIG");
        settings.beginGroup(group);
            settings.setValue( "paramMIDIchannel", m_theFMMIDIControllers[i].fixedCCMIDIChannel );
            settings.setValue( "AXEFXCCMIDIchannel", m_theFMMIDIControllers[i].fixedAXEFXMIDIChannel );
            settings.setValue( "OBcontrolMIDIchannel", m_theFMMIDIControllers[i].fixedEffectBlockOBControlMIDIChannel );
            settings.setValue( "pageMIDIchannel", m_theFMMIDIControllers[i].fixedPageControlMIDIChannel );
        settings.endGroup();
    }


//    // WRITING MIDI CONNECTIONS
//    settings.beginGroup(QSTR_CONNECTIONS);
//    if (m_midiDriver != QSTR_DRIVERNAMENET) {
//        settings.setValue(QSTR_INPORT_AXEFX,  dlgMidiSetup()->selectedInputName_AXEFX());
//        settings.setValue(QSTR_INPORT_BCR2000,  dlgMidiSetup()->selectedInputName_BCR2000());
//        settings.setValue(QSTR_INPORT_OTHER1,  dlgMidiSetup()->selectedInputName_OTHER1());
//        settings.setValue(QSTR_INPORT_OTHER2,  dlgMidiSetup()->selectedInputName_OTHER2());
//        settings.setValue(QSTR_OUTPORT_AXEFX, dlgMidiSetup()->selectedOutputName_AXEFX());
//        settings.setValue(QSTR_OUTPORT_BCR2000, dlgMidiSetup()->selectedOutputName_BCR2000());
//        settings.setValue(QSTR_OUTPORT_OTHER1, dlgMidiSetup()->selectedOutputName_OTHER1());
//        settings.setValue(QSTR_OUTPORT_OTHER2, dlgMidiSetup()->selectedOutputName_OTHER2());
//    }
//    settings.endGroup();

    // Stores the global mapping
    settings.setValue( QSTR_NUM_OF_MAPPINGS,  m_numbOfMappings );
    for(int i = 0; i < m_numbOfMappings ; i++)
    {
        QString group = QSTR_MIDI_MAPPING + QString("%1").arg(i+1, 3, 10, QChar('0'));
        settings.beginGroup(group);
        settings.setValue( QSTR_CHAN_NUMB,  m_theMappingTable[i].chanNumb );
        settings.setValue( QSTR_CCID,  m_theMappingTable[i].CCID );
        settings.setValue( QSTR_EFFECT_BLOCK_ID,  m_theMappingTable[i].effectBlockID );
        settings.setValue( QSTR_EFFECT_PARAMETER_ID,  m_theMappingTable[i].effectParameterID );
        settings.endGroup();
    }

    // Stores the local mappings
    // TODO : re-activate when list on non-fixed mapping MIDI contorller is managed properly
    for(int a = 1; a < MAX_NUMBER_MIDI_CONTROLLERS ; a++)
    {
        if( m_theMIDIControllers[a].dlgObject != 0)  //&& m_theMIDIControllers[a].controllerConnected
        {
            for(int j = 0; j < m_theMIDIControllers[a].dlgObject->m_numberOfPageSelectButtons; j++)
            {
                for(int i = 0; i <   m_theMIDIControllers[a].dlgObject->m_numberOfKnobs
                                   + m_theMIDIControllers[a].dlgObject->m_numberOfSlidders
                                   + m_theMIDIControllers[a].dlgObject->m_numberOfParameterButtons;
                    i++)
                {
                    posi = i + ( (  m_theMIDIControllers[a].dlgObject->m_numberOfSlidders
                                  + m_theMIDIControllers[a].dlgObject->m_numberOfKnobs
                                  + m_theMIDIControllers[a].dlgObject->m_numberOfParameterButtons)
                               * j  );
                    QString group = m_theMIDIControllers[a].controllerName + "_MIDImapping__P" + QString("%1").arg(j+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(i+1, 2, 10, QChar('0')) ;
                    settings.beginGroup(group);

                    if( m_theMIDIControllers[a].dlgObject->m_TheMIDIMappingTable[posi].chanNumb <= 16 )                    {
                        settings.setValue( QSTR_CHAN_NUMB,  m_theMIDIControllers[a].dlgObject->m_TheMIDIMappingTable[posi].chanNumb );
                        settings.setValue( QSTR_CCID, m_theMIDIControllers[a].dlgObject-> m_TheMIDIMappingTable[posi].CCID );
                        settings.setValue( QSTR_EFFECT_BLOCK_ID, m_theMIDIControllers[a].dlgObject-> m_TheMIDIMappingTable[posi].effectBlockID );
                        settings.setValue( QSTR_EFFECT_PARAMETER_ID, m_theMIDIControllers[a].dlgObject->m_TheMIDIMappingTable[posi].effectParameterID );
                    }
                    else {
                        settings.remove("");
                    }
                    settings.endGroup();
                }
            }
        }
    }

    QString group;
    for(int h=1; h < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; h++)
    {
        MIDIControllerGenericDialogMOD1 *curDlg = m_theFMMIDIControllers[h].dlgObject;

        if( curDlg != NULL ) //TODO: Check if needed condition:  && m_theFMMIDIControllers[h].controllerConnected )
        {
            totalNumberOfParam =   curDlg->m_numberOfKnobs
                                 + curDlg->m_numberOfSlidders
                                 + curDlg->m_numberOfParameterButtons;

            for(int j = 0; j < curDlg->m_numberOfPageSelectButtons; j++)
            {
                for(int i = 0; i < totalNumberOfParam; i++)
                {
                    posi = i + ( totalNumberOfParam * j  );

                    group = m_theFMMIDIControllers[h].controllerName + "_PageMapping__P" + QString("%1").arg(j+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(i+1, 2, 10, QChar('0')) ;
                    settings.beginGroup(group);
                    if( curDlg->m_ThePagesMIDIMappingTable[posi].effectBlockID != 255 )                    {
                        settings.setValue( QSTR_EFFECT_BLOCK_ID, curDlg-> m_ThePagesMIDIMappingTable[posi].effectBlockID );
                        settings.setValue( QSTR_EFFECT_PARAMETER_ID, curDlg->m_ThePagesMIDIMappingTable[posi].effectParameterID );
                    }
                    else {
                        settings.remove("");
                    }
                    settings.endGroup();

                    group = m_theFMMIDIControllers[h].controllerName + "_PageMapping__P" + QString("%1").arg(j+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(i+1, 2, 10, QChar('0')) + "_ControlCC";
                    settings.beginGroup(group);
                    if( curDlg->m_TheCCPagesMIDIMappingTable[posi].number != 255 )                    {
                        settings.setValue( QSTR_CC_CONTROL_NUMBER, curDlg-> m_TheCCPagesMIDIMappingTable[posi].number );
                        settings.setValue( QSTR_CC_CONTROL_CC, curDlg->m_TheCCPagesMIDIMappingTable[posi].AXE_CC );
                        settings.setValue( QSTR_CC_CONTROL_NAME, curDlg->m_TheCCPagesMIDIMappingTable[posi].controlName );
                    }
                    else {
                        settings.remove("");
                    }
                    settings.endGroup();
                }
            }
        }
    }




    settings.beginGroup("Preferences");
        settings.setValue( QSTR_PREFS_EVENT_LOG_ENABLED,  m_logEnabled );
        settings.setValue( QSTR_PREFS_COLORED_SLIDERS,  g_sliderColored );
        settings.setValue( QSTR_PREFS_DISPLAY_BLOWN_UP,  g_displayBlownUp );
        settings.setValue( QSTR_PREFS_AUTO_CONNECT,  g_autoConnect );
        settings.setValue( QSTR_PREFS_AXEFX_CHAN_NUMB, m_AXEFXChanNumb);
        settings.setValue( QSTR_PREFS_MIDI_DATA_INTERVAL,  g_MIDIdataInterval );
        settings.setValue( QSTR_PREFS_MIDI_DATA_INTERVAL_NUMBER, g_MIDIdataInterval_NumberInterval);
    settings.endGroup();

    // Write currently connected devices
    QString SVal;
    settings.beginGroup(QSTR_CONNECTIONS);
    for(int i=0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        if( m_theFMMIDIControllers[i].controllerConnected == true )
        {
            SVal = QString("%1_IN").arg( m_theFMMIDIControllers[i].controllerName );
            settings.setValue( SVal, m_theFMMIDIControllers[i].RTMIDI_IN_Port_Name);

            SVal = QString("%1_OUT").arg( m_theFMMIDIControllers[i].controllerName );
            settings.setValue( SVal, m_theFMMIDIControllers[i].RTMIDI_OUT_Port_Name);
        }
        else {
            SVal = QString("%1_IN").arg( m_theFMMIDIControllers[i].controllerName );
            settings.setValue( SVal, "");

            SVal = QString("%1_OUT").arg( m_theFMMIDIControllers[i].controllerName );
            settings.setValue( SVal, "");
        }
    }
    settings.endGroup();
}

void MidyAX::closeEvent( QCloseEvent *event )
{
    //qDebug() << "closeEvent:" << event->type();

    if (m_initialized)  writeSettings();
    event->accept();
}

void MidyAX::on_pbSyncWithAXEFX_clicked()
{
    getMidiMappingParamValues( false );
}

void MidyAX::on_rbnActivateLog_toggled(bool checked)
{
    m_logEnabled = checked;
}

void MidyAX::on_actionEXIT_triggered()
{
    close();
}

void MidyAX::updateDisplayedConnectState(void)
{
    QLabel *curLabel;
    QString LName;
    for(int i=0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++ )
    {
        LName = "connectState_" +  MIDI_Known_Controllers_Interface_Name[i];
        curLabel = this->findChild<QLabel *>( LName );
        if( curLabel != NULL )
        {
            if( m_theFMMIDIControllers[i].controllerConnected == true )
            {
                curLabel->setText("ON");
                curLabel->setStyleSheet("QLabel { /*background-color : #d2d2d2;*/ color : black; }");;
            }
            else {
                curLabel->setText("OFF");
                curLabel->setStyleSheet("QLabel { /*background-color : #d2d2d2;*/ color : red; }");;
            }
        }
    }
}


void MidyAX::on_pbClear_clicked()
{
    ui.logMIDI->clear();
}
