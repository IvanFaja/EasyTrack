#include "logicplugin_plugin.h"
#include "itemtracker.h"

#include <qqml.h>

void LogicPluginPlugin::registerTypes(const char *uri)
{
    // @uri com.sprintinventory.qml
    qmlRegisterType<ItemTracker>(uri, 1, 0, "ItemTracker");
}


