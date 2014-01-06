//
//  S14Brand.h
//  GreTest
//
//  Created by lyy on 13-6-24.
//
//

#ifndef __GreTest__S14Brand__
#define __GreTest__S14Brand__

#include "cocos2d.h"
#include <string.h>

#include "S1JinRiShangPinScene.h"

using namespace cocos2d;
using namespace std;

class S14Brand : public S1JinRiShangPin
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S14Brand);
    
private:
    CCDictionary* plistDic;
    CCSprite * showTuWenPicture;
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    //networking downloding
    
    map<string, string> showPicMap;
    
    CCSprite *tuwen_sprite;
    
};
#endif /* defined(__GreTest__S14Brand__) */
