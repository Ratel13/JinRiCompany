//
//  S132Detail.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-29.
//
//

#include "S132Detail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S13News.h"
#include "S21ZiBuLei.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"

#define classPlistName_macro "S132Detail"
#define zNum 100
#define btnTag 100
#define btnTag1000 1000

using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S132Detail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S132Detail *layer = S132Detail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S132Detail::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro+PersonalApi::convertIntToString(AppDelegate::S1NewsSelected);
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 3;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S132Detail::UpDate()
{
    ConnetToUrl("http://www.jrsp.cn/app/jnews.php","jnews","");
}

void S132Detail::refreshDownLoadingData(bool isCompleted)
{
    if (isCompleted)
    {
        string detailClassName ="S132"+PersonalApi::convertIntToString(AppDelegate::S1NewsSelected)+"Detail";
        string currentClassName(detailClassName.c_str());
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S132Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
}

void S132Detail::DownLoadFinish()
{
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    string detailClassName ="S132"+PersonalApi::convertIntToString(AppDelegate::S1NewsSelected)+"Detail";
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
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>End>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    
    //Company News
	Json* root_companynews;
    if (AppDelegate::S1NewsSelected <btnTag1000+1)
    {
        root_companynews=Json_getItem(root,"company news");
    }
    else
    {
        root_companynews=Json_getItem(root,"Industry News");
    }
    
	if (root_companynews && root_companynews->type==Json_Array)
	{
		Json* json_child=root_companynews->child;
      
        int i  = 1;
		while(json_child)
		{
			Json* child_pic_url=Json_getItem(json_child,"pic_url");
            
			if (!child_pic_url)
			{
                return;
            }
            if (AppDelegate::S1NewsSelected <btnTag1000+1)
                {
                if (i == AppDelegate::S1NewsSelected-btnTag)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S133TuWen%d.png",AppDelegate::S1NewsSelected);
                        
                       // string picNameStr(szsamllpicname);
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                    break;
                    }
                }
                else
                {
                if (i == AppDelegate::S1NewsSelected-btnTag1000)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S133TuWen%d.png",AppDelegate::S1NewsSelected);
                        
                        //string picNameStr(szsamllpicname);
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                    break;
                    }
                }
                
            i++;
			json_child=json_child->next;
		}
        
    }
    
        
    checkPicDownLoading();
}

