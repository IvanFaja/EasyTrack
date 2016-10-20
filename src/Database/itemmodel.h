#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QSqlQueryModel>
#include <QStringList>
#include <QSqlQuery>

class ItemModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        RefRole = Qt::UserRole + 1,
        SizeRole,
        AmountRole,
        PriceRole,
        ColorRole,
        ProvRole,
        LastRole =ProvRole
    };

    explicit ItemModel(QObject *parent = 0);
    void addFilter(const QString &filter, const QString &value);
    void resetFiler();
    QString getBaseQuery() const;
    void setBaseQuery(const QString &value);
    void prepare(const QSqlDatabase &db);
    Q_INVOKABLE virtual bool setProperty(int rowIndex,const QString &property, const QVariant &value);
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE virtual QVariantMap getProperty(int row);
signals:

public slots:
protected:
    QString baseQuery;
    QSqlQuery m_updateQuery;
private:
    QString filter;
    bool hasFilter;
    QStringList values;

};

#endif // ITEMMODEL_H
