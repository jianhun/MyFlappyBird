//
//  PopupEventDelegate.h
//  testShao3
//
//  Created by shaozhen on 14-2-20.
//
//

#ifndef __testShao3__PopupEventDelegate__
#define __testShao3__PopupEventDelegate__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class PopupEventDelegate
{
public:
    PopupEventDelegate()
    {
        
    }
    
    virtual ~PopupEventDelegate()
    {
        
    }
    
    virtual bool onPopupEventMenuCommand(CCLayer* component, const int menuId)
    {
        CC_UNUSED_PARAM(component);
        CC_UNUSED_PARAM(menuId);
        
        return true;
    }
    
    virtual void onPopupEventDismiss(CCLayer* component)
    {
        CC_UNUSED_PARAM(component);
    }
};

#endif /* defined(__testShao3__PopupEventDelegate__) */
