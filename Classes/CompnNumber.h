//
//  CompnNumber.h
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#ifndef __testShao3__CompnNumber__
#define __testShao3__CompnNumber__

#define COMPNNUMBERMODE_BIG     0
#define COMPNNUMBERMODE_SCORE   1
#define COMPNNUMBERMODE_RECORD  2

#include <iostream>
#include "cocos2d.h"
using namespace std;

USING_NS_CC;

class CompnNumber : public CCNode{
public:
    CompnNumber();
    
    ~CompnNumber();
        
    virtual bool init();
    
    CREATE_FUNC(CompnNumber);
    
    void setCount(int count, int mode, int padding);
    
    void setCount(int count);
private:
    int _padding;
    char *aa[5];
    int _mode;
    int _count;
    float totalWidth;
    float totalHeight;
    
    static char *fontArray[3][10];
    
    CCArray *countsArray;
};

#endif /* defined(__testShao3__CompnNumber__) */
