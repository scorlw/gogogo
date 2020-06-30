#include "widget.h"
#include <QLayout>
#include <QToolButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//�ޱ߿�
    setAttribute(Qt::WA_TranslucentBackground);//͸������

    //����
    QHBoxLayout* baseLayout = new QHBoxLayout(this);
    QVBoxLayout* itemLayout = new QVBoxLayout;
    QVBoxLayout* btnLayout = new QVBoxLayout;
    itemLayout->setMargin(0);
    itemLayout->setSpacing(0);
    baseLayout->addLayout(itemLayout);
    baseLayout->addLayout(btnLayout,15);

    QToolButton* addBtn = new QToolButton;
    QToolButton* closeBtn = new QToolButton;

    addBtn->setStyleSheet("QToolButton{border-image: url(:/pic/add.png)}");
    closeBtn->setStyleSheet("QToolButton{border-image: url(:/pic/close.png)}");
    addBtn->resize(20,20);
    closeBtn->resize(20,20);
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(closeBtn);

    QStringList itemList = itemSQL::getInstance()->getItem();
    foreach (QString itemInfo, itemList) {
        QStringList list = itemInfo.split(",");
        if(list.size() == 4){
            itemWidget* item = new itemWidget(this);
            itemLayout->addWidget(item);
            item->setItem(list.at(0));
            item->show();
        }
    }

    connect(addBtn,&QToolButton::clicked,this,[=](){
        itemDialog* dialog = new itemDialog;
        dialog->show();
        itemWidget* item = new itemWidget(this);
        itemLayout->addWidget(item);
        item->show();
        connect(dialog,&itemDialog::setName,item,&itemWidget::setItem);
        connect(dialog,&itemDialog::unset,item,&itemWidget::close);
    });

    connect(closeBtn,&QToolButton::clicked,this,&Widget::close);
}

Widget::~Widget()
{

}

BOOL Widget::enumUserWindowsCB(HWND hwnd,LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);//��ô�����ʽ
    if(!(wflags & WS_VISIBLE)) return TRUE;

    HWND sndWnd;
    if( !(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL)) ) return TRUE;
    HWND targetWnd;
    if( !(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView")) ) return TRUE;

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}

HWND Widget::findDesktopIconWnd()
{
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
    return resultHwnd;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(21, 21, 21, 210));
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//�ж�����Ƿ���
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//�ƶ���ǰ����
}

void Widget::closeEvent(QCloseEvent *event)
{
    QString wstrFilePath = QCoreApplication::applicationDirPath() + "/geometry.ini" ;//in windows���ҵĹ�����ΪEditPic����editpic.ini���ڹ���Դ�ļ�Ŀ¼��
    QSettings *settings=new QSettings(wstrFilePath,QSettings::IniFormat);//��QSetting��ȡini�ļ��е�����
    settings->clear();//��յ�ǰ�����ļ��е�����
    settings->setValue("WindowGeometry/x",this->x());
    settings->setValue("WindowGeometry/y",this->y());
}
