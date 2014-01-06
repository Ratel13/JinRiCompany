//
//  S311Detail.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#include "S311Detail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S3111Intro.h"
#include "S31MeiShi.h"
#include "FDMenu.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"

#define classPlistName_macro "S311Detail"
#define zNum 100
#define btnTag 100


CCScene* S311Detail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S311Detail *layer = S311Detail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S311Detail::initInfo2()
{
    bool bRet = false;
	do
	{
        string className(classPlistName_macro);
        className = className + PersonalApi::convertfloatToString(AppDelegate::S31MeiShiSelected);
        AppDelegate::sceneId = className;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());

        isMenuLock = false;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S311Detail::UpDate()
{

    string selectedStr = "http://www.jrsp.cn/app/jseasons.php?a=detail&menu_id="+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected);
    CCLOG("%d",AppDelegate::S31MeiShiSelected);
    ConnetToUrl(selectedStr,"jseasons","");
}

void S311Detail::refreshDownLoadingData(bool isCompleted)
{

    if (isCompleted)
    {
        string className(classPlistName_macro);
        className = className + PersonalApi::convertfloatToString(AppDelegate::S31MeiShiSelected);
 
        string currentClassName(className);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S311Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene)); 
    
}
void S311Detail::DownLoadFinish()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    string className(classPlistName_macro);
    className = className + PersonalApi::convertfloatToString(AppDelegate::S31MeiShiSelected);
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
            
            AppDelegate::loadingLabel->setString("");//removeFromParentAndCleanup(false);
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
    
    
    //wordPic
	/*
     Json* root_bigpicture=Json_getItem(root,"pic");
	if (root_bigpicture)
	{
		DownLoadFile(root_bigpicture->valuestring,"S311WordPic.png");
	}
    */
    //picture and title
	Json* root_smallpicture=Json_getItem(root,"items");
	if (root_smallpicture && root_smallpicture->type==Json_Array)
	{
		Json* json_child=root_smallpicture->child;
        map<string, string> valueMap;
        loopPicNameMap.clear();
        int i  = 0;
		while(json_child)
		{
			Json* child_pic_url=Json_getItem(json_child,"img1");
            Json* child_pic_title=Json_getItem(json_child,"title");
            
			if (child_pic_url)
			{
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S31%dScrollPic%d.png",AppDelegate::S31MeiShiSelected,i+1);
                string picNameStr(szsamllpicname);
                loopPicNameMap[PersonalApi::convertIntToString(i+1)] = picNameStr;
				DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                string valueStr = child_pic_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                i++;
                
			}
			json_child=json_child->next;
		}
        
        string str1 = "S31"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)+"scrollPic";
        string str2 = "S31"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)+"picIntro";
        PersonalApi::wirteVecToXml(loopPicNameMap,str1);
        PersonalApi::wirteVecToXml(valueMap,str2);
        
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}


