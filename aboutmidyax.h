#ifndef ABOUTMIDYAX_H
#define ABOUTMIDYAX_H

#include <QDialog>

namespace Ui {
class AboutMidyAX;
}

class AboutMidyAX : public QDialog
{
    Q_OBJECT

public:
    explicit AboutMidyAX(QWidget *parent = 0);
    ~AboutMidyAX();

private:
    Ui::AboutMidyAX *ui;
};

#endif // ABOUTMIDYAX_H
