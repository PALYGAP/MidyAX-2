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

#include "midicontrollergenericdialog.h"

// Learn mode variables
extern bool g_learnMode;
extern int g_learnModeCount;
extern unsigned char g_learnModeChan;
extern unsigned char g_learnModeCC;
extern double g_learn_paramDispValue;
extern unsigned char g_learn_MIDIValue;
//extern int g_learn_callingDialog;
extern QWidget *gp_learn_callingDialog;
extern bool g_sliderColored;
extern bool g_displayBlownUp;
extern bool g_autoConnect;


MIDIControllerGenericDialog::MIDIControllerGenericDialog(QWidget *parent,
                                                         QString MIDIControllerDialogName,
                                                         int MIDIControllerNumber,
                                                         int numberOfKnobs,
                                                         int numberOfSlidders,
                                                         int numberOfParameterButtons,
                                                         int numberOfPageSelectButtons) :
    QDialog(parent),
    m_setup(false),
    m_initMode(false),
    m_firstDisplay(true),
    m_currentPage(0)
{
    m_pMidyAXDlgInstance = qobject_cast<MidyAX*>(this->parent());
    m_slidderPalette.setColor(QPalette::Window, QColor(255, 255, 255));

    m_numberOfKnobs = numberOfKnobs;
    m_MIDIControllerNumber = MIDIControllerNumber;
    m_numberOfSlidders = numberOfSlidders;
    m_numberOfParameterButtons = numberOfParameterButtons;
    m_numberOfPageSelectButtons = numberOfPageSelectButtons;

    // Allocate the memory for the XTouch MIDI mapping Table
    m_TheMIDIMappingTable = new struct mappingTable[ (m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons) * m_numberOfPageSelectButtons];
    int totalNumberOfMapping = (m_numberOfKnobs+m_numberOfSlidders+ m_numberOfParameterButtons) * m_numberOfPageSelectButtons;
    m_ThePagesMIDIMappingTable = new struct mappingTable[ totalNumberOfMapping ];

    m_MIDIControllerDialogName = MIDIControllerDialogName;
    QSettings_win_geom_group_name = m_MIDIControllerDialogName + "_Window";
    QSettings_win_geom = m_MIDIControllerDialogName + "_Geometry";
    QSettings_group = m_MIDIControllerDialogName + "_MIDImapping";
    QSettings_visible = m_MIDIControllerDialogName + "_Visible";

    // Read Settings  --> load MIDI controller Mapping Table
    int posi;
    QString group;

    // Loads the local MAPPING table form store QSettings (ini file)
    for(int j = 0; j < m_numberOfPageSelectButtons; j++)
    {
        for(int i = 0; i < m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons; i++)
        {
            group = QSettings_group + "__P" + QString("%1").arg(j+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(i+1, 2, 10, QChar('0')) ;;
            m_pMidyAXDlgInstance->settings.beginGroup(group);

            posi = i + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * j  );
            if( !m_pMidyAXDlgInstance->settings.value( QSTR_CHAN_NUMB ).isNull() )
            {
                m_TheMIDIMappingTable[posi].chanNumb = m_pMidyAXDlgInstance->settings.value( QSTR_CHAN_NUMB ).toInt();
                m_TheMIDIMappingTable[posi].CCID = m_pMidyAXDlgInstance->settings.value( QSTR_CCID ).toInt();
                m_TheMIDIMappingTable[posi].effectBlockID = m_pMidyAXDlgInstance->settings.value( QSTR_EFFECT_BLOCK_ID ).toInt();
                m_TheMIDIMappingTable[posi].effectParameterID = m_pMidyAXDlgInstance->settings.value( QSTR_EFFECT_PARAMETER_ID ).toInt();
            }
            else {
                m_TheMIDIMappingTable[posi]. chanNumb = 255;
                m_TheMIDIMappingTable[posi].CCID = 255;
                m_TheMIDIMappingTable[posi].effectBlockID = 255;
                m_TheMIDIMappingTable[posi].effectParameterID = 255;
            }
            m_pMidyAXDlgInstance->settings.endGroup();
        }
    }
}

//void MIDIControllerGenericDialog::loadGlobalMappingtoLocalMapping()
//{
//    // Loads the local MAPPING table form store QSettings (ini file)
//    for(int j = 0; j < m_numberOfPageSelectButtons; j++)
//    {
//        for(int i = 0; i < m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons; i++)
//        {
//            group = QSettings_group + "__P" + QString("%1").arg(j+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(i+1, 2, 10, QChar('0')) ;;
//            settings.beginGroup(group);

