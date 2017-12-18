#include "parammappingMOD1.h"
#include "ui_parammappingMOD1.h"

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


ParamMappingMOD1::ParamMappingMOD1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamMappingMOD1)
{
    ui->setupUi(this);

    localpalette = palette();

    // set black background
    localpalette.setColor(QPalette::Background, Qt::darkGray);
    this->setAutoFillBackground(true);
    this->setPalette(localpalette);
}

ParamMappingMOD1::~ParamMappingMOD1()
{
    delete ui;
}

void ParamMappingMOD1::init(  struct pageMappingTable *mappingTableElement )
{
    int block_position;
    int param_position;

    loadEffectBlocks();
    loadParameters(0);

    if( mappingTableElement->effectBlockID !=255)   block_position = ui->cboEffectBlock->findText( mappingTableElement->effectBlockLabel );
    else block_position = 0;

    ui->cboEffectBlock->setCurrentIndex( block_position );
    loadParameters(block_position);

    if( mappingTableElement->effectBlockID !=255) param_position = ui->cboParameter->findText( mappingTableElement->effectParameterLabel );
    else param_position = 1;

    ui->cboParameter->setCurrentIndex(param_position);
}


void ParamMappingMOD1::loadEffectBlocks()
{
    for(int i = 0; i < AXEFX_NUMBER_EFFECTS_BLOCK; i++)  ui->cboEffectBlock->addItem( EffectBlock__names[i] );
}

void ParamMappingMOD1::loadParameters( int effectBlockNum )
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

void ParamMappingMOD1::on_cboEffectBlock_currentIndexChanged(int index)
{
    loadParameters(index);
    on_cboParameter_currentIndexChanged(0);
}

void ParamMappingMOD1::on_cboParameter_currentIndexChanged(int index)
{
    ui->lblMinValue->setText( QString::number( m_indexToParam[ index ].minDispValue ) );
    ui->lblMaxValue->setText( QString::number( m_indexToParam[ index ].maxDispValue ) );
    ui->lblUnit->setText( m_indexToParam[ index ].unit );
}

void ParamMappingMOD1::on_buttonBox_accepted()
{
    m_selectedBlockID = EffectBlock__ID[ ui->cboEffectBlock->currentIndex() ];
    m_selectedParamID = m_indexToParam[ ui->cboParameter->currentIndex() ].effectParameterID;
    QDialog::accept();
}

//void ParamMappingMOD1::get_ParamMappingMOD1( unsigned char *effectBlockID, unsigned char *effectParamID)
void ParamMappingMOD1::get_paramMapping( struct pageMappingTable *mappingTableElement )
{
    //Update MIDIMapping (BCF2000 or BCR2000) for the current Slider with the new BlockID and ParamID
    if ( mappingTableElement != NULL)
    {
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

