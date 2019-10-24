#include "fmath.h"

bool is_even(x)
{
    if(x>0 &&  !(x >> 1))
        return true;
    else
        return false;
}
