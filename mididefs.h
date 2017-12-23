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

#ifndef MIDIDEFS_H
#define MIDIDEFS_H

#define MASK_CHANNEL      0x0f
#define MASK_STATUS       0xf0
#define MASK_SAFETY       0x7f

#define CTL_MSB              0
#define CTL_LSB           0x20
#define CTL_ALL_SOUND_OFF 0x78
#define CTL_RESET_ALL_CTL 0x79
#define CTL_ALL_NOTES_OFF 0x7B

#define STATUS_NOTEOFF    0x80
#define STATUS_NOTEON     0x90
#define STATUS_POLYAFT    0xA0
#define STATUS_CTLCHG     0xB0
#define STATUS_PROGRAM    0xC0
#define STATUS_CHANAFT    0xD0
#define STATUS_BENDER     0xE0
#define STATUS_SYSEX      0xF0
#define LOG_SYSEX         0xF8

#define BLOWNUP_START     0xB1
#define BLOWNUP_STOP      0xB2
#define MIDI_CONT_SET_VAL 0x01

#define BENDER_MIN       -8192
#define BENDER_MAX        8191
#define BENDER_MID      0x2000

#define CALC_LSB(x) (x % 0x80)
#define CALC_MSB(x) (x / 0x80)

#define CTL_VOLUME           7
#define CTL_PAN             10
#define CTL_EXPRESSION      11

#endif /* MIDIDEFS_H */
