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

#include "parammapping.h"
#include "ui_parammapping.h"

#include <QMessageBox>

#include "midyax.h"

extern unsigned char EffectBlock__ID[71];
extern int Parameter__minDispValue[AXEFX_NumOf_Parameters_DEFINE];
extern int Parameter__maxDispValue[AXEFX_NumOf_Parameters_DEFINE];
extern int Parameter__unit[AXEFX_NumOf_Parameters_DEFINE];
extern char *Parameter__unitModalValues[8];
extern char *EffectBlock__names[AXEFX_NUMBER_EFFECTS_BLOCK];
extern int AXEFX_Effect_Block_ID_to_Effect_Type_ID[ AXEFX_NUMBER_EFFECTS_BLOCK ];
extern int EffectType__numOfParameters[AXEFX_NUMBER_EFFECT_TYPE-1];
extern char *Parameter__labels[AXEFX_NumOf_Parameters_DEFINE];
extern int Parameter__types[AXEFX_NumOf_Parameters_DEFINE];
extern int EffectBlock__effectTypeID[AXEFX_NUMBER_EFFECTS_BLOCK];


// Learn mode variables
extern bool g_learnMode;
extern int g_learnModeCount;
extern unsigned char g_learnModeChan;
extern unsigned char g_learnModeCC;
extern double g_learn_paramDispValue;
extern unsigned char g_learn_MIDIValue;
extern int g_learn_callingDialog;


ParamMapping::ParamMapping(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamMapping)
{
    ui->setupUi(this);
}

ParamMapping::~ParamMapping()
{
    delete ui;
}

void ParamMapping::init(  struct mappingTable *mappingTableElement )
{
    loadEffectBlocks();
    loadParameters(0);

    m_prevChanNumb = mappingTableElement->chanNumb;
    m_prevCCID = mappingTableElement->CCID;

    // Display the guiding message only if effectBlockID/effectParameterID is set and no ChanNumb is set
    if(   (mappingTableElement->chanNumb == 255
       ||  mappingTableElement->CCID== 255 )
       && ( mappingTableElement->effectBlockID != 255
       || mappingTableElement->effectParameterID != 255 ) )
    {
        ui->lblMessage->setVisible(true);
    }
    else {
        ui->lblMessage->setVisible(false);
    }

    if( mappingTableElement->chanNumb == 255 || mappingTableElement->CCID== 255 )
    {
        ui->spnChanNumb->setValue( 16 );
        ui->spnCCID->setValue( 127 );
    }
    else {
        ui->spnChanNumb->setValue( mappingTableElement->chanNumb );
        ui->spnCCID->setValue( mappingTableElement->CCID );
        int block_position = ui->cboEffectBlock->findText( mappingTableElement->effectBlockLabel );
        ui->cboEffectBlock->setCurrentIndex( block_position );
        loadParameters(block_position);
        int param_position = ui->cboParameter->findText( mappingTableElement->effectParameterLabel );
        ui->cboParameter->setCurrentIndex(param_position);
    }
}


void ParamMapping::loadEffectBlocks()
{
    for(int i = 0; i < AXEFX_NUMBER_EFFECTS_BLOCK; i++)  ui->cboEffectBlock->addItem( EffectBlock__names[i] );
}

void ParamMapping::loadParameters( int effectBlockNum )
{
    m_sizeIndexToParam = 0;
    int pos = 0;
    int posEffectType;

    ui->cboParameter->clear();

    // Calculate the possition in the parameter arrays
    posEffectType = EffectBlock__effectTypeID[ effectBlockNum ] - 2;
    for(int i = 0; i < posEffectType ; i++)
    {
        pos += EffectType__numOfParameters[ i ];
    }

    //Load the parameters in the ComboBox
    for(int i = 0; i < EffectType__numOfParameters[ posEffectType ]; i++)
    {
        // Removes the parameters that have a "" label and create a list to keep tract of the parameters IDs taking into account the holes
        if( strcmp(Parameter__labels[ pos +i ], "") != 0 )
        {
            ui->cboParameter->addItem( Parameter__labels[ pos +i ] );
            m_indexToParam[ m_sizeIndexToParam ].effectParameterID = i;
            m_indexToParam[ m_sizeIndexToParam ].effectParameterType = Parameter__types[pos+i];
            m_indexToParam[ m_sizeIndexToParam ].minDispValue = Parameter__minDispValue[ pos + i ];
            m_indexToParam[ m_sizeIndexToParam ].maxDispValue = Parameter__maxDispValue[ pos + i ];
            strncpy( m_indexToParam[ m_sizeIndexToParam ].unit, Parameter__unitModalValues[ Parameter__unit[ pos + i ] ], 7);
            m_sizeIndexToParam++;
        }
    }
}

