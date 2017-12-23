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

#ifndef AXEFXPARAM_H_
#define AXEFXPARAM_H_

#include "axefx.h"

AXEFX_EffectType TheEffectTypes[ AXEFX_NUMBER_EFFECT_TYPE ];

// Defines all the AXE_effect Block structure
AXE_effect The_AXE_Effects [AXEFX_NUMBER_EFFECTS_BLOCK] ={
{ 0x64, 	43, 	0 },
{ 0x65, 	44, 	0 },
{ 0x66, 	62, 	0 },
{ 0x67, 	63, 	0 },
{ 0x68, 	71, 	0 },
{ 0x69, 	72, 	0 },
{ 0x6A, 	37, 	100 },
{ 0x6B, 	38, 	101 },
{ 0x6C, 	39, 	102 },
{ 0x6D, 	40, 	103 },
{ 0x6E, 	83, 	116 },
{ 0x6F, 	84, 	117 },
{ 0x70, 	47, 	106 },
{ 0x71, 	48, 	107 },
{ 0x72, 	69, 	0 },
{ 0x73, 	70, 	0 },
{ 0x74, 	41, 	104 },
{ 0x75, 	42, 	105 },
{ 0x76, 	56, 	110 },
{ 0x77, 	57, 	111 },
{ 0x78, 	86, 	0 },
{ 0x79, 	87, 	0 },
{ 0x7A, 	75, 	112 },
{ 0x7B, 	76, 	113 },
{ 0x7C, 	97, 	118 },
{ 0x7D, 	98, 	119 },
{ 0x7E, 	58, 	0 },
{ 0x7F, 	93, 	0 },
{ 0x80, 	90, 	0 },
{ 0x81, 	91, 	0 },
{ 0x82, 	77, 	114 },
{ 0x83, 	52, 	0 },
{ 0x84, 	53, 	0 },
{ 0x85, 	49, 	108 },
{ 0x86, 	50, 	109 },
{ 0x87, 	51, 	0 },
{ 0x88, 	59, 	0 },
{ 0x89, 	0, 	0 },
{ 0x8A, 	0, 	0 },
{ 0x8B, 	0, 	0 },
{ 0x8C, 	0, 	0 },
{ 0x8D, 	0, 	0 },
{ 0x8E, 	0, 	0 },
{ 0x8F, 	0, 	0 },
{ 0x90, 	88, 	0 },
{ 0x91, 	89, 	0 },
{ 0x92, 	92, 	0 },
{ 0x93, 	66, 	0 },
{ 0x94, 	45, 	0 },
{ 0x95, 	46, 	0 },
{ 0x96, 	60, 	0 },
{ 0x97, 	61, 	0 },
{ 0x98, 	85, 	0 },
{ 0x99, 	78, 	115 },
{ 0x9A, 	67, 	0 },
{ 0x9B, 	68, 	0 },
{ 0x9C, 	79, 	0 },
{ 0x9D, 	80, 	0 },
{ 0x9E, 	81, 	0 },
{ 0x9F, 	82, 	0 },
{ 0xA0, 	64, 	0 },
{ 0xA1, 	65, 	0 },
{ 0xA2, 	73, 	0 },
{ 0xA3, 	74, 	0 },
{ 0xA4, 	54, 	0 },
{ 0xA5, 	55, 	0 },
{ 0xA6, 	94, 	0 },
{ 0xA7, 	95, 	0 },
{ 0xA8, 	96, 	0 },
{ 0xA9, 	0, 	0 },
{ 0xAA, 	99, 	0 }
};

// Type of each effect block
//int AXEFX_Effect_Block_ID_to_Effect_Type_ID_OLD[ AXEFX_NUMBER_EFFECTS_BLOCK ] = {
//  2,2,3,3,3,3,4,4,4,4,
//  5,5,6,6,7,7,8,8,9,9,
//  10,10,11,11,12,12,13,13,14,14,
//  15,16,16,17,17,18,18,18,18,19,
//  19,20,21,22,22,23,24,25,25,26,
//  27,28,28,29,29,30,31,31,32,32,
//  33,33,34,34,34,34,35,36,37,38, 39
//  };

int AXEFX_Effect_Block_ID_to_Effect_Type_ID[ AXEFX_NUMBER_EFFECTS_BLOCK ] = {
  2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
  7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
  12, 12, 13, 13, 14, 14, 15, 34, 16, 16,
  17, 18, 18, 19, 19, 20, 21, 22, 22, 35,
  36, 37, 23, 24, 25, 25, 26, 27, 28, 28,
  29, 29, 30, 17, 31, 31, 32, 32, 33, 33,
   3,  3,  4,  4, 18, 18, 34, 34, 34, 38, 39
};

// Number of block per effect type
int AXEFX_Effect_Type_Number[ AXEFX_NUMBER_EFFECT_TYPE ] = {
  0,0,2,4,4,2,2,2,2,2,
  2,2,2,2,2,1,2,2,4,2,
  1,1,2,1,1,2,1,1,2,2,
  1,2,2,2,4,1,1,1,1
  };


///////////////
// VARIABLES //
///////////////

unsigned char AXEFX_Firmware_Version,
              AXEFX_Model,
              MFC101_Firmware_Version,
              AXEFX_MIDI_Channel = 12;   // By default the AXE_FX channel is set to 12



//////////////////////
// LOOPER SPECIFICS //
//////////////////////

// CONTANTS //
unsigned char AXEFX_LOOPER_RECORD_CC = 28,
              AXEFX_LOOPER_PLAY_CC = 29,
              AXEFX_LOOPER_ONCE_CC = 30,
              AXEFX_LOOPER_DUB_CC = 31,
              AXEFX_LOOPER_REVERSE_CC = 32,
              AXEFX_LOOPER_BYPASS_CC = 33,
              AXEFX_LOOPER_HALF_CC = 120,
              AXEFX_LOOPER_UNDO_CC = 121,
              AXEFX_LOOPER_METRO_CC = 122;


// VARIABLES //
unsigned char AXEFX_LOOPER__STATE,        // Global LOOPER STATE - ON / OFF
              AXEFX_LOOPER_STATE_RECORD,
              AXEFX_LOOPER_STATE_PLAY,
              AXEFX_LOOPER_STATE_ONCE,
              AXEFX_LOOPER_STATE_DUB,
              AXEFX_LOOPER_STATE_REVERSE,
              AXEFX_LOOPER_STATE_UNDO,
              AXEFX_LOOPER_STATE_HALF,
              AXEFX_LOOPER_STATE_METRO;


  // LOOPER variables
  bool LOOPER_STATE_RECORD,
          LOOPER_STATE_PLAY,
          LOOPER_STATE_ONCE,
          LOOPER_STATE_DUB,
          LOOPER_STATE_REVERSE,
          LOOPER_STATE_UNDO,
          LOOPER_STATE_HALF,
          LOOPER_STATE_METRO,
          LOOPER_STATE = false;


















const int MaxNumberOfControlPages = 32;
const int MaxNumberOfParameters = 48;
const int NumOfEffectTypes = 38;
//const int TotalNumOfParameters = 1100;
const int TotalNumOfParameters = 1122;
const int NumOfEffectBlocks = 71;
const int NumOfModalList = 84;


///////////////////////////////////////////////////
////////////////  EFFECT BLOCKS  //////////////////
///////////////////////////////////////////////////

unsigned char EffectBlock__ID[AXEFX_NUMBER_EFFECTS_BLOCK] = { 106, 107, 108, 109, 116, 117, 100, 101, 148, 149, 112, 113, 133, 134, 136, 135, 142, 143, 131, 132, 164, 165, 118, 119, 126, 150, 151, 102, 103, 160, 161, 169, 147, 137, 138, 154, 155, 114, 115, 128, 129, 104, 105, 162, 163, 122, 123, 130, 153, 156, 157, 158, 159, 110, 111, 152, 120, 121, 144, 145, 170, 146, 127, 166, 167, 168, 124, 125, 139, 140, 141};

char EffectBlock__0__name[] = "Amp 1";
char EffectBlock__1__name[] = "Amp 2";
char EffectBlock__2__name[] = "Cabinet 1";
char EffectBlock__3__name[] = "Cabinet 2";
char EffectBlock__4__name[] = "Chorus 1";
char EffectBlock__5__name[] = "Chorus 2";
char EffectBlock__6__name[] = "Compressor 1";
char EffectBlock__7__name[] = "Compressor 2";
char EffectBlock__8__name[] = "Crossover 1";
char EffectBlock__9__name[] = "Crossover 2";
char EffectBlock__10__name[] = "Delay 1";
char EffectBlock__11__name[] = "Delay 2";
char EffectBlock__12__name[] = "Drive 1";
char EffectBlock__13__name[] = "Drive 2";
char EffectBlock__14__name[] = "Effects Loop";
char EffectBlock__15__name[] = "Enhancer";
char EffectBlock__16__name[] = "Feedback Send";
char EffectBlock__17__name[] = "Feedback Return";
char EffectBlock__18__name[] = "Filter 1";
char EffectBlock__19__name[] = "Filter 2";
char EffectBlock__20__name[] = "Filter 3";
char EffectBlock__21__name[] = "Filter 4";
char EffectBlock__22__name[] = "Flanger 1";
char EffectBlock__23__name[] = "Flanger 2";
char EffectBlock__24__name[] = "Formant";
char EffectBlock__25__name[] = "Gate/Expander 1";
char EffectBlock__26__name[] = "Gate/Expander 2";
char EffectBlock__27__name[] = "GraphicEQ 1";
char EffectBlock__28__name[] = "GraphicEQ 2";
char EffectBlock__29__name[] = "GraphicEQ 3";
char EffectBlock__30__name[] = "GraphicEQ 4";
char EffectBlock__31__name[] = "Looper";
char EffectBlock__32__name[] = "Megatap Delay";
char EffectBlock__33__name[] = "Mixer 1";
char EffectBlock__34__name[] = "Mixer 2";
char EffectBlock__35__name[] = "Multiband Comp 1";
char EffectBlock__36__name[] = "Multiband Comp 2";
char EffectBlock__37__name[] = "Multidelay 1";
char EffectBlock__38__name[] = "Multidelay 2";
char EffectBlock__39__name[] = "Panner/Tremolo 1";
char EffectBlock__40__name[] = "Panner/Tremolo 2";
char EffectBlock__41__name[] = "Parametric EQ 1";
char EffectBlock__42__name[] = "Parametric EQ 2";
char EffectBlock__43__name[] = "Parametric EQ 3";
char EffectBlock__44__name[] = "Parametric EQ 4";
char EffectBlock__45__name[] = "Phaser 1";
char EffectBlock__46__name[] = "Phaser 2";
char EffectBlock__47__name[] = "Pitch 1";
char EffectBlock__48__name[] = "Pitch 2";
char EffectBlock__49__name[] = "Quad Chorus 1";
char EffectBlock__50__name[] = "Quad Chorus 2";
char EffectBlock__51__name[] = "Resonator 1";
char EffectBlock__52__name[] = "Resonator 2";
char EffectBlock__53__name[] = "Reverb 1";
char EffectBlock__54__name[] = "Reverb 2";
char EffectBlock__55__name[] = "RingMod";
char EffectBlock__56__name[] = "Rotary 1";
char EffectBlock__57__name[] = "Rotary 2";
char EffectBlock__58__name[] = "Synth 1";
char EffectBlock__59__name[] = "Synth 2";
char EffectBlock__60__name[] = "Tone Match";
char EffectBlock__61__name[] = "Vocoder";
char EffectBlock__62__name[] = "Vol/Pan 1";
char EffectBlock__63__name[] = "Vol/Pan 2";
char EffectBlock__64__name[] = "Vol/Pan 3";
char EffectBlock__65__name[] = "Vol/Pan 4";
char EffectBlock__66__name[] = "Wahwah 1";
char EffectBlock__67__name[] = "Wahwah 2";
char EffectBlock__68__name[] = "NoiseGate";
char EffectBlock__69__name[] = "Output";
char EffectBlock__70__name[] = "Controllers";


char *EffectBlock__names[AXEFX_NUMBER_EFFECTS_BLOCK] = { EffectBlock__0__name, EffectBlock__1__name, EffectBlock__2__name, EffectBlock__3__name, EffectBlock__4__name, EffectBlock__5__name, EffectBlock__6__name, EffectBlock__7__name, EffectBlock__8__name, EffectBlock__9__name, EffectBlock__10__name, EffectBlock__11__name, EffectBlock__12__name, EffectBlock__13__name, EffectBlock__14__name, EffectBlock__15__name, EffectBlock__16__name, EffectBlock__17__name, EffectBlock__18__name, EffectBlock__19__name, EffectBlock__20__name, EffectBlock__21__name, EffectBlock__22__name, EffectBlock__23__name, EffectBlock__24__name, EffectBlock__25__name, EffectBlock__26__name, EffectBlock__27__name, EffectBlock__28__name, EffectBlock__29__name, EffectBlock__30__name, EffectBlock__31__name, EffectBlock__32__name, EffectBlock__33__name, EffectBlock__34__name, EffectBlock__35__name, EffectBlock__36__name, EffectBlock__37__name, EffectBlock__38__name, EffectBlock__39__name, EffectBlock__40__name, EffectBlock__41__name, EffectBlock__42__name, EffectBlock__43__name, EffectBlock__44__name, EffectBlock__45__name, EffectBlock__46__name, EffectBlock__47__name, EffectBlock__48__name, EffectBlock__49__name, EffectBlock__50__name, EffectBlock__51__name, EffectBlock__52__name, EffectBlock__53__name, EffectBlock__54__name, EffectBlock__55__name, EffectBlock__56__name, EffectBlock__57__name, EffectBlock__58__name, EffectBlock__59__name, EffectBlock__60__name, EffectBlock__61__name, EffectBlock__62__name, EffectBlock__63__name, EffectBlock__64__name, EffectBlock__65__name, EffectBlock__66__name, EffectBlock__67__name, EffectBlock__68__name, EffectBlock__69__name, EffectBlock__70__name};

int EffectBlock__effectTypeID[AXEFX_NUMBER_EFFECTS_BLOCK] = { 5, 5, 6, 6, 10, 10, 2, 2, 28, 28, 8, 8, 19, 19, 21, 20, 23, 24, 18, 18, 18, 18, 11, 11, 15, 29, 29, 3, 3, 3, 3, 38, 27, 22, 22, 31, 31, 9, 9, 16, 16, 4, 4, 4, 4, 13, 13, 17, 17, 32, 32, 33, 33, 7, 7, 30, 12, 12, 25, 25, 39, 26, 34, 34, 34, 34, 14, 14, 35, 36, 37};

unsigned char EffectBlock__ONByPass_CC[AXEFX_NUMBER_EFFECTS_BLOCK] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 59, 51, 0, 0, 52, 53, 54, 55, 56, 57, 58, 60, 61, 62, 63, 64, 65, 0, 66, 0, 0, 67, 68, 69, 70, 90, 91, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 99, 92, 93, 94, 95, 96, 97, 98, 0, 0, 0};

unsigned char EffectBlock__XY_CC[AXEFX_NUMBER_EFFECTS_BLOCK] = { 100, 101, 102, 103, 104, 105, 0, 0, 0, 0, 106, 107, 108, 109, 0, 0, 0, 0, 0, 0, 0, 0, 110, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 112, 113, 114, 115, 0, 0, 0, 0, 116, 117, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 119, 0, 0, 0};



///////////////////////////////////////////////////
////////////////  EFFECT TYPES   //////////////////
///////////////////////////////////////////////////

int EffectType__ID[AXEFX_NUMBER_EFFECT_TYPE-1] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};

char EffectType__2__name[] = "Compressor";
char EffectType__3__name[] = "GraphicEQ";
char EffectType__4__name[] = "ParametricEQ";
char EffectType__5__name[] = "Amp";
char EffectType__6__name[] = "Cab";
char EffectType__7__name[] = "Reverb";
char EffectType__8__name[] = "Delay";
char EffectType__9__name[] = "MultiDelay";
char EffectType__10__name[] = "Chorus";
char EffectType__11__name[] = "Flanger";
char EffectType__12__name[] = "Rotary";
char EffectType__13__name[] = "Phaser";
char EffectType__14__name[] = "Wah";
char EffectType__15__name[] = "Formant";
char EffectType__16__name[] = "PanTrem";
char EffectType__17__name[] = "Pitch";
char EffectType__18__name[] = "Filter";
char EffectType__19__name[] = "Drive";
char EffectType__20__name[] = "Enhancer";
char EffectType__21__name[] = "EffectsLoop";
char EffectType__22__name[] = "Mixer";
char EffectType__23__name[] = "FeedbackSend";
char EffectType__24__name[] = "FeedbackReturn";
char EffectType__25__name[] = "Synth";
char EffectType__26__name[] = "Vocoder";
char EffectType__27__name[] = "MegaTap";
char EffectType__28__name[] = "Crossover";
char EffectType__29__name[] = "GateExpander";
char EffectType__30__name[] = "RingMod";
char EffectType__31__name[] = "MultibandComp";
char EffectType__32__name[] = "QuadChorus";
char EffectType__33__name[] = "Resonator";
char EffectType__34__name[] = "VolPan";
char EffectType__35__name[] = "NoiseGate";
char EffectType__36__name[] = "Output";
char EffectType__37__name[] = "Controllers";
char EffectType__38__name[] = "Looper";
char EffectType__39__name[] = "Tone";


char *EffectType__names[AXEFX_NUMBER_EFFECT_TYPE-1] = { EffectType__2__name, EffectType__3__name, EffectType__4__name, EffectType__5__name, EffectType__6__name, EffectType__7__name, EffectType__8__name, EffectType__9__name, EffectType__10__name, EffectType__11__name, EffectType__12__name, EffectType__13__name, EffectType__14__name, EffectType__15__name, EffectType__16__name, EffectType__17__name, EffectType__18__name, EffectType__19__name, EffectType__20__name, EffectType__21__name, EffectType__22__name, EffectType__23__name, EffectType__24__name, EffectType__25__name, EffectType__26__name, EffectType__27__name, EffectType__28__name, EffectType__29__name, EffectType__30__name, EffectType__31__name, EffectType__32__name, EffectType__33__name, EffectType__34__name, EffectType__35__name, EffectType__36__name, EffectType__37__name, EffectType__38__name, EffectType__39__name};

int EffectType__subTypeParamID[AXEFX_NUMBER_EFFECT_TYPE-1] = { 12, -1, -1, 0, 12, 0, 0, 35, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, 8, -1};

int EffectType__onBypassParamID[AXEFX_NUMBER_EFFECT_TYPE-1] = { 9, 18, 23, 28, 13, 22, 22, 34, 15, 16, 11, 16, 12, 11, 14, 29, 8, 7, 5, 12, -1, -1, 5, 28, 49, 16, 14, 12, 9, 27, 44, 38, 3, -1, 19, -1, 4, 9};

//int EffectType__numOfParameters[AXEFX_NUMBER_EFFECT_TYPE-1] = { 18, 19, 24, 91, 29, 35, 70, 117, 23, 23, 18, 20, 13, 12, 15, 85, 14, 20, 11, 20, 10, 2, 6, 40, 50, 17, 15, 13, 10, 28, 46, 40, 9, 5, 20, 78, 13, 21};
int EffectType__numOfParameters[AXEFX_NUMBER_EFFECT_TYPE-1] = { 18, 19, 24, /*AMP*/ 113, 29, 35, 70, 117, 23, 23, 18, 20, 13, 12, 15, 85, 14, 20, 11, 20, 10, 2, 6, 40, 50, 17, 15, 13, 10, 28, 46, 40, 9, 5, 20, 78, 13, 21};

////////////////  PARAMETERS    //////////////////

//int Parameter__ID[1100] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
int Parameter__ID[TotalNumOfParameters] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,

//AMP 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112,

0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
0, 1,
0, 1, 2, 3, 4, 5,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
0, 1, 2, 3, 4, 5, 6, 7, 8,
0, 1, 2, 3, 4,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

char EffectType__2__Parameter__0__name[] = "COMP_THRESH";
char EffectType__2__Parameter__1__name[] = "COMP_RATIO";
char EffectType__2__Parameter__2__name[] = "COMP_ATTACK";
char EffectType__2__Parameter__3__name[] = "COMP_RELEASE";
char EffectType__2__Parameter__4__name[] = "COMP_LEVEL";
char EffectType__2__Parameter__5__name[] = "COMP_KNEE";
char EffectType__2__Parameter__6__name[] = "COMP_AUTO";
char EffectType__2__Parameter__7__name[] = "COMP_PEAKRMS";
char EffectType__2__Parameter__8__name[] = "COMP_CONTOUR";
char EffectType__2__Parameter__9__name[] = "COMP_BYPASS";
char EffectType__2__Parameter__10__name[] = "COMP_SIDECHAIN";
char EffectType__2__Parameter__11__name[] = "COMP_MIX";
char EffectType__2__Parameter__12__name[] = "COMP_TYPE";
char EffectType__2__Parameter__13__name[] = "COMP_SUSTAIN";
char EffectType__2__Parameter__14__name[] = "COMP_BYPASSMODE";
char EffectType__2__Parameter__15__name[] = "COMP_DELAYTIME";
char EffectType__2__Parameter__16__name[] = "COMP_AUTOMODE";
char EffectType__2__Parameter__17__name[] = "COMP_EMPHASIS";
char EffectType__3__Parameter__0__name[] = "GEQ_GAIN1";
char EffectType__3__Parameter__1__name[] = "GEQ_GAIN2";
char EffectType__3__Parameter__2__name[] = "GEQ_GAIN3";
char EffectType__3__Parameter__3__name[] = "GEQ_GAIN4";
char EffectType__3__Parameter__4__name[] = "GEQ_GAIN5";
char EffectType__3__Parameter__5__name[] = "GEQ_GAIN6";
char EffectType__3__Parameter__6__name[] = "GEQ_GAIN7";
char EffectType__3__Parameter__7__name[] = "GEQ_GAIN8";
char EffectType__3__Parameter__8__name[] = "GEQ_GAIN9";
char EffectType__3__Parameter__9__name[] = "GEQ_GAIN10";
char EffectType__3__Parameter__10__name[] = "GEQ_MIX";
char EffectType__3__Parameter__11__name[] = "GEQ_LEVEL";
char EffectType__3__Parameter__12__name[] = "GEQ_PAN";
char EffectType__3__Parameter__13__name[] = "GEQ_BYPASSMODE";
char EffectType__3__Parameter__14__name[] = "GEQ_GLOBALMIX";
char EffectType__3__Parameter__15__name[] = "GEQ_SPARE1";
char EffectType__3__Parameter__16__name[] = "GEQ_SPARE2";
char EffectType__3__Parameter__17__name[] = "GEQ_SPARE3";
char EffectType__3__Parameter__18__name[] = "GEQ_BYPASS";
char EffectType__4__Parameter__0__name[] = "PEQ_FREQ1";
char EffectType__4__Parameter__1__name[] = "PEQ_FREQ2";
char EffectType__4__Parameter__2__name[] = "PEQ_FREQ3";
char EffectType__4__Parameter__3__name[] = "PEQ_FREQ4";
char EffectType__4__Parameter__4__name[] = "PEQ_FREQ5";
char EffectType__4__Parameter__5__name[] = "PEQ_Q1";
char EffectType__4__Parameter__6__name[] = "PEQ_Q2";
char EffectType__4__Parameter__7__name[] = "PEQ_Q3";
char EffectType__4__Parameter__8__name[] = "PEQ_Q4";
char EffectType__4__Parameter__9__name[] = "PEQ_Q5";
char EffectType__4__Parameter__10__name[] = "PEQ_GAIN1";
char EffectType__4__Parameter__11__name[] = "PEQ_GAIN2";
char EffectType__4__Parameter__12__name[] = "PEQ_GAIN3";
char EffectType__4__Parameter__13__name[] = "PEQ_GAIN4";
char EffectType__4__Parameter__14__name[] = "PEQ_GAIN5";
char EffectType__4__Parameter__15__name[] = "PEQ_LFTYPE";
char EffectType__4__Parameter__16__name[] = "PEQ_HFTYPE";
char EffectType__4__Parameter__17__name[] = "PEQ_SPARE3";
char EffectType__4__Parameter__18__name[] = "PEQ_MIX";
char EffectType__4__Parameter__19__name[] = "PEQ_LEVEL";
char EffectType__4__Parameter__20__name[] = "PEQ_PAN";
char EffectType__4__Parameter__21__name[] = "PEQ_BYPASSMODE";
char EffectType__4__Parameter__22__name[] = "PEQ_GLOBALMIX";
char EffectType__4__Parameter__23__name[] = "PEQ_BYPASS";

// AMP
char EffectType__5__Parameter__0__name[] = "DISTORT_TYPE";
char EffectType__5__Parameter__1__name[] = "DISTORT_DRIVE";
char EffectType__5__Parameter__2__name[] = "DISTORT_BASS";
char EffectType__5__Parameter__3__name[] = "DISTORT_MID";
char EffectType__5__Parameter__4__name[] = "DISTORT_TREBLE";
char EffectType__5__Parameter__5__name[] = "DISTORT_MASTER";
char EffectType__5__Parameter__6__name[] = "DISTORT_HPFREQ";
char EffectType__5__Parameter__7__name[] = "DISTORT_LPFREQ";
char EffectType__5__Parameter__8__name[] = "DISTORT_TONEFREQ";
char EffectType__5__Parameter__9__name[] = "DISTORT_XFORMGRINT";
char EffectType__5__Parameter__10__name[] = "DISTORT_BRIGHTCAP";
char EffectType__5__Parameter__11__name[] = "DISTORT_WSLPF";
char EffectType__5__Parameter__12__name[] = "DISTORT_XFHPF";
char EffectType__5__Parameter__13__name[] = "DISTORT_XFLPF";
char EffectType__5__Parameter__14__name[] = "DISTORT_TONELOC";
char EffectType__5__Parameter__15__name[] = "DISTORT_INPUTSELECT";
char EffectType__5__Parameter__16__name[] = "DISTORT_DEPTH";
char EffectType__5__Parameter__17__name[] = "DISTORT_OFFSET1";
char EffectType__5__Parameter__18__name[] = "DISTORT_CLIPTYPE2";
char EffectType__5__Parameter__19__name[] = "DISTORT_SUPPLYSAG";
char EffectType__5__Parameter__20__name[] = "DISTORT_PRESENCE";
char EffectType__5__Parameter__21__name[] = "DISTORT_LEVEL";
char EffectType__5__Parameter__22__name[] = "DISTORT_PAN";
char EffectType__5__Parameter__23__name[] = "DISTORT_BYPASSMODE";
char EffectType__5__Parameter__24__name[] = "DISTORT_NEGFBACK"; //"DISTORT_BETA";
char EffectType__5__Parameter__25__name[] = "DISTORT_PRESFREQ";
char EffectType__5__Parameter__26__name[] = "DISTORT_SPKRFREQ";
char EffectType__5__Parameter__27__name[] = "DISTORT_SPKRGAIN";
char EffectType__5__Parameter__28__name[] = "DISTORT_BYPASS";
char EffectType__5__Parameter__29__name[] = "DISTORT_DEPTHFREQ";
char EffectType__5__Parameter__30__name[] = "DISTORT_HARDNESS";
char EffectType__5__Parameter__31__name[] = "DISTORT_MVCAP";
char EffectType__5__Parameter__32__name[] = "DISTORT_WSHPF";
char EffectType__5__Parameter__33__name[] = "DISTORT_HARMONICS"; //"DISTORT_STABILIZER";
char EffectType__5__Parameter__34__name[] = "DISTORT_TONETYPE";
char EffectType__5__Parameter__35__name[] = "DISTORT_TIMECONST";
char EffectType__5__Parameter__36__name[] = "DISTORT_BIAS";
char EffectType__5__Parameter__37__name[] = "DISTORT_FBTYPE";
char EffectType__5__Parameter__38__name[] = "DISTORT_SPKRGAIN2";
char EffectType__5__Parameter__39__name[] = "DISTORT_BRIGHT";
char EffectType__5__Parameter__40__name[] = "DISTORT_BOOST";
char EffectType__5__Parameter__41__name[] = "DISTORT_SPKRQ";
char EffectType__5__Parameter__42__name[] = "DISTORT_OFFSET2";
char EffectType__5__Parameter__43__name[] = "DISTORT_SPKRHFREQ";
char EffectType__5__Parameter__44__name[] = "DISTORT_SPKRHGAIN";
char EffectType__5__Parameter__45__name[] = "DISTORT_CUT"; //"DISTORT_SPKRHQ";
char EffectType__5__Parameter__46__name[] = "DISTORT_XDRIVE";
char EffectType__5__Parameter__47__name[] = "DISTORT_TRIM";
char EffectType__5__Parameter__48__name[] = "DISTORT_HARDNESS2";
char EffectType__5__Parameter__49__name[] = "DISTORT_MVPOSITION";
char EffectType__5__Parameter__50__name[] = "DISTORT_SPKRDRIVE";
char EffectType__5__Parameter__51__name[] = "DISTORT_GAINDIST";
char EffectType__5__Parameter__52__name[] = "DISTORT_SCREENFREQ";
char EffectType__5__Parameter__53__name[] = "DISTORT_SCREENQ";
char EffectType__5__Parameter__54__name[] = "DISTORT_SATSWITCH";
char EffectType__5__Parameter__55__name[] = "DISTORT_EQ1";
char EffectType__5__Parameter__56__name[] = "DISTORT_EQ2";
char EffectType__5__Parameter__57__name[] = "DISTORT_EQ3";
char EffectType__5__Parameter__58__name[] = "DISTORT_EQ4";
char EffectType__5__Parameter__59__name[] = "DISTORT_EQ5";
char EffectType__5__Parameter__60__name[] = "DISTORT_EQ6";
char EffectType__5__Parameter__61__name[] = "DISTORT_EQ7";
char EffectType__5__Parameter__62__name[] = "DISTORT_EQ8";
char EffectType__5__Parameter__63__name[] = "DISTORT_BIASEXCURSION";
char EffectType__5__Parameter__64__name[] = "DISTORT_EXCURSIONTIME";
char EffectType__5__Parameter__65__name[] = "DISTORT_RECOVERYTIME";
char EffectType__5__Parameter__66__name[] = "DISTORT_FEEDFWDFREQ";
char EffectType__5__Parameter__67__name[] = "DISTORT_FEEDFWDFREQ2";
char EffectType__5__Parameter__68__name[] = "DISTORT_TUBETYPE";
char EffectType__5__Parameter__69__name[] = "DISTORT_VOICING";
char EffectType__5__Parameter__70__name[] = "DISTORT_OUTCOMPCLARITY";
char EffectType__5__Parameter__71__name[] = "DISTORT_CHARQ"; //"DISTORT_PAHPFREQ";
char EffectType__5__Parameter__72__name[] = "DISTORT_HMFREQ";
char EffectType__5__Parameter__73__name[] = "DISTORT_HMRATIO";
char EffectType__5__Parameter__74__name[] = "DISTORT_OVRDRIVE"; //"DISTORT_SPKRMGAIN";
char EffectType__5__Parameter__75__name[] = "DISTORT_OUTCOMPAMOUNT"; //"DISTORT_DYNAMICS";
char EffectType__5__Parameter__76__name[] = "DISTORT_OUTCOMPTHRES";
char EffectType__5__Parameter__77__name[] = "DISTORT_MVTRIM";
char EffectType__5__Parameter__78__name[] = "DISTORT_FAT";
char EffectType__5__Parameter__79__name[] = "DISTORT_DEFINITION";
char EffectType__5__Parameter__80__name[] = "DISTORT_PREACFCOMP"; //"DISTORT_PREDYNAMICS";
char EffectType__5__Parameter__81__name[] = "DISTORT_PREACFTIME"; //"DISTORT_PREDYNTIME";
char EffectType__5__Parameter__82__name[] = "DISTORT_USEMATCHING";
char EffectType__5__Parameter__83__name[] = "DISTORT_PICKATTACK";
char EffectType__5__Parameter__84__name[] = "DISTORT_DYNPRES";
char EffectType__5__Parameter__85__name[] = "DISTORT_DYNDEPTH";
char EffectType__5__Parameter__86__name[] = "DISTORT_SUPPLYTYPE";
char EffectType__5__Parameter__87__name[] = "DISTORT_LINEFREQ";
char EffectType__5__Parameter__88__name[] = "DISTORT_PREAMPHARD"; //"DISTORT_THUNK";
char EffectType__5__Parameter__89__name[] = "DISTORT_TREMFREQ";
char EffectType__5__Parameter__90__name[] = "DISTORT_TREMDEPTH";

//AMP for QUANTUM 6
char EffectType__5__Parameter__91__name[] = "DISTORT_";
char EffectType__5__Parameter__92__name[] = "DISTORT_";
char EffectType__5__Parameter__93__name[] = "DISTORT_CATHRESIST";
char EffectType__5__Parameter__94__name[] = "DISTORT_";
char EffectType__5__Parameter__95__name[] = "DISTORT_";
char EffectType__5__Parameter__96__name[] = "DISTORT_PREAMPSAG";
char EffectType__5__Parameter__97__name[] = "DISTORT_";
char EffectType__5__Parameter__98__name[] = "DISTORT_PWRAMPBIAS";
char EffectType__5__Parameter__99__name[] = "DISTORT_PREAMPDYNAMICS";
char EffectType__5__Parameter__100__name[] = "DISTORT_HIFREQSLOPE";
char EffectType__5__Parameter__101__name[] = "DISTORT_VARIAC";
char EffectType__5__Parameter__102__name[] = "DISTORT_CHARTYPE";
char EffectType__5__Parameter__103__name[] = "DISTORT_";
char EffectType__5__Parameter__104__name[] = "DISTORT_PRESENCESHIFT";
char EffectType__5__Parameter__105__name[] = "DISTORT_";
char EffectType__5__Parameter__106__name[] = "DISTORT_";
char EffectType__5__Parameter__107__name[] = "DISTORT_";
char EffectType__5__Parameter__108__name[] = "DISTORT_";
char EffectType__5__Parameter__109__name[] = "DISTORT_PUTCOMPTYPE";
char EffectType__5__Parameter__110__name[] = "DISTORT_";
char EffectType__5__Parameter__111__name[] = "DISTORT_PREAMPCFCOMPTYP";
char EffectType__5__Parameter__112__name[] = "DISTORT_PREAMPCFHARD";

char EffectType__6__Parameter__0__name[] = "CABINET_TYPEL";
char EffectType__6__Parameter__1__name[] = "CABINET_MICL";
char EffectType__6__Parameter__2__name[] = "CABINET_TYPER";
char EffectType__6__Parameter__3__name[] = "CABINET_MICR";
char EffectType__6__Parameter__4__name[] = "CABINET_LINK";
char EffectType__6__Parameter__5__name[] = "CABINET_LEVELL";
char EffectType__6__Parameter__6__name[] = "CABINET_LEVELR";
char EffectType__6__Parameter__7__name[] = "CABINET_PANL";
char EffectType__6__Parameter__8__name[] = "CABINET_PANR";
char EffectType__6__Parameter__9__name[] = "CABINET_LEVEL";
char EffectType__6__Parameter__10__name[] = "CABINET_PAN";
char EffectType__6__Parameter__11__name[] = "CABINET_BYPASSMODE";
char EffectType__6__Parameter__12__name[] = "CABINET_MODE";
char EffectType__6__Parameter__13__name[] = "CABINET_BYPASS";
char EffectType__6__Parameter__14__name[] = "CABINET_DRIVEL";
char EffectType__6__Parameter__15__name[] = "CABINET_DRIVER";
char EffectType__6__Parameter__16__name[] = "CABINET_ROOMMIX";
char EffectType__6__Parameter__17__name[] = "CABINET_ROOMSPACE";
char EffectType__6__Parameter__18__name[] = "CABINET_MICSPACE";
char EffectType__6__Parameter__19__name[] = "CABINET_LOCUT";
char EffectType__6__Parameter__20__name[] = "CABINET_HICUT";
char EffectType__6__Parameter__21__name[] = "CABINET_SIZE";
char EffectType__6__Parameter__22__name[] = "CABINET_PROXIMITY";
char EffectType__6__Parameter__23__name[] = "CABINET_DIRECT";
char EffectType__6__Parameter__24__name[] = "CABINET_DYNAMICS";
char EffectType__6__Parameter__25__name[] = "CABINET_DIRECTFREQ";
char EffectType__6__Parameter__26__name[] = "CABINET_DELAYL";
char EffectType__6__Parameter__27__name[] = "CABINET_DELAYR";
char EffectType__6__Parameter__28__name[] = "CABINET_PROXIMITYR";
char EffectType__7__Parameter__0__name[] = "REVERB_TYPE";
char EffectType__7__Parameter__1__name[] = "REVERB_TIME";
char EffectType__7__Parameter__2__name[] = "REVERB_HICUT";
char EffectType__7__Parameter__3__name[] = "REVERB_HFRATIO";
char EffectType__7__Parameter__4__name[] = "REVERB_DIFFUSION";
char EffectType__7__Parameter__5__name[] = "REVERB_SIZE";
char EffectType__7__Parameter__6__name[] = "REVERB_REVERBDELAY";
char EffectType__7__Parameter__7__name[] = "REVERB_EARLYLEVEL";
char EffectType__7__Parameter__8__name[] = "REVERB_REVERBLEVEL";
char EffectType__7__Parameter__9__name[] = "REVERB_PREDELAY";
char EffectType__7__Parameter__10__name[] = "REVERB_LOWCUT";
char EffectType__7__Parameter__11__name[] = "REVERB_DEPTH";
char EffectType__7__Parameter__12__name[] = "REVERB_RATE";
char EffectType__7__Parameter__13__name[] = "REVERB_MIX";
char EffectType__7__Parameter__14__name[] = "REVERB_LEVEL";
char EffectType__7__Parameter__15__name[] = "REVERB_PAN";
char EffectType__7__Parameter__16__name[] = "REVERB_BYPASSMODE";
char EffectType__7__Parameter__17__name[] = "REVERB_GLOBALMIX";
char EffectType__7__Parameter__18__name[] = "REVERB_GAIN";
char EffectType__7__Parameter__19__name[] = "REVERB_DENSITY";
char EffectType__7__Parameter__20__name[] = "REVERB_INPDIFF";
char EffectType__7__Parameter__21__name[] = "REVERB_INDIFFTIME";
char EffectType__7__Parameter__22__name[] = "REVERB_BYPASS";
char EffectType__7__Parameter__23__name[] = "REVERB_NUMSPRINGS";
char EffectType__7__Parameter__24__name[] = "REVERB_TONE";
char EffectType__7__Parameter__25__name[] = "REVERB_WIDTH";
char EffectType__7__Parameter__26__name[] = "REVERB_FREQ1";
char EffectType__7__Parameter__27__name[] = "REVERB_FREQ2";
char EffectType__7__Parameter__28__name[] = "REVERB_Q1";
char EffectType__7__Parameter__29__name[] = "REVERB_Q2";
char EffectType__7__Parameter__30__name[] = "REVERB_GAIN1";
char EffectType__7__Parameter__31__name[] = "REVERB_GAIN2";
char EffectType__7__Parameter__32__name[] = "REVERB_SPRINGDRIVE";
char EffectType__7__Parameter__33__name[] = "REVERB_LFTIME";
char EffectType__7__Parameter__34__name[] = "REVERB_LFXOVER";
char EffectType__8__Parameter__0__name[] = "DELAY_MODEL";
char EffectType__8__Parameter__1__name[] = "DELAY_TYPE";
char EffectType__8__Parameter__2__name[] = "DELAY_TIME";
char EffectType__8__Parameter__3__name[] = "DELAY_RATIO";
char EffectType__8__Parameter__4__name[] = "DELAY_FEED";
char EffectType__8__Parameter__5__name[] = "DELAY_FEEDL";
char EffectType__8__Parameter__6__name[] = "DELAY_FEEDR";
char EffectType__8__Parameter__7__name[] = "DELAY_DELAYPAN";
char EffectType__8__Parameter__8__name[] = "DELAY_SPREAD";
char EffectType__8__Parameter__9__name[] = "DELAY_TEMPO";
char EffectType__8__Parameter__10__name[] = "DELAY_LOCUT";
char EffectType__8__Parameter__11__name[] = "DELAY_HICUT";
char EffectType__8__Parameter__12__name[] = "DELAY_RATE1";
char EffectType__8__Parameter__13__name[] = "DELAY_RATE2";
char EffectType__8__Parameter__14__name[] = "DELAY_DEPTH1";
char EffectType__8__Parameter__15__name[] = "DELAY_DEPTH2";
char EffectType__8__Parameter__16__name[] = "DELAY_DRIVE";
char EffectType__8__Parameter__17__name[] = "DELAY_MIX";
char EffectType__8__Parameter__18__name[] = "DELAY_LEVEL";
char EffectType__8__Parameter__19__name[] = "DELAY_PAN";
char EffectType__8__Parameter__20__name[] = "DELAY_BYPASSMODE";
char EffectType__8__Parameter__21__name[] = "DELAY_GLOBALMIX";
char EffectType__8__Parameter__22__name[] = "DELAY_BYPASS";
char EffectType__8__Parameter__23__name[] = "DELAY_GAIN";
char EffectType__8__Parameter__24__name[] = "DELAY_LFO1TYPE";
char EffectType__8__Parameter__25__name[] = "DELAY_LFO2TYPE";
char EffectType__8__Parameter__26__name[] = "DELAY_TIMER";
char EffectType__8__Parameter__27__name[] = "DELAY_HOLD";
char EffectType__8__Parameter__28__name[] = "DELAY_MSTRFDBK";
char EffectType__8__Parameter__29__name[] = "DELAY_TEMPOR";
char EffectType__8__Parameter__30__name[] = "DELAY_FEEDLR";
char EffectType__8__Parameter__31__name[] = "DELAY_FEEDRL";
char EffectType__8__Parameter__32__name[] = "DELAY_LEVELL";
char EffectType__8__Parameter__33__name[] = "DELAY_LEVELR";
char EffectType__8__Parameter__34__name[] = "DELAY_PANL";
char EffectType__8__Parameter__35__name[] = "DELAY_PANR";
char EffectType__8__Parameter__36__name[] = "DELAY_LFO1PHASE";
char EffectType__8__Parameter__37__name[] = "DELAY_LFO2PHASE";
char EffectType__8__Parameter__38__name[] = "DELAY_SPLICETIME";
char EffectType__8__Parameter__39__name[] = "DELAY_RUN";
char EffectType__8__Parameter__40__name[] = "DELAY_MODE";
char EffectType__8__Parameter__41__name[] = "DELAY_FILTORDER";
char EffectType__8__Parameter__42__name[] = "DELAY_ATTEN";
char EffectType__8__Parameter__43__name[] = "DELAY_THRESH";
char EffectType__8__Parameter__44__name[] = "DELAY_RELEASE";
char EffectType__8__Parameter__45__name[] = "DELAY_DIFFUSE";
char EffectType__8__Parameter__46__name[] = "DELAY_DIFFTIME";
char EffectType__8__Parameter__47__name[] = "DELAY_PHASEREV";
char EffectType__8__Parameter__48__name[] = "DELAY_LFO1TARGET";
char EffectType__8__Parameter__49__name[] = "DELAY_LFO2TARGET";
char EffectType__8__Parameter__50__name[] = "DELAY_LFO1TEMPO";
char EffectType__8__Parameter__51__name[] = "DELAY_LFO2TEMPO";
char EffectType__8__Parameter__52__name[] = "DELAY_RATE3";
char EffectType__8__Parameter__53__name[] = "DELAY_LFO3TYPE";
char EffectType__8__Parameter__54__name[] = "DELAY_LFO3PHASE";
char EffectType__8__Parameter__55__name[] = "DELAY_LFO3TEMPO";
char EffectType__8__Parameter__56__name[] = "DELAY_FSTART";
char EffectType__8__Parameter__57__name[] = "DELAY_FSTOP";
char EffectType__8__Parameter__58__name[] = "DELAY_Q";
char EffectType__8__Parameter__59__name[] = "DELAY_FILTERQ";
char EffectType__8__Parameter__60__name[] = "DELAY_BITREDUCE";
char EffectType__8__Parameter__61__name[] = "DELAY_FREQ1";
char EffectType__8__Parameter__62__name[] = "DELAY_FREQ2";
char EffectType__8__Parameter__63__name[] = "DELAY_Q1";
char EffectType__8__Parameter__64__name[] = "DELAY_Q2";
char EffectType__8__Parameter__65__name[] = "DELAY_GAIN1";
char EffectType__8__Parameter__66__name[] = "DELAY_GAIN2";
char EffectType__8__Parameter__67__name[] = "DELAY_LFORANGE";
char EffectType__8__Parameter__68__name[] = "DELAY_SPEED";
char EffectType__8__Parameter__69__name[] = "DELAY_OFFSET";
char EffectType__9__Parameter__0__name[] = "MULTITAP_TIME1";
char EffectType__9__Parameter__1__name[] = "MULTITAP_TIME2";
char EffectType__9__Parameter__2__name[] = "MULTITAP_TIME3";
char EffectType__9__Parameter__3__name[] = "MULTITAP_TIME4";
char EffectType__9__Parameter__4__name[] = "MULTITAP_TEMPO1";
char EffectType__9__Parameter__5__name[] = "MULTITAP_TEMPO2";
char EffectType__9__Parameter__6__name[] = "MULTITAP_TEMPO3";
char EffectType__9__Parameter__7__name[] = "MULTITAP_TEMPO4";
char EffectType__9__Parameter__8__name[] = "MULTITAP_LEVEL1";
char EffectType__9__Parameter__9__name[] = "MULTITAP_LEVEL2";
char EffectType__9__Parameter__10__name[] = "MULTITAP_LEVEL3";
char EffectType__9__Parameter__11__name[] = "MULTITAP_LEVEL4";
char EffectType__9__Parameter__12__name[] = "MULTITAP_FEEDBACK1";
char EffectType__9__Parameter__13__name[] = "MULTITAP_FEEDBACK2";
char EffectType__9__Parameter__14__name[] = "MULTITAP_FEEDBACK3";
char EffectType__9__Parameter__15__name[] = "MULTITAP_FEEDBACK4";
char EffectType__9__Parameter__16__name[] = "MULTITAP_PAN1";
char EffectType__9__Parameter__17__name[] = "MULTITAP_PAN2";
char EffectType__9__Parameter__18__name[] = "MULTITAP_PAN3";
char EffectType__9__Parameter__19__name[] = "MULTITAP_PAN4";
char EffectType__9__Parameter__20__name[] = "MULTITAP_RATE1";
char EffectType__9__Parameter__21__name[] = "MULTITAP_RATE2";
char EffectType__9__Parameter__22__name[] = "MULTITAP_RATE3";
char EffectType__9__Parameter__23__name[] = "MULTITAP_RATE4";
char EffectType__9__Parameter__24__name[] = "MULTITAP_LFOTEMPO1";
char EffectType__9__Parameter__25__name[] = "MULTITAP_LFOTEMPO2";
char EffectType__9__Parameter__26__name[] = "MULTITAP_LFOTEMPO3";
char EffectType__9__Parameter__27__name[] = "MULTITAP_LFOTEMPO4";
char EffectType__9__Parameter__28__name[] = "MULTITAP_MIX";
char EffectType__9__Parameter__29__name[] = "MULTITAP_LEVEL";
char EffectType__9__Parameter__30__name[] = "MULTITAP_PAN";
char EffectType__9__Parameter__31__name[] = "MULTITAP_BYPASSMODE";
char EffectType__9__Parameter__32__name[] = "MULTITAP_GLOBALMIX";
char EffectType__9__Parameter__33__name[] = "MULTITAP_INGAIN";
char EffectType__9__Parameter__34__name[] = "MULTITAP_BYPASS";
char EffectType__9__Parameter__35__name[] = "MULTITAP_TYPE";
char EffectType__9__Parameter__36__name[] = "MULTITAP_DECAY";
char EffectType__9__Parameter__37__name[] = "MULTITAP_DIFFUSION";
char EffectType__9__Parameter__38__name[] = "MULTITAP_DIFFMIX";
char EffectType__9__Parameter__39__name[] = "MULTITAP_DIFFTIME";
char EffectType__9__Parameter__40__name[] = "MULTITAP_THRESH";
char EffectType__9__Parameter__41__name[] = "MULTITAP_SPLICE";
char EffectType__9__Parameter__42__name[] = "MULTITAP_MSTRTIME";
char EffectType__9__Parameter__43__name[] = "MULTITAP_MSTRLVL";
char EffectType__9__Parameter__44__name[] = "MULTITAP_MSTRPAN";
char EffectType__9__Parameter__45__name[] = "MULTITAP_MSTRFREQ";
char EffectType__9__Parameter__46__name[] = "MULTITAP_MSTRQ";
char EffectType__9__Parameter__47__name[] = "MULTITAP_MSTRFDBK";
char EffectType__9__Parameter__48__name[] = "MULTITAP_MSTRPITCH";
char EffectType__9__Parameter__49__name[] = "MULTITAP_MSTRDTN";
char EffectType__9__Parameter__50__name[] = "MULTITAP_DETUNE1";
char EffectType__9__Parameter__51__name[] = "MULTITAP_DETUNE2";
char EffectType__9__Parameter__52__name[] = "MULTITAP_DETUNE3";
char EffectType__9__Parameter__53__name[] = "MULTITAP_DETUNE4";
char EffectType__9__Parameter__54__name[] = "MULTITAP_SHIFT1";
char EffectType__9__Parameter__55__name[] = "MULTITAP_SHIFT2";
char EffectType__9__Parameter__56__name[] = "MULTITAP_SHIFT3";
char EffectType__9__Parameter__57__name[] = "MULTITAP_SHIFT4";
char EffectType__9__Parameter__58__name[] = "MULTITAP_FREQ1";
char EffectType__9__Parameter__59__name[] = "MULTITAP_FREQ2";
char EffectType__9__Parameter__60__name[] = "MULTITAP_FREQ3";
char EffectType__9__Parameter__61__name[] = "MULTITAP_FREQ4";
char EffectType__9__Parameter__62__name[] = "MULTITAP_Q1";
char EffectType__9__Parameter__63__name[] = "MULTITAP_Q2";
char EffectType__9__Parameter__64__name[] = "MULTITAP_Q3";
char EffectType__9__Parameter__65__name[] = "MULTITAP_Q4";
char EffectType__9__Parameter__66__name[] = "MULTITAP_MSTRRATE";
char EffectType__9__Parameter__67__name[] = "MULTITAP_ATTEN";
char EffectType__9__Parameter__68__name[] = "MULTITAP_MSTRDEPTH";
char EffectType__9__Parameter__69__name[] = "MULTITAP_DIRECTION";
char EffectType__9__Parameter__70__name[] = "MULTITAP_SPEED";
char EffectType__9__Parameter__71__name[] = "MULTITAP_DEPTH1";
char EffectType__9__Parameter__72__name[] = "MULTITAP_DEPTH2";
char EffectType__9__Parameter__73__name[] = "MULTITAP_DEPTH3";
char EffectType__9__Parameter__74__name[] = "MULTITAP_DEPTH4";
char EffectType__9__Parameter__75__name[] = "MULTITAP_LFOLOCK";
char EffectType__9__Parameter__76__name[] = "MULTITAP_FBKSEND";
char EffectType__9__Parameter__77__name[] = "MULTITAP_FBKRET";
char EffectType__9__Parameter__78__name[] = "MULTITAP_STEREO";
char EffectType__9__Parameter__79__name[] = "MULTITAP_TIMEM";
char EffectType__9__Parameter__80__name[] = "MULTITAP_SUBDIV";
char EffectType__9__Parameter__81__name[] = "MULTITAP_QUANTIZE";
char EffectType__9__Parameter__82__name[] = "MULTITAP_RDECAY";
char EffectType__9__Parameter__83__name[] = "MULTITAP_DECAYSTYLE";
char EffectType__9__Parameter__84__name[] = "MULTITAP_NUMTAPS";
char EffectType__9__Parameter__85__name[] = "MULTITAP_SHUFFLE";
char EffectType__9__Parameter__86__name[] = "MULTITAP_RTEMPO";
char EffectType__9__Parameter__87__name[] = "MULTITAP_SPREAD";
char EffectType__9__Parameter__88__name[] = "MULTITAP_PANSHAPE";
char EffectType__9__Parameter__89__name[] = "MULTITAP_PANALPHA";
char EffectType__9__Parameter__90__name[] = "MULTITAP_LOWCUT";
char EffectType__9__Parameter__91__name[] = "MULTITAP_HICUT";
char EffectType__9__Parameter__92__name[] = "MULTITAP_OFFSET";
char EffectType__9__Parameter__93__name[] = "MULTITAP_FEEDBACK";
char EffectType__9__Parameter__94__name[] = "MULTITAP_TIME1M";
char EffectType__9__Parameter__95__name[] = "MULTITAP_TIME2M";
char EffectType__9__Parameter__96__name[] = "MULTITAP_TIME3M";
char EffectType__9__Parameter__97__name[] = "MULTITAP_TIME4M";
char EffectType__9__Parameter__98__name[] = "MULTITAP_TIME5M";
char EffectType__9__Parameter__99__name[] = "MULTITAP_TIME6M";
char EffectType__9__Parameter__100__name[] = "MULTITAP_TIME7M";
char EffectType__9__Parameter__101__name[] = "MULTITAP_TIME8M";
char EffectType__9__Parameter__102__name[] = "MULTITAP_TIME9M";
char EffectType__9__Parameter__103__name[] = "MULTITAP_TIME10M";
char EffectType__9__Parameter__104__name[] = "MULTITAP_RLEVEL1";
char EffectType__9__Parameter__105__name[] = "MULTITAP_RLEVEL2";
char EffectType__9__Parameter__106__name[] = "MULTITAP_RLEVEL3";
char EffectType__9__Parameter__107__name[] = "MULTITAP_RLEVEL4";
char EffectType__9__Parameter__108__name[] = "MULTITAP_RLEVEL5";
char EffectType__9__Parameter__109__name[] = "MULTITAP_RLEVEL6";
char EffectType__9__Parameter__110__name[] = "MULTITAP_RLEVEL7";
char EffectType__9__Parameter__111__name[] = "MULTITAP_RLEVEL8";
char EffectType__9__Parameter__112__name[] = "MULTITAP_RLEVEL9";
char EffectType__9__Parameter__113__name[] = "MULTITAP_RLEVEL10";
char EffectType__9__Parameter__114__name[] = "MULTITAP_REFTEMPO";
char EffectType__9__Parameter__115__name[] = "MULTITAP_TRACKTEMPO";
char EffectType__9__Parameter__116__name[] = "MULTITAP_RELEASE";
char EffectType__10__Parameter__0__name[] = "CHORUS_TYPE";
char EffectType__10__Parameter__1__name[] = "CHORUS_VOICES";
char EffectType__10__Parameter__2__name[] = "CHORUS_RATE";
char EffectType__10__Parameter__3__name[] = "CHORUS_TEMPO";
char EffectType__10__Parameter__4__name[] = "CHORUS_DEPTH";
char EffectType__10__Parameter__5__name[] = "CHORUS_HICUT";
char EffectType__10__Parameter__6__name[] = "CHORUS_DELAYTIME";
char EffectType__10__Parameter__7__name[] = "CHORUS_LFOPHASE";
char EffectType__10__Parameter__8__name[] = "CHORUS_LFOTYPE";
char EffectType__10__Parameter__9__name[] = "CHORUS_AUTO";
char EffectType__10__Parameter__10__name[] = "CHORUS_MIX";
char EffectType__10__Parameter__11__name[] = "CHORUS_LEVEL";
char EffectType__10__Parameter__12__name[] = "CHORUS_PAN";
char EffectType__10__Parameter__13__name[] = "CHORUS_BYPASSMODE";
char EffectType__10__Parameter__14__name[] = "CHORUS_GLOBALMIX";
char EffectType__10__Parameter__15__name[] = "CHORUS_BYPASS";
char EffectType__10__Parameter__16__name[] = "CHORUS_PHASEREV";
char EffectType__10__Parameter__17__name[] = "CHORUS_WIDTH";
char EffectType__10__Parameter__18__name[] = "CHORUS_LFO2RATE";
char EffectType__10__Parameter__19__name[] = "CHORUS_LFO2DEPTH";
char EffectType__10__Parameter__20__name[] = "CHORUS_DRIVE";
char EffectType__10__Parameter__21__name[] = "CHORUS_LOCUT";
char EffectType__10__Parameter__22__name[] = "CHORUS_SPREAD";
char EffectType__11__Parameter__0__name[] = "FLANGER_TYPE";
char EffectType__11__Parameter__1__name[] = "FLANGER_RATE";
char EffectType__11__Parameter__2__name[] = "FLANGER_TEMPO";
char EffectType__11__Parameter__3__name[] = "FLANGER_DEPTH";
char EffectType__11__Parameter__4__name[] = "FLANGER_FEEDBACK";
char EffectType__11__Parameter__5__name[] = "FLANGER_DELAYTIME";
char EffectType__11__Parameter__6__name[] = "FLANGER_MANUAL";
char EffectType__11__Parameter__7__name[] = "FLANGER_LFOPHASE";
char EffectType__11__Parameter__8__name[] = "FLANGER_LFOTYPE";
char EffectType__11__Parameter__9__name[] = "FLANGER_LFOFILTER";
char EffectType__11__Parameter__10__name[] = "FLANGER_AUTO";
char EffectType__11__Parameter__11__name[] = "FLANGER_MIX";
char EffectType__11__Parameter__12__name[] = "FLANGER_LEVEL";
char EffectType__11__Parameter__13__name[] = "FLANGER_PAN";
char EffectType__11__Parameter__14__name[] = "FLANGER_BYPASSMODE";
char EffectType__11__Parameter__15__name[] = "FLANGER_GLOBALMIX";
char EffectType__11__Parameter__16__name[] = "FLANGER_BYPASS";
char EffectType__11__Parameter__17__name[] = "FLANGER_PHASEREV";
char EffectType__11__Parameter__18__name[] = "FLANGER_THRUZERO";
char EffectType__11__Parameter__19__name[] = "FLANGER_HICUT";
char EffectType__11__Parameter__20__name[] = "FLANGER_DRIVE";
char EffectType__11__Parameter__21__name[] = "FLANGER_LOCUT";
char EffectType__11__Parameter__22__name[] = "FLANGER_SPREAD";
char EffectType__12__Parameter__0__name[] = "ROTARY_RATE";
char EffectType__12__Parameter__1__name[] = "ROTARY_LFDEPTH";
char EffectType__12__Parameter__2__name[] = "ROTARY_HFDEPTH";
char EffectType__12__Parameter__3__name[] = "ROTARY_HFLEVEL";
char EffectType__12__Parameter__4__name[] = "ROTARY_TEMPO";
char EffectType__12__Parameter__5__name[] = "ROTARY_MIX";
char EffectType__12__Parameter__6__name[] = "ROTARY_LEVEL";
char EffectType__12__Parameter__7__name[] = "ROTARY_PAN";
char EffectType__12__Parameter__8__name[] = "ROTARY_BYPASSMODE";
char EffectType__12__Parameter__9__name[] = "ROTARY_GLOBALMIX";
char EffectType__12__Parameter__10__name[] = "ROTARY_HFLENGTH";
char EffectType__12__Parameter__11__name[] = "ROTARY_BYPASS";
char EffectType__12__Parameter__12__name[] = "ROTARY_WIDTH";
char EffectType__12__Parameter__13__name[] = "ROTARY_LOWMULT";
char EffectType__12__Parameter__14__name[] = "ROTARY_LOWTIME";
char EffectType__12__Parameter__15__name[] = "ROTARY_HIGHTIME";
char EffectType__12__Parameter__16__name[] = "ROTARY_LFWIDTH";
char EffectType__12__Parameter__17__name[] = "ROTARY_DRIVE";
char EffectType__13__Parameter__0__name[] = "PHASER_TYPE";
char EffectType__13__Parameter__1__name[] = "PHASER_ORDER";
char EffectType__13__Parameter__2__name[] = "PHASER_RATE";
char EffectType__13__Parameter__3__name[] = "PHASER_LFOTYPE";
char EffectType__13__Parameter__4__name[] = "PHASER_TEMPO";
char EffectType__13__Parameter__5__name[] = "PHASER_DEPTH";
char EffectType__13__Parameter__6__name[] = "PHASER_FEEDBACK";
char EffectType__13__Parameter__7__name[] = "PHASER_FSTART";
char EffectType__13__Parameter__8__name[] = "PHASER_FSPAN";
char EffectType__13__Parameter__9__name[] = "PHASER_LFOPHASE";
char EffectType__13__Parameter__10__name[] = "PHASER_BIAS";
char EffectType__13__Parameter__11__name[] = "PHASER_MIX";
char EffectType__13__Parameter__12__name[] = "PHASER_LEVEL";
char EffectType__13__Parameter__13__name[] = "PHASER_PAN";
char EffectType__13__Parameter__14__name[] = "PHASER_BYPASSMODE";
char EffectType__13__Parameter__15__name[] = "PHASER_GLOBALMIX";
char EffectType__13__Parameter__16__name[] = "PHASER_BYPASS";
char EffectType__13__Parameter__17__name[] = "PHASER_MODE";
char EffectType__13__Parameter__18__name[] = "PHASER_FBTAP";
char EffectType__13__Parameter__19__name[] = "PHASER_TONE";
char EffectType__14__Parameter__0__name[] = "WAH_TYPE";
char EffectType__14__Parameter__1__name[] = "WAH_FSTART";
char EffectType__14__Parameter__2__name[] = "WAH_FSTOP";
char EffectType__14__Parameter__3__name[] = "WAH_Q";
char EffectType__14__Parameter__4__name[] = "WAH_TRACK";
char EffectType__14__Parameter__5__name[] = "WAH_FREQ";
char EffectType__14__Parameter__6__name[] = "WAH_LEVEL";
char EffectType__14__Parameter__7__name[] = "WAH_PAN";
char EffectType__14__Parameter__8__name[] = "WAH_BYPASSMODE";
char EffectType__14__Parameter__9__name[] = "WAH_GLOBALMIX";
char EffectType__14__Parameter__10__name[] = "WAH_DRIVE";
char EffectType__14__Parameter__11__name[] = "WAH_SPARE2";
char EffectType__14__Parameter__12__name[] = "WAH_BYPASS";
char EffectType__15__Parameter__0__name[] = "FORMANT_FSTART";
char EffectType__15__Parameter__1__name[] = "FORMANT_FMID";
char EffectType__15__Parameter__2__name[] = "FORMANT_FEND";
char EffectType__15__Parameter__3__name[] = "FORMANT_Q";
char EffectType__15__Parameter__4__name[] = "FORMANT_CTRL";
char EffectType__15__Parameter__5__name[] = "FORMANT_MIX";
char EffectType__15__Parameter__6__name[] = "FORMANT_LEVEL";
char EffectType__15__Parameter__7__name[] = "FORMANT_PAN";
char EffectType__15__Parameter__8__name[] = "FORMANT_BYPASSMODE";
char EffectType__15__Parameter__9__name[] = "FORMANT_GLOBALMIX";
char EffectType__15__Parameter__10__name[] = "FORMANT_SPARE";
char EffectType__15__Parameter__11__name[] = "FORMANT_BYPASS";
char EffectType__16__Parameter__0__name[] = "TREMOLO_TYPE";
char EffectType__16__Parameter__1__name[] = "TREMOLO_LFOTYPE";
char EffectType__16__Parameter__2__name[] = "TREMOLO_RATE";
char EffectType__16__Parameter__3__name[] = "TREMOLO_DEPTH";
char EffectType__16__Parameter__4__name[] = "TREMOLO_DUTY";
char EffectType__16__Parameter__5__name[] = "TREMOLO_TEMPO";
char EffectType__16__Parameter__6__name[] = "TREMOLO_MIX";
char EffectType__16__Parameter__7__name[] = "TREMOLO_LEVEL";
char EffectType__16__Parameter__8__name[] = "TREMOLO_PAN";
char EffectType__16__Parameter__9__name[] = "TREMOLO_BYPASSMODE";
char EffectType__16__Parameter__10__name[] = "TREMOLO_GLOBALMIX";
char EffectType__16__Parameter__11__name[] = "TREMOLO_PHASE";
char EffectType__16__Parameter__12__name[] = "TREMOLO_WIDTH";
char EffectType__16__Parameter__13__name[] = "TREMOLO_CENTER";
char EffectType__16__Parameter__14__name[] = "TREMOLO_BYPASS";
char EffectType__17__Parameter__0__name[] = "PITCH_TYPE";
char EffectType__17__Parameter__1__name[] = "PITCH_PITCHMODE";
char EffectType__17__Parameter__2__name[] = "PITCH_CTRL";
char EffectType__17__Parameter__3__name[] = "PITCH_UCTRL";
char EffectType__17__Parameter__4__name[] = "PITCH_HARM1";
char EffectType__17__Parameter__5__name[] = "PITCH_HARM2";
char EffectType__17__Parameter__6__name[] = "PITCH_KEY";
char EffectType__17__Parameter__7__name[] = "PITCH_SCALE";
char EffectType__17__Parameter__8__name[] = "PITCH_MODE";
char EffectType__17__Parameter__9__name[] = "PITCH_DETUNE1";
char EffectType__17__Parameter__10__name[] = "PITCH_DETUNE2";
char EffectType__17__Parameter__11__name[] = "PITCH_SHIFT1";
char EffectType__17__Parameter__12__name[] = "PITCH_SHIFT2";
char EffectType__17__Parameter__13__name[] = "PITCH_LEVEL1";
char EffectType__17__Parameter__14__name[] = "PITCH_LEVEL2";
char EffectType__17__Parameter__15__name[] = "PITCH_PAN1";
char EffectType__17__Parameter__16__name[] = "PITCH_PAN2";
char EffectType__17__Parameter__17__name[] = "PITCH_DELAY1";
char EffectType__17__Parameter__18__name[] = "PITCH_DELAY2";
char EffectType__17__Parameter__19__name[] = "PITCH_FEEDBACK1";
char EffectType__17__Parameter__20__name[] = "PITCH_FEEDBACK2";
char EffectType__17__Parameter__21__name[] = "PITCH_TRACKMODE";
char EffectType__17__Parameter__22__name[] = "PITCH_TRACKING";
char EffectType__17__Parameter__23__name[] = "PITCH_MIX";
char EffectType__17__Parameter__24__name[] = "PITCH_LEVEL";
char EffectType__17__Parameter__25__name[] = "PITCH_PAN";
char EffectType__17__Parameter__26__name[] = "PITCH_BYPASSMODE";
char EffectType__17__Parameter__27__name[] = "PITCH_GLOBALMIX";
char EffectType__17__Parameter__28__name[] = "PITCH_GAIN";
char EffectType__17__Parameter__29__name[] = "PITCH_BYPASS";
char EffectType__17__Parameter__30__name[] = "PITCH_XFADE";
char EffectType__17__Parameter__31__name[] = "PITCH_SPLICE1";
char EffectType__17__Parameter__32__name[] = "PITCH_SPLICE2";
char EffectType__17__Parameter__33__name[] = "PITCH_DTEMPO1";
char EffectType__17__Parameter__34__name[] = "PITCH_DTEMPO2";
char EffectType__17__Parameter__35__name[] = "PITCH_STEMPO1";
char EffectType__17__Parameter__36__name[] = "PITCH_STEMPO2";
char EffectType__17__Parameter__37__name[] = "PITCH_FBTYPE";
char EffectType__17__Parameter__38__name[] = "PITCH_DIRECTION";
char EffectType__17__Parameter__39__name[] = "PITCH_LPFREQ";
char EffectType__17__Parameter__40__name[] = "PITCH_GLIDE";
char EffectType__17__Parameter__41__name[] = "PITCH_MDELAY";
char EffectType__17__Parameter__42__name[] = "PITCH_MFDBK";
char EffectType__17__Parameter__43__name[] = "PITCH_MPAN";
char EffectType__17__Parameter__44__name[] = "PITCH_MLEVEL";
char EffectType__17__Parameter__45__name[] = "PITCH_CUSTOMNOTE";
char EffectType__17__Parameter__46__name[] = "PITCH_NOTE2";
char EffectType__17__Parameter__47__name[] = "PITCH_NOTE3";
char EffectType__17__Parameter__48__name[] = "PITCH_NOTE4";
char EffectType__17__Parameter__49__name[] = "PITCH_NOTE5";
char EffectType__17__Parameter__50__name[] = "PITCH_NOTE6";
char EffectType__17__Parameter__51__name[] = "PITCH_NOTE7";
char EffectType__17__Parameter__52__name[] = "PITCH_NOTE8";
char EffectType__17__Parameter__53__name[] = "PITCH_CUSTOMSCALE1";
char EffectType__17__Parameter__54__name[] = "PITCH_CUSTOMSCALE2";
char EffectType__17__Parameter__55__name[] = "PITCH_NUMSTEPS";
char EffectType__17__Parameter__56__name[] = "PITCH_NUMREPEATS";
char EffectType__17__Parameter__57__name[] = "PITCH_ARPRUN";
char EffectType__17__Parameter__58__name[] = "PITCH_TEMPO";
char EffectType__17__Parameter__59__name[] = "PITCH_STEP1";
char EffectType__17__Parameter__60__name[] = "PITCH_STEP2";
char EffectType__17__Parameter__61__name[] = "PITCH_STEP3";
char EffectType__17__Parameter__62__name[] = "PITCH_STEP4";
char EffectType__17__Parameter__63__name[] = "PITCH_STEP5";
char EffectType__17__Parameter__64__name[] = "PITCH_STEP6";
char EffectType__17__Parameter__65__name[] = "PITCH_STEP7";
char EffectType__17__Parameter__66__name[] = "PITCH_STEP8";
char EffectType__17__Parameter__67__name[] = "PITCH_STEP9";
char EffectType__17__Parameter__68__name[] = "PITCH_STEP10";
char EffectType__17__Parameter__69__name[] = "PITCH_STEP11";
char EffectType__17__Parameter__70__name[] = "PITCH_STEP12";
char EffectType__17__Parameter__71__name[] = "PITCH_STEP13";
char EffectType__17__Parameter__72__name[] = "PITCH_STEP14";
char EffectType__17__Parameter__73__name[] = "PITCH_STEP15";
char EffectType__17__Parameter__74__name[] = "PITCH_STEP16";
char EffectType__17__Parameter__75__name[] = "PITCH_AMPSHAPE";
char EffectType__17__Parameter__76__name[] = "PITCH_AMPALPHA";
char EffectType__17__Parameter__77__name[] = "PITCH_PANSHAPE";
char EffectType__17__Parameter__78__name[] = "PITCH_PANALPHA";
char EffectType__17__Parameter__79__name[] = "PITCH_TIME1";
char EffectType__17__Parameter__80__name[] = "PITCH_TIME2";
char EffectType__17__Parameter__81__name[] = "PITCH_SOURCE";
char EffectType__17__Parameter__82__name[] = "PITCH_INMODE";
char EffectType__17__Parameter__83__name[] = "PITCH_LEARN";
char EffectType__17__Parameter__84__name[] = "PITCH_LOCUT";
char EffectType__18__Parameter__0__name[] = "FILTER_TYPE";
char EffectType__18__Parameter__1__name[] = "FILTER_FREQ";
char EffectType__18__Parameter__2__name[] = "FILTER_Q";
char EffectType__18__Parameter__3__name[] = "FILTER_GAIN";
char EffectType__18__Parameter__4__name[] = "FILTER_LEVEL";
char EffectType__18__Parameter__5__name[] = "FILTER_BAL";
char EffectType__18__Parameter__6__name[] = "FILTER_BYPASSMODE";
char EffectType__18__Parameter__7__name[] = "FILTER_ORDER";
char EffectType__18__Parameter__8__name[] = "FILTER_BYPASS";
char EffectType__18__Parameter__9__name[] = "FILTER_PANL";
char EffectType__18__Parameter__10__name[] = "FILTER_PANR";
char EffectType__18__Parameter__11__name[] = "FILTER_PHASE";
char EffectType__18__Parameter__12__name[] = "FILTER_LOWCUT";
char EffectType__18__Parameter__13__name[] = "FILTER_HICUT";
char EffectType__19__Parameter__0__name[] = "FUZZ_TYPE";
char EffectType__19__Parameter__1__name[] = "FUZZ_DRIVE";
char EffectType__19__Parameter__2__name[] = "FUZZ_TONE";
char EffectType__19__Parameter__3__name[] = "FUZZ_LEVEL";
char EffectType__19__Parameter__4__name[] = "FUZZ_MIX";
char EffectType__19__Parameter__5__name[] = "FUZZ_BYPASSMODE";
char EffectType__19__Parameter__6__name[] = "FUZZ_SLEW";
char EffectType__19__Parameter__7__name[] = "FUZZ_BYPASS";
char EffectType__19__Parameter__8__name[] = "FUZZ_LOCUT";
char EffectType__19__Parameter__9__name[] = "FUZZ_HICUT";
char EffectType__19__Parameter__10__name[] = "FUZZ_CLIPTYPE";
char EffectType__19__Parameter__11__name[] = "FUZZ_BIAS";
char EffectType__19__Parameter__12__name[] = "FUZZ_BASS";
char EffectType__19__Parameter__13__name[] = "FUZZ_MID";
char EffectType__19__Parameter__14__name[] = "FUZZ_MIDFREQ";
char EffectType__19__Parameter__15__name[] = "FUZZ_TREBLE";
char EffectType__19__Parameter__16__name[] = "FUZZ_BITREDUCE";
char EffectType__19__Parameter__17__name[] = "FUZZ_INPUTSELECT";
char EffectType__19__Parameter__18__name[] = "FUZZ_PAN";
char EffectType__19__Parameter__19__name[] = "FUZZ_RESAMPLE";
char EffectType__20__Parameter__0__name[] = "ENHANCER_WIDTH";
char EffectType__20__Parameter__1__name[] = "ENHANCER_DEPTH";
char EffectType__20__Parameter__2__name[] = "ENHANCER_LOWCUT";
char EffectType__20__Parameter__3__name[] = "ENHANCER_HICUT";
char EffectType__20__Parameter__4__name[] = "ENHANCER_LEVEL";
char EffectType__20__Parameter__5__name[] = "ENHANCER_BYPASS";
char EffectType__20__Parameter__6__name[] = "ENHANCER_TYPE";
char EffectType__20__Parameter__7__name[] = "ENHANCER_INVERT";
char EffectType__20__Parameter__8__name[] = "ENHANCER_PANL";
char EffectType__20__Parameter__9__name[] = "ENHANCER_PANR";
char EffectType__20__Parameter__10__name[] = "ENHANCER_BALANCE";
char EffectType__21__Parameter__0__name[] = "LOOP_LEVEL1";
char EffectType__21__Parameter__1__name[] = "LOOP_LEVEL2";
char EffectType__21__Parameter__2__name[] = "LOOP_LEVEL3";
char EffectType__21__Parameter__3__name[] = "LOOP_LEVEL4";
char EffectType__21__Parameter__4__name[] = "LOOP_PAN1";
char EffectType__21__Parameter__5__name[] = "LOOP_PAN2";
char EffectType__21__Parameter__6__name[] = "LOOP_PAN3";
char EffectType__21__Parameter__7__name[] = "LOOP_PAN4";
char EffectType__21__Parameter__8__name[] = "LOOP_MAIN1";
char EffectType__21__Parameter__9__name[] = "LOOP_MAIN2";
char EffectType__21__Parameter__10__name[] = "LOOP_MAIN3";
char EffectType__21__Parameter__11__name[] = "LOOP_MAIN4";
char EffectType__21__Parameter__12__name[] = "LOOP_MAIN5";
char EffectType__21__Parameter__13__name[] = "LOOP_MAIN6";
char EffectType__21__Parameter__14__name[] = "LOOP_MAIN7";
char EffectType__21__Parameter__15__name[] = "LOOP_MAIN8";
char EffectType__21__Parameter__16__name[] = "LOOP_LEVEL";
char EffectType__21__Parameter__17__name[] = "LOOP_PAN";
char EffectType__21__Parameter__18__name[] = "LOOP_BYPASSMODE";
char EffectType__21__Parameter__19__name[] = "LOOP_BYPASS";
char EffectType__22__Parameter__0__name[] = "MIXER_GAIN1";
char EffectType__22__Parameter__1__name[] = "MIXER_GAIN2";
char EffectType__22__Parameter__2__name[] = "MIXER_GAIN3";
char EffectType__22__Parameter__3__name[] = "MIXER_GAIN4";
char EffectType__22__Parameter__4__name[] = "MIXER_PAN1";
char EffectType__22__Parameter__5__name[] = "MIXER_PAN2";
char EffectType__22__Parameter__6__name[] = "MIXER_PAN3";
char EffectType__22__Parameter__7__name[] = "MIXER_PAN4";
char EffectType__22__Parameter__8__name[] = "MIXER_MASTER";
char EffectType__22__Parameter__9__name[] = "MIXER_MODE";
char EffectType__23__Parameter__0__name[] = "FBSEND_LEVEL";
char EffectType__23__Parameter__1__name[] = "FBSEND_OUTPUT";
char EffectType__24__Parameter__0__name[] = "FEEDBACK_MIX";
char EffectType__24__Parameter__1__name[] = "FEEDBACK_LEVEL";
char EffectType__24__Parameter__2__name[] = "FEEDBACK_PAN";
char EffectType__24__Parameter__3__name[] = "FEEDBACK_BYPASSMODE";
char EffectType__24__Parameter__4__name[] = "FEEDBACK_GLOBALMIX";
char EffectType__24__Parameter__5__name[] = "FEEDBACK_BYPASS";
char EffectType__25__Parameter__0__name[] = "SYNTH_TYPE1";
char EffectType__25__Parameter__1__name[] = "SYNTH_FREQ1";
char EffectType__25__Parameter__2__name[] = "SYNTH_TRACK1";
char EffectType__25__Parameter__3__name[] = "SYNTH_SHIFT1";
char EffectType__25__Parameter__4__name[] = "SYNTH_DETUNE1";
char EffectType__25__Parameter__5__name[] = "SYNTH_DUTY1";
char EffectType__25__Parameter__6__name[] = "SYNTH_LEVEL1";
char EffectType__25__Parameter__7__name[] = "SYNTH_PAN1";
char EffectType__25__Parameter__8__name[] = "SYNTH_ATTACK1";
char EffectType__25__Parameter__9__name[] = "SYNTH_HICUT1";
char EffectType__25__Parameter__10__name[] = "SYNTH_Q1";
char EffectType__25__Parameter__11__name[] = "SYNTH_TYPE2";
char EffectType__25__Parameter__12__name[] = "SYNTH_FREQ2";
char EffectType__25__Parameter__13__name[] = "SYNTH_TRACK2";
char EffectType__25__Parameter__14__name[] = "SYNTH_SHIFT2";
char EffectType__25__Parameter__15__name[] = "SYNTH_DETUNE2";
char EffectType__25__Parameter__16__name[] = "SYNTH_DUTY2";
char EffectType__25__Parameter__17__name[] = "SYNTH_LEVEL2";
char EffectType__25__Parameter__18__name[] = "SYNTH_PAN2";
char EffectType__25__Parameter__19__name[] = "SYNTH_ATTACK2";
char EffectType__25__Parameter__20__name[] = "SYNTH_HICUT2";
char EffectType__25__Parameter__21__name[] = "SYNTH_Q2";
char EffectType__25__Parameter__22__name[] = "SYNTH_SPARE1";
char EffectType__25__Parameter__23__name[] = "SYNTH_MIX";
char EffectType__25__Parameter__24__name[] = "SYNTH_LEVEL";
char EffectType__25__Parameter__25__name[] = "SYNTH_PAN";
char EffectType__25__Parameter__26__name[] = "SYNTH_BYPASSMODE";
char EffectType__25__Parameter__27__name[] = "SYNTH_GLOBALMIX";
char EffectType__25__Parameter__28__name[] = "SYNTH_BYPASS";
char EffectType__25__Parameter__29__name[] = "SYNTH_TYPE3";
char EffectType__25__Parameter__30__name[] = "SYNTH_FREQ3";
char EffectType__25__Parameter__31__name[] = "SYNTH_TRACK3";
char EffectType__25__Parameter__32__name[] = "SYNTH_SHIFT3";
char EffectType__25__Parameter__33__name[] = "SYNTH_DETUNE3";
char EffectType__25__Parameter__34__name[] = "SYNTH_DUTY3";
char EffectType__25__Parameter__35__name[] = "SYNTH_LEVEL3";
char EffectType__25__Parameter__36__name[] = "SYNTH_PAN3";
char EffectType__25__Parameter__37__name[] = "SYNTH_ATTACK3";
char EffectType__25__Parameter__38__name[] = "SYNTH_HICUT3";
char EffectType__25__Parameter__39__name[] = "SYNTH_Q3";
char EffectType__26__Parameter__0__name[] = "VOCODER_INSOURCE";
char EffectType__26__Parameter__1__name[] = "VOCODER_NUMBANDS";
char EffectType__26__Parameter__2__name[] = "VOCODER_FREQSTART";
char EffectType__26__Parameter__3__name[] = "VOCODER_FREQSTOP";
char EffectType__26__Parameter__4__name[] = "VOCODER_CSHIFT";
char EffectType__26__Parameter__5__name[] = "VOCODER_FREEZE";
char EffectType__26__Parameter__6__name[] = "VOCODER_MASTERLVL";
char EffectType__26__Parameter__7__name[] = "VOCODER_MASTERPAN";
char EffectType__26__Parameter__8__name[] = "VOCODER_RES";
char EffectType__26__Parameter__9__name[] = "VOCODER_ATTACK";
char EffectType__26__Parameter__10__name[] = "VOCODER_RELEASE";
char EffectType__26__Parameter__11__name[] = "VOCODER_HPMIX";
char EffectType__26__Parameter__12__name[] = "VOCODER_MIX";
char EffectType__26__Parameter__13__name[] = "VOCODER_LEVEL";
char EffectType__26__Parameter__14__name[] = "VOCODER_PAN";
char EffectType__26__Parameter__15__name[] = "VOCODER_BYPASSMODE";
char EffectType__26__Parameter__16__name[] = "VOCODER_GLOBALMIX";
char EffectType__26__Parameter__17__name[] = "VOCODER_LEVEL1";
char EffectType__26__Parameter__18__name[] = "VOCODER_LEVEL2";
char EffectType__26__Parameter__19__name[] = "VOCODER_LEVEL3";
char EffectType__26__Parameter__20__name[] = "VOCODER_LEVEL4";
char EffectType__26__Parameter__21__name[] = "VOCODER_LEVEL5";
char EffectType__26__Parameter__22__name[] = "VOCODER_LEVEL6";
char EffectType__26__Parameter__23__name[] = "VOCODER_LEVEL7";
char EffectType__26__Parameter__24__name[] = "VOCODER_LEVEL8";
char EffectType__26__Parameter__25__name[] = "VOCODER_LEVEL9";
char EffectType__26__Parameter__26__name[] = "VOCODER_LEVEL10";
char EffectType__26__Parameter__27__name[] = "VOCODER_LEVEL11";
char EffectType__26__Parameter__28__name[] = "VOCODER_LEVEL12";
char EffectType__26__Parameter__29__name[] = "VOCODER_LEVEL13";
char EffectType__26__Parameter__30__name[] = "VOCODER_LEVEL14";
char EffectType__26__Parameter__31__name[] = "VOCODER_LEVEL15";
char EffectType__26__Parameter__32__name[] = "VOCODER_LEVEL16";
char EffectType__26__Parameter__33__name[] = "VOCODER_PAN1";
char EffectType__26__Parameter__34__name[] = "VOCODER_PAN2";
char EffectType__26__Parameter__35__name[] = "VOCODER_PAN3";
char EffectType__26__Parameter__36__name[] = "VOCODER_PAN4";
char EffectType__26__Parameter__37__name[] = "VOCODER_PAN5";
char EffectType__26__Parameter__38__name[] = "VOCODER_PAN6";
char EffectType__26__Parameter__39__name[] = "VOCODER_PAN7";
char EffectType__26__Parameter__40__name[] = "VOCODER_PAN8";
char EffectType__26__Parameter__41__name[] = "VOCODER_PAN9";
char EffectType__26__Parameter__42__name[] = "VOCODER_PAN10";
char EffectType__26__Parameter__43__name[] = "VOCODER_PAN11";
char EffectType__26__Parameter__44__name[] = "VOCODER_PAN12";
char EffectType__26__Parameter__45__name[] = "VOCODER_PAN13";
char EffectType__26__Parameter__46__name[] = "VOCODER_PAN14";
char EffectType__26__Parameter__47__name[] = "VOCODER_PAN15";
char EffectType__26__Parameter__48__name[] = "VOCODER_PAN16";
char EffectType__26__Parameter__49__name[] = "VOCODER_BYPASS";
char EffectType__27__Parameter__0__name[] = "MEGATAP_INGAIN";
char EffectType__27__Parameter__1__name[] = "MEGATAP_MASTERLVL";
char EffectType__27__Parameter__2__name[] = "MEGATAP_TIME";
char EffectType__27__Parameter__3__name[] = "MEGATAP_NUMTAPS";
char EffectType__27__Parameter__4__name[] = "MEGATAP_TIMESHAPE";
char EffectType__27__Parameter__5__name[] = "MEGATAP_TIMEALPHA";
char EffectType__27__Parameter__6__name[] = "MEGATAP_AMPSHAPE";
char EffectType__27__Parameter__7__name[] = "MEGATAP_AMPALPHA";
char EffectType__27__Parameter__8__name[] = "MEGATAP_PANSHAPE";
char EffectType__27__Parameter__9__name[] = "MEGATAP_PANALPHA";
char EffectType__27__Parameter__10__name[] = "MEGATAP_RANDOM";
char EffectType__27__Parameter__11__name[] = "MEGATAP_MIX";
char EffectType__27__Parameter__12__name[] = "MEGATAP_LEVEL";
char EffectType__27__Parameter__13__name[] = "MEGATAP_PAN";
char EffectType__27__Parameter__14__name[] = "MEGATAP_BYPASSMODE";
char EffectType__27__Parameter__15__name[] = "MEGATAP_GLOBALMIX";
char EffectType__27__Parameter__16__name[] = "MEGATAP_BYPASS";
char EffectType__28__Parameter__0__name[] = "CROSSOVER_FREQ";
char EffectType__28__Parameter__1__name[] = "CROSSOVER_FREQRANGE";
char EffectType__28__Parameter__2__name[] = "CROSSOVER_LOWGAINL";
char EffectType__28__Parameter__3__name[] = "CROSSOVER_HIGAINL";
char EffectType__28__Parameter__4__name[] = "CROSSOVER_LOWGAINR";
char EffectType__28__Parameter__5__name[] = "CROSSOVER_HIGAINR";
char EffectType__28__Parameter__6__name[] = "CROSSOVER_LOWPANL";
char EffectType__28__Parameter__7__name[] = "CROSSOVER_HIPANL";
char EffectType__28__Parameter__8__name[] = "CROSSOVER_LOWPANR";
char EffectType__28__Parameter__9__name[] = "CROSSOVER_HIPANR";
char EffectType__28__Parameter__10__name[] = "CROSSOVER_MIX";
char EffectType__28__Parameter__11__name[] = "CROSSOVER_LEVEL";
char EffectType__28__Parameter__12__name[] = "CROSSOVER_PAN";
char EffectType__28__Parameter__13__name[] = "CROSSOVER_BYPASSMODE";
char EffectType__28__Parameter__14__name[] = "CROSSOVER_BYPASS";
char EffectType__29__Parameter__0__name[] = "GATE_THRESH";
char EffectType__29__Parameter__1__name[] = "GATE_ATTACK";
char EffectType__29__Parameter__2__name[] = "GATE_HOLD";
char EffectType__29__Parameter__3__name[] = "GATE_RELEASE";
char EffectType__29__Parameter__4__name[] = "GATE_RATIO";
char EffectType__29__Parameter__5__name[] = "GATE_KEY";
char EffectType__29__Parameter__6__name[] = "GATE_LOWCUT";
char EffectType__29__Parameter__7__name[] = "GATE_HICUT";
char EffectType__29__Parameter__8__name[] = "GATE_MIX";
char EffectType__29__Parameter__9__name[] = "GATE_LEVEL";
char EffectType__29__Parameter__10__name[] = "GATE_PAN";
char EffectType__29__Parameter__11__name[] = "GATE_BYPASSMODE";
char EffectType__29__Parameter__12__name[] = "GATE_BYPASS";
char EffectType__30__Parameter__0__name[] = "RINGMOD_COARSE";
char EffectType__30__Parameter__1__name[] = "RINGMOD_FINE";
char EffectType__30__Parameter__2__name[] = "RINGMOD_TRACK";
char EffectType__30__Parameter__3__name[] = "RINGMOD_LOWCUT";
char EffectType__30__Parameter__4__name[] = "RINGMOD_MIX";
char EffectType__30__Parameter__5__name[] = "RINGMOD_LEVEL";
char EffectType__30__Parameter__6__name[] = "RINGMOD_PAN";
char EffectType__30__Parameter__7__name[] = "RINGMOD_BYPASSMODE";
char EffectType__30__Parameter__8__name[] = "RINGMOD_GLOBALMIX";
char EffectType__30__Parameter__9__name[] = "RINGMOD_BYPASS";
char EffectType__31__Parameter__0__name[] = "MULTICOMP_FREQ1";
char EffectType__31__Parameter__1__name[] = "MULTICOMP_FREQ2";
char EffectType__31__Parameter__2__name[] = "MULTICOMP_THRESH1";
char EffectType__31__Parameter__3__name[] = "MULTICOMP_RATIO1";
char EffectType__31__Parameter__4__name[] = "MULTICOMP_ATTACK1";
char EffectType__31__Parameter__5__name[] = "MULTICOMP_RELEASE1";
char EffectType__31__Parameter__6__name[] = "MULTICOMP_LEVEL1";
char EffectType__31__Parameter__7__name[] = "MULTICOMP_DETECT1";
char EffectType__31__Parameter__8__name[] = "MULTICOMP_MUTE1";
char EffectType__31__Parameter__9__name[] = "MULTICOMP_THRESH2";
char EffectType__31__Parameter__10__name[] = "MULTICOMP_RATIO2";
char EffectType__31__Parameter__11__name[] = "MULTICOMP_ATTACK2";
char EffectType__31__Parameter__12__name[] = "MULTICOMP_RELEASE2";
char EffectType__31__Parameter__13__name[] = "MULTICOMP_LEVEL2";
char EffectType__31__Parameter__14__name[] = "MULTICOMP_DETECT2";
char EffectType__31__Parameter__15__name[] = "MULTICOMP_MUTE2";
char EffectType__31__Parameter__16__name[] = "MULTICOMP_THRESH3";
char EffectType__31__Parameter__17__name[] = "MULTICOMP_RATIO3";
char EffectType__31__Parameter__18__name[] = "MULTICOMP_ATTACK3";
char EffectType__31__Parameter__19__name[] = "MULTICOMP_RELEASE3";
char EffectType__31__Parameter__20__name[] = "MULTICOMP_LEVEL3";
char EffectType__31__Parameter__21__name[] = "MULTICOMP_DETECT3";
char EffectType__31__Parameter__22__name[] = "MULTICOMP_MUTE3";
char EffectType__31__Parameter__23__name[] = "MULTICOMP_MIX";
char EffectType__31__Parameter__24__name[] = "MULTICOMP_LEVEL";
char EffectType__31__Parameter__25__name[] = "MULTICOMP_PAN";
char EffectType__31__Parameter__26__name[] = "MULTICOMP_BYPASSMODE";
char EffectType__31__Parameter__27__name[] = "MULTICOMP_BYPASS";
char EffectType__32__Parameter__0__name[] = "QUADCHO_MASTERTIME";
char EffectType__32__Parameter__1__name[] = "QUADCHO_MASTERLVL";
char EffectType__32__Parameter__2__name[] = "QUADCHO_MASTERPAN";
char EffectType__32__Parameter__3__name[] = "QUADCHO_MASTERRATE";
char EffectType__32__Parameter__4__name[] = "QUADCHO_MASTERDEPTH";
char EffectType__32__Parameter__5__name[] = "QUADCHO_MASTERFDBK";
char EffectType__32__Parameter__6__name[] = "QUADCHO_TIME1";
char EffectType__32__Parameter__7__name[] = "QUADCHO_TIME2";
char EffectType__32__Parameter__8__name[] = "QUADCHO_TIME3";
char EffectType__32__Parameter__9__name[] = "QUADCHO_TIME4";
char EffectType__32__Parameter__10__name[] = "QUADCHO_LEVEL1";
char EffectType__32__Parameter__11__name[] = "QUADCHO_LEVEL2";
char EffectType__32__Parameter__12__name[] = "QUADCHO_LEVEL3";
char EffectType__32__Parameter__13__name[] = "QUADCHO_LEVEL4";
char EffectType__32__Parameter__14__name[] = "QUADCHO_PAN1";
char EffectType__32__Parameter__15__name[] = "QUADCHO_PAN2";
char EffectType__32__Parameter__16__name[] = "QUADCHO_PAN3";
char EffectType__32__Parameter__17__name[] = "QUADCHO_PAN4";
char EffectType__32__Parameter__18__name[] = "QUADCHO_DEPTH1";
char EffectType__32__Parameter__19__name[] = "QUADCHO_DEPTH2";
char EffectType__32__Parameter__20__name[] = "QUADCHO_DEPTH3";
char EffectType__32__Parameter__21__name[] = "QUADCHO_DEPTH4";
char EffectType__32__Parameter__22__name[] = "QUADCHO_MORPH1";
char EffectType__32__Parameter__23__name[] = "QUADCHO_MORPH2";
char EffectType__32__Parameter__24__name[] = "QUADCHO_MORPH3";
char EffectType__32__Parameter__25__name[] = "QUADCHO_MORPH4";
char EffectType__32__Parameter__26__name[] = "QUADCHO_TYPE1";
char EffectType__32__Parameter__27__name[] = "QUADCHO_TYPE2";
char EffectType__32__Parameter__28__name[] = "QUADCHO_TYPE3";
char EffectType__32__Parameter__29__name[] = "QUADCHO_TYPE4";
char EffectType__32__Parameter__30__name[] = "QUADCHO_RATE1";
char EffectType__32__Parameter__31__name[] = "QUADCHO_RATE2";
char EffectType__32__Parameter__32__name[] = "QUADCHO_RATE3";
char EffectType__32__Parameter__33__name[] = "QUADCHO_RATE4";
char EffectType__32__Parameter__34__name[] = "QUADCHO_MDEPTH";
char EffectType__32__Parameter__35__name[] = "QUADCHO_MODE";
char EffectType__32__Parameter__36__name[] = "QUADCHO_LFOLOCK";
char EffectType__32__Parameter__37__name[] = "QUADCHO_WIDE";
char EffectType__32__Parameter__38__name[] = "QUADCHO_PHASE";
char EffectType__32__Parameter__39__name[] = "QUADCHO_MIX";
char EffectType__32__Parameter__40__name[] = "QUADCHO_LEVEL";
char EffectType__32__Parameter__41__name[] = "QUADCHO_PAN";
char EffectType__32__Parameter__42__name[] = "QUADCHO_BYPASSMODE";
char EffectType__32__Parameter__43__name[] = "QUADCHO_GLOBALMIX";
char EffectType__32__Parameter__44__name[] = "QUADCHO_BYPASS";
char EffectType__32__Parameter__45__name[] = "QUADCHO_HICUT";
char EffectType__33__Parameter__0__name[] = "RESONATOR_MODE";
char EffectType__33__Parameter__1__name[] = "RESONATOR_CHORD";
char EffectType__33__Parameter__2__name[] = "RESONATOR_INGAIN";
char EffectType__33__Parameter__3__name[] = "RESONATOR_FREQ";
char EffectType__33__Parameter__4__name[] = "RESONATOR_MASTERFREQ";
char EffectType__33__Parameter__5__name[] = "RESONATOR_MASTERLVL";
char EffectType__33__Parameter__6__name[] = "RESONATOR_MASTERPAN";
char EffectType__33__Parameter__7__name[] = "RESONATOR_MASTERFDBK";
char EffectType__33__Parameter__8__name[] = "RESONATOR_MASTERQ";
char EffectType__33__Parameter__9__name[] = "RESONATOR_FREQ1";
char EffectType__33__Parameter__10__name[] = "RESONATOR_FREQ2";
char EffectType__33__Parameter__11__name[] = "RESONATOR_FREQ3";
char EffectType__33__Parameter__12__name[] = "RESONATOR_FREQ4";
char EffectType__33__Parameter__13__name[] = "RESONATOR_FDBK1";
char EffectType__33__Parameter__14__name[] = "RESONATOR_FDBK2";
char EffectType__33__Parameter__15__name[] = "RESONATOR_FDBK3";
char EffectType__33__Parameter__16__name[] = "RESONATOR_FDBK4";
char EffectType__33__Parameter__17__name[] = "RESONATOR_LOC1";
char EffectType__33__Parameter__18__name[] = "RESONATOR_LOC2";
char EffectType__33__Parameter__19__name[] = "RESONATOR_LOC3";
char EffectType__33__Parameter__20__name[] = "RESONATOR_LOC4";
char EffectType__33__Parameter__21__name[] = "RESONATOR_Q1";
char EffectType__33__Parameter__22__name[] = "RESONATOR_Q2";
char EffectType__33__Parameter__23__name[] = "RESONATOR_Q3";
char EffectType__33__Parameter__24__name[] = "RESONATOR_Q4";
char EffectType__33__Parameter__25__name[] = "RESONATOR_LEVEL1";
char EffectType__33__Parameter__26__name[] = "RESONATOR_LEVEL2";
char EffectType__33__Parameter__27__name[] = "RESONATOR_LEVEL3";
char EffectType__33__Parameter__28__name[] = "RESONATOR_LEVEL4";
char EffectType__33__Parameter__29__name[] = "RESONATOR_PAN1";
char EffectType__33__Parameter__30__name[] = "RESONATOR_PAN2";
char EffectType__33__Parameter__31__name[] = "RESONATOR_PAN3";
char EffectType__33__Parameter__32__name[] = "RESONATOR_PAN4";
char EffectType__33__Parameter__33__name[] = "RESONATOR_MIX";
char EffectType__33__Parameter__34__name[] = "RESONATOR_LEVEL";
char EffectType__33__Parameter__35__name[] = "RESONATOR_PAN";
char EffectType__33__Parameter__36__name[] = "RESONATOR_BYPASSMODE";
char EffectType__33__Parameter__37__name[] = "RESONATOR_GLOBALMIX";
char EffectType__33__Parameter__38__name[] = "RESONATOR_BYPASS";
char EffectType__33__Parameter__39__name[] = "RESONATOR_INPUTMODE";
char EffectType__34__Parameter__0__name[] = "VOLUME_GAIN";
char EffectType__34__Parameter__1__name[] = "VOLUME_BAL";
char EffectType__34__Parameter__2__name[] = "VOLUME_TAPER";
char EffectType__34__Parameter__3__name[] = "VOLUME_BYPASS";
char EffectType__34__Parameter__4__name[] = "VOLUME_PANL";
char EffectType__34__Parameter__5__name[] = "VOLUME_PANR";
char EffectType__34__Parameter__6__name[] = "VOLUME_LEVEL";
char EffectType__34__Parameter__7__name[] = "VOLUME_BYPASSMODE";
char EffectType__34__Parameter__8__name[] = "VOLUME_INPUTMODE";
char EffectType__35__Parameter__0__name[] = "NOISEGATE_THRESH";
char EffectType__35__Parameter__1__name[] = "NOISEGATE_RATIO";
char EffectType__35__Parameter__2__name[] = "NOISEGATE_RELEASE";
char EffectType__35__Parameter__3__name[] = "NOISEGATE_ATTACK";
char EffectType__35__Parameter__4__name[] = "NOISEGATE_Z";
char EffectType__36__Parameter__0__name[] = "OUTPUT_LEVEL1";
char EffectType__36__Parameter__1__name[] = "OUTPUT_LEVEL2";
char EffectType__36__Parameter__2__name[] = "OUTPUT_LEVEL3";
char EffectType__36__Parameter__3__name[] = "OUTPUT_LEVEL4";
char EffectType__36__Parameter__4__name[] = "OUTPUT_PAN1";
char EffectType__36__Parameter__5__name[] = "OUTPUT_PAN2";
char EffectType__36__Parameter__6__name[] = "OUTPUT_PAN3";
char EffectType__36__Parameter__7__name[] = "OUTPUT_PAN4";
char EffectType__36__Parameter__8__name[] = "OUTPUT_MAIN1";
char EffectType__36__Parameter__9__name[] = "OUTPUT_MAIN2";
char EffectType__36__Parameter__10__name[] = "OUTPUT_MAIN3";
char EffectType__36__Parameter__11__name[] = "OUTPUT_MAIN4";
char EffectType__36__Parameter__12__name[] = "OUTPUT_MAIN5";
char EffectType__36__Parameter__13__name[] = "OUTPUT_MAIN6";
char EffectType__36__Parameter__14__name[] = "OUTPUT_MAIN7";
char EffectType__36__Parameter__15__name[] = "OUTPUT_MAIN8";
char EffectType__36__Parameter__16__name[] = "OUTPUT_LEVEL";
char EffectType__36__Parameter__17__name[] = "OUTPUT_PAN";
char EffectType__36__Parameter__18__name[] = "OUTPUT_BYPASSMODE";
char EffectType__36__Parameter__19__name[] = "OUTPUT_BYPASS";
char EffectType__37__Parameter__0__name[] = "CONTROLLERS_LFO1TYPE";
char EffectType__37__Parameter__1__name[] = "CONTROLLERS_LFO1FREQ";
char EffectType__37__Parameter__2__name[] = "CONTROLLERS_LFO1DEPTH";
char EffectType__37__Parameter__3__name[] = "CONTROLLERS_LFO1DUTY";
char EffectType__37__Parameter__4__name[] = "CONTROLLERS_LFO1PHASE";
char EffectType__37__Parameter__5__name[] = "CONTROLLERS_LFO1TEMPO";
char EffectType__37__Parameter__6__name[] = "CONTROLLERS_LFO2TYPE";
char EffectType__37__Parameter__7__name[] = "CONTROLLERS_LFO2FREQ";
char EffectType__37__Parameter__8__name[] = "CONTROLLERS_LFO2DEPTH";
char EffectType__37__Parameter__9__name[] = "CONTROLLERS_LFO2DUTY";
char EffectType__37__Parameter__10__name[] = "CONTROLLERS_LFO2PHASE";
char EffectType__37__Parameter__11__name[] = "CONTROLLERS_LFO2TEMPO";
char EffectType__37__Parameter__12__name[] = "CONTROLLERS_ADSR1MODE";
char EffectType__37__Parameter__13__name[] = "CONTROLLERS_ADSR1RETRIG";
char EffectType__37__Parameter__14__name[] = "CONTROLLERS_ADSR1ATTACK";
char EffectType__37__Parameter__15__name[] = "CONTROLLERS_ADSR1DECAY";
char EffectType__37__Parameter__16__name[] = "CONTROLLERS_ADSR1SUSTAIN";
char EffectType__37__Parameter__17__name[] = "CONTROLLERS_ADSR1LEVEL";
char EffectType__37__Parameter__18__name[] = "CONTROLLERS_ADSR1RELEASE";
char EffectType__37__Parameter__19__name[] = "CONTROLLERS_ADSR1THRESH";
char EffectType__37__Parameter__20__name[] = "CONTROLLERS_ADSR2MODE";
char EffectType__37__Parameter__21__name[] = "CONTROLLERS_ADSR2RETRIG";
char EffectType__37__Parameter__22__name[] = "CONTROLLERS_ADSR2ATTACK";
char EffectType__37__Parameter__23__name[] = "CONTROLLERS_ADSR2DECAY";
char EffectType__37__Parameter__24__name[] = "CONTROLLERS_ADSR2SUSTAIN";
char EffectType__37__Parameter__25__name[] = "CONTROLLERS_ADSR2LEVEL";
char EffectType__37__Parameter__26__name[] = "CONTROLLERS_ADSR2RELEASE";
char EffectType__37__Parameter__27__name[] = "CONTROLLERS_ADSR2THRESH";
char EffectType__37__Parameter__28__name[] = "CONTROLLERS_ENVATTACK";
char EffectType__37__Parameter__29__name[] = "CONTROLLERS_ENVRELEASE";
char EffectType__37__Parameter__30__name[] = "CONTROLLERS_ENVSENS";
char EffectType__37__Parameter__31__name[] = "CONTROLLERS_ENVGAIN";
char EffectType__37__Parameter__32__name[] = "CONTROLLERS_TEMPO";
char EffectType__37__Parameter__33__name[] = "CONTROLLERS_TEMPOTOUSE";
char EffectType__37__Parameter__34__name[] = "CONTROLLERS_SEQFREQ";
char EffectType__37__Parameter__35__name[] = "CONTROLLERS_SEQTEMPO";
char EffectType__37__Parameter__36__name[] = "CONTROLLERS_SEQSTAGES";
char EffectType__37__Parameter__37__name[] = "CONTROLLERS_SEQ1";
char EffectType__37__Parameter__38__name[] = "CONTROLLERS_SEQ2";
char EffectType__37__Parameter__39__name[] = "CONTROLLERS_SEQ3";
char EffectType__37__Parameter__40__name[] = "CONTROLLERS_SEQ4";
char EffectType__37__Parameter__41__name[] = "CONTROLLERS_SEQ5";
char EffectType__37__Parameter__42__name[] = "CONTROLLERS_SEQ6";
char EffectType__37__Parameter__43__name[] = "CONTROLLERS_SEQ7";
char EffectType__37__Parameter__44__name[] = "CONTROLLERS_SEQ8";
char EffectType__37__Parameter__45__name[] = "CONTROLLERS_SEQ9";
char EffectType__37__Parameter__46__name[] = "CONTROLLERS_SEQ10";
char EffectType__37__Parameter__47__name[] = "CONTROLLERS_SEQ11";
char EffectType__37__Parameter__48__name[] = "CONTROLLERS_SEQ12";
char EffectType__37__Parameter__49__name[] = "CONTROLLERS_SEQ13";
char EffectType__37__Parameter__50__name[] = "CONTROLLERS_SEQ14";
char EffectType__37__Parameter__51__name[] = "CONTROLLERS_SEQ15";
char EffectType__37__Parameter__52__name[] = "CONTROLLERS_SEQ16";
char EffectType__37__Parameter__53__name[] = "CONTROLLERS_AUTODELAY";
char EffectType__37__Parameter__54__name[] = "CONTROLLERS_SEQRUN";
char EffectType__37__Parameter__55__name[] = "CONTROLLERS_KNOBA";
char EffectType__37__Parameter__56__name[] = "CONTROLLERS_KNOBB";
char EffectType__37__Parameter__57__name[] = "CONTROLLERS_KNOBC";
char EffectType__37__Parameter__58__name[] = "CONTROLLERS_KNOBD";
char EffectType__37__Parameter__59__name[] = "CONTROLLERS_SEQ17";
char EffectType__37__Parameter__60__name[] = "CONTROLLERS_SEQ18";
char EffectType__37__Parameter__61__name[] = "CONTROLLERS_SEQ19";
char EffectType__37__Parameter__62__name[] = "CONTROLLERS_SEQ20";
char EffectType__37__Parameter__63__name[] = "CONTROLLERS_SEQ21";
char EffectType__37__Parameter__64__name[] = "CONTROLLERS_SEQ22";
char EffectType__37__Parameter__65__name[] = "CONTROLLERS_SEQ23";
char EffectType__37__Parameter__66__name[] = "CONTROLLERS_SEQ24";
char EffectType__37__Parameter__67__name[] = "CONTROLLERS_SEQ25";
char EffectType__37__Parameter__68__name[] = "CONTROLLERS_SEQ26";
char EffectType__37__Parameter__69__name[] = "CONTROLLERS_SEQ27";
char EffectType__37__Parameter__70__name[] = "CONTROLLERS_SEQ28";
char EffectType__37__Parameter__71__name[] = "CONTROLLERS_SEQ29";
char EffectType__37__Parameter__72__name[] = "CONTROLLERS_SEQ30";
char EffectType__37__Parameter__73__name[] = "CONTROLLERS_SEQ31";
char EffectType__37__Parameter__74__name[] = "CONTROLLERS_SEQ32";
char EffectType__37__Parameter__75__name[] = "CONTROLLERS_LFO1RUNCTRL";
char EffectType__37__Parameter__76__name[] = "CONTROLLERS_LFO2RUNCTRL";
char EffectType__37__Parameter__77__name[] = "CONTROLLERS_SEQRUNCTRL";
char EffectType__38__Parameter__0__name[] = "LOOPER_MIX";
char EffectType__38__Parameter__1__name[] = "LOOPER_LEVEL";
char EffectType__38__Parameter__2__name[] = "LOOPER_PAN";
char EffectType__38__Parameter__3__name[] = "LOOPER_BYPASSMODE";
char EffectType__38__Parameter__4__name[] = "LOOPER_BYPASS";
char EffectType__38__Parameter__5__name[] = "LOOPER_DUB_MIX";
char EffectType__38__Parameter__6__name[] = "LOOPER_THRESH";
char EffectType__38__Parameter__7__name[] = "LOOPER_THRESH_LEVEL";
char EffectType__38__Parameter__8__name[] = "LOOPER_MODE";
char EffectType__38__Parameter__9__name[] = "LOOPER_QUANTIZE";
char EffectType__38__Parameter__10__name[] = "LOOPER_STOP";
char EffectType__38__Parameter__11__name[] = "LOOPER_START";
char EffectType__38__Parameter__12__name[] = "LOOPER_PLAYIMMEDIATE";
char EffectType__39__Parameter__0__name[] = "EQMATCH_RUN";
char EffectType__39__Parameter__1__name[] = "EQMATCH_AMOUNT";
char EffectType__39__Parameter__2__name[] = "EQMATCH_SMOOTHING";
char EffectType__39__Parameter__3__name[] = "EQMATCH_CAPTUREREF";
char EffectType__39__Parameter__4__name[] = "EQMATCH_CAPTUREUSER";
char EffectType__39__Parameter__5__name[] = "EQMATCH_MATCH";
char EffectType__39__Parameter__6__name[] = "EQMATCH_LEVEL";
char EffectType__39__Parameter__7__name[] = "EQMATCH_PAN";
char EffectType__39__Parameter__8__name[] = "EQMATCH_BYPASSMODE";
char EffectType__39__Parameter__9__name[] = "EQMATCH_BYPASS";
char EffectType__39__Parameter__10__name[] = "EQMATCH_SOURCE";
char EffectType__39__Parameter__11__name[] = "EQMATCH_TIME";
char EffectType__39__Parameter__12__name[] = "EQMATCH_REFCHAN";
char EffectType__39__Parameter__13__name[] = "EQMATCH_LOCALCHAN";
char EffectType__39__Parameter__14__name[] = "EQMATCH_REFSOLO";
char EffectType__39__Parameter__15__name[] = "EQMATCH_RESOLUTION";
char EffectType__39__Parameter__16__name[] = "EQMATCH_TAPER";
char EffectType__39__Parameter__17__name[] = "EQMATCH_ACCUMULATE";
char EffectType__39__Parameter__18__name[] = "EQMATCH_NORM1";
char EffectType__39__Parameter__19__name[] = "EQMATCH_NORM2";
char EffectType__39__Parameter__20__name[] = "EQMATCH_LFMATCH";


char *Parameter__names[TotalNumOfParameters] = { EffectType__2__Parameter__0__name, EffectType__2__Parameter__1__name, EffectType__2__Parameter__2__name, EffectType__2__Parameter__3__name, EffectType__2__Parameter__4__name, EffectType__2__Parameter__5__name, EffectType__2__Parameter__6__name, EffectType__2__Parameter__7__name, EffectType__2__Parameter__8__name, EffectType__2__Parameter__9__name, EffectType__2__Parameter__10__name, EffectType__2__Parameter__11__name, EffectType__2__Parameter__12__name, EffectType__2__Parameter__13__name, EffectType__2__Parameter__14__name, EffectType__2__Parameter__15__name, EffectType__2__Parameter__16__name, EffectType__2__Parameter__17__name,
EffectType__3__Parameter__0__name, EffectType__3__Parameter__1__name, EffectType__3__Parameter__2__name, EffectType__3__Parameter__3__name, EffectType__3__Parameter__4__name, EffectType__3__Parameter__5__name, EffectType__3__Parameter__6__name, EffectType__3__Parameter__7__name, EffectType__3__Parameter__8__name, EffectType__3__Parameter__9__name, EffectType__3__Parameter__10__name, EffectType__3__Parameter__11__name, EffectType__3__Parameter__12__name, EffectType__3__Parameter__13__name, EffectType__3__Parameter__14__name, EffectType__3__Parameter__15__name, EffectType__3__Parameter__16__name, EffectType__3__Parameter__17__name, EffectType__3__Parameter__18__name,
EffectType__4__Parameter__0__name, EffectType__4__Parameter__1__name, EffectType__4__Parameter__2__name, EffectType__4__Parameter__3__name, EffectType__4__Parameter__4__name, EffectType__4__Parameter__5__name, EffectType__4__Parameter__6__name, EffectType__4__Parameter__7__name, EffectType__4__Parameter__8__name, EffectType__4__Parameter__9__name, EffectType__4__Parameter__10__name, EffectType__4__Parameter__11__name, EffectType__4__Parameter__12__name, EffectType__4__Parameter__13__name, EffectType__4__Parameter__14__name, EffectType__4__Parameter__15__name, EffectType__4__Parameter__16__name, EffectType__4__Parameter__17__name, EffectType__4__Parameter__18__name, EffectType__4__Parameter__19__name, EffectType__4__Parameter__20__name, EffectType__4__Parameter__21__name, EffectType__4__Parameter__22__name, EffectType__4__Parameter__23__name,

//EffectType__5__Parameter__0__name, EffectType__5__Parameter__1__name, EffectType__5__Parameter__2__name, EffectType__5__Parameter__3__name, EffectType__5__Parameter__4__name, EffectType__5__Parameter__5__name, EffectType__5__Parameter__6__name, EffectType__5__Parameter__7__name, EffectType__5__Parameter__8__name, EffectType__5__Parameter__9__name, EffectType__5__Parameter__10__name, EffectType__5__Parameter__11__name, EffectType__5__Parameter__12__name, EffectType__5__Parameter__13__name, EffectType__5__Parameter__14__name, EffectType__5__Parameter__15__name, EffectType__5__Parameter__16__name, EffectType__5__Parameter__17__name, EffectType__5__Parameter__18__name, EffectType__5__Parameter__19__name, EffectType__5__Parameter__20__name, EffectType__5__Parameter__21__name, EffectType__5__Parameter__22__name, EffectType__5__Parameter__23__name, EffectType__5__Parameter__24__name, EffectType__5__Parameter__25__name, EffectType__5__Parameter__26__name, EffectType__5__Parameter__27__name, EffectType__5__Parameter__28__name, EffectType__5__Parameter__29__name, EffectType__5__Parameter__30__name, EffectType__5__Parameter__31__name, EffectType__5__Parameter__32__name, EffectType__5__Parameter__33__name, EffectType__5__Parameter__34__name, EffectType__5__Parameter__35__name, EffectType__5__Parameter__36__name, EffectType__5__Parameter__37__name, EffectType__5__Parameter__38__name, EffectType__5__Parameter__39__name, EffectType__5__Parameter__40__name, EffectType__5__Parameter__41__name, EffectType__5__Parameter__42__name, EffectType__5__Parameter__43__name, EffectType__5__Parameter__44__name, EffectType__5__Parameter__45__name, EffectType__5__Parameter__46__name, EffectType__5__Parameter__47__name, EffectType__5__Parameter__48__name, EffectType__5__Parameter__49__name, EffectType__5__Parameter__50__name, EffectType__5__Parameter__51__name, EffectType__5__Parameter__52__name, EffectType__5__Parameter__53__name, EffectType__5__Parameter__54__name, EffectType__5__Parameter__55__name, EffectType__5__Parameter__56__name, EffectType__5__Parameter__57__name, EffectType__5__Parameter__58__name, EffectType__5__Parameter__59__name, EffectType__5__Parameter__60__name, EffectType__5__Parameter__61__name, EffectType__5__Parameter__62__name, EffectType__5__Parameter__63__name, EffectType__5__Parameter__64__name, EffectType__5__Parameter__65__name, EffectType__5__Parameter__66__name, EffectType__5__Parameter__67__name, EffectType__5__Parameter__68__name, EffectType__5__Parameter__69__name, EffectType__5__Parameter__70__name, EffectType__5__Parameter__71__name, EffectType__5__Parameter__72__name, EffectType__5__Parameter__73__name, EffectType__5__Parameter__74__name, EffectType__5__Parameter__75__name, EffectType__5__Parameter__76__name, EffectType__5__Parameter__77__name, EffectType__5__Parameter__78__name, EffectType__5__Parameter__79__name, EffectType__5__Parameter__80__name, EffectType__5__Parameter__81__name, EffectType__5__Parameter__82__name, EffectType__5__Parameter__83__name, EffectType__5__Parameter__84__name, EffectType__5__Parameter__85__name, EffectType__5__Parameter__86__name, EffectType__5__Parameter__87__name, EffectType__5__Parameter__88__name, EffectType__5__Parameter__89__name, EffectType__5__Parameter__90__name,
//AMP
EffectType__5__Parameter__0__name, EffectType__5__Parameter__1__name, EffectType__5__Parameter__2__name, EffectType__5__Parameter__3__name, EffectType__5__Parameter__4__name, EffectType__5__Parameter__5__name, EffectType__5__Parameter__6__name, EffectType__5__Parameter__7__name, EffectType__5__Parameter__8__name, EffectType__5__Parameter__9__name, EffectType__5__Parameter__10__name, EffectType__5__Parameter__11__name, EffectType__5__Parameter__12__name, EffectType__5__Parameter__13__name, EffectType__5__Parameter__14__name, EffectType__5__Parameter__15__name, EffectType__5__Parameter__16__name, EffectType__5__Parameter__17__name, EffectType__5__Parameter__18__name, EffectType__5__Parameter__19__name, EffectType__5__Parameter__20__name, EffectType__5__Parameter__21__name, EffectType__5__Parameter__22__name, EffectType__5__Parameter__23__name, EffectType__5__Parameter__24__name, EffectType__5__Parameter__25__name, EffectType__5__Parameter__26__name, EffectType__5__Parameter__27__name, EffectType__5__Parameter__28__name, EffectType__5__Parameter__29__name, EffectType__5__Parameter__30__name, EffectType__5__Parameter__31__name, EffectType__5__Parameter__32__name, EffectType__5__Parameter__33__name, EffectType__5__Parameter__34__name, EffectType__5__Parameter__35__name, EffectType__5__Parameter__36__name, EffectType__5__Parameter__37__name, EffectType__5__Parameter__38__name, EffectType__5__Parameter__39__name, EffectType__5__Parameter__40__name, EffectType__5__Parameter__41__name, EffectType__5__Parameter__42__name, EffectType__5__Parameter__43__name, EffectType__5__Parameter__44__name, EffectType__5__Parameter__45__name, EffectType__5__Parameter__46__name, EffectType__5__Parameter__47__name, EffectType__5__Parameter__48__name, EffectType__5__Parameter__49__name, EffectType__5__Parameter__50__name, EffectType__5__Parameter__51__name, EffectType__5__Parameter__52__name, EffectType__5__Parameter__53__name, EffectType__5__Parameter__54__name, EffectType__5__Parameter__55__name, EffectType__5__Parameter__56__name, EffectType__5__Parameter__57__name, EffectType__5__Parameter__58__name, EffectType__5__Parameter__59__name, EffectType__5__Parameter__60__name, EffectType__5__Parameter__61__name, EffectType__5__Parameter__62__name, EffectType__5__Parameter__63__name, EffectType__5__Parameter__64__name, EffectType__5__Parameter__65__name, EffectType__5__Parameter__66__name, EffectType__5__Parameter__67__name, EffectType__5__Parameter__68__name, EffectType__5__Parameter__69__name, EffectType__5__Parameter__70__name, EffectType__5__Parameter__71__name, EffectType__5__Parameter__72__name, EffectType__5__Parameter__73__name, EffectType__5__Parameter__74__name, EffectType__5__Parameter__75__name, EffectType__5__Parameter__76__name, EffectType__5__Parameter__77__name, EffectType__5__Parameter__78__name, EffectType__5__Parameter__79__name, EffectType__5__Parameter__80__name, EffectType__5__Parameter__81__name, EffectType__5__Parameter__82__name, EffectType__5__Parameter__83__name, EffectType__5__Parameter__84__name, EffectType__5__Parameter__85__name, EffectType__5__Parameter__86__name, EffectType__5__Parameter__87__name, EffectType__5__Parameter__88__name, EffectType__5__Parameter__89__name, EffectType__5__Parameter__90__name, EffectType__5__Parameter__91__name, EffectType__5__Parameter__92__name, EffectType__5__Parameter__93__name, EffectType__5__Parameter__94__name, EffectType__5__Parameter__95__name, EffectType__5__Parameter__96__name, EffectType__5__Parameter__97__name, EffectType__5__Parameter__98__name, EffectType__5__Parameter__99__name, EffectType__5__Parameter__100__name, EffectType__5__Parameter__101__name, EffectType__5__Parameter__102__name, EffectType__5__Parameter__103__name, EffectType__5__Parameter__104__name, EffectType__5__Parameter__105__name, EffectType__5__Parameter__106__name, EffectType__5__Parameter__107__name, EffectType__5__Parameter__108__name, EffectType__5__Parameter__109__name, EffectType__5__Parameter__110__name, EffectType__5__Parameter__111__name, EffectType__5__Parameter__112__name,

EffectType__6__Parameter__0__name, EffectType__6__Parameter__1__name, EffectType__6__Parameter__2__name, EffectType__6__Parameter__3__name, EffectType__6__Parameter__4__name, EffectType__6__Parameter__5__name, EffectType__6__Parameter__6__name, EffectType__6__Parameter__7__name, EffectType__6__Parameter__8__name, EffectType__6__Parameter__9__name, EffectType__6__Parameter__10__name, EffectType__6__Parameter__11__name, EffectType__6__Parameter__12__name, EffectType__6__Parameter__13__name, EffectType__6__Parameter__14__name, EffectType__6__Parameter__15__name, EffectType__6__Parameter__16__name, EffectType__6__Parameter__17__name, EffectType__6__Parameter__18__name, EffectType__6__Parameter__19__name, EffectType__6__Parameter__20__name, EffectType__6__Parameter__21__name, EffectType__6__Parameter__22__name, EffectType__6__Parameter__23__name, EffectType__6__Parameter__24__name, EffectType__6__Parameter__25__name, EffectType__6__Parameter__26__name, EffectType__6__Parameter__27__name, EffectType__6__Parameter__28__name,
EffectType__7__Parameter__0__name, EffectType__7__Parameter__1__name, EffectType__7__Parameter__2__name, EffectType__7__Parameter__3__name, EffectType__7__Parameter__4__name, EffectType__7__Parameter__5__name, EffectType__7__Parameter__6__name, EffectType__7__Parameter__7__name, EffectType__7__Parameter__8__name, EffectType__7__Parameter__9__name, EffectType__7__Parameter__10__name, EffectType__7__Parameter__11__name, EffectType__7__Parameter__12__name, EffectType__7__Parameter__13__name, EffectType__7__Parameter__14__name, EffectType__7__Parameter__15__name, EffectType__7__Parameter__16__name, EffectType__7__Parameter__17__name, EffectType__7__Parameter__18__name, EffectType__7__Parameter__19__name, EffectType__7__Parameter__20__name, EffectType__7__Parameter__21__name, EffectType__7__Parameter__22__name, EffectType__7__Parameter__23__name, EffectType__7__Parameter__24__name, EffectType__7__Parameter__25__name, EffectType__7__Parameter__26__name, EffectType__7__Parameter__27__name, EffectType__7__Parameter__28__name, EffectType__7__Parameter__29__name, EffectType__7__Parameter__30__name, EffectType__7__Parameter__31__name, EffectType__7__Parameter__32__name, EffectType__7__Parameter__33__name, EffectType__7__Parameter__34__name,
EffectType__8__Parameter__0__name, EffectType__8__Parameter__1__name, EffectType__8__Parameter__2__name, EffectType__8__Parameter__3__name, EffectType__8__Parameter__4__name, EffectType__8__Parameter__5__name, EffectType__8__Parameter__6__name, EffectType__8__Parameter__7__name, EffectType__8__Parameter__8__name, EffectType__8__Parameter__9__name, EffectType__8__Parameter__10__name, EffectType__8__Parameter__11__name, EffectType__8__Parameter__12__name, EffectType__8__Parameter__13__name, EffectType__8__Parameter__14__name, EffectType__8__Parameter__15__name, EffectType__8__Parameter__16__name, EffectType__8__Parameter__17__name, EffectType__8__Parameter__18__name, EffectType__8__Parameter__19__name, EffectType__8__Parameter__20__name, EffectType__8__Parameter__21__name, EffectType__8__Parameter__22__name, EffectType__8__Parameter__23__name, EffectType__8__Parameter__24__name, EffectType__8__Parameter__25__name, EffectType__8__Parameter__26__name, EffectType__8__Parameter__27__name, EffectType__8__Parameter__28__name, EffectType__8__Parameter__29__name, EffectType__8__Parameter__30__name, EffectType__8__Parameter__31__name, EffectType__8__Parameter__32__name, EffectType__8__Parameter__33__name, EffectType__8__Parameter__34__name, EffectType__8__Parameter__35__name, EffectType__8__Parameter__36__name, EffectType__8__Parameter__37__name, EffectType__8__Parameter__38__name, EffectType__8__Parameter__39__name, EffectType__8__Parameter__40__name, EffectType__8__Parameter__41__name, EffectType__8__Parameter__42__name, EffectType__8__Parameter__43__name, EffectType__8__Parameter__44__name, EffectType__8__Parameter__45__name, EffectType__8__Parameter__46__name, EffectType__8__Parameter__47__name, EffectType__8__Parameter__48__name, EffectType__8__Parameter__49__name, EffectType__8__Parameter__50__name, EffectType__8__Parameter__51__name, EffectType__8__Parameter__52__name, EffectType__8__Parameter__53__name, EffectType__8__Parameter__54__name, EffectType__8__Parameter__55__name, EffectType__8__Parameter__56__name, EffectType__8__Parameter__57__name, EffectType__8__Parameter__58__name, EffectType__8__Parameter__59__name, EffectType__8__Parameter__60__name, EffectType__8__Parameter__61__name, EffectType__8__Parameter__62__name, EffectType__8__Parameter__63__name, EffectType__8__Parameter__64__name, EffectType__8__Parameter__65__name, EffectType__8__Parameter__66__name, EffectType__8__Parameter__67__name, EffectType__8__Parameter__68__name, EffectType__8__Parameter__69__name,
EffectType__9__Parameter__0__name, EffectType__9__Parameter__1__name, EffectType__9__Parameter__2__name, EffectType__9__Parameter__3__name, EffectType__9__Parameter__4__name, EffectType__9__Parameter__5__name, EffectType__9__Parameter__6__name, EffectType__9__Parameter__7__name, EffectType__9__Parameter__8__name, EffectType__9__Parameter__9__name, EffectType__9__Parameter__10__name, EffectType__9__Parameter__11__name, EffectType__9__Parameter__12__name, EffectType__9__Parameter__13__name, EffectType__9__Parameter__14__name, EffectType__9__Parameter__15__name, EffectType__9__Parameter__16__name, EffectType__9__Parameter__17__name, EffectType__9__Parameter__18__name, EffectType__9__Parameter__19__name, EffectType__9__Parameter__20__name, EffectType__9__Parameter__21__name, EffectType__9__Parameter__22__name, EffectType__9__Parameter__23__name, EffectType__9__Parameter__24__name, EffectType__9__Parameter__25__name, EffectType__9__Parameter__26__name, EffectType__9__Parameter__27__name, EffectType__9__Parameter__28__name, EffectType__9__Parameter__29__name, EffectType__9__Parameter__30__name, EffectType__9__Parameter__31__name, EffectType__9__Parameter__32__name, EffectType__9__Parameter__33__name, EffectType__9__Parameter__34__name, EffectType__9__Parameter__35__name, EffectType__9__Parameter__36__name, EffectType__9__Parameter__37__name, EffectType__9__Parameter__38__name, EffectType__9__Parameter__39__name, EffectType__9__Parameter__40__name, EffectType__9__Parameter__41__name, EffectType__9__Parameter__42__name, EffectType__9__Parameter__43__name, EffectType__9__Parameter__44__name, EffectType__9__Parameter__45__name, EffectType__9__Parameter__46__name, EffectType__9__Parameter__47__name, EffectType__9__Parameter__48__name, EffectType__9__Parameter__49__name, EffectType__9__Parameter__50__name, EffectType__9__Parameter__51__name, EffectType__9__Parameter__52__name, EffectType__9__Parameter__53__name, EffectType__9__Parameter__54__name, EffectType__9__Parameter__55__name, EffectType__9__Parameter__56__name, EffectType__9__Parameter__57__name, EffectType__9__Parameter__58__name, EffectType__9__Parameter__59__name, EffectType__9__Parameter__60__name, EffectType__9__Parameter__61__name, EffectType__9__Parameter__62__name, EffectType__9__Parameter__63__name, EffectType__9__Parameter__64__name, EffectType__9__Parameter__65__name, EffectType__9__Parameter__66__name, EffectType__9__Parameter__67__name, EffectType__9__Parameter__68__name, EffectType__9__Parameter__69__name, EffectType__9__Parameter__70__name, EffectType__9__Parameter__71__name, EffectType__9__Parameter__72__name, EffectType__9__Parameter__73__name, EffectType__9__Parameter__74__name, EffectType__9__Parameter__75__name, EffectType__9__Parameter__76__name, EffectType__9__Parameter__77__name, EffectType__9__Parameter__78__name, EffectType__9__Parameter__79__name, EffectType__9__Parameter__80__name, EffectType__9__Parameter__81__name, EffectType__9__Parameter__82__name, EffectType__9__Parameter__83__name, EffectType__9__Parameter__84__name, EffectType__9__Parameter__85__name, EffectType__9__Parameter__86__name, EffectType__9__Parameter__87__name, EffectType__9__Parameter__88__name, EffectType__9__Parameter__89__name, EffectType__9__Parameter__90__name, EffectType__9__Parameter__91__name, EffectType__9__Parameter__92__name, EffectType__9__Parameter__93__name, EffectType__9__Parameter__94__name, EffectType__9__Parameter__95__name, EffectType__9__Parameter__96__name, EffectType__9__Parameter__97__name, EffectType__9__Parameter__98__name, EffectType__9__Parameter__99__name, EffectType__9__Parameter__100__name, EffectType__9__Parameter__101__name, EffectType__9__Parameter__102__name, EffectType__9__Parameter__103__name, EffectType__9__Parameter__104__name, EffectType__9__Parameter__105__name, EffectType__9__Parameter__106__name, EffectType__9__Parameter__107__name, EffectType__9__Parameter__108__name, EffectType__9__Parameter__109__name, EffectType__9__Parameter__110__name, EffectType__9__Parameter__111__name, EffectType__9__Parameter__112__name, EffectType__9__Parameter__113__name, EffectType__9__Parameter__114__name, EffectType__9__Parameter__115__name, EffectType__9__Parameter__116__name,
EffectType__10__Parameter__0__name, EffectType__10__Parameter__1__name, EffectType__10__Parameter__2__name, EffectType__10__Parameter__3__name, EffectType__10__Parameter__4__name, EffectType__10__Parameter__5__name, EffectType__10__Parameter__6__name, EffectType__10__Parameter__7__name, EffectType__10__Parameter__8__name, EffectType__10__Parameter__9__name, EffectType__10__Parameter__10__name, EffectType__10__Parameter__11__name, EffectType__10__Parameter__12__name, EffectType__10__Parameter__13__name, EffectType__10__Parameter__14__name, EffectType__10__Parameter__15__name, EffectType__10__Parameter__16__name, EffectType__10__Parameter__17__name, EffectType__10__Parameter__18__name, EffectType__10__Parameter__19__name, EffectType__10__Parameter__20__name, EffectType__10__Parameter__21__name, EffectType__10__Parameter__22__name,
EffectType__11__Parameter__0__name, EffectType__11__Parameter__1__name, EffectType__11__Parameter__2__name, EffectType__11__Parameter__3__name, EffectType__11__Parameter__4__name, EffectType__11__Parameter__5__name, EffectType__11__Parameter__6__name, EffectType__11__Parameter__7__name, EffectType__11__Parameter__8__name, EffectType__11__Parameter__9__name, EffectType__11__Parameter__10__name, EffectType__11__Parameter__11__name, EffectType__11__Parameter__12__name, EffectType__11__Parameter__13__name, EffectType__11__Parameter__14__name, EffectType__11__Parameter__15__name, EffectType__11__Parameter__16__name, EffectType__11__Parameter__17__name, EffectType__11__Parameter__18__name, EffectType__11__Parameter__19__name, EffectType__11__Parameter__20__name, EffectType__11__Parameter__21__name, EffectType__11__Parameter__22__name,
EffectType__12__Parameter__0__name, EffectType__12__Parameter__1__name, EffectType__12__Parameter__2__name, EffectType__12__Parameter__3__name, EffectType__12__Parameter__4__name, EffectType__12__Parameter__5__name, EffectType__12__Parameter__6__name, EffectType__12__Parameter__7__name, EffectType__12__Parameter__8__name, EffectType__12__Parameter__9__name, EffectType__12__Parameter__10__name, EffectType__12__Parameter__11__name, EffectType__12__Parameter__12__name, EffectType__12__Parameter__13__name, EffectType__12__Parameter__14__name, EffectType__12__Parameter__15__name, EffectType__12__Parameter__16__name, EffectType__12__Parameter__17__name,
EffectType__13__Parameter__0__name, EffectType__13__Parameter__1__name, EffectType__13__Parameter__2__name, EffectType__13__Parameter__3__name, EffectType__13__Parameter__4__name, EffectType__13__Parameter__5__name, EffectType__13__Parameter__6__name, EffectType__13__Parameter__7__name, EffectType__13__Parameter__8__name, EffectType__13__Parameter__9__name, EffectType__13__Parameter__10__name, EffectType__13__Parameter__11__name, EffectType__13__Parameter__12__name, EffectType__13__Parameter__13__name, EffectType__13__Parameter__14__name, EffectType__13__Parameter__15__name, EffectType__13__Parameter__16__name, EffectType__13__Parameter__17__name, EffectType__13__Parameter__18__name, EffectType__13__Parameter__19__name,
EffectType__14__Parameter__0__name, EffectType__14__Parameter__1__name, EffectType__14__Parameter__2__name, EffectType__14__Parameter__3__name, EffectType__14__Parameter__4__name, EffectType__14__Parameter__5__name, EffectType__14__Parameter__6__name, EffectType__14__Parameter__7__name, EffectType__14__Parameter__8__name, EffectType__14__Parameter__9__name, EffectType__14__Parameter__10__name, EffectType__14__Parameter__11__name, EffectType__14__Parameter__12__name,
EffectType__15__Parameter__0__name, EffectType__15__Parameter__1__name, EffectType__15__Parameter__2__name, EffectType__15__Parameter__3__name, EffectType__15__Parameter__4__name, EffectType__15__Parameter__5__name, EffectType__15__Parameter__6__name, EffectType__15__Parameter__7__name, EffectType__15__Parameter__8__name, EffectType__15__Parameter__9__name, EffectType__15__Parameter__10__name, EffectType__15__Parameter__11__name,
EffectType__16__Parameter__0__name, EffectType__16__Parameter__1__name, EffectType__16__Parameter__2__name, EffectType__16__Parameter__3__name, EffectType__16__Parameter__4__name, EffectType__16__Parameter__5__name, EffectType__16__Parameter__6__name, EffectType__16__Parameter__7__name, EffectType__16__Parameter__8__name, EffectType__16__Parameter__9__name, EffectType__16__Parameter__10__name, EffectType__16__Parameter__11__name, EffectType__16__Parameter__12__name, EffectType__16__Parameter__13__name, EffectType__16__Parameter__14__name,
EffectType__17__Parameter__0__name, EffectType__17__Parameter__1__name, EffectType__17__Parameter__2__name, EffectType__17__Parameter__3__name, EffectType__17__Parameter__4__name, EffectType__17__Parameter__5__name, EffectType__17__Parameter__6__name, EffectType__17__Parameter__7__name, EffectType__17__Parameter__8__name, EffectType__17__Parameter__9__name, EffectType__17__Parameter__10__name, EffectType__17__Parameter__11__name, EffectType__17__Parameter__12__name, EffectType__17__Parameter__13__name, EffectType__17__Parameter__14__name, EffectType__17__Parameter__15__name, EffectType__17__Parameter__16__name, EffectType__17__Parameter__17__name, EffectType__17__Parameter__18__name, EffectType__17__Parameter__19__name, EffectType__17__Parameter__20__name, EffectType__17__Parameter__21__name, EffectType__17__Parameter__22__name, EffectType__17__Parameter__23__name, EffectType__17__Parameter__24__name, EffectType__17__Parameter__25__name, EffectType__17__Parameter__26__name, EffectType__17__Parameter__27__name, EffectType__17__Parameter__28__name, EffectType__17__Parameter__29__name, EffectType__17__Parameter__30__name, EffectType__17__Parameter__31__name, EffectType__17__Parameter__32__name, EffectType__17__Parameter__33__name, EffectType__17__Parameter__34__name, EffectType__17__Parameter__35__name, EffectType__17__Parameter__36__name, EffectType__17__Parameter__37__name, EffectType__17__Parameter__38__name, EffectType__17__Parameter__39__name, EffectType__17__Parameter__40__name, EffectType__17__Parameter__41__name, EffectType__17__Parameter__42__name, EffectType__17__Parameter__43__name, EffectType__17__Parameter__44__name, EffectType__17__Parameter__45__name, EffectType__17__Parameter__46__name, EffectType__17__Parameter__47__name, EffectType__17__Parameter__48__name, EffectType__17__Parameter__49__name, EffectType__17__Parameter__50__name, EffectType__17__Parameter__51__name, EffectType__17__Parameter__52__name, EffectType__17__Parameter__53__name, EffectType__17__Parameter__54__name, EffectType__17__Parameter__55__name, EffectType__17__Parameter__56__name, EffectType__17__Parameter__57__name, EffectType__17__Parameter__58__name, EffectType__17__Parameter__59__name, EffectType__17__Parameter__60__name, EffectType__17__Parameter__61__name, EffectType__17__Parameter__62__name, EffectType__17__Parameter__63__name, EffectType__17__Parameter__64__name, EffectType__17__Parameter__65__name, EffectType__17__Parameter__66__name, EffectType__17__Parameter__67__name, EffectType__17__Parameter__68__name, EffectType__17__Parameter__69__name, EffectType__17__Parameter__70__name, EffectType__17__Parameter__71__name, EffectType__17__Parameter__72__name, EffectType__17__Parameter__73__name, EffectType__17__Parameter__74__name, EffectType__17__Parameter__75__name, EffectType__17__Parameter__76__name, EffectType__17__Parameter__77__name, EffectType__17__Parameter__78__name, EffectType__17__Parameter__79__name, EffectType__17__Parameter__80__name, EffectType__17__Parameter__81__name, EffectType__17__Parameter__82__name, EffectType__17__Parameter__83__name, EffectType__17__Parameter__84__name,
EffectType__18__Parameter__0__name, EffectType__18__Parameter__1__name, EffectType__18__Parameter__2__name, EffectType__18__Parameter__3__name, EffectType__18__Parameter__4__name, EffectType__18__Parameter__5__name, EffectType__18__Parameter__6__name, EffectType__18__Parameter__7__name, EffectType__18__Parameter__8__name, EffectType__18__Parameter__9__name, EffectType__18__Parameter__10__name, EffectType__18__Parameter__11__name, EffectType__18__Parameter__12__name, EffectType__18__Parameter__13__name,
EffectType__19__Parameter__0__name, EffectType__19__Parameter__1__name, EffectType__19__Parameter__2__name, EffectType__19__Parameter__3__name, EffectType__19__Parameter__4__name, EffectType__19__Parameter__5__name, EffectType__19__Parameter__6__name, EffectType__19__Parameter__7__name, EffectType__19__Parameter__8__name, EffectType__19__Parameter__9__name, EffectType__19__Parameter__10__name, EffectType__19__Parameter__11__name, EffectType__19__Parameter__12__name, EffectType__19__Parameter__13__name, EffectType__19__Parameter__14__name, EffectType__19__Parameter__15__name, EffectType__19__Parameter__16__name, EffectType__19__Parameter__17__name, EffectType__19__Parameter__18__name, EffectType__19__Parameter__19__name,
EffectType__20__Parameter__0__name, EffectType__20__Parameter__1__name, EffectType__20__Parameter__2__name, EffectType__20__Parameter__3__name, EffectType__20__Parameter__4__name, EffectType__20__Parameter__5__name, EffectType__20__Parameter__6__name, EffectType__20__Parameter__7__name, EffectType__20__Parameter__8__name, EffectType__20__Parameter__9__name, EffectType__20__Parameter__10__name,
EffectType__21__Parameter__0__name, EffectType__21__Parameter__1__name, EffectType__21__Parameter__2__name, EffectType__21__Parameter__3__name, EffectType__21__Parameter__4__name, EffectType__21__Parameter__5__name, EffectType__21__Parameter__6__name, EffectType__21__Parameter__7__name, EffectType__21__Parameter__8__name, EffectType__21__Parameter__9__name, EffectType__21__Parameter__10__name, EffectType__21__Parameter__11__name, EffectType__21__Parameter__12__name, EffectType__21__Parameter__13__name, EffectType__21__Parameter__14__name, EffectType__21__Parameter__15__name, EffectType__21__Parameter__16__name, EffectType__21__Parameter__17__name, EffectType__21__Parameter__18__name, EffectType__21__Parameter__19__name,
EffectType__22__Parameter__0__name, EffectType__22__Parameter__1__name, EffectType__22__Parameter__2__name, EffectType__22__Parameter__3__name, EffectType__22__Parameter__4__name, EffectType__22__Parameter__5__name, EffectType__22__Parameter__6__name, EffectType__22__Parameter__7__name, EffectType__22__Parameter__8__name, EffectType__22__Parameter__9__name,
EffectType__23__Parameter__0__name, EffectType__23__Parameter__1__name,
EffectType__24__Parameter__0__name, EffectType__24__Parameter__1__name, EffectType__24__Parameter__2__name, EffectType__24__Parameter__3__name, EffectType__24__Parameter__4__name, EffectType__24__Parameter__5__name,
EffectType__25__Parameter__0__name, EffectType__25__Parameter__1__name, EffectType__25__Parameter__2__name, EffectType__25__Parameter__3__name, EffectType__25__Parameter__4__name, EffectType__25__Parameter__5__name, EffectType__25__Parameter__6__name, EffectType__25__Parameter__7__name, EffectType__25__Parameter__8__name, EffectType__25__Parameter__9__name, EffectType__25__Parameter__10__name, EffectType__25__Parameter__11__name, EffectType__25__Parameter__12__name, EffectType__25__Parameter__13__name, EffectType__25__Parameter__14__name, EffectType__25__Parameter__15__name, EffectType__25__Parameter__16__name, EffectType__25__Parameter__17__name, EffectType__25__Parameter__18__name, EffectType__25__Parameter__19__name, EffectType__25__Parameter__20__name, EffectType__25__Parameter__21__name, EffectType__25__Parameter__22__name, EffectType__25__Parameter__23__name, EffectType__25__Parameter__24__name, EffectType__25__Parameter__25__name, EffectType__25__Parameter__26__name, EffectType__25__Parameter__27__name, EffectType__25__Parameter__28__name, EffectType__25__Parameter__29__name, EffectType__25__Parameter__30__name, EffectType__25__Parameter__31__name, EffectType__25__Parameter__32__name, EffectType__25__Parameter__33__name, EffectType__25__Parameter__34__name, EffectType__25__Parameter__35__name, EffectType__25__Parameter__36__name, EffectType__25__Parameter__37__name, EffectType__25__Parameter__38__name, EffectType__25__Parameter__39__name,
EffectType__26__Parameter__0__name, EffectType__26__Parameter__1__name, EffectType__26__Parameter__2__name, EffectType__26__Parameter__3__name, EffectType__26__Parameter__4__name, EffectType__26__Parameter__5__name, EffectType__26__Parameter__6__name, EffectType__26__Parameter__7__name, EffectType__26__Parameter__8__name, EffectType__26__Parameter__9__name, EffectType__26__Parameter__10__name, EffectType__26__Parameter__11__name, EffectType__26__Parameter__12__name, EffectType__26__Parameter__13__name, EffectType__26__Parameter__14__name, EffectType__26__Parameter__15__name, EffectType__26__Parameter__16__name, EffectType__26__Parameter__17__name, EffectType__26__Parameter__18__name, EffectType__26__Parameter__19__name, EffectType__26__Parameter__20__name, EffectType__26__Parameter__21__name, EffectType__26__Parameter__22__name, EffectType__26__Parameter__23__name, EffectType__26__Parameter__24__name, EffectType__26__Parameter__25__name, EffectType__26__Parameter__26__name, EffectType__26__Parameter__27__name, EffectType__26__Parameter__28__name, EffectType__26__Parameter__29__name, EffectType__26__Parameter__30__name, EffectType__26__Parameter__31__name, EffectType__26__Parameter__32__name, EffectType__26__Parameter__33__name, EffectType__26__Parameter__34__name, EffectType__26__Parameter__35__name, EffectType__26__Parameter__36__name, EffectType__26__Parameter__37__name, EffectType__26__Parameter__38__name, EffectType__26__Parameter__39__name, EffectType__26__Parameter__40__name, EffectType__26__Parameter__41__name, EffectType__26__Parameter__42__name, EffectType__26__Parameter__43__name, EffectType__26__Parameter__44__name, EffectType__26__Parameter__45__name, EffectType__26__Parameter__46__name, EffectType__26__Parameter__47__name, EffectType__26__Parameter__48__name, EffectType__26__Parameter__49__name,
EffectType__27__Parameter__0__name, EffectType__27__Parameter__1__name, EffectType__27__Parameter__2__name, EffectType__27__Parameter__3__name, EffectType__27__Parameter__4__name, EffectType__27__Parameter__5__name, EffectType__27__Parameter__6__name, EffectType__27__Parameter__7__name, EffectType__27__Parameter__8__name, EffectType__27__Parameter__9__name, EffectType__27__Parameter__10__name, EffectType__27__Parameter__11__name, EffectType__27__Parameter__12__name, EffectType__27__Parameter__13__name, EffectType__27__Parameter__14__name, EffectType__27__Parameter__15__name, EffectType__27__Parameter__16__name,
EffectType__28__Parameter__0__name, EffectType__28__Parameter__1__name, EffectType__28__Parameter__2__name, EffectType__28__Parameter__3__name, EffectType__28__Parameter__4__name, EffectType__28__Parameter__5__name, EffectType__28__Parameter__6__name, EffectType__28__Parameter__7__name, EffectType__28__Parameter__8__name, EffectType__28__Parameter__9__name, EffectType__28__Parameter__10__name, EffectType__28__Parameter__11__name, EffectType__28__Parameter__12__name, EffectType__28__Parameter__13__name, EffectType__28__Parameter__14__name,
EffectType__29__Parameter__0__name, EffectType__29__Parameter__1__name, EffectType__29__Parameter__2__name, EffectType__29__Parameter__3__name, EffectType__29__Parameter__4__name, EffectType__29__Parameter__5__name, EffectType__29__Parameter__6__name, EffectType__29__Parameter__7__name, EffectType__29__Parameter__8__name, EffectType__29__Parameter__9__name, EffectType__29__Parameter__10__name, EffectType__29__Parameter__11__name, EffectType__29__Parameter__12__name,
EffectType__30__Parameter__0__name, EffectType__30__Parameter__1__name, EffectType__30__Parameter__2__name, EffectType__30__Parameter__3__name, EffectType__30__Parameter__4__name, EffectType__30__Parameter__5__name, EffectType__30__Parameter__6__name, EffectType__30__Parameter__7__name, EffectType__30__Parameter__8__name, EffectType__30__Parameter__9__name,
EffectType__31__Parameter__0__name, EffectType__31__Parameter__1__name, EffectType__31__Parameter__2__name, EffectType__31__Parameter__3__name, EffectType__31__Parameter__4__name, EffectType__31__Parameter__5__name, EffectType__31__Parameter__6__name, EffectType__31__Parameter__7__name, EffectType__31__Parameter__8__name, EffectType__31__Parameter__9__name, EffectType__31__Parameter__10__name, EffectType__31__Parameter__11__name, EffectType__31__Parameter__12__name, EffectType__31__Parameter__13__name, EffectType__31__Parameter__14__name, EffectType__31__Parameter__15__name, EffectType__31__Parameter__16__name, EffectType__31__Parameter__17__name, EffectType__31__Parameter__18__name, EffectType__31__Parameter__19__name, EffectType__31__Parameter__20__name, EffectType__31__Parameter__21__name, EffectType__31__Parameter__22__name, EffectType__31__Parameter__23__name, EffectType__31__Parameter__24__name, EffectType__31__Parameter__25__name, EffectType__31__Parameter__26__name, EffectType__31__Parameter__27__name,
EffectType__32__Parameter__0__name, EffectType__32__Parameter__1__name, EffectType__32__Parameter__2__name, EffectType__32__Parameter__3__name, EffectType__32__Parameter__4__name, EffectType__32__Parameter__5__name, EffectType__32__Parameter__6__name, EffectType__32__Parameter__7__name, EffectType__32__Parameter__8__name, EffectType__32__Parameter__9__name, EffectType__32__Parameter__10__name, EffectType__32__Parameter__11__name, EffectType__32__Parameter__12__name, EffectType__32__Parameter__13__name, EffectType__32__Parameter__14__name, EffectType__32__Parameter__15__name, EffectType__32__Parameter__16__name, EffectType__32__Parameter__17__name, EffectType__32__Parameter__18__name, EffectType__32__Parameter__19__name, EffectType__32__Parameter__20__name, EffectType__32__Parameter__21__name, EffectType__32__Parameter__22__name, EffectType__32__Parameter__23__name, EffectType__32__Parameter__24__name, EffectType__32__Parameter__25__name, EffectType__32__Parameter__26__name, EffectType__32__Parameter__27__name, EffectType__32__Parameter__28__name, EffectType__32__Parameter__29__name, EffectType__32__Parameter__30__name, EffectType__32__Parameter__31__name, EffectType__32__Parameter__32__name, EffectType__32__Parameter__33__name, EffectType__32__Parameter__34__name, EffectType__32__Parameter__35__name, EffectType__32__Parameter__36__name, EffectType__32__Parameter__37__name, EffectType__32__Parameter__38__name, EffectType__32__Parameter__39__name, EffectType__32__Parameter__40__name, EffectType__32__Parameter__41__name, EffectType__32__Parameter__42__name, EffectType__32__Parameter__43__name, EffectType__32__Parameter__44__name, EffectType__32__Parameter__45__name,
EffectType__33__Parameter__0__name, EffectType__33__Parameter__1__name, EffectType__33__Parameter__2__name, EffectType__33__Parameter__3__name, EffectType__33__Parameter__4__name, EffectType__33__Parameter__5__name, EffectType__33__Parameter__6__name, EffectType__33__Parameter__7__name, EffectType__33__Parameter__8__name, EffectType__33__Parameter__9__name, EffectType__33__Parameter__10__name, EffectType__33__Parameter__11__name, EffectType__33__Parameter__12__name, EffectType__33__Parameter__13__name, EffectType__33__Parameter__14__name, EffectType__33__Parameter__15__name, EffectType__33__Parameter__16__name, EffectType__33__Parameter__17__name, EffectType__33__Parameter__18__name, EffectType__33__Parameter__19__name, EffectType__33__Parameter__20__name, EffectType__33__Parameter__21__name, EffectType__33__Parameter__22__name, EffectType__33__Parameter__23__name, EffectType__33__Parameter__24__name, EffectType__33__Parameter__25__name, EffectType__33__Parameter__26__name, EffectType__33__Parameter__27__name, EffectType__33__Parameter__28__name, EffectType__33__Parameter__29__name, EffectType__33__Parameter__30__name, EffectType__33__Parameter__31__name, EffectType__33__Parameter__32__name, EffectType__33__Parameter__33__name, EffectType__33__Parameter__34__name, EffectType__33__Parameter__35__name, EffectType__33__Parameter__36__name, EffectType__33__Parameter__37__name, EffectType__33__Parameter__38__name, EffectType__33__Parameter__39__name,
EffectType__34__Parameter__0__name, EffectType__34__Parameter__1__name, EffectType__34__Parameter__2__name, EffectType__34__Parameter__3__name, EffectType__34__Parameter__4__name, EffectType__34__Parameter__5__name, EffectType__34__Parameter__6__name, EffectType__34__Parameter__7__name, EffectType__34__Parameter__8__name,
EffectType__35__Parameter__0__name, EffectType__35__Parameter__1__name, EffectType__35__Parameter__2__name, EffectType__35__Parameter__3__name, EffectType__35__Parameter__4__name,
EffectType__36__Parameter__0__name, EffectType__36__Parameter__1__name, EffectType__36__Parameter__2__name, EffectType__36__Parameter__3__name, EffectType__36__Parameter__4__name, EffectType__36__Parameter__5__name, EffectType__36__Parameter__6__name, EffectType__36__Parameter__7__name, EffectType__36__Parameter__8__name, EffectType__36__Parameter__9__name, EffectType__36__Parameter__10__name, EffectType__36__Parameter__11__name, EffectType__36__Parameter__12__name, EffectType__36__Parameter__13__name, EffectType__36__Parameter__14__name, EffectType__36__Parameter__15__name, EffectType__36__Parameter__16__name, EffectType__36__Parameter__17__name, EffectType__36__Parameter__18__name, EffectType__36__Parameter__19__name,
EffectType__37__Parameter__0__name, EffectType__37__Parameter__1__name, EffectType__37__Parameter__2__name, EffectType__37__Parameter__3__name, EffectType__37__Parameter__4__name, EffectType__37__Parameter__5__name, EffectType__37__Parameter__6__name, EffectType__37__Parameter__7__name, EffectType__37__Parameter__8__name, EffectType__37__Parameter__9__name, EffectType__37__Parameter__10__name, EffectType__37__Parameter__11__name, EffectType__37__Parameter__12__name, EffectType__37__Parameter__13__name, EffectType__37__Parameter__14__name, EffectType__37__Parameter__15__name, EffectType__37__Parameter__16__name, EffectType__37__Parameter__17__name, EffectType__37__Parameter__18__name, EffectType__37__Parameter__19__name, EffectType__37__Parameter__20__name, EffectType__37__Parameter__21__name, EffectType__37__Parameter__22__name, EffectType__37__Parameter__23__name, EffectType__37__Parameter__24__name, EffectType__37__Parameter__25__name, EffectType__37__Parameter__26__name, EffectType__37__Parameter__27__name, EffectType__37__Parameter__28__name, EffectType__37__Parameter__29__name, EffectType__37__Parameter__30__name, EffectType__37__Parameter__31__name, EffectType__37__Parameter__32__name, EffectType__37__Parameter__33__name, EffectType__37__Parameter__34__name, EffectType__37__Parameter__35__name, EffectType__37__Parameter__36__name, EffectType__37__Parameter__37__name, EffectType__37__Parameter__38__name, EffectType__37__Parameter__39__name, EffectType__37__Parameter__40__name, EffectType__37__Parameter__41__name, EffectType__37__Parameter__42__name, EffectType__37__Parameter__43__name, EffectType__37__Parameter__44__name, EffectType__37__Parameter__45__name, EffectType__37__Parameter__46__name, EffectType__37__Parameter__47__name, EffectType__37__Parameter__48__name, EffectType__37__Parameter__49__name, EffectType__37__Parameter__50__name, EffectType__37__Parameter__51__name, EffectType__37__Parameter__52__name, EffectType__37__Parameter__53__name, EffectType__37__Parameter__54__name, EffectType__37__Parameter__55__name, EffectType__37__Parameter__56__name, EffectType__37__Parameter__57__name, EffectType__37__Parameter__58__name, EffectType__37__Parameter__59__name, EffectType__37__Parameter__60__name, EffectType__37__Parameter__61__name, EffectType__37__Parameter__62__name, EffectType__37__Parameter__63__name, EffectType__37__Parameter__64__name, EffectType__37__Parameter__65__name, EffectType__37__Parameter__66__name, EffectType__37__Parameter__67__name, EffectType__37__Parameter__68__name, EffectType__37__Parameter__69__name, EffectType__37__Parameter__70__name, EffectType__37__Parameter__71__name, EffectType__37__Parameter__72__name, EffectType__37__Parameter__73__name, EffectType__37__Parameter__74__name, EffectType__37__Parameter__75__name, EffectType__37__Parameter__76__name, EffectType__37__Parameter__77__name,
EffectType__38__Parameter__0__name, EffectType__38__Parameter__1__name, EffectType__38__Parameter__2__name, EffectType__38__Parameter__3__name, EffectType__38__Parameter__4__name, EffectType__38__Parameter__5__name, EffectType__38__Parameter__6__name, EffectType__38__Parameter__7__name, EffectType__38__Parameter__8__name, EffectType__38__Parameter__9__name, EffectType__38__Parameter__10__name, EffectType__38__Parameter__11__name, EffectType__38__Parameter__12__name,
EffectType__39__Parameter__0__name, EffectType__39__Parameter__1__name, EffectType__39__Parameter__2__name, EffectType__39__Parameter__3__name, EffectType__39__Parameter__4__name, EffectType__39__Parameter__5__name, EffectType__39__Parameter__6__name, EffectType__39__Parameter__7__name, EffectType__39__Parameter__8__name, EffectType__39__Parameter__9__name, EffectType__39__Parameter__10__name, EffectType__39__Parameter__11__name, EffectType__39__Parameter__12__name, EffectType__39__Parameter__13__name, EffectType__39__Parameter__14__name, EffectType__39__Parameter__15__name, EffectType__39__Parameter__16__name, EffectType__39__Parameter__17__name, EffectType__39__Parameter__18__name, EffectType__39__Parameter__19__name, EffectType__39__Parameter__20__name};

char EffectType__2__Parameter__0__label[] = "Threshold";
char EffectType__2__Parameter__1__label[] = "Ratio";
char EffectType__2__Parameter__2__label[] = "Attack";
char EffectType__2__Parameter__3__label[] = "Release";
char EffectType__2__Parameter__4__label[] = "Level";
char EffectType__2__Parameter__5__label[] = "Knee";
char EffectType__2__Parameter__6__label[] = "Makeup";
char EffectType__2__Parameter__7__label[] = "Detect";
char EffectType__2__Parameter__8__label[] = "Filter";
char EffectType__2__Parameter__9__label[] = "";
char EffectType__2__Parameter__10__label[] = "Sidechain Select";
char EffectType__2__Parameter__11__label[] = "Mix";
char EffectType__2__Parameter__12__label[] = "";
char EffectType__2__Parameter__13__label[] = "Sustain";
char EffectType__2__Parameter__14__label[] = "Bypass Mode";
char EffectType__2__Parameter__15__label[] = "Look-Ahead";
char EffectType__2__Parameter__16__label[] = "Auto";
char EffectType__2__Parameter__17__label[] = "Emphasis";
char EffectType__3__Parameter__0__label[] = "31";
char EffectType__3__Parameter__1__label[] = "63";
char EffectType__3__Parameter__2__label[] = "125";
char EffectType__3__Parameter__3__label[] = "250";
char EffectType__3__Parameter__4__label[] = "500";
char EffectType__3__Parameter__5__label[] = "1k";
char EffectType__3__Parameter__6__label[] = "2k";
char EffectType__3__Parameter__7__label[] = "4k";
char EffectType__3__Parameter__8__label[] = "8k";
char EffectType__3__Parameter__9__label[] = "16k";
char EffectType__3__Parameter__10__label[] = "";
char EffectType__3__Parameter__11__label[] = "Level";
char EffectType__3__Parameter__12__label[] = "Balance";
char EffectType__3__Parameter__13__label[] = "Bypass Mode";
char EffectType__3__Parameter__14__label[] = "";
char EffectType__3__Parameter__15__label[] = "";
char EffectType__3__Parameter__16__label[] = "";
char EffectType__3__Parameter__17__label[] = "";
char EffectType__3__Parameter__18__label[] = "";
char EffectType__4__Parameter__0__label[] = "Freq 1";
char EffectType__4__Parameter__1__label[] = "Freq 2";
char EffectType__4__Parameter__2__label[] = "Freq 3";
char EffectType__4__Parameter__3__label[] = "Freq 4";
char EffectType__4__Parameter__4__label[] = "Freq 5";
char EffectType__4__Parameter__5__label[] = "Q1";
char EffectType__4__Parameter__6__label[] = "Q2";
char EffectType__4__Parameter__7__label[] = "Q3";
char EffectType__4__Parameter__8__label[] = "Q4";
char EffectType__4__Parameter__9__label[] = "Q5";
char EffectType__4__Parameter__10__label[] = "Gain 1";
char EffectType__4__Parameter__11__label[] = "Gain 2";
char EffectType__4__Parameter__12__label[] = "Gain 3";
char EffectType__4__Parameter__13__label[] = "Gain 4";
char EffectType__4__Parameter__14__label[] = "Gain 5";
char EffectType__4__Parameter__15__label[] = "Frequency 1 Type";
char EffectType__4__Parameter__16__label[] = "Frequency 5 Type";
char EffectType__4__Parameter__17__label[] = "";
char EffectType__4__Parameter__18__label[] = "";
char EffectType__4__Parameter__19__label[] = "Level";
char EffectType__4__Parameter__20__label[] = "Balance";
char EffectType__4__Parameter__21__label[] = "Bypass Mode";
char EffectType__4__Parameter__22__label[] = "";
char EffectType__4__Parameter__23__label[] = "";
char EffectType__5__Parameter__0__label[] = "Amp Type";   //Corrected
char EffectType__5__Parameter__1__label[] = "Drive";
char EffectType__5__Parameter__2__label[] = "Bass";
char EffectType__5__Parameter__3__label[] = "Mid";
char EffectType__5__Parameter__4__label[] = "Treb";
char EffectType__5__Parameter__5__label[] = "Master Vol";
char EffectType__5__Parameter__6__label[] = "Low Cut";
char EffectType__5__Parameter__7__label[] = "Hi Cut";
char EffectType__5__Parameter__8__label[] = "Tone Freq";
char EffectType__5__Parameter__9__label[] = "XFormer Grind"; //""
char EffectType__5__Parameter__10__label[] = "Bright Cap";
char EffectType__5__Parameter__11__label[] = "";
char EffectType__5__Parameter__12__label[] = "XFormer Low Freq";
char EffectType__5__Parameter__13__label[] = "XFormer Hi Freq";
char EffectType__5__Parameter__14__label[] = "Tone Location";
char EffectType__5__Parameter__15__label[] = "Input Select";
char EffectType__5__Parameter__16__label[] = "Depth";
char EffectType__5__Parameter__17__label[] = "";
char EffectType__5__Parameter__18__label[] = "";
char EffectType__5__Parameter__19__label[] = "Supply Sag";
char EffectType__5__Parameter__20__label[] = "Presence";
char EffectType__5__Parameter__21__label[] = "Level";
char EffectType__5__Parameter__22__label[] = "Balance";
char EffectType__5__Parameter__23__label[] = "Bypass Mode";
char EffectType__5__Parameter__24__label[] = "Negative Feedback";
char EffectType__5__Parameter__25__label[] = "Presence Freq";
char EffectType__5__Parameter__26__label[] = "Low Res Freq";
char EffectType__5__Parameter__27__label[] = "Low Resonance";
char EffectType__5__Parameter__28__label[] = "";
char EffectType__5__Parameter__29__label[] = "Depth Freq";
char EffectType__5__Parameter__30__label[] = "";
char EffectType__5__Parameter__31__label[] = "MV Cap";
char EffectType__5__Parameter__32__label[] = "";
char EffectType__5__Parameter__33__label[] = "Harmonics";
char EffectType__5__Parameter__34__label[] = "Tonestack Type";
char EffectType__5__Parameter__35__label[] = "B+ Time Constant";
char EffectType__5__Parameter__36__label[] = "Pwr Amp Grid Bias";//"Power Tube Bias";
char EffectType__5__Parameter__37__label[] = "";
char EffectType__5__Parameter__38__label[] = "";
char EffectType__5__Parameter__39__label[] = "Bright";
char EffectType__5__Parameter__40__label[] = "Boost";
char EffectType__5__Parameter__41__label[] = "Low Res Q";
char EffectType__5__Parameter__42__label[] = "Preamp Bias";
char EffectType__5__Parameter__43__label[] = "Hi Freq";
char EffectType__5__Parameter__44__label[] = "Hi Resonance";
char EffectType__5__Parameter__45__label[] = "CUT"; //"";
char EffectType__5__Parameter__46__label[] = "XFormer Drive";
char EffectType__5__Parameter__47__label[] = "Input Trim";
char EffectType__5__Parameter__48__label[] = "Preamp Hardness"; //"Triode Hardness";
char EffectType__5__Parameter__49__label[] = "MV Location";
char EffectType__5__Parameter__50__label[] = "Speaker Drive";
char EffectType__5__Parameter__51__label[] = "XFormer Match";
char EffectType__5__Parameter__52__label[] = "";
char EffectType__5__Parameter__53__label[] = "";
char EffectType__5__Parameter__54__label[] = "Saturation";
char EffectType__5__Parameter__55__label[] = "63";
char EffectType__5__Parameter__56__label[] = "125";
char EffectType__5__Parameter__57__label[] = "250";
char EffectType__5__Parameter__58__label[] = "500";
char EffectType__5__Parameter__59__label[] = "1K";
char EffectType__5__Parameter__60__label[] = "2K";
char EffectType__5__Parameter__61__label[] = "4K";
char EffectType__5__Parameter__62__label[] = "8K";
char EffectType__5__Parameter__63__label[] = "Bias Excursion";
char EffectType__5__Parameter__64__label[] = "Excursion Time";
char EffectType__5__Parameter__65__label[] = "Recovery Time";
char EffectType__5__Parameter__66__label[] = "Triode 2 Plate Freq";
char EffectType__5__Parameter__67__label[] = "Triode 1 Plate Freq";
char EffectType__5__Parameter__68__label[] = "Power Tube Type";
char EffectType__5__Parameter__69__label[] = "Amp Voicing";
char EffectType__5__Parameter__70__label[] = "Out Comp Clarity";
char EffectType__5__Parameter__71__label[] = "Character Q";
char EffectType__5__Parameter__72__label[] = "Character Freq";
char EffectType__5__Parameter__73__label[] = "Character Amt";
char EffectType__5__Parameter__74__label[] = "Overdrive";
char EffectType__5__Parameter__75__label[] = "Out Comp Amount";
char EffectType__5__Parameter__76__label[] = "Out Comp Threshold";//"Dynamics Time";
char EffectType__5__Parameter__77__label[] = "Master Vol Trim";
char EffectType__5__Parameter__78__label[] = "Fat";
char EffectType__5__Parameter__79__label[] = "Definition";
char EffectType__5__Parameter__80__label[] = "Preamp CF Compress"; //""
char EffectType__5__Parameter__81__label[] = "Preamp CF Time"; //"Preamp Dyn Time";
char EffectType__5__Parameter__82__label[] = "Use MIMIC(TM)";
char EffectType__5__Parameter__83__label[] = "Pick Attack";
char EffectType__5__Parameter__84__label[] = "Dynamic Presence";
char EffectType__5__Parameter__85__label[] = "Dynamic Depth";
char EffectType__5__Parameter__86__label[] = "Power Supply Type";
char EffectType__5__Parameter__87__label[] = "AC Line Freq";
char EffectType__5__Parameter__88__label[] = "Pwr Amp Hardness";
char EffectType__5__Parameter__89__label[] = "Tremolo Freq";
char EffectType__5__Parameter__90__label[] = "Tremolo Depth";

// AMP - for Quantum 6
char EffectType__5__Parameter__91__label[] = "";
char EffectType__5__Parameter__92__label[] = "";
char EffectType__5__Parameter__93__label[] = "Cathode Resistance";
char EffectType__5__Parameter__94__label[] = "";
char EffectType__5__Parameter__95__label[] = "";
char EffectType__5__Parameter__96__label[] = "Preamp Sag";
char EffectType__5__Parameter__97__label[] = "";
char EffectType__5__Parameter__98__label[] = "Pwr Amp Bias";
char EffectType__5__Parameter__99__label[] = "Preamp Dynamics";
char EffectType__5__Parameter__100__label[] = "Hi Freq Slope";
char EffectType__5__Parameter__101__label[] = "Variac";
char EffectType__5__Parameter__102__label[] = "Character Type";
char EffectType__5__Parameter__103__label[] = "";
char EffectType__5__Parameter__104__label[] = "Presence Shift";
char EffectType__5__Parameter__105__label[] = "";
char EffectType__5__Parameter__106__label[] = "";
char EffectType__5__Parameter__107__label[] = "";
char EffectType__5__Parameter__108__label[] = "";
char EffectType__5__Parameter__109__label[] = "Out Comp Type";
char EffectType__5__Parameter__110__label[] = "";
char EffectType__5__Parameter__111__label[] = "Preamp CF Comp Type";
char EffectType__5__Parameter__112__label[] = "Preamp CF Hardness";


char EffectType__6__Parameter__0__label[] = "Cab L";
char EffectType__6__Parameter__1__label[] = "Mic L";
char EffectType__6__Parameter__2__label[] = "Cab R";
char EffectType__6__Parameter__3__label[] = "Mic R";
char EffectType__6__Parameter__4__label[] = "Link";
char EffectType__6__Parameter__5__label[] = "Level L";
char EffectType__6__Parameter__6__label[] = "Level R";
char EffectType__6__Parameter__7__label[] = "Pan L";
char EffectType__6__Parameter__8__label[] = "Pan R";
char EffectType__6__Parameter__9__label[] = "Level";
char EffectType__6__Parameter__10__label[] = "Balance";
char EffectType__6__Parameter__11__label[] = "Bypass Mode";
char EffectType__6__Parameter__12__label[] = "";
char EffectType__6__Parameter__13__label[] = "";
char EffectType__6__Parameter__14__label[] = "";
char EffectType__6__Parameter__15__label[] = "";
char EffectType__6__Parameter__16__label[] = "Room Level";
char EffectType__6__Parameter__17__label[] = "Room Size";
char EffectType__6__Parameter__18__label[] = "Mic Spacing";
char EffectType__6__Parameter__19__label[] = "Low Cut";
char EffectType__6__Parameter__20__label[] = "High Cut";
char EffectType__6__Parameter__21__label[] = "Cab Size";
char EffectType__6__Parameter__22__label[] = "Proximity L";
char EffectType__6__Parameter__23__label[] = "Air";
char EffectType__6__Parameter__24__label[] = "Motor Drive";
char EffectType__6__Parameter__25__label[] = "Air Frequency";
char EffectType__6__Parameter__26__label[] = "Delay Left";
char EffectType__6__Parameter__27__label[] = "Delay Right";
char EffectType__6__Parameter__28__label[] = "Proximity R";
char EffectType__7__Parameter__0__label[] = "";
char EffectType__7__Parameter__1__label[] = "Time";
char EffectType__7__Parameter__2__label[] = "High Cut";
char EffectType__7__Parameter__3__label[] = "Color";
char EffectType__7__Parameter__4__label[] = "Wall Diffusion";
char EffectType__7__Parameter__5__label[] = "Size";
char EffectType__7__Parameter__6__label[] = "Tail Delay";
char EffectType__7__Parameter__7__label[] = "Early Level";
char EffectType__7__Parameter__8__label[] = "Reverb Level";
char EffectType__7__Parameter__9__label[] = "PreDelay";
char EffectType__7__Parameter__10__label[] = "Low Cut";
char EffectType__7__Parameter__11__label[] = "Mod Depth";
char EffectType__7__Parameter__12__label[] = "Mod Rate";
char EffectType__7__Parameter__13__label[] = "Mix";
char EffectType__7__Parameter__14__label[] = "Level";
char EffectType__7__Parameter__15__label[] = "Balance";
char EffectType__7__Parameter__16__label[] = "Bypass Mode";
char EffectType__7__Parameter__17__label[] = "";
char EffectType__7__Parameter__18__label[] = "Input Gain";
char EffectType__7__Parameter__19__label[] = "Echo Density";
char EffectType__7__Parameter__20__label[] = "Input Diffusion";
char EffectType__7__Parameter__21__label[] = "Diffusion Time";
char EffectType__7__Parameter__22__label[] = "";
char EffectType__7__Parameter__23__label[] = "Number Springs";
char EffectType__7__Parameter__24__label[] = "Spring Tone";
char EffectType__7__Parameter__25__label[] = "";
char EffectType__7__Parameter__26__label[] = "Frequency 1";
char EffectType__7__Parameter__27__label[] = "Frequency 2";
char EffectType__7__Parameter__28__label[] = "Q 1";
char EffectType__7__Parameter__29__label[] = "Q 2";
char EffectType__7__Parameter__30__label[] = "Gain 1";
char EffectType__7__Parameter__31__label[] = "Gain 2";
char EffectType__7__Parameter__32__label[] = "Spring Drive";
char EffectType__7__Parameter__33__label[] = "LF Time";
char EffectType__7__Parameter__34__label[] = "LF Crossover";
char EffectType__8__Parameter__0__label[] = "";
char EffectType__8__Parameter__1__label[] = "";
char EffectType__8__Parameter__2__label[] = "Head 1 Time";
char EffectType__8__Parameter__3__label[] = "Head 2 Ratio";
char EffectType__8__Parameter__4__label[] = "Feedback 1";
char EffectType__8__Parameter__5__label[] = "Feedback L";
char EffectType__8__Parameter__6__label[] = "Feedback 2";
char EffectType__8__Parameter__7__label[] = "Echo Pan";
char EffectType__8__Parameter__8__label[] = "Spread (Width)";
char EffectType__8__Parameter__9__label[] = "Head 1 Tempo";
char EffectType__8__Parameter__10__label[] = "Low Cut";
char EffectType__8__Parameter__11__label[] = "High Cut";
char EffectType__8__Parameter__12__label[] = "LFO1 Rate";
char EffectType__8__Parameter__13__label[] = "LFO2 Rate";
char EffectType__8__Parameter__14__label[] = "LFO1 Depth";
char EffectType__8__Parameter__15__label[] = "LFO2 Depth";
char EffectType__8__Parameter__16__label[] = "Drive";
char EffectType__8__Parameter__17__label[] = "Mix";
char EffectType__8__Parameter__18__label[] = "Level";
char EffectType__8__Parameter__19__label[] = "Balance";
char EffectType__8__Parameter__20__label[] = "Bypass Mode";
char EffectType__8__Parameter__21__label[] = "";
char EffectType__8__Parameter__22__label[] = "";
char EffectType__8__Parameter__23__label[] = "Input Gain";
char EffectType__8__Parameter__24__label[] = "LFO1 Type";
char EffectType__8__Parameter__25__label[] = "LFO2 Type";
char EffectType__8__Parameter__26__label[] = "Time R";
char EffectType__8__Parameter__27__label[] = "Hold";
char EffectType__8__Parameter__28__label[] = "Master Feedback";
char EffectType__8__Parameter__29__label[] = "Tempo R";
char EffectType__8__Parameter__30__label[] = "Feedback L>R";
char EffectType__8__Parameter__31__label[] = "Feedback R>L";
char EffectType__8__Parameter__32__label[] = "Level 1";
char EffectType__8__Parameter__33__label[] = "Level 2";
char EffectType__8__Parameter__34__label[] = "Pan 1";
char EffectType__8__Parameter__35__label[] = "Pan 2";
char EffectType__8__Parameter__36__label[] = "LFO1 Phase";
char EffectType__8__Parameter__37__label[] = "LFO2 Phase";
char EffectType__8__Parameter__38__label[] = "XFade Time";
char EffectType__8__Parameter__39__label[] = "Run";
char EffectType__8__Parameter__40__label[] = "Trigger Restart";
char EffectType__8__Parameter__41__label[] = "Filter Slope";
char EffectType__8__Parameter__42__label[] = "Ducker Attenuation";
char EffectType__8__Parameter__43__label[] = "Ducker Threshold";
char EffectType__8__Parameter__44__label[] = "Ducker Release";
char EffectType__8__Parameter__45__label[] = "Diffusion";
char EffectType__8__Parameter__46__label[] = "Diff Time";
char EffectType__8__Parameter__47__label[] = "Phase Reverse";
char EffectType__8__Parameter__48__label[] = "LFO1 Target";
char EffectType__8__Parameter__49__label[] = "LFO2 Target";
char EffectType__8__Parameter__50__label[] = "LFO1 Tempo";
char EffectType__8__Parameter__51__label[] = "LFO2 Tempo";
char EffectType__8__Parameter__52__label[] = "Sweep Rate";
char EffectType__8__Parameter__53__label[] = "Sweep Type";
char EffectType__8__Parameter__54__label[] = "Sweep Phase";
char EffectType__8__Parameter__55__label[] = "Sweep Tempo";
char EffectType__8__Parameter__56__label[] = "Start Freq";
char EffectType__8__Parameter__57__label[] = "Stop Freq";
char EffectType__8__Parameter__58__label[] = "Resonance";
char EffectType__8__Parameter__59__label[] = "Q";
char EffectType__8__Parameter__60__label[] = "Bit Reduction";
char EffectType__8__Parameter__61__label[] = "Frequency 1";
char EffectType__8__Parameter__62__label[] = "Frequency 2";
char EffectType__8__Parameter__63__label[] = "Q 1";
char EffectType__8__Parameter__64__label[] = "Q 2";
char EffectType__8__Parameter__65__label[] = "Gain 1";
char EffectType__8__Parameter__66__label[] = "Gain 2";
char EffectType__8__Parameter__67__label[] = "LFO Depth Range";
char EffectType__8__Parameter__68__label[] = "Motor Speed";
char EffectType__8__Parameter__69__label[] = "Right Post Delay";
char EffectType__9__Parameter__0__label[] = "Time 1";
char EffectType__9__Parameter__1__label[] = "Time 2";
char EffectType__9__Parameter__2__label[] = "Time 3";
char EffectType__9__Parameter__3__label[] = "Time 4";
char EffectType__9__Parameter__4__label[] = "Tempo 1";
char EffectType__9__Parameter__5__label[] = "Tempo 2";
char EffectType__9__Parameter__6__label[] = "Tempo 3";
char EffectType__9__Parameter__7__label[] = "Tempo 4";
char EffectType__9__Parameter__8__label[] = "Level 1";
char EffectType__9__Parameter__9__label[] = "Level 2";
char EffectType__9__Parameter__10__label[] = "Level 3";
char EffectType__9__Parameter__11__label[] = "Level 4";
char EffectType__9__Parameter__12__label[] = "Feedback 1";
char EffectType__9__Parameter__13__label[] = "Feedback 2";
char EffectType__9__Parameter__14__label[] = "Feedback 3";
char EffectType__9__Parameter__15__label[] = "Feedback 4";
char EffectType__9__Parameter__16__label[] = "Pan 1";
char EffectType__9__Parameter__17__label[] = "Pan 2";
char EffectType__9__Parameter__18__label[] = "Pan 3";
char EffectType__9__Parameter__19__label[] = "Pan 4";
char EffectType__9__Parameter__20__label[] = "LFO1 Rate";
char EffectType__9__Parameter__21__label[] = "LFO2 Rate";
char EffectType__9__Parameter__22__label[] = "LFO3 Rate";
char EffectType__9__Parameter__23__label[] = "LFO4 Rate";
char EffectType__9__Parameter__24__label[] = "LFO1 Tempo";
char EffectType__9__Parameter__25__label[] = "LFO2 Tempo";
char EffectType__9__Parameter__26__label[] = "LFO3 Tempo";
char EffectType__9__Parameter__27__label[] = "LFO4 Tempo";
char EffectType__9__Parameter__28__label[] = "Mix";
char EffectType__9__Parameter__29__label[] = "Level";
char EffectType__9__Parameter__30__label[] = "Balance";
char EffectType__9__Parameter__31__label[] = "Bypass Mode";
char EffectType__9__Parameter__32__label[] = "";
char EffectType__9__Parameter__33__label[] = "Input Gain";
char EffectType__9__Parameter__34__label[] = "";
char EffectType__9__Parameter__35__label[] = "";
char EffectType__9__Parameter__36__label[] = "Decay time";
char EffectType__9__Parameter__37__label[] = "Diffusion";
char EffectType__9__Parameter__38__label[] = "Diffusion";
char EffectType__9__Parameter__39__label[] = "Diffusion time";
char EffectType__9__Parameter__40__label[] = "Ducker Threshold";
char EffectType__9__Parameter__41__label[] = "Crossfade";
char EffectType__9__Parameter__42__label[] = "Mstr Time";
char EffectType__9__Parameter__43__label[] = "Mstr Level";
char EffectType__9__Parameter__44__label[] = "Mstr Pan";
char EffectType__9__Parameter__45__label[] = "Mstr Frequency";
char EffectType__9__Parameter__46__label[] = "Mstr Q";
char EffectType__9__Parameter__47__label[] = "Mstr Feedback";
char EffectType__9__Parameter__48__label[] = "Master Pitch";
char EffectType__9__Parameter__49__label[] = "Master Detune";
char EffectType__9__Parameter__50__label[] = "Detune 1";
char EffectType__9__Parameter__51__label[] = "Detune 2";
char EffectType__9__Parameter__52__label[] = "Detune 3";
char EffectType__9__Parameter__53__label[] = "Detune 4";
char EffectType__9__Parameter__54__label[] = "Shift 1";
char EffectType__9__Parameter__55__label[] = "Shift 2";
char EffectType__9__Parameter__56__label[] = "Shift 3";
char EffectType__9__Parameter__57__label[] = "Shift 4";
char EffectType__9__Parameter__58__label[] = "Freq 1";
char EffectType__9__Parameter__59__label[] = "Freq 2";
char EffectType__9__Parameter__60__label[] = "Freq 3";
char EffectType__9__Parameter__61__label[] = "Freq 4";
char EffectType__9__Parameter__62__label[] = "Q 1";
char EffectType__9__Parameter__63__label[] = "Q 2";
char EffectType__9__Parameter__64__label[] = "Q 3";
char EffectType__9__Parameter__65__label[] = "Q 4";
char EffectType__9__Parameter__66__label[] = "Mstr Rate";
char EffectType__9__Parameter__67__label[] = "Ducker Attenuation";
char EffectType__9__Parameter__68__label[] = "Mstr Depth";
char EffectType__9__Parameter__69__label[] = "Direction";
char EffectType__9__Parameter__70__label[] = "Tape Speed";
char EffectType__9__Parameter__71__label[] = "LFO1 Depth";
char EffectType__9__Parameter__72__label[] = "LFO2 Depth";
char EffectType__9__Parameter__73__label[] = "LFO3 Depth";
char EffectType__9__Parameter__74__label[] = "LFO4 Depth";
char EffectType__9__Parameter__75__label[] = "LFO1 Master";
char EffectType__9__Parameter__76__label[] = "FB Send";
char EffectType__9__Parameter__77__label[] = "FB Return";
char EffectType__9__Parameter__78__label[] = "Mono/Stereo";
char EffectType__9__Parameter__79__label[] = "Delay time";
char EffectType__9__Parameter__80__label[] = "";
char EffectType__9__Parameter__81__label[] = "Quantize";
char EffectType__9__Parameter__82__label[] = "Decay";
char EffectType__9__Parameter__83__label[] = "";
char EffectType__9__Parameter__84__label[] = "Number of Taps";
char EffectType__9__Parameter__85__label[] = "Shuffle";
char EffectType__9__Parameter__86__label[] = "Delay tempo";
char EffectType__9__Parameter__87__label[] = "Spread";
char EffectType__9__Parameter__88__label[] = "Pan Shape";
char EffectType__9__Parameter__89__label[] = "Pan alpha";
char EffectType__9__Parameter__90__label[] = "Low cut";
char EffectType__9__Parameter__91__label[] = "High cut";
char EffectType__9__Parameter__92__label[] = "Ratio";
char EffectType__9__Parameter__93__label[] = "Feedback";
char EffectType__9__Parameter__94__label[] = "Tap1 Time";
char EffectType__9__Parameter__95__label[] = "Tap2 Time";
char EffectType__9__Parameter__96__label[] = "Tap3 Time";
char EffectType__9__Parameter__97__label[] = "Tap4 Time";
char EffectType__9__Parameter__98__label[] = "Tap5 Time";
char EffectType__9__Parameter__99__label[] = "Tap6 Time";
char EffectType__9__Parameter__100__label[] = "Tap7 Time";
char EffectType__9__Parameter__101__label[] = "Tap8 Time";
char EffectType__9__Parameter__102__label[] = "Tap9 Time";
char EffectType__9__Parameter__103__label[] = "Tap10 Time";
char EffectType__9__Parameter__104__label[] = "Tap1 Level";
char EffectType__9__Parameter__105__label[] = "Tap2 Level";
char EffectType__9__Parameter__106__label[] = "Tap3 Level";
char EffectType__9__Parameter__107__label[] = "Tap4 Level";
char EffectType__9__Parameter__108__label[] = "Tap5 Level";
char EffectType__9__Parameter__109__label[] = "Tap6 Level";
char EffectType__9__Parameter__110__label[] = "Tap7 Level";
char EffectType__9__Parameter__111__label[] = "Tap8 Level";
char EffectType__9__Parameter__112__label[] = "Tap9 Level";
char EffectType__9__Parameter__113__label[] = "Tap10 Level";
char EffectType__9__Parameter__114__label[] = "";
char EffectType__9__Parameter__115__label[] = "";
char EffectType__9__Parameter__116__label[] = "Ducker Release";
char EffectType__10__Parameter__0__label[] = "";
char EffectType__10__Parameter__1__label[] = "Voices";
char EffectType__10__Parameter__2__label[] = "Rate";
char EffectType__10__Parameter__3__label[] = "Tempo";
char EffectType__10__Parameter__4__label[] = "Depth";
char EffectType__10__Parameter__5__label[] = "Hi Cut Freq";
char EffectType__10__Parameter__6__label[] = "Delay time";
char EffectType__10__Parameter__7__label[] = "LFO Phase";
char EffectType__10__Parameter__8__label[] = "LFO Type";
char EffectType__10__Parameter__9__label[] = "Auto depth";
char EffectType__10__Parameter__10__label[] = "Mix";
char EffectType__10__Parameter__11__label[] = "Level";
char EffectType__10__Parameter__12__label[] = "Balance";
char EffectType__10__Parameter__13__label[] = "Bypass Mode";
char EffectType__10__Parameter__14__label[] = "";
char EffectType__10__Parameter__15__label[] = "";
char EffectType__10__Parameter__16__label[] = "Phase Reverse";
char EffectType__10__Parameter__17__label[] = "Width";
char EffectType__10__Parameter__18__label[] = "LFO2 Rate";
char EffectType__10__Parameter__19__label[] = "LFO2 Depth";
char EffectType__10__Parameter__20__label[] = "Drive";
char EffectType__10__Parameter__21__label[] = "Low Cut Freq";
char EffectType__10__Parameter__22__label[] = "Spread";
char EffectType__11__Parameter__0__label[] = "";
char EffectType__11__Parameter__1__label[] = "Rate";
char EffectType__11__Parameter__2__label[] = "Tempo";
char EffectType__11__Parameter__3__label[] = "Depth";
char EffectType__11__Parameter__4__label[] = "Feedback";
char EffectType__11__Parameter__5__label[] = "Delay Time";
char EffectType__11__Parameter__6__label[] = "Dry Delay Shift";
char EffectType__11__Parameter__7__label[] = "LFO Phase";
char EffectType__11__Parameter__8__label[] = "LFO Type";
char EffectType__11__Parameter__9__label[] = "LFO Hicut";
char EffectType__11__Parameter__10__label[] = "Auto depth";
char EffectType__11__Parameter__11__label[] = "Mix";
char EffectType__11__Parameter__12__label[] = "Level";
char EffectType__11__Parameter__13__label[] = "Balance";
char EffectType__11__Parameter__14__label[] = "Bypass Mode";
char EffectType__11__Parameter__15__label[] = "";
char EffectType__11__Parameter__16__label[] = "";
char EffectType__11__Parameter__17__label[] = "Phase Reverse";
char EffectType__11__Parameter__18__label[] = "Thru-Zero";
char EffectType__11__Parameter__19__label[] = "Hi Cut Freq";
char EffectType__11__Parameter__20__label[] = "Drive";
char EffectType__11__Parameter__21__label[] = "Low Cut Freq";
char EffectType__11__Parameter__22__label[] = "Spread";
char EffectType__12__Parameter__0__label[] = "Rate";
char EffectType__12__Parameter__1__label[] = "Low Rotor Depth";
char EffectType__12__Parameter__2__label[] = "Hi Rotor Depth";
char EffectType__12__Parameter__3__label[] = "Hi Rotor Level";
char EffectType__12__Parameter__4__label[] = "Tempo";
char EffectType__12__Parameter__5__label[] = "Mix";
char EffectType__12__Parameter__6__label[] = "Level";
char EffectType__12__Parameter__7__label[] = "Balance";
char EffectType__12__Parameter__8__label[] = "Bypass Mode";
char EffectType__12__Parameter__9__label[] = "";
char EffectType__12__Parameter__10__label[] = "Hi Rotor Horn Length";
char EffectType__12__Parameter__11__label[] = "";
char EffectType__12__Parameter__12__label[] = "HF Mic Spacing";
char EffectType__12__Parameter__13__label[] = "Low Rate Mult";
char EffectType__12__Parameter__14__label[] = "Low Time Const";
char EffectType__12__Parameter__15__label[] = "Hi Time Const";
char EffectType__12__Parameter__16__label[] = "LF Mic Spacing";
char EffectType__12__Parameter__17__label[] = "Drive";
char EffectType__13__Parameter__0__label[] = "";
char EffectType__13__Parameter__1__label[] = "Order";
char EffectType__13__Parameter__2__label[] = "Rate";
char EffectType__13__Parameter__3__label[] = "LFO Type";
char EffectType__13__Parameter__4__label[] = "Tempo";
char EffectType__13__Parameter__5__label[] = "Depth";
char EffectType__13__Parameter__6__label[] = "Feedback";
char EffectType__13__Parameter__7__label[] = "Frequency Start";
char EffectType__13__Parameter__8__label[] = "Frequency Span";
char EffectType__13__Parameter__9__label[] = "LFO Phase";
char EffectType__13__Parameter__10__label[] = "Bulb Bias";
char EffectType__13__Parameter__11__label[] = "Mix";
char EffectType__13__Parameter__12__label[] = "Level";
char EffectType__13__Parameter__13__label[] = "Balance";
char EffectType__13__Parameter__14__label[] = "Bypass Mode";
char EffectType__13__Parameter__15__label[] = "";
char EffectType__13__Parameter__16__label[] = "";
char EffectType__13__Parameter__17__label[] = "Vibe Mode";
char EffectType__13__Parameter__18__label[] = "Fdbk Tap";
char EffectType__13__Parameter__19__label[] = "Tone";
char EffectType__14__Parameter__0__label[] = "Filter Type";
char EffectType__14__Parameter__1__label[] = "Frequency Min";
char EffectType__14__Parameter__2__label[] = "Frequency Max";
char EffectType__14__Parameter__3__label[] = "Resonance";
char EffectType__14__Parameter__4__label[] = "Tracking";
char EffectType__14__Parameter__5__label[] = "Control";
char EffectType__14__Parameter__6__label[] = "Level";
char EffectType__14__Parameter__7__label[] = "Balance";
char EffectType__14__Parameter__8__label[] = "Bypass Mode";
char EffectType__14__Parameter__9__label[] = "";
char EffectType__14__Parameter__10__label[] = "Drive";
char EffectType__14__Parameter__11__label[] = "";
char EffectType__14__Parameter__12__label[] = "";
char EffectType__15__Parameter__0__label[] = "Start";
char EffectType__15__Parameter__1__label[] = "Mid";
char EffectType__15__Parameter__2__label[] = "End";
char EffectType__15__Parameter__3__label[] = "Resonance";
char EffectType__15__Parameter__4__label[] = "Control";
char EffectType__15__Parameter__5__label[] = "Mix";
char EffectType__15__Parameter__6__label[] = "Level";
char EffectType__15__Parameter__7__label[] = "Balance";
char EffectType__15__Parameter__8__label[] = "Bypass Mode";
char EffectType__15__Parameter__9__label[] = "";
char EffectType__15__Parameter__10__label[] = "";
char EffectType__15__Parameter__11__label[] = "";
char EffectType__16__Parameter__0__label[] = "";
char EffectType__16__Parameter__1__label[] = "LFO Type";
char EffectType__16__Parameter__2__label[] = "Rate";
char EffectType__16__Parameter__3__label[] = "Depth";
char EffectType__16__Parameter__4__label[] = "Duty";
char EffectType__16__Parameter__5__label[] = "Tempo";
char EffectType__16__Parameter__6__label[] = "";
char EffectType__16__Parameter__7__label[] = "Level";
char EffectType__16__Parameter__8__label[] = "Balance";
char EffectType__16__Parameter__9__label[] = "Bypass Mode";
char EffectType__16__Parameter__10__label[] = "";
char EffectType__16__Parameter__11__label[] = "LFO Phase";
char EffectType__16__Parameter__12__label[] = "Width";
char EffectType__16__Parameter__13__label[] = "Pan Center";
char EffectType__16__Parameter__14__label[] = "";
char EffectType__17__Parameter__0__label[] = "";
char EffectType__17__Parameter__1__label[] = "Mode";
char EffectType__17__Parameter__2__label[] = "Master Pitch";
char EffectType__17__Parameter__3__label[] = "Control";
char EffectType__17__Parameter__4__label[] = "Voice1 Harmony";
char EffectType__17__Parameter__5__label[] = "Voice2 Harmony";
char EffectType__17__Parameter__6__label[] = "Key";
char EffectType__17__Parameter__7__label[] = "Scale";
char EffectType__17__Parameter__8__label[] = "Track Mode";
char EffectType__17__Parameter__9__label[] = "Voice1 Detune";
char EffectType__17__Parameter__10__label[] = "Voice2 Detune";
char EffectType__17__Parameter__11__label[] = "Start";
char EffectType__17__Parameter__12__label[] = "Stop";
char EffectType__17__Parameter__13__label[] = "Level 1";
char EffectType__17__Parameter__14__label[] = "Level 2";
char EffectType__17__Parameter__15__label[] = "Pan 1";
char EffectType__17__Parameter__16__label[] = "Pan 2";
char EffectType__17__Parameter__17__label[] = "Delay 1";
char EffectType__17__Parameter__18__label[] = "Delay 2";
char EffectType__17__Parameter__19__label[] = "Feedback 1";
char EffectType__17__Parameter__20__label[] = "Feedback 2";
char EffectType__17__Parameter__21__label[] = "Pitch track";
char EffectType__17__Parameter__22__label[] = "Track Adjust";
char EffectType__17__Parameter__23__label[] = "Mix";
char EffectType__17__Parameter__24__label[] = "Level";
char EffectType__17__Parameter__25__label[] = "Balance";
char EffectType__17__Parameter__26__label[] = "Bypass Mode";
char EffectType__17__Parameter__27__label[] = "";
char EffectType__17__Parameter__28__label[] = "Input Gain";
char EffectType__17__Parameter__29__label[] = "";
char EffectType__17__Parameter__30__label[] = "Crossfade";
char EffectType__17__Parameter__31__label[] = "V1 Splice";
char EffectType__17__Parameter__32__label[] = "V2 Splice";
char EffectType__17__Parameter__33__label[] = "Tempo 1";
char EffectType__17__Parameter__34__label[] = "Delay Tempo 2";
char EffectType__17__Parameter__35__label[] = "Spltempo 1";
char EffectType__17__Parameter__36__label[] = "Spltempo 2";
char EffectType__17__Parameter__37__label[] = "Feedback type";
char EffectType__17__Parameter__38__label[] = "Reverse";
char EffectType__17__Parameter__39__label[] = "Hi Cut Frequency";
char EffectType__17__Parameter__40__label[] = "Glide Time";
char EffectType__17__Parameter__41__label[] = "Master Delay";
char EffectType__17__Parameter__42__label[] = "Master Feedback";
char EffectType__17__Parameter__43__label[] = "Master Pan";
char EffectType__17__Parameter__44__label[] = "Master Level";
char EffectType__17__Parameter__45__label[] = "Custom Notes";
char EffectType__17__Parameter__46__label[] = "Note 2";
char EffectType__17__Parameter__47__label[] = "Note 3";
char EffectType__17__Parameter__48__label[] = "Note 4";
char EffectType__17__Parameter__49__label[] = "Note 5";
char EffectType__17__Parameter__50__label[] = "Note 6";
char EffectType__17__Parameter__51__label[] = "Note 7";
char EffectType__17__Parameter__52__label[] = "Note 8";
char EffectType__17__Parameter__53__label[] = "Voice 1 Scale";
char EffectType__17__Parameter__54__label[] = "Voice 2 Scale";
char EffectType__17__Parameter__55__label[] = "Stages";
char EffectType__17__Parameter__56__label[] = "Repeats";
char EffectType__17__Parameter__57__label[] = "Run";
char EffectType__17__Parameter__58__label[] = "Tempo";
char EffectType__17__Parameter__59__label[] = "  Stage 1   Shift";
char EffectType__17__Parameter__60__label[] = "  Stage 2   Shift";
char EffectType__17__Parameter__61__label[] = "  Stage 3   Shift";
char EffectType__17__Parameter__62__label[] = "  Stage 4   Shift";
char EffectType__17__Parameter__63__label[] = "  Stage 5   Shift";
char EffectType__17__Parameter__64__label[] = "  Stage 6   Shift";
char EffectType__17__Parameter__65__label[] = "  Stage 7   Shift";
char EffectType__17__Parameter__66__label[] = "  Stage 8   Shift";
char EffectType__17__Parameter__67__label[] = "  Stage 9   Shift";
char EffectType__17__Parameter__68__label[] = "  Stage 10  Shift";
char EffectType__17__Parameter__69__label[] = "  Stage 11  Shift";
char EffectType__17__Parameter__70__label[] = "  Stage 12  Shift";
char EffectType__17__Parameter__71__label[] = "  Stage 13  Shift";
char EffectType__17__Parameter__72__label[] = "  Stage 14  Shift";
char EffectType__17__Parameter__73__label[] = "  Stage 15  Shift";
char EffectType__17__Parameter__74__label[] = "  Stage 16  Shift";
char EffectType__17__Parameter__75__label[] = "Amplitude Shape";
char EffectType__17__Parameter__76__label[] = "Amplitude Alpha";
char EffectType__17__Parameter__77__label[] = "Pan Shape";
char EffectType__17__Parameter__78__label[] = "Pan Alpha";
char EffectType__17__Parameter__79__label[] = "Delay 1";
char EffectType__17__Parameter__80__label[] = "Delay 2";
char EffectType__17__Parameter__81__label[] = "Pitch Source";
char EffectType__17__Parameter__82__label[] = "Input Mode";
char EffectType__17__Parameter__83__label[] = "Learn";
char EffectType__17__Parameter__84__label[] = "Low Cut Frequency";
char EffectType__18__Parameter__0__label[] = "Type";
char EffectType__18__Parameter__1__label[] = "Frequency";
char EffectType__18__Parameter__2__label[] = "Q";
char EffectType__18__Parameter__3__label[] = "Gain";
char EffectType__18__Parameter__4__label[] = "Level";
char EffectType__18__Parameter__5__label[] = "Balance";
char EffectType__18__Parameter__6__label[] = "Bypass Mode";
char EffectType__18__Parameter__7__label[] = "Order";
char EffectType__18__Parameter__8__label[] = "";
char EffectType__18__Parameter__9__label[] = "Pan Left";
char EffectType__18__Parameter__10__label[] = "Pan Right";
char EffectType__18__Parameter__11__label[] = "Invert";
char EffectType__18__Parameter__12__label[] = "Lowcut";
char EffectType__18__Parameter__13__label[] = "Hicut";
char EffectType__19__Parameter__0__label[] = "";
char EffectType__19__Parameter__1__label[] = "Drive";
char EffectType__19__Parameter__2__label[] = "Tone";
char EffectType__19__Parameter__3__label[] = "Level";
char EffectType__19__Parameter__4__label[] = "Mix";
char EffectType__19__Parameter__5__label[] = "Bypass Mode";
char EffectType__19__Parameter__6__label[] = "Slew Limit";
char EffectType__19__Parameter__7__label[] = "";
char EffectType__19__Parameter__8__label[] = "Low Cut";
char EffectType__19__Parameter__9__label[] = "High Cut";
char EffectType__19__Parameter__10__label[] = "Clip Type";
char EffectType__19__Parameter__11__label[] = "Bias";
char EffectType__19__Parameter__12__label[] = "Bass";
char EffectType__19__Parameter__13__label[] = "Mid";
char EffectType__19__Parameter__14__label[] = "Mid Freq";
char EffectType__19__Parameter__15__label[] = "Treble";
char EffectType__19__Parameter__16__label[] = "Bit Reduce";
char EffectType__19__Parameter__17__label[] = "Input Select";
char EffectType__19__Parameter__18__label[] = "Balance";
char EffectType__19__Parameter__19__label[] = "Sample Rate";
char EffectType__20__Parameter__0__label[] = "Width";
char EffectType__20__Parameter__1__label[] = "Depth";
char EffectType__20__Parameter__2__label[] = "Low cut";
char EffectType__20__Parameter__3__label[] = "High Cut";
char EffectType__20__Parameter__4__label[] = "Level";
char EffectType__20__Parameter__5__label[] = "";
char EffectType__20__Parameter__6__label[] = "";
char EffectType__20__Parameter__7__label[] = "Invert";
char EffectType__20__Parameter__8__label[] = "Pan Left";
char EffectType__20__Parameter__9__label[] = "Pan Right";
char EffectType__20__Parameter__10__label[] = "Balance";
char EffectType__21__Parameter__0__label[] = "Level 1";
char EffectType__21__Parameter__1__label[] = "Level 2";
char EffectType__21__Parameter__2__label[] = "Level 3";
char EffectType__21__Parameter__3__label[] = "Level 4";
char EffectType__21__Parameter__4__label[] = "Pan 1";
char EffectType__21__Parameter__5__label[] = "Pan 2";
char EffectType__21__Parameter__6__label[] = "Pan 3";
char EffectType__21__Parameter__7__label[] = "Pan 4";
char EffectType__21__Parameter__8__label[] = "";
char EffectType__21__Parameter__9__label[] = "";
char EffectType__21__Parameter__10__label[] = "";
char EffectType__21__Parameter__11__label[] = "";
char EffectType__21__Parameter__12__label[] = "";
char EffectType__21__Parameter__13__label[] = "";
char EffectType__21__Parameter__14__label[] = "";
char EffectType__21__Parameter__15__label[] = "";
char EffectType__21__Parameter__16__label[] = "Level";
char EffectType__21__Parameter__17__label[] = "Balance";
char EffectType__21__Parameter__18__label[] = "Bypass Mode";
char EffectType__21__Parameter__19__label[] = "";
char EffectType__22__Parameter__0__label[] = "Gain 1";
char EffectType__22__Parameter__1__label[] = "Gain 2";
char EffectType__22__Parameter__2__label[] = "Gain 3";
char EffectType__22__Parameter__3__label[] = "Gain 4";
char EffectType__22__Parameter__4__label[] = "Balance 1";
char EffectType__22__Parameter__5__label[] = "Balance 2";
char EffectType__22__Parameter__6__label[] = "Balance 3";
char EffectType__22__Parameter__7__label[] = "Balance 4";
char EffectType__22__Parameter__8__label[] = "Master level";
char EffectType__22__Parameter__9__label[] = "Output mode";
char EffectType__23__Parameter__0__label[] = "";
char EffectType__23__Parameter__1__label[] = "";
char EffectType__24__Parameter__0__label[] = "";
char EffectType__24__Parameter__1__label[] = "";
char EffectType__24__Parameter__2__label[] = "";
char EffectType__24__Parameter__3__label[] = "";
char EffectType__24__Parameter__4__label[] = "";
char EffectType__24__Parameter__5__label[] = "";
char EffectType__25__Parameter__0__label[] = "Type";
char EffectType__25__Parameter__1__label[] = "Frequency";
char EffectType__25__Parameter__2__label[] = "Track";
char EffectType__25__Parameter__3__label[] = "Shift";
char EffectType__25__Parameter__4__label[] = "Tune";
char EffectType__25__Parameter__5__label[] = "Duty";
char EffectType__25__Parameter__6__label[] = "Voice 1  Level";
char EffectType__25__Parameter__7__label[] = "Voice 1    Pan";
char EffectType__25__Parameter__8__label[] = "Attack";
char EffectType__25__Parameter__9__label[] = "Filter";
char EffectType__25__Parameter__10__label[] = "Q";
char EffectType__25__Parameter__11__label[] = "Type";
char EffectType__25__Parameter__12__label[] = "Frequency";
char EffectType__25__Parameter__13__label[] = "Track";
char EffectType__25__Parameter__14__label[] = "Shift";
char EffectType__25__Parameter__15__label[] = "Tune";
char EffectType__25__Parameter__16__label[] = "Duty";
char EffectType__25__Parameter__17__label[] = "Voice 2  Level";
char EffectType__25__Parameter__18__label[] = "Voice 2    Pan";
char EffectType__25__Parameter__19__label[] = "Attack";
char EffectType__25__Parameter__20__label[] = "Filter";
char EffectType__25__Parameter__21__label[] = "Q";
char EffectType__25__Parameter__22__label[] = "";
char EffectType__25__Parameter__23__label[] = "Mix";
char EffectType__25__Parameter__24__label[] = "Level";
char EffectType__25__Parameter__25__label[] = "Pan";
char EffectType__25__Parameter__26__label[] = "Bypass Mode";
char EffectType__25__Parameter__27__label[] = "";
char EffectType__25__Parameter__28__label[] = "";
char EffectType__25__Parameter__29__label[] = "Type";
char EffectType__25__Parameter__30__label[] = "Frequency";
char EffectType__25__Parameter__31__label[] = "Track";
char EffectType__25__Parameter__32__label[] = "Shift";
char EffectType__25__Parameter__33__label[] = "Tune";
char EffectType__25__Parameter__34__label[] = "Duty";
char EffectType__25__Parameter__35__label[] = "Voice 3  Level";
char EffectType__25__Parameter__36__label[] = "Voice 3    Pan";
char EffectType__25__Parameter__37__label[] = "Attack";
char EffectType__25__Parameter__38__label[] = "Filter";
char EffectType__25__Parameter__39__label[] = "Q";
char EffectType__26__Parameter__0__label[] = "Input Select (Carrier)";
char EffectType__26__Parameter__1__label[] = "Bands";
char EffectType__26__Parameter__2__label[] = "Frequency Min";
char EffectType__26__Parameter__3__label[] = "Frequency Max ";
char EffectType__26__Parameter__4__label[] = "Shift";
char EffectType__26__Parameter__5__label[] = "Freeze";
char EffectType__26__Parameter__6__label[] = "Master Level";
char EffectType__26__Parameter__7__label[] = "Master Pan";
char EffectType__26__Parameter__8__label[] = "Resonance";
char EffectType__26__Parameter__9__label[] = "Attack";
char EffectType__26__Parameter__10__label[] = "Release";
char EffectType__26__Parameter__11__label[] = "Highpass Mix In";
char EffectType__26__Parameter__12__label[] = "Mix";
char EffectType__26__Parameter__13__label[] = "Level";
char EffectType__26__Parameter__14__label[] = "Balance";
char EffectType__26__Parameter__15__label[] = "Bypass Mode";
char EffectType__26__Parameter__16__label[] = "";
char EffectType__26__Parameter__17__label[] = "1";
char EffectType__26__Parameter__18__label[] = "2";
char EffectType__26__Parameter__19__label[] = "3";
char EffectType__26__Parameter__20__label[] = "4";
char EffectType__26__Parameter__21__label[] = "5";
char EffectType__26__Parameter__22__label[] = "6";
char EffectType__26__Parameter__23__label[] = "7";
char EffectType__26__Parameter__24__label[] = "8";
char EffectType__26__Parameter__25__label[] = "9";
char EffectType__26__Parameter__26__label[] = "10";
char EffectType__26__Parameter__27__label[] = "11";
char EffectType__26__Parameter__28__label[] = "12";
char EffectType__26__Parameter__29__label[] = "13";
char EffectType__26__Parameter__30__label[] = "14";
char EffectType__26__Parameter__31__label[] = "15";
char EffectType__26__Parameter__32__label[] = "16";
char EffectType__26__Parameter__33__label[] = "Pan 1";
char EffectType__26__Parameter__34__label[] = "Pan 2";
char EffectType__26__Parameter__35__label[] = "Pan 3";
char EffectType__26__Parameter__36__label[] = "Pan 4";
char EffectType__26__Parameter__37__label[] = "Pan 5";
char EffectType__26__Parameter__38__label[] = "Pan 6";
char EffectType__26__Parameter__39__label[] = "Pan 7";
char EffectType__26__Parameter__40__label[] = "Pan 8";
char EffectType__26__Parameter__41__label[] = "Pan 9";
char EffectType__26__Parameter__42__label[] = "Pan 10";
char EffectType__26__Parameter__43__label[] = "Pan 11";
char EffectType__26__Parameter__44__label[] = "Pan 12";
char EffectType__26__Parameter__45__label[] = "Pan 13";
char EffectType__26__Parameter__46__label[] = "Pan 14";
char EffectType__26__Parameter__47__label[] = "Pan 15";
char EffectType__26__Parameter__48__label[] = "Pan 16";
char EffectType__26__Parameter__49__label[] = "";
char EffectType__27__Parameter__0__label[] = "In Gain";
char EffectType__27__Parameter__1__label[] = "Master level";
char EffectType__27__Parameter__2__label[] = "Time";
char EffectType__27__Parameter__3__label[] = "Number of Taps";
char EffectType__27__Parameter__4__label[] = "Time Shape";
char EffectType__27__Parameter__5__label[] = "Time Alpha";
char EffectType__27__Parameter__6__label[] = "Amplitude shape";
char EffectType__27__Parameter__7__label[] = "Amplitude Alpha";
char EffectType__27__Parameter__8__label[] = "Pan Shape";
char EffectType__27__Parameter__9__label[] = "Pan Alpha";
char EffectType__27__Parameter__10__label[] = "Time Randomize";
char EffectType__27__Parameter__11__label[] = "Mix";
char EffectType__27__Parameter__12__label[] = "Level";
char EffectType__27__Parameter__13__label[] = "Balance";
char EffectType__27__Parameter__14__label[] = "Bypassmode";
char EffectType__27__Parameter__15__label[] = "";
char EffectType__27__Parameter__16__label[] = "";
char EffectType__28__Parameter__0__label[] = "Freq";
char EffectType__28__Parameter__1__label[] = "Freq Multiplier";
char EffectType__28__Parameter__2__label[] = "Lo Level L";
char EffectType__28__Parameter__3__label[] = "Hi level L";
char EffectType__28__Parameter__4__label[] = "Lo Level R";
char EffectType__28__Parameter__5__label[] = "Hi Level R";
char EffectType__28__Parameter__6__label[] = "Lo Pan L";
char EffectType__28__Parameter__7__label[] = "Hi Pan L";
char EffectType__28__Parameter__8__label[] = "Lo Pan R";
char EffectType__28__Parameter__9__label[] = "Hi Pan R";
char EffectType__28__Parameter__10__label[] = "";
char EffectType__28__Parameter__11__label[] = "Level";
char EffectType__28__Parameter__12__label[] = "Balance";
char EffectType__28__Parameter__13__label[] = "Bypass Mode";
char EffectType__28__Parameter__14__label[] = "";
char EffectType__29__Parameter__0__label[] = "Threhold";
char EffectType__29__Parameter__1__label[] = "Attack";
char EffectType__29__Parameter__2__label[] = "Hold";
char EffectType__29__Parameter__3__label[] = "Release";
char EffectType__29__Parameter__4__label[] = "Ratio";
char EffectType__29__Parameter__5__label[] = "Sidechain Select";
char EffectType__29__Parameter__6__label[] = "Low Cut";
char EffectType__29__Parameter__7__label[] = "High Cut";
char EffectType__29__Parameter__8__label[] = "";
char EffectType__29__Parameter__9__label[] = "Level";
char EffectType__29__Parameter__10__label[] = "Balance";
char EffectType__29__Parameter__11__label[] = "Bypass Mode";
char EffectType__29__Parameter__12__label[] = "";
char EffectType__30__Parameter__0__label[] = "Frequency";
char EffectType__30__Parameter__1__label[] = "Frequency multiplier";
char EffectType__30__Parameter__2__label[] = "Track";
char EffectType__30__Parameter__3__label[] = "High Cut";
char EffectType__30__Parameter__4__label[] = "Mix";
char EffectType__30__Parameter__5__label[] = "Level";
char EffectType__30__Parameter__6__label[] = "Balance";
char EffectType__30__Parameter__7__label[] = "Bypass Mode";
char EffectType__30__Parameter__8__label[] = "Global Mix";
char EffectType__30__Parameter__9__label[] = "";
char EffectType__31__Parameter__0__label[] = "Frequency 1";
char EffectType__31__Parameter__1__label[] = "Frequency 2";
char EffectType__31__Parameter__2__label[] = "Thresh 1";
char EffectType__31__Parameter__3__label[] = "Ratio 1";
char EffectType__31__Parameter__4__label[] = "Attack 1";
char EffectType__31__Parameter__5__label[] = "Release 1";
char EffectType__31__Parameter__6__label[] = "Level 1";
char EffectType__31__Parameter__7__label[] = "Detect 1";
char EffectType__31__Parameter__8__label[] = "Mute 1";
char EffectType__31__Parameter__9__label[] = "Thresh 2";
char EffectType__31__Parameter__10__label[] = "Ratio 2";
char EffectType__31__Parameter__11__label[] = "Attack 2";
char EffectType__31__Parameter__12__label[] = "Release 2";
char EffectType__31__Parameter__13__label[] = "Level 2";
char EffectType__31__Parameter__14__label[] = "Detect 2";
char EffectType__31__Parameter__15__label[] = "Mute 2";
char EffectType__31__Parameter__16__label[] = "Thresh 3";
char EffectType__31__Parameter__17__label[] = "Ratio 3";
char EffectType__31__Parameter__18__label[] = "Attack 3";
char EffectType__31__Parameter__19__label[] = "Release 3";
char EffectType__31__Parameter__20__label[] = "Level 3";
char EffectType__31__Parameter__21__label[] = "Detect 3";
char EffectType__31__Parameter__22__label[] = "Mute 3";
char EffectType__31__Parameter__23__label[] = "";
char EffectType__31__Parameter__24__label[] = "Level";
char EffectType__31__Parameter__25__label[] = "Balance";
char EffectType__31__Parameter__26__label[] = "Bypass Mode";
char EffectType__31__Parameter__27__label[] = "";
char EffectType__32__Parameter__0__label[] = "Mstr Time";
char EffectType__32__Parameter__1__label[] = "Mstr Level";
char EffectType__32__Parameter__2__label[] = "Mstr Pan";
char EffectType__32__Parameter__3__label[] = "Mstr Rate";
char EffectType__32__Parameter__4__label[] = "Mstr Depth";
char EffectType__32__Parameter__5__label[] = "Feedback";
char EffectType__32__Parameter__6__label[] = "Time 1";
char EffectType__32__Parameter__7__label[] = "Time 2";
char EffectType__32__Parameter__8__label[] = "Time 3";
char EffectType__32__Parameter__9__label[] = "Time 4";
char EffectType__32__Parameter__10__label[] = "Level 1";
char EffectType__32__Parameter__11__label[] = "Level 2";
char EffectType__32__Parameter__12__label[] = "Level 3";
char EffectType__32__Parameter__13__label[] = "Level 4";
char EffectType__32__Parameter__14__label[] = "Pan 1";
char EffectType__32__Parameter__15__label[] = "Pan 2";
char EffectType__32__Parameter__16__label[] = "Pan 3";
char EffectType__32__Parameter__17__label[] = "Pan 4";
char EffectType__32__Parameter__18__label[] = "Depth 1 (From Morph)";
char EffectType__32__Parameter__19__label[] = "Depth 2 (From Morph)";
char EffectType__32__Parameter__20__label[] = "Depth 3 (From Morph)";
char EffectType__32__Parameter__21__label[] = "Depth 4 (From Morph)";
char EffectType__32__Parameter__22__label[] = "Morph1 (LFO1/2/3)";
char EffectType__32__Parameter__23__label[] = "Morph2 (LFO1/2/3)";
char EffectType__32__Parameter__24__label[] = "Morph3 (LFO1/2/3)";
char EffectType__32__Parameter__25__label[] = "Morph4 (LFO1/2/3)";
char EffectType__32__Parameter__26__label[] = "LFO1 Type";
char EffectType__32__Parameter__27__label[] = "LFO2 Type";
char EffectType__32__Parameter__28__label[] = "LFO3 Type";
char EffectType__32__Parameter__29__label[] = "LFO4 Type";
char EffectType__32__Parameter__30__label[] = "LFO1 Rate Multiplier";
char EffectType__32__Parameter__31__label[] = "LFO2 Rate Multiplier";
char EffectType__32__Parameter__32__label[] = "LFO3 Rate Multiplier";
char EffectType__32__Parameter__33__label[] = "LFO4 Rate Multiplier";
char EffectType__32__Parameter__34__label[] = "Main Depth (LFO4>ALL)";
char EffectType__32__Parameter__35__label[] = "Input Mode";
char EffectType__32__Parameter__36__label[] = "LFO1 Master";
char EffectType__32__Parameter__37__label[] = "Wide Mode";
char EffectType__32__Parameter__38__label[] = "Main Phase (LFO4)";
char EffectType__32__Parameter__39__label[] = "Mix";
char EffectType__32__Parameter__40__label[] = "Level";
char EffectType__32__Parameter__41__label[] = "Balance";
char EffectType__32__Parameter__42__label[] = "Bypass Mode";
char EffectType__32__Parameter__43__label[] = "";
char EffectType__32__Parameter__44__label[] = "";
char EffectType__32__Parameter__45__label[] = "Hi Cut Frequency";
char EffectType__33__Parameter__0__label[] = "";
char EffectType__33__Parameter__1__label[] = "Chord Type";
char EffectType__33__Parameter__2__label[] = "Input Gain";
char EffectType__33__Parameter__3__label[] = "Frequency";
char EffectType__33__Parameter__4__label[] = "Master Frequency";
char EffectType__33__Parameter__5__label[] = "Master Level";
char EffectType__33__Parameter__6__label[] = "Master Pan";
char EffectType__33__Parameter__7__label[] = "Master Feedback";
char EffectType__33__Parameter__8__label[] = "Master Q";
char EffectType__33__Parameter__9__label[] = "Freq  1";
char EffectType__33__Parameter__10__label[] = "Freq  2";
char EffectType__33__Parameter__11__label[] = "Freq  3";
char EffectType__33__Parameter__12__label[] = "Freq  4";
char EffectType__33__Parameter__13__label[] = "FB 1";
char EffectType__33__Parameter__14__label[] = "FB 2";
char EffectType__33__Parameter__15__label[] = "FB 3";
char EffectType__33__Parameter__16__label[] = "FB 4";
char EffectType__33__Parameter__17__label[] = "Filter Loc 1";
char EffectType__33__Parameter__18__label[] = "Filter Loc 2";
char EffectType__33__Parameter__19__label[] = "Filter Loc 3";
char EffectType__33__Parameter__20__label[] = "Filter Loc 4";
char EffectType__33__Parameter__21__label[] = "Q 1";
char EffectType__33__Parameter__22__label[] = "Q 2";
char EffectType__33__Parameter__23__label[] = "Q 3";
char EffectType__33__Parameter__24__label[] = "Q 4";
char EffectType__33__Parameter__25__label[] = "Level 1";
char EffectType__33__Parameter__26__label[] = "Level 2";
char EffectType__33__Parameter__27__label[] = "Level 3";
char EffectType__33__Parameter__28__label[] = "Level 4";
char EffectType__33__Parameter__29__label[] = "Pan 1";
char EffectType__33__Parameter__30__label[] = "Pan 2";
char EffectType__33__Parameter__31__label[] = "Pan 3";
char EffectType__33__Parameter__32__label[] = "Pan 4";
char EffectType__33__Parameter__33__label[] = "Mix";
char EffectType__33__Parameter__34__label[] = "Level";
char EffectType__33__Parameter__35__label[] = "Balance";
char EffectType__33__Parameter__36__label[] = "Bypassmode";
char EffectType__33__Parameter__37__label[] = "";
char EffectType__33__Parameter__38__label[] = "";
char EffectType__33__Parameter__39__label[] = "Input Mode";
char EffectType__34__Parameter__0__label[] = "Volume";
char EffectType__34__Parameter__1__label[] = "Balance";
char EffectType__34__Parameter__2__label[] = "Volume Taper";
char EffectType__34__Parameter__3__label[] = "";
char EffectType__34__Parameter__4__label[] = "Pan Left";
char EffectType__34__Parameter__5__label[] = "Pan Right";
char EffectType__34__Parameter__6__label[] = "Level";
char EffectType__34__Parameter__7__label[] = "Bypass Mode";
char EffectType__34__Parameter__8__label[] = "Input Select";
char EffectType__35__Parameter__0__label[] = "Threshold";
char EffectType__35__Parameter__1__label[] = "Ratio";
char EffectType__35__Parameter__2__label[] = "Release";
char EffectType__35__Parameter__3__label[] = "Attack";
char EffectType__35__Parameter__4__label[] = "Input Z";
char EffectType__36__Parameter__0__label[] = "Level 1";
char EffectType__36__Parameter__1__label[] = "Level 2";
char EffectType__36__Parameter__2__label[] = "Level 3";
char EffectType__36__Parameter__3__label[] = "Level 4";
char EffectType__36__Parameter__4__label[] = "Balance 1";
char EffectType__36__Parameter__5__label[] = "Balance 2";
char EffectType__36__Parameter__6__label[] = "Balance 3";
char EffectType__36__Parameter__7__label[] = "Balance 4";
char EffectType__36__Parameter__8__label[] = "";
char EffectType__36__Parameter__9__label[] = "";
char EffectType__36__Parameter__10__label[] = "";
char EffectType__36__Parameter__11__label[] = "";
char EffectType__36__Parameter__12__label[] = "";
char EffectType__36__Parameter__13__label[] = "";
char EffectType__36__Parameter__14__label[] = "";
char EffectType__36__Parameter__15__label[] = "";
char EffectType__36__Parameter__16__label[] = "";
char EffectType__36__Parameter__17__label[] = "";
char EffectType__36__Parameter__18__label[] = "";
char EffectType__36__Parameter__19__label[] = "";
char EffectType__37__Parameter__0__label[] = "LFO1 Type (Run)";
char EffectType__37__Parameter__1__label[] = "LFO1 Rate";
char EffectType__37__Parameter__2__label[] = "LFO1 Depth";
char EffectType__37__Parameter__3__label[] = "LFO1 Duty";
char EffectType__37__Parameter__4__label[] = "Output B Phase";
char EffectType__37__Parameter__5__label[] = "LFO1 Tempo";
char EffectType__37__Parameter__6__label[] = "LFO2 Type (Run)";
char EffectType__37__Parameter__7__label[] = "LFO2 Rate";
char EffectType__37__Parameter__8__label[] = "LFO2 Depth";
char EffectType__37__Parameter__9__label[] = "LFO2 Duty";
char EffectType__37__Parameter__10__label[] = "Output B Phase";
char EffectType__37__Parameter__11__label[] = "LFO2 Tempo";
char EffectType__37__Parameter__12__label[] = "Mode";
char EffectType__37__Parameter__13__label[] = "Retrig";
char EffectType__37__Parameter__14__label[] = "Attack";
char EffectType__37__Parameter__15__label[] = "Decay";
char EffectType__37__Parameter__16__label[] = "Sustain";
char EffectType__37__Parameter__17__label[] = "Level";
char EffectType__37__Parameter__18__label[] = "Release";
char EffectType__37__Parameter__19__label[] = "Threshold";
char EffectType__37__Parameter__20__label[] = "Mode";
char EffectType__37__Parameter__21__label[] = "Retrig";
char EffectType__37__Parameter__22__label[] = "Attack";
char EffectType__37__Parameter__23__label[] = "Decay";
char EffectType__37__Parameter__24__label[] = "Sustain";
char EffectType__37__Parameter__25__label[] = "Level";
char EffectType__37__Parameter__26__label[] = "Release";
char EffectType__37__Parameter__27__label[] = "Threshold";
char EffectType__37__Parameter__28__label[] = "Attack";
char EffectType__37__Parameter__29__label[] = "Release";
char EffectType__37__Parameter__30__label[] = "Threshold";
char EffectType__37__Parameter__31__label[] = "Gain";
char EffectType__37__Parameter__32__label[] = "";
char EffectType__37__Parameter__33__label[] = "";
char EffectType__37__Parameter__34__label[] = "Rate";
char EffectType__37__Parameter__35__label[] = "Tempo";
char EffectType__37__Parameter__36__label[] = "Stages";
char EffectType__37__Parameter__37__label[] = "Stage 1";
char EffectType__37__Parameter__38__label[] = "Stage 2";
char EffectType__37__Parameter__39__label[] = "Stage 3";
char EffectType__37__Parameter__40__label[] = "Stage 4";
char EffectType__37__Parameter__41__label[] = "Stage 5";
char EffectType__37__Parameter__42__label[] = "Stage 6";
char EffectType__37__Parameter__43__label[] = "Stage 7";
char EffectType__37__Parameter__44__label[] = "Stage 8";
char EffectType__37__Parameter__45__label[] = "Stage 9";
char EffectType__37__Parameter__46__label[] = "Stage 10";
char EffectType__37__Parameter__47__label[] = "Stage 11";
char EffectType__37__Parameter__48__label[] = "Stage 12";
char EffectType__37__Parameter__49__label[] = "Stage 13";
char EffectType__37__Parameter__50__label[] = "Stage 14";
char EffectType__37__Parameter__51__label[] = "Stage 15";
char EffectType__37__Parameter__52__label[] = "Stage 16";
char EffectType__37__Parameter__53__label[] = "";
char EffectType__37__Parameter__54__label[] = "Run";
char EffectType__37__Parameter__55__label[] = "Manual A";
char EffectType__37__Parameter__56__label[] = "Manual B";
char EffectType__37__Parameter__57__label[] = "Manual C";
char EffectType__37__Parameter__58__label[] = "Manual D";
char EffectType__37__Parameter__59__label[] = "Stage 17";
char EffectType__37__Parameter__60__label[] = "Stage 18";
char EffectType__37__Parameter__61__label[] = "Stage 19";
char EffectType__37__Parameter__62__label[] = "Stage 20";
char EffectType__37__Parameter__63__label[] = "Stage 21";
char EffectType__37__Parameter__64__label[] = "Stage 22";
char EffectType__37__Parameter__65__label[] = "Stage 23";
char EffectType__37__Parameter__66__label[] = "Stage 24";
char EffectType__37__Parameter__67__label[] = "Stage 25";
char EffectType__37__Parameter__68__label[] = "Stage 26";
char EffectType__37__Parameter__69__label[] = "Stage 27";
char EffectType__37__Parameter__70__label[] = "Stage 28";
char EffectType__37__Parameter__71__label[] = "Stage 29";
char EffectType__37__Parameter__72__label[] = "Stage 30";
char EffectType__37__Parameter__73__label[] = "Stage 31";
char EffectType__37__Parameter__74__label[] = "Stage 32";
char EffectType__37__Parameter__75__label[] = "";
char EffectType__37__Parameter__76__label[] = "";
char EffectType__37__Parameter__77__label[] = "";
char EffectType__38__Parameter__0__label[] = "Mix";
char EffectType__38__Parameter__1__label[] = "Level";
char EffectType__38__Parameter__2__label[] = "Balance";
char EffectType__38__Parameter__3__label[] = "Bypass Mode";
char EffectType__38__Parameter__4__label[] = "";
char EffectType__38__Parameter__5__label[] = "Dub Mix";
char EffectType__38__Parameter__6__label[] = "Threshold";
char EffectType__38__Parameter__7__label[] = "Threshold Level";
char EffectType__38__Parameter__8__label[] = "";
char EffectType__38__Parameter__9__label[] = "Quantize";
char EffectType__38__Parameter__10__label[] = "Trim Stop";
char EffectType__38__Parameter__11__label[] = "Trim Start";
char EffectType__38__Parameter__12__label[] = "Play Immediately";
char EffectType__39__Parameter__0__label[] = "";
char EffectType__39__Parameter__1__label[] = "Amount";
char EffectType__39__Parameter__2__label[] = "Smoothing";
char EffectType__39__Parameter__3__label[] = "Reference";
char EffectType__39__Parameter__4__label[] = "Local";
char EffectType__39__Parameter__5__label[] = "Match";
char EffectType__39__Parameter__6__label[] = "Level";
char EffectType__39__Parameter__7__label[] = "Balance";
char EffectType__39__Parameter__8__label[] = "Bypass Mode";
char EffectType__39__Parameter__9__label[] = "";
char EffectType__39__Parameter__10__label[] = "Ref Source";
char EffectType__39__Parameter__11__label[] = "Time";
char EffectType__39__Parameter__12__label[] = "Ref Channel";
char EffectType__39__Parameter__13__label[] = "Local Channel";
char EffectType__39__Parameter__14__label[] = "Ref Solo";
char EffectType__39__Parameter__15__label[] = "Resolution";
char EffectType__39__Parameter__16__label[] = "";
char EffectType__39__Parameter__17__label[] = "";
char EffectType__39__Parameter__18__label[] = "";
char EffectType__39__Parameter__19__label[] = "";
char EffectType__39__Parameter__20__label[] = "";


char *Parameter__labels[TotalNumOfParameters] = { EffectType__2__Parameter__0__label, EffectType__2__Parameter__1__label, EffectType__2__Parameter__2__label, EffectType__2__Parameter__3__label, EffectType__2__Parameter__4__label, EffectType__2__Parameter__5__label, EffectType__2__Parameter__6__label, EffectType__2__Parameter__7__label, EffectType__2__Parameter__8__label, EffectType__2__Parameter__9__label, EffectType__2__Parameter__10__label, EffectType__2__Parameter__11__label, EffectType__2__Parameter__12__label, EffectType__2__Parameter__13__label, EffectType__2__Parameter__14__label, EffectType__2__Parameter__15__label, EffectType__2__Parameter__16__label, EffectType__2__Parameter__17__label,
EffectType__3__Parameter__0__label, EffectType__3__Parameter__1__label, EffectType__3__Parameter__2__label, EffectType__3__Parameter__3__label, EffectType__3__Parameter__4__label, EffectType__3__Parameter__5__label, EffectType__3__Parameter__6__label, EffectType__3__Parameter__7__label, EffectType__3__Parameter__8__label, EffectType__3__Parameter__9__label, EffectType__3__Parameter__10__label, EffectType__3__Parameter__11__label, EffectType__3__Parameter__12__label, EffectType__3__Parameter__13__label, EffectType__3__Parameter__14__label, EffectType__3__Parameter__15__label, EffectType__3__Parameter__16__label, EffectType__3__Parameter__17__label, EffectType__3__Parameter__18__label,
EffectType__4__Parameter__0__label, EffectType__4__Parameter__1__label, EffectType__4__Parameter__2__label, EffectType__4__Parameter__3__label, EffectType__4__Parameter__4__label, EffectType__4__Parameter__5__label, EffectType__4__Parameter__6__label, EffectType__4__Parameter__7__label, EffectType__4__Parameter__8__label, EffectType__4__Parameter__9__label, EffectType__4__Parameter__10__label, EffectType__4__Parameter__11__label, EffectType__4__Parameter__12__label, EffectType__4__Parameter__13__label, EffectType__4__Parameter__14__label, EffectType__4__Parameter__15__label, EffectType__4__Parameter__16__label, EffectType__4__Parameter__17__label, EffectType__4__Parameter__18__label, EffectType__4__Parameter__19__label, EffectType__4__Parameter__20__label, EffectType__4__Parameter__21__label, EffectType__4__Parameter__22__label, EffectType__4__Parameter__23__label,

//EffectType__5__Parameter__0__label, EffectType__5__Parameter__1__label, EffectType__5__Parameter__2__label, EffectType__5__Parameter__3__label, EffectType__5__Parameter__4__label, EffectType__5__Parameter__5__label, EffectType__5__Parameter__6__label, EffectType__5__Parameter__7__label, EffectType__5__Parameter__8__label, EffectType__5__Parameter__9__label, EffectType__5__Parameter__10__label, EffectType__5__Parameter__11__label, EffectType__5__Parameter__12__label, EffectType__5__Parameter__13__label, EffectType__5__Parameter__14__label, EffectType__5__Parameter__15__label, EffectType__5__Parameter__16__label, EffectType__5__Parameter__17__label, EffectType__5__Parameter__18__label, EffectType__5__Parameter__19__label, EffectType__5__Parameter__20__label, EffectType__5__Parameter__21__label, EffectType__5__Parameter__22__label, EffectType__5__Parameter__23__label, EffectType__5__Parameter__24__label, EffectType__5__Parameter__25__label, EffectType__5__Parameter__26__label, EffectType__5__Parameter__27__label, EffectType__5__Parameter__28__label, EffectType__5__Parameter__29__label, EffectType__5__Parameter__30__label, EffectType__5__Parameter__31__label, EffectType__5__Parameter__32__label, EffectType__5__Parameter__33__label, EffectType__5__Parameter__34__label, EffectType__5__Parameter__35__label, EffectType__5__Parameter__36__label, EffectType__5__Parameter__37__label, EffectType__5__Parameter__38__label, EffectType__5__Parameter__39__label, EffectType__5__Parameter__40__label, EffectType__5__Parameter__41__label, EffectType__5__Parameter__42__label, EffectType__5__Parameter__43__label, EffectType__5__Parameter__44__label, EffectType__5__Parameter__45__label, EffectType__5__Parameter__46__label, EffectType__5__Parameter__47__label, EffectType__5__Parameter__48__label, EffectType__5__Parameter__49__label, EffectType__5__Parameter__50__label, EffectType__5__Parameter__51__label, EffectType__5__Parameter__52__label, EffectType__5__Parameter__53__label, EffectType__5__Parameter__54__label, EffectType__5__Parameter__55__label, EffectType__5__Parameter__56__label, EffectType__5__Parameter__57__label, EffectType__5__Parameter__58__label, EffectType__5__Parameter__59__label, EffectType__5__Parameter__60__label, EffectType__5__Parameter__61__label, EffectType__5__Parameter__62__label, EffectType__5__Parameter__63__label, EffectType__5__Parameter__64__label, EffectType__5__Parameter__65__label, EffectType__5__Parameter__66__label, EffectType__5__Parameter__67__label, EffectType__5__Parameter__68__label, EffectType__5__Parameter__69__label, EffectType__5__Parameter__70__label, EffectType__5__Parameter__71__label, EffectType__5__Parameter__72__label, EffectType__5__Parameter__73__label, EffectType__5__Parameter__74__label, EffectType__5__Parameter__75__label, EffectType__5__Parameter__76__label, EffectType__5__Parameter__77__label, EffectType__5__Parameter__78__label, EffectType__5__Parameter__79__label, EffectType__5__Parameter__80__label, EffectType__5__Parameter__81__label, EffectType__5__Parameter__82__label, EffectType__5__Parameter__83__label, EffectType__5__Parameter__84__label, EffectType__5__Parameter__85__label, EffectType__5__Parameter__86__label, EffectType__5__Parameter__87__label, EffectType__5__Parameter__88__label, EffectType__5__Parameter__89__label, EffectType__5__Parameter__90__label,
// AMP
EffectType__5__Parameter__0__label, EffectType__5__Parameter__1__label, EffectType__5__Parameter__2__label, EffectType__5__Parameter__3__label, EffectType__5__Parameter__4__label, EffectType__5__Parameter__5__label, EffectType__5__Parameter__6__label, EffectType__5__Parameter__7__label, EffectType__5__Parameter__8__label, EffectType__5__Parameter__9__label, EffectType__5__Parameter__10__label, EffectType__5__Parameter__11__label, EffectType__5__Parameter__12__label, EffectType__5__Parameter__13__label, EffectType__5__Parameter__14__label, EffectType__5__Parameter__15__label, EffectType__5__Parameter__16__label, EffectType__5__Parameter__17__label, EffectType__5__Parameter__18__label, EffectType__5__Parameter__19__label, EffectType__5__Parameter__20__label, EffectType__5__Parameter__21__label, EffectType__5__Parameter__22__label, EffectType__5__Parameter__23__label, EffectType__5__Parameter__24__label, EffectType__5__Parameter__25__label, EffectType__5__Parameter__26__label, EffectType__5__Parameter__27__label, EffectType__5__Parameter__28__label, EffectType__5__Parameter__29__label, EffectType__5__Parameter__30__label, EffectType__5__Parameter__31__label, EffectType__5__Parameter__32__label, EffectType__5__Parameter__33__label, EffectType__5__Parameter__34__label, EffectType__5__Parameter__35__label, EffectType__5__Parameter__36__label, EffectType__5__Parameter__37__label, EffectType__5__Parameter__38__label, EffectType__5__Parameter__39__label, EffectType__5__Parameter__40__label, EffectType__5__Parameter__41__label, EffectType__5__Parameter__42__label, EffectType__5__Parameter__43__label, EffectType__5__Parameter__44__label, EffectType__5__Parameter__45__label, EffectType__5__Parameter__46__label, EffectType__5__Parameter__47__label, EffectType__5__Parameter__48__label, EffectType__5__Parameter__49__label, EffectType__5__Parameter__50__label, EffectType__5__Parameter__51__label, EffectType__5__Parameter__52__label, EffectType__5__Parameter__53__label, EffectType__5__Parameter__54__label, EffectType__5__Parameter__55__label, EffectType__5__Parameter__56__label, EffectType__5__Parameter__57__label, EffectType__5__Parameter__58__label, EffectType__5__Parameter__59__label, EffectType__5__Parameter__60__label, EffectType__5__Parameter__61__label, EffectType__5__Parameter__62__label, EffectType__5__Parameter__63__label, EffectType__5__Parameter__64__label, EffectType__5__Parameter__65__label, EffectType__5__Parameter__66__label, EffectType__5__Parameter__67__label, EffectType__5__Parameter__68__label, EffectType__5__Parameter__69__label, EffectType__5__Parameter__70__label, EffectType__5__Parameter__71__label, EffectType__5__Parameter__72__label, EffectType__5__Parameter__73__label, EffectType__5__Parameter__74__label, EffectType__5__Parameter__75__label, EffectType__5__Parameter__76__label, EffectType__5__Parameter__77__label, EffectType__5__Parameter__78__label, EffectType__5__Parameter__79__label, EffectType__5__Parameter__80__label, EffectType__5__Parameter__81__label, EffectType__5__Parameter__82__label, EffectType__5__Parameter__83__label, EffectType__5__Parameter__84__label, EffectType__5__Parameter__85__label, EffectType__5__Parameter__86__label, EffectType__5__Parameter__87__label, EffectType__5__Parameter__88__label, EffectType__5__Parameter__89__label, EffectType__5__Parameter__90__label, EffectType__5__Parameter__91__label, EffectType__5__Parameter__92__label, EffectType__5__Parameter__93__label, EffectType__5__Parameter__94__label, EffectType__5__Parameter__95__label, EffectType__5__Parameter__96__label, EffectType__5__Parameter__97__label, EffectType__5__Parameter__98__label, EffectType__5__Parameter__99__label, EffectType__5__Parameter__100__label, EffectType__5__Parameter__101__label, EffectType__5__Parameter__102__label, EffectType__5__Parameter__103__label, EffectType__5__Parameter__104__label, EffectType__5__Parameter__105__label, EffectType__5__Parameter__106__label, EffectType__5__Parameter__107__label, EffectType__5__Parameter__108__label, EffectType__5__Parameter__109__label, EffectType__5__Parameter__110__label, EffectType__5__Parameter__111__label, EffectType__5__Parameter__112__label,

EffectType__6__Parameter__0__label, EffectType__6__Parameter__1__label, EffectType__6__Parameter__2__label, EffectType__6__Parameter__3__label, EffectType__6__Parameter__4__label, EffectType__6__Parameter__5__label, EffectType__6__Parameter__6__label, EffectType__6__Parameter__7__label, EffectType__6__Parameter__8__label, EffectType__6__Parameter__9__label, EffectType__6__Parameter__10__label, EffectType__6__Parameter__11__label, EffectType__6__Parameter__12__label, EffectType__6__Parameter__13__label, EffectType__6__Parameter__14__label, EffectType__6__Parameter__15__label, EffectType__6__Parameter__16__label, EffectType__6__Parameter__17__label, EffectType__6__Parameter__18__label, EffectType__6__Parameter__19__label, EffectType__6__Parameter__20__label, EffectType__6__Parameter__21__label, EffectType__6__Parameter__22__label, EffectType__6__Parameter__23__label, EffectType__6__Parameter__24__label, EffectType__6__Parameter__25__label, EffectType__6__Parameter__26__label, EffectType__6__Parameter__27__label, EffectType__6__Parameter__28__label,
EffectType__7__Parameter__0__label, EffectType__7__Parameter__1__label, EffectType__7__Parameter__2__label, EffectType__7__Parameter__3__label, EffectType__7__Parameter__4__label, EffectType__7__Parameter__5__label, EffectType__7__Parameter__6__label, EffectType__7__Parameter__7__label, EffectType__7__Parameter__8__label, EffectType__7__Parameter__9__label, EffectType__7__Parameter__10__label, EffectType__7__Parameter__11__label, EffectType__7__Parameter__12__label, EffectType__7__Parameter__13__label, EffectType__7__Parameter__14__label, EffectType__7__Parameter__15__label, EffectType__7__Parameter__16__label, EffectType__7__Parameter__17__label, EffectType__7__Parameter__18__label, EffectType__7__Parameter__19__label, EffectType__7__Parameter__20__label, EffectType__7__Parameter__21__label, EffectType__7__Parameter__22__label, EffectType__7__Parameter__23__label, EffectType__7__Parameter__24__label, EffectType__7__Parameter__25__label, EffectType__7__Parameter__26__label, EffectType__7__Parameter__27__label, EffectType__7__Parameter__28__label, EffectType__7__Parameter__29__label, EffectType__7__Parameter__30__label, EffectType__7__Parameter__31__label, EffectType__7__Parameter__32__label, EffectType__7__Parameter__33__label, EffectType__7__Parameter__34__label,
EffectType__8__Parameter__0__label, EffectType__8__Parameter__1__label, EffectType__8__Parameter__2__label, EffectType__8__Parameter__3__label, EffectType__8__Parameter__4__label, EffectType__8__Parameter__5__label, EffectType__8__Parameter__6__label, EffectType__8__Parameter__7__label, EffectType__8__Parameter__8__label, EffectType__8__Parameter__9__label, EffectType__8__Parameter__10__label, EffectType__8__Parameter__11__label, EffectType__8__Parameter__12__label, EffectType__8__Parameter__13__label, EffectType__8__Parameter__14__label, EffectType__8__Parameter__15__label, EffectType__8__Parameter__16__label, EffectType__8__Parameter__17__label, EffectType__8__Parameter__18__label, EffectType__8__Parameter__19__label, EffectType__8__Parameter__20__label, EffectType__8__Parameter__21__label, EffectType__8__Parameter__22__label, EffectType__8__Parameter__23__label, EffectType__8__Parameter__24__label, EffectType__8__Parameter__25__label, EffectType__8__Parameter__26__label, EffectType__8__Parameter__27__label, EffectType__8__Parameter__28__label, EffectType__8__Parameter__29__label, EffectType__8__Parameter__30__label, EffectType__8__Parameter__31__label, EffectType__8__Parameter__32__label, EffectType__8__Parameter__33__label, EffectType__8__Parameter__34__label, EffectType__8__Parameter__35__label, EffectType__8__Parameter__36__label, EffectType__8__Parameter__37__label, EffectType__8__Parameter__38__label, EffectType__8__Parameter__39__label, EffectType__8__Parameter__40__label, EffectType__8__Parameter__41__label, EffectType__8__Parameter__42__label, EffectType__8__Parameter__43__label, EffectType__8__Parameter__44__label, EffectType__8__Parameter__45__label, EffectType__8__Parameter__46__label, EffectType__8__Parameter__47__label, EffectType__8__Parameter__48__label, EffectType__8__Parameter__49__label, EffectType__8__Parameter__50__label, EffectType__8__Parameter__51__label, EffectType__8__Parameter__52__label, EffectType__8__Parameter__53__label, EffectType__8__Parameter__54__label, EffectType__8__Parameter__55__label, EffectType__8__Parameter__56__label, EffectType__8__Parameter__57__label, EffectType__8__Parameter__58__label, EffectType__8__Parameter__59__label, EffectType__8__Parameter__60__label, EffectType__8__Parameter__61__label, EffectType__8__Parameter__62__label, EffectType__8__Parameter__63__label, EffectType__8__Parameter__64__label, EffectType__8__Parameter__65__label, EffectType__8__Parameter__66__label, EffectType__8__Parameter__67__label, EffectType__8__Parameter__68__label, EffectType__8__Parameter__69__label,
EffectType__9__Parameter__0__label, EffectType__9__Parameter__1__label, EffectType__9__Parameter__2__label, EffectType__9__Parameter__3__label, EffectType__9__Parameter__4__label, EffectType__9__Parameter__5__label, EffectType__9__Parameter__6__label, EffectType__9__Parameter__7__label, EffectType__9__Parameter__8__label, EffectType__9__Parameter__9__label, EffectType__9__Parameter__10__label, EffectType__9__Parameter__11__label, EffectType__9__Parameter__12__label, EffectType__9__Parameter__13__label, EffectType__9__Parameter__14__label, EffectType__9__Parameter__15__label, EffectType__9__Parameter__16__label, EffectType__9__Parameter__17__label, EffectType__9__Parameter__18__label, EffectType__9__Parameter__19__label, EffectType__9__Parameter__20__label, EffectType__9__Parameter__21__label, EffectType__9__Parameter__22__label, EffectType__9__Parameter__23__label, EffectType__9__Parameter__24__label, EffectType__9__Parameter__25__label, EffectType__9__Parameter__26__label, EffectType__9__Parameter__27__label, EffectType__9__Parameter__28__label, EffectType__9__Parameter__29__label, EffectType__9__Parameter__30__label, EffectType__9__Parameter__31__label, EffectType__9__Parameter__32__label, EffectType__9__Parameter__33__label, EffectType__9__Parameter__34__label, EffectType__9__Parameter__35__label, EffectType__9__Parameter__36__label, EffectType__9__Parameter__37__label, EffectType__9__Parameter__38__label, EffectType__9__Parameter__39__label, EffectType__9__Parameter__40__label, EffectType__9__Parameter__41__label, EffectType__9__Parameter__42__label, EffectType__9__Parameter__43__label, EffectType__9__Parameter__44__label, EffectType__9__Parameter__45__label, EffectType__9__Parameter__46__label, EffectType__9__Parameter__47__label, EffectType__9__Parameter__48__label, EffectType__9__Parameter__49__label, EffectType__9__Parameter__50__label, EffectType__9__Parameter__51__label, EffectType__9__Parameter__52__label, EffectType__9__Parameter__53__label, EffectType__9__Parameter__54__label, EffectType__9__Parameter__55__label, EffectType__9__Parameter__56__label, EffectType__9__Parameter__57__label, EffectType__9__Parameter__58__label, EffectType__9__Parameter__59__label, EffectType__9__Parameter__60__label, EffectType__9__Parameter__61__label, EffectType__9__Parameter__62__label, EffectType__9__Parameter__63__label, EffectType__9__Parameter__64__label, EffectType__9__Parameter__65__label, EffectType__9__Parameter__66__label, EffectType__9__Parameter__67__label, EffectType__9__Parameter__68__label, EffectType__9__Parameter__69__label, EffectType__9__Parameter__70__label, EffectType__9__Parameter__71__label, EffectType__9__Parameter__72__label, EffectType__9__Parameter__73__label, EffectType__9__Parameter__74__label, EffectType__9__Parameter__75__label, EffectType__9__Parameter__76__label, EffectType__9__Parameter__77__label, EffectType__9__Parameter__78__label, EffectType__9__Parameter__79__label, EffectType__9__Parameter__80__label, EffectType__9__Parameter__81__label, EffectType__9__Parameter__82__label, EffectType__9__Parameter__83__label, EffectType__9__Parameter__84__label, EffectType__9__Parameter__85__label, EffectType__9__Parameter__86__label, EffectType__9__Parameter__87__label, EffectType__9__Parameter__88__label, EffectType__9__Parameter__89__label, EffectType__9__Parameter__90__label, EffectType__9__Parameter__91__label, EffectType__9__Parameter__92__label, EffectType__9__Parameter__93__label, EffectType__9__Parameter__94__label, EffectType__9__Parameter__95__label, EffectType__9__Parameter__96__label, EffectType__9__Parameter__97__label, EffectType__9__Parameter__98__label, EffectType__9__Parameter__99__label, EffectType__9__Parameter__100__label, EffectType__9__Parameter__101__label, EffectType__9__Parameter__102__label, EffectType__9__Parameter__103__label, EffectType__9__Parameter__104__label, EffectType__9__Parameter__105__label, EffectType__9__Parameter__106__label, EffectType__9__Parameter__107__label, EffectType__9__Parameter__108__label, EffectType__9__Parameter__109__label, EffectType__9__Parameter__110__label, EffectType__9__Parameter__111__label, EffectType__9__Parameter__112__label, EffectType__9__Parameter__113__label, EffectType__9__Parameter__114__label, EffectType__9__Parameter__115__label, EffectType__9__Parameter__116__label,
EffectType__10__Parameter__0__label, EffectType__10__Parameter__1__label, EffectType__10__Parameter__2__label, EffectType__10__Parameter__3__label, EffectType__10__Parameter__4__label, EffectType__10__Parameter__5__label, EffectType__10__Parameter__6__label, EffectType__10__Parameter__7__label, EffectType__10__Parameter__8__label, EffectType__10__Parameter__9__label, EffectType__10__Parameter__10__label, EffectType__10__Parameter__11__label, EffectType__10__Parameter__12__label, EffectType__10__Parameter__13__label, EffectType__10__Parameter__14__label, EffectType__10__Parameter__15__label, EffectType__10__Parameter__16__label, EffectType__10__Parameter__17__label, EffectType__10__Parameter__18__label, EffectType__10__Parameter__19__label, EffectType__10__Parameter__20__label, EffectType__10__Parameter__21__label, EffectType__10__Parameter__22__label,
EffectType__11__Parameter__0__label, EffectType__11__Parameter__1__label, EffectType__11__Parameter__2__label, EffectType__11__Parameter__3__label, EffectType__11__Parameter__4__label, EffectType__11__Parameter__5__label, EffectType__11__Parameter__6__label, EffectType__11__Parameter__7__label, EffectType__11__Parameter__8__label, EffectType__11__Parameter__9__label, EffectType__11__Parameter__10__label, EffectType__11__Parameter__11__label, EffectType__11__Parameter__12__label, EffectType__11__Parameter__13__label, EffectType__11__Parameter__14__label, EffectType__11__Parameter__15__label, EffectType__11__Parameter__16__label, EffectType__11__Parameter__17__label, EffectType__11__Parameter__18__label, EffectType__11__Parameter__19__label, EffectType__11__Parameter__20__label, EffectType__11__Parameter__21__label, EffectType__11__Parameter__22__label,
EffectType__12__Parameter__0__label, EffectType__12__Parameter__1__label, EffectType__12__Parameter__2__label, EffectType__12__Parameter__3__label, EffectType__12__Parameter__4__label, EffectType__12__Parameter__5__label, EffectType__12__Parameter__6__label, EffectType__12__Parameter__7__label, EffectType__12__Parameter__8__label, EffectType__12__Parameter__9__label, EffectType__12__Parameter__10__label, EffectType__12__Parameter__11__label, EffectType__12__Parameter__12__label, EffectType__12__Parameter__13__label, EffectType__12__Parameter__14__label, EffectType__12__Parameter__15__label, EffectType__12__Parameter__16__label, EffectType__12__Parameter__17__label,
EffectType__13__Parameter__0__label, EffectType__13__Parameter__1__label, EffectType__13__Parameter__2__label, EffectType__13__Parameter__3__label, EffectType__13__Parameter__4__label, EffectType__13__Parameter__5__label, EffectType__13__Parameter__6__label, EffectType__13__Parameter__7__label, EffectType__13__Parameter__8__label, EffectType__13__Parameter__9__label, EffectType__13__Parameter__10__label, EffectType__13__Parameter__11__label, EffectType__13__Parameter__12__label, EffectType__13__Parameter__13__label, EffectType__13__Parameter__14__label, EffectType__13__Parameter__15__label, EffectType__13__Parameter__16__label, EffectType__13__Parameter__17__label, EffectType__13__Parameter__18__label, EffectType__13__Parameter__19__label,
EffectType__14__Parameter__0__label, EffectType__14__Parameter__1__label, EffectType__14__Parameter__2__label, EffectType__14__Parameter__3__label, EffectType__14__Parameter__4__label, EffectType__14__Parameter__5__label, EffectType__14__Parameter__6__label, EffectType__14__Parameter__7__label, EffectType__14__Parameter__8__label, EffectType__14__Parameter__9__label, EffectType__14__Parameter__10__label, EffectType__14__Parameter__11__label, EffectType__14__Parameter__12__label,
EffectType__15__Parameter__0__label, EffectType__15__Parameter__1__label, EffectType__15__Parameter__2__label, EffectType__15__Parameter__3__label, EffectType__15__Parameter__4__label, EffectType__15__Parameter__5__label, EffectType__15__Parameter__6__label, EffectType__15__Parameter__7__label, EffectType__15__Parameter__8__label, EffectType__15__Parameter__9__label, EffectType__15__Parameter__10__label, EffectType__15__Parameter__11__label,
EffectType__16__Parameter__0__label, EffectType__16__Parameter__1__label, EffectType__16__Parameter__2__label, EffectType__16__Parameter__3__label, EffectType__16__Parameter__4__label, EffectType__16__Parameter__5__label, EffectType__16__Parameter__6__label, EffectType__16__Parameter__7__label, EffectType__16__Parameter__8__label, EffectType__16__Parameter__9__label, EffectType__16__Parameter__10__label, EffectType__16__Parameter__11__label, EffectType__16__Parameter__12__label, EffectType__16__Parameter__13__label, EffectType__16__Parameter__14__label,
EffectType__17__Parameter__0__label, EffectType__17__Parameter__1__label, EffectType__17__Parameter__2__label, EffectType__17__Parameter__3__label, EffectType__17__Parameter__4__label, EffectType__17__Parameter__5__label, EffectType__17__Parameter__6__label, EffectType__17__Parameter__7__label, EffectType__17__Parameter__8__label, EffectType__17__Parameter__9__label, EffectType__17__Parameter__10__label, EffectType__17__Parameter__11__label, EffectType__17__Parameter__12__label, EffectType__17__Parameter__13__label, EffectType__17__Parameter__14__label, EffectType__17__Parameter__15__label, EffectType__17__Parameter__16__label, EffectType__17__Parameter__17__label, EffectType__17__Parameter__18__label, EffectType__17__Parameter__19__label, EffectType__17__Parameter__20__label, EffectType__17__Parameter__21__label, EffectType__17__Parameter__22__label, EffectType__17__Parameter__23__label, EffectType__17__Parameter__24__label, EffectType__17__Parameter__25__label, EffectType__17__Parameter__26__label, EffectType__17__Parameter__27__label, EffectType__17__Parameter__28__label, EffectType__17__Parameter__29__label, EffectType__17__Parameter__30__label, EffectType__17__Parameter__31__label, EffectType__17__Parameter__32__label, EffectType__17__Parameter__33__label, EffectType__17__Parameter__34__label, EffectType__17__Parameter__35__label, EffectType__17__Parameter__36__label, EffectType__17__Parameter__37__label, EffectType__17__Parameter__38__label, EffectType__17__Parameter__39__label, EffectType__17__Parameter__40__label, EffectType__17__Parameter__41__label, EffectType__17__Parameter__42__label, EffectType__17__Parameter__43__label, EffectType__17__Parameter__44__label, EffectType__17__Parameter__45__label, EffectType__17__Parameter__46__label, EffectType__17__Parameter__47__label, EffectType__17__Parameter__48__label, EffectType__17__Parameter__49__label, EffectType__17__Parameter__50__label, EffectType__17__Parameter__51__label, EffectType__17__Parameter__52__label, EffectType__17__Parameter__53__label, EffectType__17__Parameter__54__label, EffectType__17__Parameter__55__label, EffectType__17__Parameter__56__label, EffectType__17__Parameter__57__label, EffectType__17__Parameter__58__label, EffectType__17__Parameter__59__label, EffectType__17__Parameter__60__label, EffectType__17__Parameter__61__label, EffectType__17__Parameter__62__label, EffectType__17__Parameter__63__label, EffectType__17__Parameter__64__label, EffectType__17__Parameter__65__label, EffectType__17__Parameter__66__label, EffectType__17__Parameter__67__label, EffectType__17__Parameter__68__label, EffectType__17__Parameter__69__label, EffectType__17__Parameter__70__label, EffectType__17__Parameter__71__label, EffectType__17__Parameter__72__label, EffectType__17__Parameter__73__label, EffectType__17__Parameter__74__label, EffectType__17__Parameter__75__label, EffectType__17__Parameter__76__label, EffectType__17__Parameter__77__label, EffectType__17__Parameter__78__label, EffectType__17__Parameter__79__label, EffectType__17__Parameter__80__label, EffectType__17__Parameter__81__label, EffectType__17__Parameter__82__label, EffectType__17__Parameter__83__label, EffectType__17__Parameter__84__label,
EffectType__18__Parameter__0__label, EffectType__18__Parameter__1__label, EffectType__18__Parameter__2__label, EffectType__18__Parameter__3__label, EffectType__18__Parameter__4__label, EffectType__18__Parameter__5__label, EffectType__18__Parameter__6__label, EffectType__18__Parameter__7__label, EffectType__18__Parameter__8__label, EffectType__18__Parameter__9__label, EffectType__18__Parameter__10__label, EffectType__18__Parameter__11__label, EffectType__18__Parameter__12__label, EffectType__18__Parameter__13__label,
EffectType__19__Parameter__0__label, EffectType__19__Parameter__1__label, EffectType__19__Parameter__2__label, EffectType__19__Parameter__3__label, EffectType__19__Parameter__4__label, EffectType__19__Parameter__5__label, EffectType__19__Parameter__6__label, EffectType__19__Parameter__7__label, EffectType__19__Parameter__8__label, EffectType__19__Parameter__9__label, EffectType__19__Parameter__10__label, EffectType__19__Parameter__11__label, EffectType__19__Parameter__12__label, EffectType__19__Parameter__13__label, EffectType__19__Parameter__14__label, EffectType__19__Parameter__15__label, EffectType__19__Parameter__16__label, EffectType__19__Parameter__17__label, EffectType__19__Parameter__18__label, EffectType__19__Parameter__19__label,
EffectType__20__Parameter__0__label, EffectType__20__Parameter__1__label, EffectType__20__Parameter__2__label, EffectType__20__Parameter__3__label, EffectType__20__Parameter__4__label, EffectType__20__Parameter__5__label, EffectType__20__Parameter__6__label, EffectType__20__Parameter__7__label, EffectType__20__Parameter__8__label, EffectType__20__Parameter__9__label, EffectType__20__Parameter__10__label,
EffectType__21__Parameter__0__label, EffectType__21__Parameter__1__label, EffectType__21__Parameter__2__label, EffectType__21__Parameter__3__label, EffectType__21__Parameter__4__label, EffectType__21__Parameter__5__label, EffectType__21__Parameter__6__label, EffectType__21__Parameter__7__label, EffectType__21__Parameter__8__label, EffectType__21__Parameter__9__label, EffectType__21__Parameter__10__label, EffectType__21__Parameter__11__label, EffectType__21__Parameter__12__label, EffectType__21__Parameter__13__label, EffectType__21__Parameter__14__label, EffectType__21__Parameter__15__label, EffectType__21__Parameter__16__label, EffectType__21__Parameter__17__label, EffectType__21__Parameter__18__label, EffectType__21__Parameter__19__label,
EffectType__22__Parameter__0__label, EffectType__22__Parameter__1__label, EffectType__22__Parameter__2__label, EffectType__22__Parameter__3__label, EffectType__22__Parameter__4__label, EffectType__22__Parameter__5__label, EffectType__22__Parameter__6__label, EffectType__22__Parameter__7__label, EffectType__22__Parameter__8__label, EffectType__22__Parameter__9__label,
EffectType__23__Parameter__0__label, EffectType__23__Parameter__1__label,
EffectType__24__Parameter__0__label, EffectType__24__Parameter__1__label, EffectType__24__Parameter__2__label, EffectType__24__Parameter__3__label, EffectType__24__Parameter__4__label, EffectType__24__Parameter__5__label,
EffectType__25__Parameter__0__label, EffectType__25__Parameter__1__label, EffectType__25__Parameter__2__label, EffectType__25__Parameter__3__label, EffectType__25__Parameter__4__label, EffectType__25__Parameter__5__label, EffectType__25__Parameter__6__label, EffectType__25__Parameter__7__label, EffectType__25__Parameter__8__label, EffectType__25__Parameter__9__label, EffectType__25__Parameter__10__label, EffectType__25__Parameter__11__label, EffectType__25__Parameter__12__label, EffectType__25__Parameter__13__label, EffectType__25__Parameter__14__label, EffectType__25__Parameter__15__label, EffectType__25__Parameter__16__label, EffectType__25__Parameter__17__label, EffectType__25__Parameter__18__label, EffectType__25__Parameter__19__label, EffectType__25__Parameter__20__label, EffectType__25__Parameter__21__label, EffectType__25__Parameter__22__label, EffectType__25__Parameter__23__label, EffectType__25__Parameter__24__label, EffectType__25__Parameter__25__label, EffectType__25__Parameter__26__label, EffectType__25__Parameter__27__label, EffectType__25__Parameter__28__label, EffectType__25__Parameter__29__label, EffectType__25__Parameter__30__label, EffectType__25__Parameter__31__label, EffectType__25__Parameter__32__label, EffectType__25__Parameter__33__label, EffectType__25__Parameter__34__label, EffectType__25__Parameter__35__label, EffectType__25__Parameter__36__label, EffectType__25__Parameter__37__label, EffectType__25__Parameter__38__label, EffectType__25__Parameter__39__label,
EffectType__26__Parameter__0__label, EffectType__26__Parameter__1__label, EffectType__26__Parameter__2__label, EffectType__26__Parameter__3__label, EffectType__26__Parameter__4__label, EffectType__26__Parameter__5__label, EffectType__26__Parameter__6__label, EffectType__26__Parameter__7__label, EffectType__26__Parameter__8__label, EffectType__26__Parameter__9__label, EffectType__26__Parameter__10__label, EffectType__26__Parameter__11__label, EffectType__26__Parameter__12__label, EffectType__26__Parameter__13__label, EffectType__26__Parameter__14__label, EffectType__26__Parameter__15__label, EffectType__26__Parameter__16__label, EffectType__26__Parameter__17__label, EffectType__26__Parameter__18__label, EffectType__26__Parameter__19__label, EffectType__26__Parameter__20__label, EffectType__26__Parameter__21__label, EffectType__26__Parameter__22__label, EffectType__26__Parameter__23__label, EffectType__26__Parameter__24__label, EffectType__26__Parameter__25__label, EffectType__26__Parameter__26__label, EffectType__26__Parameter__27__label, EffectType__26__Parameter__28__label, EffectType__26__Parameter__29__label, EffectType__26__Parameter__30__label, EffectType__26__Parameter__31__label, EffectType__26__Parameter__32__label, EffectType__26__Parameter__33__label, EffectType__26__Parameter__34__label, EffectType__26__Parameter__35__label, EffectType__26__Parameter__36__label, EffectType__26__Parameter__37__label, EffectType__26__Parameter__38__label, EffectType__26__Parameter__39__label, EffectType__26__Parameter__40__label, EffectType__26__Parameter__41__label, EffectType__26__Parameter__42__label, EffectType__26__Parameter__43__label, EffectType__26__Parameter__44__label, EffectType__26__Parameter__45__label, EffectType__26__Parameter__46__label, EffectType__26__Parameter__47__label, EffectType__26__Parameter__48__label, EffectType__26__Parameter__49__label,
EffectType__27__Parameter__0__label, EffectType__27__Parameter__1__label, EffectType__27__Parameter__2__label, EffectType__27__Parameter__3__label, EffectType__27__Parameter__4__label, EffectType__27__Parameter__5__label, EffectType__27__Parameter__6__label, EffectType__27__Parameter__7__label, EffectType__27__Parameter__8__label, EffectType__27__Parameter__9__label, EffectType__27__Parameter__10__label, EffectType__27__Parameter__11__label, EffectType__27__Parameter__12__label, EffectType__27__Parameter__13__label, EffectType__27__Parameter__14__label, EffectType__27__Parameter__15__label, EffectType__27__Parameter__16__label,
EffectType__28__Parameter__0__label, EffectType__28__Parameter__1__label, EffectType__28__Parameter__2__label, EffectType__28__Parameter__3__label, EffectType__28__Parameter__4__label, EffectType__28__Parameter__5__label, EffectType__28__Parameter__6__label, EffectType__28__Parameter__7__label, EffectType__28__Parameter__8__label, EffectType__28__Parameter__9__label, EffectType__28__Parameter__10__label, EffectType__28__Parameter__11__label, EffectType__28__Parameter__12__label, EffectType__28__Parameter__13__label, EffectType__28__Parameter__14__label,
EffectType__29__Parameter__0__label, EffectType__29__Parameter__1__label, EffectType__29__Parameter__2__label, EffectType__29__Parameter__3__label, EffectType__29__Parameter__4__label, EffectType__29__Parameter__5__label, EffectType__29__Parameter__6__label, EffectType__29__Parameter__7__label, EffectType__29__Parameter__8__label, EffectType__29__Parameter__9__label, EffectType__29__Parameter__10__label, EffectType__29__Parameter__11__label, EffectType__29__Parameter__12__label,
EffectType__30__Parameter__0__label, EffectType__30__Parameter__1__label, EffectType__30__Parameter__2__label, EffectType__30__Parameter__3__label, EffectType__30__Parameter__4__label, EffectType__30__Parameter__5__label, EffectType__30__Parameter__6__label, EffectType__30__Parameter__7__label, EffectType__30__Parameter__8__label, EffectType__30__Parameter__9__label,
EffectType__31__Parameter__0__label, EffectType__31__Parameter__1__label, EffectType__31__Parameter__2__label, EffectType__31__Parameter__3__label, EffectType__31__Parameter__4__label, EffectType__31__Parameter__5__label, EffectType__31__Parameter__6__label, EffectType__31__Parameter__7__label, EffectType__31__Parameter__8__label, EffectType__31__Parameter__9__label, EffectType__31__Parameter__10__label, EffectType__31__Parameter__11__label, EffectType__31__Parameter__12__label, EffectType__31__Parameter__13__label, EffectType__31__Parameter__14__label, EffectType__31__Parameter__15__label, EffectType__31__Parameter__16__label, EffectType__31__Parameter__17__label, EffectType__31__Parameter__18__label, EffectType__31__Parameter__19__label, EffectType__31__Parameter__20__label, EffectType__31__Parameter__21__label, EffectType__31__Parameter__22__label, EffectType__31__Parameter__23__label, EffectType__31__Parameter__24__label, EffectType__31__Parameter__25__label, EffectType__31__Parameter__26__label, EffectType__31__Parameter__27__label,
EffectType__32__Parameter__0__label, EffectType__32__Parameter__1__label, EffectType__32__Parameter__2__label, EffectType__32__Parameter__3__label, EffectType__32__Parameter__4__label, EffectType__32__Parameter__5__label, EffectType__32__Parameter__6__label, EffectType__32__Parameter__7__label, EffectType__32__Parameter__8__label, EffectType__32__Parameter__9__label, EffectType__32__Parameter__10__label, EffectType__32__Parameter__11__label, EffectType__32__Parameter__12__label, EffectType__32__Parameter__13__label, EffectType__32__Parameter__14__label, EffectType__32__Parameter__15__label, EffectType__32__Parameter__16__label, EffectType__32__Parameter__17__label, EffectType__32__Parameter__18__label, EffectType__32__Parameter__19__label, EffectType__32__Parameter__20__label, EffectType__32__Parameter__21__label, EffectType__32__Parameter__22__label, EffectType__32__Parameter__23__label, EffectType__32__Parameter__24__label, EffectType__32__Parameter__25__label, EffectType__32__Parameter__26__label, EffectType__32__Parameter__27__label, EffectType__32__Parameter__28__label, EffectType__32__Parameter__29__label, EffectType__32__Parameter__30__label, EffectType__32__Parameter__31__label, EffectType__32__Parameter__32__label, EffectType__32__Parameter__33__label, EffectType__32__Parameter__34__label, EffectType__32__Parameter__35__label, EffectType__32__Parameter__36__label, EffectType__32__Parameter__37__label, EffectType__32__Parameter__38__label, EffectType__32__Parameter__39__label, EffectType__32__Parameter__40__label, EffectType__32__Parameter__41__label, EffectType__32__Parameter__42__label, EffectType__32__Parameter__43__label, EffectType__32__Parameter__44__label, EffectType__32__Parameter__45__label,
EffectType__33__Parameter__0__label, EffectType__33__Parameter__1__label, EffectType__33__Parameter__2__label, EffectType__33__Parameter__3__label, EffectType__33__Parameter__4__label, EffectType__33__Parameter__5__label, EffectType__33__Parameter__6__label, EffectType__33__Parameter__7__label, EffectType__33__Parameter__8__label, EffectType__33__Parameter__9__label, EffectType__33__Parameter__10__label, EffectType__33__Parameter__11__label, EffectType__33__Parameter__12__label, EffectType__33__Parameter__13__label, EffectType__33__Parameter__14__label, EffectType__33__Parameter__15__label, EffectType__33__Parameter__16__label, EffectType__33__Parameter__17__label, EffectType__33__Parameter__18__label, EffectType__33__Parameter__19__label, EffectType__33__Parameter__20__label, EffectType__33__Parameter__21__label, EffectType__33__Parameter__22__label, EffectType__33__Parameter__23__label, EffectType__33__Parameter__24__label, EffectType__33__Parameter__25__label, EffectType__33__Parameter__26__label, EffectType__33__Parameter__27__label, EffectType__33__Parameter__28__label, EffectType__33__Parameter__29__label, EffectType__33__Parameter__30__label, EffectType__33__Parameter__31__label, EffectType__33__Parameter__32__label, EffectType__33__Parameter__33__label, EffectType__33__Parameter__34__label, EffectType__33__Parameter__35__label, EffectType__33__Parameter__36__label, EffectType__33__Parameter__37__label, EffectType__33__Parameter__38__label, EffectType__33__Parameter__39__label,
EffectType__34__Parameter__0__label, EffectType__34__Parameter__1__label, EffectType__34__Parameter__2__label, EffectType__34__Parameter__3__label, EffectType__34__Parameter__4__label, EffectType__34__Parameter__5__label, EffectType__34__Parameter__6__label, EffectType__34__Parameter__7__label, EffectType__34__Parameter__8__label,
EffectType__35__Parameter__0__label, EffectType__35__Parameter__1__label, EffectType__35__Parameter__2__label, EffectType__35__Parameter__3__label, EffectType__35__Parameter__4__label,
EffectType__36__Parameter__0__label, EffectType__36__Parameter__1__label, EffectType__36__Parameter__2__label, EffectType__36__Parameter__3__label, EffectType__36__Parameter__4__label, EffectType__36__Parameter__5__label, EffectType__36__Parameter__6__label, EffectType__36__Parameter__7__label, EffectType__36__Parameter__8__label, EffectType__36__Parameter__9__label, EffectType__36__Parameter__10__label, EffectType__36__Parameter__11__label, EffectType__36__Parameter__12__label, EffectType__36__Parameter__13__label, EffectType__36__Parameter__14__label, EffectType__36__Parameter__15__label, EffectType__36__Parameter__16__label, EffectType__36__Parameter__17__label, EffectType__36__Parameter__18__label, EffectType__36__Parameter__19__label,
EffectType__37__Parameter__0__label, EffectType__37__Parameter__1__label, EffectType__37__Parameter__2__label, EffectType__37__Parameter__3__label, EffectType__37__Parameter__4__label, EffectType__37__Parameter__5__label, EffectType__37__Parameter__6__label, EffectType__37__Parameter__7__label, EffectType__37__Parameter__8__label, EffectType__37__Parameter__9__label, EffectType__37__Parameter__10__label, EffectType__37__Parameter__11__label, EffectType__37__Parameter__12__label, EffectType__37__Parameter__13__label, EffectType__37__Parameter__14__label, EffectType__37__Parameter__15__label, EffectType__37__Parameter__16__label, EffectType__37__Parameter__17__label, EffectType__37__Parameter__18__label, EffectType__37__Parameter__19__label, EffectType__37__Parameter__20__label, EffectType__37__Parameter__21__label, EffectType__37__Parameter__22__label, EffectType__37__Parameter__23__label, EffectType__37__Parameter__24__label, EffectType__37__Parameter__25__label, EffectType__37__Parameter__26__label, EffectType__37__Parameter__27__label, EffectType__37__Parameter__28__label, EffectType__37__Parameter__29__label, EffectType__37__Parameter__30__label, EffectType__37__Parameter__31__label, EffectType__37__Parameter__32__label, EffectType__37__Parameter__33__label, EffectType__37__Parameter__34__label, EffectType__37__Parameter__35__label, EffectType__37__Parameter__36__label, EffectType__37__Parameter__37__label, EffectType__37__Parameter__38__label, EffectType__37__Parameter__39__label, EffectType__37__Parameter__40__label, EffectType__37__Parameter__41__label, EffectType__37__Parameter__42__label, EffectType__37__Parameter__43__label, EffectType__37__Parameter__44__label, EffectType__37__Parameter__45__label, EffectType__37__Parameter__46__label, EffectType__37__Parameter__47__label, EffectType__37__Parameter__48__label, EffectType__37__Parameter__49__label, EffectType__37__Parameter__50__label, EffectType__37__Parameter__51__label, EffectType__37__Parameter__52__label, EffectType__37__Parameter__53__label, EffectType__37__Parameter__54__label, EffectType__37__Parameter__55__label, EffectType__37__Parameter__56__label, EffectType__37__Parameter__57__label, EffectType__37__Parameter__58__label, EffectType__37__Parameter__59__label, EffectType__37__Parameter__60__label, EffectType__37__Parameter__61__label, EffectType__37__Parameter__62__label, EffectType__37__Parameter__63__label, EffectType__37__Parameter__64__label, EffectType__37__Parameter__65__label, EffectType__37__Parameter__66__label, EffectType__37__Parameter__67__label, EffectType__37__Parameter__68__label, EffectType__37__Parameter__69__label, EffectType__37__Parameter__70__label, EffectType__37__Parameter__71__label, EffectType__37__Parameter__72__label, EffectType__37__Parameter__73__label, EffectType__37__Parameter__74__label, EffectType__37__Parameter__75__label, EffectType__37__Parameter__76__label, EffectType__37__Parameter__77__label,
EffectType__38__Parameter__0__label, EffectType__38__Parameter__1__label, EffectType__38__Parameter__2__label, EffectType__38__Parameter__3__label, EffectType__38__Parameter__4__label, EffectType__38__Parameter__5__label, EffectType__38__Parameter__6__label, EffectType__38__Parameter__7__label, EffectType__38__Parameter__8__label, EffectType__38__Parameter__9__label, EffectType__38__Parameter__10__label, EffectType__38__Parameter__11__label, EffectType__38__Parameter__12__label,
EffectType__39__Parameter__0__label, EffectType__39__Parameter__1__label, EffectType__39__Parameter__2__label, EffectType__39__Parameter__3__label, EffectType__39__Parameter__4__label, EffectType__39__Parameter__5__label, EffectType__39__Parameter__6__label, EffectType__39__Parameter__7__label, EffectType__39__Parameter__8__label, EffectType__39__Parameter__9__label, EffectType__39__Parameter__10__label, EffectType__39__Parameter__11__label, EffectType__39__Parameter__12__label, EffectType__39__Parameter__13__label, EffectType__39__Parameter__14__label, EffectType__39__Parameter__15__label, EffectType__39__Parameter__16__label, EffectType__39__Parameter__17__label, EffectType__39__Parameter__18__label, EffectType__39__Parameter__19__label, EffectType__39__Parameter__20__label};

int Parameter__modifierID[TotalNumOfParameters] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 255, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0,

//AMP
//0, 203, 0, 0, 0, 207, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 210, 211,
0, 203, 0, 0, 0, 207, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 208, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 210, 211, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 203, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 200, 201, 202, 0, 200, 206, 207, 0, 0, 0, 203, 204, 205, 206, 207, 200, 201, 202, 255, 0, 0, 208, 0, 0, 204, 200, 213, 0, 0, 0, 211, 212, 0, 0, 200, 200, 0, 209, 0, 0, 200, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 200, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 203, 0, 0, 0, 0, 0, 0, 0, 0, 204, 205, 206, 207, 208, 209, 210, 211, 0, 0, 0, 0, 0, 0, 0, 0, 214, 215, 216, 217, 0, 0, 0, 0, 212, 0, 213, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 203, 0, 204, 204, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 203, 0, 204, 205, 200, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0,
203, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 203, 0, 0, 204, 205, 206, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 203, 201, 202, 255, 0, 0, 0, 0,
0, 0, 0, 204, 203, 200, 201, 202, 255, 0, 0, 0,
0, 0, 203, 204, 205, 0, 200, 201, 202, 255, 0, 200, 206, 0, 0,
0, 0, 203, 203, 200, 200, 200, 0, 0, 204, 205, 200, 200, 200, 200, 200, 200, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 206, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 207, 208, 209, 210, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 211, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 200,
0, 200, 201, 202, 203, 204, 255, 0, 0, 0, 0, 0, 0, 0,
0, 201, 202, 203, 200, 255, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 201, 205,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 201, 202, 255, 0,
200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
0, 0,
200, 201, 202, 255, 0, 0,
0, 203, 0, 213, 215, 204, 205, 206, 0, 207, 0, 0, 208, 0, 214, 216, 209, 210, 211, 0, 212, 0, 0, 200, 201, 202, 255, 0, 0, 0, 224, 0, 218, 219, 220, 221, 222, 0, 223, 0,
0, 0, 0, 0, 0, 205, 203, 204, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
203, 204, 200, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0,
200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0,
203, 0, 0, 0, 202, 0, 0, 0, 200, 201, 202, 255, 0,
203, 204, 0, 0, 200, 201, 202, 255, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0,
203, 204, 205, 206, 207, 208, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0,
0, 0, 203, 204, 205, 206, 207, 208, 209, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 202, 255, 0, 0, 0,
200, 201, 0, 0, 202, 203, 204, 255, 0,
200, 201, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
206, 200, 202, 204, 0, 0, 207, 201, 203, 205, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 200, 201, 0,
203, 202, 201, 255, 0, 200, 0, 0, 0, 0, 204, 205, 0,
0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 200, 0, 0, 0, 0, 0, 0};

int Parameter__displayType [TotalNumOfParameters] = { 0, 0, 0, 0, 0, 2, 1, 4, 0, 0, 2, 0, 0, 0, 2, 0, 1, 0,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 2, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0,

//AMP
//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

7, 7, 7, 7, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 4, 4, 4, 2, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 5, 5, 4, 0, 0, 4, 0, 0, 0, 0, 4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 2, 0, 0, 0, 0, 2, 5, 0, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 0,
0, 0, 4, 0, 0, 0, 0, 0, 2, 0, 4, 0, 0, 0, 2, 0, 0, 4, 1, 0, 0, 0, 0,
0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 4, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0,
2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,
4, 4, 4, 0, 0, 0, 0, 0, 2, 0, 0, 0,
0, 2, 0, 0, 0, 4, 0, 0, 0, 2, 0, 0, 0, 0, 0,
0, 2, 0, 0, 0, 0, 5, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 2, 1, 0,
2, 0, 0, 0, 0, 0, 2, 5, 0, 0, 0, 5, 0, 0,
0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0,
0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
3, 3, 3, 3, 0, 0, 0, 0, 0, 2,
0, 0,
0, 0, 0, 0, 0, 0,
2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
4, 5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0,
0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0,
0, 0, 1, 0, 0, 0, 0, 2, 1, 0,
0, 0, 0, 0, 0, 0, 0, 4, 1, 0, 0, 0, 0, 0, 4, 1, 0, 0, 0, 0, 0, 4, 1, 0, 0, 0, 2, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0,
0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2,
0, 0, 2, 0, 0, 0, 0, 2, 2,
0, 0, 0, 0, 2,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 1,
0, 0, 0, 1, 1, 1, 0, 0, 2, 0, 4, 0, 4, 4, 1, 4, 0, 0, 0, 0, 0};

char Parameter__displayTypeModalValues__0[] = "knob";
char Parameter__displayTypeModalValues__1[] = "toggle";
char Parameter__displayTypeModalValues__2[] = "dropdownlarge";
char Parameter__displayTypeModalValues__3[] = "slider";
char Parameter__displayTypeModalValues__4[] = "dropdown";
char Parameter__displayTypeModalValues__5[] = "dropdownsmall";
char Parameter__displayTypeModalValues__6[] = "reversetoggle";
char Parameter__displayTypeModalValues__7[] = "dropdownhuge";


char *Parameter__displayTypeModalValues[8] = { Parameter__displayTypeModalValues__0,
Parameter__displayTypeModalValues__1,
Parameter__displayTypeModalValues__2,
Parameter__displayTypeModalValues__3,
Parameter__displayTypeModalValues__4,
Parameter__displayTypeModalValues__5,
Parameter__displayTypeModalValues__6,
Parameter__displayTypeModalValues__7};

int Parameter__types[TotalNumOfParameters] = { 3, 4, 4, 4, 3, 1, 1, 1, 4, 0, 1, 3, 1, 5, 9, 3, 1, 3,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 7, 8, 10, 12, 1, 0, 0, 0,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 1, 1, 0, 6, 7, 8, 10, 12, 0,

// AMP
//1, 3, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 4, 1, 1, 3, 3, 1, 3, 3, 7, 8, 10, 3, 4, 4, 3, 0, 4, 1, 4, 4, 1, 1, 4, 3, 1, 0, 1, 1, 4, 3, 4, 3, 1, 4, 4, 3, 1, 5, 4, 4, 4, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1, 4, 4, 4, 3, 3, 3, 4, 4, 1, 3, 3, 4, 1, 3, 3, 3, 1, 3, 3, 4, 3,
1, 3, 3, 3, 3, 3, 4, 4, 4, 3,
4, 4, 4, 4, 1, 1, 3, 3, 1, 3,
3, 7, 8, 10, 3, 4, 4, 3, 0, 4,
1, 4, 4, 1, 1, 4, 3, 1, 0, 1,
1, 4, 3, 4, 3, 1, 4, 4, 3, 1,
5, 4, 4, 4, 1, 3, 3, 3, 3, 3,
3, 3, 3, 3, 4, 4, 4, 4, 1, 1,
4, 4, 4, 3, 3, 3, 4, 4, 1, 3,
3, 4, 1, 3, 3, 3, 1, 3, 3, 4,
3, 1, 1, 1, 1, 1, 1, 1, 1, 1,
// 100
1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 1,

2, 1, 2, 1, 1, 3, 3, 3, 3, 7, 8, 10, 1, 0, 5, 5, 3, 3, 3, 4, 4, 4, 3, 3, 3, 4, 3, 3, 3,
1, 3, 4, 5, 3, 3, 3, 3, 3, 3, 4, 3, 4, 6, 7, 8, 11, 12, 3, 1, 3, 3, 0, 1, 3, 3, 4, 4, 4, 4, 3, 3, 5, 4, 4,
1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 4, 4, 4, 4, 3, 3, 5, 6, 7, 8, 11, 12, 0, 3, 1, 1, 3, 1, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 3, 3, 4, 3, 3, 1, 1, 1, 1, 1, 4, 1, 3, 1, 4, 4, 5, 4, 1, 4, 4, 4, 4, 3, 3, 1, 4, 3,
3, 3, 3, 3, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 1, 1, 1, 1, 6, 7, 8, 11, 12, 3, 0, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 1, 4, 3, 3, 3, 3, 1, 13, 13, 1, 0, 1, 1, 3, 1, 1, 3, 1, 3, 1, 3, 4, 4, 3, 3, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 13, 0, 3,
1, 1, 4, 1, 3, 4, 3, 3, 1, 1, 6, 7, 8, 9, 12, 0, 1, 3, 4, 3, 5, 4, 3,
1, 4, 1, 3, 3, 3, 3, 3, 1, 4, 1, 6, 7, 8, 9, 12, 0, 1, 1, 4, 5, 4, 3,
3, 3, 3, 3, 1, 6, 7, 8, 9, 12, 3, 0, 3, 4, 4, 4, 3, 5,
1, 1, 4, 1, 1, 5, 3, 4, 3, 3, 3, 6, 7, 8, 9, 12, 0, 1, 1, 3,
1, 4, 4, 5, 3, 3, 7, 8, 10, 3, 5, 1, 0,
1, 1, 1, 5, 3, 6, 7, 8, 9, 12, 0, 0,
1, 1, 4, 3, 3, 1, 6, 7, 8, 10, 12, 3, 3, 3, 0,
1, 1, 3, 3, 1, 1, 1, 1, 1, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 6, 7, 8, 11, 12, 3, 0, 3, 3, 3, 1, 1, 1, 1, 1, 1, 4, 4, 3, 3, 3, 3, 1, 13, 13, 13, 13, 13, 13, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 3, 3, 3, 1, 1, 1, 4,
1, 4, 4, 3, 7, 8, 10, 1, 0, 3, 3, 1, 4, 4,
1, 5, 3, 3, 3, 10, 5, 0, 4, 4, 1, 3, 3, 3, 4, 3, 1, 1, 8, 4,
3, 3, 4, 4, 7, 0, 1, 1, 3, 3, 8,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 8, 10, 0,
3, 3, 3, 3, 3, 3, 3, 3, 3, 1,
3, 3,
6, 7, 8, 10, 12, 0,
1, 4, 1, 3, 3, 3, 3, 3, 4, 4, 4, 1, 4, 1, 3, 3, 3, 3, 3, 4, 4, 4, 0, 6, 7, 8, 9, 12, 0, 1, 4, 1, 3, 3, 3, 3, 3, 4, 4, 4,
1, 1, 4, 4, 4, 1, 3, 3, 4, 4, 4, 3, 6, 7, 8, 9, 12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
3, 3, 3, 1, 1, 3, 1, 3, 1, 3, 3, 6, 7, 8, 11, 12, 0,
4, 1, 4, 4, 4, 4, 3, 3, 3, 3, 0, 7, 8, 10, 0,
3, 4, 4, 4, 4, 1, 4, 4, 0, 7, 8, 10, 0,
4, 4, 1, 4, 6, 7, 8, 9, 12, 0,
4, 4, 3, 4, 4, 4, 3, 1, 1, 3, 4, 4, 4, 3, 1, 1, 3, 4, 4, 4, 3, 1, 1, 6, 7, 8, 10, 0,
3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 4, 4, 4, 4, 3, 1, 1, 1, 3, 6, 7, 8, 9, 12, 0, 4,
1, 1, 3, 4, 4, 3, 3, 3, 4, 4, 4, 4, 4, 3, 3, 3, 3, 1, 1, 1, 1, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 6, 7, 8, 11, 12, 0, 1,
3, 3, 1, 0, 3, 3, 7, 10, 1,
3, 4, 4, 4, 1,
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 8, 10, 0,
1, 4, 3, 3, 3, 1, 1, 4, 3, 3, 3, 1, 1, 1, 4, 4, 4, 3, 4, 3, 1, 1, 4, 4, 4, 3, 4, 3, 4, 4, 3, 3, 13, 1, 4, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 13, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1,
6, 7, 8, 9, 0, 3, 1, 3, 1, 1, 3, 3, 1,
1, 3, 3, 1, 1, 1, 7, 8, 10, 0, 1, 4, 1, 1, 1, 1, 1, 1, 0, 0, 1};

char Parameter__typeModalValues__0[] = "NONE";
char Parameter__typeModalValues__1[] = "INT";
char Parameter__typeModalValues__2[] = "INTXL";
char Parameter__typeModalValues__3[] = "LIN";
char Parameter__typeModalValues__4[] = "LOG";
char Parameter__typeModalValues__5[] = "LOGLOG";
char Parameter__typeModalValues__6[] = "MIX";
char Parameter__typeModalValues__7[] = "LEVEL";
char Parameter__typeModalValues__8[] = "PAN";
char Parameter__typeModalValues__9[] = "BYP1";
char Parameter__typeModalValues__10[] = "BYP2";
char Parameter__typeModalValues__11[] = "BYP3";
char Parameter__typeModalValues__12[] = "GMIX";
char Parameter__typeModalValues__13[] = "DUMMY";


char *Parameter__typeModalValues[14] = { Parameter__typeModalValues__0,
Parameter__typeModalValues__1,
Parameter__typeModalValues__2,
Parameter__typeModalValues__3,
Parameter__typeModalValues__4,
Parameter__typeModalValues__5,
Parameter__typeModalValues__6,
Parameter__typeModalValues__7,
Parameter__typeModalValues__8,
Parameter__typeModalValues__9,
Parameter__typeModalValues__10,
Parameter__typeModalValues__11,
Parameter__typeModalValues__12,
Parameter__typeModalValues__13};

unsigned int Parameter__defaultValue[TotalNumOfParameters] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

// AMP    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0,
0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int Parameter__minDispValue[TotalNumOfParameters] = { -80, 1, 0, 0, -20, 0, 0, 0, 10, 0, 0, 0, 0, 1, 0, 0, 0, 0,
-12, -12, -12, -12, -12, -12, -12, -12, -12, -12, 0, -80, -1, 0, 0, 0, 0, 0, 0,
20, 100, 100, 100, 200, 0, 0, 0, 0, 0, -12, -12, -12, -12, -12, 0, 0, 0, 0, -80, -1, 0, 0, 0,

/* AMP */
0, 0, 0, 0, 0, 0, 10, 400, 200, 0,
10, 400, 10, 4000, 0, 0, 0, -1, 0, 0,
0, -80, -1, 0, 0, 0, 40, 0, 0, 50,
0, 1, 2, 0, 0, 1, 0, 0, 0, 0,
0, 0, -1, 400, 0, 0, 0, 0, 0, 0,
0, 0, 1, 0, 2, -12, -12, -12, -12, -12,
-12, -12, -12, 0, 0, 0, 400, 400, 0, 0,
0, 10, 100, -10, 0, 0, -60, 0, 0, -10,
0, 0, 0, -1, -10, 0, 0, 30, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, -1, -10,
// #100
1, 50, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0,

0, 0, 0, 0, 0, -80, -80, -1, -1, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 20, 200, 0, 0, 0, 0, 2000, 0, 0, 0,
0, 0, 200, 0, 0, 0, 0, -40, -40, 0, 20, 0, 0, 0, -80, -1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 20, 100, 0, 0, -12, -12, 0, 0, 100,
0, 0, 0, 0, -1, -1, -1, -1, -1, 0, 20, 200, 0, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, -1, 0, 0, 0, 0, 0, 0, 0, -80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 500, 0, 0, 0, 20, 100, 0, 0, -12, -12, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -80, 0, 0, 0, -1, 0, 0, 0, -2, -2, -50, -50, -50, -50, -24, -24, -24, -24, 100, 100, 100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 20, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, 30, 0, 0,
0, 1, 0, 0, 0, 200, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -80, -1, 0, 0, 0, 0, 0, 200, 0, 20, 0,
0, 0, 0, -6, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 0, 50, 1, 0, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0,
0, 100, 500, 2, 0, 0, -80, -1, 0, 0, 0, 0, 0,
0, 0, 0, 4, 0, 0, -80, -1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 0, -1, 0,
0, 0, -1, 0, 0, 0, 0, 0, 0, -50, -50, -24, -24, 0, 0, -1, -1, 0, 0, 0, 0, 0, 30, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2000, 0, 0, 0, -1, 0, 4, 1, 2, 3, 4, 5, 6, 7, 0, 0, 2, 1, 0, 1, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20,
0, 20, 0, -12, -80, -1, 0, 0, 0, -1, -1, 0, 20, 200,
0, 0, 0, 0, 0, 0, 0, 0, 20, 200, 0, -1, -12, -12, 200, -12, 0, 0, -1, 0,
0, 0, 20, 200, -80, 0, 0, 0, -1, -1, -1,
-20, -20, -20, -20, -1, -1, -1, -1, -20, -20, -20, -20, -20, -20, -20, -20, -80, -1, 0, 0,
0, 0, 0, 0, -1, -1, -1, -1, -80, 0,
0, 0,
0, -80, -1, 0, 0, 0,
0, 40, 0, -24, -50, 0, 0, -1, 0, 200, 0, 0, 40, 0, -24, -50, 0, 0, -1, 0, 200, 0, 0, 0, -80, -1, 0, 0, 0, 0, 20, 0, -24, -50, 0, 0, -1, 0, 200, 0,
0, 0, 20, 2000, 0, 0, 0, -1, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,
0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0,
40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -80, -1, 0, 0,
-100, 0, 0, 0, 1, 0, 10, 200, 0, -80, -1, 0, 0,
2, 0, 0, 200, 0, -80, -1, 0, 0, 0,
50, 1000, -80, 1, 0, 0, -20, 0, 0, -80, 1, 0, 0, -20, 0, 0, -80, 1, 0, 0, -20, 0, 0, 0, -80, -1, 0, 0,
0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 200,
0, 0, 0, 50, 0, 0, -1, -1, 0, 100, 100, 100, 100, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, -80, -1, 0, 0, 0, 0,
0, -1, 0, 0, -1, -1, -80, 0, 0,
-100, 1, 0, 0, 0,
-20, -20, -20, -20, -1, -1, -1, -1, -20, -20, -20, -20, -20, -20, -20, -20, -80, -1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -80, 0, 0, 0, 0, 0, 0, 0, -80, 0, 0, -100, 1, 30, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, -80, -1, 0, 0, 0, 0, -100, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, -80, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int Parameter__maxDispValue[TotalNumOfParameters] = { 0, 20, 0, 1, 20, 3, 1, 2, 1000, 0, 8, 1, 2, 100, 2, 0, 1, 0,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 1, 20, 1, 1, 0, 3, 0, 0, 0,
2000, 10000, 10000, 10000, 20000, 10, 10, 10, 10, 10, 12, 12, 12, 12, 12, 2, 2, 0, 1, 20, 1, 1, 0, 0,

/* AMP */
172, 10, 10, 10, 10, 10, 1000, 40000, 2000, 10,
1000, 40000, 1000, 40000, 3, 2, 10, 1, 12, 10,
10, 20, 1, 1, 10, 10, 400, 10, 0, 500,
3, 1000, 2000, 1, 71, 100, 1, 19, 0, 1,
1, 10, 1, 4000, 24, 1, 10, 10, 10, 2,
10, 10, 100, 10, 1, 12, 12, 12, 12, 12,
12, 12, 12, 1, 0, 0, 40000, 40000, 11, 7,
10, 1000, 10000, 10, 10, 10, 0, 10, 1, 10,
100, 100, 1, 1, 10, 1, 1, 100, 10, 20,
1, 0, 0, 100, 0, 0, 1, 0, 1, 10,
// #100
10, 150, 2, 0, 1, 0, 0, 0, 0, 1,
0, 1, 10,

232, 11, 232, 11, 1, 0, 0, 1, 1, 20, 1, 1, 2, 0, 2, 2, 1, 1, 1, 2000, 20000, 4, 1, 1, 10, 20000, 0, 0, 1,
20, 20, 20000, 1, 1, 1, 0, 10, 10, 0, 2000, 1, 10, 1, 20, 1, 4, 0, 1, 8, 1, 1, 1, 6, 12, 1, 2000, 10000, 10, 10, 12, 12, 1, 2, 10000,

/* DELAY */
13, 6, 8, 1, 1, 1, 1, 1, 1, 78,
2000, 20000, 10, 20, 1, 1, 10, 1, 20, 1,
4, 0, 0, 1, 8, 8, 8, 1, 2, 78,
1, 1, 1, 1, 1, 1, 3, 3, 0, 1,
1, 4, 80, 0, 1, 1, 1, 3, 2, 2,
78, 78, 10, 8, 3, 78, 1000, 5000, 10, 10,
24, 2000, 10000, 10, 10, 12, 12, 1, 2, 0,

2, 2, 2, 2, 78, 78, 78, 78, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 78, 78, 78, 78, 1, 20, 1, 4, 0, 1, 0, 9, 60, 1, 1, 1, 0, 1, 1, 1, 1, 3, 10, 1, 2, 2, 50, 50, 50, 50, 24, 24, 24, 24, 10000, 10000, 10000, 10000, 10, 10, 10, 10, 1, 80, 1, 1, 2, 1, 1, 1, 1, 1, 3, 3, 1, 2, 78, 78, 1, 1, 10, 0, 78, 1, 5, 1, 2000, 20000, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 250, 0, 1,
10, 4, 10, 78, 1, 20000, 0, 3, 8, 2, 1, 20, 1, 2, 0, 0, 3, 1, 2, 1, 10, 2000, 1,
5, 10, 78, 1, 0, 0, 1, 3, 8, 100, 2, 1, 20, 1, 2, 0, 0, 3, 1, 20000, 1, 2000, 1,
10, 1, 1, 6, 78, 1, 20, 1, 2, 0, 1, 0, 3, 10, 10, 10, 3, 10,
7, 5, 10, 8, 78, 10, 0, 5000, 10, 3, 2, 1, 20, 1, 2, 0, 0, 2, 1, 0,
7, 1000, 5000, 20, 1, 1, 20, 1, 1, 1, 2, 5, 0,
9, 9, 9, 40, 1, 1, 20, 1, 2, 0, 0, 0,
1, 8, 20, 1, 0, 78, 1, 20, 1, 1, 0, 3, 4, 1, 0,
8, 5, 1, 1, 48, 48, 11, 17, 1, 50, 50, 24, 24, 1, 1, 1, 1, 2, 2, 1, 1, 2, 8100, 1, 20, 1, 4, 0, 1, 0, 1, 2, 2, 78, 78, 78, 78, 2, 1, 20000, 1, 1, 1, 1, 1, 8, 6, 7, 8, 9, 10, 11, 12, 31, 31, 16, 31, 1, 78, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 5, 1, 5, 1, 0, 0, 1, 1, 1, 2000,
8, 20000, 10, 12, 20, 1, 1, 1, 1, 1, 1, 3, 2000, 20000,
28, 1, 1, 1, 1, 1, 1, 0, 2000, 20000, 9, 1, 12, 12, 2000, 12, 24, 2, 1, 1,
1, 1, 2000, 20000, 20, 0, 1, 3, 1, 1, 1,
20, 20, 20, 20, 1, 1, 1, 1, 20, 20, 20, 20, 20, 20, 20, 20, 20, 1, 1, 0,
1, 1, 1, 1, 1, 1, 1, 1, 20, 1,
1, 1,
1, 20, 1, 1, 0, 0,
7, 4000, 3, 24, 50, 0, 1, 1, 1, 20000, 10, 7, 4000, 3, 24, 50, 0, 1, 1, 1, 20000, 10, 0, 1, 20, 1, 2, 0, 0, 7, 20000, 3, 24, 50, 0, 1, 1, 1, 20000, 10,
1, 3, 2000, 20000, 2, 1, 1, 1, 5, 1, 1, 1, 1, 20, 1, 2, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
1, 1, 2, 40, 5, 1, 5, 1, 5, 1, 0, 1, 20, 1, 4, 0, 0,
800, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 1, 1, 0,
0, 1, 1, 1, 20, 6, 1000, 20000, 0, 20, 1, 1, 0,
2000, 2, 1, 20000, 1, 20, 1, 2, 0, 0,
500, 10000, 0, 20, 0, 1, 20, 1, 1, 0, 20, 0, 1, 20, 1, 1, 0, 20, 0, 1, 20, 1, 1, 1, 20, 1, 1, 0,
1, 1, 1, 10, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 10, 10, 10, 10, 1, 1, 1, 1, 3, 1, 20, 1, 2, 0, 0, 20000,
1, 8, 1, 5000, 2, 1, 1, 1, 10, 10000, 10000, 10000, 10000, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 1, 4, 0, 0, 1,
1, 1, 5, 0, 1, 1, 20, 1, 2,
0, 20, 1, 1, 12,
20, 20, 20, 20, 1, 1, 1, 1, 20, 20, 20, 20, 20, 20, 20, 20, 20, 1, 1, 0,
8, 30, 0, 0, 3, 78, 8, 30, 0, 0, 3, 78, 2, 1, 10, 10, 10, 1, 10, 0, 2, 1, 10, 10, 10, 1, 10, 0, 10, 10, 0, 4, 250, 1, 30, 78, 32, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 20, 1, 1, 0, 1, 1, 0, 3, 1, 1, 0, 1,
1, 1, 1, 1, 1, 0, 20, 1, 1, 0, 7, 100, 2, 2, 1, 1, 2, 1, 0, 0, 1};

int Parameter__precision [TotalNumOfParameters] = { 1, 3, 3, 2, 1, 0, 0, 0, 2, 0, 0, 1, 0, 2, 0, 3, 0, 2,
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0,
2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 0, 0, 0, 1, 1, 1, 0, 0, 0,

// AMP    0, 2, 2, 2, 2, 2, 1, 0, 1, 3, 1, 0, 1, 0, 0, 0, 2, 3, 0, 2, 2, 1, 1, 0, 2, 3, 1, 2, 0, 2, 0, 1, 2, 0, 0, 2, 3, 0, 0, 0, 0, 3, 3, 1, 2, 0, 2, 3, 3, 0, 2, 3, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 0, 0, 0, 0, 2, 2, 2, 1, 2, 3, 0, 2, 1, 2, 0, 1, 2, 2, 0, 0, 2, 3, 1,
0, 2, 2, 2, 2, 2, 1, 0, 1, 3, 1, 0, 1, 0, 0, 0, 2, 3, 0, 2, 2, 1, 1, 0, 2, 3, 1, 2, 0, 2, 0, 1, 2, 0, 0, 2, 3, 0, 0, 0, 0, 3, 3, 1, 2, 0, 2, 3, 3, 0, 2, 3, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 0, 0, 0, 0, 2, 2, 2, 1, 2, 3, 0, 2, 1, 2, 0, 1, 2, 2, 0, 0, 2, 3, 1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2, 2, 1, 2, 1, 1, 0, 3, 2, 1, 2, 0, 3, 3, 2,
0, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 2, 1, 2, 2, 3, 3, 2, 2, 2, 2, 2,
0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 3, 3, 1, 1, 2, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 0, 2, 3, 0, 2, 2, 3, 3, 2, 2, 0, 3, 1,
1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 1, 1, 1, 0, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
0, 0, 3, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 3, 1, 2, 2, 1,
0, 3, 0, 1, 1, 2, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 2, 3, 1,
3, 1, 1, 2, 0, 1, 1, 1, 0, 0, 1, 0, 1, 3, 3, 3, 1, 2,
0, 0, 3, 0, 0, 2, 1, 1, 2, 1, 2, 1, 1, 1, 0, 0, 0, 0, 0, 2,
0, 0, 0, 2, 2, 2, 1, 1, 0, 2, 2, 0, 0,
0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 3, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 2,
0, 1, 3, 2, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1,
0, 2, 2, 2, 1, 0, 2, 0, 1, 1, 0, 3, 1, 1, 1, 1, 0, 0, 1, 0,
1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0,
1, 1, 1, 1, 2, 2, 2, 2, 1, 0,
1, 1,
0, 1, 1, 0, 0, 0,
0, 2, 0, 0, 2, 1, 1, 1, 2, 0, 3, 0, 2, 0, 0, 2, 1, 1, 1, 2, 2, 3, 0, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 2, 1, 1, 1, 2, 2, 2,
0, 0, 1, 0, 2, 0, 1, 1, 2, 2, 2, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0,
1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0,
1, 2, 2, 2, 2, 0, 2, 2, 0, 1, 1, 0, 0,
2, 3, 0, 0, 1, 1, 1, 0, 0, 0,
1, 0, 1, 3, 3, 2, 1, 0, 0, 1, 3, 3, 2, 1, 0, 0, 1, 3, 3, 2, 1, 0, 0, 1, 1, 1, 0, 0,
1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 3, 3, 3, 3, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1,
0, 0, 1, 2, 3, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
2, 2, 0, 0, 1, 1, 1, 0, 0,
1, 2, 2, 2, 0,
2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0,
0, 3, 1, 1, 1, 0, 0, 3, 1, 1, 1, 0, 0, 0, 2, 2, 2, 1, 2, 1, 0, 0, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2, 0, 0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0,
0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int Parameter__unit[TotalNumOfParameters] = { 1, 0, 4, 4, 1, 0, 0, 0, 2, 0, 0, 5, 0, 0, 0, 4, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0,
2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 5, 1, 0, 0, 0, 0,

// AMP 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, /*-8*/ 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0, /*-8*/ 0, 2, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 2, 2, 0, 0, 2, 2, 2, 0, 0, 5, 4, 0, 0, 0, 5, 4, 0, 5, 0, 0, 0, 2, 0, 2, 5,
0, 0, 0, 0, 0, 0, 2, 2, 2, 0,
0, 2, 2, 2, 0, 0, 0, 0, 0, 0,
0, 1, 0, 0, 0, 0, 2, 0, 0, 2,
0, 0, 2, 0, 0, 4, 0, 0, 0, 0,
0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 5, 4, 4, 2, 2, 0, 0,
2, 2, 2, 0, 0, 5, 4, 0, 0, 0,
5, 4, 0, 5, 0, 0, 0, 2, 0, 2,
5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 100
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0,

0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5, 0, 5, 2, 2, 0, 0, 5, 0, 2, 4, 4, 0,
0, 3, 2, 0, 5, 0, 4, 1, 1, 4, 2, 5, 2, 5, 1, 0, 0, 0, 5, 0, 5, 5, 0, 0, 0, 5, 2, 2, 0, 0, 1, 1, 0, 0, 2,
0, 0, 4, 5, 5, 5, 5, 0, 5, 0, 2, 2, 2, 2, 5, 5, 0, 5, 1, 0, 0, 0, 0, 5, 0, 0, 4, 0, 5, 0, 5, 5, 5, 5, 0, 0, 6, 6, 4, 0, 0, 0, 1, 1, 4, 5, 5, 0, 0, 0, 0, 0, 2, 0, 6, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 4,
4, 4, 4, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 5, 1, 0, 0, 0, 5, 0, 0, 3, 5, 5, 5, 1, 5, 5, 5, 5, 0, 0, 5, 5, 5, 7, 7, 7, 7, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 5, 1, 5, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 5, 0, 5, 0, 5, 2, 2, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 4,
0, 0, 2, 0, 5, 2, 4, 6, 0, 0, 5, 1, 0, 0, 0, 0, 0, 5, 2, 5, 0, 2, 5,
0, 2, 0, 5, 5, 4, 5, 6, 0, 2, 0, 5, 1, 0, 0, 0, 0, 0, 0, 2, 0, 2, 5,
2, 5, 5, 1, 0, 5, 1, 0, 0, 0, 5, 0, 5, 0, 3, 3, 5, 0,
0, 0, 2, 0, 0, 0, 5, 2, 0, 6, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0,
0, 2, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 5, 5, 1, 0, 0, 0, 0, 0,
0, 0, 2, 5, 5, 0, 5, 1, 0, 0, 0, 6, 5, 0, 0,
0, 0, 5, 5, 0, 0, 0, 0, 0, 7, 7, 0, 0, 5, 5, 0, 0, 4, 4, 5, 5, 0, 0, 5, 1, 0, 0, 0, 5, 0, 5, 4, 4, 0, 0, 0, 0, 0, 0, 2, 4, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 5, 4, 4, 0, 0, 0, 2,
0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2,
0, 0, 0, 0, 5, 0, 0, 0, 2, 2, 0, 0, 1, 1, 2, 1, 0, 0, 0, 2,
5, 5, 2, 2, 1, 0, 0, 0, 0, 0, 0,
1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
5, 5, 5, 5, 0, 0, 0, 0, 1, 0,
5, 5,
5, 1, 0, 0, 0, 0,
0, 2, 0, 0, 7, 5, 5, 0, 4, 2, 0, 0, 2, 0, 0, 7, 5, 5, 0, 4, 2, 0, 0, 5, 1, 0, 0, 0, 0, 0, 2, 0, 0, 7, 5, 5, 0, 4, 2, 0,
0, 0, 2, 2, 0, 0, 5, 5, 0, 4, 4, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
5, 5, 4, 0, 0, 5, 0, 5, 0, 5, 5, 5, 1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
1, 4, 4, 4, 0, 0, 2, 2, 0, 1, 0, 0, 0,
2, 0, 0, 2, 5, 1, 0, 0, 0, 0,
2, 2, 1, 0, 4, 4, 1, 0, 0, 1, 0, 4, 4, 1, 0, 0, 1, 0, 4, 4, 1, 0, 0, 5, 1, 0, 0, 0,
5, 5, 5, 2, 5, 5, 4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 6, 5, 1, 0, 0, 0, 0, 2,
0, 0, 5, 0, 0, 5, 5, 5, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 0, 0, 0, 5, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 1, 0, 0,
1, 0, 4, 4, 0,
1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
0, 2, 5, 5, 6, 0, 0, 2, 5, 5, 6, 0, 0, 0, 4, 4, 4, 5, 4, 1, 0, 0, 4, 4, 4, 5, 4, 1, 4, 4, 1, 0, 0, 0, 2, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0,
5, 1, 0, 0, 0, 5, 0, 1, 0, 0, 5, 5, 0,
0, 5, 5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

char Parameter__unitModalValues__0[] = "";
char Parameter__unitModalValues__1[] = "DB";
char Parameter__unitModalValues__2[] = "Hz";
char Parameter__unitModalValues__3[] = "Sec";
char Parameter__unitModalValues__4[] = "MSec";
char Parameter__unitModalValues__5[] = "Prc";
char Parameter__unitModalValues__6[] = "Deg";
char Parameter__unitModalValues__7[] = "Cents";


char *Parameter__unitModalValues[8] = { Parameter__unitModalValues__0,
Parameter__unitModalValues__1,
Parameter__unitModalValues__2,
Parameter__unitModalValues__3,
Parameter__unitModalValues__4,
Parameter__unitModalValues__5,
Parameter__unitModalValues__6,
Parameter__unitModalValues__7};

unsigned int Parameter__numVals [TotalNumOfParameters] = { 65534, 65534, 65534, 65534, 65534, 4, 2, 3, 65534, 65534, 9, 65534, 3, 65534, 3, 65534, 2, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 4, 65534, 65534, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 3, 3, 65534, 65534, 65534, 65534, 2, 65534, 65534,

// AMP   173, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 4, 3, 65534, 65534, 13, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 4, 65534, 65534, 5, 72, 65534, 65534, 20, 65534, 2, 2, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 3, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 12, 8, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 2, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534,
173, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 4, 3, 65534, 65534, 13, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 4, 65534, 65534, 5, 72, 65534, 65534, 20, 65534, 2, 2, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 3, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 12, 8, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 2, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

65534, 12, 65534, 12, 2, 65534, 65534, 65534, 65534, 65534, 65534, 2, 3, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534,
21, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 5, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534,
14, 7, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 79, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 5, 65534, 65534, 65534, 9, 9, 65534, 2, 65534, 79, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 2, 5, 65534, 65534, 65534, 65534, 65534, 4, 3, 3, 79, 79, 65534, 9, 65534, 79, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534,
65534, 65534, 65534, 65534, 79, 79, 79, 79, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 79, 79, 79, 79, 65534, 65534, 65534, 5, 65534, 65534, 65534, 10, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534, 2, 65534, 79, 79, 65534, 65534, 65534, 65534, 79, 65534, 6, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534,
11, 65534, 65534, 79, 65534, 65534, 65534, 65534, 9, 3, 65534, 65534, 65534, 3, 65534, 65534, 4, 65534, 65534, 65534, 65534, 65534, 65534,
6, 65534, 79, 65534, 65534, 65534, 65534, 65534, 9, 65534, 3, 65534, 65534, 65534, 3, 65534, 65534, 4, 2, 65534, 65534, 65534, 65534,
65534, 65534, 65534, 65534, 79, 65534, 65534, 65534, 3, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534,
8, 6, 65534, 9, 79, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 3, 65534, 65534, 3, 65534, 65534,
8, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534, 6, 65534,
10, 10, 10, 65534, 65534, 65534, 65534, 65534, 3, 65534, 65534, 65534,
2, 9, 65534, 65534, 65534, 79, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534,
9, 6, 65534, 65534, 49, 49, 12, 18, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 3, 65534, 65534, 65534, 65534, 5, 65534, 65534, 65534, 65534, 65534, 65534, 79, 79, 79, 79, 3, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 78, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 6, 65534, 6, 65534, 65534, 65534, 2, 2, 2, 65534,
9, 65534, 65534, 65534, 65534, 65534, 2, 2, 65534, 65534, 65534, 4, 65534, 65534,
29, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 10, 65534, 65534, 65534, 65534, 65534, 65534, 3, 65534, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 2, 4, 65534, 65534, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2,
65534, 65534,
65534, 65534, 65534, 2, 65534, 65534,
8, 65534, 4, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 8, 65534, 4, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 3, 65534, 65534, 8, 65534, 4, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534,
2, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 3, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534,
65534, 65534, 65534, 65534, 6, 65534, 6, 65534, 6, 65534, 65534, 65534, 65534, 65534, 5, 65534, 65534,
65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534,
65534, 65534, 65534, 65534, 65534, 7, 65534, 65534, 65534, 65534, 65534, 2, 65534,
65534, 65534, 2, 65534, 65534, 65534, 65534, 3, 65534, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 2, 65534, 65534, 65534, 65534, 65534, 2, 2, 65534, 65534, 65534, 65534, 65534, 2, 2, 65534, 65534, 65534, 2, 65534,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 9, 9, 9, 9, 65534, 65534, 65534, 65534, 65534, 2, 2, 2, 65534, 65534, 65534, 65534, 3, 65534, 65534, 65534,
2, 9, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 2, 2, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 5, 65534, 65534, 2,
65534, 65534, 6, 65534, 65534, 65534, 65534, 2, 3,
65534, 65534, 65534, 65534, 13,
65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534,
9, 65534, 65534, 65534, 65534, 79, 9, 65534, 65534, 65534, 65534, 79, 3, 2, 65534, 65534, 65534, 65534, 65534, 65534, 3, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 79, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 65534, 2, 2, 2,
65534, 65534, 65534, 2, 65534, 65534, 2, 65534, 4, 2, 65534, 65534, 2,
2, 65534, 65534, 2, 2, 65534, 65534, 65534, 2, 65534, 8, 65534, 3, 3, 2, 2, 3, 2, 65534, 65534, 65534};

int Parameter__idListVal [TotalNumOfParameters] = { -1, -1, -1, -1, -1, 1, 2, 3, -1, -1, 4, -1, 5, -1, 6, -1, 2, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, 8, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 9, 9, -1, -1, -1, -1, 7, -1, -1,

//AMP 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, 12, -1, -1, 13, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, -1, 14, -1, -1, 15, 16, -1, -1, 17, -1, 2, 2, -1, -1, -1, -1, 2, -1, -1, -1, 18, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, 20, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, 2, -1, -1, -1, 21, -1, -1, -1, -1,
10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, 12, -1, -1, 13, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, -1, 14, -1, -1, 15, 16, -1, -1, 17, -1, 2, 2, -1, -1, -1, -1, 2, -1, -1, -1, 18, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, 20, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, 2, -1, -1, -1, 21, -1, -1, -1, -1,   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,

-1, 22, -1, 22, 2, -1, -1, -1, -1, -1, -1, 7, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
24, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
26, 27, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, 29, 29, -1, 2, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 2, 30, -1, -1, -1, -1, -1, 31, 32, 32, 28, 28, -1, 29, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1,
-1, -1, -1, -1, 28, 28, 28, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, 28, 28, 28, -1, -1, -1, 25, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, 2, -1, -1, 36, -1, 28, 28, -1, -1, -1, -1, 28, -1, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
38, -1, -1, 28, -1, -1, -1, -1, 29, 39, -1, -1, -1, 6, -1, -1, 31, -1, -1, -1, -1, -1, -1,
40, -1, 28, -1, -1, -1, -1, -1, 29, -1, 39, -1, -1, -1, 6, -1, -1, 31, 2, -1, -1, -1, -1,
-1, -1, -1, -1, 28, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1,
41, 42, -1, 29, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, 43, -1, -1,
44, -1, -1, -1, -1, -1, -1, -1, 7, -1, -1, 45, -1,
46, 46, 46, -1, -1, -1, -1, -1, 6, -1, -1, -1,
47, 29, -1, -1, -1, 28, -1, -1, -1, 7, -1, -1, -1, -1, -1,
48, 49, -1, -1, 50, 50, 51, 52, 53, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 54, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, 28, 28, 28, 28, 55, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, -1, 37, -1, -1, -1, 57, 36, 2, -1,
58, -1, -1, -1, -1, -1, 7, 59, -1, -1, -1, 31, -1, -1,
60, -1, -1, -1, -1, 7, -1, -1, -1, -1, 61, -1, -1, -1, -1, -1, -1, 62, -1, -1,
-1, -1, -1, -1, -1, -1, 63, 31, -1, -1, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, 64,
-1, -1,
-1, -1, -1, 7, -1, -1,
65, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1, 65, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, 65, -1, 66, -1, -1, -1, -1, -1, -1, -1, -1,
67, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
-1, -1, -1, -1, 37, -1, 37, -1, 37, -1, -1, -1, -1, -1, 25, -1, -1,
-1, 68, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1,
-1, -1, -1, -1, -1, 69, -1, -1, -1, -1, -1, 7, -1,
-1, -1, 2, -1, -1, -1, -1, 6, -1, -1,
-1, -1, -1, -1, -1, -1, -1, 70, 71, -1, -1, -1, -1, -1, 70, 71, -1, -1, -1, -1, -1, 70, 71, -1, -1, -1, 7, -1,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, 29, 29, 29, -1, -1, -1, -1, -1, 36, 2, 2, -1, -1, -1, -1, 6, -1, -1, -1,
72, 73, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 74, 74, 74, 74, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, 36,
-1, -1, 45, -1, -1, -1, -1, 7, 75,
-1, -1, -1, -1, 76,
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1,
29, -1, -1, -1, -1, 28, 29, -1, -1, -1, -1, 28, 77, 2, -1, -1, -1, -1, -1, -1, 77, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 78, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, 2, 2,
-1, -1, -1, 79, -1, -1, 2, -1, 80, 2, -1, -1, 2,
81, -1, -1, 2, 2, -1, -1, -1, 7, -1, 82, -1, 83, 83, 2, 33, 84, 2, -1, -1, -1};

char Factory__Cabinet__0[] = "1x6 OVAL";
char Factory__Cabinet__1[] = "1x8 TWEED";
char Factory__Cabinet__2[] = "1x10 GOLD";
char Factory__Cabinet__3[] = "1x10 BLUE";
char Factory__Cabinet__4[] = "1x12 TWEED";
char Factory__Cabinet__5[] = "1x12 BLACK";
char Factory__Cabinet__6[] = "1x12 BLUE";
char Factory__Cabinet__7[] = "1x12 E12L (RW)";
char Factory__Cabinet__8[] = "1x12 STUDIO";
char Factory__Cabinet__9[] = "1x12 EMI OPEN BACK (JM)";
char Factory__Cabinet__10[] = "1x12 BOOGAFUNK BLUE (OH)";
char Factory__Cabinet__11[] = "1x12 BOOGAFUNK E12L (OH)";
char Factory__Cabinet__12[] = "1x12 TWEED BLUE (RW)";
char Factory__Cabinet__13[] = "1x12 TWEED DELUXE (RW)";
char Factory__Cabinet__14[] = "1x12 BRIT BLUE (RW)";
char Factory__Cabinet__15[] = "1x12 BRIT G12H30 (RW)";
char Factory__Cabinet__16[] = "1x15 BLUES";
char Factory__Cabinet__17[] = "1x15 THUNDERBOLT (RW)";
char Factory__Cabinet__18[] = "2x12 BLACK";
char Factory__Cabinet__19[] = "2x12 BRIT";
char Factory__Cabinet__20[] = "2x12 DOUBLEVERB D120 (RW)";
char Factory__Cabinet__21[] = "2x12 DOUBLEVERB C12N (RW)";
char Factory__Cabinet__22[] = "2x12 BLUE";
char Factory__Cabinet__23[] = "2x12 TOP BOOST BLUE (RW)";
char Factory__Cabinet__24[] = "2x12 TOP BOOST SILVER (RW)";
char Factory__Cabinet__25[] = "2x12 BOUTIQUE (RW)";
char Factory__Cabinet__26[] = "2x12 JAZZ (RW)";
char Factory__Cabinet__27[] = "2x12 GOLD 30 FAR-FIELD (JM)";
char Factory__Cabinet__28[] = "2x12 G12-65 FAR-FIELD (JM)";
char Factory__Cabinet__29[] = "2x12 BOUTIQUE";
char Factory__Cabinet__30[] = "2x15 DOUBLESHOW (RW)";
char Factory__Cabinet__31[] = "4x10 TWEED BASS";
char Factory__Cabinet__32[] = "4x10 BASSGUY P10 (RW)";
char Factory__Cabinet__33[] = "4x12 BASKETWEAVE G12H30 (RW)";
char Factory__Cabinet__34[] = "4x12 BASKETWEAVE G12L (RW)";
char Factory__Cabinet__35[] = "4x12 BASKETWEAVE G12M20 (RW)";
char Factory__Cabinet__36[] = "4x12 BASKETWEAVE G12M25 (RW)";
char Factory__Cabinet__37[] = "4x12 1960A G12M (RW)";
char Factory__Cabinet__38[] = "4x12 1960B T75 (RW)";
char Factory__Cabinet__39[] = "4x12 1960B K120 (RW)";
char Factory__Cabinet__40[] = "4x12 1960B V30 (RW)";
char Factory__Cabinet__41[] = "4x12 HI-POWER (RW)";
char Factory__Cabinet__42[] = "4x12 RECTO V30 (RW)";
char Factory__Cabinet__43[] = "4x12 RECTO V30 (OH)";
char Factory__Cabinet__44[] = "4x12 SOLO V12 (RW)";
char Factory__Cabinet__45[] = "4x12 SOLO S12X (RW)";
char Factory__Cabinet__46[] = "4x12 GERMAN V30 (RW)";
char Factory__Cabinet__47[] = "4x12 GERMAN BOUTIQUE (RW)";
char Factory__Cabinet__48[] = "4x12 PVH6160 (RW)";
char Factory__Cabinet__49[] = "4x12 UBER T75 (RW)";
char Factory__Cabinet__50[] = "4x12 UBER V30 (RW)";
char Factory__Cabinet__51[] = "4x12 UBER T75+V30 (RW)";
char Factory__Cabinet__52[] = "4x12 CITRUS V30 (RW)";
char Factory__Cabinet__53[] = "4x12 MILLs 12K (OH)";
char Factory__Cabinet__54[] = "4x12 SLM BLUE (OH)";
char Factory__Cabinet__55[] = "4x12 SLM G65 (OH)";
char Factory__Cabinet__56[] = "4x12 SLM H75 (OH)";
char Factory__Cabinet__57[] = "4x12 SLM M75 (OH)";
char Factory__Cabinet__58[] = "4x12 SLM V30 (OH)";
char Factory__Cabinet__59[] = "4x12 20W";
char Factory__Cabinet__60[] = "4x12 25W";
char Factory__Cabinet__61[] = "4x12 V30";
char Factory__Cabinet__62[] = "4x12 GERMAN";
char Factory__Cabinet__63[] = "4x12 30W (ULTRA)";
char Factory__Cabinet__64[] = "4x12 CALI";
char Factory__Cabinet__65[] = "1x15 L.A. BASS";
char Factory__Cabinet__66[] = "4x10 ALUMINUM BASS (RW)";
char Factory__Cabinet__67[] = "8x10 SV BASS (RW)";
char Factory__Cabinet__68[] = "4x12 V30 #1 (KALTHALLEN)";
char Factory__Cabinet__69[] = "4x12 V30 #2 (KALTHALLEN)";
char Factory__Cabinet__70[] = "4x12 V30 #3 (KALTHALLEN)";
char Factory__Cabinet__71[] = "4x12 V30 #4 (KALTHALLEN)";
char Factory__Cabinet__72[] = "4x12 G12T75 #1 (KALTHALLEN)";
char Factory__Cabinet__73[] = "4x12 G12T75 #2 (KALTHALLEN)";
char Factory__Cabinet__74[] = "1x8 CHAMPLIFIER MIX";
char Factory__Cabinet__75[] = "1X8 VIBRATO CHAMPLIFIER MIX";
char Factory__Cabinet__76[] = "1x10 PRINCE TONE BLACK MIX";
char Factory__Cabinet__77[] = "1x10 PRINCE TONE SILVER MIX";
char Factory__Cabinet__78[] = "1X12 JUNIOR BLUES MIX";
char Factory__Cabinet__79[] = "1x12 DELUXE VERB MIX";
char Factory__Cabinet__80[] = "1x12 DELUXE TWEED MIX";
char Factory__Cabinet__81[] = "1x12 VIBRATO LUX MIX";
char Factory__Cabinet__82[] = "1x12 CLASS-A 15W BLUE MIX";
char Factory__Cabinet__83[] = "1x12 DIVISION 13 MIX";
char Factory__Cabinet__84[] = "1x12 HOT KITTY MIX";
char Factory__Cabinet__85[] = "1x12 HAWAII MIX";
char Factory__Cabinet__86[] = "1x15 TWEED PRO MIX";
char Factory__Cabinet__87[] = "1x15 EMPIRE MIX";
char Factory__Cabinet__88[] = "2x10 SUPER TWEED MIX";
char Factory__Cabinet__89[] = "2x10 VIBRATO LUX MIX";
char Factory__Cabinet__90[] = "2x12 DOUBLE VERB MIX";
char Factory__Cabinet__91[] = "2x12 PRO VERB MIX";
char Factory__Cabinet__92[] = "2x12 CLASS-A 30W BLUE MIX";
char Factory__Cabinet__93[] = "2x12 CLASS-A 30W SILVER MIX";
char Factory__Cabinet__94[] = "2x12 SUPREMO MIX";
char Factory__Cabinet__95[] = "2x12 SANTIAGO EJ1250";
char Factory__Cabinet__96[] = "2x12 SANTIAGO ALTEC";
char Factory__Cabinet__97[] = "3x10 VIBRATO KING MIX";
char Factory__Cabinet__98[] = "4x10 BASSGUY MIX";
char Factory__Cabinet__99[] = "4x10 SUPER VERB MIX";
char Factory__Cabinet__100[] = "4x12 BASKETWEAVE GREEN MIX";
char Factory__Cabinet__101[] = "4x12 BASKETWEAVE AX MIX";
char Factory__Cabinet__102[] = "4x12 BASKETWEAVE TV MIX";
char Factory__Cabinet__103[] = "4x12 CALI LEAD 80S MIX";
char Factory__Cabinet__104[] = "4x12 RUMBLE EV12L MIX";
char Factory__Cabinet__105[] = "4x12 RUMBLE EV12S MIX";
char Factory__Cabinet__106[] = "4x12 PVH6160 MIX";
char Factory__Cabinet__107[] = "4x12 PETRUCCI V30 MIX";
char Factory__Cabinet__108[] = "1x15 SV BASS M88";
char Factory__Cabinet__109[] = "1x15 SV BASS SUBKICK";
char Factory__Cabinet__110[] = "4x10 SV BASS M88";
char Factory__Cabinet__111[] = "4x10 SV BASS SUBKICK";
char Factory__Cabinet__112[] = "4x10+TWEETER SV BASS M88";


char *Factory__Cabinets[113] = { Factory__Cabinet__0,
Factory__Cabinet__1,
Factory__Cabinet__2,
Factory__Cabinet__3,
Factory__Cabinet__4,
Factory__Cabinet__5,
Factory__Cabinet__6,
Factory__Cabinet__7,
Factory__Cabinet__8,
Factory__Cabinet__9,
Factory__Cabinet__10,
Factory__Cabinet__11,
Factory__Cabinet__12,
Factory__Cabinet__13,
Factory__Cabinet__14,
Factory__Cabinet__15,
Factory__Cabinet__16,
Factory__Cabinet__17,
Factory__Cabinet__18,
Factory__Cabinet__19,
Factory__Cabinet__20,
Factory__Cabinet__21,
Factory__Cabinet__22,
Factory__Cabinet__23,
Factory__Cabinet__24,
Factory__Cabinet__25,
Factory__Cabinet__26,
Factory__Cabinet__27,
Factory__Cabinet__28,
Factory__Cabinet__29,
Factory__Cabinet__30,
Factory__Cabinet__31,
Factory__Cabinet__32,
Factory__Cabinet__33,
Factory__Cabinet__34,
Factory__Cabinet__35,
Factory__Cabinet__36,
Factory__Cabinet__37,
Factory__Cabinet__38,
Factory__Cabinet__39,
Factory__Cabinet__40,
Factory__Cabinet__41,
Factory__Cabinet__42,
Factory__Cabinet__43,
Factory__Cabinet__44,
Factory__Cabinet__45,
Factory__Cabinet__46,
Factory__Cabinet__47,
Factory__Cabinet__48,
Factory__Cabinet__49,
Factory__Cabinet__50,
Factory__Cabinet__51,
Factory__Cabinet__52,
Factory__Cabinet__53,
Factory__Cabinet__54,
Factory__Cabinet__55,
Factory__Cabinet__56,
Factory__Cabinet__57,
Factory__Cabinet__58,
Factory__Cabinet__59,
Factory__Cabinet__60,
Factory__Cabinet__61,
Factory__Cabinet__62,
Factory__Cabinet__63,
Factory__Cabinet__64,
Factory__Cabinet__65,
Factory__Cabinet__66,
Factory__Cabinet__67,
Factory__Cabinet__68,
Factory__Cabinet__69,
Factory__Cabinet__70,
Factory__Cabinet__71,
Factory__Cabinet__72,
Factory__Cabinet__73,
Factory__Cabinet__74,
Factory__Cabinet__75,
Factory__Cabinet__76,
Factory__Cabinet__77,
Factory__Cabinet__78,
Factory__Cabinet__79,
Factory__Cabinet__80,
Factory__Cabinet__81,
Factory__Cabinet__82,
Factory__Cabinet__83,
Factory__Cabinet__84,
Factory__Cabinet__85,
Factory__Cabinet__86,
Factory__Cabinet__87,
Factory__Cabinet__88,
Factory__Cabinet__89,
Factory__Cabinet__90,
Factory__Cabinet__91,
Factory__Cabinet__92,
Factory__Cabinet__93,
Factory__Cabinet__94,
Factory__Cabinet__95,
Factory__Cabinet__96,
Factory__Cabinet__97,
Factory__Cabinet__98,
Factory__Cabinet__99,
Factory__Cabinet__100,
Factory__Cabinet__101,
Factory__Cabinet__102,
Factory__Cabinet__103,
Factory__Cabinet__104,
Factory__Cabinet__105,
Factory__Cabinet__106,
Factory__Cabinet__107,
Factory__Cabinet__108,
Factory__Cabinet__109,
Factory__Cabinet__110,
Factory__Cabinet__111,
Factory__Cabinet__112};

int Number__User__Cabinet = 100;



enum modifier_paramID
{
        MOD_CTRTLID,                                        // ID of input controller
        MOD_MIN,
        MOD_MAX,
        MOD_STARTPT,
        MOD_MIDPT,
        MOD_ENDPT,
        MOD_SLOPE,
        MOD_DAMPING,
        MOD_EFFECTID,                                        // ID of effect being controlled
        MOD_PARAM,                                                // parameter being controlled
        MOD_AUTOENGAGE,
        MOD_PCRESET,                                        // Reset on program change
        MOD_OFFVAL,                                                // auto-engage off value
        MOD_SCALE,
        MOD__OFFSET, // replace MOD_OFFSET,
        MOD_END
};



// Storage for the AXE-FX CC table
//int AXE_effect_CC_CC[128];
//QStringList AXE_effect_CC_Label;

int AXE_effect_CC_CC[128] = {
    10	,
    11	,
    12	,
    13	,
    14	,
    15	,
    16	,
    17	,
    18	,
    19	,
    20	,
    21	,
    22	,
    23	,
    24	,
    25	,
    26	,
    27	,
    28	,
    29	,
    30	,
    31	,
    32	,
    33	,
    120	,
    121	,
    122	,
    34	,
    123	,
    124	,
    35	,
    36	,
    37	,
    38	,
    39	,
    40	,
    41	,
    42	,
    43	,
    44	,
    45	,
    46	,
    47	,
    48	,
    49	,
    50	,
    51	,
    52	,
    53	,
    54	,
    55	,
    56	,
    57	,
    58	,
    59	,
    60	,
    61	,
    62	,
    63	,
    64	,
    65	,
    66	,
    67	,
    68	,
    69	,
    70	,
    71	,
    72	,
    73	,
    74	,
    75	,
    76	,
    77	,
    78	,
    79	,
    80	,
    81	,
    82	,
    83	,
    84	,
    85	,
    86	,
    87	,
    88	,
    89	,
    99	,
    90	,
    91	,
    92	,
    93	,
    94	,
    95	,
    96	,
    97	,
    98	,
    100	,
    101	,
    102	,
    103	,
    104	,
    105	,
    106	,
    107	,
    108	,
    109	,
    110	,
    111	,
    112	,
    113	,
    114	,
    115	,
    116	,
    117	,
    118	,
    119	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};

QStringList AXE_effect_CC_Label;



#endif
