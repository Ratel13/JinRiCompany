#include "MainScene.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S01FirstPage.h"
#include "S11CompanyInfo.h"
#include "S21ZiBuLei.h"
#include "S31MeiShi.h"
#include "S41Detail.h"
#include "S15ShowVideo.h"
#include "S51DingGou.h"
#include "CCUIKit.h"
#include "S61Detail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"
#define classPlistName_macro "Main"
#define zNum 100
#define btnTag 100



void DownLoadFile(const char* url,const char* picname )
{
    AppDelegate::picDidFinishCount++;
    
    CCLOG("AppDelegate::picDidFinishCount = %d",AppDelegate::picDidFinishCount);
	static int i=1;
	
	string filepath= CCFileUtils::sharedFileUtils()->getWritablePath();
	filepath +=picname;
	char sztag[128]={0};
	//sprintf(sztag,"%d",i);
	Main* phttpdownfile=new Main();
	phttpdownfile->ConnetToUrl(url,sztag,filepath);
	phttpdownfile->autorelease();
    //this->ConnetToUrl(url,sztag,filepath);
	i++;
	if (i>1000000)
	{
		i=1;
	}
}

bool Main::init()
{
	bool bRet = false;
	do 
	{
		CCFileUtils::sharedFileUtils()->addSearchPath("ipad");
        
		_menu = NULL;
		timeLabel = NULL;
		updateLabel = NULL;
		enableMenu  = NULL;
		webView_top = NULL;
		backItemImage = NULL;
		bgGrayItemImage = NULL;
		loadingActivity = NULL;
		plistDic = NULL;
		titleLabel = NULL;
		
		m_Url="";
        m_FullPathFileName="";
        m_strtag="";
        m_strUrlContent="";
        loadingLabelFont_macro =20;
        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)));

		_menu = CCMenu::create(NULL);
		_menu->setPosition(CCPointZero);

		this->addChild(_menu, zNum+1);
        
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        CC_BREAK_IF(!initInfo());
        
        CCSprite * NaviBg = CCSprite::create("PNavBar.png");
        NaviBg->setAnchorPoint(ccp(0.0,1.0));
        NaviBg->setPosition(ccp(origin.x,origin.y+visibleSize.height-20));
        this->addChild(NaviBg,zNum);
        
        CCSprite * footBar = CCSprite::create("PFootBar.png");
        footBar->setAnchorPoint(ccp(0.0,0.0));
        footBar->setPosition(ccp(origin.x,origin.y));
        this->addChild(footBar,zNum);
        
        {
            const char * labelStr = ScriptParser::getStringFromPlist(plistDic,"PFootBar");
            float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"PFootBar");
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            CCPoint labelPoint = ScriptParser::getPositionFromPlist(plistDic,"PFootBar");
            pLabel->setPosition(ccp(origin.x+visibleSize.width/2,labelPoint.y-5));
            pLabel->setColor(ccc3(255.0,255.0,255.0));
            this->addChild(pLabel,zNum);
        }
		
        {
            CCMenuItemImage * LogoImage = CCMenuItemImage::create("PLogoOne.png","PLogoOne.png",this,menu_selector(Main::menuCallback));
			LogoImage->setPosition( ScriptParser::getPositionFromPlist(plistDic,"PLogoOne"));
            LogoImage->setTag(btnTag);
			_menu->addChild(LogoImage,zNum);
		}
      
        map<string, string> naviGroupStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"naviTitle");
        float fontSize = ScriptParser::getFontSizeFromPlist(plistDic,"naviTitle");
        CCPoint naviStrPosition = ScriptParser::getPositionFromPlist(plistDic,"naviTitle");
       
        for (int i=0; i<(int)naviGroupStrMap.size(); i++)
        {
            const char * labelStr = naviGroupStrMap[PersonalApi::convertIntToString(i+1)].c_str();
        
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            pLabel->setPosition(ccp(naviStrPosition.x+pLabel->getContentSize().width*1.6*i,naviStrPosition.y));
          
            if (AppDelegate::S1NaviSelected-1 == i)
            {
                 pLabel->setColor(ccc3(199.0,195.0,0.0));
                
            }
            else
            {
               pLabel->setColor(ccc3(255.0,255.0,255.0));
            }
            
            this->addChild(pLabel,zNum);
            
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(Main::menuCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(pLabel->getPosition());
            aItem->setContentSize(pLabel->getContentSize());
            aItem->setTag(btnTag+i+1);
			_menu ->addChild(aItem,zNum);

            
            
            if(i!=naviGroupStrMap.size()-1)
            {
                CCSprite * aSprite = CCSprite::create("PNavStall.png");
                aSprite->setPosition(ccp(pLabel->getPosition().x+pLabel->getContentSize().width/2+10,pLabel->getPosition().y));
                this->addChild(aSprite,zNum);
            }
        }
        
       CCTextureCache::sharedTextureCache()->removeAllTextures(); 

     
        AppDelegate::loadingLabel = CCLabelTTF::create("", s1FontName_macro, loadingLabelFont_macro);
        AppDelegate::loadingLabel->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-100));
        AppDelegate::loadingLabel->setColor(ccRED);
        this->addChild(AppDelegate::loadingLabel,zNum+1000);
      
        refreshItemImage = CCMenuItemImage::create("view-refresh.png",
                                                               "view-refresh.png",
                                                               this,
                                                               menu_selector(Main::PressGoUpData));
        refreshItemImage->setAnchorPoint(CCPointZero);
        refreshItemImage->setPosition(ccp(970, 555));
        _menu->addChild(refreshItemImage,zNum);
        refreshItemImage->setScale(0.1);
         CC_BREAK_IF(! setUpSubClass());
        updateLabel = CCLabelTTF::create("", s1FontName_macro, 15);
        updateLabel->setPosition(ccp(900,570));
        updateLabel->setColor(ccc3(112,16,12));
        this->addChild(updateLabel,zNum+10);
        string sceneId(AppDelegate::sceneId);
        if (CCUserDefault::sharedUserDefault()->getStringForKey(sceneId.c_str()).compare(sceneId) != 0)
        {
            CCUserDefault::sharedUserDefault()->setStringForKey(sceneId.c_str(), sceneId.c_str());
        goUpData();
        }
        else
        {
            UpDate();
        }
        
        
		bRet = true;
	} while (0);

	return bRet;
}

