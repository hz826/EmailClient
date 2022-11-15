#include <QtCore/qglobal.h>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QDebug>

#include "listener.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Listener>("Tooska", 1, 0, "Listener");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    /*********************************/

    Listener * pListener = engine.rootObjects().first()->findChild<Listener *>("m_listener");
    QObject * pLoader = engine.rootObjects().first()->findChild<QObject *>("m_loader");

    pListener->init_link(pLoader);

    qDebug() << pListener;
    qDebug() << pLoader;


    /*********************************/

    return app.exec();
}
