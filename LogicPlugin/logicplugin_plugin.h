#ifndef LOGICPLUGIN_PLUGIN_H
#define LOGICPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class LogicPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // LOGICPLUGIN_PLUGIN_H

