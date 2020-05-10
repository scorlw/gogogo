#ifndef ITEMSQL_H
#define ITEMSQL_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

class itemSQL : public QObject
{
    Q_OBJECT
//public:
//    explicit itemSQL(QObject *parent = 0);
public:
    itemSQL();

    static itemSQL* m_db;

    //getInstance
    //获取实例
    static itemSQL* getInstance()
    {
        if(m_db == NULL)
        {
            m_db = new itemSQL();
        }
        return m_db;
    }
    //释放
    static void destroy()
    {
        if(m_db != NULL)
        {
            delete m_db;
            m_db = NULL;
        }
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    void addItem(QString name, int num, int count, QString path);
    void setItem(QString name, int num, int count, QString path);
    QStringList getItem(QString name);
    QStringList getItem();
    void delItem(QString name);

};

#endif // ITEMSQL_H
