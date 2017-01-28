#include"tickSeed.h"

int tsComp(const void* e1, const void* e2)
{
        TickSeed* ts1 = (TickSeed*)e1;
        TickSeed* ts2 = (TickSeed*)e2;

        return ts1->tick - ts2->tick;
}


