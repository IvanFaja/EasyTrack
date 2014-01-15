#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <item.h>
#include <QAbstractItemModel>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    Item item;
    QAbstractItemModel *model = item.readOnlyModel();
    item.load();

    viewer.engine()->rootContext()->setContextProperty("itemManager",&item);
    viewer.engine()->rootContext()->setContextProperty("itemReadOnlyModel",
                                                       model);
    viewer.setMainQmlFile(QStringLiteral("qml/GUI/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
