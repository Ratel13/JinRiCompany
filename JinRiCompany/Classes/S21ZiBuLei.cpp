//
//  S21ZiBuLei.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-24.
//
//

#include "S21ZiBuLei.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S22PicDetail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S21ZiBuLei"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;

CCScene* S21ZiBuLei::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S21ZiBuLei *layer = S21ZiBuLei::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S21ZiBuLei::initInfo2()
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
void S21ZiBuLei::UpDate()
{
    string detailClassName ="http://www.jrsp.cn/app/jproduct.php?a=show&type1="+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+"&type2="+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected);
    ConnetToUrl(detailClassName,"","");//"http://www.jrsp.cn/app/jproduct.php?a=show&type1=1&type2=1&type3=1","","");
    
}

void S21ZiBuLei::refreshDownLoadingData(bool isCompleted)
{
 
    if (isCompleted)
    {
        string detailClassName ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"ZiBuLei";
        string currentClassName(detailClassName.c_str());
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S21ZiBuLei::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
}
void S21ZiBuLei::DownLoadFinish()
{
    
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
     string detailClassName ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"ZiBuLei";
    
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
    
    Json* root_displayPicture=Json_getItem(root,"product");
    
    if (root_displayPicture && root_displayPicture->type==Json_Array)
    {
        Json* json_child=root_displayPicture->child;
        map<string, string> titleMap;
        map<string, string> weightMap;
        int index = 0;
        while (json_child) 
        {
            
            Json* child_title=Json_getItem(json_child,"title");
            Json* child_weight=Json_getItem(json_child,"weight");
            Json* child_pic_url=Json_getItem(json_child,"img2");
            
            if (child_pic_url)
            {
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S2%d%dDisplay%d.png",AppDelegate::S2SelectedScene,AppDelegate::S2LeftSelected,index+1);

                DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                
                string titleStr = child_title->valuestring;
                string weightStr = child_weight->valuestring;
                
                titleMap[PersonalApi::convertIntToString(index+1)] = titleStr;
                weightMap[PersonalApi::convertIntToString(index+1)] = weightStr;
                
                index++;
            }
            json_child=json_child->next;
        }
        /*
        for(map<string, string>::iterator iter=valueMap.begin();iter!=valueMap.end();++iter)
        {
            CCLOG("3333==%s",iter->second.c_str());
        }
        */
        string titleStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Title";
        PersonalApi::wirteVecToXml(titleMap,titleStr);
        
        string weightlStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Weight";
        PersonalApi::wirteVecToXml(weightMap,weightlStr);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
    
}

bool S21ZiBuLei::setUpSubClass2()
{
	bool bRet = false;
	do
	{
 
        float aFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"label");
        string titleStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Title";
        titleMap = PersonalApi::getRealGroupStringMap(plistDic,titleStr.c_str(),"label");
        string weightlStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Weight";
        weightMap = PersonalApi::getRealGroupStringMap(plistDic,weightlStr.c_str(),"label");
       
        scrollMaxSizeY = 0;
        
        
        CCLayer * pLayer = CCLayer::create();
        pLayer->setPosition(CCPointZero);
        
        m_pScrollView = CCScrollView::create();
        m_pScrollView->setPosition(ccp(200,70));
        m_pScrollView->setContainer(pLayer);
        
        
        CCSize showSize = CCSizeMake(900, 500);
        
        m_pScrollView->setViewSize(CCSizeMake(showSize.width, showSize.height-20));
  
        int indexNum = 1;
        imagemenu = CCMenu::create(NULL);
        imagemenu->setPosition(CCPointZero);
        
        float elementHeight;
        float itemScale = 0.5;

        int row = weightMap.size()/3+1;
        {
            string  str="S2BigPic.png";
            CCSprite * scrollPicSprite = CCSprite::create(str.c_str());
 
            elementHeight = scrollPicSprite->getContentSize().height* itemScale+50;
            scrollMaxSizeY = elementHeight*row;
        }

        for (int i  = 0; i<row; i++)//
        {
            for (int j = 0; j<3; j++)
            {
                if (indexNum==weightMap.size())
                {
                    break;
                }
                 
                string picName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(indexNum)+".png";
                
                
                string picNameStr=PersonalApi::getRealImageName(picName.c_str(),"S2BigPic.png").c_str();
                
                CCMenuItemImage *aItem = CCMenuItemImage::create(
                                                                 picNameStr.c_str(),
                                                                 picNameStr.c_str(),
                                                                 this,
                                                                 menu_selector(S21ZiBuLei::S21ZiBuLeiMenuCallback));
                aItem->setScale(itemScale);
                CCSize aItemSize = CCSizeMake(aItem->getContentSize().width*itemScale, aItem->getContentSize().height*itemScale);
                aItem->setPosition(ccp(148+(aItemSize.width+8)*j,scrollMaxSizeY-aItemSize.height*itemScale-10-(aItemSize.height+50)*i));
                aItem->setTag(btnTag+indexNum);
                FDMenu * detailMenu = FDMenu::create();
                detailMenu ->setPosition(CCPointZero);
                detailMenu->addChild(aItem,zNum);
                pLayer->addChild(detailMenu,zNum);
                
                CCSize dimensionsSize = CCSizeMake(aItemSize.width, aFontSize);
                
                string valueStr;
                if (weightlStr.size()==0)
                {
                    valueStr = titleMap[PersonalApi::convertIntToString(indexNum)];
                }
                else
                {
                    valueStr = titleMap[PersonalApi::convertIntToString(indexNum)]+"("+weightMap[PersonalApi::convertIntToString(indexNum)]+")";
                }
                
                CCLabelTTF *aLabel = CCLabelTTF::create(valueStr.c_str(), s1FontName_macro, aFontSize, dimensionsSize, kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
                aLabel->setPosition(ccp(aItem->getPosition().x,aItem->getPosition().y-105));
                aLabel->setColor(ccc3(112,16,12));
                pLayer->addChild(aLabel,zNum);
                
                indexNum++;
                
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
void S21ZiBuLei::S21ZiBuLeiMenuCallback(CCObject* pSender)
{
    if (isMenuLock == false)
    {
        CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
      
        AppDelegate::S2SelectedPicNum = aItem->getTag()-btnTag;
        CCScene *newScene = CCScene::create();
        newScene->addChild(S22PicDetail::create());
        CCDirector::sharedDirector()->replaceScene((CCTransitionFade::create(0.0f, newScene)));
    }
}

void S21ZiBuLei::S311DetailCallback(CCObject* pSender)
{
    if (isMenuLock == false)
    {

    }
}
void S21ZiBuLei::scrollViewDidScroll(CCScrollView* view)
{
    isMenuLock = true;
    this->schedule(schedule_selector(S21ZiBuLei::S31Delay),0.5f,false,0.0);
}

void S21ZiBuLei::S31Delay(float dt)
{
    isMenuLock = false;
}
