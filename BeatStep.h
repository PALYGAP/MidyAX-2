#ifndef BEATSTEP_H
#define BEATSTEP_H

#include "ui_BeatStep.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
class BeatStep;
}


class BeatStep : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit BeatStep(QWidget *parent = 0);
    ~BeatStep();

    void init( void);

private:
    Ui::BeatStep *ui;
};

#endif // BEATSTEP_H
