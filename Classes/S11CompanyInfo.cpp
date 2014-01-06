//
//  S11CompanyInfo.cpp
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#include "S11CompanyInfo.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"
#include "FDMenu.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S11CompanyInfo"
#define zNum 100
#define btnTag 100
#define scrollBtnTag 1000
#define scrollTime_macro 6.0f

CCScene* S11CompanyInfo::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S11CompanyInfo *layer = S11CompanyInfo::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S11CompanyInfo::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
       
        
        scrollMaxSizeX = 0;
        selectedScene = 1;
        currentLoopWidth = 0;
        
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S11CompanyInfo::UpDate()
{
    /*
    AppDelegate::loadingLabel = CCLabelTTF::create("", s1FontName_macro, loadingLabelFont_macro);
    AppDelegate::loadingLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    AppDelegate::loadingLabel->setColor(ccRED);
    this->addChild(AppDelegate::loadingLabel,zNum+1000);
    setButtonEnabel(true);*/
    ConnetToUrl("http://www.jrsp.cn/app/jindex.php","jindex","");
    
}

void S11CompanyInfo::refreshDownLoadingData(bool isCompleted)
{
    //AppDelegate::loadingLabel->setString("");
    
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
   
    CCScene *newScene = CCScene::create();
    newScene->addChild(S11CompanyInfo::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0, newScene));//??aбу??иC?бу?бу?
    
    //setButtonEnabel(false);
}
void S11CompanyInfo::DownLoadFinish()
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
    
	Json* root_smallpicture=Json_getItem(root,"pic");
	if (root_smallpicture && root_smallpicture->type==Json_Array)
	{
		Json* json_child=root_smallpicture->child;
        map<string, string> valueMap;
        loopPicNameMap.clear();
        int i  = 0;
		while(json_child)
		{
			Json* child_pic_url=Json_getItem(json_child,"pic_url");
            Json* child_pic_title=Json_getItem(json_child,"pic_title");
            
			if (child_pic_url)
			{
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S11BigPic%d.png",i+1);
                
                string picNameStr(szsamllpicname);
                loopPicNameMap[PersonalApi::convertIntToString(i+1)] = picNameStr;
                
				DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                string valueStr = child_pic_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                i++;
			}
			json_child=json_child->next;
		}

        PersonalApi::wirteVecToXml(loopPicNameMap,"S11BigPic");
        PersonalApi::wirteVecToXml(valueMap,"leftDownTitle");
	}
    Json* root_title=Json_getItem(root,"title");
    if (root_title)
	{
         CCUserDefault::sharedUserDefault()->setStringForKey("S11TitleStr", root_title->valuestring);
	}
    Json* root_text=Json_getItem(root,"text");
	if (root_text && root_text->type==Json_Array)
	{
		Json* json_child=root_text->child;
        map<string, string> valueMap;
        int i =0;
		while(json_child)
		{
                string valueStr = json_child->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                i++;
        
			json_child=json_child->next;
		}
       
        PersonalApi::wirteVecToXml(valueMap,"rightTitle");
	}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
 /////////////////////////////////////////////////////////////////////////////   
}

