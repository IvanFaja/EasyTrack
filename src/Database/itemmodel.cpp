#include "itemmodel.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

ItemModel::ItemModel(QObject *parent) :
    QSqlQueryModel(parent)
{

    baseQuery ="SELECT ref, size, amount, price, color, prov FROM items_resume";
    hasFilter = false;
}

void ItemModel::addFilter(const  QString &filter, const QString &value)
{
    if(hasFilter){
     this->filter += " and ";
    }
    this->filter += filter+" like ?";
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

void ItemModel::prepare(const QSqlDatabase & db)
{
    QString fullQuery = baseQuery;
    if(hasFilter){
        fullQuery += " WHERE "+ filter;
    }
    fullQuery +=" limit 100;";
    QSqlQuery q(db);
    q.prepare(fullQuery);
    foreach (QString val, values) {
        q.addBindValue("%"+val+"%");
    }
    if(!q.exec()){
         qWarning() <<"could not load items"<<q.lastError()<<q.lastQuery();
    }
    setQuery(q);
    if (lastError().isValid()){
        qWarning() << "error in query for model"<<lastError();
    }
    m_updateQuery = QSqlQuery(db);
}

bool ItemModel::setProperty(int rowIndex, const QString &property, const QVariant &value)
{
    QVariantMap rowValues = getProperty(rowIndex);
    const char * UPDATE_PRICE_RESUME="UPDATE items_resume set price = :price WHERE prov = :prov and ref = :ref and size = :size and color = :color;";
    m_updateQuery.prepare(UPDATE_PRICE_RESUME);
    m_updateQuery.bindValue(":ref",rowValues["ref"]);
    m_updateQuery.bindValue(":size",rowValues["size"]);
    m_updateQuery.bindValue(":color",rowValues["color"]);
    m_updateQuery.bindValue(":prov",rowValues["prov"]);
    m_updateQuery.bindValue(":price", value);

    if(!m_updateQuery.exec()){
        qWarning()<<"could no update resume items price"<<m_updateQuery.lastQuery();
        return false;
    }
    QHash<int, QByteArray> roles = roleNames();
    QModelIndex ind = index(rowIndex,roles.key("price"));
    QSqlQuery q = query();
    q.exec();
    setQuery(q);

    emit dataChanged(ind,ind);
    return true;
}

QHash<int, QByteArray> ItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
       roles[RefRole] = "ref";
       roles[SizeRole] = "size";
       roles[AmountRole] = "amount";
       roles[PriceRole] = "price";
       roles[ColorRole] = "color";
       roles[ProvRole] = "prov";
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

QVariantMap ItemModel::getProperty(int row)
{
    QVariantMap map;
     foreach(int k, roleNames().keys()) {
       map[roleNames().value(k)] = data(index(row, 0), k);
     }
     return map;
}

