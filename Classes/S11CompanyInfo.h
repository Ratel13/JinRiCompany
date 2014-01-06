//
//  S11CompanyInfo.h
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#ifndef __GreTest__S11CompanyInfo__
#define __GreTest__S11CompanyInfo__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S11CompanyInfo : public S1JinRiShangPin,public CCScrollViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S11CompanyInfo);
private:
    
    CCDictionary* plistDic;
    
    CCSprite * showbigPicture;
    
    
    void companyMenuCallback(CCObject* pSender);
    map<string, string> showPicMap;
    map<string, string> showStrMap;
   
    CCScrollView * loopScrollView;
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    float scrollMaxSizeX;
    float currentLoopWidth;
    void loopScroll(float dt);
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    //networking downloding
    
    
    void showBigPic(CCObject* pSender);
    
    
    map<std::string, std::string> naviGroupStrMap;
    

    
    int bigPicIndex;
    void bugFix(CCObject* pSender);
    void loopScroll1(float dt);
    void loopScroll2(float dt);
    bool isMenuLock;
    void S31Delay(float dt);
};

#endif /* defined(__GreTest__S11CompanyInfo__) */
