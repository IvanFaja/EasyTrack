#ifndef ITEMPRIVATE_H
#define ITEMPRIVATE_H

#include <QObject>

class ItemPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ItemPrivate(QObject *parent = 0);

signals:

public slots:

};

#endif // ITEMPRIVATE_H
