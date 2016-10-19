#ifndef ITEMTRACKER_H
#define ITEMTRACKER_H

#include <QQuickItem>

class ItemTracker : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(ItemTracker)

public:
    ItemTracker(QQuickItem *parent = 0);
    ~ItemTracker();
};

#endif // ITEMTRACKER_H

