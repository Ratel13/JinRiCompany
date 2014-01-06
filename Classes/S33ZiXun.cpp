//  S33ZiXun.cpp
//  JinRiCompany
//
//  Created by lyy on 13-7-2.
//
//

#include "S33ZiXun.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S311Detail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize() 
#define origin CCDirector::sharedDirector()->getVisibleOrigin() 

#define s1FontName_macro "Arial"

#define classPlistName_macro "S33ZiXun"
#define zNum 100
#define btnTag 100


CCScene* S33ZiXun::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S33ZiXun *layer = S33ZiXun::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S33ZiXun::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        selectedScene = 1;
        
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S33ZiXun::UpDate()
{

    ConnetToUrl("http://www.jrsp.cn/app/jconsult.php","jconsult","");
}

void S33ZiXun::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        string currentClassName(classPlistName_macro);
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S33ZiXun::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene)); 
  
}
void S33ZiXun::DownLoadFinish()
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
    
    //大图片
    
    Json* root_bigpicture = Json_getItem(root, "pic_url");
    if (root_bigpicture) {
        DownLoadFile(root_bigpicture->valuestring, "S33BigPic.png");
    }
    
    //电话
    Json* root_phone = Json_getItem(root, "phone");
    if (root_phone) {
        Json* json_child=root_phone->child;
        map<string, string> valueMap;
        string valueStr = json_child->valuestring;
        valueMap[PersonalApi::convertIntToString(1)] = valueStr;
        PersonalApi::wirteVecToXml(valueMap,"qqIntro");
    }
    
    //qq
	Json* root_text=Json_getItem(root,"qq");
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
        
        PersonalApi::wirteVecToXml(valueMap,"qqIntro");
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
}

bool S33ZiXun::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        string strBg = PersonalApi::getRealImageName("S33BigPic.png","S33BigPic.png").c_str();
        CCSprite *spriteBg = CCSprite::create(strBg.c_str());
        spriteBg->setPosition(ScriptParser::getPositionFromPlist(plistDic,"bigPic"));
        this->addChild(spriteBg,zNum);
        
        
        float aX = 500;
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>电话>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        map<string, string> showPhoneStrMap;
        if (PersonalApi::readXmlToVec("phoneIntro").size()>0)
        {
            showPhoneStrMap = PersonalApi::readXmlToVec("phoneIntro");
        }
        else
        {
            showPhoneStrMap = ScriptParser::getGroupStringFromPlist(plistDic, "phoneIntro");
        }
        
        string spacePhoneStr = "健康专家咨询电话：  ";
        string strphone = showPhoneStrMap[PersonalApi::convertIntToString(1)];
        strphone = spacePhoneStr + strphone;
        CCLabelTTF *phoneLabel = CCLabelTTF::create(strphone.c_str(), s1FontName_macro, 20);
        phoneLabel->setAnchorPoint(CCPointZero);
        phoneLabel->setPosition(ccp(aX-20,380));
        phoneLabel->setColor(ccRED);
        this->addChild(phoneLabel,zNum);
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>end>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        
        
        //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>qq图片+qq号>>>>>>>>>>>>>>>>>>>>>>>>>
        map<string, string> showStrMap;
        if (PersonalApi::readXmlToVec("qqIntro").size()>0)
        {
            showStrMap = PersonalApi::readXmlToVec("qqIntro");
        }
        else
        {
            showStrMap = ScriptParser::getGroupStringFromPlist(plistDic, "qqIntro");
        }
        
        for (int i=1; i<(int)showStrMap.size(); i++) {
            cocos2d::CCSprite * aSprite = CCSprite::create(ScriptParser::getImageFromPlist(plistDic, "qq"));
            aSprite->setPosition(ccp(aX,330-((i-1)*40)));
            this->addChild(aSprite,zNum);

            string spaceStr = "QQ咨询：  ";
            string strqq = showStrMap[PersonalApi::convertIntToString(i)];
            strqq = spaceStr + strqq;
            CCLabelTTF *qqLabel = CCLabelTTF::create(strqq.c_str(), s1FontName_macro, 20);
            qqLabel->setAnchorPoint(ccp(0,0.5));
            qqLabel->setPosition(ccp(aX+30,aSprite->getPosition().y));
            qqLabel->setColor(ccRED);
            this->addChild(qqLabel,zNum);
        }
        
        bRet = true;
	} while (0);
    
	return bRet;
}

void S33ZiXun::S33ZiXunCallback(CCObject* pSender)
{
    
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag:
            //newScene->addChild(S33ZiXun::create());
            
            break;
        case btnTag+1:
            //newScene->addChild(S3TestMain::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));    
}

void S33ZiXun::back(CCObject* pSender)
{
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S311Detail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(0.0f, newScene));
}
