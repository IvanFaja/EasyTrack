#include "databasemanager.h"
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
DatabaseManager::DatabaseManager()
{
       connecntionName ="itemTracker";
}

QSqlDatabase DatabaseManager::open()
{
    QSqlDatabase db;
    if( QSqlDatabase::contains(connecntionName) ){
        db = QSqlDatabase::database(connecntionName,false);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",connecntionName);
        db.setDatabaseName(databaseName);
    }
    if(!db.open()){
        qWarning()<<"data base could not be opened"<<db.connectionName()<<db.databaseName()<<db.lastError().text();
    }
    return db;
}

void DatabaseManager::create(QSqlDatabase db)
{
    const char * ITEMS_TABLE ="CREATE TABLE items(ref TEXT PRIMARY KEY );";
    const char * ITEMS_DESCRIPTION_TABLE ="CREATE TABLE items_description("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "size TEXT,amount INTEGER, "
            "price REAL,"
            " ref TEXT,"
            "UNIQUE(ref,size) ON CONFLICT FAIL, "
            "FOREIGN KEY(ref) REFERENCES items(ref));";
    const char * ITEMS_SALES_TABLE ="CREATE TABLE items_sales("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "size TEXT,sales_date INTEGER, "
            "amount INTEGER, "
            "price REAL,"
            " ref TEXT,"
            "UNIQUE(ref,size) ON CONFLICT FAIL, "
            "FOREIGN KEY(ref,size) REFERENCES items_description(ref,size));";
    const char * ITEMS_TOTAL_RESUME_TABLE ="CREATE TABLE items_resume("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "size TEXT,amount INTEGER, "
            "price REAL,"
            "ref TEXT,"
            "UNIQUE(ref,size) ON CONFLICT FAIL);";
    QSqlQuery query(db);
    if(!query.exec(ITEMS_TABLE)){
        qWarning()<<"could not create database"<<query.lastError().text();
    }
    if(!query.exec(ITEMS_DESCRIPTION_TABLE)){
        qWarning()<<"could not create database"<<query.lastError().text();
    }
    if(!query.exec(ITEMS_SALES_TABLE)){
        qWarning()<<"could not create sales tables"<<query.lastError().text();
    }
    if(!query.exec(ITEMS_TOTAL_RESUME_TABLE)){
        qWarning()<<"could not create remusme table"<<query.lastError().text()<<query.lastQuery();
    }
}

void DatabaseManager::update(QSqlDatabase db, int current, int upadted)
{

}

int DatabaseManager::newVersion() const
{
    return 1;
}

void DatabaseManager::init()
{
    QSqlDatabase db = open();
    if( db.tables().isEmpty()){
        createVersionTable(db);
        create(db);
    }else {
        update(db,currentVersion(),newVersion());
    }
    qDebug()<<"database path"<<db.databaseName();
}

void DatabaseManager::updateVersion(int version, QSqlDatabase db)
{
    const char * VERSION_UPDATE ="insert into version(history) values(?);";
    QSqlQuery query(VERSION_UPDATE,db);
    query.addBindValue(version);
    query.exec();
}

void DatabaseManager::createVersionTable(QSqlDatabase db)
{
    const char * VERSION_TABLE_CREATION ="create table version (history INTEGER PRIMATY KEY DES )";
    db.exec(VERSION_TABLE_CREATION);
    int version = newVersion();
    updateVersion(version, db);

}

int DatabaseManager::currentVersion()
{
    const char * VERSION_QUERY ="select history from version order by history desc imit 1;";
    QSqlDatabase db = open();
    QSqlQuery query(VERSION_QUERY,db);
    query.exec();
    int version = 0;
    if(query.first()){
        version = query.value("history").toInt();
    }
    return version;
}
QString DatabaseManager::getDatabaseName() const
{
    return databaseName;
}

void DatabaseManager::setDatabaseName(const QString &value)
{
    databaseName = value;
}

QString DatabaseManager::getConnecntionName() const
{
    return connecntionName;
}

void DatabaseManager::setConnecntionName(const QString &value)
{
    connecntionName = value;
}

