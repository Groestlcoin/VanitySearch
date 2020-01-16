#pragma once
#ifndef GROESTLD_H
#define GROESTLD_H

#include <string>

void groestld(uint8_t *input, int length, uint8_t *digest);
void groestld_checksum(uint8_t *input, int length, uint8_t *checksum);
#if HAS_GROESTL_SSE
void groestldsse_checksum(uint32_t *i0, uint32_t *i1, uint32_t *i2, uint32_t *i3,
	uint8_t *d0, uint8_t *d1, uint8_t *d2, uint8_t *d3);
#endif

#endif

