#ifndef SALESCONSOLIDATOR_H
#define SALESCONSOLIDATOR_H

#include <QObject>
#include "src_global.h"
#include "Database/databasemanager.h"

class SalesConsolidatorPrivate;
class DatabaseManager;
class QAbstractItemModel;
class SalesModel;
class SRCSHARED_EXPORT SalesConsolidator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString reportFilter READ salesDateFilter WRITE setSalesDateFilter)
    Q_PROPERTY(qreal totalSales READ totalSales NOTIFY totalsChanged)
    Q_PROPERTY(qreal totalProfit READ totalProfit NOTIFY totalsChanged)

public:
    explicit SalesConsolidator( DatabaseManager* databaseManager , QObject *parent = 0);
    QAbstractItemModel *getSalesDatesModel();
    QAbstractItemModel *getSalesReportModel();
    Q_INVOKABLE void loadSalesDates();
    Q_INVOKABLE void loadSalesReport();
    QString salesDateFilter() const;
    void setSalesDateFilter(const QString &salesDateFilter);

    qreal totalSales() const;

    qreal totalProfit() const;

signals:
    void totalsChanged();
public slots:
private:

    void loadRepostTotals(QSqlDatabase db);
    SalesConsolidatorPrivate * d;
    SalesModel *m_salesModel;
    QString m_salesDateFilter;
    qreal m_totalSales;
    qreal m_totalProfit;


};

#endif // SALESCONSOLIDATOR_H
