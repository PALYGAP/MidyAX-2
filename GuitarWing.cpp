#include <QCloseEvent>

#include "GuitarWing.h"

GuitarWing::GuitarWing(QWidget *parent) :
    MIDIControllerGenericDialogMOD1(parent, QString("GUITARWING"), GUITARWING_MC, 10, 0, 10, 4), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::GuitarWing)
{
    ui->setupUi(this);
    init();
}

GuitarWing::~GuitarWing()
{
    delete ui;
}

void GuitarWing::init( void)
{
   m_initMode = false;
   m_initMode_timer.start();

   m_initMode = true;
   MIDIControllerGenericDialogMOD1::init( );

   constructWidgetLists( &ui->dialogWidget );

   connectWidgetOnDialog();

   // Initiate the KNOBS elements
   // fillComboBox(); //TODO: reactivate for non-fixed mapping use
   updateKnobsDisplay();

   m_initMode = false;
   this->repaint();

}
