/*************************************************************************
	> File Name: RandomHeight.cpp
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sun 22 Mar 2015 02:23:56 AM PDT
 ************************************************************************/
#include <stdlib.h>
#include "RandomHeight.h"

RandomHeight::RandomHeight(int maxLvl, float prob)
{
    maxLevel = maxLvl;
    probability = prob;
}

int RandomHeight::newLevel(void)
{
    int tmpLvl = 1;
    // Develop a random number between 1 and maxLvl(node height))
    while ((rand()/double(RAND_MAX) < probability) && (tmpLvl < maxLevel))
        tmpLvl++;

    return tmpLvl;
}

//End of file

