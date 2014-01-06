
//  S411FeedBack.cpp
//  JinRiCompany
//
//  Created by lyy on 13-7-20.
//
//

#include "S411FeedBack.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"

#include "AppDelegate.h"

#include "S411FeedBack.h"
#include "CCUIKit.h"
#include "S41Detail.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S411FeedBack"
#define zNum 100
#define btnTag 100



CCScene* S411FeedBack::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S411FeedBack *layer = S411FeedBack::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S411FeedBack::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        //plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 1;
        
        bRet = true;
	} while (0);
    
	return bRet;
}

bool S411FeedBack::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        refreshItemImage->setOpacity(0);
        refreshItemImage->setEnabled(false);
        isMale = true;
        AppDelegate::S51TextViewStr = "";
        
        feedBackSp = CCSprite::create("S41FeedBack.png");
        feedBackSp->setPosition(ccp(530,330));
        this->addChild(feedBackSp, zNum, 10);
        
        float pox = 487;
        float poy = 477;
        
        male = CCSprite::create("S49RadioSelected.png");
        male->setPosition(ccp(pox,poy));
        this->addChild(male,zNum);
        
        CCSprite * sprite1 = CCSprite::create();
        CCSprite * sprite2 = CCSprite::create();
        CCMenuItemSprite * maleItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S411FeedBack::changeSex));
        maleItem->setPosition(male->getPosition());
        maleItem->setContentSize(CCSizeMake(male->getContentSize().width*3, male->getContentSize().height*3));
        _menu->addChild(maleItem,zNum);
        
        
        
        
        famale =CCSprite::create("S49RadioSelected.png");
        famale->setPosition(ccp(pox+45,poy));
        this->addChild(famale,zNum);
        famale->setOpacity(0);
        
        CCSprite * sprite3 = CCSprite::create();
        CCSprite * sprite4 = CCSprite::create();
        CCMenuItemSprite * faMaleItem = CCMenuItemSprite::create(sprite3, sprite4,this,menu_selector(S411FeedBack::changeSex));
        faMaleItem->setPosition(famale->getPosition());
        faMaleItem->setContentSize(CCSizeMake(famale->getContentSize().width*3, famale->getContentSize().height*3));
        _menu->addChild(faMaleItem,zNum);
        
        
        float editFontSize = 10;
        float addWidth = 128.0;
        float addHeight = 45;
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
        
        
        
        CCScale9Sprite *sacel9SprG4=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG4->setOpacity(1);
        mailBox=CCEditBox::create(CCSizeMake(sacel9SprG4->getContentSize().width*2.8, sacel9SprG4->getContentSize().height), sacel9SprG4);
        mailBox->setFontSize(editFontSize);
        mailBox->setFontColor(ccBLACK);
        mailBox->setPlaceHolder(input);
        mailBox->setPosition(ccp(240+addWidth,335+addHeight));
        this->addChild(mailBox,zNum);
        mailBox->setDelegate(this);
        
        
        CCScale9Sprite *sacel9SprG5=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG5->setOpacity(1);
        msnBox=CCEditBox::create(CCSizeMake(sacel9SprG5->getContentSize().width*2.8, sacel9SprG5->getContentSize().height), sacel9SprG5);
        msnBox->setFontSize(editFontSize);
        msnBox->setFontColor(ccBLACK);
        msnBox->setPlaceHolder(input);
        msnBox->setPosition(ccp(240+addWidth,305+addHeight));
        this->addChild(msnBox,zNum);
        msnBox->setDelegate(this);
        
        
        CCScale9Sprite *sacel9SprG6=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG6->setOpacity(1);
        addressBox=CCEditBox::create(CCSizeMake(sacel9SprG6->getContentSize().width*4, sacel9SprG6->getContentSize().height), sacel9SprG6);
        addressBox->setFontSize(editFontSize);
        addressBox->setFontColor(ccBLACK);
        addressBox->setPlaceHolder(input);
        addressBox->setPosition(ccp(270+addWidth,269+addHeight));
        this->addChild(addressBox,zNum);
        addressBox->setDelegate(this);
        
        CCScale9Sprite *sacel9SprG7=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG7->setOpacity(1);
        submitBox=CCEditBox::create(CCSizeMake(sacel9SprG7->getContentSize().width*1.5, sacel9SprG7->getContentSize().height), sacel9SprG7);
        submitBox->setFontSize(editFontSize);
        submitBox->setFontColor(ccBLACK);
       // submitBox->setPlaceHolder("asdhjashdkjansda\nasdjgkjahdkjas");//input);
        submitBox->setPosition(ccp(210+addWidth,140+addHeight));
        this->addChild(submitBox,zNum);
        submitBox->setDelegate(this);
        
        textView = CCUIKit::create();
        CCRect aRect = CCRectMake(295, 480, 500, 100);
        textView->creatWithRect(aRect,this);
        addChild(textView);
        AppDelegate::isTextViewExist = false;
        
        CCScale9Sprite *sacel9SprG8=CCScale9Sprite::create("S49Submit.png");
        sacel9SprG8->setOpacity(1);
        yanzhengBox=CCEditBox::create(CCSizeMake(sacel9SprG8->getContentSize().width*1.5, sacel9SprG8->getContentSize().height), sacel9SprG8);
        yanzhengBox->setFontSize(editFontSize);
        yanzhengBox->setFontColor(ccBLACK);
        yanzhengBox->setPlaceHolder(input);
        yanzhengBox->setPosition(ccp(210+addWidth,110+addHeight));
        this->addChild(yanzhengBox,zNum);
        yanzhengBox->setDelegate(this);
        
        
        
        CCMenuItemFont *aItem = CCMenuItemFont::create("提交留言",this,menu_selector(S411FeedBack::submit));
        aItem->setOpacity(1);
        aItem->setColor(ccBLACK);
        aItem->setScale(1.2);
        aItem->setPosition(ccp(550,165));
        aItem->setContentSize(CCSizeMake(100,100));
        _menu ->addChild(aItem,zNum);
    
        CCLabelTTF * titlelabel = CCLabelTTF::create("我要加盟", s1FontName_macro, 15);
        titlelabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+155));
        titlelabel->setColor(ccWHITE);
        this->addChild(titlelabel,zNum+1000);
        
		bRet = true;
	} while (0);
    
	return bRet;
}
void S411FeedBack::editBoxEditingDidBegin(CCEditBox *editBox)
{
    CCLOG("start edit");
    
}
void S411FeedBack::editBoxEditingDidEnd(CCEditBox *editBox)
{
    CCLOG("end edit");
}
void S411FeedBack::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    CCLOG("textchanged");
    
}
void S411FeedBack::editBoxReturn(CCEditBox *editBox)
{
    CCLOG("editboxreturn");
    
}



