#ifndef _SCRYPTO_BINARY_H
#define _SCRYPTO_BINARY_H

// https://github.com/TheSnowfield

#include <stdint.h>

inline uint32_t _swap_16(uint16_t value) {
	#ifdef _MSC_VER
		return _byteswap_ushort(value);
	#elif __GNUC__
		return __builtin_bswap16(value);
	#else
		return ((value & 0xff00) >> 8) |
				 ((value & 0x00ff) << 8);
	#endif
}

inline uint32_t _swap_32(uint32_t value) {
	#ifdef _MSC_VER
		return _byteswap_ulong(value);
	#elif __GNUC__
		return __builtin_bswap32(value);
	#else
		return ((value & 0xff000000) >> 24) |
				 ((value & 0x00ff0000) >> 8)  |
				 ((value & 0x0000ff00) << 8)  |
				 ((value & 0x000000ff) << 24);
	#endif
}

inline uint64_t _swap_64(uint64_t value) {
	#ifdef _MSC_VER
		return _byteswap_uint64(value);
	#elif __GNUC__
		return __builtin_bswap64(value);
	#else
		return ((value & 0xff00000000000000) >> 56) |
			 ((value & 0x00ff000000000000) >> 40) |
			 ((value & 0x0000ff0000000000) >> 24) |
			 ((value & 0x000000ff00000000) >> 8)  |
			 ((value & 0x00000000ff000000) << 8)  |
			 ((value & 0x0000000000ff0000) << 24) |
			 ((value & 0x000000000000ff00) << 40) |
			 ((value & 0x00000000000000ff) << 56);
	#endif
}

#endif /* _SCRYPTO_BINARY_H */
