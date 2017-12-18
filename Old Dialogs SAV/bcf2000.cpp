#include "bcf2000.h"
#include "axefx.h"
#include "midyax.h"
#include "constants.h"

extern void delay( int millisecondsToWait );

extern quint8 CCtoAXE[16][128][3];
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

// Learn mode variables
extern bool g_learnMode;
extern int g_learnModeCount;
extern int g_learnModeChan;
extern unsigned char g_learnModeCC;
extern double g_learn_paramDispValue;
extern unsigned char g_learn_MIDIValue;
extern int g_learn_callingDialog;
extern bool g_sliderColored;
extern bool g_displayBlownUp;
extern bool g_autoConnect;


BCF2000::BCF2000(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BCF2000),
    m_setup(false),
    m_initMode(false)
{
    ui->setupUi(this);
    m_pInstance = qobject_cast<MidyAX*>(this->parent());

    m_slidderPalette.setColor(QPalette::Window, QColor(255, 255, 255));

    QComboBox* l_TheComboBoxs[ NUMofSLIDDERS ] = { ui->comboBox_1, ui->comboBox_2, ui->comboBox_3, ui->comboBox_4, ui->comboBox_5, ui->comboBox_6, ui->comboBox_7, ui->comboBox_8};
    QLineEditMod1 *l_TheLineEdits[NUMofSLIDDERS] = { ui->lineEdit_1, ui->lineEdit_2, ui->lineEdit_3, ui->lineEdit_4, ui->lineEdit_5, ui->lineEdit_6, ui->lineEdit_7, ui->lineEdit_8};
    QSliderMod1 *l_TheSliders[ NUMofSLIDDERS ] = { ui->verticalSlider_1, ui->verticalSlider_2, ui->verticalSlider_3, ui->verticalSlider_4, ui->verticalSlider_5, ui->verticalSlider_6, ui->verticalSlider_7, ui->verticalSlider_8 };
    QLabel *l_TheBlockLabels[ NUMofSLIDDERS ] = { ui->label_1, ui->label_2, ui->label_3, ui->label_4, ui->label_5, ui->label_6, ui->label_7, ui->label_8};
    QLabel *l_TheParamLabels[ NUMofSLIDDERS ] = { ui->label_9, ui->label_10, ui->label_11, ui->label_12, ui->label_13, ui->label_14, ui->label_15, ui->label_16 };
    QLabel *l_TheMaxLabels[ NUMofSLIDDERS ] = { ui->label_17, ui->label_18, ui->label_19, ui->label_20, ui->label_21, ui->label_22, ui->label_23, ui->label_24 };
    QLabel *l_TheMinLabels[ NUMofSLIDDERS ] = { ui->label_25, ui->label_26, ui->label_27, ui->label_28, ui->label_29, ui->label_30, ui->label_31, ui->label_32 };

    // Initialize the Member ARRAYS with the ordered UI Widgets
    for(int i=0; i < NUMofSLIDDERS ; i++)
    {
        m_TheComboBoxs << l_TheComboBoxs[ i ];
        m_TheLineEdits << l_TheLineEdits[ i ];
        m_TheSliders << l_TheSliders[ i ];
        m_TheBlockLabels << l_TheBlockLabels[ i ];
        m_TheParamLabels << l_TheParamLabels[ i ];
        m_TheMaxLabels << l_TheMaxLabels[ i ];
        m_TheMinLabels << l_TheMinLabels[ i ];
    }

    // SIGNAL/SLOT connections
    for(int i=0; i < NUMofSLIDDERS ; i++)
    {
        m_setup = true;
        connect(m_TheLineEdits[i], SIGNAL(editingFinished(void)), this, SLOT(onLineEditEditingFinished(void)) );
        connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        connect(m_TheSliders[i], SIGNAL(valueChanged( int )), m_TheLineEdits[i], SLOT( setTextFromInt(int)) );
        //connect(m_TheComboBoxs[i], SIGNAL(currentIndexChanged(int)), this, SLOT( updateBCF2000Mapping(int)) );
        connect(m_TheSliders[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onVerticalSliderCustomContextMenuRequested(const QPoint )) );
    }

    // Read Settings  --> load BCF2000 Mapping Table
    QSettings settings;
    for(int i = 0; i < NUMofSLIDDERS ; i++)
    {
        QString group = QSTR_BCF2000_MIDI_MAPPING + QString::number(i);
        settings.beginGroup(group);

        if( !settings.value( QSTR_CHAN_NUMB ).isNull() )
        {
            m_BCF2000MappingTable[i].chanNumb = settings.value( QSTR_CHAN_NUMB ).toInt();
            m_BCF2000MappingTable[i].CCID = settings.value( QSTR_CCID ).toInt();
            m_BCF2000MappingTable[i].effectBlockID = settings.value( QSTR_EFFECT_BLOCK_ID ).toInt();
            m_BCF2000MappingTable[i].effectParameterID = settings.value( QSTR_EFFECT_PARAMETER_ID ).toInt();
        }
        else {
            m_BCF2000MappingTable[i]. chanNumb = 255;
            m_BCF2000MappingTable[i].CCID = 255;
            m_BCF2000MappingTable[i].effectBlockID = 255;
            m_BCF2000MappingTable[i].effectParameterID = 255;
        }
        settings.endGroup();
    }

    init();
}

