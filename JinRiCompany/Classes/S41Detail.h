//
//  S41Detail.h
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#ifndef __jinRiCompany__S41Detail__
#define __jinRiCompany__S41Detail__

#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"

#include "S4HeZuo.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S41Detail : public S4HeZuo, public CCScrollViewDelegate,public CCEditBoxDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S41Detail);
private:
    CCDictionary* plistDic;
    CCScrollView *m_pScrollView;
    
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    //networking downloding
    
    CCMenuItemImage * feedBackSp;
    void feedBack(CCObject * pSender);
    CCEditBox *nameBox;
    CCEditBox *telBox;
    CCEditBox *mobilePhoneBox;
    CCEditBox *mailBox;
    CCEditBox *msnBox;
    CCEditBox *addressBox;
    CCEditBox *messageBox;
    CCEditBox *yanzhengBox;
    
    CCLabelTTF *nameBoxLabel;
    CCLabelTTF *telBoxLabel;
    CCLabelTTF *mobilePhoneBoxLabel;
    CCLabelTTF *mailBoxLabel;
    CCLabelTTF *msnBoxLabel;
    CCLabelTTF *addressBoxLabel;
    CCLabelTTF *messageBoxLabel;
    CCLabelTTF *yanzhengBoxLabel;
    
    void submit(CCObject * pSender);
    void time(float dt);
    
    virtual void editBoxEditingDidBegin(CCEditBox *editBox);
    virtual void editBoxEditingDidEnd(CCEditBox *editBox);
    virtual void editBoxTextChanged(CCEditBox *editBox,const std::string &text);
    virtual void editBoxReturn(CCEditBox *editBox);
    
    bool isMenuLock;
    void S31Delay(float dt);
    
    
    
};

#endif /* defined(__jinRiCompany__S41Detail__) */
