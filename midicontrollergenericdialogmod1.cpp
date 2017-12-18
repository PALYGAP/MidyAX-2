#include "midicontrollergenericdialogmod1.h"

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

extern QStringList  AXE_effect_CC_Label;

BlownUpParamDisplay *MIDIControllerGenericDialogMOD1::m_dlgBlownUpParamDisplay = NULL;

MIDIControllerGenericDialogMOD1::MIDIControllerGenericDialogMOD1(QWidget *parent,
                                                         QString MIDIControllerDialogName, //Use for QSettings variables name construction
                                                         int MIDIControllerNumber,  //Use to sent CC and to access info from m_theMIDIController
                                                         int numberOfKnobs,
                                                         int numberOfSlidders,
                                                         int numberOfParameterButtons,
                                                         int numberOfPageSelectButtons) :
    QDialog( parent ),
    m_setup( false ),
    m_initMode( false ),
    m_firstDisplay( true ),
    m_currentPage( 0 )
{
    m_pMidyAXDlgInstance = qobject_cast<MidyAX*>(this->parent());
    m_slidderPalette.setColor(QPalette::Window, QColor(255, 255, 255));

    m_numberOfKnobs = numberOfKnobs;
    m_MIDIControllerNumber = MIDIControllerNumber;
    m_numberOfSlidders = numberOfSlidders;
    m_numberOfParameterButtons = numberOfParameterButtons;
    m_numberOfPageSelectButtons = numberOfPageSelectButtons;
    m_fixedParamControlMIDIChannel = m_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIControllerNumber].fixedCCMIDIChannel;
    m_fixedEffectBlockOBControlMIDIChannel = m_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIControllerNumber].fixedEffectBlockOBControlMIDIChannel;
    m_fixedPageControlMIDIChannel = m_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIControllerNumber].fixedPageControlMIDIChannel;
    m_fixedAXEFXMIDIChannel = m_pMidyAXDlgInstance->m_theFMMIDIControllers[MIDIControllerNumber].fixedAXEFXMIDIChannel;


    m_MIDIControllerDialogName = MIDIControllerDialogName;
    QSettings_win_geom_group_name = m_MIDIControllerDialogName + "_Window";
    QSettings_win_geom = m_MIDIControllerDialogName + "_Geometry";
    QSettings_group = m_MIDIControllerDialogName + "_MIDImapping";
    QSettings_visible = m_MIDIControllerDialogName + "_Visible";

    // Allocate the memory for the XTouch MIDI mapping Table
    int totalNumberOfMapping = ( m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons ) * m_numberOfPageSelectButtons;
    m_ThePagesMIDIMappingTable = new struct pageMappingTable[ totalNumberOfMapping ];
    m_TheCCPagesMIDIMappingTable = new struct CCpageMappingTable[ totalNumberOfMapping ];

//    //If no custom mapping loads factory mapping
//    if( /*Custom mapping present*/ ) loadFactoryMapping();

//    QFile file(":files/BCR2000_Mapping.csv");
//    if (!file.open(QIODevice::ReadOnly)) {
//        qDebug() << file.errorString();
//        return 1;
//    }

