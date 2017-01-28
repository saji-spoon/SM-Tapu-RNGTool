#pragma once
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

char numtoR17(int x);

void uint64toHex(uint64_t src, char* dst);

void uint32toR17Str(uint32_t src, char dst[], int digit);

uint32_t r17toNum(char c);

uint32_t r17toUint32(char src[]);

