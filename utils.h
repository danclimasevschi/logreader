#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <constants.h>
#include <log.h>

class Utils{

public:
    static QStringList readFromFile(bool *status){
        QStringList logList;
        QFile logFile(LOG_PATH);
        *status = true;
        if (logFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&logFile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                logList.append(line);
            }
            logFile.close();
        }else {
            *status = false;
        }
        return logList;
    }
};
#endif // UTILS_H