BCF2000::~BCF2000()
{
    delete ui;
}

void BCF2000::init( void)
{
    m_pInstance->settings.beginGroup(QSTR_BCF2000_WINDOW);
    restoreGeometry(m_pInstance->settings.value(QSTR_BCF2000_GEOMETRY).toByteArray());
    m_pInstance->settings.endGroup();

    m_initMode = true;
    m_initMode_timer.start();

    bool found;
    // Check that all the mappings in the BCF2000 mapping still exists
   for( int i=0 ; i < NUMofSLIDDERS ; i++)
   {
       // Initiate the values of the BCF2000 table mapping with the value of the Global Mapping table
       found = false;
       for( int j=0 ; j < m_pInstance->m_numbOfMappings ; j++)
       {
           if(         m_pInstance->m_theMappingTable[j].chanNumb == m_BCF2000MappingTable[i]. chanNumb
               &&   m_pInstance->m_theMappingTable[j].CCID == m_BCF2000MappingTable[i].CCID
               &&   m_pInstance->m_theMappingTable[j].effectBlockID == m_BCF2000MappingTable[i].effectBlockID
               &&   m_pInstance->m_theMappingTable[j].effectParameterID == m_BCF2000MappingTable[i].effectParameterID)
           {
               found = true;

               // If exists copy the current values from m_pInstance->m_theMappingTable
               strncpy( m_BCF2000MappingTable[i].effectBlockLabel, m_pInstance->m_theMappingTable[j].effectBlockLabel, 30);
               strncpy( m_BCF2000MappingTable[i].effectParameterLabel, m_pInstance->m_theMappingTable[j].effectParameterLabel, 30);
               m_BCF2000MappingTable[i].effectParameterType = m_pInstance->m_theMappingTable[j].effectParameterType;
               m_BCF2000MappingTable[i].minDispValue = m_pInstance->m_theMappingTable[j].minDispValue;
               m_BCF2000MappingTable[i].maxDispValue = m_pInstance->m_theMappingTable[j].maxDispValue;
               strncpy( m_BCF2000MappingTable[i].unit, m_pInstance->m_theMappingTable[j].unit, 7);
               m_BCF2000MappingTable[i].paramDispValue = m_pInstance->m_theMappingTable[j].paramDispValue;
               m_BCF2000MappingTable[i].MIDIValue = m_pInstance->m_theMappingTable[j].MIDIValue;

               break;
           }
       }

       if( !found )
       {
            strncpy( m_BCF2000MappingTable[i].effectBlockLabel, "", 30);
            strncpy( m_BCF2000MappingTable[i].effectParameterLabel, "", 30);
            strncpy( m_BCF2000MappingTable[i].unit, "", 7);
            m_BCF2000MappingTable[i].minDispValue = 0;
            m_BCF2000MappingTable[i].maxDispValue = 0;
            m_BCF2000MappingTable[i].effectParameterType = 0;
            m_BCF2000MappingTable[i]. chanNumb = 255;
            m_BCF2000MappingTable[i].CCID = 255;
            m_BCF2000MappingTable[i].effectBlockID = 255;
            m_BCF2000MappingTable[i].effectParameterID = 255;
            m_BCF2000MappingTable[i].paramDispValue = 0;
            m_BCF2000MappingTable[i].MIDIValue = 0;
       }
   }


   // Initiate the Control elements of the BCF2000
   for(int i=0; i<NUMofSLIDDERS ; i++)
   {
       m_setup = true;
       m_TheBlockLabels[i]->setText( m_BCF2000MappingTable[i].effectBlockLabel);
       m_TheParamLabels[i]->setText( m_BCF2000MappingTable[i].effectParameterLabel );
       m_TheMaxLabels[i]->setText( QString::number( m_BCF2000MappingTable[i].maxDispValue ) );
       m_TheMinLabels[i]->setText( QString::number( m_BCF2000MappingTable[i].minDispValue ) );

       m_TheSliders[i]->setMinimum( m_BCF2000MappingTable[i].minDispValue * 1000);
       m_TheSliders[i]->setMaximum( m_BCF2000MappingTable[i].maxDispValue * 1000);
       m_TheSliders[i]->setTickInterval( (m_BCF2000MappingTable[i].maxDispValue - m_BCF2000MappingTable[i].minDispValue) / 100);
       m_TheSliders[i]->setSingleStep( (m_BCF2000MappingTable[i].maxDispValue - m_BCF2000MappingTable[i].minDispValue) / 10 );
       m_TheSliders[i]->setPageStep( (m_BCF2000MappingTable[i].maxDispValue - m_BCF2000MappingTable[i].minDispValue)  * 100);

       m_setup = false;
       m_TheSliders[i]->setValue( m_BCF2000MappingTable[i].paramDispValue * 1000 );

       colorSlider( i );
       m_TheSliders[i]->setAutoFillBackground(true);
   }

   fillComboBox();
   m_initMode = false;
}

