//
//  CompnButton.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-19.
//
//

#include "CompnButton.h"

CompnButton::CompnButton(){
    
}

CompnButton::~CompnButton(){
    
}

CompnButton* CompnButton::create(){
    CompnButton* compnButton = new CompnButton();
    if (compnButton && compnButton->init()) {
        compnButton->autorelease();
        return compnButton;
    }
    else{
        delete compnButton;
        compnButton = NULL;
        return NULL;
    }
}

bool CompnButton::init(){
    if (CCNode::init()) {
        return true;
    }
    return false;
}

void CompnButton::setContent(const int bid, cocos2d::CCNode *content){
    _bid = bid;
    
    this->removeAllChildrenWithCleanup(true);
    _content = content;
    this->addChild(content);
    
    CCSize size = content->getContentSize();
    this->setHitRect(CCRectMake(-size.width*0.5, -size.height*0.5, size.width, size.height));
}

CCNode* CompnButton::getContent(){
    return _content;
}

void CompnButton::setBid(const int bid){
    _bid = bid;
}

int CompnButton::getBid(){
    return _bid;
}

void CompnButton::setHitRect(const cocos2d::CCRect &rect){
    _rcHit = rect;
}

void CompnButton::resizeHitRect(float flactor){
    CCPoint center = ccp(_rcHit.origin.x + _rcHit.size.width * 0.5, _rcHit.origin.y + _rcHit.size.height * 0.5);
    CCSize size = CCSizeMake(_rcHit.size.width * flactor, _rcHit.size.height * flactor);
    _rcHit = CCRectMake(center.x - size.width * 0.5, center.y - size.height * 0.5, size.width, size.height);
}

CCRect CompnButton::getHitRect(){
    if(this->isVisible())
    {
        CCPoint worldPos = this->convertToWorldSpaceAR(CCPointZero);
        return CCRectMake(worldPos.x + _rcHit.origin.x, worldPos.y + _rcHit.origin.y, _rcHit.size.width, _rcHit.size.height);
        
    }else {
        return CCRectMake(0.0, 0.0, 0.0, 0.0);
    }

}

void CompnButton::touch(){
    CCMoveBy *move = CCMoveBy::create(0.05, ccp(0, -10));
    _content->runAction(move);
}

void CompnButton::click(){
    CCMoveBy *move = CCMoveBy::create(0.05, ccp(0, 10));
    _content->runAction(move);
}



