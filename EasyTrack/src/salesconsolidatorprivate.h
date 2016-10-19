#ifndef SALESCONSOLIDATORPRIVATE_H
#define SALESCONSOLIDATORPRIVATE_H

#include <QObject>
#include <QStringList>
#include "Database/salesdatemodel.h"

class DatabaseManager;
class SalesConsolidatorPrivate : public QObject
{
    Q_OBJECT
public:
    explicit SalesConsolidatorPrivate(DatabaseManager* databaseManager,QObject *parent = 0);
    void updateSalesDates();
signals:

public slots:
private:
    friend class SalesConsolidator;
    DatabaseManager* databaseManager;
    SalesDateModel salesDates;


};

#endif // SALESCONSOLIDATORPRIVATE_H