//    QStringList wordList;
//    while (!file.atEnd()) {
//        QByteArray line = file.readLine();
//        wordList.append(line.split(',').first());
//    }
//    qDebug() << wordList;

    // Load user (custom) page PARAM mappings from QSettings settings
    QString groupName, QSettings_group = m_MIDIControllerDialogName + "_PageMapping__P";
    int posi;

    for( int i=0; i < m_numberOfPageSelectButtons; i++)
    {
        for( int j=0; j < m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons; j++)
        {
            groupName = QSettings_group + QString("%1").arg(i+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(j+1, 2, 10, QChar('0')) ;;
            m_pMidyAXDlgInstance->settings.beginGroup(groupName);

            posi = j + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * i  );

            if( !(m_pMidyAXDlgInstance->settings.value( QSTR_EFFECT_BLOCK_ID ).isNull()) )
            {
                m_ThePagesMIDIMappingTable[posi].effectBlockID = m_pMidyAXDlgInstance->settings.value( QSTR_EFFECT_BLOCK_ID ).toInt();
                m_ThePagesMIDIMappingTable[posi].effectParameterID = m_pMidyAXDlgInstance->settings.value( QSTR_EFFECT_PARAMETER_ID ).toInt();

                // Fill the fast correspondance table MIDIContActMap
                for(int a=0; a < AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE; a++)
                {
                    if( m_pMidyAXDlgInstance->MIDIContActMap[ m_MIDIControllerNumber - 1 ]
                                                            [ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100]
                                                            [ m_ThePagesMIDIMappingTable[posi].effectParameterID ]
                                                            [0][a] == 255 ) //Stops as soon as one element has "empty" value
                    {
                        m_pMidyAXDlgInstance->MIDIContActMap[ m_MIDIControllerNumber -1 ]
                                                     [ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100 ]
                                                     [ m_ThePagesMIDIMappingTable[posi].effectParameterID ][ 0 ][a] = i;
                        m_pMidyAXDlgInstance->MIDIContActMap[ m_MIDIControllerNumber -1 ]
                                                     [ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100 ]
                                                     [ m_ThePagesMIDIMappingTable[posi].effectParameterID ][ 1 ][a] = j;
                        break;
                    }
                }

                // Fill the m_theMappingTable with the Block, Param label and Param Type ... after finding the right item :)
                int l;
                for( l = 0; l < AXEFX_NUMBER_EFFECTS_BLOCK ; l++)
                {
                    if( m_ThePagesMIDIMappingTable[posi].effectBlockID == EffectBlock__ID[l] ) break;
                }
                //TODO: display a message instead of exit(0)
                if( l == AXEFX_NUMBER_EFFECTS_BLOCK )
                    exit(0);
                strncpy( m_ThePagesMIDIMappingTable[posi].effectBlockLabel,
                         EffectBlock__names[ l ],
                         30);

                // Calculate the possition in the parameter arrays
                int pos = 0;
                int posEffectType = AXEFX_Effect_Block_ID_to_Effect_Type_ID[ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100 ] - 2;

                for(int k = 0; k < posEffectType ; k++)
                {
                    pos += EffectType__numOfParameters[ k ];
                }
                pos = pos + m_ThePagesMIDIMappingTable[posi].effectParameterID;
                strncpy( m_ThePagesMIDIMappingTable[posi].effectParameterLabel, Parameter__labels[ pos], 30);
                m_ThePagesMIDIMappingTable[posi].effectParameterType = Parameter__types[ pos ];
                m_ThePagesMIDIMappingTable[posi].minDispValue = Parameter__minDispValue[ pos ];
                m_ThePagesMIDIMappingTable[posi].maxDispValue = Parameter__maxDispValue[ pos ];
                strncpy( m_ThePagesMIDIMappingTable[posi].unit, Parameter__unitModalValues[ Parameter__unit[ pos ] ], 7);
            }
            else {
                m_ThePagesMIDIMappingTable[posi].effectBlockID = 255;
                m_ThePagesMIDIMappingTable[posi].effectParameterID = 255;
            }
            m_pMidyAXDlgInstance->settings.endGroup();
        }
    }


    // Load user (custom) page CC mappings from QSettings settings
    QSettings_group = m_MIDIControllerDialogName + "_PageMapping__P";

    for( int i=0; i < m_numberOfPageSelectButtons; i++)
    {
        for( int j=0; j < m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons; j++)
        {
            groupName = QSettings_group + QString("%1").arg(i+1, 2, 10, QChar('0')) + "_" + QString("%1").arg(j+1, 2, 10, QChar('0')) + "_ControlCC";
            m_pMidyAXDlgInstance->settings.beginGroup(groupName);

            posi = j + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * i  );

            if( !(m_pMidyAXDlgInstance->settings.value( QSTR_CC_CONTROL_NUMBER ).isNull()) )
            {
                m_TheCCPagesMIDIMappingTable[posi].number = m_pMidyAXDlgInstance->settings.value( QSTR_CC_CONTROL_NUMBER ).toInt();
                m_TheCCPagesMIDIMappingTable[posi].AXE_CC = m_pMidyAXDlgInstance->settings.value( QSTR_CC_CONTROL_CC ).toInt();

                m_TheCCPagesMIDIMappingTable[posi].controlName = AXE_effect_CC_Label[ m_TheCCPagesMIDIMappingTable[posi].number - 1 ];

                // Set initial MIDI VALUE
                // TODO : finish --> get looper and block info.
                //Bypass, Tempo, Tuner, Ext Contr, Looper controls, scene select
                if( m_TheCCPagesMIDIMappingTable[ posi ].number >= 4 && m_TheCCPagesMIDIMappingTable[ posi ].number <= 28 ) m_TheCCPagesMIDIMappingTable[ posi ].MIDIValue = 0;
                // Effect Block ON/Bypass and X/Y
                if( m_TheCCPagesMIDIMappingTable[ posi ].number >= 33 && m_TheCCPagesMIDIMappingTable[ posi ].number <= 115 ) m_TheCCPagesMIDIMappingTable[ posi ].MIDIValue = 0;
                // for the other number --> Inc/Decr functionning    <=63 OFF    >63 ON
            }
            else {
                m_TheCCPagesMIDIMappingTable[posi].number = 255;
                m_TheCCPagesMIDIMappingTable[posi].AXE_CC = 255;
            }
            m_pMidyAXDlgInstance->settings.endGroup();
        }
    }

    // Initialize the BLOWN-UP DISPLAY dialog
    if( m_dlgBlownUpParamDisplay == NULL) m_dlgBlownUpParamDisplay = new BlownUpParamDisplay;
    //m_timerDlgBlownUpParamDisplay = new QTimer(this);
    connect( &m_timerDlgBlownUpParamDisplay, SIGNAL(timeout()), this, SLOT(closeDlgBlownUpParamDisplay()) );

    m_timeLastValueChanged.start();
}

void MIDIControllerGenericDialogMOD1::closeDlgBlownUpParamDisplay()
{
    m_dlgBlownUpParamDisplay->hide();
    this->raise();
}

void MIDIControllerGenericDialogMOD1::startDlgBlownUpParamDisplayTimer()
{
//    m_pMidyAXDlgInstance->settings.beginGroup("BlownUp_Window");
//    restoreGeometry(m_pMidyAXDlgInstance->settings.value("BlownUp_Geometry").toByteArray());
//    m_pMidyAXDlgInstance->settings.endGroup();

    m_dlgBlownUpParamDisplay->show();
    if(g_displayBlownUp == true) m_dlgBlownUpParamDisplay->raise();
                            else m_dlgBlownUpParamDisplay->lower();
    m_timerDlgBlownUpParamDisplay.setSingleShot(true);
    m_timerDlgBlownUpParamDisplay.start(1500);
}


void MIDIControllerGenericDialogMOD1::setQEditVal(int value)
{
    int index, posi;
    QSliderMod1* obj = qobject_cast<QSliderMod1 *>( sender() );

    for( index = 0; index < m_numberOfSlidders + m_numberOfKnobs ; index++ )
    {
        if( obj == m_TheSliders[index]) break;
    }
    posi = index + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    if( m_ThePagesMIDIMappingTable[posi].effectParameterType == AXEFX_LOG_Parameter_Type_DEFINE )
    m_TheLineEdits[ index ]->setTextFromInt( m_ThePagesMIDIMappingTable[posi].paramDispValue  * 1000);
    else m_TheLineEdits[ index ]->setTextFromInt( value );
}

//void MIDIControllerGenericDialogMOD1::loadFactoryMapping( void)
//{
//    // Read Settings  --> load Factory Mapping Table

//    // Loads the local MAPPING table from included "static table"
//    for(int j = 0; j < m_numberOfPageSelectButtons; j++)
//    {
//        for(int i = 0; i < m_numberOfKnobs + m_numberOfSlidders + m_numberOfParameterButtons; i++)
//        {
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



MIDIControllerGenericDialogMOD1::~MIDIControllerGenericDialogMOD1()
{}


void MIDIControllerGenericDialogMOD1::init( void )
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
}

