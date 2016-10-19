#include <QString>
#include <QtTest>
#include <item.h>
#include <itemprivate.h>
#include <QDir>
#include <QFile>

class InsertItemTester : public QObject
{
    Q_OBJECT

public:
    InsertItemTester();

private Q_SLOTS:
    void cleanup();
    void addNewItem();
    void addSale();
    void addNotEnoutghItemsSale();
    void addInvalidItem();
private:
    QString path;
};

InsertItemTester::InsertItemTester()
{
//    path = QDir::tempPath();
//    path +="/database";
}

void InsertItemTester::cleanup()
{
//    QFile f(path);
//    if(f.exists())
//    Q_ASSERT(QFile::remove(path));
}

void InsertItemTester::addNewItem()
{
//        ItemPrivate *test =  new ItemPrivate(path);
//        ItemData data;
//        data.amount= 1;
//        data.ref ="1234";
//        data.price = 12;
//        data.color = "non";
//        data.size ="sx";
//        test->updateBoughts(data);
//        Q_ASSERT(!test->getLastError().isValid());
//        delete test;
}

void InsertItemTester::addSale()
{
//    ItemPrivate test (path);
//    ItemData data;
//    data.amount= 3;
//    data.ref ="1234";
//    data.price = 12;
//    data.color = "non";
//    data.size ="sx";
//    data.proveedor="CAlzaya";
//    test.updateBoughts(data);
//    Q_ASSERT(!test.getLastError().isValid());
//    test.registerSale(data);
//    Q_ASSERT(!test.getLastError().isValid());

}

void InsertItemTester::addNotEnoutghItemsSale()
{

//    ItemPrivate test (path);
//    ItemData data;
//    data.amount= 3;
//    data.ref ="1234";
//    data.price = 12;
//    data.color = "non";
//    data.size ="sx";
//    data.proveedor="CAlzaya";
//    test.updateBoughts(data);
//    Q_ASSERT(!test.getLastError().isValid());
//    data.amount = 5;
//    test.registerSale(data);
//    Q_ASSERT(test.getLastError().isValid());
//    Q_ASSERT(test.getLastError().errorCode == ErrorEvents::NotEnoughItems);
}

void InsertItemTester::addInvalidItem()
{
//    ItemPrivate *test =  new ItemPrivate(path);
//    ItemData data;
//    data.amount= 1;
//    data.ref ="";
//    data.price = 12;
//    data.color = "non";
//    data.size ="";
//    data.proveedor="CAlzaya";
//    test->updateBoughts(data);
//    Q_ASSERT(test->getLastError().isValid());
//    delete test;
}

QTEST_APPLESS_MAIN(InsertItemTester)

#include "tst_insertitemtester.moc"
