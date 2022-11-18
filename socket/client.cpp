#include"client.h"

void SMTP::Quit() {
    delete smtpSock;
}

void SMTP::Login_and_Keep(string emailServer, string username, string password) {
    _emailServer=emailServer;
    _username=username;
    _password=password;

    smtpSock = new MySocket(emailServer, 25);
	string send, recv;

	recv = smtpSock->RecvData();
	//cout << recv << "\n--------\n" << endl;

	//HELO
	send = "HELO fyc\r\n";
	smtpSock->SendData(send);

	recv = smtpSock->RecvData();
	//cout << recv << "\n--------\n" << endl;

	//login
	send = "AUTH LOGIN\r\n";
	smtpSock->SendData(send);

	recv = smtpSock->RecvData();
	//cout << recv << "\n--------\n" << endl;
	
	send = username;
	send = Base64::Encode(send);
	send += "\r\n";
	smtpSock->SendData(send);

	recv = smtpSock->RecvData();
	//cout << recv << "\n--------\n" << endl;

	send = password;
	send = Base64::Encode(send);
	send += "\r\n";
	smtpSock->SendData(send);
	
	recv = smtpSock->RecvData();
    //cout << recv << "\n--------\n" << endl;

    success_login = ((int)recv.find("235 Authentication successful") != -1);
	//cout << recv << "\n--------\n" << endl;
}

bool SMTP::Login(string emailServer, string username, string password) {
    Login_and_Keep(emailServer, username, password);
    smtpSock->SendData("quit\r\n");
    smtpSock->RecvData();
    Quit();
    return success_login;
}

void SMTP::SendEmail(string fromAddress, string toAddress, string subject, string text) {
    //from to

    string send, recv;

    Login_and_Keep(_emailServer, _username, _password);

    send = "mail from:<";
    send += fromAddress;
    send += ">\r\n";
	smtpSock->SendData(send);

	recv = smtpSock->RecvData();
	//cout << recv << "\n--------\n" << endl;

    send = "rcpt to:<";
    send += toAddress;
    send += ">\r\n";
	smtpSock->SendData(send);

	recv = smtpSock->RecvData();

    //test
    smtpSock->SendData("data\r\n");
    send = "subject:";
    send += subject;
    send += "\r\n";
    smtpSock->SendData(send);
    
    send = "\r\n";
    send += text;
    send += "\r\n.\r\n";
    smtpSock->SendData(send);

	recv = smtpSock->RecvData();

    smtpSock->SendData("quit\r\n");
	recv = smtpSock->RecvData();
    Quit();
    
	//cout << recv << "\n--------\n" << endl;
}