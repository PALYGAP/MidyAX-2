#ifndef QLINEEDITMOD1_H
#define QLINEEDITMOD1_H

#include <QLineEdit>

class QLineEditMod1 : public QLineEdit
{
    Q_OBJECT

public:
    QLineEditMod1( QWidget * parent = 0);

public slots :
    void setTextFromInt(int value);
};

#endif // QLINEEDITMOD1_H
