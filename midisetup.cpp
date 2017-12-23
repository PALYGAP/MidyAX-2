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

#include "midisetup.h"

extern QStringList MIDI_Known_Controllers;

MidiSetup::MidiSetup(QWidget *parent) : QDialog(parent)
{
    ui.setupUi(this);

    QString widgetName = "comboInput";
    fillWidgetList( &inputComboBox, (QWidget *) this, &widgetName );
    widgetName = "comboOutput";
    fillWidgetList( &outputComboBox, (QWidget *) this, &widgetName );

    QString sBName;
    QSpinBox *curSB;
    for(int i = 1; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
      m_currentINIndex[ i ] = -1;
      m_currentOUTIndex[ i ] = -1;
      m_fixedCCMIDIChannel[ i ] = 0;
      m_fixedPageControlMIDIChannel[ i ] = 16;
      m_fixedEffectBlockOBControlMIDIChannel[ i ] = 15;
      m_fixedAXEFXMIDIChannel[ i ] = 14;

      sBName = "sBparamChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
      curSB = this->findChild<QSpinBox *>( sBName );
      if( curSB != NULL )
      {
          curSB->setValue( m_fixedCCMIDIChannel[ i ] );
          connect(curSB, SIGNAL(valueChanged(int)), this, SLOT(onSBValueChanged(int)) );
          sBparamChannel.append( curSB );
      }

      sBName = "sBpageChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
      curSB = this->findChild<QSpinBox *>( sBName );
      if( curSB != NULL )
      {
          curSB->setValue( m_fixedPageControlMIDIChannel[ i ] );
          connect(curSB, SIGNAL(valueChanged(int)), this, SLOT(onSBValueChanged(int)) );
          sBpageChannel.append( curSB );
      }

//      sBName = "sBEffectBlockOBChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
//      curSB = this->findChild<QSpinBox *>( sBName );
//      if( curSB != NULL )
//      {
//          curSB->setValue( m_fixedEffectBlockOBControlMIDIChannel[ i ] );
//          connect(curSB, SIGNAL(valueChanged(int)), this, SLOT(onSBValueChanged(int)) );
//          sBEffectBlockOBChannel.append( curSB );
//      }

      sBName = "sBAXEFXChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
      curSB = this->findChild<QSpinBox *>( sBName );
      if( curSB != NULL )
      {
          curSB->setValue( m_fixedAXEFXMIDIChannel[ i ] );
          connect(curSB, SIGNAL(valueChanged(int)), this, SLOT(onSBValueChanged(int)) );
          sBAXEFXChannel.append( curSB );
      }
    }    
}

void MidiSetup::fillWidgetList(  QList<QComboBox *> *WidgetList, QWidget *gridLayoutWidget, QString *widgetName )
{
    QString QCBName;
    for(int i=0;; i++ )
    {
        QCBName = *widgetName + "_" + QString::number(i, 10);// + MIDI_Known_Controllers[i];
        if( gridLayoutWidget->findChild<QComboBox *>( QCBName ) != NULL )
        {
            WidgetList->append( gridLayoutWidget->findChild<QComboBox *>( QCBName ) );
        }
        else {
            break;
        }
    }
}






int MidiSetup::exec()
{
    for(int i = 0; i < inputComboBox.size(); i++)
    {
        inputComboBox[ i ]->setCurrentIndex( m_currentINIndex[ i ]);
    }
    for(int i = 0; i < outputComboBox.size(); i++)
    {
        outputComboBox[ i ]->setCurrentIndex( m_currentOUTIndex[ i ]);
    }
    return QDialog::exec();
}

void MidiSetup::clearCombos()
{
    for(int i = 0; i < inputComboBox.size(); i++)
    {
        inputComboBox[i]->clear();
    }
    for(int i = 0; i < outputComboBox.size(); i++)
    {
        outputComboBox[i]->clear();
    }
}

void MidiSetup::addInputPortName(const QString& input, int index)
{
    for(int i = 0; i < inputComboBox.size(); i++)
    {
        inputComboBox[i]->addItem(input, index);
    }
}
void MidiSetup::addOutputPortName(const QString& output, int index)
{
    for(int i = 0; i < inputComboBox.size(); i++)
    {
        outputComboBox[i]->addItem(output, index);
    }
}

void MidiSetup::setCurrentInputIndexByPortOutputPortNumber(int MIDIControllerIndex, int portNumber)
{
    if (portNumber < 0)
    {
        inputComboBox[MIDIControllerIndex]->setCurrentIndex(-1);
        m_currentINIndex[MIDIControllerIndex] = -1;
    }
    else {
        int i;
        for( i = 0; i < inputComboBox[MIDIControllerIndex]->count(); ++i )
        {
            if( portNumber == inputComboBox[MIDIControllerIndex]->itemData(i).toInt() )
            {
                inputComboBox[MIDIControllerIndex]->setCurrentIndex(i);
                break;
            }
        }
        m_currentINIndex[MIDIControllerIndex] = i;
    }
}