//            posi = i + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * j  );
//            if( !settings.value( QSTR_CHAN_NUMB ).isNull() )
//            {
//                m_TheMIDIMappingTable[posi].chanNumb = settings.value( QSTR_CHAN_NUMB ).toInt();
//                m_TheMIDIMappingTable[posi].CCID = settings.value( QSTR_CCID ).toInt();
//                m_TheMIDIMappingTable[posi].effectBlockID = settings.value( QSTR_EFFECT_BLOCK_ID ).toInt();
//                m_TheMIDIMappingTable[posi].effectParameterID = settings.value( QSTR_EFFECT_PARAMETER_ID ).toInt();
//            }
//            else {
//                m_TheMIDIMappingTable[posi]. chanNumb = 255;
//                m_TheMIDIMappingTable[posi].CCID = 255;
//                m_TheMIDIMappingTable[posi].effectBlockID = 255;
//                m_TheMIDIMappingTable[posi].effectParameterID = 255;
//            }
//            settings.endGroup();
//        }
//    }
//}




MIDIControllerGenericDialog::~MIDIControllerGenericDialog()
{}


void MIDIControllerGenericDialog::init( void )
{
    m_initMode = true;
    m_initMode_timer.start();

    if(m_firstDisplay == true)
    {
        m_pMidyAXDlgInstance->settings.beginGroup(QSettings_win_geom_group_name);
        restoreGeometry(m_pMidyAXDlgInstance->settings.value(QSettings_win_geom).toByteArray());
        m_pMidyAXDlgInstance->settings.endGroup();
        m_firstDisplay = false;
    }

    // Check that all the mappings in the controller mapping still exists
    bool found;
    int posi;
    for( int i=0 ; i < m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons; i++)
    {
        // Initiate the values of the XTouchMini table mapping with the value of the Global Mapping table
        for(int j = 0; j < m_numberOfPageSelectButtons; j++)
        {
            found = false;
            posi = i + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * j );
            for( int k=0 ; k < m_pMidyAXDlgInstance->m_numbOfMappings ; k++)
            {
               if( m_pMidyAXDlgInstance->m_theMappingTable[k] == m_TheMIDIMappingTable[posi] )
               {
                   // If exists ==> copy the current values from m_pMidyAXDlgInstance->m_theMappingTable
                   found = true;
                   m_TheMIDIMappingTable[posi] = m_pMidyAXDlgInstance->m_theMappingTable[k];

                   break;
               }
            }
            if( !found )
            {
                m_TheMIDIMappingTable[posi].setToZero();

                // put the position number in the effectBlock label
                char thetempostring[30]; sprintf(thetempostring, "%d", posi+1);
                strncpy( m_TheMIDIMappingTable[posi].effectBlockLabel, thetempostring, 30);
            }
        }
    }
}

void MIDIControllerGenericDialog::connectWidgetOnDialog(void)
{
    // SIGNAL/SLOT connections
    for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs; i++)
    {
        m_setup = true;
        connect(m_TheLineEdits[i], SIGNAL(editingFinished(void)), this, SLOT(onLineEditEditingFinished(void)) );
        connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        connect(m_TheSliders[i], SIGNAL(valueChanged( int )), m_TheLineEdits[i], SLOT( setTextFromInt(int)) );
        connect(m_TheSliders[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onVerticalSliderCustomContextMenuRequested(const QPoint )) );
        //connect(m_TheComboBoxs[i], SIGNAL(currentIndexChanged(int)), this, SLOT( updateXTouchMiniMapping(int)) ) ==> See fillComboBox
    }
    for(int i=0; i < m_numberOfParameterButtons; i++)
    {
        connect(m_TheParameterPushButtons[i], SIGNAL(clicked()), this, SLOT(onPushButtonClicked()) );
    }
}

void MIDIControllerGenericDialog::closeEvent(QCloseEvent * event)
{
    storeGeom();
    event->accept();
}

void MIDIControllerGenericDialog::accept()
{
    m_currentPage = m_PageSelectPBGroup->checkedId();
    storeGeom();
    QDialog::accept();
}

void MIDIControllerGenericDialog::reject()
{
    storeGeom();
    QDialog::reject();
}

void MIDIControllerGenericDialog::storeGeom()
{
    m_pMidyAXDlgInstance->settings.beginGroup(QSettings_win_geom_group_name);
    m_pMidyAXDlgInstance->settings.setValue(QSettings_win_geom, saveGeometry());
    m_pMidyAXDlgInstance->settings.endGroup();
}