//networking downloding
bool S11CompanyInfo::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        string  str=PersonalApi::getRealImageName("S11BigPic1.png","S11BigPic.png").c_str();
        showbigPicture = CCSprite::create(str.c_str());
        showbigPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S11BigPic"));
        this->addChild(showbigPicture,zNum);
		
        bigPicIndex = 1;
    
       this->schedule(schedule_selector(S11CompanyInfo::loopScroll), 0.1, 0, 0.0f);
        
        

        CCSprite * rulerSprite = CCSprite::create("S11BigPic.png");
        CCSize showSize = CCSizeMake(showbigPicture->getContentSize().width, rulerSprite->getContentSize().height);
      
        
        CCLayer * pLayer = CCLayer::create();
        pLayer->setPosition(CCPointZero);
        
        loopScrollView = CCScrollView::create();
        loopScrollView->setContainer(pLayer);
        loopScrollView->setAnchorPoint(ccp(0.0,1.0));
        loopScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        loopScrollView->setTouchEnabled(true);
        loopScrollView->setDelegate(this);
        loopScrollView->setPosition(ccp(showbigPicture->getPosition().x-showbigPicture->getContentSize().width/2-1,showbigPicture->getPosition().y-showbigPicture->getContentSize().height/2-115));
        
        loopScrollView->setViewSize(CCSizeMake(showSize.width, showSize.height));
        
        
        showPicMap = PersonalApi::getRealGroupImageMap(plistDic,"S11BigPic","S11BigPic");
        for (int i  = 0; i<(int)showPicMap.size(); i++)
        {
            const char * imageName = showPicMap[PersonalApi::convertIntToString(i+1)].c_str();
            string  str=PersonalApi::getRealImageName(imageName,"S11BigPic.png").c_str();
            CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                   str.c_str(),
                                                                   this,
                                                                   menu_selector(S11CompanyInfo::showBigPic));
            aItemImage->setAnchorPoint(CCPointZero);
            aItemImage->setPosition(ccp(scrollMaxSizeX,0));
            FDMenu * detailMenu = FDMenu::create();
            detailMenu->setPosition(CCPointZero);
            detailMenu->addChild(aItemImage,zNum);
            pLayer->addChild(detailMenu,zNum);
            
            aItemImage->setTag(scrollBtnTag+1+i);
            float smallPicScale = 0.36f;
            aItemImage->setScale(smallPicScale);
            scrollMaxSizeX += aItemImage->getContentSize().width*smallPicScale;
        }
        
  
        pLayer->setContentSize(CCSizeMake(scrollMaxSizeX,showSize.height));
        loopScrollView->setContentOffset(ccp(0,0));
        this->addChild(loopScrollView);
     
        //
        
        naviGroupStrMap = PersonalApi::getRealGroupStringMap(plistDic,"leftDownTitle","leftDownTitle");
     
        
        float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"leftDownTitle");
        CCSize dimensionsSize = ScriptParser::getSizeFromPlist(plistDic,"leftDownTitle");
        float lastLabelHeight;
        float lastLabelPositionY;
        
        int k = 1;
        for (int i=0; i<(int)naviGroupStrMap.size()/2; i++)
        {
            for (int j = 0; j<2; j++)
            {
                const char * labelStr = naviGroupStrMap[PersonalApi::convertIntToString(k)].c_str();
               
                CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize, dimensionsSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
                pLabel->setAnchorPoint(ccp(0.0,1.0));
                pLabel->setPosition(ccp(loopScrollView->getPosition().x+showbigPicture->getContentSize().width/2*j,loopScrollView->getPosition().y-pLabel->getContentSize().height*1.2*i-10));
                pLabel->setColor(ccc3(112.0,16.0,12.0));
                this->addChild(pLabel,zNum);
                
                k++;
            }
        }
        
        
        map<string, string> showStrMap = PersonalApi::getRealGroupStringMap(plistDic,"rightTitle","rightTitle");
        
        
        if (CCUserDefault::sharedUserDefault()->getStringForKey("S11TitleStr").length()==0)
        {
            CCUserDefault::sharedUserDefault()->setStringForKey("S11TitleStr",showStrMap[PersonalApi::convertIntToString(1)].c_str());
        }
        CCSize titleSize = CCSizeMake(400, 100);
        float titleFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"rightFirstTitle");
        CCLabelTTF *titleLabel = CCLabelTTF::create(CCUserDefault::sharedUserDefault()->getStringForKey("S11TitleStr").c_str(), s1FontName_macro, titleFontSize, titleSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        titleLabel->setAnchorPoint(ccp(0.0,0.5));
        CCPoint titleLabelPosition = ScriptParser::getPositionFromPlist(plistDic,"rightTitleTableView");
        titleLabel->setPosition(ccp(titleLabelPosition.x+10,showbigPicture->getPosition().y+showbigPicture->getContentSize().height/2-24));
        titleLabel->setColor(ccc3(112.0,16.0,12.0));
        this->addChild(titleLabel,zNum);
        
        dimensionsSize = ScriptParser::getSizeFromPlist(plistDic,"rightTitleTableView");
        lastLabelHeight = titleLabel->getContentSize().height;
        lastLabelPositionY = titleLabel->getPosition().y;
        
        for (int i  = 1; i<(int)showStrMap.size(); i++)
        {
            CCSprite *pSprite = CCSprite::create("S11triangle.png");
            if (1 == i)
            {
                pSprite->setPosition(ccp(titleLabel->getPosition().x+10,lastLabelPositionY-lastLabelHeight+57));
            }
            else
            {
                pSprite->setPosition(ccp(titleLabel->getPosition().x+10,lastLabelPositionY-lastLabelHeight-20));
            }
            
            this->addChild(pSprite,zNum);
           
         
            string spaceStr = " ";
            string labelNoSpaceStr = showStrMap[PersonalApi::convertIntToString(i)];
            for (int j = 0; j<3; j++)
            {
                labelNoSpaceStr = spaceStr + labelNoSpaceStr;
            }
            
            const char * labelStr = labelNoSpaceStr.c_str();
            float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"rightTitle");
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize, dimensionsSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            pLabel->setAnchorPoint(ccp(0.0,1.0));
            pLabel->setPosition(ccp(pSprite->getPosition().x-5,pSprite->getPosition().y+10));
            pLabel->setColor(ccBLACK);
            this->addChild(pLabel,zNum);
            
            lastLabelHeight = pLabel->getContentSize().height;
            lastLabelPositionY = pLabel->getPosition().y;
            
            
            
        }

        CCMenuItemImage * aItemImage = CCMenuItemImage::create("S11BigPic.png",
                                                               "S11BigPic.png",
                                                               this,
                                                               menu_selector(S11CompanyInfo::bugFix));
        aItemImage->setAnchorPoint(CCPointZero);
        aItemImage->setPosition(ccp(560,100));
        FDMenu * detailMenu = FDMenu::create();
        detailMenu->setPosition(CCPointZero);
        detailMenu->addChild(aItemImage,zNum);
        this->addChild(detailMenu,zNum);
        aItemImage->setOpacity(1.0f);
		bRet = true;
	} while (0);
    
	return bRet;
}
void S11CompanyInfo::bugFix(CCObject* pSender)
{
}
void S11CompanyInfo::scrollViewDidScroll(CCScrollView* view)
{
    isMenuLock = true;
    this->schedule(schedule_selector(S11CompanyInfo::S31Delay),0.5f);
}
void S11CompanyInfo::S31Delay(float dt)
{
    isMenuLock = false;
}
void S11CompanyInfo::showBigPic(CCObject* pSender)
{
    if (isMenuLock)
        return;
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    int picIndex = aItem->getTag()-scrollBtnTag;
    
    bigPicIndex = picIndex;
    
    string bigPicStr = "S11BigPic"+PersonalApi::convertIntToString(picIndex)+".png";
    
    string realPicName = PersonalApi::getRealImageName(bigPicStr.c_str(), "S11BigPic.png");
    showbigPicture ->setTexture(CCTextureCache::sharedTextureCache()->addImage(realPicName.c_str()));

   

}
void S11CompanyInfo::companyMenuCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            newScene->addChild(S11CompanyInfo::create());
            
            break;
        case btnTag+1:
            //newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0, newScene));//??aбу??иC?бу?бу?
}

