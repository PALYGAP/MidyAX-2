#ifndef GUITARWING_H
#define GUITARWING_H

#include "ui_GuitarWing.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class GuitarWing;
}


class GuitarWing : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit GuitarWing(QWidget *parent = 0);
    ~GuitarWing();

    void init( void);

private:
    Ui::GuitarWing *ui;
};

#endif // GUITARWING_H
