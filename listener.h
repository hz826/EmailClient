#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QObject>
#include <QUrl>
#include <QDebug>

class Listener : public QObject
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = 0);
    void init_link(QObject *pLoader);

public slots:
    void login();
    void exit();

private:
    QObject *pLoader;

    void BeforeModify();
    void AfterModify();
};

#endif // LISTENER_H
