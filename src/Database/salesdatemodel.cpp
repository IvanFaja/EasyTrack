#include "salesdatemodel.h"

SalesDateModel::SalesDateModel(QObject *parent) :
    ItemModel(parent)
{
    const char * SALES_DATES="SELECT DISTINCT strftime('%Y-%m', sales_date) FROM items_sales ";

    baseQuery = SALES_DATES;

}

QHash<int, QByteArray> SalesDateModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[YearMonthRole] = "yearMonth";
    return roles;
}
