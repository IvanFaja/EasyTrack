#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QSqlTableModel>

class ItemModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = 0);

signals:

public slots:

};

#endif // ITEMMODEL_H
