#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QAbstractListModel>

class Log
{
public:
    enum MessageType {
        UNDEFINED=0x00,
        INFO=0x01,
        WARNING=0x02,
        ERROR=0x03
    };

    Log(uint id,uint timestamp,const QString& messageType,const QString& message,bool hasRebooted);
    inline uint getId() const {return m_id;}
    inline uint getTimestamp() const {return m_timestamp;}
    inline QString getMessageType() const {return m_messageType;}
    inline QString getMessage() const {return m_message;}
    inline bool getHasRebooted() const {return m_hasRebooted;}

private:
    uint m_id;
    uint m_timestamp;
    QString m_messageType;
    QString m_message;
    bool m_hasRebooted;
};

class LogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LogRoles {
        IdRole = Qt::UserRole + 1,
        TimestampRole,
        MessageTypeRole,
        MessageRole
    };

    LogModel(QObject *parent = 0);

    void addLog(const Log &log);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Log> m_logs;
};


#endif // LOG_H
