#include "widget.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString appPath = QCoreApplication::applicationDirPath();
    QDir::setCurrent(appPath);
    Widget w;

    HWND desktopHwnd = w.findDesktopIconWnd();
    if(desktopHwnd) SetParent((HWND)(w.winId()), desktopHwnd);

    //读取ini文件中上一次关闭软件时候的窗口位置和大小：
    QString wstrFilePath = appPath + "/geometry.ini" ;
    QSettings *settings=new QSettings(wstrFilePath,QSettings::IniFormat);//用QSetting获取ini文件中的数据
    int x = settings->value("WindowGeometry/x").toInt();
    int y = settings->value("WindowGeometry/y").toInt();
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    /*
    if(x<0 || x>clientRect.width() || y<0 || y>clientRect.height())//如果上一次关闭软件的时候，窗口位置不正常，则本次显示在(1050,245)
    {
        w.move(1050,245);
    }
    else{
        w.move(x, y);
    }
    */
    w.move(x, y);
    w.show();

    return a.exec();
}
