
/*
 * This file is part of the VanitySearch distribution (https://github.com/Groestlcoin/VanitySearch).
 * Copyright (c) 2020 Hash Engineering Solutions
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
extern "C" {
	#include "sph_groestl.h"
}
#include "groestld.h"

//#define BSWAP


#ifdef BSWAP
#define WRITEBE32(ptr,x) *((uint32_t *)(ptr)) = _byteswap_ulong(x)
#define WRITEBE64(ptr,x) *((uint64_t *)(ptr)) = _byteswap_uint64(x)
#define READBE32(ptr) (uint32_t)_byteswap_ulong(*(uint32_t *)(ptr))
#else
#define WRITEBE32(ptr,x) *((uint32_t *)(ptr)) = x
#define WRITEBE64(ptr,x) *((uint64_t *)(ptr)) = x
#define READBE32(ptr) *(uint32_t *)(ptr)
#endif

static sph_groestl512_context ctx;

void groestld(uint8_t *input, int length, uint8_t *digest)
{
	unsigned char hash1[64];
	unsigned char hash2[64];

	sph_groestl512_init(&ctx);
	sph_groestl512(&ctx, input, length);
	sph_groestl512_close(&ctx, hash1);

	sph_groestl512_init(&ctx);
	sph_groestl512(&ctx, hash1, sizeof(hash1));
	sph_groestl512_close(&ctx, hash2);

	memcpy_s(digest, 32, hash2, 32);

}

static const unsigned char pad[64] = { 0x80 };


void groestld_checksum(uint8_t *input, int length, uint8_t *checksum) {

	uint32_t s[8];
	uint8_t b[64];
	memcpy(b, input, length);
	memcpy(b + length, pad, 56 - length);
	WRITEBE64(b + 56, length << 3);
	//_sha256::Transform2(s, b);
	groestld(b, length, (uint8_t*)s);
	WRITEBE32(checksum, s[0]);

}
#if HAS_GROESTL_SSE
/* this is not yet an SSE function */
void groestldsse_checksum(uint32_t *i0, uint32_t *i1, uint32_t *i2, uint32_t *i3,
	uint8_t *d0, uint8_t *d1, uint8_t *d2, uint8_t *d3) {
	// this function does not work, there is some BE/LE issue probably
	groestld_checksum((uint8_t*)i0, 21, d0);
	groestld_checksum((uint8_t*)i1, 21, d1);
	groestld_checksum((uint8_t*)i2, 21, d2);
	groestld_checksum((uint8_t*)i3, 21, d3);
}
#endif