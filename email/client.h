#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>
#include <regex>
#include "mySocket.h"
#include "base64.h"
using std::string;

class SMTP {
    private:
    MySocket *smtpSock;
    string emailServer, username, password;
    bool success_login;
    void Login();
    void Quit();

    public:
    SMTP() {success_login = false;}
    bool Verify(string _emailServer, string _username, string _password);
    void SendEmail(string toAddress, string fromAddress, string subject, string text);
};

class POP3 {
    private:
    MySocket *popSock;
    bool success_login;
    string emailServer, username, password;

    void Login();
    void Quit();

    public:

    struct Status {
        int count, size;
    };

    struct Email {
        string date, from, to, subject, body;
    };
    
    POP3() {success_login=false;};
    bool Verify(string _emailServer, string _username, string _password);
    Status STAT();
    Email RETR(int id);
};

class EmailClient {
    SMTP smtp;
    POP3 pop3;
    string emailServer, fromAddress, username, password;

    public:
    bool Login(string emailServer, string fromAddress, string username, string password);
    POP3::Status GetState();
    POP3::Email  GetEmail(int id);
    void SendEmail(string toAddress, string subject, string body);
    void Quit();
};