void Main::menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    removeUIKit();
    AppDelegate::isTextViewExist = true;
    CCUIKit::removeTextView(1);
    
    AppDelegate::S2LeftSelected = 1;
    AppDelegate::S2Alpha = 0.0;
    AppDelegate::S2SceneNum = 1;
    AppDelegate::S2SelectedScene = 1;
    AppDelegate::S22Selected = 1;
    AppDelegate::S23IsBigPic =false;
    AppDelegate::S2isInParent = true;
    AppDelegate::S2SelectedPicNum = 1;
    AppDelegate::IsChangeScrollView = false;
    AppDelegate::S3SceneSelect = 1;
    AppDelegate::S4SelectNavi = 1;
    AppDelegate::S21NetWorkLock = 0;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            AppDelegate::S1NaviSelected = 0;
            AppDelegate::S2LeftSelected = 1;
            newScene->addChild(S01FirstPage::create());
            
            break;
        case btnTag+1:
            AppDelegate::S1NaviSelected = 1;
            AppDelegate::S2LeftSelected = 1;
            newScene->addChild(S11CompanyInfo::create());
            
            break;
        case btnTag+2:
            AppDelegate::S1NaviSelected = 2;
            newScene->addChild(S21ZiBuLei::create());
            
            break;
            
        case btnTag+3:
            AppDelegate::S2LeftSelected = 1;
             AppDelegate::S1NaviSelected = 3;
             newScene->addChild(S31MeiShi::create());
            
            break;
            
        case btnTag+4:
            AppDelegate::S2LeftSelected = 1;
            AppDelegate::S1NaviSelected = 4;
            newScene->addChild(S61Detail::create());
            break;
            
        case btnTag+5:
            AppDelegate::S2LeftSelected = 1;
            AppDelegate::S1NaviSelected = 5;
            newScene->addChild(S41Detail::create());
            break;
            
        case btnTag+6:
            AppDelegate::S2LeftSelected = 1;
            AppDelegate::S1NaviSelected = 6;
            newScene->addChild(S51DingGou::create());
       
            break;
            
        default:
            break;
    }
    
    
    
    CCDirector::sharedDirector()->replaceScene(newScene);    
}