void MIDIControllerGenericDialogMOD1::connectWidgetOnDialog(void)
{
    // SIGNAL/SLOT connections
    for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs; i++)
    {
        m_setup = true;
        connect(m_TheLineEdits[i], SIGNAL(editingFinished(void)), this, SLOT(onLineEditEditingFinished(void)) );
        connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        //connect(m_TheSliders[i], SIGNAL(valueChanged( int )), m_TheLineEdits[i], SLOT( setTextFromInt(int)) );
        connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT( setQEditVal(int)) );
        connect(m_TheBlockLabels[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onCustomContextMenuRequested(const QPoint )) );
        connect(m_TheParamLabels[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onCustomContextMenuRequested(const QPoint )) );
        connect(m_TheLineEdits[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onCustomContextMenuRequested(const QPoint )) );
        connect(m_TheSliders[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onCustomContextMenuRequested(const QPoint )) );
    }
    for(int i=0; i < m_numberOfParameterButtons; i++)
    {
        connect(m_TheParameterPushButtons[i], SIGNAL(toggled(bool)), this, SLOT(onPushButtonToggled(bool)) );
        connect(m_TheParameterPushButtons[i], SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onCustomContextMenuRequested(const QPoint )) );
    }
}

void MIDIControllerGenericDialogMOD1::closeEvent(QCloseEvent * event)
{
    storeGeom();
    event->accept();
}

void MIDIControllerGenericDialogMOD1::accept()
{
    if( m_MIDIControllerNumber != 5) //for now : no select page button on FCB1010
    m_currentPage = m_PageSelectPBGroup->checkedId();
    else m_currentPage =0;

    storeGeom();
    QDialog::accept();
}

void MIDIControllerGenericDialogMOD1::reject()
{
    storeGeom();
    QDialog::reject();
}

void MIDIControllerGenericDialogMOD1::storeGeom()
{
    m_pMidyAXDlgInstance->settings.beginGroup(QSettings_win_geom_group_name);
    m_pMidyAXDlgInstance->settings.setValue(QSettings_win_geom, saveGeometry());
    m_pMidyAXDlgInstance->settings.endGroup();
}


//void MIDIControllerGenericDialogMOD1::constructWidgetLists( QObject *theDialog )
//{
//    QString widgetName = "lineEdit_";
//   fillWidgetList<QLineEditMod1>( &m_TheLineEdits, theDialog, &widgetName);
//}

void MIDIControllerGenericDialogMOD1::constructWidgetLists( QWidget **gridLayoutWidget )
{
    QString widgetName = "lineEdit_";
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
        m_ThePageSelectPushButtons[m_currentPage]->setChecked(true);

        if(  m_pMidyAXDlgInstance->m_theFMMIDIControllers[m_MIDIControllerNumber].controllerConnected == true )
        {
            for(int i=0; i < m_numberOfPageSelectButtons ; i++)
            {
                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, i+1, 0, m_MIDIControllerNumber);
            }
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, m_currentPage+1, 127, m_MIDIControllerNumber);
        }

        connect(m_PageSelectPBGroup, SIGNAL( buttonToggled(int, bool)), this, SLOT(onButtonGroupButtonPushed(int, bool)));
    }
}


void MIDIControllerGenericDialogMOD1::setSliderValue( int sliderIndex, double value)
{
    // ////////////////////////////////////
    // Function Specific for PARAM mapping
    if ( m_timeLastValueChanged.isValid() && m_timeLastValueChanged.elapsed() > 100 )
    {
        //double sentVal = value * double(1000);
        m_TheSliders[sliderIndex]->setValue( int( value * double(1000) ) );

        if( g_sliderColored )
        {
            int posi = sliderIndex + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );
            colorSlider( sliderIndex, m_ThePagesMIDIMappingTable[ posi ].MIDIValue );
        }
        //this->update();

        if( g_displayBlownUp )
        {
            QEvent* ev = 0;
            if( m_timerDlgBlownUpParamDisplay.isActive() == false ) this->raise();
            int posi = sliderIndex + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );
            m_dlgBlownUpParamDisplay->updateBlownUpParamDisplayMOD1( posi, m_ThePagesMIDIMappingTable, value, &m_MIDIControllerDialogName );
            ev = new BlownUpStartEvent( );
            QApplication::postEvent(this, ev);
        }
    }
}

void MIDIControllerGenericDialogMOD1::setSliderValue( int sliderIndex, int MIDIValue )
{
    // ///////////////////////////////////////
    // Function Specific for AXE-FX CC mapping
    QEvent* ev = 0;

    if ( m_timeLastValueChanged.isValid() && m_timeLastValueChanged.elapsed() > 100 )
    {
        m_TheSliders[sliderIndex]->setValue( MIDIValue );

        int posi = sliderIndex + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );
        colorSlider( sliderIndex, m_TheCCPagesMIDIMappingTable[ posi ].MIDIValue );
        this->update();

        if( g_displayBlownUp )
        {
            if( m_timerDlgBlownUpParamDisplay.isActive() == false ) this->raise();
            m_dlgBlownUpParamDisplay->show();
            m_dlgBlownUpParamDisplay->updateBlownUpParamDisplayMOD1( posi, m_TheCCPagesMIDIMappingTable, MIDIValue, &m_MIDIControllerDialogName );
            ev = new BlownUpStartEvent( );
            QApplication::postEvent(this, ev);
            //startDlgBlownUpParamDisplayTimer();
        }
    }
}



void MIDIControllerGenericDialogMOD1::colorSlider( int sliderIndex, int MIDIValue )
{
    if( g_sliderColored )
    {
        if( MIDIValue > 127 ||  MIDIValue < 0)
            m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(), QColor( 0, 0, 0, 0 ));
        else if( MIDIValue > 63)
            m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(),
                                     QColor(
                                         255,
                                         255 - ( (MIDIValue -63) * 3.9),
                                         255 - ( (MIDIValue -63) * 3.9),
                                         255)  );
         else
            m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(),
                                  QColor(
                                         255 - ( (63 - MIDIValue) * 3.9),
                                         255 - ( (63 - MIDIValue) * 3.9),
                                         255,
                                         255  )       );
        m_TheSliders[ sliderIndex ]->setPalette(m_slidderPalette);
    }
}



void MIDIControllerGenericDialogMOD1::onLineEditEditingFinished(void)
{
    QLineEditMod1* obj = qobject_cast<QLineEditMod1 *>( sender() );

    int i;
    for( i = 0; i < m_numberOfKnobs; i++ )
    {
        if( obj == m_TheLineEdits[i]) break;
    }
    //TODO: finish function
}


