#pragma once
#ifndef GROESTLD_H
#define GROESTLD_H

#include <string>

void groestld(uint8_t *input, int length, uint8_t *digest);
void groestld_checksum(uint8_t *input, int length, uint8_t *checksum);

#endif

