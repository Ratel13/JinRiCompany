//
//  S31MeiShi.h
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __jinRiCompany__S31MeiShi__
#define __jinRiCompany__S31MeiShi__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"
#include "S3SijiYangSheng.h"

using namespace cocos2d;
using namespace std;
using namespace extension;


class S31MeiShi : public S3SijiYangSheng, public CCScrollViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S31MeiShi);
private:
    CCDictionary* plistDic;
    CCMenu *imagemenu ;
    void S31MeiShiMenuCallback(CCObject* pSender);
    
    void timer(CCTime dt);
    void timer2(CCTime dt);
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    map<string, string> showPicMap;
    map<string, string> showStrMap;
    void S31MeiShiCallback(CCObject * pSender);
    
    float countOffSet;
    float OffSetY;
    CCScrollView *m_pScrollView;
    
    
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    void S31Delay(float dt);
    bool isMenuLock;
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    std::map<string, string> titlePicNameMap;
    //networking downloding
    
};

#endif /* defined(__jinRiCompany__S31MeiShi__) */
