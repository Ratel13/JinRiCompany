//
//  GRETestAppDelegate.h
//  GRETest
//
//  Created by lyy on 13-3-26.
//  Copyright __MyCompanyName__ 2013ƒÍ. All rights reserved.
//

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "CCApplication.h"
#include "cocos2d.h"
#include <string.h>
/**
@brief    The cocos2d Application.

The reason to implement with private inheritance is to hide some interface details of CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function is called when the application enters the background
    @param  the pointer of the application instance
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function is called when the application enters the foreground
    @param  the pointer of the application instance
    */
    virtual void applicationWillEnterForeground();
    
    static std::string sceneId;
    static bool isNetWork;
    static bool isUpDateLock;
    static cocos2d::CCSprite *loadingActivity;
    static int picDidFinishNum;
    static int picDidFinishCount;
    static bool isDownLoadedFinish;
    static cocos2d::CCLabelTTF *loadingLabel;
    static int S1NaviSelected;
    static std::map<std::string, std::string> rightDetailTitleMap1;
    static std::map<std::string, std::string> rightDetailTitleMap2;
    static std::map<std::string, std::string> rightDetailSubTitleMap1;
    static std::map<std::string, std::string> rightDetailSubTitleMap2;
    static std::map<std::string, std::string> rightTimeMap1;
    static std::map<std::string, std::string> rightTimeMap2;
    static int S21NetWorkLock;
    static int S22NetWorkLock;
    static bool S22LeftSelectLock;
    static int S1NewsSelected;
    static int S2LeftSelected;
    static int S151DetailSelected;
    static float S2Alpha;
    static int S2SceneNum;
    static int  S2SelectedScene;
    static int  S22Selected;
    static bool S23IsBigPic;
    static bool S2isInParent;
    static int S2SelectedPicNum;
    static bool IsChangeScrollView;
    static int S3SceneSelect;
    static int S31MeiShiSelected;
    static int S311DetailSelected;
    static int S32XiaoTieShiSelected;
    static int S4SelectNavi;
    static std::string S51TextViewStr;
    static int S52ProcessSelected;
    static std::string S49TextViewStr;
    static bool isTextViewExist;
    static int S6SelectNavi;

};

#endif // _APP_DELEGATE_H_

