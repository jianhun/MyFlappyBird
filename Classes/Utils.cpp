//
//  Utils.cpp
//  testShao3
//
//  Created by shaozhen on 14-2-18.
//
//

#include "Utils.h"
#include "CompnButton.h"

static map<string, vector<string> > atlasMap = map<string, vector<string> >();
map<string, vector<string> > Utils::sharedAtlasMap(){
    if (atlasMap.size() == 0) {
        unsigned char* fileContents = NULL;
        unsigned long fileSize = 0;
        string contents;
        string thisLine;
        vector<string> lines;
        
        string fullfilename = "atlas.txt";
        string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(fullfilename.c_str());
        fileContents = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "r", &fileSize);
        contents.append((char*)fileContents, fileSize);
        istringstream fileStringStream(contents);
        while (getline(fileStringStream, thisLine)) {
            lines.push_back(thisLine);
        }
        if(fileContents) {
            delete[] fileContents;
            fileContents = NULL;
        }
        
        
        int idx = 0;
        while (idx < lines.size()) {
            string line = lines[idx];
            vector<string> v = componentsSeparatedByString(line, " ");
            atlasMap[v[0]] = v;
            idx++;
        }
    }
    
    return atlasMap;
}

vector<string> Utils::componentsSeparatedByString(const string &str, const string &delim){
    vector<string> tokens;
    string::size_type lastPos = 0;
    string::size_type pos = str.find(delim, lastPos);
    while (string::npos != pos) {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = pos + delim.size();
        pos = str.find(delim, lastPos);
    }
    tokens.push_back(str.substr(lastPos, str.size() - lastPos));
    return tokens;
}

CCSprite* Utils::createSprite(const string &name){
    int w = 1024;
    int h = 1024;
    vector<string> pos = sharedAtlasMap()[name];
    CCSprite *sprite = CCSprite::create("atlas.png", CCRectMake(atof(pos[3].c_str()) * w, atof(pos[4].c_str()) * h, atof(pos[5].c_str()) * w, atof(pos[6].c_str()) * h));
    return sprite;
};

CCArray* Utils::createAnimArray(const string &name, int count){
    CCArray *animArray = CCArray::createWithCapacity(count);
    int w = 1024;
    int h = 1024;
    
    int idx = 0;
    while (idx < count) {
        stringstream stream;
        stream << name << "_" << idx;
        string idxName = stream.str();
        
        vector<string> pos = sharedAtlasMap()[idxName];
        CCSpriteFrame *sFrame = CCSpriteFrame::create("atlas.png", CCRectMake(atof(pos[3].c_str()) * w, atof(pos[4].c_str()) * h, atof(pos[5].c_str()) * w, atof(pos[6].c_str()) * h));
        animArray->addObject(sFrame);
        
        idx++;
    }
    return animArray;
};

int Utils::hitTest(const cocos2d::CCPoint &pos, const vector<cocos2d::CCRect> &regions){
    int hit = -1;
    if (regions.size() != 0) {
        for (int i = regions.size(); i >= 0; i--) {
            CCRect rc = regions[i];
            if (rc.containsPoint(pos)) {
                hit = i;
                break;
            }
        }
    }
    return hit;
}

int Utils::buttonHitTest(const cocos2d::CCPoint &pos, CCArray *buttonArray){
    int hit = -1;

    if (buttonArray->count()>0) {
        for (int i = 0; i < buttonArray->count(); i++) {
            CompnButton *btn = (CompnButton*)buttonArray->objectAtIndex(i);
            CCRect rc = btn->getHitRect();
            if (rc.containsPoint(pos)) {
                hit = i;
                break;
            }
        }
    }
    return hit;
}



