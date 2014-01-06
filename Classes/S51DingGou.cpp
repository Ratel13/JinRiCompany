//  S51DingGou.cpp
//  JinRiCompany
//
//  Created by lyy on 13-7-20.
//
//

#include "S51DingGou.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"

#include "AppDelegate.h"

#include "S51DingGou.h"
//#include "CCUIKit.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"

#define classPlistName_macro "S51DingGou"
#define zNum 100
#define btnTag 100



CCScene* S51DingGou::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S51DingGou *layer = S51DingGou::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S51DingGou::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        
        bRet = true;
	} while (0);
    
	return bRet;
}

bool S51DingGou::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        refreshItemImage->setOpacity(0);
        //setTouchEnabled(true);
        //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -3000, true);
        isMale = true;
        AppDelegate::S51TextViewStr = "";
        feedBackSp = CCSprite::create("FeedBack.png");
        feedBackSp->setPosition(ccp(530,330));
        this->addChild(feedBackSp, zNum, 10);
        
        CCLabelTTF * titlelabel = CCLabelTTF::create(ScriptParser::getStringFromPlist(plistDic,"title"), s1FontName_macro, 15);
        titlelabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+155));
        titlelabel->setColor(ccWHITE);
        this->addChild(titlelabel,zNum+1000);
        float pox = 487+102;
        float poy = 477+12;
        
        male = CCSprite::create("S49RadioSelected.png");//, "S49RadioSelected.png",this,menu_selector(S411FeedBack::changeSex));
        male->setPosition(ccp(pox,poy));
        this->addChild(male,zNum);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        CCMenuItemSprite * maleItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S51DingGou::changeSex));
        maleItem->setPosition(male->getPosition());
        maleItem->setContentSize(CCSizeMake(male->getContentSize().width*3, male->getContentSize().height*3));
        _menu->addChild(maleItem,zNum);
        
        
        
        
        famale =CCSprite::create("S49RadioSelected.png");//, "S49RadioSelected.png",this,menu_selector(S411FeedBack::changeSex));
        famale->setPosition(ccp(pox+60,poy+2));
        this->addChild(famale,zNum);
        famale->setOpacity(0);
        
        CCSprite * sprite3 = CCSprite::create();
        CCSprite * sprite4 = CCSprite::create();
        CCMenuItemSprite * faMaleItem = CCMenuItemSprite::create(sprite3, sprite4,this,menu_selector(S51DingGou::changeSex));
        faMaleItem->setPosition(famale->getPosition());
        faMaleItem->setContentSize(CCSizeMake(famale->getContentSize().width*3, famale->getContentSize().height*3));
        _menu->addChild(faMaleItem,zNum);
        
        
        float editFontSize = 10;
        float addWidth = 128.0+45;
        float addHeight = 45+10;
        const char * input = "";
        
        CCScale9Sprite *sacel9SprG1=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG1->setOpacity(1);
        nameBox=CCEditBox::create(CCSizeMake(sacel9SprG1->getContentSize().width*2.8, sacel9SprG1->getContentSize().height), sacel9SprG1);
        nameBox->setFontName(s1FontName_macro);
        nameBox->setFontSize(editFontSize);
        nameBox->setFontColor(ccBLACK);
        nameBox->setInputMode(kEditBoxInputModeAny);
        nameBox->setPlaceHolder(input);
        nameBox->setPosition(ccp(240+addWidth,430+addHeight));
        this->addChild(nameBox,zNum);
        nameBox->setDelegate(this);
        
        
        
        
        CCScale9Sprite *sacel9SprG2=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG2->setOpacity(1);
        telBox=CCEditBox::create(CCSizeMake(sacel9SprG2->getContentSize().width*2.8, sacel9SprG2->getContentSize().height), sacel9SprG2);
        telBox->setFontSize(editFontSize);
        telBox->setFontColor(ccBLACK);
        telBox->setPlaceHolder(input);
        telBox->setPosition(ccp(240+addWidth,400+addHeight));
        this->addChild(telBox,zNum);
        telBox->setDelegate(this);
        
        
        CCScale9Sprite *sacel9SprG3=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG3->setOpacity(1);
        mobilePhoneBox=CCEditBox::create(CCSizeMake(sacel9SprG3->getContentSize().width*2.8, sacel9SprG3->getContentSize().height), sacel9SprG3);
        mobilePhoneBox->setFontSize(editFontSize);
        mobilePhoneBox->setFontColor(ccBLACK);
        mobilePhoneBox->setPlaceHolder(input);
        mobilePhoneBox->setPosition(ccp(240+addWidth,365+addHeight));
        this->addChild(mobilePhoneBox,zNum);
        mobilePhoneBox->setDelegate(this);
        
        
        
        
        
        CCScale9Sprite *sacel9SprG5=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG5->setOpacity(1);
        msnBox=CCEditBox::create(CCSizeMake(sacel9SprG5->getContentSize().width*2.8, sacel9SprG5->getContentSize().height), sacel9SprG5);
        msnBox->setFontSize(editFontSize);
        msnBox->setFontColor(ccBLACK);
        msnBox->setPlaceHolder(input);
        msnBox->setPosition(ccp(240+addWidth,335+addHeight));//(ccp(240+addWidth,305+addHeight));
        this->addChild(msnBox,zNum);
        msnBox->setDelegate(this);
        
        
        CCScale9Sprite *sacel9SprG6=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG6->setOpacity(1);
        addressBox=CCEditBox::create(CCSizeMake(sacel9SprG6->getContentSize().width*4, sacel9SprG6->getContentSize().height), sacel9SprG6);
        addressBox->setFontSize(editFontSize);
        addressBox->setFontColor(ccBLACK);
        addressBox->setPlaceHolder(input);
        addressBox->setPosition(ccp(275+addWidth,300+addHeight));//(ccp(270+addWidth,269+addHeight));
        this->addChild(addressBox,zNum);
        addressBox->setDelegate(this);
        
         purcharseIntentionX = 377;
         purcharseIntentionY = 330;
        purcharseIntentionScale = 3.0;
        purcharseIntention = CCSprite::create("S49RadioSelected.png");
        purcharseIntention->setPosition(ccp(purcharseIntentionX-purcharseIntention->getContentSize().width/2*(purcharseIntentionScale-1),purcharseIntentionY-purcharseIntention->getContentSize().height/2*(purcharseIntentionScale-1)));
        this->addChild(purcharseIntention,zNum);
        int index = 1;
        for (int i = 0; i<3; i++)
        {
            for (int j= 0; j<3; j++)
            {
                CCSprite * sprite1 = CCSprite::create();
                CCSprite * sprite2 = CCSprite::create();
                CCMenuItemSprite * maleItem = CCMenuItemSprite::create(
                                                                       sprite1,
                                                                       sprite2,
                                                                       this,
                                                                       menu_selector(S51DingGou::changeIntention));
                maleItem->setTag(btnTag+index);
                maleItem->setPosition(ccp(purcharseIntentionX+j*140,purcharseIntentionY-i*37));
                if (j==2)
                {
                    maleItem->setPosition(ccp(purcharseIntentionX+j*130,purcharseIntentionY-i*37));
                }
                if (i==2)
                {
                    maleItem->setPosition(ccp(purcharseIntentionX+j*140,purcharseIntentionY-i*35));
                    if (j==2)
                    {
                        maleItem->setPosition(ccp(purcharseIntentionX+j*130,purcharseIntentionY-i*35));
                    }
                }
                maleItem->setContentSize(CCSizeMake(male->getContentSize().width*purcharseIntentionScale, male->getContentSize().height*purcharseIntentionScale));
                _menu->addChild(maleItem,zNum);
                index++;
            }
        }
        /*
        textView = CCUIKit::create();
        CCRect aRect = CCRectMake(295, 480, 500, 100);
        textView->creatWithRect(aRect,this);
        addChild(textView);
        AppDelegate::isTextViewExist = false;
       */
        
        CCScale9Sprite *sacel9SprG8=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG8->setOpacity(1);
        submitBox=CCEditBox::create(CCSizeMake(sacel9SprG8->getContentSize().width*1.5, sacel9SprG8->getContentSize().height), sacel9SprG8);
        submitBox->setFontSize(editFontSize);
        submitBox->setFontColor(ccBLACK);
        //submitBox->setPlaceHolder("asdhjashdkjansda\nasdjgkjahdkjas");//input);
        submitBox->setPosition(ccp(210+addWidth,140+addHeight));
        this->addChild(submitBox,zNum);
        submitBox->setDelegate(this);
        
        
        CCMenuItemFont *aItemFont = CCMenuItemFont::create(ScriptParser::getStringFromPlist(plistDic,"submit"),this,menu_selector(S51DingGou::submit));
        aItemFont->setOpacity(1);
        aItemFont->setColor(ccBLACK);
        aItemFont->setPosition(ccp(550,115));
        _menu ->addChild(aItemFont,zNum);
        
		bRet = true;
	} while (0);
    
	return bRet;
}
void S51DingGou::editBoxEditingDidBegin(CCEditBox *editBox)
{
    CCLOG("start edit");
    
}
void S51DingGou::editBoxEditingDidEnd(CCEditBox *editBox)
{
    CCLOG("end edit");
}
void S51DingGou::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    CCLOG("textchanged");
    
}
void S51DingGou::editBoxReturn(CCEditBox *editBox)
{
    CCLOG("editboxreturn");
    
}
/*
void S51DingGou::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (textView->isEditing)
    {
        textView->setFirstResponder(true);
    }
    
}
*/
void S51DingGou::feedBack(CCObject * pSender)
{
}
void S51DingGou::submit(CCObject * pSender)
{
    _menu->setEnabled(false);

    string plistStr = classPlistName_macro;
    plistStr += ".plist";
    plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
    AppDelegate::loadingLabel = CCLabelTTF::create(ScriptParser::getStringFromPlist(plistDic,"submiting"), s1FontName_macro, 40);
    AppDelegate::loadingLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    AppDelegate::loadingLabel->setColor(ccRED);
    this->addChild(AppDelegate::loadingLabel,zNum+1000);
    
    string name(nameBox->getText());
    string sex;
    if (isMale)
    {
        sex = ScriptParser::getStringFromPlist(plistDic,"male");
    }
    else
    {
        sex = ScriptParser::getStringFromPlist(plistDic,"famale");
    }
    string tel(telBox->getText());
    if (name.size()==0||tel.size()==0)
    {
        AppDelegate::loadingLabel ->setString("请完整填写必填信息");
         this->schedule(schedule_selector(S51DingGou::time),1.0f,false,0.0);
        return;
    }
    string mobilePhone(mobilePhoneBox->getText());
    string msn(msnBox->getText());
    string address(addressBox->getText());
    string submitStr(submitBox->getText());
    string requestSr = "http://www.jrsp.cn/app/iwant.php?name="+name+"&sex="+sex+"&phone="+tel+"&mobile="+mobilePhone+msn+"&address="+address+"&address="+intentionStr+"&message="+submitStr;
   
    
   
    requestSr = PersonalApi::string_replace(requestSr," ","%20");
    requestSr = PersonalApi::string_replace(requestSr,"\n","%0D");
    
    PostToUrl(requestSr.c_str(),"name","name");

    //setButtonEnabel(true);
}
void S51DingGou::time(float dt)
{
    AppDelegate::loadingLabel->setString("");
    nameBox->setText("");
    telBox->setText("");
    mobilePhoneBox->setText("");
    msnBox->setText("");
    addressBox->setText("");
   
    submitBox->setText("");
    
    intentionStr = "";
    purcharseIntention->setPosition(ccp(purcharseIntentionX-purcharseIntention->getContentSize().width/2*(purcharseIntentionScale-1),purcharseIntentionY-purcharseIntention->getContentSize().height/2*(purcharseIntentionScale-1)));
}