void BCF2000::fillComboBox( void )
{
    bool found;

    int selectedPos, currentItemNumb;

    for(int i=0; i < NUMofSLIDDERS ; i++)
    {
        disconnect(m_TheComboBoxs[i], SIGNAL(currentIndexChanged(int)), this, SLOT( updateBCF2000Mapping(int)) );
    }


    for(int i=0; i<NUMofSLIDDERS ; i++)
    {
        selectedPos = -1;
        currentItemNumb = 0;
        // Fill local Mapping table
        m_TheComboBoxs[i]->clear();
        m_TheComboBoxs[i]->addItem( QString::null, -1 );

        for(int j=0; j < m_pInstance->m_numbOfMappings ; j++)
        {
            found = false;
            for(int k=0; k<NUMofSLIDDERS ; k++)
            {
                if(           m_pInstance->m_theMappingTable[j].chanNumb == m_BCF2000MappingTable[k].chanNumb
                      &&   m_pInstance->m_theMappingTable[j].CCID == m_BCF2000MappingTable[k].CCID
                      &&   m_pInstance->m_theMappingTable[j].effectBlockID == m_BCF2000MappingTable[k].effectBlockID
                      &&   m_pInstance->m_theMappingTable[j].effectParameterID == m_BCF2000MappingTable[k].effectParameterID
                      &&   i  != k  )
                {
                    found = true;
                    break;
                }
            }
            if( !found )
            {
                m_TheComboBoxs[i]->addItem( QString("%1 - %2 -- Chan=%3 CC=%4").arg( m_pInstance->m_theMappingTable[j].effectBlockLabel,
                                                                                   m_pInstance->m_theMappingTable[j].effectParameterLabel,
                                                                                   QString::number(m_pInstance->m_theMappingTable[j].chanNumb),
                                                                                   QString::number(m_pInstance->m_theMappingTable[j].CCID)),
                                            j);
                //int ind = m_TheComboBoxs[i]->itemData(currentItemNumb).toInt();
                //QVariant qint = m_TheComboBoxs[i]->itemData(currentItemNumb);
                currentItemNumb++;
                if(         m_pInstance->m_theMappingTable[j].chanNumb == m_BCF2000MappingTable[i]. chanNumb
                    &&   m_pInstance->m_theMappingTable[j].CCID == m_BCF2000MappingTable[i].CCID
                    &&   m_pInstance->m_theMappingTable[j].effectBlockID == m_BCF2000MappingTable[i].effectBlockID
                    &&   m_pInstance->m_theMappingTable[j].effectParameterID == m_BCF2000MappingTable[i].effectParameterID)
                { selectedPos = currentItemNumb;}
            }
        }
        m_TheComboBoxs[i]->setCurrentIndex( selectedPos );
    }

    for(int i=0; i < NUMofSLIDDERS ; i++)
    {
        connect(m_TheComboBoxs[i], SIGNAL(currentIndexChanged(int)), this, SLOT( updateBCF2000Mapping(int)) );
    }
}



