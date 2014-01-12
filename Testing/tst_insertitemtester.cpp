#include <QString>
#include <QtTest>

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
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(InsertItemTester)

#include "tst_insertitemtester.moc"
