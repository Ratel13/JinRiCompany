//
//  S41Detail.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S41Detail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"

#include "AppDelegate.h"

#include "S411FeedBack.h"
#include "FDMenu.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"

#define classPlistName_macro "S41Detail"
#define zNum 100
#define btnTag 100



CCScene* S41Detail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S41Detail *layer = S41Detail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S41Detail::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 1;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S41Detail::UpDate()
{
    if (8 != AppDelegate::S4SelectNavi)
    {
        
        string titileStr;
        switch (AppDelegate::S4SelectNavi)
        {
            case 1:
                titileStr = "forward";
                break;
            case 2:
                titileStr = "store";
                break;
            case 3:
                titileStr = "league";
                break;
            case 4:
                titileStr = "policy";
                break;
            case 5:
                titileStr = "support";
                break;
            case 6:
                titileStr = "flow";
                break;
            case 7:
                titileStr = "investment";
                break;
            case 8:
                titileStr = "iwant";
                break;
                
            default:
                break;
        }
        string requestSr = "http://www.jrsp.cn/app/jcooperation.php?a=display&type="+titileStr;
        CCLOG("request == %s",requestSr.c_str());
        
        ConnetToUrl(requestSr,"s21","");
    }
}

void S41Detail::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        string className(classPlistName_macro);
        className = className + PersonalApi::convertfloatToString(AppDelegate::S4SelectNavi);
        string currentClassName(className);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S41Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
}
void S41Detail::DownLoadFinish()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    string className(classPlistName_macro);
    className = className + PersonalApi::convertfloatToString(AppDelegate::S4SelectNavi);
    string currentClassName(className);
    string version = currentClassName+"version";
    string needUpDate = currentClassName+"needUpDate";
    string newVersion = currentClassName+"newVersion";
    string time = currentClassName+"time";
    
    Json* root_Version=Json_getItem(root,"version");
    
    if (!root_Version)
	{
        return;
    }
        string versionStr(root_Version->valuestring);
        
        
        if (CCUserDefault::sharedUserDefault()->getStringForKey(version.c_str()).compare(versionStr) == 0 && AppDelegate::isUpDateLock)
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey(needUpDate.c_str(),false);
            
            AppDelegate::loadingLabel->setString("");
            _menu->setEnabled(true);
            
            setUpUpDateLabel(CCPointMake(130, 570),CCPointMake(900, 570),CCUserDefault::sharedUserDefault()->getStringForKey(time.c_str()),CCUserDefault::sharedUserDefault()->getBoolForKey(needUpDate.c_str()));
            
            
            return;
        }
            CCUserDefault::sharedUserDefault()->setBoolForKey(needUpDate.c_str(),true);
        
        if (AppDelegate::isUpDateLock)
        {
            setUpUpDateLabel(CCPointMake(130, 570),CCPointMake(900, 570),CCUserDefault::sharedUserDefault()->getStringForKey(time.c_str()),CCUserDefault::sharedUserDefault()->getBoolForKey(needUpDate.c_str()));
            return;
	}
        CCUserDefault::sharedUserDefault()->setStringForKey(newVersion.c_str(), root_Version->valuestring);
    
    Json* root_time=Json_getItem(root,"time");
    if (root_time)
	{
        CCUserDefault::sharedUserDefault()->setStringForKey(time.c_str(), root_time->valuestring);
	}
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  
	Json* root_picUrl=Json_getItem(root,"pic_url");
	
    char szsamllpicname[512]={0};
    sprintf(szsamllpicname, "S4TuWen%d.png",AppDelegate::S4SelectNavi);
    DownLoadFile(root_picUrl->valuestring,szsamllpicname);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}
