//
//  Pipe.h
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#ifndef __testShao3__Pipe__
#define __testShao3__Pipe__

#include <iostream>
#include "cocos2d.h"
#include "AniNode.h"

USING_NS_CC;

class Pipe : public AniNode{

public:
    Pipe();
    virtual ~Pipe();
    virtual bool init();
    
    CREATE_FUNC(Pipe);
    
    float getCenterH();
    
    float getPipePadding();
    
    void setPassed(const bool state);
    
    bool getPassed();
private:
    CCSprite *pipeUp;
    CCSprite *pipeDown;
    
    float pipePadding;
    float centerH;
    
    bool isPassed;

};

#endif /* defined(__testShao3__Pipe__) */
