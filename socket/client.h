#include <cstdio>
#include <string>
#include <cstdlib>
#include "mySocket.h"
typedef unsigned char uchar;
using std::string;
class Base64 {
    public:
    enum Base64Option {
        Base64Encoding = 0,
        Base64UrlEncoding = 1,
 
        KeepTrailingEquals = 0,
        OmitTrailingEquals = 2
    };
    static string Encode(const string sourceData, int options = Base64Encoding);
    static string Decode(const string sourceData, int options = Base64Encoding);
};

class SMTP {
    public:
    void Login(string emailServer, string fromAddress, string username, string password);
    void SendEmail(string toAddress, string text);
    void Quit();
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