void MIDIControllerGenericDialogMOD1::onPushButtonToggled(bool checked)
{
    // ONLY process PB click from param PB not pageChange PB

    // Find the PushButton that has changed/clicked
    QPushButton* obj = qobject_cast<QPushButton *>( sender() );
    int index;
    for( index = 0; index < m_numberOfParameterButtons ; index++ )
    {
        if( obj == m_TheParameterPushButtons[index] ) break;
    }

    int posi;
    posi =   index
           + m_numberOfSlidders+ m_numberOfKnobs
           + ( ( m_numberOfSlidders+ m_numberOfKnobs+ m_numberOfParameterButtons)
                       * m_PageSelectPBGroup->checkedId()  );

    if( m_ThePagesMIDIMappingTable[posi].effectBlockID  != 255 )
    {
        m_pMidyAXDlgInstance->sendSYSEXtoAXEFX(
                    AXEFX_SYSEX_PARAM_SET_S,
                    m_ThePagesMIDIMappingTable[posi].effectBlockID,
                    m_ThePagesMIDIMappingTable[posi].effectParameterID,
                    m_ThePagesMIDIMappingTable[posi].effectParameterType,
                    ((int)checked) *127);
    }
    else if( m_TheCCPagesMIDIMappingTable[posi].number  != 255 )
    {
        m_pMidyAXDlgInstance->sendCCtoMIDIout(
                                    m_pMidyAXDlgInstance->m_AXEFXChanNumb,
                                    m_TheCCPagesMIDIMappingTable[posi].AXE_CC,
                                    ((int)checked) *127,
                                    0 /* AXE-FX */);
    }
}


void MIDIControllerGenericDialogMOD1::onSliderValueChanged( int val )
{
    // Process the changes in param/cc value from the Slidders (Slidders or Knobs elements)

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

    if( m_ThePagesMIDIMappingTable[posi].effectBlockID  != 255 )
    {

        // Calculate corresponding MIDI value
        double convertedValue = double(val) / double(1000);
        convertedValue -= double(m_ThePagesMIDIMappingTable[posi].minDispValue);
        convertedValue /= double((m_ThePagesMIDIMappingTable[posi].maxDispValue - m_ThePagesMIDIMappingTable[posi].minDispValue) );
        convertedValue *= double(127);
        convertedValue += double(0.5);
        m_ThePagesMIDIMappingTable[posi].MIDIValue = int(convertedValue);

        // Send new value to AXE-FX and current MIDI controller
        if(    ( ( m_pMidyAXDlgInstance->m_MIDIIN_timer.elapsed() > 3000 && m_pMidyAXDlgInstance->m_MIDIIN_timer.isValid()) || !m_pMidyAXDlgInstance->m_MIDIIN_timer.isValid() )
            && m_initMode_timer.elapsed() > 1000 )
        {
            // Sends SYSEX to AXE-FX
            m_pMidyAXDlgInstance->sendSYSEXtoAXEFX( AXEFX_SYSEX_PARAM_SET_S,
                                  m_ThePagesMIDIMappingTable[posi].effectBlockID,
                                  m_ThePagesMIDIMappingTable[posi].effectParameterID,
                                  m_ThePagesMIDIMappingTable[posi].effectParameterType,
                                  m_ThePagesMIDIMappingTable[posi].MIDIValue );

            // Sends CC to connected MIDI device
//            if( m_pMidyAXDlgInstance->m_theFMMIDIControllers[ m_MIDIControllerNumber ].controllerConnected == true )
//            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel,      // uses MIDI channel m_fixedParamControlMIDIChannel (set at init) for sending param control
//                                                   index+1,
//                                                   m_ThePagesMIDIMappingTable[posi].MIDIValue,
//                                                   m_MIDIControllerNumber);

            //TODO: check if param is mapped on other MIDI controller --> update value
        }

        //TODO: ckeck if the following should be inside the preceeding if block
        double reConvertedValue = m_ThePagesMIDIMappingTable[posi].MIDIValue;
        reConvertedValue /= 127;
        reConvertedValue *= ( m_ThePagesMIDIMappingTable[posi].maxDispValue - m_ThePagesMIDIMappingTable[posi].minDispValue );
        reConvertedValue += m_ThePagesMIDIMappingTable[posi].minDispValue;
        m_ThePagesMIDIMappingTable[posi].paramDispValue = reConvertedValue;

        // Store the new paramDispValue and MIDIValue for use in other displays ( in m_theMappingTable - the main mapping table )
        for(int i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++)
        {
            if(  m_pMidyAXDlgInstance->m_theMappingTable[i].effectBlockID == m_ThePagesMIDIMappingTable[posi].effectBlockID
             && m_pMidyAXDlgInstance->m_theMappingTable[i].effectParameterID == m_ThePagesMIDIMappingTable[posi].effectParameterID )
            {
                m_pMidyAXDlgInstance->m_theMappingTable[i].paramDispValue = m_ThePagesMIDIMappingTable[posi].paramDispValue;
                m_pMidyAXDlgInstance->m_theMappingTable[i].MIDIValue = int(convertedValue);
            }
        }
        colorSlider( index,  m_ThePagesMIDIMappingTable[posi].MIDIValue );
    }
    else if( m_TheCCPagesMIDIMappingTable[posi].number  != 255  )
    {
        if(   (( m_pMidyAXDlgInstance->m_MIDIIN_timer.elapsed() > 3000 && m_pMidyAXDlgInstance->m_MIDIIN_timer.isValid()) || !m_pMidyAXDlgInstance->m_MIDIIN_timer.isValid())
           && m_initMode_timer.elapsed() > 1000 )
        {
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_pMidyAXDlgInstance->m_AXEFXChanNumb,      // uses MIDI channel m_fixedParamControlMIDIChannel (set at init) for sending param control
                                                   m_TheCCPagesMIDIMappingTable[posi].AXE_CC,
                                                   val,
                                                   0 /* AXE-FX */);
            m_TheCCPagesMIDIMappingTable[posi].MIDIValue = val;


            // Sends CC to connected MIDI device
            if( m_pMidyAXDlgInstance->m_theFMMIDIControllers[ m_MIDIControllerNumber ].controllerConnected == true )
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel,      // uses MIDI channel m_fixedParamControlMIDIChannel (set at init) for sending param control
                                                   index+1,
                                                   m_TheCCPagesMIDIMappingTable[posi].MIDIValue,
                                                   m_MIDIControllerNumber);
        }
        colorSlider( index,  m_TheCCPagesMIDIMappingTable[posi].MIDIValue );
    }
        m_timeLastValueChanged.start();
}   

