#include "itemsql.h"

itemSQL* itemSQL::m_db = nullptr;

//itemSQL::itemSQL(QObject *parent) : QObject(parent)
itemSQL::itemSQL()
{
    db.setDatabaseName("goItem.dat");    //�����Ŀ¼��û�и��ļ�,����ڱ�Ŀ¼������,�������Ӹ��ļ�
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.exec("create table GoItem ("
               "name varchar(60) primary key,"
               "num INTEGER NOT NULL,"
               "count INTEGER NOT NULL,"
               "path varchar(60))");//����sql���
}
void itemSQL::addItem(QString name, int num, int count, QString path)
{
    QString sqlStr = QString("INSERT INTO GoItem (name, num, count, path) VALUES ('%1', %2, %3, '%4')").arg(name).arg(num).arg(count).arg(path);
    QSqlQuery query;
    query.exec(sqlStr);
}

void itemSQL::setItem(QString name, int num, int count, QString path)
{
    QString sqlStr = QString("UPDATE GoItem SET num = %2, count = %3, path = '%4' WHERE  name='%1' ").arg(name).arg(num).arg(count).arg(path);
    QSqlQuery query;
    query.exec(sqlStr);
}

QStringList itemSQL::getItem()
{
    QStringList myitem;
    QString sqlStr = QString("SELECT * FROM GoItem");
    QSqlQuery query;
    query.exec(sqlStr);
    while(query.next()){
        QString myname = query.value(0).toString();
        QString num = query.value(1).toString();
        QString count = query.value(2).toString();
        QString path = query.value(3).toString();
        QString item = myname + "," + num + "," + count + "," + path;
        myitem.append(item);
    }
    return myitem;
}

QStringList itemSQL::getItem(QString name)
{
    QStringList myitem;
    QString sqlStr = QString("SELECT * FROM GoItem WHERE name = '%1';").arg(name);
    QSqlQuery query;
    query.exec(sqlStr);
    if(query.next()){
        QString myname = query.value(0).toString();
        QString num = query.value(1).toString();
        QString count = query.value(2).toString();
        QString path = query.value(3).toString();
        myitem.append(myname);
        myitem.append(num);
        myitem.append(count);
        myitem.append(path);
    }
    return myitem;
}

void itemSQL::delItem(QString name)
{
    QString sqlStr = QString("DELETE FROM GoItem WHERE name = '%1'").arg(name);
    QSqlQuery query;
    query.exec(sqlStr);
}
