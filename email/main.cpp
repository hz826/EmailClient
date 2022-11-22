#include <stdio.h>
#include <iostream>
#include <sstream>
#include "client.h"
using namespace std;

int main()
{
    POP3 pop3;
    // pop3.Verify("whu.edu.cn", "houzhe_@whu.edu.cn", "nicai");
    // pop3.Verify("pop.163.com", "houzhe2501@163.com", "nicai");

    // {
    //     auto p = pop3.STAT();
    //     cout << ">>>" << p.count << endl;
    //     cout << ">>>" << p.size << endl;
    // }

    try {
        auto p = pop3.RETR(100);
        cout << ">>>" << p.date << endl;
        cout << ">>>" << p.from << endl;
        cout << ">>>" << p.to << endl;
        cout << ">>>" << p.subject << endl;
        cout << ">>>" << p.body << endl;
    } catch (const char *s) {
        cout << "ERROR" << endl;
        cout << s << endl;
    }

    // string header = "+OK 20085 octets[[CRLF]]Received: from =?UTF-8?B?572R5piT6YKu566x5Yqp5omL?= (unknown [10.110.47.68])[[CRLF]]	by trans1 (Coremail) with SMTP id gMCowACXjoAxOXJjw6kHIg--.10972S2;[[CRLF]]	Mon, 14 Nov 2022 20:48:49 +0800 (CST)[[CRLF]]From: =?UTF-8?B?572R5piT6YKu566x5Yqp5omL?= <mailpublicize@service.netease.com>[[CRLF]]Sender: mailpublicize@service.netease.com[[CRLF]]To: houzhe2501@163.com[[CRLF]]Message-ID: <1181893726.2650447.1668430130122.JavaMail.mailpublicize@service.netease.com>[[CRLF]]Subject: =?UTF-8?B?6YKu5Lu25Yqe5YWs77yM5aaC5q2k6L275p2+?=[[CRLF]] =?UTF-8?B?77yB5qyi6L+O5p2l5Yiw572R5piT6YKu566x77yB?=[[CRLF]]MIME-Version: 1.0[[CRLF]]Content-Type: text/html; charset=UTF-8[[CRLF]]Content-Transfer-Encoding: quoted-printable[[CRLF]]X-CM-TRANSID:gMCowACXjoAxOXJjw6kHIg--.10972S2[[CRLF]]X-Coremail-Antispam: 1Uf129KBjvdXoWruFy3ur1rKFWUCF45GFW3ZFb_yoW3CrgE9r[[CRLF]]	y5XrnIgFy3Aw4Iqa1vyF4IyFsrJ34DK34DA34DW3srAry29w1jkFs3GF45ZF1xtF40qFs5[[CRLF]]	Wr13Ca1FyrnxZjkaLaAFLSUrUb_Jgb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT[[CRLF]]	9fnUUvcSsGvfC2KfnxnUUI43ZEXa7IUOov3UUUUUU==[[CRLF]]X-Originating-IP: [10.110.47.68][[CRLF]]Date: Mon, 14 Nov 2022 20:48:49 +0800 (CST)";

    // regex pattern("\\[\\[CRLF\\]\\][\\w-]*:\\s?");
    // vector<string> keys  (sregex_token_iterator(header.begin(), header.end(), pattern,  0), sregex_token_iterator());
    // vector<string> values(sregex_token_iterator(header.begin(), header.end(), pattern, -1), sregex_token_iterator());

    // map<string,string> header_splited;
    // for (int i=0;i<(int)keys.size();i++) {
    //     string k = keys[i];
    //     k = regex_replace(k, regex("\\[\\[CRLF\\]\\]"), "");
    //     k = regex_replace(k, regex(":\\s?"), "");
    //     transform(k.begin(), k.end(), k.begin(), ::toupper);

    //     string v = values[i+1];
    //     v = regex_replace(v, regex("\\[\\[CRLF\\]\\]"), "");
    //     v = regex_replace(v, regex("\t"), "");
    //     header_splited[k] = v;
    // }
    
    // for(auto& p : header_splited) cout<<">>>"<<p.first<<"<<<>>>"<<p.second<<"\n";
}