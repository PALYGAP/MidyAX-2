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

#include "blownupparamdisplay.h"
#include "ui_blownupparamdisplay.h"

BlownUpParamDisplay::BlownUpParamDisplay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlownUpParamDisplay)
{
    ui->setupUi(this);

    connect(ui->verticalSlider_blownup, SIGNAL(valueChanged( int )), ui->lineEdit_1, SLOT( setTextFromInt(int)) );

    m_slidderPalette.setColor(QPalette::Window, QColor(255, 255, 255));
    ui->verticalSlider_blownup->setAutoFillBackground(true);
    ui->verticalSlider_blownup->setPalette(m_slidderPalette);
}

BlownUpParamDisplay::~BlownUpParamDisplay()
{
    delete ui;
}

void BlownUpParamDisplay::hideEvent(QHideEvent *event)
{
    //Store position
    m_geom = saveGeometry();
}

void BlownUpParamDisplay::showEvent(QShowEvent *event)
{
    //Store position
    restoreGeometry( m_geom);
}


void BlownUpParamDisplay::updateBlownUpParamDisplay( int posi, struct mappingTable theMappingTable[], double paramValue )
{
    ui->verticalSlider_blownup->setMinimum( theMappingTable[posi].minDispValue * 1000);
    ui->verticalSlider_blownup->setMaximum( theMappingTable[posi].maxDispValue * 1000);
    ui->verticalSlider_blownup->setTickInterval( (theMappingTable[posi].maxDispValue - theMappingTable[posi].minDispValue) / 100);
    ui->verticalSlider_blownup->setSingleStep( (theMappingTable[posi].maxDispValue - theMappingTable[posi].minDispValue) / 10);
    ui->verticalSlider_blownup->setPageStep( (theMappingTable[posi].maxDispValue - theMappingTable[posi].minDispValue)  * 100);

    QFont tempFont1("DejaVu Sans Condensed", 14, QFont::Bold);
    QFont tempFont2("DejaVu Sans Condensed", 10, QFont::Bold);
    ui->lblBlock->setFont(tempFont2);
    ui->lblBlock->setText( theMappingTable[posi].effectBlockLabel);

    if( strlen( theMappingTable[posi].effectParameterLabel) < 12 )
            ui->lblParam->setFont(tempFont1);
    else    ui->lblParam->setFont(tempFont2);
    ui->lblParam->setText( theMappingTable[posi].effectParameterLabel );

    ui->lbl_MaxVal->setText( QString::number( theMappingTable[posi].maxDispValue ) );
    ui->lbl_MinVal->setText( QString::number( theMappingTable[posi].minDispValue ) );

    double sentVal = paramValue * double(1000);
    ui->verticalSlider_blownup->setValue( int( sentVal ) );
    ui->dial_1->setValue( theMappingTable[posi].MIDIValue );

    QColor TheCurrentColor;

    if( theMappingTable[ posi ].MIDIValue > 127 )
         TheCurrentColor.setRgb( 0, 0, 0, 0);
    else if( theMappingTable[ posi ].MIDIValue > 63)
        TheCurrentColor.setRgb(
                255,
                int( 255 - ( (theMappingTable[ posi ].MIDIValue -63) * 3.9) ),
                int( 255 - ( (theMappingTable[ posi ].MIDIValue -63) * 3.9) ),
                255)  ;
    else
        TheCurrentColor.setRgb(
                int( 255 - ( (63 - theMappingTable[ posi ].MIDIValue) * 3.9) ),
                int( 255 - ( (63 - theMappingTable[ posi ].MIDIValue) * 3.9) ),
                255,
                255  );


//    if( MIDIValue > 63)
//        m_slidderPalette.setColor(verticalSlider_blownup->backgroundRole(),
//                                 QColor(
//                                     255,
//                                     int( 255 - ( (theMappingTable[ posi ].MIDIValue -63) * 3.9) ),
//                                     int( 255 - ( (theMappingTable[ posi ].MIDIValue -63) * 3.9) ),
//                                     255)  );
//     else
//        m_slidderPalette.setColor(m_TheSliders[sliderIndex]->backgroundRole(),
//                              QColor(
//                                     int( 255 - ( (63 - theMappingTable[ posi ].MIDIValue) * 3.9) ),
//                                     int( 255 - ( (63 - theMappingTable[ posi ].MIDIValue) * 3.9) ),
//                                     255,
//                                     255  )       );
//    m_TheSliders[ sliderIndex ]->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(ui->verticalSlider_blownup->backgroundRole(), TheCurrentColor);
    ui->verticalSlider_blownup->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(QPalette::Button, TheCurrentColor);
    ui->dial_1->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(ui->lineEdit_1->backgroundRole(), TheCurrentColor);
    ui->lineEdit_1->setPalette(m_slidderPalette);
}


