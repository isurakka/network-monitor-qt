#ifndef HOURLYMODEL_H
#define HOURLYMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include <QMap>
#include <QDateTime>
#include <QDate>
#include <QTime>

#include "networkstorage.h"
#include "applicationsettings.h"

class HourlyModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    NetworkStorage* storage;
    ApplicationSettings* settings;

public:
    explicit HourlyModel(ApplicationSettings* settings, NetworkStorage* storage, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // HOURLYMODEL_H
