#include"client.h"

void SMTP::Quit() {
    smtpSock->SendData("QUIT\r\n");
    smtpSock->RecvData();
    success_login = false;
    delete smtpSock;
}

void SMTP::Login() {
    smtpSock = new MySocket(emailServer, 25);
	string send, recv;

	recv = smtpSock->RecvData();

	send = "HELO fyc\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData();

	send = "AUTH LOGIN\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData();
	
	send = Base64::Encode(username) + "\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData();

	send = Base64::Encode(password) + "\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData();

    // cout << ">>> SMTP_login\n" << recv << ">>> SMTP_login\n" << endl;
    success_login = ((int)recv.find("235 Authentication successful") != -1);
}

bool SMTP::Verify(string _emailServer, string _username, string _password) {
    emailServer = _emailServer;
    username    = _username;
    password    = _password;
    Login();
    Quit();
    return success_login;
}

void SMTP::SendEmail(string fromAddress, string toAddress, string subject, string text) {
    string send, recv;
    Login();

    send = "mail from:<" + fromAddress + ">\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData();

    send = "rcpt to:<" + toAddress + ">\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData();

    send = "data\r\n";
    smtpSock->SendData(send);
    send = "subject:" + subject + "\r\n";
    smtpSock->SendData(send);
    
    send = "\r\n" + text + "\r\n.\r\n";
    smtpSock->SendData(send);
	recv = smtpSock->RecvData();

    // cout << ">>> SMTP_send\n" << recv << ">>> SMTP_send\n" << endl;
    Quit();
}

void POP3::Quit() {
    popSock->SendData("QUIT\r\n");
    popSock->RecvData();
    success_login = false;
    delete popSock;
}

void POP3::Login() {
    popSock = new MySocket(emailServer,110);

    string send,recv;

    recv = popSock->RecvData();

    send = "USER " + username + "\r\n";
    popSock->SendData(send);
    recv = popSock->RecvData();

    send = "PASS " + password + "\r\n";
    popSock->SendData(send);
    recv = popSock->RecvData();

    success_login = ((int)recv.find("+OK") != -1);
    // cout << ">>> SMTP_login\n" << recv << ">>> SMTP_login\n" << endl;
}

bool POP3::Verify(string _emailServer, string _username, string _password) {
    emailServer = _emailServer;
    username    = _username;
    password    = _password;
    Login();
    Quit();
    return success_login;
}

POP3::Status POP3::STAT() {
    Login();
    if (!success_login) throw "POP3_STAT : UNSUCCESSD LOGIN";

    string send, recv;
    
    send = "STAT\r\n";
    popSock->SendData(send);
    recv = popSock->RecvData();

    Quit();

    stringstream ss(recv);
    string s;
    Status status;
    
    ss >> s >> status.count >> status.size;
    if (s != "+OK") throw "POP3 : STAT ERROR";
    return status;
    // cout << ">>> SMTP_STAT\n" << recv << ">>> SMTP_STAT\n" << endl;
}

POP3::Email POP3::RETR(int id) {
    Login();
    if (!success_login) throw "POP3_RETR : UNSUCCESSD LOGIN";

    string send, recv, save;
    regex pattern;
    Email email;

    send = "RETR " + std::to_string(id) + "\r\n";
    popSock->SendData(send);

    save = "";
    do {
        recv = popSock->RecvData();
        save += recv;
        // cout << ">>> SMTP_RETR_RECVING\n" << save << ">>> SMTP_RETR_RECVING\n" << endl;
    } while ((int)recv.find("\r\n.\r\n") == -1);

    save = regex_replace(save, regex("\r\n"), "[[CRLF]]");
    cout << ">>> SMTP_RETR_SAVE\n" << save << ">>> SMTP_RETR_SAVE\n" << endl;

    Quit();

    pattern = regex("\\[\\[CRLF\\]\\]\\[\\[CRLF\\]\\]");
    vector<string> split0(sregex_token_iterator(save.begin(), save.end(), pattern, -1), sregex_token_iterator());
    string header = split0[0];
    string body   = split0[1];
    if (split0.size() != 2) throw "POP3_RETR : SYNTAX ERROR";

    pattern = regex("\\[\\[CRLF\\]\\][\\w-]*:\\s?");
    vector<string> keys  (sregex_token_iterator(header.begin(), header.end(), pattern,  0), sregex_token_iterator());
    vector<string> values(sregex_token_iterator(header.begin(), header.end(), pattern, -1), sregex_token_iterator());

    map<string,string> header_splited;
    for (int i=0;i<(int)keys.size();i++) {
        string k = keys[i];
        k = regex_replace(k, regex("\\[\\[CRLF\\]\\]"), "");
        k = regex_replace(k, regex(":\\s?"), "");
        transform(k.begin(), k.end(), k.begin(), ::toupper);

        string v = values[i+1];
        v = regex_replace(v, regex("\\[\\[CRLF\\]\\]"), "");
        v = regex_replace(v, regex("\t"), "");
        header_splited[k] = v;
    }

    body = regex_replace(body, regex("\\[\\[CRLF\\]\\][.]\\[\\[CRLF\\]\\]*"), "");

    email.date    = header_splited["DATE"];
    email.from    = header_splited["SENDER"];
    email.to      = header_splited["TO"];
    email.subject = header_splited["SUBJECT"];
    email.body    = body;
    return email;
}

bool EmailClient::Login(string _emailServer, string _fromAddress, string _username, string _password) {
    emailServer = _emailServer;
    fromAddress = _fromAddress;
    username    = _username;
    password    = _password;

    bool f1 = smtp.Verify(emailServer, username, password);
    bool f2 = pop3.Verify(emailServer, username, password);

    return f1 && f2;
}

POP3::Status EmailClient::GetState() {
    return pop3.STAT();
}

POP3::Email EmailClient::GetEmail(int id) {
    return pop3.RETR(id);
}

void EmailClient::SendEmail(string toAddress, string subject, string body) {
    smtp.SendEmail(fromAddress, toAddress, subject, body);
}

void EmailClient::Quit() {

}