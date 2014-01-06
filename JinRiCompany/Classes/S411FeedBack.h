//
//  S411FeedBack.h
//  JinRiCompany
//
//  Created by lyy on 13-7-20.
//
//

#ifndef __JinRiCompany__S411FeedBack__
#define __JinRiCompany__S411FeedBack__

#include <string>
#include "cocos-ext.h"

#include "S4HeZuo.h"

using namespace cocos2d;
using namespace std;
using namespace extension;
class CCUIKit;
class S411FeedBack : public S4HeZuo,public CCEditBoxDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CCUIKit* textView;
    CCSprite * feedBackSp;
    CREATE_FUNC(S411FeedBack);
private:
    CCDictionary* plistDic;
  
    void feedBack(CCObject * pSender);
    CCEditBox *nameBox;
    CCEditBox *telBox;
    CCEditBox *mobilePhoneBox;
    CCEditBox *mailBox;
    CCEditBox *msnBox;
    CCEditBox *addressBox;
    CCEditBox *messageBox;
    CCEditBox *yanzhengBox;
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

    void back(CCObject * pSender);
    

    //这个是返回的数据
    virtual void onPostFinished(CCNode *node,void *data);
    
};

#endif /* defined(__jinRiCompany__S411FeedBack__) */

