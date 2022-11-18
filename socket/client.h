#include <cstdio>
#include <string>
#include <cstdlib>
#include "mySocket.h"
#include "base64.h"
using std::string;

class SMTP {
    private:
    MySocket *smtpSock;
    string _emailServer, _username, _password;
    bool success_login;
    void Login_and_Keep(string emailServer, string username, string password);
    void Quit();

    public:
    SMTP() {success_login = false;}
    bool Login(string emailServer, string username, string password);
    void SendEmail(string toAddress, string fromAddress, string subject, string text);
};

class POP3 {
    public:
    void Login(string emailServer, string username, string password);
    string STAT();
    string RETR(int id);
    void Quit();
};

class EmailClient {
    public:
    void Login(string emailServer, string fromAddress, string username, string password);
    string GetState();
    string GetEmail(int id);
    void SendEmail(string toAddress, string text);
    void Quit();
};
