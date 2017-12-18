#include <QCloseEvent>

#include "bcf2000.h"


BCF2000::BCF2000(QWidget *parent) :
    MIDIControllerGenericDialogMOD1(parent, QString("BCF2000"), BCF2000_MC, 8, 8, 8, 16), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::BCF2000)
{
    ui->setupUi(this);
    init();
}

BCF2000::~BCF2000()
{
    delete ui;
}


void BCF2000::init( void)
{
    m_initMode = true;
    m_initMode_timer.start();

    MIDIControllerGenericDialogMOD1::init( );

    constructWidgetLists( &ui->gridLayoutWidget );

    connectWidgetOnDialog();

    // Initiate the KNOBS elements
    // fillComboBox(); //TODO: reactivate for non-fixed mapping use
    updateKnobsDisplay();

    m_initMode = false;
    this->update();
}



