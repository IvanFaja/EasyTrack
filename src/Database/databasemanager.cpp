#include "databasemanager.h"
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QFile>
#include <QFileInfo>

#include "ErrorEvents.h"

DatabaseManager::DatabaseManager()
{
    connecntionName ="itemTracker";
}

DatabaseManager::~DatabaseManager()
{
    QSqlDatabase::removeDatabase(connecntionName);
}

void DatabaseManager::enableForeingKeyConstrain(QSqlDatabase db)
{
    QSqlQuery query(db);
    if(!query.exec("PRAGMA foreign_keys = ON;")){
        qWarning()<<"could not enable foreing keys";
    }
}

QSqlDatabase DatabaseManager::open()
{
    QSqlDatabase db;
    if( QSqlDatabase::contains(connecntionName) ){
        db = QSqlDatabase::database(connecntionName,true);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",connecntionName);
        db.setDatabaseName(databaseName);
        db.open();
        enableForeingKeyConstrain(db);
    }
    if(!db.isOpen()){
        qWarning()<<"data base could not be opened"<<db.connectionName()<<db.databaseName()<<db.lastError().text();
    }
    return db;
}

void DatabaseManager::create(QSqlDatabase db)
{
//    const char * ITEMS_TABLE ="CREATE TABLE items(ref TEXT PRIMARY KEY );";
    const char * ITEMS_DESCRIPTION_TABLE ="CREATE TABLE items_description("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "size TEXT,amount INTEGER NOT NULL, "
            "color TEXT, "
            "price REAL NOT NULL,"
            "ref TEXT NOT NULL,"
            "prov TEXT,"
            "UNIQUE(prov,ref,size,color) ON CONFLICT FAIL) ";
    const char * ITEMS_SALES_TABLE ="CREATE TABLE items_sales("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "size TEXT,sales_date INTEGER, "
            "amount INTEGER NOT NULL, "
            "color TEXT, "
            "price REAL NOT NULL,"
            "ref TEXT NOT NULL,"
            "prov TEXT,"
            "FOREIGN KEY(prov,ref,size,color) REFERENCES items_description(prov,ref,size,color));";
    const char * ITEMS_TOTAL_RESUME_TABLE ="CREATE TABLE items_resume("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "size TEXT,amount INTEGER NOT NULL, "
            "price REAL NOT NULL,"
            "ref TEXT NOT NULL,"
            "color TEXT, "
            "prov TEXT,"
            "UNIQUE(prov,ref,size,color) ON CONFLICT FAIL);";
    const char * ITEMS_COLORS_TABLE ="CREATE TABLE items_colors(color TEXT);";
    QSqlQuery query(db);
//    if(!query.exec(ITEMS_TABLE)){
//        qWarning()<<"could not create database"<<query.lastError().text();
//    }
    if(!query.exec(ITEMS_DESCRIPTION_TABLE)){
        qWarning()<<"could not create database"<<query.lastError().text()<<query.lastQuery();
    }
    if(!query.exec(ITEMS_SALES_TABLE)){
        qWarning()<<"could not create sales tables"<<query.lastError().text();
    }
    if(!query.exec(ITEMS_TOTAL_RESUME_TABLE)){
        qWarning()<<"could not create remusme table"<<query.lastError().text()<<query.lastQuery();
    }
    if(!query.exec(ITEMS_COLORS_TABLE)){
        qWarning()<<"could not create color table"<<query.lastError().text()<<query.lastQuery();
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

void DatabaseManager::copyDataBase(const QString &sourceFile,const QString &destinationFile)
{
    QFile file(destinationFile);
    file.remove();
    bool ok = QFile::copy(sourceFile,destinationFile);
    if(!ok){
        ErrorEvents e;
        e.errorCode = ErrorEvents::BackupFail;
        e.log = "fail to copy database";
        qWarning()<<"could not create Backup"<<file.errorString();
        throw e;
    }
}

void DatabaseManager::restoreBackup(const QString &file)
{
    open().close();
    QString backup = databaseName +".orgin";
    try {
        copyDataBase(databaseName,backup);

    } catch (ErrorEvents e) {
        qWarning()<<"could not create Backup file firts abroting";
        e.errorCode = ErrorEvents::ResctoreBackupAbrot;
        throw e;
    }
    try {
        QFile currentDataBase(databaseName);
        currentDataBase.remove();
        copyDataBase(file,databaseName);

    } catch (ErrorEvents e) {
        qWarning()<<"fail to restore backup, unroling";
        copyDataBase(backup,databaseName);
        e.errorCode = ErrorEvents::ResctoreBackupAbrot;
        throw e;
    }
}

void DatabaseManager::createBackup(const QString &file)
{
    copyDataBase(databaseName,file);
}

QString DatabaseManager::getConnecntionName() const
{
    return connecntionName;
}

void DatabaseManager::setConnecntionName(const QString &value)
{
    connecntionName = value;
}

