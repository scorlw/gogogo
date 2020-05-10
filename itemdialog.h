#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include "itemsql.h"

namespace Ui {
class itemDialog;
}

class itemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit itemDialog(QWidget *parent = 0);
    ~itemDialog();

signals:
    void setName(QString name);
    void unset();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::itemDialog *ui;
    bool isOk = false;
};

#endif // ITEMDIALOG_H
