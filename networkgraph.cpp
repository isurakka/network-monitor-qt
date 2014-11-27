#include "networkgraph.h"

NetworkGraph::NetworkGraph(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{

}

void NetworkGraph::paint(QPainter *painter)
{
    const int penWidth = 3;
    const qreal margin = (qreal)penWidth / (qreal)2;

    QBrush brush(QColor("#bdc3c7"));
    QPen pen(color);
    pen.setWidth(penWidth);

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);

    auto rect = this->boundingRect();

    pen.setColor(brush.color().darker(150));
    painter->setPen(pen);
    painter->drawRect(rect);

    pen.setColor(color);
    painter->setPen(pen);

    rect = QRectF(
                rect.left() + margin,
                rect.top() + margin,
                rect.width() - margin * (qreal)2,
                rect.height() - margin * (qreal)2);

    auto barCount =  std::floor(QVariant(rect.width() / (qreal)barSpacing).toInt());

    auto dateTimeMax = QDateTime::currentDateTimeUtc();
    auto time = dateTimeMax.time();
    dateTimeMax.setTime(QTime(time.hour(), time.minute(), time.second()));
    //dateTimeMax.setTime(dateTimeMax.time().addSecs(-1));

    auto dateTimeMin = dateTimeMax;
    dateTimeMin.setTime(dateTimeMax.time().addSecs(-barCount));

    auto ifName = settings->getCurrentInterface().getName();

    // Calculate max value
    graphMax = 0;
    SnapshotList::iterator j;
    for (j = (*snapshots).begin(); j != (*snapshots).end(); ++j)
    {
        auto pair = (*j);
        if (pair.first > dateTimeMax || pair.first < dateTimeMin)
        {
            continue;
        }

        auto trPair = pair.second.value(ifName);

        graphMax = qMax(graphMax, trPair.value(type));
    }

    // Draw lines
    auto end = (*snapshots).end();
    int i = -1;
    for (
         QDateTime currentDateTime = dateTimeMax;
         currentDateTime >= dateTimeMin;
         currentDateTime.setTime(currentDateTime.time().addSecs(-1)))
    {
        i++;

        auto nextDateTime = currentDateTime;
        nextDateTime.setTime(currentDateTime.time().addSecs(-1));

        if (nextDateTime < dateTimeMin)
        {
            continue;
        }

        auto curIt = findDataForTime(currentDateTime);
        auto nexIt = findDataForTime(nextDateTime);

        if (curIt == end || nexIt == end)
        {
            continue;
        }

        auto curDlVal = curIt->second.value(ifName).value(type);
        auto nexDlVal = nexIt->second.value(ifName).value(type);

        auto perCurDl = (qreal)curDlVal / (qreal)graphMax;
        auto perNexDl = (qreal)nexDlVal / (qreal)graphMax;

        auto p1 = rect.topLeft() + QPointF(
                    rect.width() - rect.width() * (i / barCount),
                    rect.height() - rect.height() * perCurDl);
        auto p2 = rect.topLeft() + QPointF(
                    rect.width() - rect.width() * ((i + 1) / barCount),
                    rect.height() - rect.height() * perNexDl);

        painter->drawLine(p1, p2);
    }
}

SnapshotList::iterator NetworkGraph::findDataForTime(QDateTime time)
{
    SnapshotList::iterator i;
    for (i = (*snapshots).begin(); i != (*snapshots).end(); ++i)
    {
        auto pair = (*i);

        auto snapshotTime = pair.first;
        snapshotTime.setTime(QTime(snapshotTime.time().hour(), snapshotTime.time().minute(), snapshotTime.time().second()));

        if (snapshotTime == time)
        {
            return i;
        }
    }

    return (*snapshots).end();
}
