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

#ifndef TYPES_H
#define TYPES_H

#include "RtMidi.h"

class MIDIControllerGenericDialog;
class MIDIControllerGenericDialogMOD1;


#define MAX_NUMBER_MIDI_CONTROLLERS 0
#define MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS 10

typedef void (*midiCallback)( double, std::vector< unsigned char > *, void * );

struct MIDI_CONTROLLER
{
    QString controllerName;
    QString The_MIDI_IN_Name;
    QString The_MIDI_OUT_Name;
    int RTMIDI_OUT_Port_Number;
    int RTMIDI_IN_Port_Number;
    RtMidiIn * The_MIDI_IN;
    RtMidiOut * The_MIDI_OUT;
    MIDIControllerGenericDialog * dlgObject;
    midiCallback MidiCallbackFunctions;
    bool controllerConnected;
};

struct FIXED_CC_MIDI_CONTROLLER
{
    QString controllerName;
    QString The_MIDI_IN_Name;
    QString The_MIDI_OUT_Name;
    int RTMIDI_OUT_Port_Number;
    int RTMIDI_IN_Port_Number;
    QString RTMIDI_OUT_Port_Name;
    QString RTMIDI_IN_Port_Name;
    RtMidiIn * The_MIDI_IN;
    RtMidiOut * The_MIDI_OUT;
    MIDIControllerGenericDialogMOD1 * dlgObject;
    midiCallback MidiCallbackFunctions;
    bool controllerConnected;

    quint8 fixedCCMIDIChannel;
    quint8 fixedPageControlMIDIChannel;
    quint8 fixedEffectBlockOBControlMIDIChannel;
    quint8 fixedAXEFXMIDIChannel;
};

enum DIRECTION {
    IN,
    OUT
};

enum MIDI_CONTROLLERS {
    AXEFX_MC,
    BCR2000_MC,
    BCF2000_MC,
    XTOUCHMINI_MC,
    BEATSTEP_MC,
    GUITARWING_MC,
    QUNEO_MC,
    FCB1010_MC,
    OTHER1_MC,
    OTHER2_MC
};

enum MIDI_MAPPINGS {
    FIXED_CC_MAPPING,
    GLOBAL_MAPPING
};


struct CCpageMappingTable {
    int number;
    quint8 AXE_CC;
    QString controlName;
    quint8 MIDIValue;
    int type;
};


struct pageMappingTable {
    unsigned char effectBlockID;
    char effectBlockLabel[30];
    unsigned char effectParameterID;
    char effectParameterLabel[30];
    char unit[8];

    unsigned char MIDIValue;
    int paramValue;

    double paramDispValue;
    int effectParameterType;
    int minDispValue;
    int maxDispValue;
};

struct mappingTable {
    int chanNumb;
    unsigned char CCID;
    unsigned char effectBlockID;
    char effectBlockLabel[30];
    unsigned char effectParameterID;
    char effectParameterLabel[30];
    int effectParameterType;
    char unit[8];
    int paramValue;
    unsigned char MIDIValue;
    double paramDispValue;
    int minDispValue;
    int maxDispValue;

    mappingTable& operator=( const mappingTable& a )
    {
        chanNumb = a. chanNumb;
        CCID = a.CCID;
        effectBlockID = a.effectBlockID;
        effectParameterID = a.effectParameterID;
        strncpy( effectBlockLabel, a.effectBlockLabel, 30);
        strncpy( effectParameterLabel, a.effectParameterLabel, 30);
        effectParameterType = a.effectParameterType;
        strncpy( unit, a.unit, 8);
        paramValue = a.paramValue;
        MIDIValue = a.MIDIValue;
        paramDispValue = a.paramDispValue;
        minDispValue = a.minDispValue;
        maxDispValue = a.maxDispValue;

        return *this;
    }

    bool operator==( const mappingTable& a ) const
    {
        return( chanNumb == a. chanNumb  &&  CCID == a.CCID  &&  effectBlockID == a.effectBlockID  &&  effectParameterID == a.effectParameterID);
    }

    void setToZero( void )
    {
        chanNumb = 255;
        CCID = 255;
        effectBlockID = 255;
        effectParameterID = 255;
        strncpy( effectBlockLabel, "", 30);
        strncpy( effectParameterLabel, "", 30);
        effectParameterType = 0;
        strncpy( unit, "", 8);
        paramValue = 0;
        MIDIValue = 0;
        paramDispValue = 0;
        minDispValue = 0;
        maxDispValue = 0;
    }
};


#endif // TYPES_H
