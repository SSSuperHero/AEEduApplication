#ifndef ECHOAESUTILITY_H
#define ECHOAESUTILITY_H

#include <QObject>
#include "aes.h"

class EchoAesUtility
{
public:
    EchoAesUtility();
    static uint8_t *aes_decrypt(const char *hex_in, uint8_t *key, int *p_ret_len);
    static uint8_t *aes_decrypt_raw(uint8_t *in, int in_len, uint8_t *key, int *p_ret_len);

    static QString aes_decrypt_bellUrl(const QString _aesUrl);
private:
    static uint8_t *hex2bin(const char *hex, int *p_bin_len);
    static uint8_t *aes_pad(uint8_t *data, int len, int block_size, int *p_ret_len);
};

#endif // ECHOAESUTILITY_H
