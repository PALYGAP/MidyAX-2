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

#ifndef AXEFX_H_
#define AXEFX_H_


#define AXEFX_NUMBER_EFFECTS_BLOCK 71
#define AXEFX_NUMBER_EFFECT_TYPE 39  // Effect type 1 is not assigned

struct AXEFX_EffectBlock {
    unsigned char ID;
    char name[32]; // The max is "Feedback Return" = 15 characters
    unsigned char effectTypeID;
    unsigned char ONByPass_CC;
    unsigned char XY_CC;
};


struct AXEFX_Parameter {
    unsigned char ID;
    char name[32]; // char *name;
    char label[32]; //char *label;
    unsigned char modifierID; // ID du modifiers qui peut piloter ce paramètres    0 = No modifier
    //bool sticky; //???
    unsigned char displayType; // knob, slider, toggle, ...
    unsigned char type; // LIN, LOG, ...
    unsigned int defaultValue; // Default internal value  -- Not really needed since it could be reloaded from the AXE-FX if the effect type changes
    int minDispValue;
    unsigned int maxDispValue;
    unsigned char precision; //Précision interne ???
    unsigned char unit; // dB, pF, Hz, ...
    unsigned int numVals; // Si <300 contient le nombre de modalitées possibles, sinon c'est le MAX de la valeur interne MIDI.
    int idListVal; //identifiant de la liste de valeurs.
    quint32 paramType, paramLowLimit, paramHighLimit, paramMultiplier, paramResolution;
};

struct AXEFX_EffectType {
    unsigned char ID; //the ID is also the index in the table of effectTypes
    char name[32]; //char *name;
    char subTypeParamID; // -1 if no sub-type parameter for that EFFECT TYPE
    unsigned char onBypassParamID; // -1 if no ONBYpass parameter for that EFFECT TYPE
    unsigned char numOfParameters;  // Number of parameters for that effect
    //struct AXEFX_Parameter (*TheParameters)[];
    struct AXEFX_Parameter TheParameters[100];
};

// CREATE the AXE_effect Block structure
struct AXE_effect {
  unsigned char  effect_id_hex;
  unsigned char  effect_onbypass_cc;
  unsigned char  effect_xy_cc;
};


  ///////////////
  // CONSTANTS //
  ///////////////

  #define AXEFX_NumberOf_EffectTypes_DEFINE    38
  #define AXEFX_NumberOf_EffectBlocks_DEFINE   71
  #define AXEFX_MAX_NumberOf_ParamPerBlock_DEFINE  120
  #define AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE 10
  #define AXEFX_NumOf_Parameters_DEFINE        1100
  #define AXEFX_NumOf_ModalLists_DEFINE        84
  #define AXEFX_INT_Parameter_Type_DEFINE      1
  #define AXEFX_INTXL_Parameter_Type_DEFINE    2
  #define AXEFX_LIN_Parameter_Type_DEFINE      3
  #define AXEFX_LOG_Parameter_Type_DEFINE      4

  // Target of the current MidyAX software
//  PROGMEM byte AXEFX_Firmware_Version_ToUse = 11,
//               AXEFX_Model_ToUse = 3,
//               MFC101_Firmware_Version_ToUse = 2;

