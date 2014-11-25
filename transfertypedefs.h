#ifndef TRANSFERTYPEDEFS_H
#define TRANSFERTYPEDEFS_H

#include <QPair>
#include <QHash>
#include <QLinkedList>
#include <QDateTime>

#include <networkunit.h>

typedef QHash<NetworkTransferType, quint64> TransferTypeData;
typedef QHash<QString, TransferTypeData> InterfaceData;

typedef QPair<QDateTime, InterfaceData> DataSnapshot;
typedef QLinkedList<DataSnapshot> SnapshotList;

#endif // TRANSFERTYPEDEFS_H
