#include "qslidermod1.h"

QSliderMod1::QSliderMod1( QWidget * parent ) : QSlider(parent)
{
}

void QSliderMod1::setValueFromText( QString text)
{
    //bool ok;
    //int val = text.toInt(&ok, 10);
    double dVal = text.toDouble();
    int iVal = int( dVal * 10 );
    QSlider::setValue( iVal );
}
