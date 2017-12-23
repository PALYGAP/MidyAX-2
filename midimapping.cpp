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

#include "midimapping.h"
#include "ui_midimapping.h"
#include "axefx.h"
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

MidiMapping::MidiMapping(QWidget *parent) :  QDialog(parent)
{
    ui.setupUi(this);

    m_pMidyAXDlgInstance = qobject_cast<MidyAX*>(this->parent());
}

MidiMapping::~MidiMapping()
{
}

void MidiMapping::init()
{
    ui.tableMidiMapping->setColumnHidden(3,true);
    ui.tableMidiMapping->setColumnHidden(5,true);
    ui.tableMidiMapping->setColumnHidden(6,true);
    ui.tableMidiMapping->setColumnHidden(7,true);
    ui.tableMidiMapping->setColumnHidden(8,true);
    ui.tableMidiMapping->setColumnHidden(9,true);

    loadEffectBlocks();
    loadParameters(0);

    // Clear the QTableWidget
    ui.tableMidiMapping->setRowCount(0);

    for(int i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++)
    {
        ui.tableMidiMapping->insertRow( ui.tableMidiMapping->rowCount());
        createRow( i );
        ui.tableMidiMapping->item(i,0)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb ));
        ui.tableMidiMapping->item(i,1)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].CCID ));
        ui.tableMidiMapping->item(i,2)->setText( m_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockLabel );
        ui.tableMidiMapping->item(i,3)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockID ));
        ui.tableMidiMapping->item(i,4)->setText( m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterLabel );
        ui.tableMidiMapping->item(i,5)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterID ));
        ui.tableMidiMapping->item(i,6)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterType ));
        ui.tableMidiMapping->item(i,7)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].minDispValue ));
        ui.tableMidiMapping->item(i,8)->setText( QString::number( m_pMidyAXDlgInstance->m_theMappingTable[i].maxDispValue ));
        ui.tableMidiMapping->item(i,9)->setText( m_pMidyAXDlgInstance->m_theMappingTable[i].unit );
    }

    // TODO : check that a row is selected in tableMidiMapping
    ui.psbDel->setEnabled(true);
}

void MidiMapping::loadEffectBlocks()
{
    for(int i = 0; i < AXEFX_NUMBER_EFFECTS_BLOCK; i++)  ui.cboEffectBlock->addItem( EffectBlock__names[i] );
}

void MidiMapping::loadParameters( int effectBlockNum )
{
    m_sizeIndexToParam = 0;
    int pos = 0;
    int posEffectType;

    ui.cboParameter->clear();

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
            ui.cboParameter->addItem( Parameter__labels[ pos +i ] );
            m_indexToParam[ m_sizeIndexToParam ].effectParameterID = i;
            m_indexToParam[ m_sizeIndexToParam ].effectParameterType = Parameter__types[pos+i];
            m_indexToParam[ m_sizeIndexToParam ].minDispValue = Parameter__minDispValue[ pos + i ];
            m_indexToParam[ m_sizeIndexToParam ].maxDispValue = Parameter__maxDispValue[ pos + i ];
            strncpy( m_indexToParam[ m_sizeIndexToParam ].unit, Parameter__unitModalValues[ Parameter__unit[ pos + i ] ], 7);
            m_sizeIndexToParam++;
        }
    }
}


void MidiMapping::on_cboParameter_currentIndexChanged(int index)
{
    ui.lblMinValue->setText( QString::number( m_indexToParam[ index ].minDispValue ) );
    ui.lblMaxValue->setText( QString::number( m_indexToParam[ index ].maxDispValue ) );
    ui.lblUnit->setText( m_indexToParam[ index ].unit );
}

void MidiMapping::on_cboEffectBlock_currentIndexChanged(int index)
{
    loadParameters(index);
    on_cboParameter_currentIndexChanged(0);
}

void MidiMapping::createRow( int index)
{
    for(int j = 0; j < 10 ; j++)
    {
        ui.tableMidiMapping->setItem(index, j, new QTableWidgetItem(QString::number( j )));
    }
}


