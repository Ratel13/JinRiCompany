//
//  S24AutoPlay.h
//  JinRiCompany
//
//  Created by lyy on 13-7-1.
//
//

#ifndef __JinRiCompany__S24AutoPlay__
#define __JinRiCompany__S24AutoPlay__

#include <string.h>
#include "cocos-ext.h"

#include "S2ZiBu.h"
#include "FDScrollView.h"

class S24AutoPlay : public cocos2d::CCLayerColor 
{
public:
    static cocos2d::CCScene* scene();
    virtual bool init();
    cocos2d::CCMenu* _menu;
    CREATE_FUNC(S24AutoPlay);
private:
    cocos2d::CCDictionary* plistDic;
    
    FDScrollView *m_pScrollView;
    
    map<std::string, std::string>picMp;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    
    //virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){ return true;};
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){ return;};
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){ return;};
    
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};
    void S2menuCallback(CCObject* pSender);
    void showBigPic(CCObject* pSender);
    void S4back(CCObject* pSender);
    
    std::map<std::string, std::string> titleMap;
    std::map<std::string, std::string> weightMap;
    
};
#endif /* defined(__JinRiCompany__S24AutoPlay__) */
