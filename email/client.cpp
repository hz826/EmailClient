#include"client.h"

void SMTP::Quit() {
    smtpSock->SendData("QUIT\r\n");
    smtpSock->RecvData("\r\n");
    delete smtpSock;
}

void SMTP::Login() {
    smtpSock = new MySocket(emailServer, 25);
	string send, recv;

	recv = smtpSock->RecvData("\r\n");

	send = "HELO fyc\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData("\r\n");

	send = "AUTH LOGIN\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData("\r\n");
	
	send = Base64::Encode(username) + "\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData("\r\n");

	send = Base64::Encode(password) + "\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData("\r\n");

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
	recv = smtpSock->RecvData("\r\n");

    send = "rcpt to:<" + toAddress + ">\r\n";
	smtpSock->SendData(send);
	recv = smtpSock->RecvData("\r\n");

    send = "data\r\n";
    smtpSock->SendData(send);
    send = "subject:" + subject + "\r\n";
    smtpSock->SendData(send);
    
    send = "\r\n" + text + "\r\n.\r\n";
    smtpSock->SendData(send);
	recv = smtpSock->RecvData("\r\n");

    // cout << ">>> SMTP_send\n" << recv << ">>> SMTP_send\n" << endl;
    Quit();
}

void POP3::Quit() {
    popSock->SendData("QUIT\r\n");
    popSock->RecvData("\r\n");
    delete popSock;
}

void POP3::Login() {
    popSock = new MySocket(emailServer,110);

    string send,recv;

    recv = popSock->RecvData("\r\n");

    send = "USER " + username + "\r\n";
    popSock->SendData(send);
    recv = popSock->RecvData("\r\n");

    send = "PASS " + password + "\r\n";
    popSock->SendData(send);
    recv = popSock->RecvData("\r\n");

    // cout << ">>> POP3_login\n" << recv << ">>> POP3_login\n" << endl;
    success_login = ((int)recv.find("+OK") != -1);
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
    if (!success_login) throw "POP3_STAT : LOGIN FAILED";

    string send, recv;
    
    send = "STAT\r\n";
    popSock->SendData(send);
    recv = popSock->RecvData("\r\n");

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
    if (!success_login) throw "POP3_RETR : LOGIN FAILED";

    string send, recv;
    Email email;

    send = "RETR " + std::to_string(id) + "\r\n";
    popSock->SendData(send);

    recv = popSock->RecvData("\r\n.\r\n");

    if (recv.substr(0,3) != "+OK") throw "POP3_RETR : REQUEST FAILED";

    recv = regex_replace(recv, regex("\r\n"), "[[CRLF]]");
//    cout << ">>> SMTP_RETR_recv\n" << recv << ">>> SMTP_RETR_recv\n" << endl;

    Quit();

    string pattern0 = "[[CRLF]][[CRLF]]";
    int index = recv.find(pattern0);
    string header = recv.substr(0, index);
    string body   = recv.substr(index+pattern0.length());

    regex pattern1("\\[\\[CRLF\\]\\][\\w-]*:\\s?");
    vector<string> keys  (sregex_token_iterator(header.begin(), header.end(), pattern1,  0), sregex_token_iterator());
    vector<string> values(sregex_token_iterator(header.begin(), header.end(), pattern1, -1), sregex_token_iterator());

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
    body = regex_replace(body, regex("\\[\\[CRLF\\]\\]"), "\n");

    email.date    = header_splited["DATE"];
    email.from    = header_splited["FROM"];
    email.to      = header_splited["TO"];
    email.subject = header_splited["SUBJECT"];
    email.body    = body;

    // email.body = "";
    // for (auto p : header_splited) {
    //     email.body += p.first + "->" + p.second + "\n";
    // }

    return email;
}

bool EmailClient::Login(string _smtpServer, string _pop3Server, string _username, string _password) {
    smtpServer  = _smtpServer;
    pop3Server  = _pop3Server;
    fromAddress = _username;
    username    = _username;
    password    = _password;

    bool f1 = smtp.Verify(smtpServer, username, password);
    bool f2 = pop3.Verify(pop3Server, username, password);

    // cout << f1 << f2 << endl;
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
