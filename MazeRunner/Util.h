#ifndef UTIL_H
#define UTIL_H
#include <cstdlib> 
#include <time.h> 
#include "CONSTANTS.H"
#include <vector>
#include <utility>
#include "cell.h"

typedef struct node node;
int get_random_number(int max);

struct node
{
    int prev_x, prev_y, current_x, current_y;
    node& operator =(const node& a) 
    {
        prev_x = a.prev_x;
        prev_y = a.prev_y;
        current_x = a.current_x;
        current_y = a.current_y;
        return *this;
    }
};



#endif

