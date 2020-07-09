#include "log.h"
#include "constants.h"

Log::Log(uint id, uint timestamp, const QString& messageType, const QString &message, bool hasRebooted):
    m_id(id),m_timestamp(timestamp), m_messageType(messageType), m_message(message), m_hasRebooted(hasRebooted)
{
}

////////////////////////////////////
//////  LogModel class  ////////////
////////////////////////////////////
LogModel::LogModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void LogModel::addLog(const Log &log)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_logs << log;
    endInsertRows();
}

int LogModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_logs.count();
}

QVariant LogModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_logs.count())
        return QVariant();

    const Log &log = m_logs[index.row()];
    if (role == IdRole)
        return log.getId();
    else if (role == TimestampRole)
        return log.getTimestamp();
    else if (role == MessageTypeRole)
        return log.getMessageType();
    else if (role == MessageRole)
        return log.getMessage();
    return QVariant();
}


QHash<int, QByteArray> LogModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TimestampRole] = "timestamp";
    roles[MessageTypeRole] = "messageType";
    roles[MessageRole] = "message";
    return roles;
}
