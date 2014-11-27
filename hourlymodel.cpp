#include "hourlymodel.h"

HourlyModel::HourlyModel(ApplicationSettings* settings, NetworkStorage* storage, QObject *parent) :
    QAbstractTableModel(parent),
    settings(settings),
    storage(storage)
{

}

int HourlyModel::rowCount(const QModelIndex &parent) const
{
    auto ifName = settings->getCurrentInterface().getName();
    return storage->savedData.value(ifName).count();
}

int HourlyModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant HourlyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    qDebug() << QString("row %1, col%2, role %3")
         .arg(row).arg(col).arg(role);

    auto ifName = settings->getCurrentInterface().getName();

    auto pair = storage->savedData.value(ifName).begin() + row;
    auto date = pair.key().date();
    auto time = pair.key().time();
    auto locale = QLocale();

    auto unit = settings->getCurrentUnit();
    auto realBytes = (qreal)unit.getBytes();

    auto unitPost = " " + unit.getDisplayName();

    if (role == 0)
    {
        return locale.toString(date, QLocale::ShortFormat);
    }
    else if (role == 1)
    {
        return locale.toString(time, QLocale::ShortFormat) + " - " + locale.toString(time.addSecs(3599), QLocale::ShortFormat);
    }
    else if (role == 2)
    {
        auto final = pair.value().dlAmount / realBytes;
        return QVariant(final).toString() + unitPost;
    }
    else if (role == 3)
    {
        auto final = pair.value().ulAmount / realBytes;
        return QVariant(final).toString() + unitPost;
    }
    return QVariant();
}

QHash<int, QByteArray> HourlyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[0] = "date";
    roles[1] = "timespan";
    roles[2] = "download";
    roles[3] = "upload";
    return roles;
}
