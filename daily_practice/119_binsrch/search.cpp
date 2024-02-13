#include "function.h"
#include <cstdio>
#include <cstdlib>

int binarySearchForZero(Function<int, int> * f, int low, int high){
    if (low == high){
        return low;
    }
    if (f->invoke(high)<0){
        return high-1;
    }
    else if (f->invoke(low)>=0){
        return low;
    }

    int mid;
    int mid_val;
    high = high -1;
    while (low <= high){
        mid = (low+high)/2;
        mid_val = f->invoke(mid);

        if (mid_val==0){
            return mid;
        }
        else if(mid_val > 0){
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    if (mid_val>0){
        return high;
    }
    return mid;
}
