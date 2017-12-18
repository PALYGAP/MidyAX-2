#ifndef BCR2000_H
#define BCR2000_H

#include "ui_bcr2000.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
    class BCR2000;
}

class BCR2000 : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit BCR2000(QWidget *parent = 0);
    ~BCR2000();

    void init( void);

private:
    Ui::BCR2000 *ui;
};

#endif // BCR2000_H
