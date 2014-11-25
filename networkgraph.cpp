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

    auto barCount =  std::floor(QVariant(rect.width() / (qreal)barSpacing).toInt());

    auto dateTime = QDateTime::currentDateTimeUtc();

    for (int i = 0; i < barCount; i++)
    {
        auto nextTime = QDateTime(dateTime);
        nextTime.setTime(dateTime.time().addSecs(-1));

        SnapshotList::iterator i;
        for (i = (*snapshots).begin(); i != (*snapshots).end(); ++i)
        {
            if ((*i).first == dateTime && (*(++i)).first == nextTime)
            {
                // Draw line
                break;
            }
        }

        dateTime = nextTime;
    }

    for (auto& snapshot : *snapshots)
    {
        //snapshot
    }

    painter->drawRect(QRect(rect.topLeft().toPoint(), rect.bottomRight().toPoint()));
}
