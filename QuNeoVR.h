#ifndef QUNEOVR_H
#define QUNEOVR_H

#include "ui_QuNeoVR.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class QuNeoVR;
}


class QuNeoVR : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit QuNeoVR(QWidget *parent = 0);
    ~QuNeoVR();

    void init( void);

private:
    Ui::QuNeoVR *ui;
};

#endif // QUNEOVR_H
