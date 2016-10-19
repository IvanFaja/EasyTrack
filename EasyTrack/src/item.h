#ifndef ITEM_H
#define ITEM_H

#include "src_global.h"
#include <QObject>
#include <QUrl>

class ItemPrivate;
class ItemModel;
class QAbstractItemModel;
class SalesModel;
struct ItemData;
class DatabaseManager;

class SRCSHARED_EXPORT Item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString reference READ ref WRITE setRef)
    Q_PROPERTY(int amount READ amount WRITE setAmount)
    Q_PROPERTY(QString size READ size WRITE setSize)
    Q_PROPERTY(double price READ price WRITE setPrice)
    Q_PROPERTY(QString color READ color WRITE setColor)
    Q_PROPERTY(QString messageText READ messageText)
    Q_PROPERTY(QString detailedInfo READ detailedInfo)
    Q_PROPERTY(QString proveedor READ proveedor WRITE setProveedor)
public:
    Item();
    Q_INVOKABLE void save();
    Q_INVOKABLE void load();
    Q_INVOKABLE void sale();
    Q_INVOKABLE void reset();
    Q_INVOKABLE void backup();
    Q_INVOKABLE void restore();
    Q_INVOKABLE void backup(const QString &folder);
    Q_INVOKABLE void restore(const QString &file);
    Q_INVOKABLE QUrl deaultBackUpPath();
    Q_INVOKABLE void openUrl(const QUrl &url);


    QString ref() const;
    void setRef(const QString &value);

    int amount() const;
    void setAmount(int amount);

    QString size() const;
    void setSize(const QString &size);


    DatabaseManager *getDatabaseManager();

    QAbstractItemModel *readOnlyModel();

    double price() const;
    void setPrice(double price);

    QString color() const;
    void setColor(const QString &color);

    void fillItemData(ItemData &data);
    SalesModel *salesModel() const;
    QString salesDate() const;
    void setSalesDate(const QDate &salesDate);

    QString messageText() const;

    QString getBackupFilePath();
    QString detailedInfo() const;

    QString proveedor() const;
    void setProveedor(const QString &proveedor);

    void cancelSale();
signals:
    void done(bool succeed);
private:
    QString getShareDirectory();
    QString m_ref;
    QString m_size;
    int m_amount;
    double m_price;
    QString m_salesDate;
    ItemPrivate *d;
    ItemModel *m_itemModel;
    QString m_color;
    QString m_detailedInfo;
    QString m_proveedor;
};

#endif // ITEM_H
