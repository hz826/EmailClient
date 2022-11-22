#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    pageID = 1;
}

void Listener::login() {
    QString account  = Account ->property("text").toString();
    QString password = Password->property("text").toString();
    QString server   = "whu.edu.cn";

    bool success = false;
    try {
        success = client.Login(server.toStdString(), account.toStdString(), account.toStdString(), password.toStdString());
    } catch (const char* s) {
        qDebug() << "!!! " << s;
    }

    qDebug() << "login with" << account << password << success;

    if (success) {
        Info->setProperty("text", "欢迎" + account);
        Text->setProperty("text", "");
        PageID->setProperty("text", "第0/0篇");

        LoginPage->setProperty("visible", "false");
        MainPage ->setProperty("visible", "true");
        qDebug() << "login succeed";

        refresh();
    } else {
        qDebug() << "login failed";
    }
}

void Listener::exit() {
    try {
        client.Quit();
    } catch (const char* s) {
        qDebug() << "!!! " << s;
    }

    qDebug() << "exit";
    LoginPage->setProperty("visible", "true");
    MainPage ->setProperty("visible", "false");
}

void Listener::refresh() {
    QString account  = Account ->property("text").toString();

    pageCount = 5;

    Info->setProperty("text", QString("欢迎%1，您有%2封邮件").arg(account).arg(pageCount));
    Text->setProperty("text", "");
    PageID->setProperty("text", QString("第%1/%2篇").arg(pageID).arg(pageCount));
}

void Listener::getPrevious() {
    if (pageID > 1) {
        pageID--;
        refresh();
    }
}

void Listener::getNext() {
    if (pageID < pageCount) {
        pageID++;
        refresh();
    }
}

void Listener::send() {
    QString sendto = Sendto->property("text").toString();
    QString title  = Title ->property("text").toString();
    QString body   = Body  ->property("text").toString();
    qDebug() << "send" << sendto << title << body;
}