void MIDIControllerGenericDialog::constructWidgetLists( QWidget **gridLayoutWidget )
{
    QString widgetName = "comboBox_";
    fillWidgetList<QComboBox>( &m_TheComboBoxs, gridLayoutWidget, &widgetName);

    widgetName = "lineEdit_";
    fillWidgetList<QLineEditMod1>( &m_TheLineEdits, gridLayoutWidget, &widgetName);

    widgetName = "blockLabel_";
    fillWidgetList<QLabel>( &m_TheBlockLabels, gridLayoutWidget, &widgetName);

    widgetName = "paramLabel_";
    fillWidgetList<QLabel>( &m_TheParamLabels, gridLayoutWidget, &widgetName);

    widgetName = "verticalSlider_";
    fillWidgetList<QSliderMod1>( &m_TheSliders, gridLayoutWidget, &widgetName);

    widgetName = "pageSelect_pushButton_";
    fillWidgetList<QPushButton>( &m_ThePageSelectPushButtons, gridLayoutWidget, &widgetName);

    widgetName = "parameter_pushButton_";
    fillWidgetList<QPushButton>( &m_TheParameterPushButtons, gridLayoutWidget, &widgetName);

    widgetName = "minLabel_";
    fillWidgetList<QLabel>( &m_TheMinLabels, gridLayoutWidget, &widgetName);

    widgetName = "maxLabel_";
    fillWidgetList<QLabel>( &m_TheMaxLabels, gridLayoutWidget, &widgetName);


    // Initiate the PAGESELECT PUSHBUTTONS elements
    if( m_numberOfPageSelectButtons > 0 )
    {
        m_PageSelectPBGroup = new QButtonGroup(this);
        for(int i=0; i < m_numberOfPageSelectButtons ; i++)
        {
           m_ThePageSelectPushButtons[i]->setCheckable(true);
           m_PageSelectPBGroup->addButton(m_ThePageSelectPushButtons[i]);
           m_PageSelectPBGroup->setId( m_ThePageSelectPushButtons[i] , i);
        }
        m_PageSelectPBGroup->setExclusive(true);
        m_ThePageSelectPushButtons[0]->setChecked(true);

        if(  m_pMidyAXDlgInstance->m_theMIDIControllers[m_MIDIControllerNumber].controllerConnected == true )
        {
            for(int i=0; i < m_numberOfPageSelectButtons ; i++)
            {
                m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, i+1, 0, m_MIDIControllerNumber);
            }
            m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, 1, 127, m_MIDIControllerNumber);
        }

        connect(m_PageSelectPBGroup, SIGNAL( buttonToggled(int, bool)), this, SLOT(onButtonGroupButtonPushed(int, bool)));
    }
}



void MIDIControllerGenericDialog::setSliderValue( int sliderIndex, double value)
{
    if ( m_timeLastValueChanged.elapsed() > 100 )
    {
        double sentVal = value * double(1000);
        m_TheSliders[sliderIndex]->setValue( int( sentVal ) );

        colorSlider( sliderIndex );

        if( g_displayBlownUp )
        {
//            int  posi = sliderIndex + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

// RELOCATION Blown-up
// TODO: Update when GLOBAL MAPPING mode is but back in place
//            m_pMidyAXDlgInstance->m_dlgBlownUpParamDisplay->show();
//            m_pMidyAXDlgInstance->m_dlgBlownUpParamDisplay->updateBlownUpParamDisplayMOD1( posi, m_ThePagesMIDIMappingTable, value, &m_MIDIControllerDialogName );
//            m_pMidyAXDlgInstance->startDlgBlownUpParamDisplayTimer();
        }
    }
}

void MIDIControllerGenericDialog::colorSlider( int sliderIndex )
{
    if( g_sliderColored )
    {
        int posi = sliderIndex + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

        if( m_TheMIDIMappingTable[ posi ].MIDIValue > 63)
            m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(),
                                     QColor(
                                         255,
                                         255 - ( (m_TheMIDIMappingTable[ posi ].MIDIValue -63) * 3.9),
                                         255 - ( (m_TheMIDIMappingTable[ posi ].MIDIValue -63) * 3.9),
                                         255)  );
         else
            m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(),
                                  QColor(
                                         255 - ( (63 - m_TheMIDIMappingTable[ posi ].MIDIValue) * 3.9),
                                         255 - ( (63 -m_TheMIDIMappingTable[ posi ].MIDIValue) * 3.9),
                                         255,
                                         255  )       )
        ;
        m_TheSliders[ sliderIndex ]->setPalette(m_slidderPalette);
    }
}