void MidiMapping::on_psbAdd_clicked()
{
    int currentPos;
    bool found = false, ok;
    // TODO : Check if the mapping item already exists
//    for(int i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++)
//    {
//        if(    ui.spnChanNumb->value() == m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb
//            && ui.spnCCID->value() == m_pMidyAXDlgInstance->m_theMappingTable[i].CCID  )
//        {
//            found = true;
//            break;
//        }
//    }
    for(int i = 0; i < ui.tableMidiMapping->rowCount() ; i++)
    {
        if(    ui.spnChanNumb->value() == ui.tableMidiMapping->item(i,0)->text().toInt(&ok, 10)
            && ui.spnCCID->value() == ui.tableMidiMapping->item(i,1)->text().toInt(&ok, 10)  )
        {
            found = true;
            break;
        }
    }

  if( found )
    {
        QMessageBox* msgBox 	= new QMessageBox();
        msgBox->setWindowTitle("Cannot add this mapping");
        msgBox->setText("This Channel/CC couple is allready mapped");
        msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->exec();
        return;
    }

    // Add the mapping item to the QTableWidget
    if( ui.tableMidiMapping->rowCount() == 0 )
    {
        ui.tableMidiMapping->insertRow( 0 );
        ui.tableMidiMapping->setCurrentCell(0,0);
        currentPos = 0;
    }
    else {
        if( ui.tableMidiMapping->currentRow() < 0 )
        {
            currentPos = 0;
        }
        else  currentPos = ui.tableMidiMapping->currentRow();
        ui.tableMidiMapping->insertRow( currentPos );
        ui.tableMidiMapping->setCurrentCell( currentPos, 0 );
    }
    createRow( currentPos );
    ui.tableMidiMapping->item(currentPos, 0)->setText( QString::number( ui.spnChanNumb->value() ));
    ui.tableMidiMapping->item(currentPos, 1)->setText( QString::number(ui.spnCCID->value() ));
    ui.tableMidiMapping->item(currentPos, 2)->setText( ui.cboEffectBlock->currentText() );
    ui.tableMidiMapping->item(currentPos, 3)->setText( QString::number( EffectBlock__ID[ui.cboEffectBlock->currentIndex()] ));
    ui.tableMidiMapping->item(currentPos, 4)->setText( ui.cboParameter->currentText() );
    ui.tableMidiMapping->item(currentPos, 5)->setText( QString::number( m_indexToParam[ ui.cboParameter->currentIndex() ].effectParameterID ));
    ui.tableMidiMapping->item(currentPos, 6)->setText( QString::number( m_indexToParam[ ui.cboParameter->currentIndex() ].effectParameterType ));
    ui.tableMidiMapping->item(currentPos, 7)->setText( QString::number( m_indexToParam[ ui.cboParameter->currentIndex() ].minDispValue ));
    ui.tableMidiMapping->item(currentPos, 8)->setText( QString::number( m_indexToParam[ ui.cboParameter->currentIndex() ].maxDispValue ));
    ui.tableMidiMapping->item(currentPos, 9)->setText( m_indexToParam[ ui.cboParameter->currentIndex() ].unit );

    // Update the m_pMidyAXDlgInstance->m_theMappingTable like on dialog exit
    // on_buttonBox_accepted();
}

void MidiMapping::on_psbDel_clicked()
{
    if( ui.tableMidiMapping->currentRow() > -1) ui.tableMidiMapping->removeRow(ui.tableMidiMapping->currentRow());
    //on_buttonBox_accepted();
}

void MidiMapping::on_buttonBox_accepted()
{
    bool ok;

    // Fill the mapping table with the content of the QTableWidget
    for(int i = 0; i < ui.tableMidiMapping->rowCount() ; i++)
    {
        m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb = ui.tableMidiMapping->item(i,0)->text().toInt(&ok, 10);
        m_pMidyAXDlgInstance->m_theMappingTable[i].CCID = ui.tableMidiMapping->item(i,1)->text().toInt(&ok, 10);
        strncpy( m_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockLabel, ui.tableMidiMapping->item(i,2)->text().toStdString().c_str(), 30 );
        m_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockID = ui.tableMidiMapping->item(i,3)->text().toInt(&ok, 10);
        strncpy( m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterLabel, ui.tableMidiMapping->item(i,4)->text().toStdString().c_str(), 30 );
        m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterID = ui.tableMidiMapping->item(i,5)->text().toInt(&ok, 10);
        m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterType = ui.tableMidiMapping->item(i,6)->text().toInt(&ok, 10);
        m_pMidyAXDlgInstance->m_theMappingTable[i].minDispValue = ui.tableMidiMapping->item(i,7)->text().toInt(&ok, 10);
        m_pMidyAXDlgInstance->m_theMappingTable[i].maxDispValue = ui.tableMidiMapping->item(i,8)->text().toInt(&ok, 10);
        strncpy( m_pMidyAXDlgInstance->m_theMappingTable[i].unit, ui.tableMidiMapping->item(i,9)->text().toStdString().c_str(), 7 );
    }
    m_pMidyAXDlgInstance->m_numbOfMappings = ui.tableMidiMapping->rowCount();

    emit accept();
}


