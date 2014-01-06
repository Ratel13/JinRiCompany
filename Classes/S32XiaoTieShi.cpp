//
//  S32XiaoTieShi.cpp
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#include "S32XiaoTieShi.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S311Detail.h"
#include "S321Detail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//可视区域size
#define origin CCDirector::sharedDirector()->getVisibleOrigin()//可视区域原点

#define s1FontName_macro "Arial"

#define classPlistName_macro "S32XiaoTieShi"
#define zNum 100
#define btnTag 100

using namespace cocos2d;

CCScene* S32XiaoTieShi::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S32XiaoTieShi *layer = S32XiaoTieShi::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S32XiaoTieShi::initInfo2()
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
void S32XiaoTieShi::UpDate()
{

    ConnetToUrl("http://www.jrsp.cn/app/jtips.php","jtips","");
}

void S32XiaoTieShi::refreshDownLoadingData(bool isCompleted)
{
 
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S32XiaoTieShi::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));

}
void S32XiaoTieShi::DownLoadFinish()
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
    
	Json* root_leaderpicture=Json_getItem(root,"articles");
	if (root_leaderpicture && root_leaderpicture->type==Json_Array)
	{
		Json* json_child=root_leaderpicture->child;
        map<string, string> valueMap;
        loopPicNameMap.clear();
        int i  = 0;
		while(json_child)
		{
        
			Json* child_pic_url=Json_getItem(json_child,"img1");
            Json* child_pic_title=Json_getItem(json_child,"title");
            
			if (child_pic_url && child_pic_title)
			{
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S32ScrollPic_%d.png",i+1);
                
                string picNameStr(szsamllpicname);
                loopPicNameMap[PersonalApi::convertIntToString(i+1)] = picNameStr;
                
                DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                string valueStr = child_pic_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                i++;
                
			}
			json_child=json_child->next;
		}
        PersonalApi::wirteVecToXml(loopPicNameMap,"S32ScrollPic");
        PersonalApi::wirteVecToXml(valueMap,"S32TitleIntro");
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}
bool S32XiaoTieShi::setUpSubClass2()
{
    
	bool bRet = false;
	do
	{
        showStrMap = PersonalApi::getRealGroupStringMap(plistDic, "S32TitleIntro", "titleIntro");
        showPicMap = PersonalApi::getRealGroupImageMap(plistDic, "S32ScrollPic", "scrollPic");//readXmlToVec("scrollPic");
      
        CCSize scrollPicSize = ScriptParser::getSizeFromPlist(plistDic,"scrollPic");
        CCPoint scrollPicPosition = ScriptParser::getPositionFromPlist(plistDic,"scrollPic");
        pTableView = CCTableView::create(this, CCSizeMake(scrollPicSize.width,scrollPicSize.height-10));
        pTableView->setDirection(kCCScrollViewDirectionVertical);
        pTableView->setAnchorPoint(ccp(0.0,1.0));
        pTableView->setPosition(ccp(scrollPicPosition.x,scrollPicPosition.y));
        pTableView->setDelegate(this);
        pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView,zNum+1);
        pTableView->reloadData();
                
		bRet = true;
	} while (0);
    
	return bRet;
}

void S32XiaoTieShi::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
    AppDelegate::S32XiaoTieShiSelected = cell->getIdx()+1;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S321Detail::create());
   
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.0f, newScene));//动画过场
}

CCSize S32XiaoTieShi::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    string realImg = PersonalApi::getRealImageName(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str(), "S32DispalySmall1.png");
    
    CCSprite *pSprite = CCSprite::create(realImg.c_str());
    
    const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx)].c_str();
    float fontSize = 40;//ScriptParser::getFontSizeFromPlist(plistDic,"titleIntro");
    CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
    pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
    float size1 = pLabel->getContentSize().height;
    float size2 = pSprite->getContentSize().height;
    return CCSizeMake(table->getContentSize().width, size1+size2+5);
    
}

CCTableViewCell* S32XiaoTieShi::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        string realImg = PersonalApi::getRealImageName(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str(), "S32DispalySmall1.png");
        CCSprite *pSprite = CCSprite::create(realImg.c_str());
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setTag(123);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
		CCSize MaxSize=CCSizeMake(600,200);
        const char * labelStr = showStrMap[PersonalApi::convertIntToString(idx+1)].c_str();//"S31Titlejinri.png";
        float fontSize = 26;//ScriptParser::getFontSizeFromPlist(plistDic,"titleIntro");
        CCLabelTTF *pLabel =  CCLabelTTF::create(labelStr, s1FontName_macro, fontSize, MaxSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        pLabel->setPosition(ccp(pSprite->getContentSize().width+350,pSprite->getContentSize().height/2));
        pLabel->setTag(246);
        pLabel->setColor(ccBLACK);
		pLabel->setHorizontalAlignment(kCCTextAlignmentLeft);
        pCell->addChild(pLabel,zNum+1);
        
        CCSprite *BottomLineSprite = CCSprite::create("S35Xuxian.png");
        BottomLineSprite->setAnchorPoint(CCPointZero);
        BottomLineSprite->setPosition(ccp(0,-30));
        pCell->addChild(BottomLineSprite);
        
    }
    else
    {
        string realImg = PersonalApi::getRealImageName(showPicMap[PersonalApi::convertIntToString(idx+1)].c_str(), "S32DispalySmall1.png");
        CCSprite *pSprite = (CCSprite*)pCell->getChildByTag(123);
        //cocos2d-x 动态修改图片
         pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(realImg.c_str()));
        
        
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(246);
        string aStr = showStrMap[PersonalApi::convertIntToString(idx+1)];
        PersonalApi::string_replace(aStr, "<br/>", "\n");
        pLabel->setString(aStr.c_str());
        
    }
    
    return pCell;
}

unsigned int S32XiaoTieShi::numberOfCellsInTableView(CCTableView *table)
{
    return showPicMap.size()-1;
}

void S32XiaoTieShi::S2menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S311Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.0f, newScene));//动画过场
}

void S32XiaoTieShi::S2back(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    
}