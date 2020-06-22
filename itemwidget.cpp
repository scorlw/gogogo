#include "itemwidget.h"
#include <QLayout>
#include <QToolButton>
#include <QSpacerItem>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QStringList>
#include <QFont>

itemWidget::itemWidget(QWidget *parent) : QWidget(parent),
    m_image(":/pic/progressBar.png")
{
    this->resize(300,37);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    this->setSizePolicy(sizePolicy);
    QHBoxLayout* baseLayout = new QHBoxLayout(this);

    QFont font(QString::fromLocal8Bit("华文行楷"),11,50);
    itemName.setFont(font);
    itemName.setStyleSheet("QLabel{color:rgb(170, 170, 255);}");

    proBar.setFixedSize(120,14);

    QToolButton* addBtn = new QToolButton;
    QToolButton* subBtn = new QToolButton;
    QToolButton* delBtn = new QToolButton;
    addBtn->resize(10,10);
    subBtn->resize(10,10);
    delBtn->resize(10,10);
    addBtn->setStyleSheet("QToolButton{border-image: url(:/pic/add.png)}");
    subBtn->setStyleSheet("QToolButton{border-image: url(:/pic/remove.png)}");
    delBtn->setStyleSheet("QToolButton{border-image: url(:/pic/close.png)}");
    baseLayout->addWidget(&itemName);
    baseLayout->addSpacerItem(new QSpacerItem(10,37,QSizePolicy::Expanding));
    baseLayout->addWidget(&proBar);
    baseLayout->addSpacerItem(new QSpacerItem(10,37,QSizePolicy::Expanding));
    baseLayout->addWidget(addBtn);
    baseLayout->addWidget(subBtn);
    baseLayout->addWidget(delBtn);

    connect(addBtn,&QToolButton::clicked,this,&itemWidget::cntP);
    connect(subBtn,&QToolButton::clicked,this,&itemWidget::cntS);
    connect(delBtn,&QToolButton::clicked,this,&itemWidget::delItem);

    connect(&itemName,&myLabel::isDC,this,&itemWidget::openFile);
}

void itemWidget::setItem(QString name)
{
    QStringList myItem = itemSQL::getInstance()->getItem(name);
    m_name = myItem.at(0);
    m_num = myItem.at(1).toInt();
    m_count = myItem.at(2).toInt();
    m_path = myItem.at(3);
    itemName.setText(m_name);
    proBar.setMinimum(0);
    proBar.setMaximum(myItem.at(1).toInt());
    proBar.setValue(myItem.at(2).toInt());
    proBar.setFormat(QString("%1/%2 %p%").arg(myItem.at(2)).arg(myItem.at(1)));
    reflashProBar();
}

void itemWidget::reflashProBar()
{
    QString qss= "QProgressBar{"
                 "border: 1px solid #FFFFFF;"
                 "text-align: center;"
                 "border-radius: 7px; }"
                 "QProgressBar::chunk:enabled {"
                 "border-radius: 6px; "
                 "background: qlineargradient(x1:0, y1:0, x2:1, y2:0" ;

        double v = proBar.maximum();
        double EndColor = static_cast<double>(m_count) / v ;    //获取比例

        for(int i = 0; i < 100; i++)
        {
         double Current = EndColor * i / 100;
         QRgb rgb = m_image.pixel((m_image.width()-1)*Current,m_image.height()/2);
         QColor c(rgb);
         qss.append(QString(",stop:%1  rgb(%2,%3,%4)").arg(i/100.0).arg(c.red()).arg(c.green()).arg(c.blue()));
        }

        qss.append(");}");
        proBar.setStyleSheet(qss);
}

void itemWidget::cntP()
{
    qDebug() << "123";
    m_count++;
    itemSQL::getInstance()->setItem(m_name, m_num, m_count, m_path);
    setItem(m_name);
    reflashProBar();
}

void itemWidget::cntS()
{
    m_count--;
    itemSQL::getInstance()->setItem(m_name, m_num, m_count, m_path);
    setItem(m_name);
    reflashProBar();
}

void itemWidget::delItem()
{
    itemSQL::getInstance()->delItem(m_name);
    this->close();
}

void itemWidget::openFile()
{
    QFile bfilePath(m_path);

    if(!bfilePath.exists()){

    return;

    }

    QString filePath = "file:///" + m_path; //打开zd文件夹用filse:///,打开网页用http://

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
