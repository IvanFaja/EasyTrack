#ifndef ITEMPRIVATE_H
#define ITEMPRIVATE_H

#include <QObject>
#include "Database/databasemanager.h"
#include "Database/itemmodel.h"
#include "ErrorEvents.h"

struct ItemData{
    QString ref;
    QString size;
    QString color;
    QString proveedor;
    int amount;
    int price;

};

class ItemPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ItemPrivate(const QString &dbName ="", QObject *parent = 0);
    bool updateBoughts(const ItemData & data);
    void registerSale(const ItemData & data);
    void insertResume(const ItemData &data,const QSqlDatabase &db );
    int updateResume(QSqlDatabase db, const ItemData &data);
    int updateItemDescirption(const ItemData &data, const QSqlDatabase &db);
    void addItemToResume(const ItemData &data, const QSqlDatabase &db);
    void addBougthtem(const ItemData &data, const QSqlDatabase &db);
    void insertSale(QSqlDatabase db, const ItemData &data);
    int updateSale(const ItemData &data, const QSqlDatabase &db );
    int abiableItemAmount(const ItemData &data, const QSqlDatabase &db);
    ErrorEvents getLastError() const;
    void setLastError(const ErrorEvents &value);

    void intiError();
    void updatePrice(const ItemData &data, QSqlDatabase db);
signals:

public slots:
private:
    friend class Item;
    void addItemDescription(QSqlDatabase db, const ItemData &data);
    void addItem(QSqlDatabase db, const ItemData &data);
    DatabaseManager databaseManager;
    ItemModel itemModel;
    ErrorEvents lastError;

};

#endif // ITEMPRIVATE_H