void MIDIControllerGenericDialog::fillComboBox(void)
{
    bool found;

    int selectedPos, currentItemNumb;

    // Disconnect the signals to avoid multiple updating
    for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
    {
        disconnect(m_TheComboBoxs[i], SIGNAL(currentIndexChanged(int)), this, SLOT( updateMIDIMapping(int)) );
    }

    // Fills each COMBOBOX or KNOBs and SLIDDERs list
    int posi;
    for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs; i++)
    {
        selectedPos = -1;
        currentItemNumb = 0;
        // Fill local Mapping table
        m_TheComboBoxs[i]->clear();
        m_TheComboBoxs[i]->addItem( QString::null, -1 );

        // Check if a mapping from the global "m_theMappingTable" mapping has a local correspondance in "m_TheMIDIMappingTable"
        for(int j=0; j < m_pMidyAXDlgInstance->m_numbOfMappings ; j++)
        {
            // Check if a global mapping matches a local mapping. If yes fill combobox.
            found = false;
            for(int k=0; k < m_numberOfSlidders + m_numberOfKnobs ; k++)
            {
//                for(int l=0; l < m_numberOfPageSelectButtons ; l++)
//                {
                    posi = k + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );
                    if( m_pMidyAXDlgInstance->m_theMappingTable[j] == m_TheMIDIMappingTable[posi] &&   i  != k  )
                    {
                        found = true;
                        break;
                    }
//                }
            }

            if( !found )
            {
                m_TheComboBoxs[i]->addItem( QString("%1 - %2 -- Chan=%3 CC=%4").arg( m_pMidyAXDlgInstance->m_theMappingTable[j].effectBlockLabel,
                                                                                   m_pMidyAXDlgInstance->m_theMappingTable[j].effectParameterLabel,
                                                                                   QString::number(m_pMidyAXDlgInstance->m_theMappingTable[j].chanNumb),
                                                                                   QString::number(m_pMidyAXDlgInstance->m_theMappingTable[j].CCID)),
                                            j);
                currentItemNumb++;
                //If the mapping is put on a knob/slider set it as the Selected item in the combobox
                posi = i + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );
                if( m_pMidyAXDlgInstance->m_theMappingTable[j] == m_TheMIDIMappingTable[posi] )
                { selectedPos = currentItemNumb;}
            }
        }
        m_TheComboBoxs[i]->setCurrentIndex( selectedPos );
    }

    for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
    {
        connect(m_TheComboBoxs[i], SIGNAL(currentIndexChanged(int)), this, SLOT( updateMIDIMapping(int)) );
    }
}


void MIDIControllerGenericDialog::onLineEditEditingFinished(void)
{
    QLineEditMod1* obj = qobject_cast<QLineEditMod1 *>( sender() );

    int i;
    for( i = 0; i < m_numberOfKnobs; i++ )
    {
        if( obj == m_TheLineEdits[i]) break;
    }
    //TODO: finish function
}

void MIDIControllerGenericDialog::onPushButtonClicked(void)
{
    // ONLY process PB click from param PB not pageChange PB

    // Find the PushButton that has changed/clicked
    QPushButton* obj = qobject_cast<QPushButton *>( sender() );
    int index;
    for( index = 0; index < m_numberOfPageSelectButtons ; index++ )
    {
        if( obj == m_ThePageSelectPushButtons[index] ) break;
    }
    //TODO: finish function
    //processPageChangeRequest( index, 127 );
    fillComboBox();
    updateKnobsDisplay();

}


void MIDIControllerGenericDialog::updateMIDIMapping( int qcomboIndex )
{
    // Called when a new item is selected in the "mapping" combobox of the KNOBs or SLIDDERs
    // If in init mode the QComboBox currentIndexChanged fired won't be processed by this function
    if( m_initMode ) return;

    QComboBox* obj = qobject_cast<QComboBox *>( sender() );
    int sendingComboBox, posi, posInTheMappingTable;
    for( sendingComboBox = 0; sendingComboBox < m_numberOfSlidders + m_numberOfKnobs ; sendingComboBox++ )
    {
        if( obj == m_TheComboBoxs[sendingComboBox]) break;
    }

    posi = sendingComboBox + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    //  qcomboIndex value go from 1 to n for mappings, 0 if for empty selection
    if( qcomboIndex == 0 )
    {
        // Remove the mapping from the local mapping table
        m_TheMIDIMappingTable[posi].setToZero();

        // Update the dialog display for the corresponding Knob/Slidder
        m_TheSliders[sendingComboBox]->setMinimum( 0 );
        m_TheSliders[sendingComboBox]->setMaximum( 0 );
        m_TheSliders[sendingComboBox]->setTickInterval( 0 );
        m_TheSliders[sendingComboBox]->setSingleStep( 0 );
        m_TheSliders[sendingComboBox]->setPageStep( 0 );
        m_TheBlockLabels[sendingComboBox]->setText( "" );
        m_TheParamLabels[sendingComboBox]->setText( "" );
        m_TheSliders[sendingComboBox]->setValue( 0 );
        this->update();
//        if( sendingComboBox < NUMofSLIDDERS )
//        {
//            m_TheMaxLabels[sendingComboBox]->setText( "0" );
//            m_TheMinLabels[sendingComboBox]->setText( "0" );
//        }
    }
    else {
        //QVariant qint = m_TheComboBoxs[sendingComboBox]->itemData(qcomboIndex);
        //int ind = m_TheComboBoxs[sendingComboBox]->itemData(qcomboIndex ).toInt();

        // get the ItemData from the newly selected item in the combobox. Itemdata  contains the number of the mapping in the global mapping table
        posInTheMappingTable = m_TheComboBoxs[sendingComboBox]->itemData(qcomboIndex ).toInt();

        m_TheMIDIMappingTable[posi] = m_pMidyAXDlgInstance->m_theMappingTable[posInTheMappingTable];

        m_TheSliders[sendingComboBox]->setMinimum( m_TheMIDIMappingTable[posi].minDispValue * 1000);
        m_TheSliders[sendingComboBox]->setMaximum( m_TheMIDIMappingTable[posi].maxDispValue * 1000);
        m_TheSliders[sendingComboBox]->setTickInterval( (m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue) / 100);
        m_TheSliders[sendingComboBox]->setSingleStep( (m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue) / 10);
        m_TheSliders[sendingComboBox]->setPageStep( (m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue)  * 100);

        m_TheBlockLabels[sendingComboBox]->setText( m_TheMIDIMappingTable[posi].effectBlockLabel);
        m_TheParamLabels[sendingComboBox]->setText( m_TheMIDIMappingTable[posi].effectParameterLabel );
//        if( sendingComboBox < NUMofSLIDDERS )
//        {
//            m_TheMaxLabels[sendingComboBox]->setText( QString::number( m_TheMIDIMappingTable[posi].maxDispValue ) );
//            m_TheMinLabels[sendingComboBox]->setText( QString::number( m_TheMIDIMappingTable[posi].minDispValue ) );
//        }

        m_setup = false;
        m_TheSliders[sendingComboBox]->setValue( m_TheMIDIMappingTable[posi].paramDispValue * 1000 );

        // TODO : Check if it is enough to properly update the display !!!

    }
    // Update all the comboBox
    fillComboBox();
    updateKnobsDisplay();
}


