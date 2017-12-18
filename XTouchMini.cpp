#include <QCloseEvent>

#include "XTouchMini.h"


XTouchMini::XTouchMini(QWidget *parent) :
    //After MOD1 ---- MIDIControllerGenericDialog(parent, QString("X-TOUCH"), XTOUCHMINI_MC, 8, 0, 8, 16), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    MIDIControllerGenericDialogMOD1(parent, QString("X-TOUCH"), XTOUCHMINI_MC, 8, 0, 8, 16), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::XTouchMini)
{
    ui->setupUi(this);
    init();
}

XTouchMini::~XTouchMini()
{
    delete ui;
}

void XTouchMini::init( void)
{
    m_initMode = true;
    m_initMode_timer.start();

    //After MOD1 ---- MIDIControllerGenericDialog::init( );
    MIDIControllerGenericDialogMOD1::init( );

    constructWidgetLists( &ui->gridLayoutWidget );

    connectWidgetOnDialog();

    // Initiate the KNOBS elements
    //after MOD1 ---- fillComboBox();
    updateKnobsDisplay();

    m_initMode = false;
    this->update();
}
