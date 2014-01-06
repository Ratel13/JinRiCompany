//
//  S4HeZuo.h
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __jinRiCompany__S4HeZuo__
#define __jinRiCompany__S4HeZuo__


#include "cocos2d.h"
#include <string.h>
#include "MainScene.h"

#include "cocos-ext.h"
using namespace cocos2d::extension;
using namespace cocos2d;
using namespace std;
class CCUIKit;
class S4HeZuo : public Main
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
   CCSprite * selectedSprite;
    CCUIKit  * textView;
    
    
};

#endif /* defined(__jinRiCompany__S4HeZuo__) */
