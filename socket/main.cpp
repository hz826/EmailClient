#include <stdio.h>
#include <iostream>
#include <time.h> 
#include "client.h"
using namespace std;

int main()
{
    POP3 pop3;
    // pop3.Login("pop.163.com", "houzhe2501@163.com", "nicai");
    pop3.Login("whu.edu.cn", "houzhe_@whu.edu.cn", "nicai");

    // auto p = pop3.STAT();
    // cout << p.first << "\n---\n" << p.second << endl;

    auto p = pop3.RETR(90);
    cout << p.first << "\n---\n" << p.second << endl;
}