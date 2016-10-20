#ifndef SALESMODEL_H
#define SALESMODEL_H

#include <QObject>
#include <QSqlQuery>
#include "itemmodel.h"

class SalesModel : public ItemModel
{
    Q_OBJECT
public:
    enum SalesItemRoles{
        DateRole = ItemModel::LastRole + 1,
        BuyPriceRole,
        ProfitRole,
        LastRole = ProfitRole
    };
    explicit SalesModel(QObject *parent = 0);
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE virtual bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    Q_INVOKABLE virtual bool setProperty(int rowIndex,const QString &property, const QVariant &value);
    void prepare( const QString& dateFilter, const QSqlDatabase & db );

    QSqlQuery updateQuery() const;
    void setUpdateQuery(const QSqlQuery &updateQuery);

signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> & roles = QVector<int> ());
public slots:
private:
    void updateResume(int row);
    void removeSale(int row, const QModelIndex &parent);
    QSqlQuery m_updateQuery;
    QSqlDatabase db;

};

#endif // SALESMODEL_H