void ParamMapping::on_cboEffectBlock_currentIndexChanged(int index)
{
    loadParameters(index);
    on_cboParameter_currentIndexChanged(0);
}

void ParamMapping::on_cboParameter_currentIndexChanged(int index)
{
    ui->lblMinValue->setText( QString::number( m_indexToParam[ index ].minDispValue ) );
    ui->lblMaxValue->setText( QString::number( m_indexToParam[ index ].maxDispValue ) );
    ui->lblUnit->setText( m_indexToParam[ index ].unit );
}

void ParamMapping::on_buttonBox_accepted()
{
    MidyAX *m_pMidyAXDlgInstance = qobject_cast<MidyAX*>(this->parent());
    bool found = false;

    int i;
    // TODO : Check if the mapping item already exists
    for( i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++ )
    {
        if(    ui->spnChanNumb->value() == m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb
            && ui->spnCCID->value() == m_pMidyAXDlgInstance->m_theMappingTable[i].CCID  )
        {
            found = true;
            g_learnMode = false;
            g_learnModeCount = 0;
            g_learnModeChan = 0;
            g_learnModeCC = 255;
            break;
        }
    }
    if( found && ( m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb != m_prevChanNumb ||
                   m_pMidyAXDlgInstance->m_theMappingTable[i].CCID != m_prevCCID ))
    {
        QMessageBox* msgBox 	= new QMessageBox();
        msgBox->setWindowTitle("Cannot add this mapping");
        msgBox->setText("This Channel/CC couple is allready mapped");
        msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->exec();
        return;
    }

    m_selectedChanNumb = ui->spnChanNumb->value();
    m_selectedCCID = ui->spnCCID->value();
    m_selectedBlockID = EffectBlock__ID[ ui->cboEffectBlock->currentIndex() ];
    m_selectedParamID = m_indexToParam[ ui->cboParameter->currentIndex() ].effectParameterID;
    QDialog::accept();
}

//void ParamMapping::get_paramMapping( unsigned char *effectBlockID, unsigned char *effectParamID)
void ParamMapping::get_paramMapping( struct mappingTable *mappingTableElement )
{
    //Update MIDIMapping (BCF2000 or BCR2000) for the current Slider with the new BlockID and ParamID
    if ( mappingTableElement != NULL)
    {
        mappingTableElement->chanNumb = m_selectedChanNumb;
        mappingTableElement->CCID = m_selectedCCID;
        mappingTableElement->effectBlockID = m_selectedBlockID;
        strncpy( mappingTableElement->effectBlockLabel, ui->cboEffectBlock->currentText().toStdString().c_str(), 30 );
        mappingTableElement->effectParameterID = m_selectedParamID;
        strncpy( mappingTableElement->effectParameterLabel,     ui->cboParameter->currentText().toStdString().c_str(),    30   );
        mappingTableElement->effectParameterType = m_indexToParam[ ui->cboParameter->currentIndex() ].effectParameterType;
        mappingTableElement->minDispValue = m_indexToParam[ ui->cboParameter->currentIndex() ].minDispValue;
        mappingTableElement->maxDispValue = m_indexToParam[ ui->cboParameter->currentIndex() ].maxDispValue;
        strncpy( mappingTableElement->unit, m_indexToParam[ ui->cboParameter->currentIndex()].unit, 7 );
    }
}

