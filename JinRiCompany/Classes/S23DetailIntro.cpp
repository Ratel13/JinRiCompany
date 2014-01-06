//
//  S23DetailIntro.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S23DetailIntro.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()
#define s1FontName_macro "Arial"

#define classPlistName_macro "S23DetailIntro"
#define zNum 100
#define btnTag 100
#include "FDScrollView.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S23DetailIntro::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S23DetailIntro *layer = S23DetailIntro::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S23DetailIntro::initInfo2()
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
//networking downloding
void S23DetailIntro::UpDate()
{

    string requestSr = "http://www.jrsp.cn/app/jproduct.php?a=displayIntro&type2="+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected);
    CCLOG("requestSr == %s",requestSr.c_str());
    ConnetToUrl(requestSr,"s21","");
}

void S23DetailIntro::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        string detailClassName ="S23DetailIntro"+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected);
        string currentClassName(detailClassName.c_str());
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S23DetailIntro::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));

}
void S23DetailIntro::DownLoadFinish()
{
    
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    string detailClassName ="S23DetailIntro"+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected);
    string currentClassName(detailClassName.c_str());
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
    
    Json* root_displayPicture= Json_getItem(root,"displayIntro");
    Json* pic_url=Json_getItem(root_displayPicture,"img1");
   
    char szsamllpicname[512]={0};
    sprintf(szsamllpicname, "S23DetailPage%d.png",AppDelegate::S2LeftSelected);
    DownLoadFile(pic_url->valuestring,szsamllpicname);
    CCLOG("%d",AppDelegate::S2LeftSelected);
    CCLOG("%s",pic_url->valuestring);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
    
}
bool S23DetailIntro::setUpSubClass2()
{
	bool bRet = false;
	do
	{
     

        CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
        m_pScrollView = CCScrollView::create(showSize);//creat(showSize, pLayer);
        
       // if (false == AppDelegate::S23IsBigPic)
        {
            string S22BigImgStr = "S23DetailPage"+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+".png";
            
            string bigStr = PersonalApi::getRealImageName(S22BigImgStr.c_str(), "S241DetailPage.png");
            
            CCSprite * showbigPicture = CCSprite::create(bigStr.c_str());
            
            showbigPicture->setPosition(CCPointZero);
            m_pScrollView->addChild(showbigPicture,zNum);
            
            scrollMaxSizeX = showbigPicture->getContentSize().width;
            scrollMaxSizeY = showbigPicture->getContentSize().height;
            
            
            
            m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"S23DetailPage"));
            CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
            m_pScrollView->setContentOffset(ccp(0,-(showbigPicture->getContentSize().height-showSize.height)));
            m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height));
            m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
            
            m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
            //m_pScrollView->setDelegate(this);
            this->addChild(m_pScrollView);
        }
		bRet = true;
	} while (0);
    
	return bRet;
}

void S23DetailIntro::showBigPic(CCObject* pSender)
{
   
    AppDelegate::S23IsBigPic = true;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S23DetailIntro::create());
    CCDirector::sharedDirector()->replaceScene((CCTransitionSlideInR::create(0.0f, newScene)));
}

void S23DetailIntro::S2back(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
}