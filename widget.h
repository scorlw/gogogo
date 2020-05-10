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
    //������������¼�����
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    //����Ƿ�������
    bool m_bPressed=false;

    //���º�ǰ���λ������
    QPoint m_point;

    virtual void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_H
