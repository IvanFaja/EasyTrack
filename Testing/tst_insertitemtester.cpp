#include <QString>
#include <QtTest>
#include <item.h>
#include <itemprivate.h>
class InsertItemTester : public QObject
{
    Q_OBJECT

public:
    InsertItemTester();

private Q_SLOTS:
    void addNewItem();
};

InsertItemTester::InsertItemTester()
{
}

void InsertItemTester::addNewItem()
{
    ItemPrivate test("");
    ItemData data;
    data.amount= 1;
    data.ref ="1234";
    data.size ="sx";
    test.insert(data);

    Item item;
    item.load();
    QAbstractItemModel* model =item.readOnlyModel();
    Q_ASSERT(model->columnCount()>0);
    Q_ASSERT(model->rowCount()>0);


}

QTEST_APPLESS_MAIN(InsertItemTester)

#include "tst_insertitemtester.moc"
