#ifndef QSLIDERMOD1_H
#define QSLIDERMOD1_H

#include <QSlider>

class QSliderMod1 : public QSlider
{
    Q_OBJECT

public:
    QSliderMod1( QWidget * parent = 0 );

protected slots :
    void setValueFromText(QString text);
};

#endif // QSLIDERMOD1_H
