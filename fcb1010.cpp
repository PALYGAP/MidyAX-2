#include "fcb1010.h"
#include "ui_fcb1010.h"


FCB1010::FCB1010(QWidget *parent) :
    MIDIControllerGenericDialogMOD1(parent, QString("FCB1010"), FCB1010_MC, 2, 0, 10, 10), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::FCB1010)
{
    ui->setupUi(this);
    init();
}

FCB1010::~FCB1010()
{
    delete ui;
}

void FCB1010::init( void)
{
    m_initMode = true;
    m_initMode_timer.start();

    MIDIControllerGenericDialogMOD1::init();

    constructWidgetLists( &ui->gridLayoutWidget );

    MIDIControllerGenericDialogMOD1::connectWidgetOnDialog(); //TODO : Check why use base class fuction --> nees to overload it ?

   // Initiate the KNOBS elements
   updateKnobsDisplay();

   m_initMode = false;
   this->repaint();
}