void S11CompanyInfo::loopScroll(float dt)
{
    /*currentLoopWidth -= (scrollMaxSizeX/2)/(60*3);
    loopScrollView->setContentOffset(ccp(currentLoopWidth,0),false);
    if (currentLoopWidth == -(scrollMaxSizeX/2))
    {
        currentLoopWidth = 0;
        loopScrollView->setContentOffset(ccp(0,0),false);
    }
     */
    this->schedule(schedule_selector(S11CompanyInfo::loopScroll1), scrollTime_macro-1.0f, 0, 0.0f);//(S11CompanyInfo::loopScroll1),2.0);
    
    
}
void S11CompanyInfo::loopScroll1(float dt)
{
    CCFadeOut* fadeOut=CCFadeOut::create(0.5f);
    
    showbigPicture->runAction(fadeOut);
    this->schedule(schedule_selector(S11CompanyInfo::loopScroll2), 0.5f, 0, 0.0f);
}
void S11CompanyInfo::loopScroll2(float dt)
{
    bigPicIndex++;
    
    if (bigPicIndex == showPicMap.size())
    {
        bigPicIndex = 1;
    }
    string bigPicStr = "S11BigPic"+PersonalApi::convertIntToString(bigPicIndex)+".png";
    string realPicName = PersonalApi::getRealImageName(bigPicStr.c_str(), "S11BigPic.png");
    showbigPicture ->setTexture(CCTextureCache::sharedTextureCache()->addImage(realPicName.c_str()));
    CCFadeIn* fadeIn=CCFadeIn::create(0.5f);
    showbigPicture->runAction(fadeIn);
    this->schedule(schedule_selector(S11CompanyInfo::loopScroll), scrollTime_macro, 0, 0.0f);
}



