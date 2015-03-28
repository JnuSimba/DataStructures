/*************************************************************************
	> File Name: RandomHeight.h
	> Author: Simba
	> Mail: dameng34@163.com 
	> Created Time: Sun 22 Mar 2015 02:20:24 AM PDT
 ************************************************************************/

#ifndef SKIP_LIST_RAND_H_
#define SKIP_LIST_RAND_H_

class RandomHeight
{
    public:
        RandomHeight(int maxLvl, float prob);
        ~RandomHeight() {}
        int newLevel(void);
    private:
        int maxLevel;
        float probability;
};

#endif //SKIP_LIST_RAND

