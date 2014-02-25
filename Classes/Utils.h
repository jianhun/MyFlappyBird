//
//  Utils.h
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#ifndef __testShao3__Utils__
#define __testShao3__Utils__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Utils : public CCObject{
public:
    static map<string, vector<string> > sharedAtlasMap();
    
    static vector<string> componentsSeparatedByString(const string &str, const string &delim);
    
    static CCSprite* createSprite(const string &name);
    
    static CCArray* createAnimArray(const string &name, int count);
    
    static int hitTest(const CCPoint &pos, const vector<CCRect> &regions);
    
    static int buttonHitTest(const CCPoint &pos, CCArray *buttonArray);
private:
    //static map<string, vector<string> > atlasMap;
};

#endif /* defined(__testShao3__Utils__) */
