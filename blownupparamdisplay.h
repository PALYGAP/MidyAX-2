#ifndef BLOWNUPPARAMDISPLAY_H
#define BLOWNUPPARAMDISPLAY_H

#include <QDialog>
#include "MidyAX_types.h"

namespace Ui {
class BlownUpParamDisplay;
}

class BlownUpParamDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit BlownUpParamDisplay(QWidget *parent = 0);
    ~BlownUpParamDisplay();

//private slots:
    void updateBlownUpParamDisplay( int posi, struct mappingTable theMappingTable[], double paramValue );
    void updateBlownUpParamDisplayMOD1( int posi, struct pageMappingTable pageMappingTable[], double paramValue, QString *controllerName );
    void updateBlownUpParamDisplayMOD1( int posi, struct CCpageMappingTable pageMappingTable[], int MIDIVal, QString *controllerName );

private:
    Ui::BlownUpParamDisplay *ui;

    QPalette m_slidderPalette;
    QByteArray m_geom;

    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);


};

#endif // BLOWNUPPARAMDISPLAY_H
