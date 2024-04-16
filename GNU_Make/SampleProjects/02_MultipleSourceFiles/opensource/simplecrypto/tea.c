// https://github.com/Mrs4s/MiraiGo/blob/master/binary/tea.go

#include <stdlib.h>
#include <string.h>
#if !__APPLE__
	#include <endian.h>
#else
	#include <machine/endian.h>
#endif
#include "simplecrypto.h"
#include "binary.h"

const static uint32_t qqsumtable[0x10] = {
	0x9e3779b9,
	0x3c6ef372,
	0xdaa66d2b,
	0x78dde6e4,
	0x1715609d,
	0xb54cda56,
	0x5384540f,
	0xf1bbcdc8,
	0x8ff34781,
	0x2e2ac13a,
	0xcc623af3,
	0x6a99b4ac,
	0x08d12e65,
	0xa708a81e,
	0x454021d7,
	0xe3779b90,
};

// tea_encrypt_qq use qq sumtable, read from src, write to dst, return write count
//    please allocate no less than tea_encrypt_len(len(src)) bytes for dst
int64_t tea_encrypt_qq(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst) {
	int64_t fill = 10 - (srclen+1)%8;
	int64_t dstlen = fill+srclen+7;
	((uint32_t*)dst)[0] = rand();
	((uint32_t*)dst)[1] = rand();
	((uint32_t*)dst)[2] = rand();
	dst[0] = (fill-3)|0xF8; // 存储pad长度
	memcpy(dst+fill, src, srclen);
	uint64_t iv1 = 0, iv2 = 0, holder;
	for(int64_t i = 0; i < dstlen/8; i++) {
		#ifdef WORDS_BIGENDIAN
			uint64_t block = ((uint64_t*)dst)[i];
		#else
			uint64_t block = _swap_64(((uint64_t*)dst)[i]);
		#endif
		holder = block ^ iv1;
		iv1 = holder;
		uint32_t v1 = holder;
		iv1 >>= 32;
		uint32_t v0 = iv1;
		for (int i = 0; i < 0x10; i++) {
			v0 += (v1 + qqsumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
			v1 += (v0 + qqsumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
		}
		iv1 = ((uint64_t)v0<<32) | (uint64_t)v1;
		iv1 = iv1 ^ iv2;
		iv2 = holder;
		#ifdef WORDS_BIGENDIAN
			((uint64_t*)dst)[i] = iv1;
		#else
			((uint64_t*)dst)[i] = _swap_64(iv1);
		#endif
	}
	return dstlen;
}

// tea_encrypt use custom sumtable, read from src, write to dst, return write count
//    please allocate no less than tea_encrypt_len(len(src)) bytes for dst
int64_t tea_encrypt(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst) {
	int64_t fill = 10 - (srclen+1)%8;
	int64_t dstlen = fill+srclen+7;
	((uint32_t*)dst)[0] = rand();
	((uint32_t*)dst)[1] = rand();
	((uint32_t*)dst)[2] = rand();
	dst[0] = (fill-3)|0xF8; // 存储pad长度
	memcpy(dst+fill, src, srclen);
	uint64_t iv1 = 0, iv2 = 0, holder;
	for(int64_t i = 0; i < dstlen/8; i++) {
		#ifdef WORDS_BIGENDIAN
			uint64_t block = ((uint64_t*)dst)[i];
		#else
			uint64_t block = _swap_64(((uint64_t*)dst)[i]);
		#endif
		holder = block ^ iv1;
		iv1 = holder;
		uint32_t v1 = holder;
		iv1 >>= 32;
		uint32_t v0 = iv1;
		for (int i = 0; i < 0x10; i++) {
			v0 += (v1 + sumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
			v1 += (v0 + sumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
		}
		iv1 = ((uint64_t)v0<<32) | (uint64_t)v1;
		iv1 = iv1 ^ iv2;
		iv2 = holder;
		#ifdef WORDS_BIGENDIAN
			((uint64_t*)dst)[i] = iv1;
		#else
			((uint64_t*)dst)[i] = _swap_64(iv1);
		#endif
	}
	return dstlen;
}

// tea_encrypt_qq_native_endian is the same as tea_encrypt_qq on BE machine
int64_t tea_encrypt_qq_native_endian(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst) {
	int64_t fill = 10 - (srclen+1)%8;
	int64_t dstlen = fill+srclen+7;
	((uint32_t*)dst)[0] = rand();
	((uint32_t*)dst)[1] = rand();
	((uint32_t*)dst)[2] = rand();
	dst[0] = (fill-3)|0xF8; // 存储pad长度
	memcpy(dst+fill, src, srclen);
	uint64_t iv1 = 0, iv2 = 0, holder;
	for(int64_t i = 0; i < dstlen/8; i++) {
		uint64_t block = ((uint64_t*)dst)[i];
		holder = block ^ iv1;
		iv1 = holder;
		uint32_t v1 = holder;
		iv1 >>= 32;
		uint32_t v0 = iv1;
		for (int i = 0; i < 0x10; i++) {
			v0 += (v1 + qqsumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
			v1 += (v0 + qqsumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
		}
		iv1 = ((uint64_t)v0<<32) | (uint64_t)v1;
		iv1 = iv1 ^ iv2;
		iv2 = holder;
		((uint64_t*)dst)[i] = iv1;
	}
	return dstlen;
}

// tea_encrypt_native_endian is the same as tea_encrypt on BE machine
int64_t tea_encrypt_native_endian(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst) {
	int64_t fill = 10 - (srclen+1)%8;
	int64_t dstlen = fill+srclen+7;
	((uint32_t*)dst)[0] = rand();
	((uint32_t*)dst)[1] = rand();
	((uint32_t*)dst)[2] = rand();
	dst[0] = (fill-3)|0xF8; // 存储pad长度
	memcpy(dst+fill, src, srclen);
	uint64_t iv1 = 0, iv2 = 0, holder;
	for(int64_t i = 0; i < dstlen/8; i++) {
		uint64_t block = ((uint64_t*)dst)[i];
		holder = block ^ iv1;
		iv1 = holder;
		uint32_t v1 = holder;
		iv1 >>= 32;
		uint32_t v0 = iv1;
		for (int i = 0; i < 0x10; i++) {
			v0 += (v1 + sumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
			v1 += (v0 + sumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
		}
		iv1 = ((uint64_t)v0<<32) | (uint64_t)v1;
		iv1 = iv1 ^ iv2;
		iv2 = holder;
		((uint64_t*)dst)[i] = iv1;
	}
	return dstlen;
}

// tea_decrypt_qq use qq sumtable, read from src, write to dst, return start pointer of decrypted data
//    length can be calculated by tea_decrypt_len or dst_buf_last-dst
uint8_t* tea_decrypt_qq(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst) {
	if (srclen < 16 || srclen%8 != 0) return 0;
	uint64_t iv1, iv2 = 0, holder = 0;
	for(int64_t i = 0; i < srclen/8; i++) {
		#ifdef WORDS_BIGENDIAN
			iv1 = ((uint64_t*)(src))[i];
		#else
			iv1 = _swap_64(((uint64_t*)(src))[i]);
		#endif
		iv2 ^= iv1;
		uint32_t v1 = iv2;
		iv2 >>= 32;
		uint32_t v0 = iv2;
		for (int i = 0x0f; i >= 0; i--) {
			v1 -= (v0 + qqsumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
			v0 -= (v1 + qqsumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
		}
		iv2 = ((uint64_t)v0<<32) | (uint64_t)v1;
		#ifdef WORDS_BIGENDIAN
			((uint64_t*)dst)[i] = iv2^holder;
		#else
			((uint64_t*)dst)[i] = _swap_64(iv2^holder);
		#endif
		holder = iv1;
	}
	int start = (dst[0]&7)+3;
	return dst+start;
}

// tea_decrypt use custom sumtable, read from src, write to dst, return start pointer of decrypted data
//    length can be calculated by tea_decrypt_len or dst_buf_last-dst
uint8_t* tea_decrypt(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst) {
	if (srclen < 16 || srclen%8 != 0) return 0;
	uint64_t iv1, iv2 = 0, holder = 0;
	for(int64_t i = 0; i < srclen/8; i++) {
		#ifdef WORDS_BIGENDIAN
			iv1 = ((uint64_t*)(src))[i];
		#else
			iv1 = _swap_64(((uint64_t*)(src))[i]);
		#endif
		iv2 ^= iv1;
		uint32_t v1 = iv2;
		iv2 >>= 32;
		uint32_t v0 = iv2;
		for (int i = 0x0f; i >= 0; i--) {
			v1 -= (v0 + sumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
			v0 -= (v1 + sumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
		}
		iv2 = ((uint64_t)v0<<32) | (uint64_t)v1;
		#ifdef WORDS_BIGENDIAN
			((uint64_t*)dst)[i] = iv2^holder;
		#else
			((uint64_t*)dst)[i] = _swap_64(iv2^holder);
		#endif
		holder = iv1;
	}
	int start = (dst[0]&7)+3;
	return dst+start;
}

// tea_decrypt_qq_native_endian is the same as tea_decrypt_qq on BE machine
uint8_t* tea_decrypt_qq_native_endian(const TEA t, const uint8_t* src, int64_t srclen, uint8_t* dst) {
	if (srclen < 16 || srclen%8 != 0) return 0;
	uint64_t iv1, iv2 = 0, holder = 0;
	for(int64_t i = 0; i < srclen/8; i++) {
		iv1 = ((uint64_t*)(src))[i];
		iv2 ^= iv1;
		uint32_t v1 = iv2;
		iv2 >>= 32;
		uint32_t v0 = iv2;
		for (int i = 0x0f; i >= 0; i--) {
			v1 -= (v0 + qqsumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
			v0 -= (v1 + qqsumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
		}
		iv2 = ((uint64_t)v0<<32) | (uint64_t)v1;
		((uint64_t*)dst)[i] = iv2^holder;
		holder = iv1;
	}
	int start = (dst[0]&7)+3;
	return dst+start;
}

// tea_decrypt_native_endian is the same as tea_decrypt on BE machine
uint8_t* tea_decrypt_native_endian(const TEA t, const uint32_t sumtable[0x10], const uint8_t* src, int64_t srclen, uint8_t* dst) {
	if (srclen < 16 || srclen%8 != 0) return 0;
	uint64_t iv1, iv2 = 0, holder = 0;
	for(int64_t i = 0; i < srclen/8; i++) {
		iv1 = ((uint64_t*)(src))[i];
		iv2 ^= iv1;
		uint32_t v1 = iv2;
		iv2 >>= 32;
		uint32_t v0 = iv2;
		for (int i = 0x0f; i >= 0; i--) {
			v1 -= (v0 + sumtable[i]) ^ ((v0 << 4) + t.t[2]) ^ ((v0 >> 5) + t.t[3]);
			v0 -= (v1 + sumtable[i]) ^ ((v1 << 4) + t.t[0]) ^ ((v1 >> 5) + t.t[1]);
		}
		iv2 = ((uint64_t)v0<<32) | (uint64_t)v1;
		((uint64_t*)dst)[i] = iv2^holder;
		holder = iv1;
	}
	int start = (dst[0]&7)+3;
	return dst+start;
}


#ifdef TEST_SIMPLE_CRYPTO
int main(int argc, char **argv) {
	TEA t;
	memcpy(t.t, "32107654BA98FEDC", 4*8);
 
	if (argc != 3) {
		printf("usage: %s -[e|d] 'string'\n", argv[0]);
		return 1;
	}
	switch(argv[1][1]) {
		case 'e':
			uint8_t* data = (uint8_t*)(argv[2]);
			int64_t datalen = strlen(argv[2]);
			int64_t outlen = tea_encrypt_len(datalen);
			uint8_t* out = (uint8_t*)malloc(outlen);
			tea_encrypt_qq(t, data, datalen, out);
			// display result
			for (int i = 0; i < outlen; i++) printf("%02x", ((uint8_t*)(out))[i]);
			putchar('\n');
			free(out);
		break;
		case 'd':
			int64_t datalen = strlen(argv[2])/2;
			// printf("decode input len: %lld\n", td->len);
			uint8_t* data = malloc(datalen);
			int i = datalen;
			while (i--) {
				int x;
				sscanf(argv[2]+i*2, "%02x", &x);
				data[i] = x;
				argv[2][i*2] = 0;
			}
			uint8_t* out = (uint8_t*)malloc(datalen);
			uint8_t* outdat = tea_decrypt_qq(t, data, datalen, out);
			if (outdat) {
				// printf("decode output len: %lld\n", tdd->len);
				for (int i = 0; i < tea_decrypt_len(datalen, out[0]); i++) putchar(outdat[i]);
				putchar('\n');
				free(out);
			} else puts("decode error!");
			free(data);
		break;
		default: break;
	}
	return 0;
}
#endif