void BlownUpParamDisplay::updateBlownUpParamDisplayMOD1( int posi, struct pageMappingTable pageMappingTable[], double paramValue, QString *controllerName )
{
    restoreGeometry( m_geom);

    ui->verticalSlider_blownup->setMinimum( pageMappingTable[posi].minDispValue * 1000);
    ui->verticalSlider_blownup->setMaximum( pageMappingTable[posi].maxDispValue * 1000);
    ui->verticalSlider_blownup->setTickInterval( (pageMappingTable[posi].maxDispValue - pageMappingTable[posi].minDispValue) * 50);
    ui->verticalSlider_blownup->setSingleStep( (pageMappingTable[posi].maxDispValue - pageMappingTable[posi].minDispValue) * 100);
    ui->verticalSlider_blownup->setPageStep( (pageMappingTable[posi].maxDispValue - pageMappingTable[posi].minDispValue)  * 50);

    ui->lblController->setText( *controllerName );

    QFont tempFont1("DejaVu Sans Condensed", 48 );
    QFont tempFont2("DejaVu Sans Condensed", 36 );
    ui->lblBlock->setFont(tempFont2);
    ui->lblBlock->setText( pageMappingTable[posi].effectBlockLabel);

    if( strlen( pageMappingTable[posi].effectParameterLabel) < 12 )
            ui->lblParam->setFont(tempFont1);
    else    ui->lblParam->setFont(tempFont2);
    ui->lblParam->setText( pageMappingTable[posi].effectParameterLabel );

    ui->lbl_MaxVal->setText( QString::number( pageMappingTable[posi].maxDispValue ) );
    ui->lbl_MinVal->setText( QString::number( pageMappingTable[posi].minDispValue ) );

    double sentVal = paramValue * double(1000);
    ui->verticalSlider_blownup->setValue( int( sentVal ) );
    ui->dial_1->setValue( pageMappingTable[posi].MIDIValue );

    QColor TheCurrentColor;

    if( pageMappingTable[ posi ].MIDIValue > 127 )
        TheCurrentColor.setRgb( 0, 0, 0, 0);
    else if( pageMappingTable[ posi ].MIDIValue > 63)
        TheCurrentColor.setRgb(
                255,
                255 - ( (pageMappingTable[ posi ].MIDIValue -63) * 3.9),
                255 - ( (pageMappingTable[ posi ].MIDIValue -63) * 3.9),
                255)  ;
    else
        TheCurrentColor.setRgb(
                255 - ( (63 - pageMappingTable[ posi ].MIDIValue) * 3.9),
                255 - ( (63 - pageMappingTable[ posi ].MIDIValue) * 3.9),
                255,
                255  );
    m_slidderPalette.setColor(ui->verticalSlider_blownup->backgroundRole(), TheCurrentColor);
    ui->verticalSlider_blownup->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(QPalette::Button, TheCurrentColor);
    ui->dial_1->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(ui->lineEdit_1->backgroundRole(), TheCurrentColor);
    ui->lineEdit_1->setPalette(m_slidderPalette);
}


void BlownUpParamDisplay::updateBlownUpParamDisplayMOD1( int posi, struct CCpageMappingTable theCCpageMappingTable[], int MIDIVal, QString *controllerName )
{
    ui->verticalSlider_blownup->setMinimum( 0 );
    ui->verticalSlider_blownup->setMaximum( 127 );
    ui->verticalSlider_blownup->setTickInterval( 12 );
    ui->verticalSlider_blownup->setSingleStep( 5 );
    ui->verticalSlider_blownup->setPageStep( 12 );

    ui->lblController->setText( *controllerName );
    ui->lblBlock->setText( "CTRL CC" );
    ui->lblParam->setText( theCCpageMappingTable[posi].controlName );

    ui->lbl_MaxVal->setText( QString::number( 127 ) );
    ui->lbl_MinVal->setText( QString::number( 0 ) );

    ui->verticalSlider_blownup->setValue( MIDIVal );
    ui->dial_1->setValue( MIDIVal );

    QColor TheCurrentColor;

    if( MIDIVal > 127 ||  MIDIVal < 0)
        TheCurrentColor.setRgb( 0, 0, 0, 0);
    else if( MIDIVal > 63)
        TheCurrentColor.setRgb(
                255,
                255 - ( (MIDIVal -63) * 3.9),
                255 - ( (MIDIVal -63) * 3.9),
                255)  ;
    else
        TheCurrentColor.setRgb(
                255 - ( (63 - MIDIVal) * 3.9),
                255 - ( (63 - MIDIVal) * 3.9),
                255,
                255  );
    m_slidderPalette.setColor(ui->verticalSlider_blownup->backgroundRole(), TheCurrentColor);
    ui->verticalSlider_blownup->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(QPalette::Button, TheCurrentColor);
    ui->dial_1->setPalette(m_slidderPalette);

    m_slidderPalette.setColor(ui->lineEdit_1->backgroundRole(), TheCurrentColor);
    ui->lineEdit_1->setPalette(m_slidderPalette);
}

