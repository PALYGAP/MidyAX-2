#include <QCloseEvent>
#include <QtUiTools/QtUiTools>

#include "QuNeo.h"

QuNeo::QuNeo(QWidget *parent) :
    MIDIControllerGenericDialogMOD1(parent, QString("QUNEO"), QUNEO_MC, 2, 0, 10, 10), //m_numberOfKnobs,  m_numberOfSlidders, m_numberOfParameterButtons, m_numberOfPageSelectButtons
    ui(new Ui::QuNeo)
{
    ui->setupUi(this);
    init();
}

QuNeo::~QuNeo()
{
    delete ui;
}

void QuNeo::init( void)
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


//QWidget* QuNeo::loadUiFile()
//{
//    QUiLoader loader;

//    QFile file(":/forms/vQuNeo.ui");
//    file.open(QFile::ReadOnly);

//    QWidget *formWidget = loader.load(&file, this);
//    file.close();

//    return formWidget;
//}
