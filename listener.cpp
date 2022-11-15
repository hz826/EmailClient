#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
}

void Listener::init_link(QObject *pLoader) {
    this->pLoader = pLoader;
    //this->pRenderer = pR;
    //this->pTextView = pT;
}

void Listener::login() {
    qDebug() << "login";
    pLoader->setProperty("source", QUrl(QStringLiteral("qrc:/MainPage.qml")));
}

void Listener::exit() {
    qDebug() << "exit";
    pLoader->setProperty("source", QUrl(QStringLiteral("qrc:/LoginPage.qml")));
}
