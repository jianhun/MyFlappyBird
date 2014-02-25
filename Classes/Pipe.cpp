//
//  Pipe.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#include "Pipe.h"
#include "Utils.h"

Pipe::Pipe():isPassed(false){
    
}

Pipe::~Pipe(){
    
}

bool Pipe::init(){
    if (!CCNode::init()) {
        return false;
    }
    
    pipePadding = 50;
    int pipeTop = CCDirector::sharedDirector()->getWinSize().height -  100;
    int pipeBottom = 200;
    
    centerH = pipeBottom + rand() % (pipeTop - pipeBottom + 1);
    
    //up
    pipeUp = Utils::createSprite("pipe_up");
    pipeUp->setAnchorPoint(ccp(0.0, 1.0));
    pipeUp->setPosition(ccp(0.0, centerH - pipePadding));
    this->addChild(pipeUp);
    
    //down
    pipeDown = Utils::createSprite("pipe_down");
    pipeDown->setAnchorPoint(ccp(0.0, 0.0));
    pipeDown->setPosition(ccp(0.0, centerH + pipePadding));
    this->addChild(pipeDown);
    
    return true;
}

float Pipe::getCenterH(){
    return centerH;
}

float Pipe::getPipePadding(){
    return pipePadding;
}

void Pipe::setPassed(const bool state)
{
    isPassed = state;
}

bool Pipe::getPassed()
{
    return isPassed;
}




