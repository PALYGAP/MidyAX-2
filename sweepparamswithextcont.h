#ifndef SWEEPPARAMSWITHEXTCONT_H
#define SWEEPPARAMSWITHEXTCONT_H

#include <QDialog>

namespace Ui {
class sweepParamsWithExtCont;
}

class sweepParamsWithExtCont : public QDialog
{
    Q_OBJECT

public:
    explicit sweepParamsWithExtCont(QWidget *parent = 0);
    ~sweepParamsWithExtCont();

private:
    Ui::sweepParamsWithExtCont *ui;
};

#endif // SWEEPPARAMSWITHEXTCONT_H
