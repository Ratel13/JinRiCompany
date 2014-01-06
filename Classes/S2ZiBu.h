//
//  S2ZiBu.h
//  JinRiCompany
//
//  Created by lyy on 13-6-24.
//
//

#ifndef __JinRiCompany__S2ZiBu__
#define __JinRiCompany__S2ZiBu__

#include "cocos2d.h"
#include <string.h>
#include "MainScene.h"

class S2ZiBu : public Main
{
public:
    int selectedScene;
    
    virtual bool initInfo();
    virtual bool setUpSubClass();
    virtual bool initInfo2(){return 0;};
    virtual bool setUpSubClass2(){return 0;};
    
    virtual bool initInfo4(){return 0;};
    virtual bool setUpSubClass4(){return 0;};
    std::map<std::string, std::string> leftNaviGroupStrMap;
    
    std::map<std::string, std::string> titleMap;
    std::map<std::string, std::string> weightMap;
  
private:
    cocos2d::CCDictionary* plistDic;
    void menuCallback(CCObject* pSender);
    void leftMenuCallback(CCObject* pSender);
    void introCallback(CCObject* pSender);
    cocos2d::CCSprite * selectedSprite;
    cocos2d::CCLabelTTF * shangPinLabel;
    cocos2d::CCLabelTTF *colorLabel;
    cocos2d::CCLabelTTF * introLabel;
    cocos2d::CCSprite * introSeleSprite;
 
};


#endif /* defined(__JinRiCompany__S2ZiBu__) */
