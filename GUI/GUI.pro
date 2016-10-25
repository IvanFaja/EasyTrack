
QT += sql qml quick widgets
TARGET = Stocks
SOURCES += main.cpp
RC_FILE  += Stocks.rc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lsrc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lsrc
else:unix: LIBS += -L$$OUT_PWD/../src/ -lsrc

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

OTHER_FILES += \
    qml/GUI/InputBox.qml \
    android/AndroidManifest.xml \
    qml/GUI/PickerBox.qml \
    qml/GUI/SimpleMenu.qml \
    qml/GUI/SimpleMenuItem.qml \
    qml/GUI/AddItemFrom.qml \
    qml/GUI/AddSalesItem.qml \
    qml/GUI/BackupForm.qml \
    qml/GUI/main.qml \
    qml/GUI/MessageBox.qml \
    qml/GUI/SalesReportForm.qml \
    qml/GUI/SimpleButton.qml \
    qml/GUI/SimpleDialog.qml

ANDROID_EXTRA_LIBS += $$OUT_PWD/../src/libsrc.so

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    resources.qrc

