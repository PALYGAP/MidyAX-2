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

#ifndef EVENTS_H
#define EVENTS_H

#include "mididefs.h"
#include <QEvent>

const QEvent::Type ControlChangeEventType = QEvent::Type(   QEvent::registerEventType( QEvent::User + STATUS_CTLCHG ) );
const QEvent::Type ProgramChangeEventType = QEvent::Type(   QEvent::registerEventType( QEvent::User + STATUS_PROGRAM ) );
const QEvent::Type ChannelKeyPressEventType = QEvent::Type(    QEvent::registerEventType( QEvent::User + STATUS_CHANAFT ) );
const QEvent::Type PitchWheelEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + STATUS_BENDER) );
const QEvent::Type SysExEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + STATUS_SYSEX) );
const QEvent::Type LogSentSysExEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + LOG_SYSEX) );

const QEvent::Type MIDIContDialSetValEventType = QEvent::Type( QEvent::registerEventType( QEvent::User + 1/*MIDI_CONT_SET_VAL*/) );
const QEvent::Type MIDIContDialPageChangeEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + 2) );
const QEvent::Type AXEFXMIDIChannelEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + 3) );
const QEvent::Type IHMSetValEventType = QEvent::Type( QEvent::registerEventType( QEvent::User + 40 ) );

const QEvent::Type BlownUpStartEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + BLOWNUP_START) );
const QEvent::Type BlownUpStopEventType = QEvent::Type(     QEvent::registerEventType( QEvent::User + BLOWNUP_STOP) );

class AXEFXMIDIChannelEvent : public QEvent
{
public:
    AXEFXMIDIChannelEvent( quint8 AXEFX_Channel) : QEvent(AXEFXMIDIChannelEventType), m_AXEFXChannel(AXEFX_Channel) { }
    int getAXEFXChannel() const { return m_AXEFXChannel; }
protected:
    quint8 m_AXEFXChannel;
};

class MIDIContDialSetValEvent : public QEvent
{
public:
    MIDIContDialSetValEvent( int MIDIContNumb, int pageNumb,  int elemNumb, double dispValue )
         : QEvent(MIDIContDialSetValEventType), m_MIDIContNumb(MIDIContNumb), m_pageNumb( pageNumb), m_elemNumb(elemNumb), m_dispValue(dispValue)  { }
    int getMIDIContNumb() const { return m_MIDIContNumb; }
    int getPageNumb() const { return m_pageNumb; }
    int getElemNumb() const { return m_elemNumb; }
    double getDispValue() const { return m_dispValue; }
protected:
    int m_MIDIContNumb;
    int m_pageNumb;
    int m_elemNumb;
    double m_dispValue;
};


class IHMSetValEvent : public QEvent
{
public:
    IHMSetValEvent(  int pageNumb,  int elemNumb, double dispValue )
         : QEvent(IHMSetValEventType), m_pageNumb( pageNumb), m_elemNumb(elemNumb), m_dispValue(dispValue)  { }
    int getPageNumb() const { return m_pageNumb; }
    int getElemNumb() const { return m_elemNumb; }
    double getDispValue() const { return m_dispValue; }
protected:
    int m_pageNumb;
    int m_elemNumb;
    double m_dispValue;
};


class BlownUpStartEvent : public QEvent
{
public:
    BlownUpStartEvent() : QEvent(BlownUpStartEventType), m_state(true) { }
protected:
    bool m_state;
};

class BlownUpStopEvent : public QEvent
{
public:
    BlownUpStopEvent() : QEvent(BlownUpStopEventType), m_state(false) { }
protected:
    bool m_state;
};

class MIDIContDialPageChangeEvent : public QEvent
{
public:
    MIDIContDialPageChangeEvent( int MIDIContNumb, int receivedCC,  int receivedVal )
         : QEvent(MIDIContDialPageChangeEventType), m_MIDIContNumb(MIDIContNumb), m_receivedCC( receivedCC), m_receivedVal(receivedVal)  { }
    int getMIDIContNumb() const { return m_MIDIContNumb; }
    int getReceivedCC() const { return m_receivedCC; }
    int getReceivedVal() const { return m_receivedVal; }
protected:
    int m_MIDIContNumb;
    int m_receivedCC;
    int m_receivedVal;
};

class ControlChangeEvent : public QEvent
{
public:
    ControlChangeEvent(int device, unsigned char channel,unsigned char ctl, unsigned char value, unsigned char direction)
        : QEvent(ControlChangeEventType), m_device(device), m_channel(channel), m_ctl(ctl), m_value(value), m_direction(direction) { }
    int getDevice() const { return m_device; }
    unsigned char getChannel() const { return m_channel; }
    unsigned char getController() const { return m_ctl; }
    unsigned char getValue() const { return m_value; }
    unsigned char getDirection() const { return m_direction; }
private:
    int m_device;
    unsigned char m_channel;
    unsigned char m_ctl;
    unsigned char m_value;
    unsigned char m_direction;
};

class ValueEvent : public QEvent
{
public:
    ValueEvent(int value, QEvent::Type type)
        : QEvent(type), m_value(value) { }
    int getValue() const { return m_value; }
private:
    int m_value;
};

class ProgramChangeEvent : public ValueEvent
{
public:
    ProgramChangeEvent(unsigned char value)
        : ValueEvent(value, ProgramChangeEventType) { }
};

class ChannelKeyPressEvent : public ValueEvent
{
public:
    ChannelKeyPressEvent(unsigned char value)
        : ValueEvent(value, ChannelKeyPressEventType) { }
};

class PitchWheelEvent : public ValueEvent
{
public:
    PitchWheelEvent(int value)
        : ValueEvent(value, PitchWheelEventType) { }
};

class SysExEvent : public QEvent
{
    // Event used to process SYSEX message received from MIDI device
public:
    SysExEvent(int device, std::vector<unsigned char> sysex_vector)
        : QEvent(SysExEventType), m_device(device), m_sysex_vector(sysex_vector) { }
    int getDevice() { return m_device; }
    std::vector<unsigned char> * getSysEx()  { return &m_sysex_vector; }
private :
    int m_device;
    std::vector<unsigned char> m_sysex_vector;
};

class LogSentSysExEvent : public QEvent
{
    // Event used to log SYSEX message send to MIDI device
public:
    LogSentSysExEvent(int device, std::vector<unsigned char> sysex_vector)
        : QEvent(LogSentSysExEventType), m_device(device), m_sysex_vector(sysex_vector) { }
    int getDevice() { return m_device; }
    std::vector<unsigned char> * getSysEx()  { return &m_sysex_vector; }
private :
    int m_device;
    std::vector<unsigned char> m_sysex_vector;
};



#endif /* EVENTS_H */
