#include <QCloseEvent>

#include "BeatStep.h"

BeatStep::BeatStep(QWidget *parent) :
    MIDIControllerGenericDialogMOD1(parent, QString("BEATSTEP"), BEATSTEP_MC, 17, 0, 0, 16), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::BeatStep)
{
    ui->setupUi(this);
    init();
}

BeatStep::~BeatStep()
{
    delete ui;
}

void BeatStep::init( void)
{
   m_initMode = false;
   m_initMode_timer.start();

   m_initMode = true;
   MIDIControllerGenericDialogMOD1::init( );

   constructWidgetLists( &ui->gridLayoutWidget );

   connectWidgetOnDialog();

   // Initiate the KNOBS elements
   // fillComboBox(); //TODO: reactivate for non-fixed mapping use
   updateKnobsDisplay();

   m_initMode = false;
   this->repaint();

}
