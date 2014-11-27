#ifndef NETWORKGRAPH_H
#define NETWORKGRAPH_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QDebug>

#include "applicationsettings.h"
#include "transfertypedefs.h"

class NetworkGraph : public QQuickPaintedItem
{
    Q_OBJECT

private:
    const int barSpacing = 10;
    SnapshotList::iterator findDataForTime(QDateTime time);

public:
    NetworkGraph(QQuickItem *parent = 0);
    void paint(QPainter *painter);

    ApplicationSettings* settings;
    SnapshotList* snapshots;
    NetworkTransferType type;
    QColor color;
};

#endif // NETWORKGRAPH_H
