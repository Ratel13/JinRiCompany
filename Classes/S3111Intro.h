//
//  S3111Intro.h
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#ifndef __jinRiCompany__S3111Intro__
#define __jinRiCompany__S3111Intro__

#include "cocos2d.h"
#include <string.h>
#include "S3SijiYangSheng.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace std;
using namespace extension;
class S3111Intro : public S3SijiYangSheng, public CCScrollViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();

    CREATE_FUNC(S3111Intro);
private:
	CCDictionary* plistDic;
    CCMenu *imagemenu ;
    void back(CCObject* pSender);
    map<string, string> showPicMap;
    map<string, string> showStrMap;
    void S3111IntroCallback(CCObject * pSender);
    void next(CCObject* pSender);
    void last(CCObject* pSender);
    
    
    CCScrollView *m_pScrollView;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    
    virtual void scrollViewDidScroll(CCScrollView* view){};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    //networking downloding
    
};

#endif /* defined(__jinRiCompany__S3111Intro__) */

