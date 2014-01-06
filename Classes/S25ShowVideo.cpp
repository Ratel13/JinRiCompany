//
//  S25ShowVideo.cpp
//  GreTest
//
//  Created by lyy on 13-6-24.
//
//

#include "S25ShowVideo.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S25ShowVideo"
#define zNum 100
#define btnTag 100

CCScene* S25ShowVideo::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S25ShowVideo *layer = S25ShowVideo::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S25ShowVideo::initInfo2()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 5;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S25ShowVideo::UpDate()
{

    string selectedStr = "http://www.jrsp.cn/app/jvideo.php?type="+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected);
    ConnetToUrl(selectedStr,"jseasons","");
    
}

void S25ShowVideo::refreshDownLoadingData(bool isCompleted)
{

    if (isCompleted)
    {
        string detailClassName ="S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"ShowVideo";
        string currentClassName(detailClassName.c_str());
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S25ShowVideo::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));

}

void S25ShowVideo::DownLoadFinish()
{
    
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    string detailClassName ="S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"ShowVideo";
    string currentClassName(detailClassName.c_str());
    string version = currentClassName+"version";
    string needUpDate = currentClassName+"needUpDate";
    string newVersion = currentClassName+"newVersion";
    string time = currentClassName+"time";
    
    Json* root_Version=Json_getItem(root,"version");
    
    if (root_Version)
	{
        string versionStr(root_Version->valuestring);
        
        
        if (CCUserDefault::sharedUserDefault()->getStringForKey(version.c_str()).compare(versionStr) == 0)
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey(needUpDate.c_str(),false);
            
            
            AppDelegate::loadingLabel->setString("");
            //setButtonEnabel(false);
            
            setUpUpDateLabel(CCPointMake(130, 570),CCPointMake(900, 570),CCUserDefault::sharedUserDefault()->getStringForKey(time.c_str()),CCUserDefault::sharedUserDefault()->getBoolForKey(needUpDate.c_str()));
            
            
            return;
        }
        else
        {
            CCUserDefault::sharedUserDefault()->setBoolForKey(needUpDate.c_str(),true);
            CCUserDefault::sharedUserDefault()->setStringForKey(newVersion.c_str(), root_Version->valuestring);
        }
	}
    
    Json* root_time=Json_getItem(root,"time");
    if (root_time)
	{
        CCUserDefault::sharedUserDefault()->setStringForKey(time.c_str(), root_time->valuestring);
	}
    
    setUpUpDateLabel(CCPointMake(130, 570),CCPointMake(900, 570),CCUserDefault::sharedUserDefault()->getStringForKey(time.c_str()),CCUserDefault::sharedUserDefault()->getBoolForKey(needUpDate.c_str()));
   // setButtonEnabel(true);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
	//picture and title
	Json* root_smallpicture=Json_getItem(root,"video");
	if (root_smallpicture && root_smallpicture->type==Json_Array)
	{
		Json* json_child=root_smallpicture->child;
        map<string, string> valueMap;
        showPicMap.clear();
        showBigPicMap.clear();
        int i = 0;//smal image
        int k = 0;
        int j = 0;//big image
		while(json_child)
		{
			Json* child_pic_url=Json_getItem(json_child,"img");
            Json* child_video_url=Json_getItem(json_child,"video_url");
            
            if (i==0) {
                
                //self
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollBigPic%d.png",AppDelegate::S1NaviSelected,j+1);
                        string picNameStr(szsamllpicname);
                        showBigPicMap[PersonalApi::convertIntToString(j+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(j+1)] = valueStr;
                    }
                    j++;
                }
                
            }else if (i==1) {
                
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                        string picNameStr(szsamllpicname);
                        showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    }
                    k++;
                }
                
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                        string picNameStr(szsamllpicname);
                        showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    }
                    k++;
                }
                
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                        string picNameStr(szsamllpicname);
                        showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    }
                    k++;
                }
                
            }else if (i==3) {
                
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                        string picNameStr(szsamllpicname);
                        showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    }
                    k++;
                    
                }
                
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                        string picNameStr(szsamllpicname);
                        showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    }
                    k++;
                    
                }
                
                //self
                {
                    if (child_pic_url)
                    {
                        char szsamllpicname[512]={0};
                        sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                        string picNameStr(szsamllpicname);
                        showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                        DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                        
                        string valueStr = child_video_url->valuestring;
                        valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    }
                    k++;
                }
                
                
            }else{
                if(child_pic_url){
                    char szsamllpicname[512]={0};
                    sprintf(szsamllpicname, "S%d5ScrollPic%d.png",AppDelegate::S1NaviSelected,k+1);
                    string picNameStr(szsamllpicname);
                    showPicMap[PersonalApi::convertIntToString(k+1)] = picNameStr;
                    DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                    
                    string valueStr = child_video_url->valuestring;
                    valueMap[PersonalApi::convertIntToString(k+1)] = valueStr;
                    
                }
                k++;
            }
            
            i++;
			json_child=json_child->next;
		}
        
        string str1 = "S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"5scrollPic";
        string str2 = "S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"5VideoIntro";
        
        PersonalApi::wirteVecToXml(showPicMap,str1);
        PersonalApi::wirteVecToXml(valueMap,str2);
        
	}
    
    checkPicDownLoading();
}
bool S25ShowVideo::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        scrollMaxSizeY = 0;
        
        CCLayer *pLayer = CCLayer::create();
        pLayer->setPosition(CCPointZero);
        
        m_pScrollView = CCScrollView::create();
        m_pScrollView->setPosition(ScriptParser::getPositionFromPlist(plistDic, "scrollView"));
        m_pScrollView->setContainer(pLayer);
        
        CCSize showSize = ScriptParser::getSizeFromPlist(plistDic, "showSize");
        
        m_pScrollView->setViewSize(CCSizeMake(showSize.width, showSize.height-20));
        
        string str1 = "S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"5scrollPic";
        string str2 = "S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"5VideoIntro";
        string str3 = "S"+PersonalApi::convertIntToString(AppDelegate::S1NaviSelected) +"5ScrollBigPic";
        
        showStrUrlMap = PersonalApi::getRealGroupStringMap(plistDic,str2.c_str(),"videoIntro");
        showPicMap = PersonalApi::getRealGroupImageMap(plistDic,str1.c_str(),"scrollPic");
        showBigPicMap = PersonalApi::getRealGroupImageMap(plistDic,str3.c_str(),"scrollBigPic");
        
        int indexNum = 1;
        
        float elementWidth;
        float elementHeight;
        int mapSize = showPicMap.size();
        int mapSizeRemainder = mapSize%4;
        int mapSizeAver;
        
        if (mapSizeRemainder>0) {
            mapSizeAver = mapSize/4+1;
        }else{
            mapSizeAver = mapSize/4;
        }
        
        
        {
            const char *imageName = showPicMap[PersonalApi::convertfloatToString(indexNum)].c_str();
            string str = PersonalApi::getRealImageName(imageName, "S15Small_1.png").c_str();
            CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                   str.c_str(),
                                                                   this,
                                                                   menu_selector(S25ShowVideo::S15DetailCallback));
            
            elementWidth = aItemImage->getContentSize().width+31;
            elementHeight = aItemImage->getContentSize().height+20;
            
            scrollMaxSizeY = elementHeight*mapSizeAver;
            
            
        }
        
        
        for (int i  = 0; i<(int)showPicMap.size()/4+1; i++){
            if (4*(i+1)<=mapSize) {
                for (int j = 0; j<4; j++)
                {
                    const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum)].c_str();
                    
                    string  str=PersonalApi::getRealImageName(imageName,"S15Small_1.png").c_str();
                    CCLOG("aaaaa%s",str.c_str());
                    
                    CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                           str.c_str(),
                                                                           this,
                                                                           menu_selector(S25ShowVideo::S15DetailCallback));
                    aItemImage->setPosition(ccp(3+145+(aItemImage->getContentSize().width+31)*j,scrollMaxSizeY-elementHeight/2-elementHeight*i));//showSize.height-elementHeight*1.5+(aItemImage->getContentSize().height+20)*i)
                    
                    FDMenu * detailMenu = FDMenu::create();
                    detailMenu ->setPosition(CCPointZero);
                    detailMenu->addChild(aItemImage,zNum);
                    pLayer->addChild(detailMenu,zNum);
                    
                    aItemImage->setTag(btnTag+indexNum);
                    if (i==0&&j<2)
                    {
                        aItemImage->setOpacity(1);
                    }
                    indexNum++;
                }
            }else{
                for (int j = 0; j<mapSizeRemainder; j++)
                {
            
                    const char * imageName = showPicMap[PersonalApi::convertIntToString(indexNum)].c_str();
                    
                    string  str=PersonalApi::getRealImageName(imageName,"S15Small_1.png").c_str();
//                    CCLOG("aaaaa%s",str.c_str());
                    
                    CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                           str.c_str(),
                                                                           this,
                                                                           menu_selector(S25ShowVideo::S15DetailCallback));
                    aItemImage->setPosition(ccp(3+145+(aItemImage->getContentSize().width+31)*j,scrollMaxSizeY-elementHeight/2-elementHeight*(i)));//scrollMaxSizeY-elementHeight/2+elementHeight*i)   scrollMaxSizeY-elementHeight/2-elementHeight*(mapSizeAver-i-1)
                    FDMenu * detailMenu = FDMenu::create();
                    detailMenu ->setPosition(CCPointZero);
                    detailMenu->addChild(aItemImage,zNum);
                    pLayer->addChild(detailMenu,zNum);
                    
                    aItemImage->setTag(btnTag+indexNum);
                    
                    indexNum++;
                }
            }
            
            
            if(i==0){
                const char * imageName = "S25ScrollBigPic1.png";//showBigPicMap[PersonalApi::convertIntToString(i+1)].c_str();
                
                string  str=PersonalApi::getRealImageName(imageName,"S15Big_1.png").c_str();
                
                CCMenuItemImage * aItemImage = CCMenuItemImage::create(str.c_str(),
                                                                       str.c_str(),
                                                                       this,
                                                                       menu_selector(S25ShowVideo::S15DetailCallback));
                aItemImage->setAnchorPoint(CCPointZero);
                aItemImage->setPosition(ccp(36,2+scrollMaxSizeY-elementHeight*2+elementHeight*i));
                if (1 == (int)showPicMap.size()/4+1)
                {
                    aItemImage->setPosition(ccp(36,-(aItemImage->getContentSize().height-30)-2+scrollMaxSizeY-elementHeight*2+elementHeight*i));
                }
                
                FDMenu * detailMenu = FDMenu::create();
                detailMenu ->setPosition(CCPointZero);
                detailMenu->addChild(aItemImage,zNum);
                pLayer->addChild(detailMenu,zNum+1);
                
                aItemImage->setTag(btnTag+indexNum-3);
            }
            
        }
        
        
        
        m_pScrollView->setTouchEnabled(true);
        
        pLayer->setContentSize(CCSizeMake(showSize.width, scrollMaxSizeY));
        m_pScrollView->setContentOffset(ccp(0,-(scrollMaxSizeY-showSize.height)));
        m_pScrollView->setDirection(kCCScrollViewDirectionVertical);
        m_pScrollView->setDelegate(this);
        this->addChild(m_pScrollView);
        
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S25ShowVideo::S15DetailCallback(CCObject* pSender)
{
    if (isMenuLock == false)
    {
        //showStrUrlMap = PersonalApi::getRealGroupStringMap(plistDic,"S15VideoIntro","videoIntro");
        
        CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
        AppDelegate::S151DetailSelected = aItem->getTag()-btnTag;
        
        webView_top = (SPWebView *)SPWebView::create();
        webView_top->setTag(1);
        CCRect rect;
        
        if (webView_top->getScreenWidthSize()==1)
        {
            rect= CCRect(origin.x+70/2, origin.y+475/2, visibleSize.width-130/2,visibleSize.height-590/2);
        }
        else
        {
            rect= CCRect(origin.x+70, origin.y+475, visibleSize.width*2-130,visibleSize.height*2-590);
        }
        
        
        const char * picIntr = showStrUrlMap[PersonalApi::convertIntToString(AppDelegate::S151DetailSelected-1)].c_str();
        if (1 == (int)showPicMap.size()/4+1)
        {
            picIntr = showStrUrlMap[PersonalApi::convertIntToString(AppDelegate::S151DetailSelected+2)].c_str();
        }
        webView_top->addWebViewWithCloseButton(picIntr, rect);
        this->addChild(webView_top);
        
        const char * imageName = "S31Back.png";
        backItemImage = CCMenuItemImage::create(imageName,
                                                imageName,
                                                this,
                                                menu_selector(Main::removeVideo));
        
        backItemImage->setPosition(ccp(960,550));
        CCMenu * backMenu = CCMenu::create(NULL);
        backMenu ->setPosition(CCPointZero);
        _menu->addChild(backItemImage,zNum);
        
        
    }
}
void S25ShowVideo::scrollViewDidScroll(CCScrollView* view)
{
    isMenuLock = true;
    this->schedule(schedule_selector(S25ShowVideo::S31Delay),0.5f);
}

void S25ShowVideo::S31Delay(float dt)
{
    isMenuLock = false;
}


