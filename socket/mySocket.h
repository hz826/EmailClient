#include <Winsock2.h>
#include <Windows.h>
#include <string>
using namespace std;

//只是对Socket中使用TCP协议的一种封装
class MySocket{
public:
    static int InitClient(SOCKET *sock, string ip, int port);
    static int CloseMySocket(SOCKET *Sock);
    static int SendData(SOCKET sock, const string data);
    static int RecvData(SOCKET sock, string &data);
};