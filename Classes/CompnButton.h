//
//  CompnButton.h
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#ifndef __testShao3__CompnButton__
#define __testShao3__CompnButton__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CompnButton : public CCNode{
public:
    CompnButton();
    
    virtual ~CompnButton();
    
    virtual bool init();
    
    static CompnButton* create();
    
    void setContent(const int bid, CCNode* content);
    
    CCNode* getContent();
    
    void setBid(const int bid);
    
    int getBid();
    
    void setHitRect(const CCRect &rect);
    
    void resizeHitRect(float flactor);
    
    CCRect getHitRect();
    
    void touch();
    
    void click();
private:
    CCNode* _content;
    int _bid;
    CCRect _rcHit;
};

#endif /* defined(__testShao3__CompnButton__) */
