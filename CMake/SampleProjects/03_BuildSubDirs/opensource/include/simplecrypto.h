#ifndef _SIMPLECRYPTO_H_
#define _SIMPLECRYPTO_H_
#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus__
extern "C" {
#endif

// ---------------MD5 area---------------

// return 128bit(16bytes) digest
uint8_t* md5(const uint8_t *data, size_t data_len, uint8_t digest[16]);

// ---------------MD5 area---------------


// ---------------TEA area---------------

// TEA is the password of the tea algorithm
struct TEA {
    uint32_t t[4];
};
typedef struct TEA TEA;

// tea_encrypt_len is exactly the input buffer length
inline int64_t tea_encrypt_len(int64_t inlen) {
    int64_t fill = 10 - (inlen+1)%8;
    return fill+inlen+7;
}

// tea_decrypt_len's buf0 is the first byte of the buffer passed into decode
//    if you want to allocate decode buffer, just use the encoded data length
inline int64_t tea_decrypt_len(int64_t inlen, uint8_t buf0) {
    int start = (buf0&7)+3;
    return inlen-7-start;
}

// tea_encrypt_qq use qq sumtable, read from src, write to dst, return write count
//    please allocate no less than tea_encrypt_len(len(src)) bytes for dst
int64_t  tea_encrypt_qq(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_encrypt use custom sumtable, read from src, write to dst, return write count
//    please allocate no less than tea_encrypt_len(len(src)) bytes for dst
int64_t  tea_encrypt(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_encrypt_qq_native_endian is the same as tea_encrypt_qq on BE machine
int64_t  tea_encrypt_qq_native_endian(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_encrypt_native_endian is the same as tea_encrypt on BE machine
int64_t  tea_encrypt_native_endian(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_decrypt_qq use qq sumtable, read from src, write to dst, return start pointer of decrypted data
//    length can be calculated by tea_decrypt_len or dst_buf_last-dst
uint8_t* tea_decrypt_qq(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_decrypt use custom sumtable, read from src, write to dst, return start pointer of decrypted data
//    length can be calculated by tea_decrypt_len or dst_buf_last-dst
uint8_t* tea_decrypt(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_decrypt_qq_native_endian is the same as tea_decrypt_qq on BE machine
uint8_t* tea_decrypt_qq_native_endian(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst);

// tea_decrypt_native_endian is the same as tea_decrypt on BE machine
uint8_t* tea_decrypt_native_endian(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst);

// ---------------TEA area---------------

#ifdef __cplusplus__
}
#endif

#endif
