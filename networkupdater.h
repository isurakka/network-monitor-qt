#ifndef NETWORKUPDATER_H
#define NETWORKUPDATER_H

#include <QObject>
#include <QTimer>

class NetworkUpdater : public QObject
{
    Q_OBJECT

private:
    QTimer* timer;
    quint64 interval;

public:
    explicit NetworkUpdater(quint64 interval, QObject *parent = 0);

signals:

private slots:
    void update();

public slots:

};

#endif // NETWORKUPDATER_H
