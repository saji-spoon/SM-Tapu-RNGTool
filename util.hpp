#pragma once
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<string>
#include<vector>

char numtoR17(int x);

void uint64toHex(uint64_t src, char* dst);

std::string uint32toHeptStr(uint32_t src, int digit);

uint32_t HepttoNum(char c);

uint32_t r17toUint32(char src[]);

std::string dbFilename(int num);


