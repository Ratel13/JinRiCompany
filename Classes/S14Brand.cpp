//
//  S14Brand.cpp
//  GreTest
//
//  Created by lyy on 13-6-24.
//
//

#include "S14Brand.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S14Brand"
#define zNum 100
#define btnTag 100

CCScene* S14Brand::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S14Brand *layer = S14Brand::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S14Brand::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 4;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S14Brand::UpDate()
{

    ConnetToUrl("http://www.jrsp.cn/app/jbrand.php","jbrand","");
    
}

void S14Brand::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S14Brand::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
}

void S14Brand::DownLoadFinish()
{
    
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    string currentClassName(classPlistName_macro);
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
    
    
    
	Json* root_smallpicture=Json_getItem(root,"brand");
    
    Json* child_pic_url=Json_getItem(root_smallpicture,"pic_url");
    
    if (child_pic_url)
    {
        //test
        DownLoadFile(child_pic_url->valuestring,"s14tuwen.png");
        
//        const char * imageName = "http://www.jrsp.cn/app/a/../images/showbigPicture.png";
//        DownLoadFile(imageName, "s14tuwen.png");
    }
    
    checkPicDownLoading();
}
bool S14Brand::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        string  str=PersonalApi::getRealImageName("s14tuwen.png","s14tuwen.png").c_str();
        tuwen_sprite = CCSprite::create(str.c_str());
        tuwen_sprite->setPosition( ScriptParser::getPositionFromPlist(plistDic,"s14tuwen"));
        this->addChild(tuwen_sprite,zNum);
        
		bRet = true;
	} while (0);
    
	return bRet;
}

