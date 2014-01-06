//
//  S0FirstPage.cpp
//  JinRiCompany
//
//  Created by lyy on 13-7-26.
//
//

#include "S0FirstPage.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"

#include "S01FirstPage.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S0FirstPage"
#define zNum 100
#define btnTag 100

bool S0FirstPage::initInfo()
{
    bool bRet = false;
	do
	{
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        //plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
        
        CC_BREAK_IF(!initInfo2());
        
        bRet = true;
	} while (0);
    
	return bRet;
}
bool S0FirstPage::setUpSubClass()
{
	bool bRet = false;
	do
	{
        
        CC_BREAK_IF(! setUpSubClass2());
        
		bRet = true;
	} while (0);
    
	return bRet;
}

void S0FirstPage::menuCallback(CCObject* pSender)
{

    
}
