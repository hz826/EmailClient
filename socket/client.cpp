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

void POP3::Quit(){
    delete popSock;
}

void POP3::Login_and_Keep(string emailServer,string username,string password){
    _emailServer=emailServer;
    _username=username;
    _password=password;

    popSock=new MySocket(emailServer,110);

    string send,recv;

    recv=popSock->RecvData();
    send="user ";
    send+=username;
    send+="\r\n";
    popSock->SendData(send);
    recv=popSock->RecvData();


    send="pass ";
    send+=password;
    send+="\r\n";
    // cout<<send<<endl<<"\n---\n";
    popSock->SendData(send);
    recv=popSock->RecvData();

    // cout<<recv<<endl;

    success_login=((int)recv.find("+OK")!=-1);
}

void POP3::Login(string emailServer,string username,string password){
    Login_and_Keep(emailServer,username,password);
    Quit();
}

pair<long long int, long long int>  POP3::STAT(){
    Login_and_Keep(_emailServer,_username,_password);

    string send,recv,save;
    
    send="stat";
    send+="\r\n";
    popSock->SendData(send);
    recv=popSock->RecvData();
    save=recv;

    send="quit\r\n";
    popSock->SendData(send);
    recv=popSock->RecvData();
    Quit();

    // int st=save.find("+OK");

    pair<long long int, long long int> result;
    sscanf(save.c_str(), "+OK %I64d %I64d", &result.first, &result.second);
    return result;
    // return save.substr(st+3,-1);
}

pair<string,string> POP3::RETR(int id){
    Login_and_Keep(_emailServer,_username,_password);

    string send,recv,save;

    send="retr ";
    send+=std::to_string(id);
    send+="\r\n";

    popSock->SendData(send);
    // recv=popSock->RecvData();
    // save=recv;

    save = "";
    while (1) {
        recv=popSock->RecvData();
        // cout << "---\n" << recv << "\n---\n";
        save += recv;

        if ((int)recv.find("\r\n.\r\n") != -1) break;
    }
    cout << save << endl;

    popSock->SendData("quit\r\n");
    recv=popSock->RecvData();
    Quit();

    int titleSt,titleEd,textSt,textEd;
    string title,text;

    auto lower_string = [](string str) -> string {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    };

    titleSt=lower_string(save).find("\r\nsubject:")+10;//mail title
    while (save[titleSt] == ' ') ++titleSt;

    // cout << ">>>>>>>>>>>" << save[titleSt] << endl;

    // cout << save.substr(titleSt) << endl;

    titleEd=save.find("\r\n", titleSt);
    title=save.substr(titleSt,titleEd-titleSt);

    textSt=save.find("\r\n\r\n")+4;//mail text
    textEd=save.find("\r\n.", textSt);
    text=Base64::Decode(save.substr(textSt, textEd-textSt)); // 163.com
    // text=save.substr(textSt, textEd-textSt); // email.whu.edu.cn

    return make_pair(title,text);
}