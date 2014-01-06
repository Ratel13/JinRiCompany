#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "support/CCNotificationCenter.h"
#include "FDMenu.h"

#include "DataConvert.h"
#include "spine/Json.h"
// #include "Json.h"
#include <string>

USING_NS_CC_EXT;
using namespace cocos2d;
using namespace std;

void DownLoadFile(const char* url,const char* picname );
class SPWebView;
class Main : public cocos2d::CCLayerColor 
{
public:
    void ConnetToUrl(string url,string strtag,string fullpathfilename);
    
	virtual void DownLoadFinish(){};
    
    //这个是post方法
	void PostToUrl(string url,string strtag,string strcontent);
    
	//这个是返回的数据
    virtual void onPostFinished(CCNode *node,void *data){};
    
protected:
    	string m_strUrlContent;
private:
	void httpRequestFinish(CCNode *node,void *_data);
private:
	string m_Url;
	string m_FullPathFileName;
	string m_strtag;

public:
    virtual bool init();
    cocos2d::CCMenu* _menu;
    virtual bool initInfo(){return 0;};
    virtual bool setUpSubClass(){return 0;};
    float loadingLabelFont_macro;
    
    cocos2d::CCLabelTTF * timeLabel;
    cocos2d::CCLabelTTF * updateLabel;
    void setUpUpDateLabel(cocos2d::CCPoint timeLabelPosition,cocos2d::CCPoint updateLabelPosition,std::string time,bool isNeedUpDate);
    virtual void UpDate();
    void checkPicDownLoading();
    void checkPicDownLoadingFinished(float dt);
 

    
    void setLoadingActivityEnabel(bool isLoadingActivityEnabel);
    cocos2d::CCMenu * enableMenu;
    void outOfTime(float dt);
    virtual void refreshDownLoadingData(bool isCompleted){};
    SPWebView *webView_top;
    CCMenuItemImage * backItemImage;
    void removeVideo(CCObject * pSender);
    void removeUIKit();

    
	void PressGoUpData(CCObject* pSender);
    void goUpData();
    void goRefreshDownLoadingData(bool isCompleted);
    CCMenuItemSprite * bgGrayItemImage;
    CCSprite * loadingActivity;
    CCMenuItemImage * refreshItemImage;
    void upDateColdTime(CCTime * time);
   private:
    
    cocos2d::CCDictionary* plistDic;
    cocos2d::CCLabelTTF *titleLabel;
    void menuCallback(CCObject* pSender);
  
    int selectedTitle;
};

#endif  // __HELLOWORLD_SCENE_H__
