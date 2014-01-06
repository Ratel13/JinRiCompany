//
//  S5DingGou.h
//  JinRiCompany
//
//  Created by lyy on 13-7-20.
//
//

#ifndef __JinRiCompany__S5DingGou__
#define __JinRiCompany__S5DingGou__

#include <string.h>
#include "MainScene.h"

#include "cocos-ext.h"

using namespace cocos2d::extension;
using namespace cocos2d;
using namespace std;
class CCUIKit;
class S5DingGou : public Main
{
public:
    int selectedScene;
    
    virtual bool initInfo();
    virtual bool setUpSubClass();
    virtual bool initInfo2(){return 0;};
    virtual bool setUpSubClass2(){return 0;};
    
    virtual bool initInfo4(){return 0;};
    virtual bool setUpSubClass4(){return 0;};
    
    CCUIKit  * textView;
    CCSprite * feedBackSp;
    
private:
    CCDictionary* plistDic;
    void menuCallback(CCObject* pSender);
    CCSprite * selectedSprite;
    
    
    
};

#endif /* defined(__JinRiCompany__S5DingGou__) */
