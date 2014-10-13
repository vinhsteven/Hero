
#include "gd.h"

void swapArray(int *pArray, int nLength)
{
    if (nLength == 2)
    {
        if (CCRANDOM_0_1() > 0.5f)
        {
            int tmp   = pArray[0];
            pArray[0] = pArray[1];
            pArray[1] = tmp;
        }
        
        return;
    }
    
    int nHalfLength  = nLength >> 1;
    int nHalfLength2 = nLength - nHalfLength;
    float fPercent  = CCRANDOM_0_1();
    int i, j, tmp;
    
    if (fPercent < 0.30f)
    {
        for (i = 0; i < nHalfLength; i++)
        {
            // Gets random index
            j = RANDOM_IN_RANGE(nHalfLength2, nLength - 1);
            
            // Swaps
            tmp       = pArray[i];
            pArray[i] = pArray[j];
            pArray[j] = tmp;
        }
    }
    else if (fPercent > 0.70f)
    {
        for (j = nHalfLength2; j < nLength; j++)
        {
            // Gets random index
            i = RANDOM_0_N_EXCLUSIVE(nHalfLength);
            
            // Swaps
            tmp       = pArray[i];
            pArray[i] = pArray[j];
            pArray[j] = tmp;
        }
    }
    else
    {
        for (int k = 0; k < nHalfLength2; k++)
        {
            // Gets random indices
            i = RANDOM_0_N_EXCLUSIVE(nHalfLength);
            j = RANDOM_IN_RANGE(nHalfLength, nLength - 1);
            
            // Swaps
            tmp       = pArray[i];
            pArray[i] = pArray[j];
            pArray[j] = tmp;
        }
    }
}