void S411FeedBack::feedBack(CCObject * pSender)
{
   /* AppDelegate::S4IsFeedBack = true;
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S411FeedBack::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0,newScene));
	*/
}

void S411FeedBack::back(CCObject * pSender)
{
    CCScene *newScene = CCScene::create();
    newScene->addChild(S41Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f,newScene));
}

void S411FeedBack::submit(CCObject * pSender)
{    
    AppDelegate::loadingLabel = CCLabelTTF::create("提交中", s1FontName_macro, 40);
    AppDelegate::loadingLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    AppDelegate::loadingLabel->setColor(ccRED);
    this->addChild(AppDelegate::loadingLabel,zNum+1000);
    
    string name(nameBox->getText());
    string sex;
    if (isMale)
    {
        sex = "男";
    }
    else
    {
        sex = "女";
    }
    string tel(telBox->getText());
    if (name.size()==0||tel.size()==0)
    {
        AppDelegate::loadingLabel ->setString("请完整填写必填信息");
        this->schedule(schedule_selector(S411FeedBack::time),1.0f,false,0.0);
        return;
    }
    string mobilePhone(mobilePhoneBox->getText());
    string mail(mailBox->getText());
    string msn(msnBox->getText());
    string address(addressBox->getText());
    //textView->setTextViewString("");
    string yanzheng(yanzhengBox->getText());
    string submitStr(submitBox->getText());
    
    string requestSr = "http://www.jrsp.cn/app/iwant.php?name="+name+"&sex="+sex+"&phone="+tel+"&mobile="+mobilePhone+"&email="+mail+"&qq="+msn+"&address="+address+"&message="+submitStr;
    requestSr = PersonalApi::string_replace(requestSr," ","%20");
     requestSr = PersonalApi::string_replace(requestSr,"\n","%0D");
    PostToUrl(requestSr.c_str(),"name","name");
    
    //setButtonEnabel(true);
}
void S411FeedBack::time(float dt)
{
    _menu->setEnabled(true);
    AppDelegate::loadingLabel->setString("");
    nameBox->setText("");
    telBox->setText("");
    mobilePhoneBox->setText("");
    mailBox->setText("");
    msnBox->setText("");
    addressBox->setText("");
    
    yanzhengBox->setText("");
    submitBox->setText("");
}

void S411FeedBack::changeSex(CCObject * pSender)
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
void S411FeedBack::onPostFinished(CCNode *node,void *data)
{
    AppDelegate::loadingLabel ->setString("");
    _menu->setEnabled(true);
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
        this->schedule(schedule_selector(S411FeedBack::time),1.0f,false,0.0);
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
    this->schedule(schedule_selector(S411FeedBack::time),1.0f,false,0.0);
}

