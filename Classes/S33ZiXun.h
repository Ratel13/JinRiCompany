//
//  S33ZiXun.h
//  JinRiCompany
//
//  Created by lyy on 13-7-2.
//
//

#ifndef __JinRiCompany__S33ZiXun__
#define __JinRiCompany__S33ZiXun__

#include <iostream>
#include "cocos2d.h"
#include <string.h>
#include "S3SijiYangSheng.h"

using namespace cocos2d;
using namespace std;
class S33ZiXun : public S3SijiYangSheng
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    
    CREATE_FUNC(S33ZiXun);
private:
	CCDictionary* plistDic;
    CCMenu *imagemenu ;
    void back(CCObject* pSender);
    map<string, string> showPicMap;
    map<string, string> showStrMap;
    void S33ZiXunCallback(CCObject * pSender);
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    //networking downloding
};

#endif /* defined(__JinRiCompany__S33ZiXun__) */
