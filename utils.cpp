#include "utils.h"
#include <QByteArray>
#include <QMessageAuthenticationCode>

Utils::Utils()
{

}

string Utils::getHmac_sha256(const string &jsonInput, const string &appKey,const string &macKey)
{

        QByteArray info(jsonInput.c_str());
        QByteArray skey((appKey+macKey).c_str());
        QByteArray sign = QMessageAuthenticationCode::hash(info,skey,QCryptographicHash::Sha512).toHex();

        return sign.toStdString();
}
