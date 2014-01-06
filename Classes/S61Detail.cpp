//
//  S61Detail.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S61Detail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"

#include "AppDelegate.h"


#include "FDMenu.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S61Detail"
#define zNum 100
#define btnTag 100



CCScene* S61Detail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S61Detail *layer = S61Detail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S61Detail::initInfo2()
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
void S61Detail::UpDate()
{
        
        string titileStr;
        switch (AppDelegate::S6SelectNavi)
        {
            case 1:
                titileStr = "winner";
                break;
            case 2:
                titileStr = "sang";
                break;
            case 3:
                titileStr = "trepang";
                break;
            case 4:
                titileStr = "birdsnest";
                break;
            case 5:
                titileStr = "pilose";
                break;
            case 6:
                titileStr = "dendrobe";
                break;
            case 7:
                titileStr = "pieces";
                break;
            case 8:
                titileStr = "boiling";
                break;
                
            default:
                break;
        }
        string requestSr = "http://www.jrsp.cn/app/jteach.php?a=display&type="+titileStr;
        CCLOG("request == %s",requestSr.c_str());
        
        ConnetToUrl(requestSr,"s21","");
    
}

void S61Detail::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        string className(classPlistName_macro);
        className = className + PersonalApi::convertfloatToString(AppDelegate::S6SelectNavi);
        string currentClassName(className);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S61Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
}
void S61Detail::DownLoadFinish()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    string className(classPlistName_macro);
    className = className + PersonalApi::convertfloatToString(AppDelegate::S6SelectNavi);
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
    sprintf(szsamllpicname, "S6TuWen%d.png",AppDelegate::S6SelectNavi);
    DownLoadFile(root_picUrl->valuestring,szsamllpicname);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}
bool S61Detail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        
            string imageName = "S6TuWen"+PersonalApi::convertIntToString(AppDelegate::S6SelectNavi)+".png";
            imageName = PersonalApi::getRealImageName(imageName.c_str(),"S4TuWen1.png");
        CCSprite * showbigPicture;
     
            showbigPicture = CCSprite::create(imageName.c_str());
       
            showbigPicture->setPosition(CCPointZero);
            
            m_pScrollView = CCScrollView::create();
            m_pScrollView->addChild(showbigPicture,zNum);
            
            scrollMaxSizeX = showbigPicture->getContentSize().width;
            scrollMaxSizeY = showbigPicture->getContentSize().height;
           
            m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView")); 
            CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
            m_pScrollView->setContentOffset(ccp(0,-(showbigPicture->getContentSize().height-showSize.height)));
            m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height));
            m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
            
            m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
            m_pScrollView->setDelegate(this);
            this->addChild(m_pScrollView);
        
      
      
		bRet = true;
	} while (0);
    
	return bRet;
}
void S61Detail::editBoxEditingDidBegin(CCEditBox *editBox)
{
    CCLOG("start edit");
 
}
void S61Detail::editBoxEditingDidEnd(CCEditBox *editBox)
{
    CCLOG("end edit");
}
void S61Detail::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    CCLOG("textchanged");
    
}
void S61Detail::editBoxReturn(CCEditBox *editBox)
{
    CCLOG("editboxreturn");
 
}

void S61Detail::scrollViewDidScroll(CCScrollView* view)
{
    CCLOG("%f,%f",view->getContentOffset().x,view->getContentOffset().y);
    
    isMenuLock = true;
    this->schedule(schedule_selector(S61Detail::S31Delay),1.0f,false,0.0);
}
void S61Detail::S31Delay(float dt)
{
    isMenuLock = false;
}

void S61Detail::submit(CCObject * pSender)
{
    this->schedule(schedule_selector(S61Detail::time_),1.0f,false,0.0);
    AppDelegate::loadingLabel = CCLabelTTF::create("提交中", s1FontName_macro, 40);
    AppDelegate::loadingLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    AppDelegate::loadingLabel->setColor(ccRED);
    this->addChild(AppDelegate::loadingLabel,zNum+1000);
    //setButtonEnabel(true);
}
void S61Detail::time_(float dt)
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