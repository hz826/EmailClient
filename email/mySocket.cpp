#include "mySocket.h"

//只是对Socket中使用TCP协议的封装

MySocket::MySocket(string host_name, int port)
{
    WSADATA wsaData;//初始化wsaData
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw "ERROR IN WSAStartup";
    }

    //创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        WSACleanup();
        throw "ERROR IN CREATING SOCKET";
    }
    struct hostent *host = gethostbyname(host_name.c_str());
    if (!host)
	{
		throw "ERROR IN GETTING IP ADDRESS";
	}

    //cout << inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)host->h_addr_list[0]));

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        throw "ERROR IN CONNECTING SOCKET";
    }
}

MySocket::~MySocket()
{
    if (closesocket(sock) == SOCKET_ERROR)
    {
        WSACleanup();
        //throw "ERROR IN CLOSING SOCKET";
    }
}

string MySocket::RecvData(const string wait)
{
    const int bufLen = 255;
    char buf[bufLen+1];
    int recvLen = 0;
    int iResult;
    buf[bufLen] = '\0';
    string data;

    while ((int)data.find(wait) == -1)
    {
        iResult = recv(sock, buf, bufLen, 0);
        if (iResult < 0)
        {
            throw "ERROR IN RECVING DATA";
        }

        recvLen += iResult;

        if (iResult == 0)
        {
            return data;
        }

        if (iResult == bufLen)
        {
            data += buf;
            memset(buf, 0, sizeof(buf));
            continue;
        }

        if (iResult > 0 && iResult < bufLen)
        {
            data += buf;
            memset(buf, 0, sizeof(buf));
            continue;
        }
    }

    return data;
}

void MySocket::SendData(const string data)
{
    int iResult = send(sock, data.c_str(), data.length(), 0);
    if (iResult == SOCKET_ERROR) {
        this -> ~MySocket();
        WSACleanup();
        throw "ERROR IN SENDING DATA";
    }
}