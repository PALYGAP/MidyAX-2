#ifndef AMPSGUTS_H
#define AMPSGUTS_H

#include <QDialog>

namespace Ui {
class AmpsGuts;
}

class AmpsGuts : public QDialog
{
    Q_OBJECT

public:
    explicit AmpsGuts(QWidget *parent = 0);
    ~AmpsGuts();

private:
    Ui::AmpsGuts *ui;
};

#endif // AMPSGUTS_H
