#ifndef ITEMPRIVATE_H
#define ITEMPRIVATE_H

#include <QObject>
#include "Database/databasemanager.h"
#include "Database/itemmodel.h"
struct ItemData{
    QString ref;
    QString size;
    int amount;
    int price;

};

class ItemPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ItemPrivate(const QString &dbName ="", QObject *parent = 0);
    bool insert(const ItemData & data);
    void registerSale(const ItemData & data);
    void insertResume(const ItemData &data, QSqlDatabase db);
    int updateResume(QSqlDatabase db, const ItemData &data);
    int updateItemDescirption(const ItemData &data, QSqlDatabase db);
    void addItemToResume(const ItemData &data, QSqlDatabase db);
    void addBuyItem(const ItemData &data, QSqlDatabase db);
    void insertSale(QSqlDatabase db, const ItemData &data);
signals:

public slots:
private:
    friend class Item;
    void addItemDescription(QSqlDatabase db, const ItemData &data);
    void addItem(QSqlDatabase db, const ItemData &data);
    DatabaseManager databaseManager;
    ItemModel itemModel;

};

#endif // ITEMPRIVATE_H
