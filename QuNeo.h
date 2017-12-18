#ifndef QUNEO_H
#define QUNEO_H

#include "ui_QuNeo.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class QuNeo;
}


class QuNeo : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit QuNeo(QWidget *parent = 0);
    ~QuNeo();

    void init( void);

private:
    Ui::QuNeo *ui;
};

#endif // QUNEO_H