void MIDIControllerGenericDialog::onSliderValueChanged( int val )
{
    int index, posi;

    // No change of value while set-up
    if( m_setup) return;

    // Find the Slider that has changed value
    QSliderMod1* obj = qobject_cast<QSliderMod1 *>( sender() );

    for( index = 0; index < m_numberOfSlidders + m_numberOfKnobs ; index++ )
    {
        if( obj == m_TheSliders[index]) break;
    }
    posi = index + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );


    // Can't be INDEX for parent-->m_theMappingTable[index]
    //m_TheMIDIMappingTable[posi].paramDispValue = double(val) / double(100);

    // Calculate corresponding MIDI value
    double convertedValue = double(val) / double(1000);
    convertedValue -= double(m_TheMIDIMappingTable[posi].minDispValue);
    convertedValue /= double((m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue) );
    convertedValue *= double(127);
    convertedValue += double(0.5);
    m_TheMIDIMappingTable[posi].MIDIValue = int(convertedValue);

    // Send new value to AXE-FX and XTouchMini if
    if(   (( m_pMidyAXDlgInstance->m_MIDIIN_timer.elapsed() > 3000 && m_pMidyAXDlgInstance->m_MIDIIN_timer.isValid()) || !m_pMidyAXDlgInstance->m_MIDIIN_timer.isValid())
       && m_initMode_timer.elapsed() > 1000
       && m_TheMIDIMappingTable[posi].effectBlockID != 255)
    {
        // Sends SYSEX to AXE-FX
        m_pMidyAXDlgInstance->sendSYSEXtoAXEFX( AXEFX_SYSEX_PARAM_SET_S,
                              m_TheMIDIMappingTable[posi].effectBlockID,
                              m_TheMIDIMappingTable[posi].effectParameterID,
                              m_TheMIDIMappingTable[posi].effectParameterType,
                              m_TheMIDIMappingTable[posi].MIDIValue );

        //if( m_TheMIDIMappingTable[posi].chanNumb - 1 > -1 ) //Added because call to on_Slider_valueChanged on UI init

        // Sends CC to connected MIDI device
        if( m_pMidyAXDlgInstance->m_theMIDIControllers[ m_MIDIControllerNumber ].controllerConnected == true )
        m_pMidyAXDlgInstance->sendCCtoMIDIout( m_TheMIDIMappingTable[posi].chanNumb,
                                 //m_TheMIDIMappingTable[posi].CCID,
                                 index+1,
                                 m_TheMIDIMappingTable[posi].MIDIValue,
                                 m_MIDIControllerNumber);

        //TODO: check if param is mapped on other MIDI controller --> update value
    }

    double reConvertedValue = m_TheMIDIMappingTable[posi].MIDIValue;
    reConvertedValue /= 127;
    reConvertedValue *= ( m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue );
    reConvertedValue += m_TheMIDIMappingTable[posi].minDispValue;
    m_TheMIDIMappingTable[posi].paramDispValue = reConvertedValue;

    // Store the new paramDispValue and MIDIValue for use in other displays ( in m_theMappingTable - the main mapping table )
    for(int i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++)
    {
        if(  m_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockID == m_TheMIDIMappingTable[posi].effectBlockID
         && m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterID == m_TheMIDIMappingTable[posi].effectParameterID )
        {
            m_pMidyAXDlgInstance->m_theMappingTable[i].paramDispValue = m_TheMIDIMappingTable[posi].paramDispValue;
            m_pMidyAXDlgInstance->m_theMappingTable[i].MIDIValue = int(convertedValue);
        }
    }

    colorSlider( index );

    m_timeLastValueChanged.start();
}

