#include "echoaesutility.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "config/echoconfig.h"

#define CBC 1
#define ECB 1

EchoAesUtility::EchoAesUtility()
{

}

uint8_t* EchoAesUtility::aes_pad(uint8_t* data, int len, int block_size, int* p_ret_len) {
    int pad = block_size - (len % block_size);
    uint8_t* ret = (uint8_t*)malloc(len + pad);
    memcpy(ret, data, len);
    memset(ret, pad, pad);
    if(p_ret_len) {
        *p_ret_len = pad + len;
    }
    return ret;
}

uint8_t* EchoAesUtility::aes_decrypt_raw(uint8_t* in, int in_len, uint8_t* key, int* p_ret_len) {
    int block_size = 16;
    int i, formalized_len, pad, ret_len;
    uint8_t* formalized_input = in; // aes_pad(in, in_len, block_size, &formalized_len);
    uint8_t* formalized_output;
    if(in_len % block_size != 0 || in == NULL) {
        return NULL;
    }
    formalized_len = in_len;
    formalized_output = (uint8_t*)malloc(formalized_len);
    memset(formalized_output, 0, formalized_len);
    for(i = 0; i < formalized_len; i += block_size) {
        AES128_ECB_decrypt(formalized_input + i, key, formalized_output + i);
    }
    // pHex2(formalized_output, in_len);
    pad = formalized_output[in_len - 1];
    ret_len = in_len - pad;
    if(pad >= block_size || pad < 0 || ret_len < 0) {
        free(formalized_output);
        return NULL;
    }
    memset(formalized_output + ret_len, 0, pad);
    if(p_ret_len) {
        *p_ret_len = ret_len;
    }
    return formalized_output;
}

//static char* bin2hex(uint8_t* bin, int len) {
//    int i, j;
//    char* hex = (char*)malloc(len + len + 1);
//    const char* map = "0123456789abcdef";
//    for(i=0; i < len; ++i) {
//        j = i + i;
//        hex[j] = map[bin[i] / 16];
//        hex[j+1] = map[bin[i] % 16];
//    }
//    hex[len + len] = '\x0';
//    return hex;
//}

uint8_t* EchoAesUtility::hex2bin(const char* hex, int* p_bin_len)
{
    int i, j, len = strlen(hex) / 2;
    uint8_t* bin = (uint8_t*)malloc(len + 1);
    for(i=0; i < len; ++i) {
        j = i + i;
        bin[i] = (hex[j] - ((hex[j] < 'a') ? '0' : ('a' - 10)) ) * 16 + (hex[j+1] - ((hex[j+1] < 'a') ? '0' : ('a' - 10)));
    }
    bin[len] = '\0';
    if(p_bin_len) {
        *p_bin_len = len;
    }
    return bin;
}

uint8_t* EchoAesUtility::aes_decrypt(const char* hex_in, uint8_t* key, int* p_ret_len)
{
    int in_len;
    uint8_t* bin_in = hex2bin(hex_in, &in_len);

    uint8_t* ret = aes_decrypt_raw(bin_in, in_len, key, p_ret_len);
    if(ret == NULL) {
        free(bin_in);
        return ret;
    }
    return ret;
}

QString EchoAesUtility::aes_decrypt_bellUrl( const QString _aesUrl )
{
    if( _aesUrl.isEmpty() )
        return "";

    char *_urlBuf = _aesUrl.toLatin1().data();
    int _len = _aesUrl.length();
    uint8_t *_aesKey = (uint8_t *)(ECHO_BELLS_KEY);

    uint8_t *aesDecryptBuf =  EchoAesUtility::aes_decrypt( _urlBuf, _aesKey, &_len );
    QString _bellUrl = QString((char *)aesDecryptBuf);

    return _bellUrl;
}

