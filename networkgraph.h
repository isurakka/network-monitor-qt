#ifndef NETWORKGRAPH_H
#define NETWORKGRAPH_H

#include <QQuickPaintedItem>
#include <QPainter>

#include "applicationsettings.h"
#include "transfertypedefs.h"

class NetworkGraph : public QQuickPaintedItem
{
    Q_OBJECT

private:
    const int barSpacing = 10;

public:
    NetworkGraph(QQuickItem *parent = 0);
    void paint(QPainter *painter);

    ApplicationSettings* settings;
    SnapshotList* snapshots;
};

#endif // NETWORKGRAPH_H
