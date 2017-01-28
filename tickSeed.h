#pragma once
#include<stdint.h>

typedef struct TickSeed_ 
{
        uint32_t tick;
        uint32_t seed;
} TickSeed;

int tsComp(const void* e1, const void* e2);