void MIDIControllerGenericDialogMOD1::setValue( quint8 page, quint8 elementNumber, double paramDispValue)
{
    bool buttonState;

    if( m_PageSelectPBGroup->checkedId() != page) return;

    if( elementNumber < m_numberOfSlidders + m_numberOfKnobs )
    {
        setSliderValue( elementNumber , paramDispValue  );
    }
    else {
        int posi = elementNumber + (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * page;
        if( m_ThePagesMIDIMappingTable[ posi ].MIDIValue <= 63 ) buttonState = false;
        else buttonState = true;

        m_TheParameterPushButtons[ elementNumber - ( m_numberOfSlidders + m_numberOfKnobs ) ]->setChecked( buttonState );
    }

    this->update();
}





void MIDIControllerGenericDialogMOD1::setValueIfMapped( int number, int CCVal )
{
    int posi = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId();
    int slidderNumb, buttonNumb;
    bool buttonState;

    // On the current page of the MIDI controller dialog look if the mapping exits --> if yes update value
    for( int i=posi ; i < posi+ m_numberOfSlidders + m_numberOfKnobs ; i++)
    {
        if( m_TheCCPagesMIDIMappingTable[i].number == number)
        {
            slidderNumb = i - posi;
            //disconnect(m_TheSliders[ slidderNumb ], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
            setSliderValue( slidderNumb , CCVal  );
            //connect(m_TheSliders[ slidderNumb ], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
            this->update();
            break;
        }
    }

    //Check if the updated param is mapped to a paramButton --> update display
    posi = posi+ m_numberOfSlidders + m_numberOfKnobs;
    for( int i= posi ; i < posi+ m_numberOfParameterButtons  ; i++)
    {
        if( m_TheCCPagesMIDIMappingTable[i].number == number)
        {
            buttonNumb = i - posi;

            if( m_TheCCPagesMIDIMappingTable[i].MIDIValue <= 63 ) buttonState = false;
            else buttonState = true;

            m_TheParameterPushButtons[ buttonNumb ]->setChecked( buttonState );
            break;
        }
    }
}


void MIDIControllerGenericDialogMOD1::onCustomContextMenuRequested(const QPoint &pos)
{
    QWidget* obj = qobject_cast<QWidget *>( sender() );

    // Search and store the slidder on whitch the Menu was requested
    // and store it for use by the reception function setParameterMapping
    int i;
    for( i=0 ; i < m_numberOfKnobs + m_numberOfSlidders; i++)
    {
        if(       obj == (QWidget *) m_TheSliders[i]
               || obj == (QWidget *) m_TheLineEdits[i]
               || obj == (QWidget *) m_TheBlockLabels[i]
               || obj == (QWidget *) m_TheParamLabels[i]   )
        {
            m_controlNumberForContextMenu = i;
            break;
        }
    }

    // Remmbers the position of the click --> to display dialog at it
    m_CurrentPosition = this->pos() + obj->pos() + pos;

    if( i == m_numberOfKnobs + m_numberOfSlidders )
    {
        for( i=0 ; i < m_numberOfParameterButtons; i++)
        {
            if( obj == (QWidget *) m_TheParameterPushButtons[i]    )
            {
                m_controlNumberForContextMenu = m_numberOfKnobs + m_numberOfSlidders + i;
                break;
            }

        }
    }

    // Create the Context Menu
    QMenu *menu=new QMenu(this);
    setParamMapping = new QAction("Map AXE-FX parameter", this);
    dispParamInfo = new QAction("Display current parameter info", this);
    setCCMapping = new QAction("Map AXE-FX CC", this);
    clearMap = new QAction("Clear Mapping", this);

    menu->addAction( setParamMapping);
    menu->addAction( setCCMapping);
    menu->addAction( dispParamInfo);
    menu->addAction( clearMap);

    // Enable/disable Menu items
    dispParamInfo->setEnabled(false);
    int posi = m_controlNumberForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );
    if( m_ThePagesMIDIMappingTable[posi].effectBlockID != 255)  setCCMapping->setEnabled( false );
    if( m_TheCCPagesMIDIMappingTable[posi].number != 255)  setParamMapping->setEnabled( false );
    if( m_ThePagesMIDIMappingTable[posi].effectBlockID == 255 && m_TheCCPagesMIDIMappingTable[posi].number == 255)  clearMap->setEnabled( false );

    // Connect the menu items to the right functions
    connect( setParamMapping, SIGNAL(triggered()), this, SLOT( setParameterMapping() ) );
    //connect( dispParamInfo, SIGNAL(triggered()), this, SLOT( dipParamInfo() ) );
    //TODO: program the function dipParamInfo()
    connect( setCCMapping, SIGNAL(triggered()), this, SLOT( setAXEFXCCMapping() ) );
    connect( clearMap, SIGNAL(triggered()), this, SLOT( clearMapping() ) );

    // Display the Context Menu
    menu->popup( obj->mapToGlobal(pos));
}


//void MIDIControllerGenericDialogMOD1::midiLearnIt(void)
//{
//    // Manage Learn mode !!!
//    int posi = m_currentSliderForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

//    g_learnMode = true;
//    g_learn_paramDispValue = m_TheMIDIMappingTable[ posi ].paramDispValue;
//    g_learn_MIDIValue = m_TheMIDIMappingTable[ posi ].MIDIValue;
//    //g_learn_callingDialog = 3;
//    gp_learn_callingDialog = (QWidget *) this;
//}


//void MIDIControllerGenericDialogMOD1::updateWithLearnedMapping( unsigned char learnedChannel, int learnedCC )
//{
//    bool found = false;

//    if( gp_learn_callingDialog != this ) return;

//    // TODO : Check if the mapping item already exists
//    for(int i = 0; i < m_pMidyAXDlgInstance->m_numbOfMappings ; i++)
//    {
//        if(    learnedChannel+1 == m_pMidyAXDlgInstance->m_theMappingTable[i].chanNumb
//            && learnedCC == m_pMidyAXDlgInstance->m_theMappingTable[i].CCID  )
//        {
//            found = true;
//            g_learnMode = false;
//            g_learnModeCount = 0;
//            g_learnModeChan = 0;
//            g_learnModeCC = 255;
//            break;
//        }
//    }
//    if( found )
//    {
//        QMessageBox* msgBox 	= new QMessageBox();
//        msgBox->setWindowTitle("Cannot add this mapping");
//        msgBox->setText("This Channel/CC couple is allready mapped");
//        msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
//        msgBox->exec();
//        return;
//    }

//    int posi = m_currentSliderForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

