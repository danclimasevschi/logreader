#include "logsystemcontroller.h"
#include <QList>
#include <log.h>
#include <utils.h>

LogSystemController::LogSystemController(QObject *parent) : QObject(parent)
{
    m_model = new LogModel(parent);
}

LogSystemController::~LogSystemController(){
    m_model->deleteLater();
}

bool LogSystemController::readLogs(){
    bool success = false;
    Q_ASSERT(m_model);

    QStringList logList = Utils::readFromFile(&success);
    if(!success){
        qDebug()<<"Failed to read from file!";
        return false;
    }

    uint previousTimeStamp = 0;
    uint id = 0;
    for ( const QString& line : logList  )
    {
        if(line == QString::fromLatin1(".")){
            // This means a reboot
            Log newLog(id,previousTimeStamp,"Reboot","Reboot",true);
            m_model->addLog(newLog);
        }else {
            QStringList elements = line.split(',');
            if(elements.count() == LOG_FIELDS){
                bool status = false;

                //Fetch the timestamp
                const uint timeStamp = elements[0].toUInt(&status);
                previousTimeStamp = timeStamp+1;

                //If the cast failed move to the next log
                if(!status)
                    continue;

                //Fetch the message type
                const QString messType = elements[1];

                //Fetch the message string
                const QString message = elements[2];
                Log newLog(id,timeStamp,messType,message,false);
                m_model->addLog(newLog);
            }else {
                qDebug()<<"Oops! Invalid line found:"<<line;
            }
        }
        ++id;
    }

    return success;
}

LogModel *LogSystemController::getModel() const
{
    return m_model;
}