void MidiSetup::setCurrentOutputIndexByPortOutputPortNumber( int MIDIControllerIndex, int portNumber )
{
    if (portNumber < 0) //Case portNumber = -1
    {
        outputComboBox[MIDIControllerIndex]->setCurrentIndex(-1);
        m_currentOUTIndex[MIDIControllerIndex] = -1;
    }
    else {
        int i;
        for( i = 0; i < outputComboBox[MIDIControllerIndex]->count(); ++i )
        {
            if (portNumber == outputComboBox[MIDIControllerIndex]->itemData(i).toInt())
            {
                outputComboBox[MIDIControllerIndex]->setCurrentIndex(i);
                break;
            }
        }
        m_currentOUTIndex[MIDIControllerIndex] = i;
    }
}


int MidiSetup::getSelectedInputIndex(int MIDIControllerIndex )
{
    return inputComboBox[MIDIControllerIndex]->currentIndex();
}

int MidiSetup::getSelectedOutputIndex( int MIDIControllerIndex )
{
    return outputComboBox[MIDIControllerIndex]->currentIndex();
}


int MidiSetup::getCurrentInputIndex(int MIDIControllerIndex )
{
    return m_currentINIndex[MIDIControllerIndex];
}

int MidiSetup::getCurrentOutputIndex( int MIDIControllerIndex )
{
    return m_currentOUTIndex[MIDIControllerIndex];
}

int MidiSetup::getCurrentInputPortNumber(int MIDIControllerIndex )
{
    return inputComboBox[MIDIControllerIndex]->itemData( m_currentINIndex[MIDIControllerIndex] ).toInt();
}

int MidiSetup::getCurrentOutputPortNumber( int MIDIControllerIndex )
{
    return outputComboBox[MIDIControllerIndex]->itemData( m_currentOUTIndex[MIDIControllerIndex] ).toInt();
}



int MidiSetup::getSelectedInputPortNumber( int MIDIControllerIndex )
{
    int idx = inputComboBox[ MIDIControllerIndex ]->currentIndex();
    if (idx >= 0)
        return inputComboBox[ MIDIControllerIndex ]->itemData( idx ).toInt();
    else
        return -1;
}

int MidiSetup::getSelectedOutputPortNumber( int MIDIControllerIndex )
{
    int idx = outputComboBox[ MIDIControllerIndex ]->currentIndex();
    if (idx >= 0)
        return outputComboBox[ MIDIControllerIndex ]->itemData( idx ).toInt();
    else
        return -1;
}


//QString MidiSetup::selectedInputName( int MIDIControllerIndex ) const
//{
//    int idx = inputComboBox[ MIDIControllerIndex ]->currentIndex();
//    if (idx >= 0)
//        return inputComboBox[ MIDIControllerIndex ]->itemText(idx);
//    else
//        return QString();
//}

//QString MidiSetup::selectedOutputName_AXEFX( int MIDIControllerIndex ) const
//{
//    int idx = outputComboBox[ MIDIControllerIndex ]->currentIndex();
//    if (idx >= 0)
//        return outputComboBox[ MIDIControllerIndex ]->itemText(idx);
//    else
//        return QString();
//}


void MidiSetup::on_buttonBox_accepted()
{
    // Store the selected IN/OUT port as the current IN/OUT port
//    for(int i = 0; i < inputComboBox.size(); i++)
//    {
//        m_currentIN[ i ] = selectedInput( i );
//    }
//    for(int i = 0; i < outputComboBox.size(); i++)
//    {
//        m_currentOUT[ i ] = selectedOutput( i );
//    }

    QSpinBox *curSB;
    QString sBName;
    for(int i = 0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS; i++)
    {
        sBName = "sBparamChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
        curSB = this->findChild<QSpinBox *>( sBName );
        if( curSB != NULL )
        {
            m_fixedCCMIDIChannel[ i ] = curSB->value();
        }

        sBName = "sBpageChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
        curSB = this->findChild<QSpinBox *>( sBName );
        if( curSB != NULL )
        {
            m_fixedPageControlMIDIChannel[ i ] = curSB->value();
        }

        sBName = "sBEffectBlockOBChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
        curSB = this->findChild<QSpinBox *>( sBName );
        if( curSB != NULL )
        {
            m_fixedEffectBlockOBControlMIDIChannel[ i ] = curSB->value();
        }

        sBName = "sBAXEFXChannel_" +  QString("%1").arg( i, 2, 10, QChar('0') );
        curSB = this->findChild<QSpinBox *>( sBName );
        if( curSB != NULL )
        {
            m_fixedAXEFXMIDIChannel[ i ] = curSB->value();
        }
    }
}


void MidiSetup::retranslateUi()
{
    ui.retranslateUi(this);
}


