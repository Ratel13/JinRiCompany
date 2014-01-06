//
//  S13News.h
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#ifndef __GreTest__S13News__
#define __GreTest__S13News__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S13News : public S1JinRiShangPin
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S13News);
private:
    cocos2d::CCDictionary* plistDic;
    void newsMenuCallback(CCObject* pSender);
    void showDetail(CCObject* pSender);
    
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    //networking downloding
    
    map<string, string> rightBigTitleCnMap;
    map<string, string> rightBigTitleEnMap;
    map<string, string> rightDetailTitleMap;
};

#endif /* defined(__GreTest__S13News__) */