void BCF2000::updateBCF2000Mapping( int qcomboIndex )
{
    // If in init mode the QComboBox currentIndexChanged fired won't be processed by this function
    if( m_initMode ) return;

    QComboBox* obj = qobject_cast<QComboBox *>( sender() );
    int sendingComboBox;
    for( sendingComboBox = 0; sendingComboBox < NUMofSLIDDERS ; sendingComboBox++ )
    {
        if( obj == m_TheComboBoxs[sendingComboBox]) break;
    }

    //  qcomboIndex value go from 1 to n for mappings, 0 if for empty selection
    if( qcomboIndex == 0 )
    {
        strncpy( m_BCF2000MappingTable[sendingComboBox].effectBlockLabel, "", 30);
        strncpy( m_BCF2000MappingTable[sendingComboBox].effectParameterLabel, "", 30);
        strncpy( m_BCF2000MappingTable[sendingComboBox].unit, "", 7);
        m_BCF2000MappingTable[sendingComboBox].minDispValue = 0;
        m_BCF2000MappingTable[sendingComboBox].maxDispValue = 0;
        m_BCF2000MappingTable[sendingComboBox].effectParameterType = 0;
        m_BCF2000MappingTable[sendingComboBox]. chanNumb = 255;
        m_BCF2000MappingTable[sendingComboBox].CCID = 255;
        m_BCF2000MappingTable[sendingComboBox].effectBlockID = 255;
        m_BCF2000MappingTable[sendingComboBox].effectParameterID = 255;
        m_BCF2000MappingTable[sendingComboBox].paramDispValue = 0;
        m_BCF2000MappingTable[sendingComboBox].MIDIValue = 0;

        m_TheSliders[sendingComboBox]->setMinimum( 0 );
        m_TheSliders[sendingComboBox]->setMaximum( 0 );
        m_TheSliders[sendingComboBox]->setTickInterval( 0 );
        m_TheSliders[sendingComboBox]->setSingleStep( 0 );
        m_TheSliders[sendingComboBox]->setPageStep( 0 );
        m_TheBlockLabels[sendingComboBox]->setText( "" );
        m_TheParamLabels[sendingComboBox]->setText( "" );
        m_TheMaxLabels[sendingComboBox]->setText( "0" );
        m_TheMinLabels[sendingComboBox]->setText( "0" );
        m_TheSliders[sendingComboBox]->setValue( 0 );
    }
    else {
        //QVariant qint = m_TheComboBoxs[sendingComboBox]->itemData(qcomboIndex);
        //int ind = m_TheComboBoxs[sendingComboBox]->itemData(qcomboIndex ).toInt();

        qcomboIndex = m_TheComboBoxs[sendingComboBox]->itemData(qcomboIndex ).toInt();
        m_BCF2000MappingTable[sendingComboBox]. chanNumb = m_pInstance->m_theMappingTable[qcomboIndex].chanNumb;
        m_BCF2000MappingTable[sendingComboBox].CCID = m_pInstance->m_theMappingTable[qcomboIndex].CCID;
        m_BCF2000MappingTable[sendingComboBox].effectBlockID = m_pInstance->m_theMappingTable[qcomboIndex].effectBlockID;
        m_BCF2000MappingTable[sendingComboBox].effectParameterID = m_pInstance->m_theMappingTable[qcomboIndex].effectParameterID;

        strncpy( m_BCF2000MappingTable[sendingComboBox].effectBlockLabel, m_pInstance->m_theMappingTable[qcomboIndex].effectBlockLabel, 30);
        strncpy( m_BCF2000MappingTable[sendingComboBox].effectParameterLabel, m_pInstance->m_theMappingTable[qcomboIndex].effectParameterLabel, 30);

        m_BCF2000MappingTable[sendingComboBox].effectParameterType   =   m_pInstance->m_theMappingTable[qcomboIndex].effectParameterType;
        m_BCF2000MappingTable[sendingComboBox].minDispValue   =   m_pInstance->m_theMappingTable[qcomboIndex].minDispValue;
        m_BCF2000MappingTable[sendingComboBox].maxDispValue   =   m_pInstance->m_theMappingTable[qcomboIndex].maxDispValue;
        strncpy( m_BCF2000MappingTable[sendingComboBox].unit, m_pInstance->m_theMappingTable[qcomboIndex].unit, 7);

        m_BCF2000MappingTable[sendingComboBox].paramDispValue   =   m_pInstance->m_theMappingTable[qcomboIndex].paramDispValue;
        m_BCF2000MappingTable[sendingComboBox].MIDIValue   =   m_pInstance->m_theMappingTable[qcomboIndex].MIDIValue;



        m_TheSliders[sendingComboBox]->setMinimum( m_BCF2000MappingTable[sendingComboBox].minDispValue * 1000);
        m_TheSliders[sendingComboBox]->setMaximum( m_BCF2000MappingTable[sendingComboBox].maxDispValue * 1000);
        m_TheSliders[sendingComboBox]->setTickInterval( (m_BCF2000MappingTable[sendingComboBox].maxDispValue - m_BCF2000MappingTable[sendingComboBox].minDispValue) / 100);
        m_TheSliders[sendingComboBox]->setSingleStep( (m_BCF2000MappingTable[sendingComboBox].maxDispValue - m_BCF2000MappingTable[sendingComboBox].minDispValue) / 10);
        m_TheSliders[sendingComboBox]->setPageStep( (m_BCF2000MappingTable[sendingComboBox].maxDispValue - m_BCF2000MappingTable[sendingComboBox].minDispValue)  * 100);

        m_TheBlockLabels[sendingComboBox]->setText( m_BCF2000MappingTable[sendingComboBox].effectBlockLabel);
        m_TheParamLabels[sendingComboBox]->setText( m_BCF2000MappingTable[sendingComboBox].effectParameterLabel );
        m_TheMaxLabels[sendingComboBox]->setText( QString::number( m_BCF2000MappingTable[sendingComboBox].maxDispValue ) );
        m_TheMinLabels[sendingComboBox]->setText( QString::number( m_BCF2000MappingTable[sendingComboBox].minDispValue ) );

        m_setup = false;
        m_TheSliders[sendingComboBox]->setValue( m_BCF2000MappingTable[sendingComboBox].paramDispValue * 1000 );

        // TODO : Check if it is enough to properly update the display !!!

    }
    // Update all the comboBox
    fillComboBox();
}

