#ifndef LOGSYSTEMCONTROLLER_H
#define LOGSYSTEMCONTROLLER_H

#include <QObject>
#include <log.h>

class LogSystemController : public QObject
{
    Q_OBJECT
public:
    explicit LogSystemController(QObject *parent = nullptr);
    virtual ~LogSystemController() override;

    bool readLogs();
    LogModel *getModel() const;
private:
    LogModel *m_model;
};
#endif // LOGSYSTEMCONTROLLER_H