void MidiMapping::on_tableMidiMapping_doubleClicked(const QModelIndex &index)
{
    int row;
    QString cellText;

    if (index.isValid())
    {
        cellText = index.data().toString();
        row = index.row();

        // Get the value of the doubleCLicked Row
        bool ok;
        int chanNumb = ui.tableMidiMapping->item(row,0)->text().toInt(&ok, 10);
        int CCID = ui.tableMidiMapping->item(row,1)->text().toInt(&ok, 10);
        char effectBlockLabel[30];
        strncpy(effectBlockLabel, ui.tableMidiMapping->item(row,2)->text().toStdString().c_str(), 30);
        char effectParameterLabel[30];
        strncpy(effectParameterLabel, ui.tableMidiMapping->item(row,4)->text().toStdString().c_str(), 30);

        // Set the value QComboBox  and QSpinBox
        ui.spnChanNumb->setValue( chanNumb );
        ui.spnCCID->setValue( CCID );
        int block_position = ui.cboEffectBlock->findText(effectBlockLabel);
        ui.cboEffectBlock->setCurrentIndex(block_position);
        loadParameters(block_position);
        int param_position = ui.cboParameter->findText(effectParameterLabel);
        ui.cboParameter->setCurrentIndex(param_position);
    }

    // TODO: Change ADD button label and go into EDIT MODE
}



void MidiMapping::on_psbUP_clicked()
{
    struct mappingTable tempo;
    int currentPos;
    bool ok;

    if(    ui.tableMidiMapping->rowCount() < 2
        || ui.tableMidiMapping->currentRow() < 1 )
    {
        return;
    }
    else {
        currentPos = ui.tableMidiMapping->currentRow();

        tempo.chanNumb = ui.tableMidiMapping->item(currentPos,0)->text().toInt(&ok, 10);
        tempo.CCID = ui.tableMidiMapping->item(currentPos,1)->text().toInt(&ok, 10);
        strncpy( tempo.effectBlockLabel, ui.tableMidiMapping->item(currentPos,2)->text().toStdString().c_str(), 30 );
        tempo.effectBlockID = ui.tableMidiMapping->item(currentPos,3)->text().toInt(&ok, 10);
        strncpy( tempo.effectParameterLabel, ui.tableMidiMapping->item(currentPos,4)->text().toStdString().c_str(), 30 );
        tempo.effectParameterID = ui.tableMidiMapping->item(currentPos,5)->text().toInt(&ok, 10);
        tempo.effectParameterType = ui.tableMidiMapping->item(currentPos,6)->text().toInt(&ok, 10);
        tempo.minDispValue = ui.tableMidiMapping->item(currentPos,7)->text().toInt(&ok, 10);
        tempo.maxDispValue = ui.tableMidiMapping->item(currentPos,8)->text().toInt(&ok, 10);
        strncpy( tempo.unit, ui.tableMidiMapping->item(currentPos,9)->text().toStdString().c_str(), 7 );

        ui.tableMidiMapping->setCurrentCell( currentPos, 0 );
        ui.tableMidiMapping->item(currentPos, 0)->setText( ui.tableMidiMapping->item(currentPos-1,0)->text() );
        ui.tableMidiMapping->item(currentPos, 1)->setText( ui.tableMidiMapping->item(currentPos-1,1)->text() );
        ui.tableMidiMapping->item(currentPos, 2)->setText( ui.tableMidiMapping->item(currentPos-1,2)->text() );
        ui.tableMidiMapping->item(currentPos, 3)->setText( ui.tableMidiMapping->item(currentPos-1,3)->text() );
        ui.tableMidiMapping->item(currentPos, 4)->setText( ui.tableMidiMapping->item(currentPos-1,4)->text() );
        ui.tableMidiMapping->item(currentPos, 5)->setText( ui.tableMidiMapping->item(currentPos-1,5)->text() );
        ui.tableMidiMapping->item(currentPos, 6)->setText( ui.tableMidiMapping->item(currentPos-1,6)->text() );
        ui.tableMidiMapping->item(currentPos, 7)->setText( ui.tableMidiMapping->item(currentPos-1,7)->text() );
        ui.tableMidiMapping->item(currentPos, 8)->setText( ui.tableMidiMapping->item(currentPos-1,8)->text() );
        ui.tableMidiMapping->item(currentPos, 9)->setText( ui.tableMidiMapping->item(currentPos-1,9)->text() );

        ui.tableMidiMapping->item(currentPos-1,0)->setText( QString::number( tempo.chanNumb ));
        ui.tableMidiMapping->item(currentPos-1,1)->setText( QString::number( tempo.CCID ));
        ui.tableMidiMapping->item(currentPos-1,2)->setText( tempo.effectBlockLabel );
        ui.tableMidiMapping->item(currentPos-1,3)->setText( QString::number( tempo.effectBlockID ));
        ui.tableMidiMapping->item(currentPos-1,4)->setText( tempo.effectParameterLabel );
        ui.tableMidiMapping->item(currentPos-1,5)->setText( QString::number( tempo.effectParameterID ));
        ui.tableMidiMapping->item(currentPos-1,6)->setText( QString::number( tempo.effectParameterType ));
        ui.tableMidiMapping->item(currentPos-1,7)->setText( QString::number( tempo.minDispValue ));
        ui.tableMidiMapping->item(currentPos-1,8)->setText( QString::number( tempo.maxDispValue ));
        ui.tableMidiMapping->item(currentPos-1,9)->setText( tempo.unit );

        ui.tableMidiMapping->setCurrentCell( currentPos-1, 0 );
    }
}