void BCF2000::onSliderValueChanged( int val)
{
    // No change of value while set-up
    if( m_setup) return;

    // Find the Slider that has changed value
    QSliderMod1* obj = qobject_cast<QSliderMod1 *>( sender() );
    int index;
    for( index = 0; index < NUMofSLIDDERS ; index++ )
    {
        if( obj == m_TheSliders[index]) break;
    }

    // Can't be INDEX for parent-->m_theMappingTable[index]
    //m_BCF2000MappingTable[index].paramDispValue = double(val) / double(100);

    // Calculate corresponding MIDI value
    double convertedValue = double(val) / double(1000);
    convertedValue -= double(m_BCF2000MappingTable[index].minDispValue);
    convertedValue /= double((m_BCF2000MappingTable[index].maxDispValue - m_BCF2000MappingTable[index].minDispValue) );
    convertedValue *= double(127);
    convertedValue += double(0.5);
    m_BCF2000MappingTable[index].MIDIValue = int(convertedValue);

    // Send new value to AXE-FX and BCF2000 if
    if(   (( m_pInstance->m_MIDIIN_timer.elapsed() > 3000 && m_pInstance->m_MIDIIN_timer.isValid()) || !m_pInstance->m_MIDIIN_timer.isValid())
       && m_initMode_timer.elapsed() > 1000
       && m_BCF2000MappingTable[index].effectBlockID != 255)
    {
        // Send SYSEX to AXE-FX
        m_pInstance->sendSYSEXtoAXEFX( AXEFX_SYSEX_PARAM_SET_S,
                              m_BCF2000MappingTable[index].effectBlockID,
                              m_BCF2000MappingTable[index].effectParameterID,
                              m_BCF2000MappingTable[index].effectParameterType,
                              m_BCF2000MappingTable[index].MIDIValue );
        // Send CC to BCF2000
        if( m_BCF2000MappingTable[index].chanNumb - 1 > -1 ) //Added because call to on_Slider_valueChanged on UI init
        m_pInstance->sendCCtoMIDIout( m_BCF2000MappingTable[index].chanNumb - 1,
                                 m_BCF2000MappingTable[index].CCID,
                                 m_BCF2000MappingTable[index].MIDIValue,
                                 OTHER1_DEVICE);
    }

    double reConvertedValue = m_BCF2000MappingTable[index].MIDIValue;
    reConvertedValue /= 127;
    reConvertedValue *= ( m_BCF2000MappingTable[index].maxDispValue - m_BCF2000MappingTable[index].minDispValue );
    reConvertedValue += m_BCF2000MappingTable[index].minDispValue;
    m_BCF2000MappingTable[index].paramDispValue = reConvertedValue;

    // Store the new paramDispValue and MIDIValue for use in other displays ( in m_theMappingTable - the main mapping table )
    for(int i = 0; i < m_pInstance->m_numbOfMappings ; i++)
    {
        if(  m_pInstance->m_theMappingTable[i].effectBlockID == m_BCF2000MappingTable[index].effectBlockID
         && m_pInstance->m_theMappingTable[i].effectParameterID == m_BCF2000MappingTable[index].effectParameterID )
        {
            m_pInstance->m_theMappingTable[i].paramDispValue = m_BCF2000MappingTable[index].paramDispValue;
            m_pInstance->m_theMappingTable[i].MIDIValue = int(convertedValue);
        }
    }

    colorSlider( index );

    m_timeLastValueChanged.start();
}


