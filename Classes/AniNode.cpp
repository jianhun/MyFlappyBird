//
//  AniNode.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-22.
//
//

#include "AniNode.h"

AniNode::AniNode():aniNode_accMoveSpeed(ccp(0, 0)), aniNode_maxMoveSpeed(ccp(1024, 1024)), aniNode_moveSpeed(ccp(0, 0)), aniNode_rotateSpeed(0), aniNode_accRotateSpeed(0), aniNode_maxRotateSpeed(360)
{
    
}

bool AniNode::init()
{
    if (!CCNode::init()) {
        return false;
    }
    return true;
}

void AniNode::update(float delta)
{
    if (ccpLength(aniNode_moveSpeed) != 0 || ccpLength(aniNode_accMoveSpeed) != 0) {
        CCPoint dis = ccpAdd(ccpMult(aniNode_moveSpeed, delta), ccpMult(aniNode_accMoveSpeed, 0.5 * delta * delta));
        this->setPosition(ccpAdd(this->getPosition(), dis));
        aniNode_moveSpeed = ccpAdd(aniNode_moveSpeed, ccpMult(aniNode_accMoveSpeed, delta));
    }    
    
    if (aniNode_rotateSpeed != 0 || aniNode_accRotateSpeed != 0) {
        float rot = aniNode_rotateSpeed * delta + 0.5 * aniNode_accRotateSpeed * delta * delta;
        this->setRotation(this->getRotation() + rot);
        aniNode_rotateSpeed = aniNode_rotateSpeed + aniNode_accRotateSpeed * delta;
    }    
    
}

void AniNode::setMoveSpeed(cocos2d::CCPoint speed)
{
    aniNode_moveSpeed = speed;
}

CCPoint AniNode::getMoveSpeed()
{
    return aniNode_moveSpeed;
}

void AniNode::setMoveAccSpeed(cocos2d::CCPoint speed)
{
    aniNode_accMoveSpeed = speed;
}

CCPoint AniNode::getMoveAccSpeed()
{
    return aniNode_accMoveSpeed;
}

void AniNode::setMoveMaxSpeed(cocos2d::CCPoint speed)
{
    aniNode_maxMoveSpeed = speed;
}

CCPoint AniNode::getMoveMaxSpeed()
{
    return aniNode_maxMoveSpeed;
}

void AniNode::setRotateSpeed(float speed)
{
    aniNode_rotateSpeed = speed;
}

float AniNode::getRotateSpeed()
{
    return aniNode_rotateSpeed;
}

void AniNode::setRotateAccSpeed(float speed)
{
    aniNode_accRotateSpeed = speed;
}

float AniNode::getRotateAccSpeed()
{
    return aniNode_accRotateSpeed;
}

void AniNode::setRotateMaxSpeed(float speed)
{
    aniNode_maxRotateSpeed = speed;
}

float AniNode::getRotateMaxSpeed()
{
    return aniNode_maxRotateSpeed;
}




