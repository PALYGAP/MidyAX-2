#ifndef XTOUCHMINI_H
#define XTOUCHMINI_H

#include "ui_XTouchMini.h"
//After MOD1 ---- #include "midicontrollergenericdialog.h"
#include "midicontrollergenericdialogmod1.h"

namespace Ui {
    class XTouchMini;
}


// After MOD1 ---- class XTouchMini : public MIDIControllerGenericDialog
class XTouchMini : public MIDIControllerGenericDialogMOD1
{
    Q_OBJECT

public:
    explicit XTouchMini(QWidget *parent = 0);
    ~XTouchMini();

    void init( void);

private:
    Ui::XTouchMini *ui;
};

#endif // XTOUCHMINI_H