void BCF2000::setSliderValue( int sliderIndex, double value)
{
    if ( m_timeLastValueChanged.elapsed() > 100 )
    {
        double sentVal = value * double(1000);
        m_TheSliders[sliderIndex]->setValue( int( sentVal ) );

        colorSlider(sliderIndex);

        if( g_displayBlownUp )
        {
            m_pInstance->m_dlgBlownUpParamDisplay->show();
            m_pInstance->m_dlgBlownUpParamDisplay->updateBlownUpParamDisplay( sliderIndex, m_BCF2000MappingTable, value );
            m_pInstance->startDlgBlownUpParamDisplayTimer();
        }
    }
}

void BCF2000::colorSlider( int sliderIndex )
{
    if( g_sliderColored )
    {
        m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(),
                                  QColor(255,
                                         255 - (m_BCF2000MappingTable[ sliderIndex ].MIDIValue * 1.5),
                                         255 - (m_BCF2000MappingTable[ sliderIndex ].MIDIValue * 1.5),
                                         255)  );
        m_TheSliders[ sliderIndex ]->setPalette(m_slidderPalette);
    }
}

void BCF2000::setValueIfMapped( unsigned char effectBlockID, unsigned char effectParameterID, double paramDispValue)
{
    for( int i=0 ; i < NUMofSLIDDERS ; i++)
    {
        if( m_BCF2000MappingTable[i].effectBlockID == effectBlockID
           &&  m_BCF2000MappingTable[i].effectParameterID == effectParameterID )
        {
            setSliderValue( i, paramDispValue  );
            break;
        }
    }
}


void BCF2000::onVerticalSliderCustomContextMenuRequested(const QPoint &pos)
{
    QSlider* obj = qobject_cast<QSlider *>( sender() );

    // Search and store the slidder on with the Menu was requested
    int i;
    for( i=0 ; i < NUMofSLIDDERS ; i++)
    {
        if( obj == m_TheSliders[i]) break;
    }
    m_currentSliderForContextMenu = i;

    QMenu *menu=new QMenu(this);
    midiLearn = new QAction("MIDI Learn", this);
    setParamMapping = new QAction("Map AXE-FX param", this);

    connect( midiLearn, SIGNAL(triggered()), this, SLOT( midiLearnIt()) );
    connect( setParamMapping, SIGNAL(triggered()), this, SLOT( setParameterMapping()) );

    if( m_BCF2000MappingTable[m_currentSliderForContextMenu].effectBlockID == 255 )
    { midiLearn->setEnabled(false);}

    menu->addAction( midiLearn);
    menu->addAction( setParamMapping);
    menu->popup( obj->mapToGlobal(pos));
}

