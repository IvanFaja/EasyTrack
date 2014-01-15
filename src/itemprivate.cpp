#include "itemprivate.h"
#include <QStandardPaths>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDir>
#include <QDebug>
#include <QDateTime>

ItemPrivate::ItemPrivate(const QString &dbName,QObject *parent) :
    QObject(parent)
{
    QString dataPath =dbName;
    if(dataPath.isEmpty()){
        dataPath = QStandardPaths::standardLocations(QStandardPaths::DataLocation).first();
        QDir dir;
        if(!dir.mkpath(dataPath)){
            qWarning()<<"could not create database";
        }

        dataPath.append("/database");
    }
    qDebug()<<"************"<<dataPath;
    databaseManager.setDatabaseName(dataPath);
    databaseManager.init();
}

void ItemPrivate::addItem(QSqlDatabase db, const ItemData &data)
{
    const char * INSERT_ITEM ="INSERT INTO items(ref) values(?)";
    QSqlQuery query(db);
    query.prepare(INSERT_ITEM);
    query.addBindValue(QVariant(data.ref));
    if(!query.exec()){
        qWarning()<<"fail inserting item ref"<<query.lastQuery()<<query.lastError().text();
    }
}

void ItemPrivate::addItemDescription(QSqlDatabase db, const ItemData &data)
{
    const char * INSERT_DESCRIOTION_STAMENT="INSERT INTO items_description(ref,size,amount,price)values(?,?,?,?);";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.amount);
    query.bindValue(3,data.price);
    if(!query.exec()){
        qWarning()<<"could no insert items "<<query.lastError().text();
    }
}

int ItemPrivate::updateResume(QSqlDatabase db, const ItemData &data)
{
    const char * INSERT_DESCRIOTION_STAMENT="UPDATE items_resume set amount = amount + :amount WHERE ref = :ref and size = :size;";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(":ref",data.ref);
    query.bindValue(":size",data.size);
    query.bindValue(":amount",data.amount);
    if(!query.exec()){
        qWarning()<<"could no update resume items "<<query.lastQuery();
    }
    return query.numRowsAffected();
}

void ItemPrivate::insertResume(const ItemData &data, QSqlDatabase db)
{
    const char * INSERT_DESCRIOTION_STAMENT="INSERT INTO items_resume(ref,size,amount,price)values(?,?,?,?);";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.amount);
    query.bindValue(3,data.price);
    if(!query.exec()){
        qWarning()<<"could no insert items "<<query.lastQuery();
    }
}

int ItemPrivate::updateItemDescirption(const ItemData &data, QSqlDatabase db)
{
    const char * INSERT_DESCRIOTION_STAMENT="UPDATE items_description set amount = amount + :amount WHERE ref = :ref and size = :size;";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(":ref",data.ref);
    query.bindValue(":size",data.size);
    query.bindValue(":amount",data.amount);
    if(!query.exec()){
        qWarning()<<"could no update resume items "<<query.lastQuery();
    }
    return query.numRowsAffected();
}

void ItemPrivate::addItemToResume(const ItemData &data, QSqlDatabase db)
{
    if(updateResume(db,data) <= 0){
        insertResume(data, db);
    }
}

void ItemPrivate::addBuyItem(const ItemData &data, QSqlDatabase db)
{
    addItem(db, data);
    if(updateItemDescirption(data, db) <=0){
        addItemDescription(db, data);
    }
}

bool ItemPrivate::insert(const ItemData &data)
{
    QSqlDatabase db = databaseManager.open();
    addBuyItem(data, db);
    addItemToResume(data, db);

    return true;
}

void ItemPrivate::insertSale(QSqlDatabase db, const ItemData &data)
{
    const char * INSERT_DESCRIOTION_STAMENT="INSERT INTO items_sales(ref,size,amount,price,sales_date)values(?,?,?,?,?);";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.amount);
    query.bindValue(3,data.price);
    QDateTime time = QDateTime::currentDateTimeUtc();
    query.bindValue(4,time);
    if(!query.exec()){
        qWarning()<<"could no insert items "<<query.lastError().text();
    }
}

void ItemPrivate::registerSale(const ItemData &data)
{
    QSqlDatabase db = databaseManager.open();
    insertSale(db, data);
    ItemData saleData = data;
    saleData.amount = -data.amount;
    addItemToResume(saleData,db);
}