bool S132Detail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        
        
        
       /*
        float titleFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"title");
        const char * titleLabelStr = ScriptParser::getStringFromPlist(plistDic,"title");
        
        CCLabelTTF *titleLabel = CCLabelTTF::create(titleLabelStr, s1FontName_macro, titleFontSize);
        titleLabel->setAnchorPoint(ccp(0.0,1.0));
        titleLabel->setPosition(ScriptParser::getPositionFromPlist(plistDic,"title"));
        titleLabel->setColor(ccBLACK);
        this->addChild(titleLabel,zNum);
        */
        {
            CCSprite * aSprite = CCSprite::create("PBackBtn.png");
            aSprite->setPosition( ScriptParser::getPositionFromPlist(plistDic,"PBackBtn"));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S132Detail::moreMenuCallback));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag);
            _menu ->addChild(aItem,zNum);
        }
        /*
        CCSprite * showbigPicture = CCSprite::create("s133LeftBigImg.png");
        showbigPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"s133LeftBigImg"));
        this->addChild(showbigPicture,zNum);
		
        
        CCTextureCache::sharedTextureCache()->removeAllTextures();
        float detailFontSize1 = ScriptParser::getFontSizeFromPlist(plistDic,"detailStr");
        CCSize detailDimensionsSize1 = ScriptParser::getSizeFromPlist(plistDic,"detailStr1");
        const char * detailLabelStr1 = ScriptParser::getStringFromPlist(plistDic,"detailStr1");
        
        
        CCLabelTTF *detailLabel1 = CCLabelTTF::create(detailLabelStr1, s1FontName_macro, detailFontSize1, detailDimensionsSize1, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        detailLabel1->setAnchorPoint(ccp(0.0,1.0));
        detailLabel1->setPosition(ScriptParser::getPositionFromPlist(plistDic,"detailStr1"));
        detailLabel1->setColor(ccBLACK);
        this->addChild(detailLabel1,zNum);
        
        
        float detailFontSize2 = ScriptParser::getFontSizeFromPlist(plistDic,"detailStr");
        CCSize detailDimensionsSize2 = ScriptParser::getSizeFromPlist(plistDic,"detailStr2");
        const char * detailLabelStr2 = ScriptParser::getStringFromPlist(plistDic,"detailStr2");
        
        
        CCLabelTTF *detailLabel2 = CCLabelTTF::create(detailLabelStr2, s1FontName_macro, detailFontSize2, detailDimensionsSize2, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        detailLabel2->setAnchorPoint(ccp(0.0,1.0));
        detailLabel2->setPosition(ScriptParser::getPositionFromPlist(plistDic,"detailStr2"));
        detailLabel2->setColor(ccBLACK);
        this->addChild(detailLabel2,zNum);
        */
        
        
        //showbigPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S133TuWen"));
        //this->addChild(showbigPicture,zNum);
		
        
    
        
        m_pScrollView = CCScrollView::create();
        
        string imageName = "S133TuWen"+PersonalApi::convertIntToString(AppDelegate::S1NewsSelected)+".png";
        imageName = PersonalApi::getRealImageName(imageName.c_str(),"S321ScrollPic.png");
        
        CCSprite * showbigPicture; 
        if (imageName.compare("S321ScrollPic.png") != 0)
        {
            showbigPicture = CCSprite::create(imageName.c_str());
        }
        else
        {
            showbigPicture = CCSprite::create();
        }
        showbigPicture->setPosition(CCPointZero);
        m_pScrollView->addChild(showbigPicture,zNum);
        
     
        scrollMaxSizeX = showbigPicture->getContentSize().width;
        scrollMaxSizeY = showbigPicture->getContentSize().height;
        
        
        
        m_pScrollView->setPosition(ccp(30,100)); //¡¯?¡°a¡Ü¦¸??1.0¡Þ¨º¡À?¡Ìa¡±¨C¦Ì?¡ê¡§¡Â?¡°?¡ê¡ã
        CCSize showSize = CCSizeMake(showbigPicture->getContentSize().width, 450);
        m_pScrollView->setContentOffset(ccp(0,-(showbigPicture->getContentSize().height-showSize.height)));
        m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height));
        m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
         
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
        
        
        {
            CCSprite * aSprite = CCSprite::create("PPreBtn.png");
            aSprite->setPosition( ScriptParser::getPositionFromPlist(plistDic,"PPreBtn"));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S132Detail::last));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag+1);
            _menu ->addChild(aItem,zNum);
        }
        
        {
            CCSprite * aSprite = CCSprite::create("PNextBtn.png");
            aSprite->setPosition( ScriptParser::getPositionFromPlist(plistDic,"PNextBtn"));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S132Detail::next));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag+1);
            _menu ->addChild(aItem,zNum);
        }
        
        
		bRet = true;
	} while (0);
    
	return bRet;
}
void S132Detail::next(CCObject* pSender)
{
   

    int index = AppDelegate::S1NewsSelected;
    if (AppDelegate::S1NewsSelected <btnTag1000+1)
    {
    
        if (AppDelegate::S1NewsSelected-btnTag<AppDelegate::rightDetailTitleMap1.size())
        {
            AppDelegate::S1NewsSelected++;
        }
    }
    else
    {
        if (AppDelegate::S1NewsSelected-btnTag1000<AppDelegate::rightDetailTitleMap1.size())
        {
            AppDelegate::S1NewsSelected++;
        }
    }
  
    if (index == AppDelegate::S1NewsSelected)
    {
        return;
    }
    CCScene *newScene = CCScene::create();
    newScene->addChild(S132Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));//??a¡Ù¦Ð?¡Ý¡ã
    
}
void S132Detail::last(CCObject* pSender)
{
    
    int index = AppDelegate::S1NewsSelected;
    if (AppDelegate::S1NewsSelected <btnTag1000+1)
    {
        if ((AppDelegate::S1NewsSelected-btnTag)>1)
        {
            AppDelegate::S1NewsSelected--;
        }
    }
    else
    {
        if (AppDelegate::S1NewsSelected-btnTag1000>1)
        {
            AppDelegate::S1NewsSelected--;
        }
    }
    CCLOG("last = %d",AppDelegate::S1NewsSelected);
    if (index == AppDelegate::S1NewsSelected)
    {
        return;
    }
    CCScene *newScene = CCScene::create();
    newScene->addChild(S132Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));//??a¡Ù¦Ð?¡Ý¡ã
    
}
void S132Detail::moreMenuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            newScene->addChild(S13News::create());
            
            break;
        case btnTag+1:
            // newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));     
}