//-----jeff yan modify start
bool S311Detail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        std::map<string, string> titleImage = PersonalApi::readXmlToVec("S31TitleImge");
        string titleName = titleImage[PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)];
        if (titleName.compare("")==0)
        {
            titleName = "S31TitleImg.png";
        }
        else
        {
        titleName = PersonalApi::getRealImageName(titleName.c_str(), "S31TitleImg.png");
        }
        
        CCSprite * wordPic = CCSprite::create(titleName.c_str());
        wordPic->setPosition(ScriptParser::getPositionFromPlist(plistDic,"wordPic"));
        this->addChild(wordPic,zNum);
  
        scrollMaxSizeY = 0;
        
        
        CCLayer * pLayer = CCLayer::create();
        pLayer->setPosition(CCPointZero);
        
        m_pScrollView = CCScrollView::create();
        m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView")); 
        m_pScrollView->setContainer(pLayer);
        
        
        CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
        
        m_pScrollView->setViewSize(CCSizeMake(showSize.width, showSize.height-20));
    

        string str1 = "S31"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)+"scrollPic";
        string str2 = "S31"+PersonalApi::convertIntToString(AppDelegate::S31MeiShiSelected)+"picIntro";
        showStrMap = PersonalApi::getRealGroupStringMap(plistDic,str2.c_str(),"picIntro");
        showPicMap = PersonalApi::getRealGroupImageMap(plistDic,str1.c_str(),"scrollPic");
        float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
        int indexNum = 1;
    
        float elementHeight;
        int row = showPicMap.size()/4+1;
        {
            const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum)].c_str();
            string  str=PersonalApi::getRealImageName(imageName,"S31Yaoshan_01.png").c_str();
            CCSprite * scrollPicSprite = CCSprite::create(str.c_str());
            
  
            elementHeight = scrollPicSprite->getContentSize().height+50;
            scrollMaxSizeY = elementHeight*row;
        }
        
        
        for (int i  = 0; i<(int)showPicMap.size()/4; i++)//
        {
            for (int j = 0; j<4; j++)
            {
                if (indexNum==showPicMap.size())
                {
                    break;
                }
                
                const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum)].c_str();
                string  str=PersonalApi::getRealImageName(imageName,"S31Yaoshan_01.png").c_str();
                CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                       str.c_str(),
                                                                       this,
                                                                       menu_selector(S311Detail::S311DetailCallback));
                
                aItemImage->setPosition(ccp(148+(aItemImage->getContentSize().width+8)*j,scrollMaxSizeY-aItemImage->getContentSize().height-130-(aItemImage->getContentSize().height+50)*i));
                aItemImage->setTag(btnTag+indexNum);
                FDMenu * detailMenu = FDMenu::create();
                detailMenu ->setPosition(CCPointZero);
                detailMenu->addChild(aItemImage,zNum);
                pLayer->addChild(detailMenu,zNum);
                
                
                
                const char * picIntr = showStrMap[PersonalApi::convertIntToString(indexNum)].c_str();
                CCLabelTTF *titleEnLabel = CCLabelTTF::create(picIntr, s1FontName_macro, titleEnFontSize);
                titleEnLabel->setPosition(ccp(aItemImage->getPosition().x,aItemImage->getPosition().y-105));
                titleEnLabel->setColor(ccc3(112,16,12));
                pLayer->addChild(titleEnLabel,zNum);
                
          
                indexNum++;
            }
        }

        m_pScrollView->setTouchEnabled(true);
       
        pLayer->setContentSize(CCSizeMake(showSize.width, scrollMaxSizeY-200));
        m_pScrollView->setContentOffset(ccp(0,-(scrollMaxSizeY-showSize.height)+200));
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
     
        
        const char * imageName = "S31Back.png";
        CCMenuItemImage * backItemImage = CCMenuItemImage::create(imageName,
                                                imageName,
                                                this,
                                                menu_selector(S311Detail::back));
        
        backItemImage->setPosition(ScriptParser::getPositionFromPlist(plistDic, "back"));
        backItemImage->setPosition(ccp(backItemImage->getPosition().x+5,backItemImage->getPosition().y));
        CCMenu * backMenu = CCMenu::create(NULL);
        backMenu ->setPosition(CCPointZero);
        _menu->addChild(backItemImage,zNum);
        
        
        
		bRet = true;
	} while (0);
    
	return bRet;
}

//-----jeff yan modify end

void S311Detail::S311DetailCallback(CCObject* pSender)
{
    if (isMenuLock == false)
    {
        CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
     
        AppDelegate::S311DetailSelected = aItem->getTag()-btnTag;
  
        CCScene *newScene = CCScene::create();
        newScene->addChild(S3111Intro::create());
        CCDirector::sharedDirector()->replaceScene(newScene);
    }
}
void S311Detail::scrollViewDidScroll(CCScrollView* view)
{
    isMenuLock = true;
    this->schedule(schedule_selector(S311Detail::S31Delay),0.5f,false,0.0);
}

void S311Detail::S31Delay(float dt)
{
    isMenuLock = false;
}

void S311Detail::back(CCObject* pSender)
{
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S31MeiShi::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.0f, newScene));
}

