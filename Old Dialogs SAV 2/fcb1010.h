#ifndef FCB1010_H
#define FCB1010_H

#include <QDialog>
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class FCB1010;
}

class FCB1010 : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit FCB1010(QWidget *parent = 0);
    ~FCB1010();

    void init( void);

private:
    Ui::FCB1010 *ui;
};

#endif // FCB1010_H