void MIDIControllerGenericDialog::setValueIfMapped( unsigned char effectBlockID, unsigned char effectParameterID, double paramDispValue)
{
    int posi = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId();

    for( int i=posi ; i < posi+ m_numberOfSlidders + m_numberOfKnobs ; i++)
    {
        if( m_TheMIDIMappingTable[i].effectBlockID == effectBlockID
           &&  m_TheMIDIMappingTable[i].effectParameterID == effectParameterID )
        {
            setSliderValue( (i - posi) , paramDispValue  );
            break;
        }
    }
}


void MIDIControllerGenericDialog::onVerticalSliderCustomContextMenuRequested(const QPoint &pos)
{
    QSlider* obj = qobject_cast<QSlider *>( sender() );

    // Search and store the slidder on with the Menu was requested
    int i;
    for( i=0 ; i < m_numberOfKnobs ; i++)
    {
        if( obj == m_TheSliders[i]) break;
    }
    m_currentSliderForContextMenu = i;

    QMenu *menu=new QMenu(this);
    midiLearn = new QAction("MIDI Learn", this);
    setParamMapping = new QAction("Map AXE-FX param", this);

    connect( midiLearn, SIGNAL(triggered()), this, SLOT( midiLearnIt()) );
    connect( setParamMapping, SIGNAL(triggered()), this, SLOT( setParameterMapping()) );

    int posi = m_currentSliderForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    if( m_TheMIDIMappingTable[ posi ].effectBlockID == 255 )
    { midiLearn->setEnabled(false);}

    menu->addAction( midiLearn);
    menu->addAction( setParamMapping);
    menu->popup( obj->mapToGlobal(pos));
}


void MIDIControllerGenericDialog::midiLearnIt(void)
{
    // Manage Learn mode !!!
    int posi = m_currentSliderForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    g_learnMode = true;
    g_learn_paramDispValue = m_TheMIDIMappingTable[ posi ].paramDispValue;
    g_learn_MIDIValue = m_TheMIDIMappingTable[ posi ].MIDIValue;
    //g_learn_callingDialog = 3;
    gp_learn_callingDialog = (QWidget *) this;
}


