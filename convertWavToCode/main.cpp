#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QTimer>
#include <QLabel>
#include <QStatusBar>
#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   //MainWindow w;
    //w.show();







    QSplashScreen *splash=new QSplashScreen;

#ifdef Q_OS_LINUX
    qDebug()<<"LINUX OS";
    splash->setPixmap(QPixmap(qApp->applicationDirPath() + "/../convertWavToCode/png/icon_convert.png"));

    qDebug()<<"folder:"<<qApp->applicationDirPath();

#else
    qDebug()<<"MAC OS";
    splash->setPixmap(QPixmap(qApp->applicationDirPath() + "/../../../../convertWavToCode/png/animal.png"));
#endif

    qDebug()<<"Link:"<<qApp->applicationDirPath();

    splash->setWindowOpacity(0.95);
    splash->show();
    QTimer::singleShot(1000,splash,SLOT(close()));

    MainWindow w;
#ifdef Q_OS_LINUX
    QIcon icon(qApp->applicationDirPath() + "/../convertWavToCode/png/icon_convert.png");
#else
    QIcon icon(qApp->applicationDirPath() + "/../../../../convertWavToCode/png/icon_convert.png");
#endif
    w.setWindowIcon(icon);
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    QTimer::singleShot(1000,&w,SLOT(show()));
    return a.exec();
}
