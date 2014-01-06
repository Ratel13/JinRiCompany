//
//  S12Leader.cpp
//  GreTest
//
//  Created by lihex on 6/23/13.
//
//

#include "S12Leader.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S12Leader"
#define zNum 100
#define btnTag 100
#define scrollBtnTag 1000

CCScene* S12Leader::scene()
{
	CCScene * scene = NULL;
	do
	{
        AppDelegate::sceneId = "S12";
		scene = CCScene::create();
		S12Leader *layer = S12Leader::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}


bool S12Leader::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        selectedScene = 2;
        
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S12Leader::UpDate()
{
    ConnetToUrl("http://www.jrsp.cn/app/jleader.php","jindex","");
}

void S12Leader::refreshDownLoadingData(bool isCompleted)
{
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S12Leader::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0, newScene));//??aбу??иC?бу?бу?
  
}
void S12Leader::DownLoadFinish()
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
   
	Json* root_leaderpicture=Json_getItem(root,"leader");
	if (root_leaderpicture && root_leaderpicture->type==Json_Array)
	{
		Json* json_child=root_leaderpicture->child;
        map<string, string> valueMap;
        map<string, string> picNameMap;
        int i  = 0;
		while(json_child)
		{
            Json* child_id=Json_getItem(json_child, "id");
			Json* child_pic_url=Json_getItem(json_child,"pic_url");
            Json* child_pic_title=Json_getItem(json_child,"text1");
            
			if (child_pic_url && child_id)
			{
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S12Leader_%d.png",i+1);
                
                string picNameStr(szsamllpicname);
                picNameMap[PersonalApi::convertIntToString(i+1)] = picNameStr;
       
                DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                string valueStr = child_pic_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                i++;
                
			}
			json_child=json_child->next;
		}
         PersonalApi::wirteVecToXml(picNameMap,"showPicture");
        PersonalApi::wirteVecToXml(valueMap,"rightContent");
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}
bool S12Leader::setUpSubClass2()
{
	bool bRet = false;
	do
	{
 
        CCSprite * showLeftPicture = CCSprite::create("S12GroundImg.png");
        showLeftPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S12LeftPic"));
        this->addChild(showLeftPicture);
       
       
        if (PersonalApi::readXmlToVec("showPicture").size()>0)
        {
            showPicMap = PersonalApi::readXmlToVec("showPicture");
        }
        else
        {
            showPicMap =  ScriptParser::getGroupImageFromPlist(plistDic,"showPicture");
        
          
            
            
        }
        
        if (PersonalApi::readXmlToVec("rightContent").size()>0)
        {
            showStrMap = PersonalApi::readXmlToVec("rightContent");
        }
        else
        {
            showStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"rightContent");
        }
        
        demission = ScriptParser::getSizeFromPlist(plistDic, "rightContent");
        fntSize = ScriptParser::getFontSizeFromPlist(plistDic, "rightContent");
        
        
        CCSize scrollPicSize = ScriptParser::getSizeFromPlist(plistDic,"showSize");
        CCPoint scrollPicPosition = ScriptParser::getPositionFromPlist(plistDic,"scrollView");
        pTableView = CCTableView::create(this, scrollPicSize);
		pTableView->setDirection(kCCScrollViewDirectionVertical);
		pTableView->setAnchorPoint(ccp(0.0,1.0));
        pTableView->setPosition(scrollPicPosition);
		pTableView->setDelegate(this);
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView,zNum+1000);
		pTableView->reloadData();
        bRet = true;
    } while (0);
    
    return bRet;
}

void S12Leader::menuCallback(CCObject* pSender)
{


}
void S12Leader::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}
CCSize S12Leader::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    const char* picName = showPicMap[PersonalApi::convertIntToString(idx+1)].c_str();
    string  str=PersonalApi::getRealImageName(picName,"S12Leader_1.png").c_str();
    CCSprite* pic = CCSprite::create(str.c_str());
    return CCSizeMake(pic->getContentSize().width, pic->getContentSize().height+10);
}
CCTableViewCell* S12Leader::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        const char* picName = showPicMap[PersonalApi::convertIntToString(idx+1)].c_str();
        string  str=PersonalApi::getRealImageName(picName,"S12Leader_1.png").c_str();
        CCSprite* pic = CCSprite::create(str.c_str());
        pic->setAnchorPoint(CCPointZero);
        pic->setPosition(CCPointZero);
        pic->setTag(234);
        pCell->addChild(pic,zNum);
        const char* ctntStr = showStrMap[PersonalApi::convertIntToString(idx+1)].c_str();
        CCLabelTTF* label = CCLabelTTF::create(ctntStr, s1FontName_macro, fntSize, demission, kCCTextAlignmentLeft);
        label->setColor(ccc3(84, 84, 84));
        label->setAnchorPoint(CCPointZero);
        label->setPosition(ccp(pic->getContentSize().width+20, pic->getPosition().y-10));
        label->setTag(567);
        pCell->addChild(label,zNum);
    }
    else
    {
        const char* picName = showPicMap[PersonalApi::convertIntToString(idx+1)].c_str();
        string  str=PersonalApi::getRealImageName(picName,"S12Leader_1.png").c_str();
        CCSprite * pSprite = (CCSprite *)pCell ->getChildByTag(234);
        pSprite ->setTexture(CCTextureCache::sharedTextureCache()->addImage(str.c_str()));
        const char* ctntStr = showStrMap[PersonalApi::convertIntToString(idx+1)].c_str();
        CCLabelTTF *pLabel2 = (CCLabelTTF*)pCell->getChildByTag(567);
        pLabel2->setString(ctntStr);
    }
    return pCell;
}
unsigned int S12Leader::numberOfCellsInTableView(CCTableView *table)
{
    return showPicMap.size()-1;
}
