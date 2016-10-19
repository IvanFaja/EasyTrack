#include "salesconsolidatorprivate.h"
#include "Database/databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
SalesConsolidatorPrivate::SalesConsolidatorPrivate(DatabaseManager* databaseManager,QObject *parent) :
    QObject(parent)
{
    this->databaseManager = databaseManager;
}

void SalesConsolidatorPrivate::updateSalesDates()
{
    QSqlDatabase db = databaseManager->open();
    salesDates.prepare(db);
}
