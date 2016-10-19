#include "salesconsolidator.h"
#include "salesconsolidatorprivate.h"
#include "Database/salesmodel.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

SalesConsolidator::SalesConsolidator( DatabaseManager* databaseManager,QObject *parent) :
    QObject(parent)
{
    d = new SalesConsolidatorPrivate(databaseManager);
    m_salesModel = new SalesModel(this);
}

QAbstractItemModel * SalesConsolidator::getSalesDatesModel()
{
    d->updateSalesDates();
    return &(d->salesDates);
}

QAbstractItemModel *SalesConsolidator::getSalesReportModel()
{
    loadSalesReport();
    return m_salesModel;
}

void SalesConsolidator::loadSalesDates()
{
    d->updateSalesDates();
}

void SalesConsolidator::loadRepostTotals(QSqlDatabase db)
{
    const char *TOTALS_QUERY="SELECT SUM((items_sales.price - items_resume.price)*items_sales.amount) as total_profit , SUM( items_sales.price) as total_sales FROM "
            "items_sales INNER JOIN items_resume ON items_sales.ref = items_resume.ref "
            "and items_sales.color = items_resume.color and items_sales.size = items_resume.size and "
            "items_sales.prov = items_resume.prov "
            "WHERE strftime('%Y-%m', sales_date) = ?;";
    QSqlQuery query(TOTALS_QUERY,db);
    query.addBindValue(m_salesDateFilter);
    bool ok = query.exec();
    if( ok && query.first() ){
        m_totalProfit = query.value(0).toDouble(&ok);
        m_totalSales = query.value(1).toDouble(&ok);
        emit totalsChanged();
    }else{
        qWarning()<<"could not calculate totals"<<query.lastError()<<query.lastQuery();
    }
}

void SalesConsolidator::loadSalesReport()
{
    QSqlDatabase db = d->databaseManager->open();
    m_salesModel->prepare(m_salesDateFilter,db);
    loadRepostTotals(db);

}
QString SalesConsolidator::salesDateFilter() const
{
    return m_salesDateFilter;
}

void SalesConsolidator::setSalesDateFilter(const QString &salesDateFilter)
{
    m_salesDateFilter = salesDateFilter;
}
qreal SalesConsolidator::totalSales() const
{
    return m_totalSales;
}

qreal SalesConsolidator::totalProfit() const
{
    return m_totalProfit;
}



