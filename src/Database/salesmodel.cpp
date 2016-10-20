#include "salesmodel.h"
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SalesModel::SalesModel(QObject *parent) :
    ItemModel(parent)
{
    baseQuery ="SELECT items_sales.ref,"
            "items_sales.size, "
            "items_sales.amount,"
            "items_sales.price as sales_price, "
            "items_sales.color, "
            "items_sales.prov, "
            "sales_date,"
            "items_resume.price as buy_price,"
            "(items_sales.price - items_resume.price)*items_sales.amount as profit "
            " FROM "
            "items_sales INNER JOIN items_resume ON items_sales.ref = items_resume.ref "
            "and items_sales.color = items_resume.color and items_sales.size = items_resume.size and items_sales.prov = items_resume.prov";

}

QHash<int, QByteArray> SalesModel::roleNames() const
{
    QHash<int, QByteArray> roles( ItemModel::roleNames());
    roles[DateRole] = "date";
    roles[BuyPriceRole] = "buyPrice";
    roles[ProfitRole] = "profit";
    return roles;
}

QVariant SalesModel::data(const QModelIndex &index, int role) const
{
    QVariant value = ItemModel::data(index, role);;
//    if(role == DateRole)
//    {
//        value = value.toDateTime().toLocalTime();

//    }

    return value;

}

void SalesModel::removeSale(int row, const QModelIndex &parent)
{

    QSqlQuery deleter(db);
    QVariantMap rowValues = getProperty(row);
    const char * UPDATE_STAMENT="DELETE FROM items_sales WHERE prov = :prov"
            " and ref = :ref and size = :size and color = :color"
            " and sales_date = :sales_date;";

    deleter.prepare(UPDATE_STAMENT);
    deleter.bindValue(":ref",rowValues["ref"]);
    deleter.bindValue(":size",rowValues["size"]);
    deleter.bindValue(":color",rowValues["color"]);
    deleter.bindValue(":prov",rowValues["prov"]);
    deleter.bindValue(":sales_date",rowValues["date"]);

    if(!deleter.exec()){
        qDebug()<<"delete fail"<<deleter.lastQuery();
    }

}

void SalesModel::updateResume(int row)
{

    QVariantMap rowValues = getProperty(row);
    const char * INSERT_DESCRIOTION_STAMENT="UPDATE items_resume set amount = amount + :amount WHERE prov = :prov and ref = :ref and size = :size and color = :color;";
    QSqlQuery query(db);
    query.prepare(INSERT_DESCRIOTION_STAMENT);
    query.bindValue(":ref",rowValues["ref"]);
    query.bindValue(":size",rowValues["size"]);
    query.bindValue(":amount",rowValues["amount"]);
    query.bindValue(":color",rowValues["color"]);
    query.bindValue(":prov",rowValues["prov"]);
    if(!query.exec()){
        qWarning()<<"could no update resume items "<<query.lastQuery();
    }

}

bool SalesModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent,row,row);
    qDebug()<<"deleting sale";
    removeSale(row, parent);
    updateResume(row);
    return true;
    endRemoveRows();
}

bool SalesModel::setProperty(int rowIndex, const QString &property, const QVariant &value)
{

    QVariantMap rowValues = getProperty(rowIndex);
    const char * UPDATE_STAMENT="UPDATE items_sales set price = :price WHERE prov = :prov and ref = :ref "
            "and size = :size and color = :color and sales_date = :sales_date;";
    m_updateQuery.prepare(UPDATE_STAMENT);
    m_updateQuery.bindValue(":ref",rowValues["ref"]);
    m_updateQuery.bindValue(":size",rowValues["size"]);
    m_updateQuery.bindValue(":color",rowValues["color"]);
    m_updateQuery.bindValue(":prov",rowValues["prov"]);
    m_updateQuery.bindValue(":sales_date",rowValues["date"]);
    m_updateQuery.bindValue(":price", value);
    if(!m_updateQuery.exec()){
        qWarning()<<"could no update sales "<<m_updateQuery.lastQuery();
        return false;

    }
    qDebug()<<"price updated "<<value;
    QHash<int, QByteArray> roles = roleNames();
    QModelIndex ind = index(rowIndex,roles.key("price"));
    QSqlQuery q = query();
    q.exec();
    setQuery(q);

    emit dataChanged(ind,ind);
    return true;

}


void SalesModel::prepare(const QString &dateFilter, const QSqlDatabase &db)
{
    this->db = db;
    QString fullQuery = baseQuery;
    fullQuery += " WHERE strftime('%Y-%m', sales_date) = ? ";
    fullQuery += " limit 100;";
    QSqlQuery q(db);
    q.prepare(fullQuery);
    q.addBindValue(dateFilter);
    if(!q.exec()){
        qWarning() <<"could not load sales report"<<q.lastError()<<q.lastQuery();
    }
    setQuery(q);
    if (lastError().isValid()){
        qWarning() << "error in query for model sales report"<<lastError();
    }

    QSqlQuery qupdate(db);
    setUpdateQuery(qupdate);

}
QSqlQuery SalesModel::updateQuery() const
{
    return m_updateQuery;
}

void SalesModel::setUpdateQuery(const QSqlQuery &updateQuery)
{
    m_updateQuery = updateQuery;
}



