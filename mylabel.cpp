#include "mylabel.h"

myLabel::myLabel(QWidget *parent):
    QLabel(parent)
{

}

void myLabel::mouseDoubleClickEvent(QMouseEvent *)
{
    emit isDC();
}
