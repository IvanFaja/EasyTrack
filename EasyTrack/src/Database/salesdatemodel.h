#ifndef SALESDATEMODEL_H
#define SALESDATEMODEL_H
#include "itemmodel.h"
class SalesDateModel : public ItemModel
{
    Q_OBJECT
public:
    enum SalesDateRoles {
        YearMonthRole = Qt::UserRole + 1,
        LastRole = YearMonthRole
    };
    explicit SalesDateModel(QObject *parent = 0);
    virtual QHash<int, QByteArray> roleNames() const;

signals:

public slots:

};

#endif // SALESDATEMODEL_H
