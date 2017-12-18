#include "midiknob.h"

MIDIKnob::MIDIKnob(QObject *parent) : QObject(parent)
{
    connect(m_TheSlider, SIGNAL(valueChanged( int )), this, SLOT( onSliderValueChanged(int)) );
    connect(m_TheSlider, SIGNAL(valueChanged( int )), m_TheLineEdit, SLOT( setTextFromInt(int)) );
    connect(m_TheComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT( onComboBoxCurrentIndexChanged(int)) );
    connect(m_TheSlider, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT( onVerticalSliderCustomContextMenuRequested(const QPoint )) );
}

void onSliderValueChanged( int value )
{
    emit knobValueChanges( value );
}

void onComboBoxCurrentIndexChanged( int index )
{
    emit knobCurrentIndexChanged( index );
}

//void onLineEditEditingFinished( void )
//{
//    emit knobLEEditingFinished();
//}

void onVerticalSliderCustomContextMenuRequested( const QPoint loc )
{
    emit knobCustomContextMenuRequested( loc );
}





void setBlockLabel( Qstring blockLabel )
{
    m_TheBlockLabel.setText( blockLabel);
}

void setEffectLabel( Qstring effectLabel )
{
    m_TheEffectLabel.setText( effectLabel );
}


