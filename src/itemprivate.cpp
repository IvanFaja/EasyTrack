#include "itemprivate.h"
#include <QStandardPaths>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDir>
#include <QDebug>
#include <QDateTime>

#include "ErrorEvents.h"

ItemPrivate::ItemPrivate(const QString &dbName,QObject *parent) :
    QObject(parent)
{
    QString dataPath =dbName;
    if(dataPath.isEmpty()){
        qDebug()<<"xxxxxxxxxxx" <<QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
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
    ErrorEvents e;
    e.errorCode = ErrorEvents::UnKnown;
    if(data.ref.isEmpty() ){
        e.errorCode = ErrorEvents::NoAllowedNullValue;
        e.log =" ref value is null";
        throw e;
    }
    const char * INSERT_ITEM ="INSERT INTO items(ref) select ? WHERE NOT EXISTS (SELECT 1 FROM items WHERE ref = ?);";
    QSqlQuery query(db);
    query.prepare(INSERT_ITEM);
    query.addBindValue(data.ref);
    query.addBindValue(data.ref);
    if(!query.exec()){
        qWarning()<<"fail inserting item ref"<<query.lastQuery()<<query.lastError().text();
        e.log = query.lastError().text();
        throw e;
    }
}
ErrorEvents ItemPrivate::getLastError() const
{
    return lastError;
}

void ItemPrivate::setLastError(const ErrorEvents &value)
{
    lastError = value;
}


void ItemPrivate::addItemDescription(QSqlDatabase db, const ItemData &data)
{
    const char * INSERT_DESCRIOTION_STAMENT="INSERT INTO items_description(ref,size,amount,price,color,prov)values(?,?,?,?,?,?);";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.amount);
    query.bindValue(3,data.price);
    query.bindValue(4,data.color);
    query.bindValue(5,data.proveedor);
    if(!query.exec()){
        ErrorEvents e;
        e.errorCode =ErrorEvents::QueryFail;
        qWarning()<<"could no insert items "<<query.lastError().text();
    }
}

int ItemPrivate::abiableItemAmount(const ItemData &data, const QSqlDatabase &db)
{
    ErrorEvents e;
    e.errorCode = ErrorEvents::UnKnown;

    const char * AMOUNT_STAMENT="SELECT amount as total FROM items_resume WHERE ref= ? and size = ? and color = ? and prov = ? ";
    QSqlQuery query(AMOUNT_STAMENT,db);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.color);
    query.bindValue(3,data.proveedor);

    if(!query.exec()){
        e.log = query.lastError().text();
        throw e;
    }
    if(!query.first()){
        qDebug()<<"xxxxxxxxx is select"<<query.isSelect()<<query.boundValues();
        qWarning()<<"error cout  resume "<<query.lastQuery()<<db.databaseName();
        e.errorCode = ErrorEvents::ItemNotExists;
        e.log = query.lastError().text();
        throw e;
    }
    int amount = query.value(0).toInt();
    return amount;
}

void ItemPrivate::updatePrice(const ItemData &data, QSqlDatabase db)
{
    ErrorEvents e;
    e.errorCode = ErrorEvents::UnKnown;
    const char * INSERT_DESCRIOTION_STAMENT="UPDATE items_resume set price = :price WHERE prov = :prov and ref = :ref and size = :size and color = :color;";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(":ref",data.ref);
    query.bindValue(":size",data.size);
    query.bindValue(":price",data.price);
    query.bindValue(":color",data.color);
    query.bindValue(":prov",data.proveedor);
    if(!query.exec()){
        qWarning()<<"could no update resume items "<<query.lastQuery();
        e.log = query.lastError().text();
        throw e;
    }
}

int ItemPrivate::updateResume(QSqlDatabase db, const ItemData &data)
{

    ErrorEvents e;
    e.errorCode = ErrorEvents::UnKnown;
    const char * INSERT_DESCRIOTION_STAMENT="UPDATE items_resume set amount = amount + :amount WHERE prov = :prov and ref = :ref and size = :size and color = :color;";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(":ref",data.ref);
    query.bindValue(":size",data.size);
    query.bindValue(":amount",data.amount);
    query.bindValue(":color",data.color);
    query.bindValue(":prov",data.proveedor);
    if(!query.exec()){
        qWarning()<<"could no update resume items "<<query.lastQuery();
        e.log = query.lastError().text();
        throw e;
    }


    return query.numRowsAffected();
}

