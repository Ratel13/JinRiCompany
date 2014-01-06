
//  S24AutoPlay.cpp
//  JinRiCompany
//
//  Created by lyy on 13-7-1.
//
//

#include "S24AutoPlay.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S22PicDetail.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S24AutoPlay"
#define zNum 100
#define btnTag 100
#include "FDScrollView.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S24AutoPlay::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S24AutoPlay *layer = S24AutoPlay::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}
bool S24AutoPlay::init()
{
	bool bRet = false;
	do
	{
        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(0, 0, 0, 255)));

		//√ø∏ˆœÓƒø∂º“™¥¥Ω®µƒ∂´Œ˜
        
		_menu = CCMenu::create(NULL);
		_menu->setPosition(CCPointZero);
        
		this->addChild(_menu, zNum+100);
        
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
     
		//øÿº˛
        CCSprite * NaviBg = CCSprite::create("navBar.png");
        NaviBg->setAnchorPoint(ccp(0.0,1.0));
        NaviBg->setPosition(ccp(origin.x-2,origin.y+visibleSize.height));
        this->addChild(NaviBg,zNum);
        
        CCSprite * quitButton = CCSprite::create("quit.png");
        quitButton->setAnchorPoint(ccp(0.0,1.0));
        quitButton->setPosition(ccp(origin.x,origin.y+visibleSize.height-25));
        this->addChild(quitButton,zNum);
        
        CCMenuItemFont * back = CCMenuItemFont::create("BACK", this, menu_selector(S24AutoPlay::S4back));
                                                       back->setPosition(ccp(quitButton->getPosition().x+35,quitButton->getPosition().y-15));
                                                       _menu ->addChild(back,zNum);
        quitButton->setAnchorPoint(ccp(0.0,1.0));
        back->setColor(ccBLACK);
        back->setOpacity(1);
        
        /*
        CCMenuItemFont * play = CCMenuItemFont::create("Menu", this, menu_selector(S24AutoPlay::S4back));
        play->setPosition(ccp(900,700));
        _menu ->addChild(play,zNum);
        play->setColor(ccBLACK);
        */
        CCSprite * footBar = CCSprite::create("S24yj.png");
        footBar->setScaleY(0.5);
        footBar->setAnchorPoint(ccp(0.0,0.0));
        footBar->setPosition(ccp(origin.x,origin.y));
        this->addChild(footBar,zNum);
        
        CCSize showSize = CCSizeMake(visibleSize.width, visibleSize.height-NaviBg->getContentSize().height);
        m_pScrollView = FDScrollView::create(showSize);
        
        
        string titleStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Title";
        titleMap = PersonalApi::getRealGroupStringMap(plistDic,titleStr.c_str(),"label");
        
        string weightlStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Weight";
        weightMap = PersonalApi::getRealGroupStringMap(plistDic,weightlStr.c_str(),"label");
     

        string picName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(AppDelegate::S22Selected)+".png";
        
            string picNameStr=PersonalApi::getRealImageName(picName.c_str(),"S2BigPic.png").c_str();
            CCLOG("111==%s",picNameStr.c_str());
            CCSprite * showbigPicture = CCSprite::create(picNameStr.c_str());
        showbigPicture->setPosition(ccp(visibleSize.width/2-showbigPicture->getContentSize().width/2,200));
            m_pScrollView->addChild(showbigPicture,zNum);
     
        
        m_pScrollView->setPosition(CCPointZero);
        
        m_pScrollView->setContentOffset(ccp(0,0));
        m_pScrollView->setViewSize(CCSizeMake(visibleSize.width, visibleSize.height-NaviBg->getContentSize().height));//???????????
        m_pScrollView->setContentSize(CCSizeMake(visibleSize.width, (visibleSize.height-NaviBg->getContentSize().height)*2));
        
        m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        m_pScrollView->setTouchEnabled(true);
        this->addChild(m_pScrollView);
        
		bRet = true;
	} while (0);

	return bRet;
}



void S24AutoPlay::showBigPic(CCObject* pSender)
{
    
    AppDelegate::S23IsBigPic = true;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S24AutoPlay::create());
    CCDirector::sharedDirector()->replaceScene(newScene);
}

void S24AutoPlay::S4back(CCObject* pSender)
{

    CCScene *newScene = CCScene::create();
    newScene->addChild(S22PicDetail::create());
    CCDirector::sharedDirector()->replaceScene((CCTransitionSlideInR::create(0.0f, newScene)));
    
}