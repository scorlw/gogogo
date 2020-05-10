#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QWidget>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);

protected:
    void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void isDC();

public slots:
};

#endif // MYLABEL_H