void MidiMapping::on_psbDOWN_clicked()
{
    struct mappingTable tempo;
    int currentPos;
    bool ok;

    if(    ui.tableMidiMapping->rowCount() < 2
        || ui.tableMidiMapping->currentRow() < 0
        || ui.tableMidiMapping->currentRow() > ui.tableMidiMapping->rowCount() -2 )
    {
        return;
    }
    else {
        currentPos = ui.tableMidiMapping->currentRow()+1;

        tempo.chanNumb = ui.tableMidiMapping->item(currentPos,0)->text().toInt(&ok, 10);
        tempo.CCID = ui.tableMidiMapping->item(currentPos,1)->text().toInt(&ok, 10);
        strncpy( tempo.effectBlockLabel, ui.tableMidiMapping->item(currentPos,2)->text().toStdString().c_str(), 30 );
        tempo.effectBlockID = ui.tableMidiMapping->item(currentPos,3)->text().toInt(&ok, 10);
        strncpy( tempo.effectParameterLabel, ui.tableMidiMapping->item(currentPos,4)->text().toStdString().c_str(), 30 );
        tempo.effectParameterID = ui.tableMidiMapping->item(currentPos,5)->text().toInt(&ok, 10);
        tempo.effectParameterType = ui.tableMidiMapping->item(currentPos,6)->text().toInt(&ok, 10);
        tempo.minDispValue = ui.tableMidiMapping->item(currentPos,7)->text().toInt(&ok, 10);
        tempo.maxDispValue = ui.tableMidiMapping->item(currentPos,8)->text().toInt(&ok, 10);
        strncpy( tempo.unit, ui.tableMidiMapping->item(currentPos,9)->text().toStdString().c_str(), 7 );

        ui.tableMidiMapping->setCurrentCell( currentPos, 0 );
        ui.tableMidiMapping->item(currentPos, 0)->setText( ui.tableMidiMapping->item(currentPos-1,0)->text() );
        ui.tableMidiMapping->item(currentPos, 1)->setText( ui.tableMidiMapping->item(currentPos-1,1)->text() );
        ui.tableMidiMapping->item(currentPos, 2)->setText( ui.tableMidiMapping->item(currentPos-1,2)->text() );
        ui.tableMidiMapping->item(currentPos, 3)->setText( ui.tableMidiMapping->item(currentPos-1,3)->text() );
        ui.tableMidiMapping->item(currentPos, 4)->setText( ui.tableMidiMapping->item(currentPos-1,4)->text() );
        ui.tableMidiMapping->item(currentPos, 5)->setText( ui.tableMidiMapping->item(currentPos-1,5)->text() );
        ui.tableMidiMapping->item(currentPos, 6)->setText( ui.tableMidiMapping->item(currentPos-1,6)->text() );
        ui.tableMidiMapping->item(currentPos, 7)->setText( ui.tableMidiMapping->item(currentPos-1,7)->text() );
        ui.tableMidiMapping->item(currentPos, 8)->setText( ui.tableMidiMapping->item(currentPos-1,8)->text() );
        ui.tableMidiMapping->item(currentPos, 9)->setText( ui.tableMidiMapping->item(currentPos-1,9)->text() );

        ui.tableMidiMapping->item(currentPos-1,0)->setText( QString::number( tempo.chanNumb ));
        ui.tableMidiMapping->item(currentPos-1,1)->setText( QString::number( tempo.CCID ));
        ui.tableMidiMapping->item(currentPos-1,2)->setText( tempo.effectBlockLabel );
        ui.tableMidiMapping->item(currentPos-1,3)->setText( QString::number( tempo.effectBlockID ));
        ui.tableMidiMapping->item(currentPos-1,4)->setText( tempo.effectParameterLabel );
        ui.tableMidiMapping->item(currentPos-1,5)->setText( QString::number( tempo.effectParameterID ));
        ui.tableMidiMapping->item(currentPos-1,6)->setText( QString::number( tempo.effectParameterType ));
        ui.tableMidiMapping->item(currentPos-1,7)->setText( QString::number( tempo.minDispValue ));
        ui.tableMidiMapping->item(currentPos-1,8)->setText( QString::number( tempo.maxDispValue ));
        ui.tableMidiMapping->item(currentPos-1,9)->setText( tempo.unit );
    }
}

void MidiMapping::on_MidiMapping_accepted()
{

}
