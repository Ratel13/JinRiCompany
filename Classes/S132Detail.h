//
//  S132Detail.h
//  jinRiCompany
//
//  Created by lyy on 13-6-29.
//
//

#ifndef __jinRiCompany__S132Detail__
#define __jinRiCompany__S132Detail__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

class S132Detail : public S1JinRiShangPin, public CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S132Detail);
private:
    cocos2d::CCDictionary* plistDic;
    std::map<std::string, std::string> titleMap;
    void moreMenuCallback(CCObject* pSender);
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

    //networking downloding
};
#endif /* defined(__jinRiCompany__S132Detail__) */
