//
//  UtilsJNI.h
//  testShao3
//
//  Created by shaozhen on 14-2-21.
//
//

#ifndef __testShao3__UtilsJNI__
#define __testShao3__UtilsJNI__

extern "C"
{
    int JNI_getInt(const char *key, int defaultValue);
    
    void JNI_setInt(const char *key, int value);
    
    bool JNI_getBool(const char *key, bool defaultValue);
    
    void JNI_setBool(const char *key, bool value);

    void JNI_showAdsScreen();

    void JNI_closeAdsScreen();
};

#endif /* defined(__testShao3__UtilsJNI__) */
