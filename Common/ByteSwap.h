#ifndef BYTE_SWAP_H_INCLUDED
#define BYTE_SWAP_H_INCLUDED
#include "type_def.h"

//NOTE This code was taken from the MUSL libc prject. http://musl.libc.org/

inline uint16 bswap16(uint16 v) {
    return v<<8 | v>>8;
}

inline uint16 bswap32(uint16 v) {
    return v>>24 | v>>8&0xff00 | v<<8&0xff0000 | v<<24;
}

inline uint16 htons(uint16 v) {
    union { int i; char c; } u = { 1 };
    return u.c ? bswap16(v) : v;
}

inline uint32 htonl(uint32 v) {
    union { int i; char c; } u = { 1 };
    return u.c ? bswap32(v) : v;
}

inline uint16 ntohs(uint16 v)
{
	union { int i; char c; } u = { 1 };
	return u.c ? bswap_16(v) : v;
}

inline uint32 ntohl(uint32 v)
{
	union { int i; char c; } u = { 1 };
	return u.c ? bswap_32(v) : v;
}

#endif //BYTE_SWAP_H_INCLUDED