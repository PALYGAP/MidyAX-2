/*
MidyAX
*/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <QApplication>
#include <QString>

/* Don't translate any string defined in this header */

#define LITERAL(s) #s
#define STRINGIFY(s) LITERAL(s)
const QString PGM_VERSION(STRINGIFY(VERSION));

const QString BLD_DATE(__DATE__);
const QString BLD_TIME(__TIME__);
#if defined(Q_CC_GNU) || defined(Q_CC_GCCE)
const QString CMP_VERSION(__VERSION__);
#elif defined(Q_CC_MSVC)
const QString CMP_VERSION(QString::number(_MSC_VER/100.0,'g',2));
#else
const QString CMP_VERSION(QString());
#endif

const QString QSTR_ORGNAME("LeafONICs");
const QString QSTR_APPNAME("MidyAX by LeafONICs");
const QString QSTR_DOMAIN("www.LeafONICs.com");
const QString QSTR_MIDYAXPX("MidyAX_");
const QString QSTR_QTPX("qt_");

const QString QSTR_WINDOW("Window");
const QString QSTR_GEOMETRY("Geometry");
const QString QSTR_STATE("State");

const QString QSTR_MIDYAX("MIDYAX");
const QString QSTR_NUM_OF_MAPPINGS("NumOfMappings");
const QString QSTR_MIDI_MAPPING("Global_MidiMapping");

// MIDI Connections
const QString QSTR_CONNECTIONS("MIDI_Connections");
const QString QSTR_MIDYAX_VIRTUAL_INPUT("MIDYAX2_IN");
const QString QSTR_MIDYAX_VIRTUAL_OUTPUT("MIDYAX2_OUT");

// For each mapping
const QString QSTR_CHAN_NUMB("MidiChannel" );
const QString QSTR_CCID("CCID");
const QString QSTR_EFFECT_BLOCK_ID("EffectBlockID");
const QString QSTR_EFFECT_PARAMETER_ID("EffectParameterID");
const QString QSTR_CC_CONTROL_NUMBER("ControlNumber");
const QString QSTR_CC_CONTROL_CC("ControlCC");
const QString QSTR_CC_CONTROL_NAME("ControlNAME");

//Preferences
const QString QSTR_PREFS_EVENT_LOG_ENABLED("EventLogEnable");
const QString QSTR_PREFS_COLORED_SLIDERS("ColoredSliders");
const QString QSTR_PREFS_DISPLAY_BLOWN_UP("DisplayBlownUp");
const QString QSTR_PREFS_AUTO_CONNECT("AutoConnect");
const QString QSTR_PREFS_AXEFX_CHAN_NUMB("AXEFXChanNumb");
const QString QSTR_PREFS_MIDI_DATA_INTERVAL("MIDIDataInterval");
const QString QSTR_PREFS_MIDI_DATA_INTERVAL_NUMBER("MIDIDataInterval_Number");




const QString QSTR_MIDIDRIVER("MIDIDriver");
const QString QSTR_DRIVERNAMEALSA("ALSA Sequencer");
const QString QSTR_DRIVERNAMEJACK("Jack MIDI");
const QString QSTR_DRIVERNAMEMACOSX("Mac OSX CoreMIDI");
const QString QSTR_DRIVERNAMEIRIX("SGI Irix MD");
const QString QSTR_DRIVERNAMEWINMM("Windows MM");
const QString QSTR_DRIVERNAMENET("Network UDP (IpMIDI)");
const QString QSTR_MULTICAST_ADDRESS("225.0.0.37");
const QString QSTR_PALETTEPREFIX("Palette_");
const QString QSTR_CURRENTPALETTE("CurrentPalette");
const QString QSTR_SHOWCOLORSCALE("ShowColorScale");

#if defined(Q_OS_LINUX)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEALSA);
#elif defined(Q_OS_MAC)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEMACOSX);
#elif defined(Q_OS_IRIX)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEIRIX);
#elif defined(Q_OS_WIN)
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMEWINMM);
#else
const QString QSTR_DRIVERDEFAULT(QSTR_DRIVERNAMENET);
#endif


#if defined(Q_WS_MAC) && defined(QT_MAC_USE_COCOA)
#error "This program requires Qt built with the Carbon framework. Sorry."
#endif

#endif /*CONSTANTS_H_*/
