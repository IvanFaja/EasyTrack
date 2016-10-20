#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

#include "src_global.h"

class SRCSHARED_EXPORT DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    QSqlDatabase open();
    void init();

    QString getConnecntionName() const;
    void setConnecntionName(const QString &value);

    QString getDatabaseName() const;
    void setDatabaseName(const QString &value);
    void restoreBackup(const QString &file);
    void createBackup(const QString &file);

    void enableForeingKeyConstrain(QSqlDatabase db);
protected:
    virtual void create(QSqlDatabase db);
    virtual void update(QSqlDatabase db,int current,int upadted);
    virtual int newVersion()const;
private:
    void copyDataBase(const QString &sourceFile, const QString &destinationFile);
    void updateVersion(int version, QSqlDatabase db);
    void createVersionTable(QSqlDatabase db);
    int currentVersion();
    QString connecntionName;
    QString databaseName;
};

#endif // DATABASEMANAGER_H
