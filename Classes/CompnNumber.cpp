//
//  CompnNumber.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#include "CompnNumber.h"
#include "Utils.h"

char *CompnNumber::fontArray[3][10]={
    {
        "font_big_0",
        "font_big_1",
        "font_big_2",
        "font_big_3",
        "font_big_4",
        "font_big_5",
        "font_big_6",
        "font_big_7",
        "font_big_8",
        "font_big_9"
    },
    {
        "number_score_0",
        "number_score_1",
        "number_score_2",
        "number_score_3",
        "number_score_4",
        "number_score_5",
        "number_score_6",
        "number_score_7",
        "number_score_8",
        "number_score_9"
    },
    {
        "number_context_0",
        "number_context_1",
        "number_context_2",
        "number_context_3",
        "number_context_4",
        "number_context_5",
        "number_context_6",
        "number_context_7",
        "number_context_8",
        "number_context_9"
    }
};


CompnNumber::CompnNumber():_padding(0),_mode(COMPNNUMBERMODE_BIG),_count(-1){
    

}

CompnNumber::~CompnNumber(){
    if (countsArray != NULL) {
        countsArray->release();
        countsArray = NULL;
    }
}

bool CompnNumber::init(){
    if (!CCNode::init()) {
        return false;
    }
    
    countsArray = CCArray::create();
    countsArray->retain();
    
    return true;
}

void CompnNumber::setCount(int count, int mode, int padding){
    _mode = mode;
    
    if (_count != count) {
        _count = count;
        _padding = padding;
        
        //clear
        for (int i=0; i < countsArray->count(); i++)
        {
            this->removeChild((CCSprite*)countsArray->objectAtIndex(i));
        }
        countsArray->removeAllObjects();
        totalWidth = 0;
        
        //add
        char buffer[5];
        sprintf(buffer, "%d", _count);
        for (int i=0; i < strlen(buffer); i++)
        {
            //
            //string str = "font_" ;
            //str = str + buffer[i];
            //或者
            //stringstream ss;
            //ss << "font_" << buffer[i];
            //string str = ss.str();
            string str = fontArray[_mode][buffer[i] - '0'];
            
            CCSprite *sprite = Utils::createSprite(str);
            countsArray->addObject(sprite);
            
            totalWidth += sprite->getContentSize().width + _padding;
        }
        
        totalHeight = ((CCSprite*)countsArray->objectAtIndex(0))->getContentSize().height;
        totalWidth -= _padding;
        this->setContentSize(CCSizeMake(totalWidth, totalHeight));
        
        //setPosition
        for (int i=0; i < countsArray->count(); i++)
        {
            CCSprite *child = (CCSprite*)countsArray->objectAtIndex(i);
            this->addChild(child);
            child->setAnchorPoint(ccp(0, 0));
            if (i == 0)
            {
                child->setPosition(ccp(0, 0));
            }
            else
            {
                CCSprite *last = (CCSprite*)countsArray->objectAtIndex(i-1);
                child->setPosition(ccpAdd(last->getPosition(), ccp(last->getContentSize().width + _padding, 0)));
            }
            
        }

    }
}

void CompnNumber::setCount(int count){
    setCount(count, _mode, _padding);
}



