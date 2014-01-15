# Add more folders to ship with the application, here
folder_01.source = qml/GUI
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01
QT += sql
# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lsrc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lsrc
else:unix: LIBS += -L$$OUT_PWD/../src/ -lsrc

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

OTHER_FILES += \
    qml/GUI/InputBox.qml \
    android/AndroidManifest.xml \
    qml/GUI/PickerBox.qml

ANDROID_EXTRA_LIBS += $$OUT_PWD/../src/libsrc.so

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

