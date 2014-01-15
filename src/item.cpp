#include "item.h"
#include "itemprivate.h"
#include "Database/itemmodel.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

Item::Item()
{
    d = new ItemPrivate("",this);
    m_itemModel = new ItemModel(this);

}

void Item::save()
{
    ItemData data;
    data.amount = amount();
    data.ref = ref();
    data.size = size();
    data.price = m_price;
    d->insert(data);
}

void Item::load()
{
    m_itemModel->resetFiler();
    if(!m_ref.isEmpty()){
        m_itemModel->addFilter("ref",m_ref);
    }
    if(!m_size.isEmpty()){
        m_itemModel->addFilter("size",m_size);
    }
    QSqlDatabase db = d->databaseManager.open();
    m_itemModel->prepare(db);
}

void Item::sale()
{
    ItemData data;
    data.amount = amount();
    data.ref = ref();
    data.size = size();
    data.price = m_price;
    d->registerSale(data);
}

void Item::reset()
{
    m_amount =1;
    m_price = 0;
    m_ref = "";
    m_size = "";
}
QString Item::ref() const
{
    return m_ref;
}

void Item::setRef(const QString &value)
{
    m_ref = value;
}
int Item::amount() const
{
    return m_amount;
}

void Item::setAmount(int amount)
{
    m_amount = amount;
}
QString Item::size() const
{
    return m_size;
}

void Item::setSize(const QString &size)
{
    m_size = size.toLower();
}
QAbstractItemModel *Item::readOnlyModel()
{
    m_itemModel->prepare(d->databaseManager.open());
    return m_itemModel;
}
double Item::price() const
{
    return m_price;
}

void Item::setPrice(double price)
{
    m_price = price;
}






