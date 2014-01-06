//
//  S3SijiYangSheng.h
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __jinRiCompany__S3SijiYangSheng__
#define __jinRiCompany__S3SijiYangSheng__

#include "cocos2d.h"
#include <string.h>
#include "MainScene.h"

using namespace cocos2d;
using namespace std;


class S3SijiYangSheng : public Main
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

};

#endif /* defined(__jinRiCompany__S3SijiYangSheng__) */
