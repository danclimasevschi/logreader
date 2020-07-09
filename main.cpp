#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml/qqml.h>
#include "sortfilterproxymodel.h"
#include <logsystemcontroller.h>
#include <log.h>



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // Register the proxy model
    qmlRegisterType<SortFilterProxyModel>("com.qt.logs", 1, 0, "SortFilterProxyModel");
    QQmlApplicationEngine engine;

    // Initialize the controller
    LogSystemController controller(&engine);
    // Read the logs
    bool success = controller.readLogs();
    if(success)
        qDebug()<<"Parsed successfully";
    else
        qDebug()<<"An error occurred while parsing...";

    //Fetch the model and add it to the context
    LogModel *logModel = controller.getModel();

    engine.rootContext()->setContextProperty("logsModel", QVariant::fromValue(logModel));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
