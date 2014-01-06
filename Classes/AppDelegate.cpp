//
//  GRETestAppDelegate.cpp
//  GRETest
//
//  Created by lyy on 13-3-26.
//  Copyright __MyCompanyName__ 2013Âπ? All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"


#include "S01FirstPage.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;
#define rate_macro 1.5
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()
#define naviNum_macro AppDelegate::S1NaviSelected

string  AppDelegate::sceneId = "";
bool AppDelegate::isNetWork = true;
bool AppDelegate::isUpDateLock = true;
CCSprite * AppDelegate::loadingActivity = NULL;
int AppDelegate::picDidFinishNum = 0;
int AppDelegate::picDidFinishCount = 0;
bool AppDelegate::isDownLoadedFinish = false;
CCLabelTTF * AppDelegate::loadingLabel = NULL;
int AppDelegate::S1NaviSelected = 0;
map<string, string> AppDelegate::rightDetailTitleMap1;
map<string, string> AppDelegate::rightDetailTitleMap2;
std::map<std::string, std::string> AppDelegate::rightDetailSubTitleMap1;
std::map<std::string, std::string> AppDelegate::rightDetailSubTitleMap2;
std::map<std::string, std::string> AppDelegate::rightTimeMap1;
std::map<std::string, std::string> AppDelegate::rightTimeMap2;
int AppDelegate::S21NetWorkLock = 0;
int AppDelegate::S22NetWorkLock = 0;
bool AppDelegate::S22LeftSelectLock = false;
int AppDelegate::S1NewsSelected = 0;
int AppDelegate::S151DetailSelected;
int AppDelegate::S2LeftSelected = 1;
float AppDelegate::S2Alpha = 0.0;
int AppDelegate::S2SceneNum = 1;
int AppDelegate::S2SelectedScene = 1;
int AppDelegate::S22Selected = 1;
bool AppDelegate::S23IsBigPic =false;
bool AppDelegate::S2isInParent = true;
int AppDelegate::S2SelectedPicNum = 1;
bool AppDelegate::IsChangeScrollView = false;
int AppDelegate::S3SceneSelect = 1;
int AppDelegate::S31MeiShiSelected = 0;
int AppDelegate::S311DetailSelected = 0;
int AppDelegate::S32XiaoTieShiSelected = 0;
int AppDelegate::S4SelectNavi = 1;
std::string AppDelegate::S51TextViewStr = "";
int AppDelegate::S52ProcessSelected = 0;
std::string AppDelegate::S49TextViewStr = "";
bool AppDelegate::isTextViewExist = false;
int AppDelegate::S6SelectNavi = 1;

AppDelegate::AppDelegate()
{
    /*
     if (2 != CCUserDefault::sharedUserDefault()->getIntegerForKey("firstIn"))
     {
     CCUserDefault::sharedUserDefault()->setIntegerForKey("S2SelectedScene",1);
     CCUserDefault::sharedUserDefault()->setIntegerForKey("firstIn", 2);
     }
     else
     {
     leftSelected = CCUserDefault::sharedUserDefault()->getStringForKey("leftSelected");
     }
     */
     //CCUserDefault::sharedUserDefault()->setIntegerForKey("S2SelectedScene",1);
}

AppDelegate::~AppDelegate()
{
    //CCUserDefault::sharedUserDefault()->setIntegerForKey("S2SelectedScene",1);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("S2SelectedScene",1);
	CCDirector* pDirector = CCDirector::sharedDirector();

	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);

	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	CCSize designSize = CCSizeMake(1024, 768);
	CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();

	if (screenSize.height > 320)
	{
		CCSize resourceSize = CCSizeMake(1024, 768);
		std::vector<std::string> searchPaths;
		searchPaths.push_back("ipad");
		pFileUtils->setSearchPaths(searchPaths);
		pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
	}

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);

	// turn on display FPS
	//pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = S01FirstPage::scene();

	// run
	pDirector->runWithScene(pScene);

	//glClearColor(1.0, 1.0, 1.0, 1.0);//angeBackGroundDefautColor

		return true;

    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
