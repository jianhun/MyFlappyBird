//
//  AniNode.h
//  testShao3
//
//  Created by shaozhen on 14-2-22.
//
//

#ifndef __testShao3__AniNode__
#define __testShao3__AniNode__

#include "cocos2d.h"

USING_NS_CC;

class AniNode : public CCNode
{
public:
    AniNode();
    
    virtual bool init();
    
    virtual void update(float delta);
    
    void setMoveSpeed(CCPoint speed);
    
    CCPoint getMoveSpeed();
    
    void setMoveAccSpeed(CCPoint speed);
    
    CCPoint getMoveAccSpeed();
    
    void setMoveMaxSpeed(CCPoint speed);
    
    CCPoint getMoveMaxSpeed();
    
    void setRotateSpeed(float speed);
    
    float getRotateSpeed();
    
    void setRotateAccSpeed(float speed);
    
    float getRotateAccSpeed();
    
    void setRotateMaxSpeed(float speed);
    
    float getRotateMaxSpeed();
protected:
    CCPoint aniNode_moveSpeed;
    
    CCPoint aniNode_accMoveSpeed;
    
    CCPoint aniNode_maxMoveSpeed;
    
    float aniNode_rotateSpeed;
    
    float aniNode_accRotateSpeed;
    
    float aniNode_maxRotateSpeed;
};

#endif /* defined(__testShao3__AniNode__) */
