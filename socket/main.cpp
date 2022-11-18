#include <stdio.h>
#include <iostream>
#include <time.h> 
#include "mySocket.h"
#include "base64.h"
using namespace std;
int main()
{
    MySocket smtpSock("smtp.163.com",25);
	string send, recv;

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	//HELO
	send = "HELO fyc\r\n";
	smtpSock.SendData(send);

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	//login
	send = "AUTH LOGIN\r\n";
	smtpSock.SendData(send);

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;
	
	send = "fengyecong@163.com";
	send = Base64::Encode(send);
	send += "\r\n";
	smtpSock.SendData(send);

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	send = "secret";
	send = Base64::Encode(send);
	send += "\r\n";
	smtpSock.SendData(send);
	
	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	//from to
	smtpSock.SendData("mail from:<fengyecong@163.com>\r\n");

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	smtpSock.SendData("rcpt to:<houzhe_@whu.edu.cn>\r\n");

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	//text
	smtpSock.SendData("data\r\n");
	smtpSock.SendData("subject:test\r\n");
	smtpSock.SendData("\r\nmeow!\r\n.\r\n");

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;

	//quit
	smtpSock.SendData("quit\r\n");

	recv = smtpSock.RecvData();
	//cout << recv << "\n--------\n" << endl;
}
// SOCKET clientSock;
// string str;
// int iResult;
// if (MySocket::InitClient(&clientSock, "218.197.158.130", 80) == -1)//主机IP地址+端口号
// {
//     printf("FAIL\n");
//     return -1;
// }
// string head = "GET / HTTP/1.1\r\n";
// head.append("Host: m.cnblogs.com\r\n");//请求的域名
// head.append("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");
// head.append("User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.120 Safari/537.36\r\n");
// head.append("Accept-Language: zh-cn,zh;q=0.8,en-us;q=0.5,en;q=0.3\r\n");
// head.append("Accept-Charset: GB2312,utf-8;q=0.7,*;q=0.7");
// head.append("Accept-Encoding: gzip,deflate\r\n");
// head.append("\r\n");//表明请求头结束了
// iResult = MySocket::SendData(clientSock, head);
// if (iResult == -1)
// {
//     printf("ERROR IN SENDING\n");
//     return -1;
// }
// iResult = MySocket::RecvData(clientSock, str);

// if (iResult  == -1)
// {
//     printf("ERROR IN RECEIVING\n");
//     return -1;
// }
// printf("----RECEIVED DATA LENGTH:%d----\n", iResult);
// printf(str.c_str());
// MySocket::CloseMySocket(&clientSock);
// return 0;