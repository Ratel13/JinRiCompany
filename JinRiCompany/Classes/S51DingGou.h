//
//  S51DingGou.h
//  JinRiCompany
//
//  Created by lyy on 13-7-20.
//
//

#ifndef __JinRiCompany__S51DingGou__
#define __JinRiCompany__S51DingGou__
#include <string>
#include "cocos-ext.h"

#include "S4HeZuo.h"
#include "S5DingGou.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S51DingGou : public S5DingGou,public CCEditBoxDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S51DingGou);
    
    string textViewStr;
    
private:
    CCDictionary* plistDic;

    void feedBack(CCObject * pSender);
    CCEditBox *nameBox;
    CCEditBox *telBox;
    CCEditBox *mobilePhoneBox;
    CCEditBox *msnBox;
    CCEditBox *addressBox;
    CCEditBox *messageBox;
    CCEditBox * submitBox;
    
    
    
    void submit(CCObject * pSender);
    void time(float dt);
    
    virtual void editBoxEditingDidBegin(CCEditBox *editBox);
    virtual void editBoxEditingDidEnd(CCEditBox *editBox);
    virtual void editBoxTextChanged(CCEditBox *editBox,const std::string &text);
    virtual void editBoxReturn(CCEditBox *editBox);

    CCSprite * male;
    CCSprite * famale;
    
    
    
    void changeSex(CCObject * pSender);
    bool isMale;
    
    CCSprite * purcharseIntention;
    void changeIntention(CCObject * pSender);
    float purcharseIntentionX;
    float purcharseIntentionY ;
    float purcharseIntentionScale;
    string intentionStr;
    //这个是返回的数据
    virtual void onPostFinished(CCNode *node,void *data);
    
    /*
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};
    */
};
#endif /* defined(__JinRiCompany__S51DingGou__) */
