class Base64 {
    public:
    static string Encode(string s);
    static string Decode(string s);
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