void Main::ConnetToUrl(string url,string strtag,string fullpathfilename)
{
	if (url.empty())
		return;
    
	m_Url=url;
	m_FullPathFileName=fullpathfilename;
	m_strtag=strtag;
	if(!m_FullPathFileName.empty())
		remove(m_FullPathFileName.c_str());
    
    CCHttpClient *httpClient = CCHttpClient::getInstance();
    
    CCHttpRequest *request = new CCHttpRequest();
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setUrl(m_Url.c_str());
    
    request->setResponseCallback(this, callfuncND_selector(Main::httpRequestFinish));
    
    request->setTag(m_strtag.c_str());
    
    httpClient->setTimeoutForConnect(30);
    
    httpClient->send(request);
    
    request->release();
    
}

void Main::httpRequestFinish(cocos2d::CCNode *node,void *_data)
{
    CCHttpResponse *response = (CCHttpResponse*)_data;
    
    if(!response->isSucceed())
    {
        printf("error is here %s",response->getErrorBuffer());
        AppDelegate::isNetWork = false;
        AppDelegate::loadingLabel->setString("网络超时了，请检查您的网络！");
        AppDelegate::picDidFinishNum = 0;
        AppDelegate::picDidFinishCount = 0;
        this->schedule(schedule_selector(Main::outOfTime),1.0f);

        return;
    }

    const char* tag = response->getHttpRequest()->getTag();
    if(0 == strcmp(tag, m_strtag.c_str()))
    {
        std::vector<char> *data = response->getResponseData();
        
        int vectorLength = data->size();
        if(vectorLength <= 0)
        {
            printf("ResponseData is null");
            return;
        }
        
        std::string recieveData(data->begin(),data->end());
		if (m_FullPathFileName.empty())
		{
			m_strUrlContent=recieveData;
			this->DownLoadFinish();
        }
		else
		{
			FILE *fp = fopen(m_FullPathFileName.c_str(), "wb+");
			fwrite(recieveData.c_str(), 1,data->size(),fp);
			fclose(fp);
            AppDelegate::picDidFinishNum++;
          
		}
        
    }
}
void Main::checkPicDownLoading()
{
    this->schedule(schedule_selector(Main::checkPicDownLoadingFinished),1.0f);
}
void Main::checkPicDownLoadingFinished(float dt)
{
    CCLOG("AppDelegate::picDidFinishCount = %d,AppDelegate::picDidFinishNum = %d",AppDelegate::picDidFinishCount,AppDelegate::picDidFinishNum);
     
    AppDelegate::isUpDateLock = true;
    string loadingStr = "加载进度"+PersonalApi::convertIntToString((float)AppDelegate::picDidFinishNum/(float)AppDelegate::picDidFinishCount*100)+"%";
    AppDelegate::loadingLabel->setString(loadingStr.c_str());
    if (AppDelegate::picDidFinishNum == AppDelegate::picDidFinishCount)
    {
        AppDelegate::picDidFinishNum = 0;
        AppDelegate::picDidFinishCount = 0;
        this->unschedule(schedule_selector(Main::checkPicDownLoadingFinished));
        goRefreshDownLoadingData(true);
    }
}
void Main::setUpUpDateLabel(cocos2d::CCPoint timeLabelPosition,cocos2d::CCPoint updateLabelPosition,string timeStr,bool isNeedUpDate)
{
    timeLabel = CCLabelTTF::create(timeStr.c_str(), s1FontName_macro, 15);
    timeLabel->setPosition(timeLabelPosition);//ccp(100,570));
    timeLabel->setColor(ccc3(112,16,12));
    this->addChild(timeLabel,zNum+10);
    
    if (isNeedUpDate)
    {
        updateLabel-> setString("有最新的内容请更新");//= CCLabelTTF::create("有最新的内容请更新", s1FontName_macro, 15);
        updateLabel->setPosition(updateLabelPosition);//ccp(900,570));
        //AppDelegate::updateLabel->setColor(ccc3(112,16,12));
        //this->addChild(AppDelegate::updateLabel,zNum+10);
        
        
    }
 
}
void Main::setLoadingActivityEnabel(bool isLoadingActivityEnabel)
{
    if (true== isLoadingActivityEnabel)
    {
        CCSprite * sprite1 = CCSprite::create("Bg.png");
        CCSprite * sprite2 = CCSprite::create("Bg.png");
        bgGrayItemImage = CCMenuItemSprite::create(sprite1,
                                                                 sprite2,
                                                                 this,
                                                                 NULL);
        bgGrayItemImage->setAnchorPoint(CCPointZero);
        bgGrayItemImage->setContentSize(visibleSize);
        bgGrayItemImage->setPosition(ccp(origin.x,origin.y));
        this->addChild(bgGrayItemImage,zNum);

        
 
        AppDelegate::loadingActivity = CCSprite::create("refreshNew.png");
        AppDelegate::loadingActivity->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
        addChild(AppDelegate::loadingActivity,100000);
        CCRepeatForever *repeat = CCRepeatForever::create(CCRotateBy::create(1.0f, 360));
        AppDelegate::loadingActivity->runAction(repeat);
        
        
        //AppDelegate::loadingActivity->setOpacity(255);
    }
    else
    {
        
        if (bgGrayItemImage)
        {
            bgGrayItemImage->setOpacity(1);
            AppDelegate::loadingActivity->setOpacity(1);
        }
    }
}
void Main::outOfTime(float dt)
{
   AppDelegate::loadingLabel->setString("");
    setLoadingActivityEnabel(false);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   _menu->setEnabled(true);
       
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void Main::removeVideo(CCObject * pSender)
{
    refreshItemImage->setOpacity(255);
    updateLabel->setOpacity(255);
    refreshItemImage->setEnabled(true);
    removeUIKit();
  
}

void Main::removeUIKit()
{
    if (backItemImage)
    {
        webView_top->removeUIView(1);
        webView_top = NULL;
        backItemImage->removeFromParentAndCleanup(true);
        backItemImage = NULL;
    }
}

void Main::PostToUrl(string url,string strtag,string strcontent)
{
	if (url.empty())
		return;
    
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setResponseCallback(this, callfuncND_selector(Main::onPostFinished));
    
	request->setRequestData(strcontent.c_str(), strcontent.size());
    
	request->setTag(strtag.c_str());
	CCHttpClient::getInstance()->send(request);
	request->release();
}
void Main::PressGoUpData(CCObject* pSender)
{
	goUpData();
}
void Main::goUpData()
{
    AppDelegate::isNetWork = true;
    AppDelegate::isUpDateLock = false;
    setLoadingActivityEnabel(true);
     removeUIKit();
    CCUIKit::removeTextView(1);
    _menu->setEnabled(false);
    UpDate();
}
void Main::UpDate()
{
    AppDelegate::isNetWork = false;
    AppDelegate::isUpDateLock = true;
    setLoadingActivityEnabel(false);
    _menu->setEnabled(true);
}
void Main::goRefreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    _menu->setEnabled(true);
    refreshDownLoadingData(true);
}
