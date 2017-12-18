#include "CCmapping.h"
#include "ui_CCmapping.h"

#include <QMessageBox>

#include "midyax.h"

//extern unsigned char EffectBlock__ID[71];
//extern int Parameter__minDispValue[AXEFX_NumOf_Parameters_DEFINE];
//extern int Parameter__maxDispValue[AXEFX_NumOf_Parameters_DEFINE];
//extern int Parameter__unit[AXEFX_NumOf_Parameters_DEFINE];
//extern char *Parameter__unitModalValues[8];
//extern char *EffectBlock__names[AXEFX_NUMBER_EFFECTS_BLOCK];
//extern int AXEFX_Effect_Block_ID_to_Effect_Type_ID[ AXEFX_NUMBER_EFFECTS_BLOCK ];
//extern int EffectType__numOfParameters[AXEFX_NUMBER_EFFECT_TYPE-1];
//extern char *Parameter__labels[AXEFX_NumOf_Parameters_DEFINE];
//extern int Parameter__types[AXEFX_NumOf_Parameters_DEFINE];
//extern int EffectBlock__effectTypeID[AXEFX_NUMBER_EFFECTS_BLOCK];

extern int AXE_effect_CC_CC[128];
extern QStringList  AXE_effect_CC_Label;

// Learn mode variables
extern bool g_learnMode;
extern int g_learnModeCount;
extern unsigned char g_learnModeChan;
extern unsigned char g_learnModeCC;
extern double g_learn_paramDispValue;
extern unsigned char g_learn_MIDIValue;
extern int g_learn_callingDialog;


CCMapping::CCMapping(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCMapping)
{
    ui->setupUi(this);

    localpalette = palette();

    // set black background
    localpalette.setColor(QPalette::Background, Qt::darkGray);
    this->setAutoFillBackground(true);
    this->setPalette(localpalette);
}

CCMapping::~CCMapping()
{
    delete ui;
}

void CCMapping::init(  struct CCpageMappingTable *mappingTableElement )
{
    int CCposition;
    loadCCList();

    // Set the Position to the current selected mapping if any
    if( mappingTableElement->number !=255)   CCposition = ui->cboControlName->findText( mappingTableElement->controlName );
    else CCposition = -1;

    // Update UI accordingly
    ui->cboControlName->setCurrentIndex( CCposition );
    ui->cboCCnumber->setCurrentIndex( CCposition );
}

void CCMapping::loadCCList( void )
{
    ui->cboControlName->addItem(QString::null, -1);
    ui->cboCCnumber->addItem(QString::null, -1);

    for(int i = 0; i < 128; i++)
    {
        if( AXE_effect_CC_CC[i] != 0)
        {
            ui->cboControlName->addItem( AXE_effect_CC_Label[i], i );
            ui->cboCCnumber->addItem( QString::number( AXE_effect_CC_CC[i] ), i );
        }
    }
}

void CCMapping::on_buttonBox_accepted()
{
    if(ui->cboCCnumber->currentIndex() != 0)
    {
        m_selectedControlNumber = ui->cboCCnumber->currentIndex();
        m_selectedControlCC = AXE_effect_CC_CC[ ui->cboControlName->currentIndex() -1 ];
    }
    else {
        m_selectedControlNumber = 255;
        m_selectedControlCC = 255;
    }
    QDialog::accept();
}

//void ParamMappingMOD1::get_ParamMappingMOD1( unsigned char *effectBlockID, unsigned char *effectParamID)
void CCMapping::get_paramMapping( struct CCpageMappingTable *mappingTableElement )
{
    //Update MIDIMapping (BCF2000 or BCR2000) for the current Slider with the new BlockID and ParamID
    if ( mappingTableElement != NULL)
    {
        if( m_selectedControlNumber != -1 && m_selectedControlNumber != 255 )
        {
            mappingTableElement->number = m_selectedControlNumber;
            mappingTableElement->controlName = AXE_effect_CC_Label[m_selectedControlNumber-1];
            mappingTableElement->AXE_CC = m_selectedControlCC;
        }
        else{
            mappingTableElement->number = 255;
            mappingTableElement->controlName = "";
            mappingTableElement->AXE_CC = 255;
        }
    }
}


void CCMapping::on_cboControlName_currentIndexChanged(int index)
{
    ui->cboCCnumber->setCurrentIndex( index );
}
