#include<string>
typedef unsigned char uchar;
using std::string;
class Base64 {
    public:
    enum Base64Option {
        Base64Encoding = 0,
        Base64UrlEncoding = 1,
 
        KeepTrailingEquals = 0,
        OmitTrailingEquals = 2
    };
    static string Encode(const string sourceData, int options = Base64Encoding);
    static string Decode(const string sourceData, int options = Base64Encoding);
};