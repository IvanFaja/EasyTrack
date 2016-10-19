#include "item.h"
#include "itemprivate.h"
#include "Database/itemmodel.h"
#include "Database/salesmodel.h"
#include "ErrorEvents.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QUrl>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QDesktopServices>

Item::Item()
{
    d = new ItemPrivate("",this);
    m_itemModel = new ItemModel(this);
}

void Item::fillItemData(ItemData& data)
{
    data.amount = amount();
    data.ref = ref();
    data.size = size();
    data.price = m_price;
    data.color = m_color;
    data.proveedor = m_proveedor;

}


void Item::save()
{
    m_detailedInfo.clear();
    ItemData data;
    fillItemData(data);
    d->updateBoughts(data);
    emit done(!d->lastError.isValid());
}

void Item::load()
{
    m_detailedInfo.clear();
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
    m_detailedInfo.clear();
    ItemData data;
    fillItemData(data);
    d->registerSale(data);
    emit done(!d->lastError.isValid());
}

void Item::cancelSale()
{
    m_detailedInfo.clear();
    ItemData data;
    data.amount = -data.amount;
    fillItemData(data);
    d->updateResume(d->databaseManager.open(),data);
    emit done(!d->lastError.isValid());
}

void Item::reset()
{
    m_detailedInfo.clear();
    m_amount =1;
    m_price = 0;
    m_ref = "";
    m_size = "";
    m_color ="";
    m_proveedor ="";
}

QString Item::getBackupFilePath()
{
    QString dir = getShareDirectory();

    dir.append("/backup.db");

    return dir;
}

void Item::backup()
{
    QString dir = getBackupFilePath();
    m_detailedInfo = tr("En :")+dir;
    backup(dir);

}

void Item::restore()
{

    QString dir = getBackupFilePath();
    m_detailedInfo = tr("En :")+dir;
    restore(dir);
}

void Item::backup(const QString &fileUrl)
{
    try {

        d->databaseManager.createBackup(fileUrl);

    } catch (ErrorEvents e) {
        d->lastError = e;
    }
    emit done(!d->lastError.isValid());
}

void Item::restore(const QString &file)
{
    try {
        d->databaseManager.restoreBackup(file);
    } catch (ErrorEvents e) {
        d->lastError = e;
    }
    emit done(!d->lastError.isValid());
}

QString Item::getShareDirectory()
{
    QString ext;
#if defined(Q_OS_ANDROID)
    ext = getenv("EXTERNAL_STORAGE");
#else
    ext = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
#endif
    ext +="/"+QCoreApplication::applicationName();
    QDir dir(ext);
    if(!dir.exists()){
        dir.mkpath(ext);
    }

    return ext;
}
QString Item::proveedor() const
{
    return m_proveedor;
}

void Item::setProveedor(const QString &proveedor)
{
    m_proveedor = proveedor;
}

QString Item::detailedInfo() const
{
    return m_detailedInfo;
}


QUrl Item::deaultBackUpPath()
{
    QString ext = getShareDirectory();
    QUrl path = QUrl::fromLocalFile(ext);
    return path;
}

void Item::openUrl(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}

QString Item::ref() const
{
    return m_ref;
}

QString Item::messageText() const
{
    switch (d->lastError.errorCode) {
    case ErrorEvents::ItemNotExists:
        return tr("El tiem no existe");
    case ErrorEvents::NotEnoughItems:
        return tr("El no hay suficientes items");
    case ErrorEvents::UnKnown:
        return tr("Ocurrio un error deconocido");
    case ErrorEvents::NoError:
        return tr("Los datos se guardaron correctamente");
    case ErrorEvents::NoAllowedNullValue:
        return tr("La referencia no puede ser nula");
    case ErrorEvents::ResctoreBackupAbrot:
    case ErrorEvents::BackupFail:
        return tr("No se puede aseguar la integridad de los datos,"
                  "asegurese que ningun archivo este abierto o dando");
    case ErrorEvents::QueryFail:
        return tr("Existen inconsistencias con la base datos,"
                  "asegurese de haber restaurado la aplicacion con un archivo valido");
    default:
        break;
    }
    return"";
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

DatabaseManager *Item::getDatabaseManager()
{
    return &(d->databaseManager);
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
QString Item::color() const
{
    return m_color;
}

void Item::setColor(const QString &color)
{
    m_color = color;
}







