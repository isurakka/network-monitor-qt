#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QVariant>

#include "networkinterface.h"
#include "networkunit.h"

class ApplicationSettings : public QObject
{
    Q_OBJECT

public:
    explicit ApplicationSettings(QObject *parent = 0);
    NetworkInterface getCurrentInterface();
    NetworkUnit getCurrentUnit();

signals:

public slots:

};

#endif // APPLICATIONSETTINGS_H
