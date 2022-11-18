#include "mySocket.h"

//只是对Socket中使用TCP协议的封装

int MySocket::InitClient(SOCKET *sock, string ip, int port)
{
    WSADATA wsaData;//初始化wsaData
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return -1;
    }

    //创建套接字
    if ((*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        WSACleanup();
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(*sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        return -1;
    }

    return 0;
}

int MySocket::CloseMySocket(SOCKET *sock)
{
    if (closesocket(*sock) == SOCKET_ERROR)
    {
        WSACleanup();
        return -1;
    }
    return 0 ;
}

int MySocket::RecvData(SOCKET sock, string &data)
{
    int bufLen = 255;
    char buf[256];
    int recvLen= 0;
    int iResult;
    buf[bufLen] = '\0';
    while (true)
    {
        iResult = recv(sock, buf, bufLen, 0);
        if (iResult < 0)
        {
            data = "";
            return -1;
        }

        recvLen += iResult;

        if (iResult == 0)
        {
            return recvLen;
        }

        if (iResult == bufLen)
        {
            data += buf;
            ZeroMemory(buf, bufLen);
            continue;
        }
        if (iResult > 0 && iResult < bufLen)
        {
            data += buf;
            return recvLen;
        }
    }
}

int MySocket::SendData(SOCKET sock, const string data)
{
    int iResult = send(sock, data.c_str(), data.length(), 0);
    if (iResult == SOCKET_ERROR) {
        MySocket::CloseMySocket(&sock);
        WSACleanup();
        return -1;
    }

    return 0;
}