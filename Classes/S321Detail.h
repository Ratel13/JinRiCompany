//
//  S321Detail.h
//  JinRiCompany
//
//  Created by lyy on 13-7-3.
//
//

#ifndef __jinRiCompany__S321Detail__
#define __jinRiCompany__S321Detail__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S32XiaoTieShi.h"

class S321Detail : public S32XiaoTieShi, public CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S321Detail);
private:
    cocos2d::CCDictionary* plistDic;
    std::map<std::string, std::string> titleMap;
    void moreMenuCallback(CCObject* pSender);
    void next(CCObject* pSender);
    void last(CCObject* pSender);
    void back(CCObject* pSender);
    
    CCScrollView *m_pScrollView;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    
    virtual void scrollViewDidScroll(CCScrollView* view){};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    //networking downloding
};
#endif /* defined(__jinRiCompany__S321Detail__) */

