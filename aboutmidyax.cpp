#include "aboutmidyax.h"
#include "ui_aboutmidyax.h"

AboutMidyAX::AboutMidyAX(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutMidyAX)
{
    ui->setupUi(this);
    ui->lblPALYGAPWebLink->setOpenExternalLinks(true);
    ui->lblNewsWebLink->setOpenExternalLinks(true);
    ui->lblCompileDate->setText(__DATE__);
    //ui->lblVersionID->setText("0.7.3");
    QString TheVersion = QString::number(VERSION_MAJOR)+"."+QString::number(VERSION_MINOR)+"."+QString::number(VERSION_BUILD);
    ui->lblVersionID->setText( TheVersion );
    //ui->lblVersionID->setText(VERSION); //TODO : use version from file MidyAX.pro
}

AboutMidyAX::~AboutMidyAX()
{
    delete ui;
}
