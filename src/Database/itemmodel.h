#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QSqlQueryModel>
#include <QStringList>

class ItemModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        RefRole = Qt::UserRole + 1,
        SizeRole,
        AmountRole,
        PriceRole
    };
    explicit ItemModel(QObject *parent = 0);
    void addFilter(const QString &filter, const QString &value);
    void resetFiler();
    QString getBaseQuery() const;
    void setBaseQuery(const QString &value);
    void prepare(QSqlDatabase db);
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
signals:

public slots:
private:
    QString baseQuery;
    QString filter;
    bool hasFilter;
    QStringList values;

};

#endif // ITEMMODEL_H
