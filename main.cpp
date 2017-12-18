#include "midyax.h"
#include <QApplication>
#include "constants.h"
#include <QFontDatabase>

quint8 CCtoAXE[16][128][3];

MidyAX* g_pMidyAXDlgInstance;

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(QSTR_ORGNAME);
    QCoreApplication::setOrganizationDomain(QSTR_DOMAIN);
    QCoreApplication::setApplicationName(QSTR_APPNAME);

    QApplication a(argc, argv);

    MidyAX w;
    g_pMidyAXDlgInstance = &w;

    // Load the embedded font.
    QString fontPath = ":/font/arial.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if (fontId != -1)
    {
        QFont font("MyFont");
        a.setFont(font);
    }

    QString iconPath = ":/new/icon/MidyAX.icns";
    QApplication::setWindowIcon(QIcon(iconPath));

    w.show();

    return a.exec();

}

