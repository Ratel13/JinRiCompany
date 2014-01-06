//
//  S31MeiShi.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-26.
//
//

#include "S31MeiShi.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S311Detail.h"
#include "FDMenu.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S31MeiShi"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S31MeiShi::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S31MeiShi *layer = S31MeiShi::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S31MeiShi::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 1;
        
        isMenuLock = false;
        
        bRet = true;
	} while (0);
    
	return bRet;
}


//networking downloding
void S31MeiShi::UpDate()
{
 
    ConnetToUrl("http://www.jrsp.cn/app/jseasons.php","jseasons","");
}

void S31MeiShi::refreshDownLoadingData(bool isCompleted)
{

    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S31MeiShi::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
   
}
void S31MeiShi::DownLoadFinish()
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    
 
    //wordPic
	Json* root_bigpicture=Json_getItem(root,"pic");
	if (root_bigpicture)
	{
		DownLoadFile(root_bigpicture->valuestring,"S3WordPic.png");
	}
    
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
            Json* child_title_pic_url=Json_getItem(json_child,"img2");
            Json* child_pic_title=Json_getItem(json_child,"title");
            
			if (child_pic_url)
			{
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S31ScrollPic%d.png",i+1);
                string picNameStr(szsamllpicname);
                loopPicNameMap[PersonalApi::convertIntToString(i+1)] = picNameStr;
				DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                char szsamllpicname2[512]={0};
                sprintf(szsamllpicname2, "S31TitleImge%d.png",i+1);
                string picNameStr2(szsamllpicname2);
                titlePicNameMap[PersonalApi::convertIntToString(i+1)] = picNameStr2;
				DownLoadFile(child_title_pic_url->valuestring,szsamllpicname2);
                
                
                
                string valueStr = child_pic_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                i++;
              //CCLOG("%d==%s",i,valueStr.c_str());
			}
			json_child=json_child->next;
		}
     
            // π”√ * ∑√Œ µ¸¥˙∆˜À˘÷∏œÚµƒ‘™Àÿ
         PersonalApi::wirteVecToXml(loopPicNameMap,"S31ScrollPic");
        PersonalApi::wirteVecToXml(titlePicNameMap,"S31TitleImge");
        PersonalApi::wirteVecToXml(valueMap,"S31picIntro");
     
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}

bool S31MeiShi::setUpSubClass2()
{
	bool bRet = false;
	do
	{

        string  str=PersonalApi::getRealImageName("S3WordPic.png","S3WordPic.png").c_str();
        CCSprite * wordPic = CCSprite::create(str.c_str());
        wordPic->setAnchorPoint(CCPointZero);
     
       
        CCLayer * pLayer = CCLayer::create();
        pLayer->setPosition(CCPointZero);
        pLayer->addChild(wordPic);
        
        m_pScrollView = CCScrollView::create();
        
        m_pScrollView->addChild(pLayer,zNum);
        
        scrollMaxSizeX = wordPic->getContentSize().width;
        scrollMaxSizeY = wordPic->getContentSize().height;
        
        
       
      showStrMap = PersonalApi::getRealGroupStringMap(plistDic,"S31picIntro","picIntro");
      showPicMap = PersonalApi::getRealGroupImageMap(plistDic,"S31ScrollPic","scrollPic");
  
        float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"picIntro");
        
        int rows = (int)showPicMap.size()/3;
        
        // 根据行数设置wordPic的位置
        wordPic->setPosition(ccpAdd(CCPointZero,ccp(0,300 * rows)));
        int indexNum = 1;
        
        for (int i  = 0; i < rows; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum)].c_str();
                
                string  str=PersonalApi::getRealImageName(imageName,"S31Product_01.png").c_str();
                
                CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                       str.c_str(),
                                                                       this,
                                                                       menu_selector(S31MeiShi::S31MeiShiCallback));
                
                aItemImage->setAnchorPoint(CCPointZero);
                aItemImage->setPosition(ccp((aItemImage->getContentSize().width+110)*j,wordPic->getPosition().y-wordPic->getContentSize().height/2-60-(aItemImage->getContentSize().height+70)*i));
                aItemImage->setTag(btnTag+indexNum);
                
                
                FDMenu * aMenu = FDMenu::create();
                aMenu->setAnchorPoint(CCPointZero);
                aMenu->setPosition(CCPointZero);
                aMenu->addChild(aItemImage,zNum);
                pLayer->addChild(aMenu,zNum);
                
                const char * picIntr = showStrMap[PersonalApi::convertIntToString(indexNum)].c_str();
                CCLabelTTF *titleEnLabel = CCLabelTTF::create(picIntr, s1FontName_macro, titleEnFontSize);
                
                titleEnLabel->setAnchorPoint(CCPointZero);
                titleEnLabel->setPosition(ccp(aItemImage->getPosition().x+(aItemImage->getContentSize().width-titleEnLabel->getContentSize().width)/2,aItemImage->getPosition().y-50));
                titleEnLabel->setColor(ccc3(112,16,12));
                pLayer->addChild(titleEnLabel,zNum);
                
                indexNum++;
            }
            // 累计偏移量
            scrollMaxSizeY += 200;
        }
        
        
		//这一步是1.0版本没有的，重要！
        m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollView"));
		CCSize showSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
        
        // 根据行数设置初始状态事偏移的位置
        m_pScrollView->setContentOffset(ccp(0,35+(-200 * rows)));
        m_pScrollView->setViewSize(CCSizeMake(scrollMaxSizeX, showSize.height-15));//大小要设置得比图片的小
        
        m_pScrollView->setContentSize(CCSizeMake(scrollMaxSizeX, scrollMaxSizeY+200));
        
        // 设置滚动方向，
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S31MeiShi::S31MeiShiCallback(CCObject* pSender)
{
    if (isMenuLock == false)
    {
        CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
        AppDelegate::S31MeiShiSelected = aItem->getTag()-btnTag;
        CCScene *newScene = CCScene::create();
        newScene->addChild(S311Detail::create());
        CCDirector::sharedDirector()->replaceScene(newScene);//动画过场
    }
}
void S31MeiShi::scrollViewDidScroll(CCScrollView* view)
{
    isMenuLock = true;
    this->schedule(schedule_selector(S31MeiShi::S31Delay),0.5f);
}

void S31MeiShi::S31Delay(float dt)
{
    isMenuLock = false;
}


