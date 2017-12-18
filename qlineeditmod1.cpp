#include "qlineeditmod1.h"

QLineEditMod1::QLineEditMod1( QWidget * parent ) : QLineEdit(parent)
{
}

void QLineEditMod1::setTextFromInt(int value)
{
    double dVal = value;
    dVal /= double(1000);
    if( dVal < 100)    QLineEdit::setText( QString::number( dVal, 'f', 2 ) );
    else QLineEdit::setText( QString::number( dVal, 'f', 0 ) );
}
