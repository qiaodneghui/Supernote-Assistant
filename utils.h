#ifndef UTILS_H
#define UTILS_H
#include <string>
using namespace std;

class Utils
{
public:
    Utils();

    static string getHmac_sha256(const string &jsonInput,const string &appKey,const string &macKey );
};

#endif // UTILS_H
