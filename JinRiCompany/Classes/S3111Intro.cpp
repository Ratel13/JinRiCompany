
//  S3111Intro.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#include "S3111Intro.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S311Detail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"

#define classPlistName_macro "S3111Intro"
#define zNum 100
#define btnTag 100


CCScene* S3111Intro::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S3111Intro *layer = S3111Intro::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S3111Intro::initInfo2()
{
    bool bRet = false;
	do
	{
        string className(classPlistName_macro);
        className = className  + PersonalApi::convertfloatToString(AppDelegate::S31MeiShiSelected)+ PersonalApi::convertfloatToString(AppDelegate::S311DetailSelected);
        AppDelegate::sceneId = className;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 1;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S3111Intro::UpDate()
{

    string selectedStr = "http://www.jrsp.cn/app/jseasons.php?a=detail&menu_id="+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected);
    ConnetToUrl(selectedStr,"jseasons","");
    //ConnetToUrl("http://www.jrsp.cn/app/jseasons.php?a=detail&menu_id=2","jseasons","");
}

void S3111Intro::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        
        string className(classPlistName_macro);
        className = className  + PersonalApi::convertfloatToString(AppDelegate::S31MeiShiSelected)+ PersonalApi::convertfloatToString(AppDelegate::S311DetailSelected);
        string currentClassName(className);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S3111Intro::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
  
}
void S3111Intro::DownLoadFinish()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    string className(classPlistName_macro);
    className = className  + PersonalApi::convertfloatToString(AppDelegate::S31MeiShiSelected)+ PersonalApi::convertfloatToString(AppDelegate::S311DetailSelected);
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

    //picture and title
	Json* root_smallpicture=Json_getItem(root,"items");
	if (root_smallpicture && root_smallpicture->type==Json_Array)
	{
		Json* json_child=root_smallpicture->child;
        int i  = 1;
		while(json_child)
		{
			Json* child_pic_url=Json_getItem(json_child,"img2");
            Json * child_pic2_url=Json_getItem(json_child,"img3");
        
			if (i == AppDelegate::S311DetailSelected)
			{
                
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S3111ScrollPic%d%d.png",AppDelegate::S31MeiShiSelected,AppDelegate::S311DetailSelected);
				DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                char szsamllpicname2[1512]={0};
                sprintf(szsamllpicname2, "S31YaoshanDisplay_%d%d.png",AppDelegate::S31MeiShiSelected,AppDelegate::S311DetailSelected);
                DownLoadFile(child_pic2_url->valuestring,szsamllpicname2);
				

                break;
			}
            i++;
			json_child=json_child->next;
		}
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}

bool S3111Intro::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        CCTextureCache::sharedTextureCache()->removeAllTextures();
        std::map<string, string> titleImage = PersonalApi::readXmlToVec("S31TitleImge");
        string titleName = titleImage[PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)];
        CCSprite * LogoPic ;
        if (titleName.compare("")==0)
        {
            LogoPic = CCSprite::create();
        }
        else
        {
        titleName = PersonalApi::getRealImageName(titleName.c_str(), "S31TitleImg.png");
            if (titleName.compare("S31TitleImg.png")==0)
            {
             LogoPic = CCSprite::create();
            }
            else
            {
             LogoPic = CCSprite::create(titleName.c_str());
            }
        }
        LogoPic->setPosition(ScriptParser::getPositionFromPlist(plistDic,"LogoPic"));
        this->addChild(LogoPic,zNum);
        
        
        string imageName = "S3111ScrollPic"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)+PersonalApi::convertIntToString(AppDelegate::S311DetailSelected)+".png";
        string  str=PersonalApi::getRealImageName(imageName.c_str(),"S311Intro.png").c_str();
        CCSprite * bigPic ;
        if (titleName.compare("S311Intro.png")==0)
        {
            bigPic = CCSprite::create();
        }
        else
        {
            bigPic = CCSprite::create(str.c_str());
        }
      
        bigPic->setPosition(CCPointZero);
        
         
         m_pScrollView = CCScrollView::create();
         
         m_pScrollView->addChild(bigPic,zNum);
         
         scrollMaxSizeX = bigPic->getContentSize().width;
         scrollMaxSizeY = bigPic->getContentSize().height;
         
         
         
        m_pScrollView->setPosition(ccp(80,200));
         CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
         m_pScrollView->setContentOffset(ccp(0,-(bigPic->getContentSize().height-showSize.height)));
         m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height));
         m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY));
          
         m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
         m_pScrollView->setDelegate(this);
         this->addChild(m_pScrollView);
         
        string titleName2 =  "S31YaoshanDisplay_"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected) +PersonalApi::convertIntToString(AppDelegate::S311DetailSelected)+".png";
        
        
        titleName2 = PersonalApi::getRealImageName(titleName2.c_str(), "S31YaoshanDisplay_01.png");
        CCSprite * picPicture ;
        if (titleName.compare("S31YaoshanDisplay_01.png")==0)
        {
            picPicture = CCSprite::create();
        }
        else
        {
            picPicture = CCSprite::create(titleName2.c_str());
        }
        picPicture->setPosition(ccp(750,350));
        this->addChild(picPicture,zNum);
        
        
        const char * backImageName = "S31Back.png";
        CCMenuItemImage * backItemImage = CCMenuItemImage::create(backImageName,
                                                                  backImageName,
                                                                  this,
                                                                  menu_selector(S3111Intro::back));
        
        backItemImage->setPosition(ScriptParser::getPositionFromPlist(plistDic, "back"));
        CCMenu * backMenu = CCMenu::create(NULL);
        backMenu ->setPosition(CCPointZero);
        _menu->addChild(backItemImage,zNum);
        
        
        
        
        {
            CCSprite * aSprite = CCSprite::create("PPreBtn.png");
            aSprite->setPosition(ccp(100,100));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S3111Intro::last));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag+1);
            _menu ->addChild(aItem,zNum);
        }
        
        {
            CCSprite * aSprite = CCSprite::create("PNextBtn.png");
            aSprite->setPosition( ccp(950,100));
            this->addChild(aSprite,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
            CCSprite * sprite2 = CCSprite::create();
            
            CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S3111Intro::next));
            aItem->setPosition(aSprite->getPosition());
            aItem->setContentSize(aSprite->getContentSize());
            aItem->setTag(btnTag+1);
            _menu ->addChild(aItem,zNum);
        }
        
        
     
        bRet = true;
	} while (0);
    
	return bRet;
}

void S3111Intro::S3111IntroCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            //newScene->addChild(S3111Intro::create());
            
            break;
        case btnTag+1:
            //newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));
    
}

void S3111Intro::next(CCObject* pSender)
{
    string str1 = "S31"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)+"scrollPic";
    std::map<string, string> aMap = PersonalApi::readXmlToVec(str1.c_str());
    CCLOG("%ld,%d",aMap.size(),AppDelegate::S311DetailSelected);
    
    if (aMap.size()>AppDelegate::S311DetailSelected+1)
    {
        AppDelegate::S311DetailSelected++;
        
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(S3111Intro::create());
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene)); 
    }
    
    
}
void S3111Intro::last(CCObject* pSender)
{
 
    if (AppDelegate::S311DetailSelected-1>0)
    {
        AppDelegate::S311DetailSelected--;
        CCScene *newScene = CCScene::create();
        
        newScene->addChild(S3111Intro::create());
        
        CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene)); 
    }
}

void S3111Intro::back(CCObject* pSender)
{
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S311Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.0f, newScene)); 
}
