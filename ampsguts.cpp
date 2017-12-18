#include "ampsguts.h"
#include "ui_ampsguts.h"

AmpsGuts::AmpsGuts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmpsGuts)
{
    ui->setupUi(this);
}

AmpsGuts::~AmpsGuts()
{
    delete ui;
}
