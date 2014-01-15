#ifndef ITEM_H
#define ITEM_H

#include "src_global.h"
#include <QObject>
class ItemPrivate;
class ItemModel;
class QAbstractItemModel;
class SRCSHARED_EXPORT Item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString reference READ ref WRITE setRef)
    Q_PROPERTY(int amount READ amount WRITE setAmount)
    Q_PROPERTY(QString size READ size WRITE setSize)
    Q_PROPERTY(double price READ price WRITE setPrice)
public:
    Item();
    Q_INVOKABLE void save();
    Q_INVOKABLE void load();
    Q_INVOKABLE void sale();
    Q_INVOKABLE void reset();
    QString ref() const;
    void setRef(const QString &value);

    int amount() const;
    void setAmount(int amount);

    QString size() const;
    void setSize(const QString &size);


    QAbstractItemModel *readOnlyModel();

    double price() const;
    void setPrice(double price);

private:
    QString m_ref;
    QString m_size;
    int m_amount;
    double m_price;
    ItemPrivate *d;
    ItemModel *m_itemModel;
};

#endif // ITEM_H
