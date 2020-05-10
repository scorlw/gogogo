#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QImage>
#include "mylabel.h"
#include "itemsql.h"

class itemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit itemWidget(QWidget *parent = 0);

private:
    myLabel itemName;
    QProgressBar proBar;
    QImage m_image;
    QString m_path = "";
    QString m_name = "";
    int m_num = 0;
    int m_count = 0;

    void reflashProBar();

signals:

public slots:
    void setItem(QString name);

private slots:
    void cntP();
    void cntS();
    void delItem();
    void openFile();
};

#endif // ITEMWIDGET_H