//    m_ThePagesMIDIMappingTable[ posi ].chanNumb = learnedChannel + 1;
//    m_ThePagesMIDIMappingTable[ posi ].CCID = learnedCC;

//    int qcomboIndex = m_TheComboBoxs[ posi ]->itemData( m_TheComboBoxs[ posi ]->currentIndex() ).toInt();
//    m_pMidyAXDlgInstance->m_theMappingTable[qcomboIndex].chanNumb = learnedChannel + 1;
//    m_pMidyAXDlgInstance->m_theMappingTable[qcomboIndex].CCID = learnedCC;
//    m_pMidyAXDlgInstance->fillCCtoAXE();
//    m_ThePagesMIDIMappingTable[ posi ].paramDispValue = g_learn_paramDispValue;
//    m_ThePagesMIDIMappingTable[ posi ].MIDIValue = g_learn_MIDIValue;
//    setSliderValue( m_currentSliderForContextMenu, m_ThePagesMIDIMappingTable[ posi ].paramDispValue);



//    if( m_TheMIDIMappingTable[posi].chanNumb - 1 > -1 )
//    m_pMidyAXDlgInstance->sendCCtoMIDIout( m_ThePagesMIDIMappingTable[posi].chanNumb - 1,
//                                m_ThePagesMIDIMappingTable[posi].CCID,
//                                m_ThePagesMIDIMappingTable[posi].MIDIValue,
//                                m_MIDIControllerNumber);

//    QMessageBox* msgBox = new QMessageBox();
//    msgBox->setWindowTitle("From MidyAX");
//    msgBox->setText("Learn Finished");
//    msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
//    msgBox->exec();
//    g_learnMode = false;
//    g_learnModeCount = 0;
//    g_learnModeChan = 0;
//    g_learnModeCC = 255;
//}

void MIDIControllerGenericDialogMOD1::setParameterMapping(void)
{
    int posi = m_controlNumberForContextMenu + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

    m_dlgParamMappingMOD1 = new ParamMappingMOD1(m_pMidyAXDlgInstance);

    // If the current mapping is empty pre-load dialog with the one next to it
    if( m_ThePagesMIDIMappingTable[posi].effectBlockID == 255  && posi != 0)
          m_dlgParamMappingMOD1->init( & (m_ThePagesMIDIMappingTable[ posi - 1 ])  );
    else
          m_dlgParamMappingMOD1->init( & (m_ThePagesMIDIMappingTable[ posi ])  );

    m_dlgParamMappingMOD1->move( m_CurrentPosition ); //Does not position it right

    if ( m_dlgParamMappingMOD1->exec() == QDialog::Accepted )
    {
        //Adds the mapping into the pageMappingtable at position posi
        m_dlgParamMappingMOD1->get_paramMapping(  & (m_ThePagesMIDIMappingTable[ posi ])   );

        // Add the mapping to the fast correspondance table MIDIContActMap
        for(int a=0; a < AXEFX_MAX_NumberOf_SameMappingPerMIDIController_DEFINE; a++)
        {
            if( m_pMidyAXDlgInstance->MIDIContActMap[ m_MIDIControllerNumber - 1 ]
                                                    [ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100]
                                                    [ m_ThePagesMIDIMappingTable[posi].effectParameterID ]
                                                    [0][a] == 255 ) //Stops as soon as one element has "empty" value
            {
                m_pMidyAXDlgInstance->MIDIContActMap[ m_MIDIControllerNumber -1 ]
                                             [ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100 ]
                                             [ m_ThePagesMIDIMappingTable[posi].effectParameterID ][ 0 ][a] = m_PageSelectPBGroup->checkedId() ;
                m_pMidyAXDlgInstance->MIDIContActMap[ m_MIDIControllerNumber -1 ]
                                             [ m_ThePagesMIDIMappingTable[posi].effectBlockID - 100 ]
                                             [ m_ThePagesMIDIMappingTable[posi].effectParameterID ][ 1 ][a] = m_controlNumberForContextMenu;
                break;
            }
        }


        //Get value of new param from AXE-FX
        m_pMidyAXDlgInstance->sendSYSEXtoAXEFX( AXEFX_SYSEX_PARAM_SET_Q,
                                                m_ThePagesMIDIMappingTable[posi].effectBlockID,
                                                m_ThePagesMIDIMappingTable[posi].effectParameterID);
        delay(100);

        // Update the value of the controller
        int posi,page;
        page = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId();

        posi = m_controlNumberForContextMenu + ( page );
        if( m_ThePagesMIDIMappingTable[posi].effectBlockID !=255 ) //Added because call to on_Slider_valueChanged on UI init
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel, // uses MIDI channel 1 for sending param control
                                                   m_controlNumberForContextMenu+1,
                                                   m_ThePagesMIDIMappingTable[posi].MIDIValue,
                                                   m_MIDIControllerNumber);
        else
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel, // uses MIDI channel 1 for sending param control,
                                          m_controlNumberForContextMenu+1,
                                          0,
                                          m_MIDIControllerNumber);
        updateKnobsDisplay();
        // TODO : Build an init for one Slidder/Knob
    }
    this->raise();
}


void MIDIControllerGenericDialogMOD1::  clearMapping(void)
{
    int posi,page;
    page = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId();
    posi = m_controlNumberForContextMenu + ( page );

    m_TheCCPagesMIDIMappingTable[posi].number = 255;
    m_ThePagesMIDIMappingTable[posi].effectBlockID = 255;

    updateKnobsDisplay();
    this->update();
    this->raise();
}



