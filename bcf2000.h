#ifndef BCF2000_H
#define BCF2000_H

#include "ui_bcf2000.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
    class BCF2000;
}

class BCF2000 : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit BCF2000(QWidget *parent = 0);
    ~BCF2000();

    void init( void);

private:
    Ui::BCF2000 *ui;
};

#endif // BCF2000_H
