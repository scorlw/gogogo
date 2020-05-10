#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <windows.h>
#include <QPainter>
#include <QDesktopWidget>
#include <QRect>
#include <QMouseEvent>
#include <QSettings>
#include <QCoreApplication>
#include "itemdialog.h"
#include "itemsql.h"
#include "itemwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    HWND findDesktopIconWnd();

private:
    static BOOL enumUserWindowsCB(HWND hwnd,LPARAM lParam);

protected:
    void paintEvent(QPaintEvent *);
    //声明三个鼠标事件函数
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    //鼠标是否按下属性
    bool m_bPressed=false;

    //按下后当前鼠标位置属性
    QPoint m_point;

    virtual void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
