//
//  S23DetailIntro.h
//  JinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __JinRiCompany__S23DetailIntro__
#define __JinRiCompany__S23DetailIntro__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S2ZiBu.h"

class S23DetailIntro : public S2ZiBu,public CCScrollViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S23DetailIntro);
private:
    cocos2d::CCDictionary* plistDic;
    
    CCScrollView *m_pScrollView;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){ return false;};
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){ return;};
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){ return;};
    
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};
    void S2menuCallback(CCObject* pSender);
    void showBigPic(CCObject* pSender);
    void S2back(CCObject* pSender);

    virtual void scrollViewDidScroll(CCScrollView* view){};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    //networking downloding
    
    
};
#endif /* defined(__JinRiCompany__S23DetailIntro__) */