void BCF2000::midiLearnIt( void )
{
    // Manage Learn mode !!!
    g_learnMode = true;
    g_learn_paramDispValue = m_BCF2000MappingTable[ m_currentSliderForContextMenu ].paramDispValue;
    g_learn_MIDIValue = m_BCF2000MappingTable[ m_currentSliderForContextMenu ].MIDIValue;
    g_learn_callingDialog = 1;
}

void BCF2000::updateWithLearnedMapping( unsigned char learnedChannel, int learnedCC )
{
    bool found = false;

    if( g_learn_callingDialog != 1) return;

    // TODO : Check if the mapping item already exists
    for(int i = 0; i < m_pInstance->m_numbOfMappings ; i++)
    {
        if(    learnedChannel+1 == m_pInstance->m_theMappingTable[i].chanNumb
            && learnedCC == m_pInstance->m_theMappingTable[i].CCID  )
        {
            found = true;
            g_learnMode = false;
            g_learnModeCount = 0;
            g_learnModeChan = 0;
            g_learnModeCC = 255;
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

    m_BCF2000MappingTable[ m_currentSliderForContextMenu ].chanNumb = learnedChannel + 1;
    m_BCF2000MappingTable[ m_currentSliderForContextMenu ].CCID = learnedCC;

    int qcomboIndex = m_TheComboBoxs[ m_currentSliderForContextMenu ]->itemData( m_TheComboBoxs[ m_currentSliderForContextMenu ]->currentIndex() ).toInt();
    m_pInstance->m_theMappingTable[qcomboIndex].chanNumb = learnedChannel + 1;
    m_pInstance->m_theMappingTable[qcomboIndex].CCID = learnedCC;
    m_pInstance->fillCCtoAXE();
    m_BCF2000MappingTable[ m_currentSliderForContextMenu ].paramDispValue = g_learn_paramDispValue;
    m_BCF2000MappingTable[ m_currentSliderForContextMenu ].MIDIValue = g_learn_MIDIValue;
    setSliderValue( m_currentSliderForContextMenu, m_BCF2000MappingTable[ m_currentSliderForContextMenu ].paramDispValue);

    if( m_BCF2000MappingTable[m_currentSliderForContextMenu].chanNumb - 1 > -1 )
    m_pInstance->sendCCtoMIDIout( m_BCF2000MappingTable[m_currentSliderForContextMenu].chanNumb - 1,
                                m_BCF2000MappingTable[m_currentSliderForContextMenu].CCID,
                                m_BCF2000MappingTable[m_currentSliderForContextMenu].MIDIValue,
                                OTHER1_DEVICE);

    QMessageBox* msgBox 	= new QMessageBox();
    msgBox->setWindowTitle("From MidyAX");
    msgBox->setText("Learn Finished");
    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBox->exec();
    g_learnMode = false;
    g_learnModeCount = 0;
    g_learnModeChan = 0;
    g_learnModeCC = 255;
    init();
}

void BCF2000::setParameterMapping( void)
{
    m_dlgParamMapping = new ParamMapping();

    m_dlgParamMapping->init( & (m_BCF2000MappingTable[ m_currentSliderForContextMenu ])  );

    if ( m_dlgParamMapping->exec() == QDialog::Accepted )
    {
        unsigned char prevEffectBlockID = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectBlockID;
        unsigned char prevEffectParameterID = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterID;
        int prevChanNumb = m_BCF2000MappingTable[m_currentSliderForContextMenu].chanNumb;

        m_dlgParamMapping->get_paramMapping(  & (m_BCF2000MappingTable[ m_currentSliderForContextMenu ])   );

        //Check if there allready was a mapping for the selected Slider/Knob
        if( prevChanNumb <= 16)
        {
            for( int j=0 ; j < m_pInstance->m_numbOfMappings ; j++)
            {
                if(      m_pInstance->m_theMappingTable[j].chanNumb == m_BCF2000MappingTable[m_currentSliderForContextMenu].chanNumb
                    &&   m_pInstance->m_theMappingTable[j].CCID == m_BCF2000MappingTable[m_currentSliderForContextMenu].CCID
                         &&   m_pInstance->m_theMappingTable[j].effectBlockID == prevEffectBlockID
                         &&   m_pInstance->m_theMappingTable[j].effectParameterID == prevEffectParameterID)
                {
                    m_pInstance->m_theMappingTable[j].effectBlockID = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectBlockID;
                    m_pInstance->m_theMappingTable[j].effectParameterID = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterID;
                    strncpy( m_pInstance->m_theMappingTable[j].effectBlockLabel, m_BCF2000MappingTable[m_currentSliderForContextMenu].effectBlockLabel, 30 );
                    strncpy( m_pInstance->m_theMappingTable[j].effectParameterLabel, m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterLabel, 30 );
                    m_pInstance->m_theMappingTable[j].effectParameterType = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterType;
                    m_pInstance->m_theMappingTable[j].minDispValue = m_BCF2000MappingTable[m_currentSliderForContextMenu].minDispValue;
                    m_pInstance->m_theMappingTable[j].maxDispValue = m_BCF2000MappingTable[m_currentSliderForContextMenu].maxDispValue;
                    strncpy( m_pInstance->m_theMappingTable[j].unit, m_BCF2000MappingTable[m_currentSliderForContextMenu].unit, 7 );
                    break;
                }
            }
        }
        else {
            m_pInstance->m_numbOfMappings++;
            int numMap =m_pInstance->m_numbOfMappings -1;

            m_pInstance->m_theMappingTable[numMap].chanNumb = m_BCF2000MappingTable[m_currentSliderForContextMenu].chanNumb;
            m_pInstance->m_theMappingTable[numMap].CCID = m_BCF2000MappingTable[m_currentSliderForContextMenu].CCID;
            m_pInstance->m_theMappingTable[numMap].effectBlockID = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectBlockID;
            m_pInstance->m_theMappingTable[numMap].effectParameterID = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterID;
            strncpy( m_pInstance->m_theMappingTable[numMap].effectBlockLabel, m_BCF2000MappingTable[m_currentSliderForContextMenu].effectBlockLabel, 30 );
            strncpy( m_pInstance->m_theMappingTable[numMap].effectParameterLabel, m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterLabel, 30 );
            m_pInstance->m_theMappingTable[numMap].effectParameterType = m_BCF2000MappingTable[m_currentSliderForContextMenu].effectParameterType;
            m_pInstance->m_theMappingTable[numMap].minDispValue = m_BCF2000MappingTable[m_currentSliderForContextMenu].minDispValue;
            m_pInstance->m_theMappingTable[numMap].maxDispValue = m_BCF2000MappingTable[m_currentSliderForContextMenu].maxDispValue;
            strncpy( m_pInstance->m_theMappingTable[numMap].unit, m_BCF2000MappingTable[m_currentSliderForContextMenu].unit, 7 );

            // To get the new mapped parmeter value
            m_pInstance->sendSYSEXtoAXEFX(AXEFX_SYSEX_PARAM_SET_Q,
                                        m_pInstance->m_theMappingTable[numMap].effectBlockID,
                                        m_pInstance->m_theMappingTable[numMap].effectParameterID);
        }
        delay(300);
        init();
        // TODO : Build an init for one Slidder/Knob

        // Update the "RT" mapping table
        m_pInstance->fillCCtoAXE();
    }
}


void BCF2000::onLineEditEditingFinished(void)
{
    QLineEditMod1* obj = qobject_cast<QLineEditMod1 *>( sender() );

    int i;
    for( i = 0; i < NUMofSLIDDERS ; i++ )
    {
        if( obj == m_TheLineEdits[i]) break;
    }

    //TODO finish function and add to BCR2000

//    QMessageBox* msgBox 	= new QMessageBox();
//    msgBox->setWindowTitle("From MidyAX");
//    msgBox->setText( QString::number( i ) + "  " +  m_TheLineEdits[i]->objectName());
//    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
//    msgBox->exec();
}

void BCF2000::closeEvent(QCloseEvent * event)
{
    storeGeom();
    event->accept();
}

void BCF2000::accept()
{
    storeGeom();
    QDialog::accept();
}

void BCF2000::reject()
{
    storeGeom();
    QDialog::reject();
}

void BCF2000::storeGeom()
{
    m_pInstance->settings.beginGroup(QSTR_BCF2000_WINDOW);
    m_pInstance->settings.setValue(QSTR_BCF2000_GEOMETRY, saveGeometry());
    m_pInstance->settings.endGroup();
}
