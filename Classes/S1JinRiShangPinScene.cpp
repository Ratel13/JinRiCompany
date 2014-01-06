//
//  S1S1JinRiShangPinScene.cpp
//  GreTest
//
//  Created by lyy on 13-6-23.
//
//

#include "S1JinRiShangPinScene.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"

#include "S11CompanyInfo.h"
#include "S12Leader.h"
#include "S13News.h"
#include "S14Brand.h"
#include "S15ShowVideo.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S1JinRiShangPin"
#define zNum 100
#define btnTag 100

bool S1JinRiShangPin::initInfo()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        CC_BREAK_IF(!initInfo2());
        
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S1JinRiShangPin::setUpSubClass()
{
	bool bRet = false;
	do
	{
        
        
        map<string, string> naviGroupStrMap =  ScriptParser::getGroupStringFromPlist(plistDic,"naviTitle");
        float naviFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"naviTitle");
        float firstStrFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"firstTitle");
        CCPoint naviStrPosition = ScriptParser::getPositionFromPlist(plistDic,"naviTitle");
        
        for (int i=0; i<(int)naviGroupStrMap.size(); i++)
        {
            const char * labelStr = naviGroupStrMap[PersonalApi::convertIntToString(i+1)].c_str();
            
            float fontSize;
            if (0 == i)
            {
                fontSize = firstStrFontSize;
            }
            else
            {
                fontSize = naviFontSize;
            }
            CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, fontSize);
            pLabel->setPosition(ccp(naviStrPosition.x+pLabel->getContentSize().width*1.5*i,naviStrPosition.y));
            if (i>0)
            {
                pLabel->setPosition(ccp(30+naviStrPosition.x+pLabel->getContentSize().width*1.6*i,naviStrPosition.y));
            }
            if (0 == i)
            {
                pLabel->setColor(ccc3(193.0,159.0,113.0));
                
            }
            else if (selectedScene == i)
            {
                pLabel->setColor(ccc3(255.0,255.0,255.0));
                CCSprite * selectFrameSprite = CCSprite::create("PSubNavBackground.png");
                selectFrameSprite ->setPosition(pLabel->getPosition());
                this->addChild(selectFrameSprite,zNum);
            }
            else
            {
                pLabel->setColor(ccc3(128.0,128.0,128.0));
            }
            pLabel->setTag(234);
            this->addChild(pLabel,zNum+1);
            
            if (0 != i)
            {
            CCSprite * sprite1 = CCSprite::create();
			CCSprite * sprite2 = CCSprite::create();
            
			CCMenuItemSprite *aItem = CCMenuItemSprite::create(
                                                               sprite1,
                                                               sprite2,
                                                               this,
                                                               menu_selector(S1JinRiShangPin::menuCallback));
			CC_BREAK_IF(! aItem);
			aItem->setPosition(pLabel->getPosition());
            aItem->setContentSize(pLabel->getContentSize());
            aItem->setTag(btnTag+i);
			_menu ->addChild(aItem,zNum);
            }
        }
        CCLabelTTF *titleLabel = (CCLabelTTF*)this->getChildByTag(234);
        CCSprite * S1PSubBottomSprite = CCSprite::create("S1PSubBottom.png");
        S1PSubBottomSprite->setPosition( ccp(origin.x+visibleSize.width/2,titleLabel->getPosition().y-titleLabel->getContentSize().height/2-10));
        this->addChild(S1PSubBottomSprite,zNum);
        
     
        
        CC_BREAK_IF(! setUpSubClass2());
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S1JinRiShangPin::menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    removeUIKit();
    CCScene *newScene = CCScene::create();
    switch (aItem->getTag())
    {
        case btnTag+1:
            newScene->addChild(S11CompanyInfo::create());
            
            break;
        case btnTag+2:
            newScene->addChild(S12Leader::create());
            
            break;
        case btnTag+3:
            newScene->addChild(S13News::create());
            
            break;
        case btnTag+4:
            newScene->addChild(S14Brand::create());
            
            break;
            
        case btnTag+5:
        {
            /*
            SPWebView *webView_top = (SPWebView *)SPWebView::create();
            CCRect rect = CCRect(origin.x, origin.y, visibleSize.width,visibleSize.height);
            //webView_top->setTag(tag_webView_icon4);
            webView_top->addWebViewWithCloseButton("http://v.youku.com/v_show/id_XNTgwOTMwMzc2.html?f=19454091&ev=1", rect);
            this->addChild(webView_top);
             */
            newScene->addChild(S15ShowVideo::create());
             
        }
            break;
            
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(newScene);
    
}
