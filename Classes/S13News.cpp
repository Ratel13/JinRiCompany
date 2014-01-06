//
//  S13News.cpp
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#include "S13News.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S132Detail.h"
#include "S131More.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S13News"
#define zNum 100
#define btnTag 100
#define btnTag1000 1000
#define btnTag10000 10000

CCScene* S13News::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S13News *layer = S13News::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S13News::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        selectedScene = 3;
        
        bRet = true;
	} while (0);
    
	return bRet;
}

//networking downloding
void S13News::UpDate()
{

    ConnetToUrl("http://www.jrsp.cn/app/jnews.php","jnews","");
}

void S13News::refreshDownLoadingData(bool isCompleted)
{
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S13News::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
}

void S13News::DownLoadFinish()
{
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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
    
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>End>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    
    //Company News
	Json* root_companynews=Json_getItem(root,"Company News");
	if (root_companynews && root_companynews->type==Json_Array)
	{
		Json* json_child=root_companynews->child;
        map<string, string> valueMap;
        map<string, string> subTitleMap;
        map<string, string> timeMap;
       // int i  = 0;
  
        for (int i = 0; i<Json_getSize(root_companynews); i++)
		{
            Json* child_title=Json_getItem(json_child,"title");
            Json* child_subTitle=Json_getItem(json_child,"sub_title");
            Json* child_time=Json_getItem(json_child,"time");
            if (child_title && child_subTitle &&child_time)
			{
          
                string valueStr = child_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
          
                string subTitleStr;
                if (Json_getSize(child_subTitle) != 0)
                {
                    subTitleStr = child_subTitle->valuestring;
                }
                else
                {
                    //subTitleStr = "нч";
                    subTitleStr = " ";
                }
                subTitleMap[PersonalApi::convertIntToString(i+1)] = subTitleStr;
                
                string timeStr = child_time->valuestring;
                timeMap[PersonalApi::convertIntToString(i+1)] = timeStr;
                
			}
			json_child=json_child->next;
		}

        PersonalApi::wirteVecToXml(valueMap,"S13RightTitleDetail1");
        PersonalApi::wirteVecToXml(subTitleMap,"S13SubTitle1");
        PersonalApi::wirteVecToXml(timeMap,"S13Time1");
    }
    
    //Industry News
	Json* root_industrynews=Json_getItem(root,"Industry News");
	if (root_industrynews && root_industrynews->type==Json_Array)
	{
		Json* json_child=root_industrynews->child;
        map<string, string> valueMap;
        map<string, string> subTitleMap;
        map<string, string> timeMap;
        int i  = 0;
		while(json_child)
		{
			
            Json* child_title=Json_getItem(json_child,"title");
            Json* child_subTitle=Json_getItem(json_child,"sub_title");
            Json* child_time=Json_getItem(json_child,"time");
            
			if (child_title && child_subTitle)
			{

                string valueStr = child_title->valuestring;
                valueMap[PersonalApi::convertIntToString(i+1)] = valueStr;
                
                string subTitleStr;
                if (Json_getSize(child_subTitle) != 0)
                {
                    subTitleStr = child_subTitle->valuestring;
                }
                else
                {
                   // subTitleStr = "нч";
                    subTitleStr = " ";
                }
                subTitleMap[PersonalApi::convertIntToString(i+1)] = subTitleStr;
                
                string timeStr = child_time->valuestring;
                timeMap[PersonalApi::convertIntToString(i+1)] = timeStr;
                
                i++;
			}
			json_child=json_child->next;
		}

        PersonalApi::wirteVecToXml(valueMap,"S13RightTitleDetail2");
      
        PersonalApi::wirteVecToXml(subTitleMap,"S13SubTitle2");
        PersonalApi::wirteVecToXml(timeMap,"S13Time2");
    }
    
    checkPicDownLoading();
}