bool S41Detail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        
            string imageName = "S4TuWen"+PersonalApi::convertIntToString(AppDelegate::S4SelectNavi)+".png";
            imageName = PersonalApi::getRealImageName(imageName.c_str(),"S4TuWen1.png");
        CCSprite * showbigPicture;
        if (8 != AppDelegate::S4SelectNavi)
        {
            showbigPicture = CCSprite::create(imageName.c_str());
        }
        else
        {
            showbigPicture = CCSprite::create("S4TuWen8.png");
        }
            showbigPicture->setPosition(CCPointZero);
            
            m_pScrollView = CCScrollView::create();
            m_pScrollView->addChild(showbigPicture,zNum);
            
            scrollMaxSizeX = showbigPicture->getContentSize().width;
            scrollMaxSizeY = showbigPicture->getContentSize().height;
           
            m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView")); 
        if (8 == AppDelegate::S4SelectNavi)
        {
            m_pScrollView->setPosition(ccp(m_pScrollView->getPosition().x+30,m_pScrollView->getPosition().y));
        }
            CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
            m_pScrollView->setContentOffset(ccp(0,-(showbigPicture->getContentSize().height-showSize.height)));
            m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height)); 
            m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
             
            m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
            m_pScrollView->setDelegate(this);
            this->addChild(m_pScrollView);
        
        if (8 == AppDelegate::S4SelectNavi)
        {
            
            feedBackSp = CCMenuItemImage::create("S41FeedBack.png", "S41FeedBack.png",this,menu_selector(S41Detail::feedBack));
            feedBackSp->setPosition(ccp(m_pScrollView->getPosition().x+365,240));
            FDMenu * detailMenu = FDMenu::create();
            detailMenu ->setPosition(CCPointZero);
            detailMenu->addChild(feedBackSp,zNum);
            m_pScrollView->addChild(detailMenu, zNum, 10);
            feedBackSp->setOpacity(0.1);
            
            CCLabelTTF * titlelabel = CCLabelTTF::create("我要加盟", s1FontName_macro, 15);
            titlelabel->setPosition(ccp(m_pScrollView->getPosition().x+350,490));
            titlelabel->setColor(ccWHITE);
            m_pScrollView->addChild(titlelabel,zNum+1000);
            refreshItemImage->setOpacity(0);
            refreshItemImage->setEnabled(false);
        }
      
		bRet = true;
	} while (0);
    
	return bRet;
}
void S41Detail::editBoxEditingDidBegin(CCEditBox *editBox)
{
    CCLOG("start edit");
 
}
void S41Detail::editBoxEditingDidEnd(CCEditBox *editBox)
{
    CCLOG("end edit");
}
void S41Detail::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    CCLOG("textchanged");
    
}
void S41Detail::editBoxReturn(CCEditBox *editBox)
{
    CCLOG("editboxreturn");
 
}

void S41Detail::scrollViewDidScroll(CCScrollView* view)
{
    CCLOG("%f,%f",view->getContentOffset().x,view->getContentOffset().y);
    
    isMenuLock = true;
    this->schedule(schedule_selector(S41Detail::S31Delay),1.0f,false,0.0);
}
void S41Detail::S31Delay(float dt)
{
    isMenuLock = false;
}
void S41Detail::feedBack(CCObject * pSender)
{
    if (isMenuLock == false)
    {
 
    CCScene *newScene = CCScene::create();
    newScene->addChild(S411FeedBack::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f,newScene));
    }
}
void S41Detail::submit(CCObject * pSender)
{
    this->schedule(schedule_selector(S41Detail::time),1.0f,false,0.0);
    AppDelegate::loadingLabel = CCLabelTTF::create("提交中", s1FontName_macro, 40);
    AppDelegate::loadingLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    AppDelegate::loadingLabel->setColor(ccRED);
    this->addChild(AppDelegate::loadingLabel,zNum+1000);
    //setButtonEnabel(true);
}
void S41Detail::time(float dt)
{
    AppDelegate::loadingLabel->setString("");//removeFromParentAndCleanup(false);// = CCLabelTTF::create("提交中", s1FontName_macro, 40);
    //setButtonEnabel(false);
    
    nameBox->setText("");
    telBox->setText("");
    mobilePhoneBox->setText("");
    mailBox->setText("");
    msnBox->setText("");
    addressBox->setText("");
    messageBox->setText("");
    yanzhengBox->setText("");
     
}