void MidiSetup::setFixedCCMIDIChannel( int MIDIControllerNumber, int MIDIChannel )
{
    m_fixedCCMIDIChannel[ MIDIControllerNumber ] = MIDIChannel;

    QSpinBox *curSB;
    QString sBName;
    sBName = "sBparamChannel_" +  QString("%1").arg( MIDIControllerNumber, 2, 10, QChar('0') );
    curSB = this->findChild<QSpinBox *>( sBName );
    if( curSB != NULL )
    {
        curSB->setValue( MIDIChannel );
    }
}
void MidiSetup::setAXEFXMIDIChannel( int MIDIControllerNumber, int MIDIChannel )
{
    m_fixedAXEFXMIDIChannel[ MIDIControllerNumber ] = MIDIChannel;

    QSpinBox *curSB;
    QString sBName;
    sBName = "sBAXEFXChannel_" +  QString("%1").arg( MIDIControllerNumber, 2, 10, QChar('0') );
    curSB = this->findChild<QSpinBox *>( sBName );
    if( curSB != NULL )
    {
        curSB->setValue( MIDIChannel );
    }
}
void MidiSetup::setFixedEffectBlockOBControlMIDIChannel( int MIDIControllerNumber, int MIDIChannel )
{
    m_fixedEffectBlockOBControlMIDIChannel[ MIDIControllerNumber ] = MIDIChannel;

    QSpinBox *curSB;
    QString sBName;
    sBName = "sBEffectBlockOBChannel_" +  QString("%1").arg( MIDIControllerNumber, 2, 10, QChar('0') );
    curSB = this->findChild<QSpinBox *>( sBName );
    if( curSB != NULL )
    {
        curSB->setValue( MIDIChannel );
    }
}
void MidiSetup::setFixedPageControlMIDIChannel( int MIDIControllerNumber, int MIDIChannel )
{
    m_fixedPageControlMIDIChannel[ MIDIControllerNumber ] = MIDIChannel;

    QSpinBox *curSB;
    QString sBName;
    sBName = "sBpageChannel_" +  QString("%1").arg( MIDIControllerNumber, 2, 10, QChar('0') );
    curSB = this->findChild<QSpinBox *>( sBName );
    if( curSB != NULL )
    {
        curSB->setValue( MIDIChannel );
    }
}

int MidiSetup::getFixedCCMIDIChannel( int MIDIControllerNumber )
{
    return m_fixedCCMIDIChannel[ MIDIControllerNumber ];
}
int MidiSetup::getAXEFXMIDIChannel( int MIDIControllerNumber )
{
    return m_fixedAXEFXMIDIChannel[ MIDIControllerNumber ];
}
int MidiSetup::getFixedEffectBlockOBControlMIDIChannel( int MIDIControllerNumber )
{
    return m_fixedEffectBlockOBControlMIDIChannel[ MIDIControllerNumber ];
}
int MidiSetup::getFixedPageControlMIDIChannel( int MIDIControllerNumber )
{
    return m_fixedPageControlMIDIChannel[ MIDIControllerNumber ];
}

void MidiSetup::setFractProdName( QString fractProdName)
{
    ui.lbFractProd->setText(fractProdName);
}




void MidiSetup::onSBValueChanged( int newSBValue )
{
    int i;
    // Find the Slider that has changed value
    QSpinBox* obj = qobject_cast<QSpinBox *>( sender() );

    // Determine the number of the MIDI Controller
    for( i = 0; i < MAX_NUMBER_FIXED_CC_MIDI_CONTROLLERS ; i++ )
    {
        if(    obj == sBparamChannel[ i ]
            || obj == sBpageChannel[ i ]
            || obj == sBAXEFXChannel[ i ]
//            || obj == sBEffectBlockOBChannel[ i ]
               )   break;
    }

    // If set to a MIDI channel already used setback to original value
    if(    m_fixedCCMIDIChannel[ i ] == newSBValue
        || m_fixedPageControlMIDIChannel[ i ] == newSBValue
        || m_fixedAXEFXMIDIChannel[ i ] == newSBValue
           )
    {
        // Set changed sB to its previous value
        if( obj == sBparamChannel[ i ])  obj->setValue( m_fixedCCMIDIChannel[ i ] );
        if( obj == sBpageChannel[ i ])  obj->setValue( m_fixedPageControlMIDIChannel[ i ] );
        if( obj == sBAXEFXChannel[ i ])  obj->setValue( m_fixedAXEFXMIDIChannel[ i ] );
//        if( obj == sBEffectBlockOBChannel[ i ])  obj->setValue( m_fixedEffectBlockOBControlMIDIChannel[i] );
    }
    else {
        // Otherwise accept new value
        if( obj == sBparamChannel[ i ])  m_fixedCCMIDIChannel[i] = newSBValue;
        if( obj == sBpageChannel[ i ])  m_fixedPageControlMIDIChannel[i] = newSBValue;
        if( obj == sBAXEFXChannel[ i ])  m_fixedAXEFXMIDIChannel[i] = newSBValue;
//        if( obj == sBEffectBlockOBChannel[ i ])  m_fixedEffectBlockOBControlMIDIChannel[i] = newSBValue;

        obj->setValue( newSBValue );
    }
}