bool S13News::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        CCSprite * showbigPicture = CCSprite::create("S13PLeftimg.png");
        showbigPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S13PLeftimg"));
        this->addChild(showbigPicture,zNum);
		
        CCSprite * lineSprite = CCSprite::create("s13PMiddleString.png");
        lineSprite->setPosition( ccp(showbigPicture->getPosition().x+showbigPicture->getContentSize().width/2+10,showbigPicture->getPosition().y-50));
        this->addChild(lineSprite,zNum);
      
        
        rightBigTitleCnMap = ScriptParser::getGroupStringFromPlist(plistDic,"rightBigTitleCn");
        rightBigTitleEnMap = ScriptParser::getGroupStringFromPlist(plistDic,"rightBigTitleEn");
        
        CCPoint titleCnPosition =  CCPointMake(lineSprite->getPosition().x + 15,lineSprite->getPosition().y+lineSprite->getContentSize().height/2-40);

        float lastTitlePositionY = titleCnPosition.y;
        float lastLabelHeight;
        float lastLabelPositionY = titleCnPosition.y;
        
        

        AppDelegate::rightDetailTitleMap1 = PersonalApi::getRealGroupStringMap(plistDic,"S13RightTitleDetail1","rightTitleDetail1");
        AppDelegate::rightDetailTitleMap2 = PersonalApi::getRealGroupStringMap(plistDic,"S13RightTitleDetail2","rightTitleDetail2");
        
        AppDelegate::rightDetailSubTitleMap1 = PersonalApi::getRealGroupStringMap(plistDic,"S13SubTitle1","rightTitleDetail2");
        AppDelegate::rightDetailSubTitleMap2 = PersonalApi::getRealGroupStringMap(plistDic,"S13SubTitle2","rightTitleDetail2");
        AppDelegate::rightTimeMap1 = PersonalApi::getRealGroupStringMap(plistDic,"S13Time1","rightTitleDetail2");
        AppDelegate::rightTimeMap2 = PersonalApi::getRealGroupStringMap(plistDic,"S13Time2","rightTitleDetail2");

        for (int i = 0; i<(int)rightBigTitleCnMap.size(); i++)
        {
            CCSprite * dotTitleLineSprite = CCSprite::create("s131RightWordBottom.png");
            
            //
            const char * titleCnStr = rightBigTitleCnMap[PersonalApi::convertIntToString(i+1)].c_str();
            float titleCnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"titleCnFontSize");
            CCSize titleCnSize = CCSizeMake(dotTitleLineSprite->getContentSize().width, titleCnFontSize);
            CCLabelTTF *titleCnLabel = CCLabelTTF::create(titleCnStr, s1FontName_macro, titleCnFontSize,titleCnSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            titleCnLabel->setAnchorPoint(ccp(0.0,0.5));
            titleCnLabel->setPosition(ccp(titleCnPosition.x,lastTitlePositionY));
            titleCnLabel->setColor(ccBLACK);
            this->addChild(titleCnLabel,zNum);
            
            //
            const char * titleEnStr = rightBigTitleEnMap[PersonalApi::convertIntToString(i+1)].c_str();
            float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"titleEnFontSize");
            CCSize titleEnSize = CCSizeMake(dotTitleLineSprite->getContentSize().width, titleCnFontSize);
            CCLabelTTF *titleEnLabel = CCLabelTTF::create(titleEnStr, s1FontName_macro, titleEnFontSize,titleEnSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            titleEnLabel->setAnchorPoint(ccp(0.0,0.5));
            titleEnLabel->setPosition(ccp(titleCnLabel->getPosition().x+100,titleCnLabel->getPosition().y));
            titleEnLabel->setColor(ccGRAY);
            this->addChild(titleEnLabel,zNum);
            
            //
           float moreFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"moreFontSize");
            CCLabelTTF *moreLabel = CCLabelTTF::create("more", s1FontName_macro, moreFontSize);
            moreLabel->setPosition(ccp(titleCnLabel->getPosition().x+dotTitleLineSprite->getContentSize().width/1.1+30,titleCnLabel->getPosition().y-5));
            moreLabel->setColor(ccc3(112,16,12));
            this->addChild(moreLabel,zNum+1);
            {
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S13News::newsMenuCallback));
			aItem->setPosition(moreLabel->getPosition());
            aItem->setContentSize(moreLabel->getContentSize());
                aItem->setTag(btnTag10000+1+i);
			_menu ->addChild(aItem,zNum);
            }
            //
            
            
            lastLabelHeight  = titleCnLabel->getContentSize().height;
            lastLabelPositionY = titleCnLabel->getPosition().y;
            dotTitleLineSprite->setPosition(ccp(titleCnLabel->getPosition().x + dotTitleLineSprite->getContentSize().width/2,titleCnLabel->getPosition().y-titleCnLabel->getContentSize().height+5));
            this->addChild(dotTitleLineSprite,zNum);
            
            
            string rightDetailTitle = "S13RightTitleDetail"+PersonalApi::convertIntToString(i+1);
            rightDetailTitleMap = PersonalApi::getRealGroupStringMap(plistDic,rightDetailTitle.c_str(),"rightTitleDetail1");
            
    
            for (int j  = 0; j<4; j++)
            {
                CCSprite *detailSprite = CCSprite::create("S13PRightPoint.png");
                detailSprite->setPosition(ccp(titleCnLabel->getPosition().x+5,lastLabelPositionY-lastLabelHeight-29));
                this->addChild(detailSprite,zNum);
               
                const char * titleDetailLabelStr = rightDetailTitleMap[PersonalApi::convertIntToString(j+1)].c_str();
                float titleDetailFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"titleDetailFontSize");
                CCSize titleDetailSize = CCSizeMake(dotTitleLineSprite->getContentSize().width, titleCnFontSize);
                
                CCLabelTTF *titleDetailLabel = CCLabelTTF::create(titleDetailLabelStr, s1FontName_macro, titleDetailFontSize, titleDetailSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
                titleDetailLabel->setAnchorPoint(ccp(0.0,1.0));
                titleDetailLabel->setPosition(ccp(detailSprite->getPosition().x+10,detailSprite->getPosition().y+12));
                titleDetailLabel->setColor(ccBLACK);
                this->addChild(titleDetailLabel,zNum);
                
                lastLabelHeight = titleDetailLabel->getContentSize().height+5;
                lastLabelPositionY = titleDetailLabel->getPosition().y;
                
                if (j == 3)
                {
                    
                    lastTitlePositionY = titleDetailLabel->getPosition().y-80;
                    
                }
                
                CCSprite * sprite1 = CCSprite::create();
                CCSprite * sprite2 = CCSprite::create();
                
                CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                                   sprite1,
                                                                   sprite2,
                                                                   this,
                                                                   menu_selector(S13News::showDetail));
                aItem->setAnchorPoint(ccp(0.0,1.0));
                aItem->setPosition(titleDetailLabel->getPosition());
                aItem->setContentSize(titleDetailLabel->getContentSize());
                if (0==i)
                {
                    aItem->setTag(btnTag+1+j);
                }
                else
                {
                    aItem->setTag(btnTag1000+1+j);
                }
                _menu ->addChild(aItem,zNum);
                
                CCSprite * dotDetailTitleLineSprite = CCSprite::create("s131RightWordBottom.png");
                dotDetailTitleLineSprite->setPosition(ccp(detailSprite->getPosition().x + dotDetailTitleLineSprite->getContentSize().width/2-5,titleDetailLabel->getPosition().y-12-10));//titleDetailLabel->getContentSize().height-10));
                this->addChild(dotDetailTitleLineSprite,zNum);
     
            }
            
        }

		bRet = true;
	} while (0);
    
	return bRet;
}

void S13News::newsMenuCallback(CCObject* pSender)
{
    
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    AppDelegate::S1NewsSelected = aItem->getTag();
    CCScene *newScene = CCScene::create();
    newScene->addChild(S131More::create());
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));
}
void S13News::showDetail(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    AppDelegate::S1NewsSelected = aItem->getTag();
    CCScene *newScene = CCScene::create();
    newScene->addChild(S132Detail::create());
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));
}

