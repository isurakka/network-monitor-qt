#ifndef OVERVIEWUPDATER_H
#define OVERVIEWUPDATER_H

#include "applicationsettings.h"

#include <QObject>
#include <QTimer>
#include <QDebug>

#include <networkinterface.h>

class OverviewUpdater : public QObject
{
    Q_OBJECT

private:
    QTimer* timer;
    QObject* container;
    ApplicationSettings* settings;
    quint64 lastDownload;
    quint64 lastUpload;

public:
    explicit OverviewUpdater(QObject* container, ApplicationSettings* settings, QObject *parent = 0, int interval = 1000);

signals:

private slots:
    void update();

public slots:

};

#endif // OVERVIEWUPDATER_H
