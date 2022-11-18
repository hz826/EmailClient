#include <QtCore/qglobal.h>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QDebug>

#include "listener.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<Listener>("myEmailClient", 1, 0, "Listener");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Listener *pListener  = engine.rootObjects().first()->findChild<Listener *>("listener");
    pListener->LoginPage = engine.rootObjects().first()->findChild<QObject *>("loginpage");
    pListener->MainPage  = engine.rootObjects().first()->findChild<QObject *>("mainpage");

    qDebug() << pListener << pListener->LoginPage << pListener->MainPage;

    pListener->Account  = engine.rootObjects().first()->findChild<QObject *>("login_account");
    pListener->Password = engine.rootObjects().first()->findChild<QObject *>("login_password");

    pListener->Info     = engine.rootObjects().first()->findChild<QObject *>("read_info");
    pListener->Text     = engine.rootObjects().first()->findChild<QObject *>("read_text");
    pListener->PageID   = engine.rootObjects().first()->findChild<QObject *>("read_pageid");

    pListener->Sendto   = engine.rootObjects().first()->findChild<QObject *>("write_sendto");
    pListener->Title    = engine.rootObjects().first()->findChild<QObject *>("write_title");
    pListener->Body     = engine.rootObjects().first()->findChild<QObject *>("write_body");

    return app.exec();
}
