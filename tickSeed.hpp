#pragma once
#include<stdint.h>

struct TickSeed
{
        uint32_t tick;
        uint32_t seed;
};

int tsComp(const void* e1, const void* e2);

