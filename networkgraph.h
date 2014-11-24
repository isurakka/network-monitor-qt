#ifndef NETWORKGRAPH_H
#define NETWORKGRAPH_H

#include <QQuickPaintedItem>
#include <QPainter>

class NetworkGraph : public QQuickPaintedItem
{
    Q_OBJECT

public:
    NetworkGraph(QQuickItem *parent = 0);
    void paint(QPainter *painter);
};

#endif // NETWORKGRAPH_H
