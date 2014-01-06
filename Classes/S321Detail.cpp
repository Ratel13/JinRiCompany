//
//  S321Detail.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-29.
//
//

#include "S321Detail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S321Detail"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S321Detail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S321Detail *layer = S321Detail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S321Detail::initInfo2()
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
void S321Detail::UpDate()
{

    ConnetToUrl("http://www.jrsp.cn/app/jtips.php","jtips","");
    
}

void S321Detail::refreshDownLoadingData(bool isCompleted)
{

    if (isCompleted)
    {
        string className(classPlistName_macro);
        className = className + PersonalApi::convertfloatToString(AppDelegate::S32XiaoTieShiSelected);
        string currentClassName(className);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S321Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));

}
void S321Detail::DownLoadFinish()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    string className(classPlistName_macro);
    className = className + PersonalApi::convertfloatToString(AppDelegate::S32XiaoTieShiSelected);
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
    
	Json* root_leaderpicture=Json_getItem(root,"articles");
	if (root_leaderpicture && root_leaderpicture->type==Json_Array)
	{
		Json* json_child=root_leaderpicture->child;
        map<string, string> valueMap;
        
        int i  = 0;
		while(json_child)
		{
            
			Json* child_pic_url=Json_getItem(json_child,"img2");
           // CCLOG("AppDelegate::S32XiaoTieShiSelected = %d,i=%d",AppDelegate::S32XiaoTieShiSelected,i);
			if (child_pic_url && i == AppDelegate::S32XiaoTieShiSelected-1)
			{
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S321ScrollPic_%d.png",i+1);
                
                string picNameStr(szsamllpicname);
                DownLoadFile(child_pic_url->valuestring,szsamllpicname); 
			}
			json_child=json_child->next;
            i++;
		}

	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}
bool S321Detail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        string aImageName = "S321ScrollPic_"+PersonalApi::convertIntToString(AppDelegate::S32XiaoTieShiSelected)+".png";
        aImageName = PersonalApi::getRealImageName(aImageName.c_str(),"S321ScrollPic.png");
        CCSprite * showbigPicture = CCSprite::create(aImageName.c_str());
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
        //m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
        
        {
            CCSprite * aSprite = CCSprite::create("PPreBtn.png");
            aSprite->setPosition( ccp(40,75));//ScriptParser::getPositionFromPlist(plistDic,"PPreBtn"));
            aSprite->setOpacity(125.0f);
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S321Detail::last));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag+1);
            _menu ->addChild(aItem,zNum);
        }
        
        {
            CCSprite * aSprite = CCSprite::create("PNextBtn.png");
            aSprite->setPosition( ccp(980,75));//ScriptParser::getPositionFromPlist(plistDic,"PNextBtn"));
            aSprite->setOpacity(125.0f);
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S321Detail::next));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag+1);
            _menu ->addChild(aItem,zNum);
        }
        
        {
            const char * imageName = "S31Back.png";
            CCMenuItemImage * backItemImage = CCMenuItemImage::create(imageName,
                                                                      imageName,
                                                                      this,
                                                                      menu_selector(S321Detail::back));
            
            backItemImage->setPosition(ScriptParser::getPositionFromPlist(plistDic, "back"));
            CCMenu * backMenu = CCMenu::create(NULL);
            backMenu ->setPosition(CCPointZero);
            _menu->addChild(backItemImage,zNum);
        }
        
		bRet = true;
	} while (0);
    
	return bRet;
}
void S321Detail::next(CCObject* pSender)
{
    
    std::map<string, string> aMap = PersonalApi::readXmlToVec("S32TitleIntro");
    if (aMap.size()>AppDelegate::S32XiaoTieShiSelected+1)
    {
        AppDelegate::S32XiaoTieShiSelected++;
        
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(S321Detail::create());
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene)); 
    }
    
    
}
void S321Detail::last(CCObject* pSender)
{
    if (AppDelegate::S32XiaoTieShiSelected-1>0)
    {
        AppDelegate::S32XiaoTieShiSelected--;
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(S321Detail::create());
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene)); 
    }  
}


void S321Detail::back(CCObject* pSender)
{
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S32XiaoTieShi::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.0f, newScene)); 
}

void S321Detail::moreMenuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            newScene->addChild(S321Detail::create());
            
            break;
        case btnTag+1:
            // newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene)); 
    
}