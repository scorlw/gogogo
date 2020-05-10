#include "itemdialog.h"
#include "ui_itemdialog.h"

itemDialog::itemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::itemDialog)
{
    ui->setupUi(this);
    connect(this,&itemDialog::finished,[=](){
        if(!isOk){
            emit unset();
        }
    });
}

itemDialog::~itemDialog()
{
    delete ui;
}

void itemDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(ui->buttonBox->button(QDialogButtonBox::Ok) == (QPushButton*)button){
        QString name = ui->nameEdit->text();
        int num = ui->numEdit->text().toInt();
        int count = ui->countEdit->text().toInt();
        QString path = ui->pathEdit->text();
        itemSQL::getInstance()->addItem(name, num, count, path);
        itemSQL::getInstance()->setItem(name, num, count, path);
        isOk = true;
        emit setName(name);
    }
    else if(ui->buttonBox->button(QDialogButtonBox::Cancel) == (QPushButton*)button){
        emit unset();
    }
}