void MIDIControllerGenericDialog::updateWithLearnedMapping( unsigned char learnedChannel, int learnedCC )
{
    bool found = false;

    if( gp_learn_callingDialog != this ) return;

    // TODO : Check if the mapping item already exists
    for(int i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++)
    {
        if(    learnedChannel+1 == m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb
            && learnedCC == m_pMidyAXDlgInstance->m_theMappingTable[i].CCID  )
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

    int posi = m_currentSliderForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    m_TheMIDIMappingTable[ posi ].chanNumb = learnedChannel + 1;
    m_TheMIDIMappingTable[ posi ].CCID = learnedCC;

    int qcomboIndex = m_TheComboBoxs[ posi ]->itemData( m_TheComboBoxs[ posi ]->currentIndex() ).toInt();
    m_pMidyAXDlgInstance->m_theMappingTable[qcomboIndex].chanNumb = learnedChannel + 1;
    m_pMidyAXDlgInstance->m_theMappingTable[qcomboIndex].CCID = learnedCC;
    m_pMidyAXDlgInstance->fillCCtoAXE();
    m_TheMIDIMappingTable[ posi ].paramDispValue = g_learn_paramDispValue;
    m_TheMIDIMappingTable[ posi ].MIDIValue = g_learn_MIDIValue;
    setSliderValue( m_currentSliderForContextMenu, m_TheMIDIMappingTable[ posi ].paramDispValue);



    if( m_TheMIDIMappingTable[posi].chanNumb > -1 )
    m_pMidyAXDlgInstance->sendCCtoMIDIout( m_TheMIDIMappingTable[posi].chanNumb,
                                m_TheMIDIMappingTable[posi].CCID,
                                m_TheMIDIMappingTable[posi].MIDIValue,
                                m_MIDIControllerNumber);

    QMessageBox* msgBox = new QMessageBox();
    msgBox->setWindowTitle("From MidyAX");
    msgBox->setText("Learn Finished");
    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
    msgBox->exec();
    g_learnMode = false;
    g_learnModeCount = 0;
    g_learnModeChan = 0;
    g_learnModeCC = 255;

    fillComboBox();
}

void MIDIControllerGenericDialog::setParameterMapping(void)
{
    int posi = m_currentSliderForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    m_dlgParamMapping = new ParamMapping(m_pMidyAXDlgInstance);
    m_dlgParamMapping->init( & (m_TheMIDIMappingTable[ posi ])  );

    if ( m_dlgParamMapping->exec() == QDialog::Accepted )
    {
        unsigned char prevEffectBlockID = m_TheMIDIMappingTable[posi].effectBlockID;
        unsigned char prevEffectParameterID = m_TheMIDIMappingTable[posi].effectParameterID;
        int prevChanNumb = m_TheMIDIMappingTable[posi].chanNumb;

        m_dlgParamMapping->get_paramMapping(  & (m_TheMIDIMappingTable[ posi ])   );

        // If the XTouchMini Knob/Slidder was allready mapped
        // --> Check if there allready was a mapping for the selected chanNumb/CCID couple
        if( prevChanNumb <= 16)
        {
            for( int j=0 ; j < m_pMidyAXDlgInstance->m_numbOfMappings ; j++)
            {
                if(      m_pMidyAXDlgInstance->m_theMappingTable[j].chanNumb == m_TheMIDIMappingTable[posi].chanNumb
                    &&   m_pMidyAXDlgInstance->m_theMappingTable[j].CCID == m_TheMIDIMappingTable[posi].CCID
                    &&   m_pMidyAXDlgInstance->m_theMappingTable[j].effectBlockID == prevEffectBlockID
                    &&   m_pMidyAXDlgInstance->m_theMappingTable[j].effectParameterID == prevEffectParameterID)

                {
                    m_pMidyAXDlgInstance->m_theMappingTable[j] = m_TheMIDIMappingTable[posi];

                    // To get the new mapped parmeter value
                    m_pMidyAXDlgInstance->sendSYSEXtoAXEFX(AXEFX_SYSEX_PARAM_SET_Q,
                                                m_pMidyAXDlgInstance->m_theMappingTable[j].effectBlockID,
                                                m_pMidyAXDlgInstance->m_theMappingTable[j].effectParameterID);
                    break;
                }
            }
        }
        else {
            m_pMidyAXDlgInstance->m_numbOfMappings++;
            int numMap =m_pMidyAXDlgInstance->m_numbOfMappings -1;

            m_pMidyAXDlgInstance->m_theMappingTable[numMap] = m_TheMIDIMappingTable[posi];

            // To get the new mapped parmeter value
            m_pMidyAXDlgInstance->sendSYSEXtoAXEFX(AXEFX_SYSEX_PARAM_SET_Q,
                                        m_pMidyAXDlgInstance->m_theMappingTable[numMap].effectBlockID,
                                        m_pMidyAXDlgInstance->m_theMappingTable[numMap].effectParameterID);
        }
        delay(300);
        init();
        //In case a local mapping has been removed --> update comboBocx
        fillComboBox();
        updateKnobsDisplay();
        // TODO : Build an init for one Slidder/Knob

        // Update the "RT" mapping table
        m_pMidyAXDlgInstance->fillCCtoAXE();
        //m_pMidyAXDlgInstance->getMidiMappingParamValues();

    }

    updateKnobsDisplay();
}

void MIDIControllerGenericDialog::updateKnobsDisplay(void)
{
    int posi;
    for(int i=0; i < m_numberOfKnobs + m_numberOfSlidders ; i++)
    {
        posi = i + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

        m_setup = true; // Avoid slidder display updates that call onSlidderValueChnaged

        if( m_TheMIDIMappingTable[posi].chanNumb != 255 )
        {
            m_TheBlockLabels[i]->setText( m_TheMIDIMappingTable[posi].effectBlockLabel);
            m_TheParamLabels[i]->setText( m_TheMIDIMappingTable[posi].effectParameterLabel );
            m_TheSliders[i]->setMinimum( m_TheMIDIMappingTable[posi].minDispValue * 1000);
            m_TheSliders[i]->setMaximum( m_TheMIDIMappingTable[posi].maxDispValue * 1000);
            m_TheSliders[i]->setTickInterval( (m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue) / 100);
            m_TheSliders[i]->setSingleStep( (m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue) / 10 );
            m_TheSliders[i]->setPageStep( (m_TheMIDIMappingTable[posi].maxDispValue - m_TheMIDIMappingTable[posi].minDispValue)  * 100);
            m_TheSliders[i]->setEnabled( true );

            //TODO : add display of Min/max value for Slidder controls

        }
        else {
            m_TheSliders[i]->setEnabled( false );
        }

        m_setup = false; // Stopd avoiding slidder display updates that call onSlidderValueChnaged
        m_TheSliders[i]->setValue( m_TheMIDIMappingTable[posi].paramDispValue * 1000 );

        colorSlider( i );
        m_TheSliders[i]->setAutoFillBackground(true);
    }
    this->update();
}


void MIDIControllerGenericDialog::processCC( int chanNumb, int CCID, int MIDIValue )
{
    // Process the page change request (on channel 16)
    if( chanNumb == 15 && CCID <= m_numberOfPageSelectButtons )
    {
        processPageChangeRequest( CCID, MIDIValue );
    }

    // Process the EffectBlock ON/OFF request (on channel 15)
    if( chanNumb == 14 && CCID <= m_numberOfPageSelectButtons )
    {
        //process the pushButtons
        processPageChangeRequest( CCID, MIDIValue );
    }
}

void MIDIControllerGenericDialog::processPageChangeRequest( int CCID, int MIDIValue )
{
    int currentON = m_PageSelectPBGroup->checkedId()+1;

    // If request OFF for currentON refuse and set currentON back ON
    if( CCID == currentON && MIDIValue <= 63 )
    {
        // Send CC to right device with OFF for CCID
        m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, CCID, 127, m_MIDIControllerNumber);
        this->raise();
        return;
    }

    if( CCID != currentON && MIDIValue > 63 )
    {
        // Disconnect the signals to avoid multiple updating
        for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
        {
            disconnect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        }

        // Send CC to right device with OFF for currentON
        m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, currentON, 0, m_MIDIControllerNumber);
        m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, CCID, 127, m_MIDIControllerNumber);

        // Update display
        m_ThePageSelectPushButtons[CCID-1]->setChecked(true);

