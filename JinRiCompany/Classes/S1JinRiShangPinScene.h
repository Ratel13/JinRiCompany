//
//  S1S1JinRiShangPinScene.h
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#ifndef __GreTest__S1S1JinRiShangPinScene__
#define __GreTest__S1S1JinRiShangPinScene__

#include "cocos2d.h"
#include <string.h>
#include "MainScene.h"

using namespace cocos2d;
using namespace std;

class S1JinRiShangPin : public Main
{
public:
    int selectedScene;
    
    virtual bool initInfo();
    virtual bool setUpSubClass();
    virtual bool initInfo2(){return 0;};
    virtual bool setUpSubClass2(){return 0;};
    
    virtual bool initInfo4(){return 0;};
    virtual bool setUpSubClass4(){return 0;};
private:
    CCDictionary* plistDic;
    void menuCallback(CCObject* pSender);
};

#endif /* defined(__GreTest__S1S1JinRiShangPinScene__) */
