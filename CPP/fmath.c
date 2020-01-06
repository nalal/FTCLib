#include "fmath.h"

bool is_even(int x)
{
    if(x>0 &&  !(x >> 1))
        return true;
    else
        return false;
}
