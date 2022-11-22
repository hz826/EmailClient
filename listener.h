#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QObject>
#include <QUrl>
#include <QDebug>
#include "email/client.h"

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = 0);
    QObject *LoginPage, *MainPage, *Account, *Password, *Info, *Text, *PageID, *Sendto, *Title, *Body;

public slots:
    void login();
    void exit();
    void getPrevious();
    void getNext();
    void send();

private:
    int pageID, pageCount;
    void refresh();
};

#endif // LISTENER_H
