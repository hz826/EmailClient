#include "listener.h"

Listener::Listener(QObject *parent) : QObject(parent) {
    QMetaObject::connectSlotsByName(this);
    pageID = 1;
}

void Listener::login() {
    cache.clear();
    QString account    = Account ->property("text").toString();
    QString password   = Password->property("text").toString();
    QString smtpserver = SMTPServ->property("text").toString();
    QString pop3server = POP3Serv->property("text").toString();

    bool success = false;
    try {
        success = client.Login(smtpserver.toStdString(), pop3server.toStdString(), account.toStdString(), password.toStdString());

        auto state = client.GetState();
        pageCount = state.count;
        pageID = 1;
    } catch (const char* s) {
        qDebug() << "!!! " << s;
    }

    qDebug() << "login with" << account << password << success;

    if (success) {
        Info->setProperty("text", "欢迎" + account);
        Text->setProperty("text", "加载中...");
        PageID->setProperty("text", "第1/1篇");

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

void Listener::update_username() {
    QString account  = Account ->property("text").toString();

    if (account.endsWith("@163.com")) {
        SMTPServ->setProperty("text", "smtp.163.com");
        POP3Serv->setProperty("text", "pop.163.com");
    }

    if (account.endsWith("@whu.edu.cn")) {
        SMTPServ->setProperty("text", "smtp.whu.edu.cn");
        POP3Serv->setProperty("text", "pop.whu.edu.cn");
    }
}

void Listener::getemail(int id) {
    if (id < 1 || id > pageCount) return ;
    if (cache.find(id) != cache.end()) return ;

    auto email = client.GetEmail(pageCount + 1 - pageID);
    cache[id] = email;
}

void Listener::refresh() {
    QString account  = Account ->property("text").toString();
    Text->setProperty("text", "加载中...");

    QString text;

    try {
        getemail(pageID);
        auto email = cache[pageID];

        text  = QString("DATE   : %1\nFROM   : %2\nTO     : %3\nSUBJECT: %4\n\n%5\n")
            .arg(QString::fromStdString(email.date))
            .arg(QString::fromStdString(email.from))
            .arg(QString::fromStdString(email.to))
            .arg(QString::fromStdString(email.subject))
            .arg(QString::fromStdString(email.body));
    } catch (const char* s) {
        qDebug() << "!!! " << s;
        text = "获取邮件内容发生错误";
    }

    Info->setProperty("text", QString("欢迎%1，您有%2封邮件").arg(account).arg(pageCount));
    Text->setProperty("text", text);
    PageID->setProperty("text", QString("第%1/%2篇").arg(pageID).arg(pageCount));
    Vbar->setProperty("position", 0);

//    try {
//        for (int i=1;i<=5;i++) {
//            getemail(pageID+i);
//            getemail(pageID-i);
//        }
//    } catch (const char* s) {
//        qDebug() << "!!! " << s;
//    }
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

    try {
        client.SendEmail(sendto.toStdString(), title.toStdString(), body.toStdString());
    } catch (const char* s) {
        qDebug() << "!!! " << s;
    }
}
