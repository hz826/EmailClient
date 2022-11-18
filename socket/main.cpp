#include <stdio.h>
#include <iostream>
#include <time.h> 
#include "client.h"
using namespace std;
int main()
{
    string s;
    cin >> s;
    string st = Base64::Decode(s);
    cout << st;
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