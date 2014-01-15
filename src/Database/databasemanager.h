#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DatabaseManager
{
public:
    DatabaseManager();
    QSqlDatabase open();
    void init();

    QString getConnecntionName() const;
    void setConnecntionName(const QString &value);

    QString getDatabaseName() const;
    void setDatabaseName(const QString &value);

protected:
    virtual void create(QSqlDatabase db);
    virtual void update(QSqlDatabase db,int current,int upadted);
    virtual int newVersion()const;
private:
    void updateVersion(int version, QSqlDatabase db);
    void createVersionTable(QSqlDatabase db);
    int currentVersion();
    QString connecntionName;
    QString databaseName;
};

#endif // DATABASEMANAGER_H
