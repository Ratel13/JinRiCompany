//
//  S0FirstPage.h
//  JinRiCompany
//
//  Created by lyy on 13-7-26.
//
//

#ifndef __JinRiCompany__S0FirstPage__
#define __JinRiCompany__S0FirstPage__

#include "cocos2d.h"
#include <string.h>
#include "MainScene.h"

using namespace cocos2d;

class S0FirstPage : public Main
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
#endif /* defined(__JinRiCompany__S0FirstPage__) */