void S51DingGou::changeSex(CCObject * pSender)
{
    
    if (isMale)
    {
        isMale = false;
        famale->setOpacity(0);
        male->setOpacity(255);
    }
    else
    {
        isMale = true;
        famale->setOpacity(255);
        male->setOpacity(0);
    }
    
}
void S51DingGou::changeIntention(CCObject * pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    string plistStr = classPlistName_macro;
    plistStr += ".plist";
    plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
    map<string, string>aMap = ScriptParser::getGroupStringFromPlist(plistDic,"Intention");
    intentionStr  =  aMap[PersonalApi::convertIntToString(aItem->getTag()-btnTag)];
    purcharseIntention->setPosition(ccp(aItem->getPosition().x-purcharseIntention->getContentSize().width/2*(purcharseIntentionScale-1),aItem->getPosition().y-purcharseIntention->getContentSize().height/2*(purcharseIntentionScale-1)));
}
void S51DingGou::onPostFinished(CCNode *node,void *data)
{
    _menu->setEnabled(true);
    AppDelegate::loadingLabel ->setString("");
	CCHttpResponse *response = (CCHttpResponse*)data;
	if (!response)
	{
		return;
	}
	int s=response->getHttpRequest()->getRequestType();
	CCLOG("request type %d",s);
    
    
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLOG("%s ------>oked", response->getHttpRequest()->getTag());
	}
    
	int statusCode = response->getResponseCode();
	CCLOG("response code: %d", statusCode);
    
    
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLOG("statusString");
    
	if (!response->isSucceed())
	{
		CCLOG("response failed");
		CCLOG("error buffer: %s", response->getErrorBuffer());
        AppDelegate::loadingLabel->setString("提交失败");
         this->schedule(schedule_selector(S51DingGou::time),1.0f,false,0.0);
		return;
	}
	
	//上面这些都是一些判断是否请求成功，下面这个是获得的请求数据
	std::vector<char> *buffer = response->getResponseData();
	CCLOG("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		CCLOG("%c", (*buffer)[i]);//这里打印从服务器返回的数据
        
	}
	CCLOG("\n");
    AppDelegate::loadingLabel->setString("提交成功");
   this->schedule(schedule_selector(S51DingGou::time),1.0f,false,0.0);
}
