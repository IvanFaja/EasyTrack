#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <item.h>
#include <QAbstractItemModel>
#include <QQmlApplicationEngine>
#include <salesconsolidator.h>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine viewer;
    Item item;
    SalesConsolidator sales( item.getDatabaseManager());
    QAbstractItemModel *model = item.readOnlyModel();
    item.load();

    QAbstractItemModel *salesModel = sales.getSalesReportModel();
    QAbstractItemModel *salesDatesModel = sales.getSalesDatesModel();
    viewer.rootContext()->setContextProperty("itemManager",&item);
    viewer.rootContext()->setContextProperty("itemReadOnlyModel",
                                                       model);
    viewer.rootContext()->setContextProperty("salesReportModel",
                                                       salesModel);
    viewer.rootContext()->setContextProperty("salesDatesModel",
                                                       salesDatesModel);
    viewer.rootContext()->setContextProperty("sales",
                                                       &sales);
    viewer.load(QUrl("qrc:/qml/GUI/main.qml"));
//    viewer.showExpanded();

    return app.exec();
}