void ItemPrivate::insertResume(const ItemData &data, const QSqlDatabase &db)
{
    ErrorEvents e;

    const char * INSERT_DESCRIOTION_STAMENT="INSERT INTO items_resume(ref,size,amount,price,color,prov)values(?,?,?,?,?,?) ;";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.amount);
    query.bindValue(3,data.price);
    query.bindValue(4,data.color);
    query.bindValue(5,data.proveedor);

    if(!query.exec()){
        qWarning()<<"could no insert items resume "<<query.lastQuery();
        e.errorCode = ErrorEvents::UnKnown;
        e.log = query.lastError().text();
        throw e;
    }
}

int ItemPrivate::updateItemDescirption(const ItemData &data, const QSqlDatabase &db )
{
    ErrorEvents e;
    e.errorCode = ErrorEvents::UnKnown;
    const char * UPDATE_DESCRIOTION_STAMENT="UPDATE items_description set amount = amount + :amount WHERE ref = :ref and size = :size "
            "and prov = :prov and color =:color;";
    QSqlQuery query(db);
    query.prepare(UPDATE_DESCRIOTION_STAMENT);
    query.bindValue(":ref",data.ref);
    query.bindValue(":size",data.size);
    query.bindValue(":amount",data.amount);
    query.bindValue(":prov",data.proveedor);
    query.bindValue(":color",data.color);
    if(!query.exec()){
        qWarning()<<"could no update resume items "<<query.lastError()<<query.lastQuery();
        e.log = query.lastError().text();
        e.errorCode =ErrorEvents::QueryFail;
        throw e;
    }
    return query.numRowsAffected();
}

void ItemPrivate::addItemToResume(const ItemData &data, const QSqlDatabase &db)
{
    if(updateResume(db,data) <= 0){
        insertResume(data, db);
    }
}

void ItemPrivate::addBougthtem(const ItemData &data, const QSqlDatabase &db)
{

//    addItem(db, data);
    ErrorEvents e;
    e.errorCode = ErrorEvents::UnKnown;
    if(data.ref.isEmpty() ){
        e.errorCode = ErrorEvents::NoAllowedNullValue;
        e.log =" ref value is null";
        throw e;
    }
    if(updateItemDescirption(data, db) <=0){
        addItemDescription(db, data);
    }
}

void ItemPrivate::intiError()
{
    lastError.errorCode = ErrorEvents::NoError;
    lastError.log ="";
}

bool ItemPrivate::updateBoughts(const ItemData &data)
{
    QSqlDatabase db = databaseManager.open();
    intiError();
    try {

        db.transaction();
        addBougthtem(data, db);
        addItemToResume(data, db);
        db.commit();

    } catch (ErrorEvents e) {
        lastError = e;
        qWarning()<<"Error udating items boughts"<<e.log;
        db.rollback();
    }
    db.close();
    return true;
}


void ItemPrivate::insertSale(QSqlDatabase db, const ItemData &data)
{
    const char * INSERT_DESCRIOTION_STAMENT="INSERT INTO items_sales(ref,"
            "size,amount,price,sales_date,color,prov)values(?,?,?,?,?,?,?);";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(0,data.ref);
    query.bindValue(1,data.size);
    query.bindValue(2,data.amount);
    query.bindValue(3,data.price);
    QDateTime time = QDateTime::currentDateTimeUtc();
    query.bindValue(4,time);
    query.bindValue(5,data.color);
    query.bindValue(6,data.proveedor);
    if(!query.exec()){
        qWarning()<<"could no insert items sale "<<query.lastError()<<query.lastQuery();
        lastError.errorCode = ErrorEvents::ItemNotExists;
        lastError.log = query.lastError().text();
        throw lastError;
    }
}

void ItemPrivate::registerSale(const ItemData &data)
{
    QSqlDatabase db = databaseManager.open();
    intiError();
    try{
        db.transaction();
        insertSale(db, data);
        ItemData saleData = data;
        saleData.amount = -data.amount;

        int itemsAmount =  abiableItemAmount(data, db) - data.amount;
        if(itemsAmount < 0){
            ErrorEvents e;
            e.errorCode = ErrorEvents::NotEnoughItems;
            throw e;
        }
        addItemToResume(saleData,db);
        db.commit();
    }catch(ErrorEvents e){
        lastError = e;
        qWarning()<<"error registing sale"<<e.log;
        db.rollback();
    }
}