//        int posi,page;
//        page = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * (CCID-1);
//        for(int i= 0; i < m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons; i++ )
//        {
//            posi = i + ( page );
//            if( m_TheMIDIMappingTable[posi].chanNumb !=255 ) //Added because call to on_Slider_valueChanged on UI init
//                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_TheMIDIMappingTable[posi].chanNumb - 1,
//                                              ( m_TheMIDIMappingTable[posi].CCID - page ),
//                                              m_TheMIDIMappingTable[posi].MIDIValue,
//                                              m_MIDIControllerNumber);
//            else
//                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_pMidyAXDlgInstance->m_theMIDIControllers[m_MIDIControllerNumber].fixedCCMIDIChannel-1,
//                                              i+1,
//                                              0,
//                                              m_MIDIControllerNumber);

//        }
//        fillComboBox();
//        updateKnobsDisplay();
//        this->update();

        // RE-Connect the signals
        for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
        {
            connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        }
    }
}

void MIDIControllerGenericDialog::onButtonGroupButtonPushed(int id, bool checked)
{
    // Two signal buttonToggled (checked and unchecked) are send when changing the ON PB. Only one (checked) is processed.

    //int device;
    if( checked == true )
    {
        // Disconnect the signals to avoid multiple updating
        for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
        {
            disconnect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        }

        for(int i = 0; i < m_numberOfPageSelectButtons; i++)//
        {
            if( i != id )m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, i, 0, m_MIDIControllerNumber);
        }
        m_pMidyAXDlgInstance->sendCCtoMIDIout( 16, id+1, 127, m_MIDIControllerNumber);

        int posi,page;
        page = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * id;
        for(int i= 0; i < m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons; i++ )
        {
            posi = i + ( page );
            if( m_TheMIDIMappingTable[posi].chanNumb !=255 ) //Added because call to on_Slider_valueChanged on UI init
                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_TheMIDIMappingTable[posi].chanNumb,
                                              ( m_TheMIDIMappingTable[posi].CCID - page ),
                                              m_TheMIDIMappingTable[posi].MIDIValue,
                                              m_MIDIControllerNumber);
            //TODO: Check if that FIXED_CC_MAPPING code is still needed here
//            else
//                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_pMidyAXDlgInstance->m_theMIDIControllers[m_MIDIControllerNumber].fixedCCMIDIChannel-1,
//                                              i+1,
//                                              0,
//                                              m_MIDIControllerNumber);
        }
        fillComboBox();
        updateKnobsDisplay();
        this->update();
        this->raise();

        // RE-Connect the signals
        for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
        {
            connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        }
    }
}


void MIDIControllerGenericDialog::showEvent(QShowEvent * event)
{
    //Use to refresh the de dialog display before it beeing shown
    event->setAccepted(true);
    m_ThePageSelectPushButtons[ m_currentPage ]->click();   // Should trigger clicked signal, and check the button
}
