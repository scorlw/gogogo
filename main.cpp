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

    //��ȡini�ļ�����һ�ιر����ʱ��Ĵ���λ�úʹ�С��
    QString wstrFilePath = appPath + "/geometry.ini" ;
    QSettings *settings=new QSettings(wstrFilePath,QSettings::IniFormat);//��QSetting��ȡini�ļ��е�����
    int x = settings->value("WindowGeometry/x").toInt();
    int y = settings->value("WindowGeometry/y").toInt();
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    /*
    if(x<0 || x>clientRect.width() || y<0 || y>clientRect.height())//�����һ�ιر������ʱ�򣬴���λ�ò��������򱾴���ʾ��(1050,245)
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
