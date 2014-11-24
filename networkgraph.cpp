#include "networkgraph.h"

NetworkGraph::NetworkGraph(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{

}

void NetworkGraph::paint(QPainter *painter)
{
    QBrush brush(QColor("#FF0000"));
    QPen pen(QColor("#00FF00"));

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);

    auto rect = this->boundingRect();

    painter->drawRect(QRect(rect.topLeft().toPoint(), rect.bottomRight().toPoint()));
}
