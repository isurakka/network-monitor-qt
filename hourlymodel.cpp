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
    // HACK: Row is inverted because normal table sorting doesn't work
    int row = rowCount() - 1 - index.row();
    int col = index.column();

    auto ifName = settings->getCurrentInterface().getName();

    //std::sort(storage->savedData.value(ifName).begin(), storage->savedData.value(ifName).end(), qLess<int>());
    auto pair = storage->savedData.value(ifName).begin() + row;
    auto localDateTime = pair.key().toLocalTime();
    auto date = localDateTime.date();
    auto time = localDateTime.time();
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
        auto final = QString::number(pair.value().dlAmount / realBytes, 'f', 2);
        return final + unitPost;
    }
    else if (role == 3)
    {
        auto final = QString::number(pair.value().ulAmount / realBytes, 'f', 2);
        return final + unitPost;
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

void HourlyModel::sort(int column, Qt::SortOrder order)
{
    qDebug() << "Sorting by column " << column << " order " << order;
    //QAbstractTableModel::sort(column, order);
}
