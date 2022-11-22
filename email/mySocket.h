#include <Winsock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

//只是对Socket中使用TCP协议的一种封装
class MySocket {
private:
    SOCKET sock;

public:
    MySocket(string host_name, int port);
    ~MySocket();

    void SendData(const string data);
    string RecvData(const string wait);
};