//  PROGMEM byte AXEFX_NumOf_SCENES = 8,
//               AXEFX_MaxNumerOf_Instance_per_EffectBlock = 4,
//               AXEFX_NumberOf_EffectBlock_per_EffectType = 4;
//  PROGMEM byte AXEFX_Manuf_ID[3] = {0x00, 0x01, 0x74 };


  // List of the FAS models
  enum FAS_Model {
    FAS_Model_Standard,
    FAS_Model_ULTRA,
    FAS_Model_MFC101,
    FAS_Model_II,
  };




    // AXE-FX SYSEX FUNCTION CODES
      #define AXEFX_SYSEX_WHO_AM_I 0x00
      #define AXEFX_SYSEX_PARAM_DUMP 0x01
      #define AXEFX_SYSEX_PARAM_SET 0x02
      #define AXEFX_SYSEX_PARAM_SET_Q 0xFD  // Value not possible in the AXE-FX SYSEX
      #define AXEFX_SYSEX_PARAM_SET_S 0xFE  // Value not possible in the AXE-FX SYSEX
      #define AXEFX_SYSEX_PARAM_SET_D 0xFF  // Value not possible in the AXE-FX SYSEX
      #define AXEFX_SYSEX_PATCH_DUMP 0x03
      #define AXEFX_SYSEX_PATCH_RCV 0x04
      #define AXEFX_SYSEX_PLACE_EFFECT 0x05
      #define AXEFX_SYSEX_CONNECT_EFFECT 0x06
      #define AXEFX_SYSEX_MODIFIER_SET 0x07
      #define AXEFX_SYSEX_QUERY_VERSION 0x08
      #define AXEFX_SYSEX_SET_NAME 0x09
      #define AXEFX_SYSEX_CABIR_RCV 0x0A
      #define AXEFX_SYSEX_CHECKSUM 0x0B
      #define AXEFX_SYSEX_SET_GRID 0x0C
      #define AXEFX_SYSEX_TUNER 0x0D
      #define AXEFX_SYSEX_QUERY_STATES 0x0E
      #define AXEFX_SYSEX_QUERY_NAME 0x0F
      #define AXEFX_SYSEX_TEMPO 0x10
      #define AXEFX_SYSEX_XY 0x11
      #define AXEFX_SYSEX_CABNAME 0x12
      #define AXEFX_SYSEX_CPULOAD 0x13
      #define AXEFX_SYSEX_PATCHNUM 0x14
      #define AXEFX_SYSEX_QUERY_NAME_BY_NUM 0x15
      #define AXEFX_SYSEX_GET_PARAM_INFO 0x16
      #define AXEFX_SYSEX_GET_MIDI_CHANNEL 0x17
      #define AXEFX_SYSEX_GET_MODIFIER_INFO 0x18
      #define AXEFX_SYSEX_CAB_DUMP 0x19
      #define AXEFX_SYSEX_GLOBAL_BLOCK_USED 0x1A
      #define AXEFX_SYSEX_GLOBAL_PATCH 0x1B
      #define AXEFX_SYSEX_BANK_DUMP 0x1C
      #define AXEFX_SYSEX_SAVE_PATCH 0x1D
      #define AXEFX_SYSEX_SET_BYPASS 0x1E
      #define AXEFX_SYSEX_GET_ALL_PARAMS 0x1F
      #define AXEFX_SYSEX_GET_GRID 0x20
      #define AXEFX_SYSEX_RESYNC 0x21
      #define AXEFX_SYSEX_SET_DEFAULTS 0x22
      #define AXEFX_SYSEX_LOOPER_STATE 0x23
      #define AXEFX_SYSEX_MOVE_EFFECT 0x24
      #define AXEFX_SYSEX_FW_UPDATE 0x25
      #define AXEFX_SYSEX_FPGA_UPDATE 0x26
      #define AXEFX_SYSEX_MICRO_UPDATE 0x27
      #define AXEFX_SYSEX_GET_PARAM_STRINGS 0x28
      #define AXEFX_SYSEX_SET_SCENE 0x29
      #define AXEFX_SYSEX_GET_FLAGS 0x2A
      #define AXEFX_SYSEX_MODIFIER_DUMP 0x2B
      #define AXEFX_SYSEX_MODIFIER 0x2C
      #define AXEFX_SYSEX_SET_CAB_NAME 0x2D
      #define AXEFX_SYSEX_SET_PARAM_DIRECT 0x2E
      #define AXEFX_SYSEX_BPM 0x2F
      #define AXEFX_SYSEX_GET_GRAPH 0x30
      #define AXEFX_SYSEX_TM_DATA 0x31
      #define AXEFX_SYSEX_MULTIMSG_START 0x32
      #define AXEFX_SYSEX_MULTIMSG_END 0x33
      #define AXEFX_SYSEX_ERASE_SECTOR 0x34
      #define AXEFX_SYSEX_GET_CONFIG 0x35
      #define AXEFX_SYSEX_GET_GRAPHN 0x36
      #define AXEFX_SYSEX_EDIT_EFFECT 0x37
      #define AXEFX_SYSEX_BROADCAST_KNOB 0x38
      #define AXEFX_SYSEX_BROADCAST_MODIFIER 0x39
      #define AXEFX_SYSEX_GET_POSITION 0x3A
      #define AXEFX_SYSEX_SET_MODPARAM_DIRECT 0x3B
      #define AXEFX_SYSEX_RECALL_PATCH 0x3C
      #define AXEFX_SYSEX_FAILSAFE_FW_UPDATE 0x3D
      #define AXEFX_SYSEX_MUTE 0x3E
      #define AXEFX_SYSEX_SET_IRCAP_NAME 0x3F
      #define AXEFX_SYSEX_CONTROL_IRCAP 0x40
      #define AXEFX_SYSEX_DELETE_CABIR 0x41
      #define AXEFX_SYSEX_EDITOR_DISCONNECT 0x42
      #define AXEFX_SYSEX_DUMP_SYSTEM 0x43
      #define AXEFX_SYSEX_CAB_BANK_DUMP 0x44

      #define AXEFX_SYSEX_ACT_RESYNC 0x47

      #define AXEFX_SYSEX_STATUS_MSG 0x64
      #define AXEFX_SYSEX_RAWIR_START 0x67
      #define AXEFX_SYSEX_RAWIR_DATA 0x68
      #define AXEFX_SYSEX_RAWIR_END 0x69
      #define AXEFX_SYSEX_FPGA_UPDATE_START 0x6A
      #define AXEFX_SYSEX_FPGA_UPDATE_DATA 0x6B
      #define AXEFX_SYSEX_FPGA_UPDATE_END 0x6C
      #define AXEFX_SYSEX_MICRO_UPDATE_START 0x6D
      #define AXEFX_SYSEX_MICRO_UPDATE_DATA 0x6E
      #define AXEFX_SYSEX_MICRO_UPDATE_END 0x6F
      #define AXEFX_SYSEX_EFFECT_START 0x74
      #define AXEFX_SYSEX_EFFECT_DATA 0x75
      #define AXEFX_SYSEX_EFFECT_END 0x76
      #define AXEFX_SYSEX_PATCH_START 0x77
      #define AXEFX_SYSEX_PATCH_DATA 0x78
      #define AXEFX_SYSEX_PATCH_END 0x79
      #define AXEFX_SYSEX_CABIR_START 0x7A
      #define AXEFX_SYSEX_CABIR_DATA 0x7B
      #define AXEFX_SYSEX_CABIR_END 0x7C
      #define AXEFX_SYSEX_FW_UPDATE_START 0x7D
      #define AXEFX_SYSEX_FW_UPDATE_DATA 0x7E
      #define AXEFX_SYSEX_FW_UPDATE_END 0x7F

#endif // AXEFX_H
