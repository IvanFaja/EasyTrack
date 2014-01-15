#include "itemmodel.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

ItemModel::ItemModel(QObject *parent) :
    QSqlQueryModel(parent)
{

    baseQuery ="SELECT ref, size, amount, price FROM items_resume";
    hasFilter = false;

}

void ItemModel::addFilter(const  QString &filter, const QString &value)
{
    if(hasFilter){
     this->filter += " and ";
    }
    this->filter += filter+" = ?";
    values.append(value);
    hasFilter = true;

}

void ItemModel::resetFiler()
{
    filter ="";
    hasFilter = false;
    values.clear();
}
QString ItemModel::getBaseQuery() const
{
    return baseQuery;
}

void ItemModel::setBaseQuery(const QString &value)
{
    baseQuery = value;
}

void ItemModel::prepare(QSqlDatabase db)
{
    QString fullQuery = baseQuery;
    if(hasFilter){
        fullQuery += " WHERE "+ filter;
    }
    fullQuery +=" limit 20;";
    QSqlQuery q(db);
    q.prepare(fullQuery);
    foreach (QString val, values) {
        q.addBindValue(val);
    }
    if(!q.exec()){
         qWarning() <<"could not load items"<<q.lastError()<<q.lastQuery();
    }
    setQuery(q);
    if (lastError().isValid()){
        qWarning() << "error in query for model"<<lastError();
    }
}

QHash<int, QByteArray> ItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
       roles[RefRole] = "ref";
       roles[SizeRole] = "size";
       roles[AmountRole] = "amount";
       roles[PriceRole] = "price";
       return roles;
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
       if(role < Qt::UserRole)
       {
           value = QSqlQueryModel::data(index, role);
       }
       else
       {
           int columnIdx = role - Qt::UserRole - 1;
           QModelIndex modelIndex = this->index(index.row(), columnIdx);
           value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
       }
       return value;
}