void MIDIControllerGenericDialogMOD1::setAXEFXCCMapping(void)
{
    int posi,page;
    page = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId();
    posi = m_controlNumberForContextMenu + ( page );

    m_dlgCCMapping = new CCMapping(m_pMidyAXDlgInstance);

    // If the current mapping is empty pre-load dialog with the one next to it
    if( m_TheCCPagesMIDIMappingTable[posi].number == 255 && posi != 0)
          m_dlgCCMapping->init( & (m_TheCCPagesMIDIMappingTable[ posi - 1 ])  );
    else
          m_dlgCCMapping->init( & (m_TheCCPagesMIDIMappingTable[ posi ])  );

    // Position dialog
    m_dlgCCMapping->move( m_CurrentPosition ); //TODO: FIX, Does not position it right

    // Exec dialog
    if ( m_dlgCCMapping->exec() == QDialog::Accepted )
    {
        //Adds the mapping into the pageMappingtable at position posi
        m_dlgCCMapping->get_paramMapping(  & (m_TheCCPagesMIDIMappingTable[ posi ])   );

        //Set Initial value
        //Bypass, Tempo, Tuner, Ext Contr, Looper controls, scene select
        if( m_TheCCPagesMIDIMappingTable[ posi ].number >= 4 && m_TheCCPagesMIDIMappingTable[ posi ].number <= 28 ) m_TheCCPagesMIDIMappingTable[ posi ].MIDIValue = 0;
        // Effect Block ON/Bypass and X/Y
        if( m_TheCCPagesMIDIMappingTable[ posi ].number >= 33 && m_TheCCPagesMIDIMappingTable[ posi ].number <= 115 ) m_TheCCPagesMIDIMappingTable[ posi ].MIDIValue = 0;
        // for the other number --> Inc/Decr functionning    <=63 OFF    >63 ON


        // Update the value on the controller
        if( m_TheCCPagesMIDIMappingTable[posi].number !=255 ) //Added because call to on_Slider_valueChanged on UI init
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel, // uses MIDI channel 1 for sending param control
                                                   m_controlNumberForContextMenu+1,
                                                   m_TheCCPagesMIDIMappingTable[posi].MIDIValue,
                                                   m_MIDIControllerNumber);
        else
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel,
                                          m_controlNumberForContextMenu+1,
                                          0,
                                          m_MIDIControllerNumber);
        updateKnobsDisplay();
        // TODO : Build an init for one Slidder/Knob
    }
    this->raise();
}

void MIDIControllerGenericDialogMOD1::updateKnobsDisplay(void)
{
    // Updates the KNOBs and SLIDDERs display on the MIDI Controller dialog

    int posi;
    m_setup = true; // Avoid slidder display updates that call onSlidderValueChnaged

    for(int i=0; i < m_numberOfKnobs + m_numberOfSlidders ; i++)
    {
        posi = i + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

        if( m_ThePagesMIDIMappingTable[posi].effectBlockID != 255 )
        {
            QFont tempFont1("DejaVu Sans Condensed", 14, QFont::Bold);
            QFont tempFont2("DejaVu Sans Condensed", 10, QFont::Bold);
            QFont tempFont3("DejaVu Sans Condensed", 14);
            QFont tempFont4("DejaVu Sans Condensed", 10);

            if( strlen(m_ThePagesMIDIMappingTable[posi].effectBlockLabel) < 9)
                m_TheBlockLabels[i]->setFont(tempFont3);
            else m_TheBlockLabels[i]->setFont(tempFont4);
            m_TheBlockLabels[i]->setText( m_ThePagesMIDIMappingTable[posi].effectBlockLabel);

            if( strlen(m_ThePagesMIDIMappingTable[posi].effectParameterLabel) < 12)
                    m_TheParamLabels[i]->setFont(tempFont1);
            else    m_TheParamLabels[i]->setFont(tempFont2);
            m_TheParamLabels[i]->setText( m_ThePagesMIDIMappingTable[posi].effectParameterLabel );

            m_TheSliders[i]->setMinimum( m_ThePagesMIDIMappingTable[posi].minDispValue * 1000);
            m_TheSliders[i]->setMaximum( m_ThePagesMIDIMappingTable[posi].maxDispValue * 1000);
            m_TheSliders[i]->setTickInterval( (m_ThePagesMIDIMappingTable[posi].maxDispValue - m_ThePagesMIDIMappingTable[posi].minDispValue) * 50);
            m_TheSliders[i]->setSingleStep( (m_ThePagesMIDIMappingTable[posi].maxDispValue - m_ThePagesMIDIMappingTable[posi].minDispValue) * 10 );
            m_TheSliders[i]->setPageStep( (m_ThePagesMIDIMappingTable[posi].maxDispValue - m_ThePagesMIDIMappingTable[posi].minDispValue)  * 100);
            m_TheSliders[i]->setEnabled( true );

            // Display of Min/max value for Slidder controls
            if( i <m_numberOfSlidders )
            {
                m_TheMinLabels[i]->setText( QString::number(m_ThePagesMIDIMappingTable[posi].minDispValue) );
                m_TheMaxLabels[i]->setText( QString::number(m_ThePagesMIDIMappingTable[posi].maxDispValue) );
            }
            m_TheSliders[i]->setValue( m_ThePagesMIDIMappingTable[posi].paramDispValue * 1000 );
            colorSlider( i , m_ThePagesMIDIMappingTable[posi].MIDIValue );
        }
        else if( m_TheCCPagesMIDIMappingTable[posi].number != 255 )
        {
            m_TheBlockLabels[i]->setText( "CTRL CC");
            m_TheParamLabels[i]->setText( m_TheCCPagesMIDIMappingTable[posi].controlName );
            m_TheSliders[i]->setMinimum( 0 );
            m_TheSliders[i]->setMaximum( 127 );
            m_TheSliders[i]->setTickInterval( 12 );
            m_TheSliders[i]->setSingleStep( 5 );
            m_TheSliders[i]->setPageStep( 12 );
            m_TheSliders[i]->setEnabled( true );

            // Display of Min/max value for Slidder controls
            if( i <m_numberOfSlidders )
            {
                m_TheMinLabels[i]->setText( QString::number( 0 ) );
                m_TheMaxLabels[i]->setText( QString::number( 127 ) );
            }
            m_TheSliders[i]->setValue( m_TheCCPagesMIDIMappingTable[posi].MIDIValue );
            colorSlider( i , m_TheCCPagesMIDIMappingTable[posi].MIDIValue );
        }
        else {
            m_TheBlockLabels[i]->setText( QString::number(i+1) );
            m_TheParamLabels[i]->setText( "" );
            m_TheSliders[i]->setMinimum( 0 );
            m_TheSliders[i]->setMaximum( 0 );
            m_TheSliders[i]->setTickInterval( 0 );
            m_TheSliders[i]->setSingleStep( 0 );
            m_TheSliders[i]->setPageStep( 0);

            // Display of Min/max value for Slidder controls
            if( i <m_numberOfSlidders )
            {
                m_TheMinLabels[i]->setText( QString::number( 0 ) );
                m_TheMaxLabels[i]->setText( QString::number( 0 ) );
            }
            m_TheSliders[i]->setValue( m_ThePagesMIDIMappingTable[posi].paramDispValue * 1000 );
            colorSlider( i , m_ThePagesMIDIMappingTable[posi].MIDIValue );
        }
        m_TheSliders[i]->setAutoFillBackground(true);
    }

    m_setup = false; // Stops avoiding slidder display updates that call onSlidderValueChnaged
    bool PBIsChecked;

    for(int i=0; i < m_numberOfParameterButtons ; i++)
    {
        posi =    i
                + ( m_numberOfKnobs + m_numberOfSlidders )
                + ( (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * m_PageSelectPBGroup->checkedId() );

        if( m_ThePagesMIDIMappingTable[posi].effectBlockID != 255 )
        {
            m_TheParameterPushButtons[i]->setText(   m_ThePagesMIDIMappingTable[posi].effectBlockLabel
                                                   + QString(" / ")
                                                   + m_ThePagesMIDIMappingTable[posi].effectParameterLabel);

            if( m_ThePagesMIDIMappingTable[posi].MIDIValue <= 63) PBIsChecked = false;
            else PBIsChecked = true;
            m_TheParameterPushButtons[i]->setChecked( PBIsChecked );
        }
        else if( m_TheCCPagesMIDIMappingTable[posi].number != 255 )
        {
            if( m_MIDIControllerNumber == FCB1010_MC )
            m_TheParameterPushButtons[i]->setText( QString("CTRL CC\n/\n") + m_TheCCPagesMIDIMappingTable[posi].controlName );
            else
            m_TheParameterPushButtons[i]->setText( QString("AXECC/") + m_TheCCPagesMIDIMappingTable[posi].controlName );

            if( m_TheCCPagesMIDIMappingTable[posi].MIDIValue <= 63) PBIsChecked = false;
            else PBIsChecked = true;
            m_TheParameterPushButtons[i]->setChecked( PBIsChecked );

        }
        else {
            // Case - No mapping
            m_TheParameterPushButtons[i]->setText(  QString::number(i+1) );
            m_TheParameterPushButtons[i]->setChecked( false );
        }
    }

    this->update();
}


void MIDIControllerGenericDialogMOD1::processCC( int chanNumb, int CCID, int MIDIValue )
{
    // Process the page change request (on channel 16)
    if( /*chanNumb == m_fixedPageControlMIDIChannel &&*/ CCID <= m_numberOfPageSelectButtons )
    {
        processPageChangeRequest( CCID, MIDIValue );
    }

    // Process the EffectBlock ON/OFF request (on channel 15)
//    if( chanNumb == 14 && CCID <= m_numberOfPageSelectButtons )
//    {
//        //process the pushButtons
//        //processPageChangeRequest( CCID, MIDIValue );
//    }
}

void MIDIControllerGenericDialogMOD1::processPageChangeRequest( int CCID, int MIDIValue )
{
    int currentON = m_PageSelectPBGroup->checkedId()+1;

    // If request OFF for currentON refuse and set currentON back ON
    if( CCID == currentON && MIDIValue <= 63 )
    {
        // Send CC to right device with OFF for CCID
        m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, CCID, 127, m_MIDIControllerNumber);

        // Put the dialog on top
        this->raise();
        this->update();
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
        m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, currentON, 0, m_MIDIControllerNumber);
        m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, CCID, 127, m_MIDIControllerNumber);

        // Update display
        m_ThePageSelectPushButtons[CCID-1]->setChecked(true);

        // RE-Connect the signals
        for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
        {
            connect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        }

        // Put the dialog on top
        this->raise();
        this->update();
    }
}

