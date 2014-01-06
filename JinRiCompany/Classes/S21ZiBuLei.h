//
//  S21ZiBuLei.h
//  JinRiCompany
//
//  Created by lyy on 13-6-24.
//
//

#ifndef __JinRiCompany__S21ZiBuLei__
#define __JinRiCompany__S21ZiBuLei__

#include "cocos2d.h"
#include <string.h>

#include "S2ZiBu.h"
#include "cocos-ext.h"
using namespace extension;

class S21ZiBuLei : public S2ZiBu, public CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S21ZiBuLei);
private:
    cocos2d::CCDictionary* plistDic;
    void S21ZiBuLeiMenuCallback(CCObject* pSender);
    
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    map<string, string> showPicMap;
    map<string, string> showStrMap;
    void S311DetailCallback(CCObject * pSender);
    
    float countOffSet;
    float OffSetY;
    CCScrollView *m_pScrollView;
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
    void S31Delay(float dt);
    bool isMenuLock;
    CCMenu * imagemenu;
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    void goRequest();
    //networking downloding

};
#endif /* defined(__JinRiCompany__S21ZiBuLei__) */
