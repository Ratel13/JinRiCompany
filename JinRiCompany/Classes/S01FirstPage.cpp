//
//  S01FirstPage.cpp
//  JinRiCompany
//
//  Created by lyy on 13-7-26.
//
//

#include "S01FirstPage.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"
#include "FDMenu.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S01FirstPage"
#define zNum 100
#define btnTag 100
#define scrollBtnTag 1000

CCScene* S01FirstPage::scene()
{
	CCScene * scene = NULL;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
		scene = CCScene::create();
		S01FirstPage *layer = S01FirstPage::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}
void S01FirstPage::UpDate()
{
    ConnetToUrl("http://www.jrsp.cn/app/jexpand.php","jindex","");
}
void S01FirstPage::refreshDownLoadingData(bool isCompleted)
{
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    CCScene *newScene = CCScene::create();
    newScene->addChild(S01FirstPage::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0, newScene));//??aбу??иC?бу?бу?
}
void S01FirstPage::DownLoadFinish()
{
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
	Json* root= Json_create(m_strUrlContent.c_str());
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
    if (CCUserDefault::sharedUserDefault()->getStringForKey(version.c_str()).compare(versionStr) == 0)// && AppDelegate::isUpDateLock)
    {
        CCUserDefault::sharedUserDefault()->setBoolForKey(needUpDate.c_str(),false);
        AppDelegate::loadingLabel->setString("");
        _menu->setEnabled(true);
        setUpUpDateLabel(CCPointMake(130, 650),CCPointMake(9000, 650),CCUserDefault::sharedUserDefault()->getStringForKey(time.c_str()),CCUserDefault::sharedUserDefault()->getBoolForKey(needUpDate.c_str()));
        return;
    }
    CCUserDefault::sharedUserDefault()->setBoolForKey(needUpDate.c_str(),true);
    {
        setUpUpDateLabel(CCPointMake(130, 650),CCPointMake(9000, 650),CCUserDefault::sharedUserDefault()->getStringForKey(time.c_str()),CCUserDefault::sharedUserDefault()->getBoolForKey(needUpDate.c_str()));
    }
    CCUserDefault::sharedUserDefault()->setStringForKey(newVersion.c_str(), root_Version->valuestring);
    Json* root_time=Json_getItem(root,"time");
    if (root_time)
    {
        CCUserDefault::sharedUserDefault()->setStringForKey(time.c_str(), root_time->valuestring);
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
        PersonalApi::wirteVecToXml(valueMap,"S01Detail");
    }
    checkPicDownLoading();
}

bool S01FirstPage::initInfo2()
{
    bool bRet = false;
	do
	{
     
        
        bRet = true;
	} while (0);
    
	return bRet;
}

//networking downloding
bool S01FirstPage::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        refreshItemImage->setOpacity(0.0f);
        CCSprite * showbigPicture = CCSprite::create("firstPage.png");
        showbigPicture->setPosition( ccp(visibleSize.width/2,visibleSize.height/2-30));
        showbigPicture->setScale(1.02f);
        showbigPicture->setScaleX(1.1f);
        this->addChild(showbigPicture,zNum);
		
        if (PersonalApi::readXmlToVec("S01Detail").size()>0)
        {
            showStrMap = PersonalApi::readXmlToVec("S01Detail");
        }
        showStrMapSize = showStrMap.size();
        for (int i = 0; i<showStrMapSize; i++)
        {
            showStrMap[PersonalApi::convertIntToString(showStrMapSize+i-1)] = showStrMap[PersonalApi::convertIntToString(i+1)];
        }
        scrollDistance = -showStrMapSize*20;
        pTableView = CCTableView::create(this, CCSizeMake(500, 390));
		pTableView->setDirection(kCCScrollViewDirectionVertical);
        pTableView->setPosition(ccp(550,100));
		pTableView->setDelegate(this);
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView,zNum+1000);
		pTableView->reloadData();
        pTableView->setTouchEnabled(false);
        
        if (showStrMapSize>11)
        {
            this->schedule(schedule_selector(S01FirstPage::pTableViewScroll),1.0f);
        }
        
		bRet = true;
	} while (0);
    
	return bRet;
}
void S01FirstPage::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}
CCSize S01FirstPage::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    const char * labelStr;
    labelStr = showStrMap[PersonalApi::convertIntToString(idx+2)].c_str();
     CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, 10);
    if(idx+1 == showStrMap.size()-1)
    {
        return CCSizeMake(pLabel->getContentSize().width, pLabel->getContentSize().height+30);
    }
    return CCSizeMake(pLabel->getContentSize().width, pLabel->getContentSize().height+20);
}
CCTableViewCell* S01FirstPage::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        string aStr;
        aStr = showStrMap[PersonalApi::convertIntToString(idx+1)];
        const char * labelStr = aStr.c_str();
        float titleFontSize = 20;
        CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, titleFontSize);
        pLabel->setTag(234);
        pLabel->setAnchorPoint(ccp(0,0));
        pLabel->setPosition(CCPointZero);
        pLabel->setColor(ccWHITE);
        pCell->addChild(pLabel);
    }
    else
    {
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(234);
        string aStr=showStrMap[PersonalApi::convertIntToString(idx+1)];
        pLabel->setString(aStr.c_str());
    }
    return pCell;
}
unsigned int S01FirstPage::numberOfCellsInTableView(CCTableView *table)
{
    int row = showStrMap.size();
    if (row-1 < 0)
    {
        return 0;
    }
    return row-1;
}
void S01FirstPage::pTableViewScroll()
{
    scrollTimes++;
    scrollDistance+=20;
    pTableView->setContentOffset(CCPointMake(0, scrollDistance), false);
    
    if(scrollTimes == 11)
    {
        scrollDistance = -showStrMapSize*20;
        scrollTimes = 0 ;
    }
}