void MIDIControllerGenericDialogMOD1::onButtonGroupButtonPushed(int id, bool checked)
{
    // Two signal buttonToggled (checked and unchecked) are send when changing the ON PB. Only one (checked) is processed.

    //int device;
    if( checked == true )
    {
        m_currentPage = m_PageSelectPBGroup->checkedId();
        // Disconnect the signals to avoid multiple updating
        for(int i=0; i < m_numberOfSlidders + m_numberOfKnobs ; i++)
        {
            disconnect(m_TheSliders[i], SIGNAL(valueChanged( int )), this, SLOT(onSliderValueChanged(int)) );
        }

        // Update the Page Control buttons status
        for(int i = 0; i < m_numberOfPageSelectButtons; i++)//
        {
            m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, i+1, 0, m_MIDIControllerNumber);
        }
        m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedPageControlMIDIChannel, id+1, 127, m_MIDIControllerNumber);

        // Update the Value of the controllers
        int posi,page;
        page = (m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons) * id;
        for(int i= 0; i < m_numberOfSlidders + m_numberOfKnobs + m_numberOfParameterButtons; i++ )
        {
            posi = i + ( page );
            if( m_ThePagesMIDIMappingTable[posi].effectBlockID !=255 ) //Added because call to on_Slider_valueChanged on UI init
                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel, // uses MIDI channel 1 for sending param control
                                                       i+1,
                                                       m_ThePagesMIDIMappingTable[posi].MIDIValue,
                                                       m_MIDIControllerNumber);
            else
                m_pMidyAXDlgInstance->sendCCtoMIDIout( m_fixedParamControlMIDIChannel, // uses MIDI channel 1 for sending param control,
                                              i+1,
                                              0,
                                              m_MIDIControllerNumber);

        }
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


void MIDIControllerGenericDialogMOD1::showEvent(QShowEvent * event)
{
    //Use to refresh the de dialog display before it beeing shown
    event->setAccepted(true);
    if( m_MIDIControllerNumber != 5) //for now : no select page button on FCB1010
    m_ThePageSelectPushButtons[ m_currentPage ]->click();   // Should trigger clicked signal, and check the button
}



void MIDIControllerGenericDialogMOD1::customEvent ( QEvent *event )
{
    //QString MIDI_Message = QString("Message Received" );
    //ui.logMIDI->append(MIDI_Message);
    //qDebug() << "customEvent:" << event->type();

    if( event->type() ==  65526/*IHMSetValEventType*/) {
        IHMSetValEvent *ev = static_cast<IHMSetValEvent *>(event);
        setValue( ev->getPageNumb(), ev->getElemNumb(), ev->getDispValue() );
        event->accept();
    }
    else if( event->type() ==  BlownUpStartEventType) {
        startDlgBlownUpParamDisplayTimer();
        event->accept();
    }
    else if( event->type() ==  BlownUpStopEventType) {
        closeDlgBlownUpParamDisplay();
        event->accept();
    }
    else {
        event->ignore();
    }
}
