//
//  S131More.cpp
//  GreTest
//
//  Created by lyy on 13-6-24.
//
//

#include "S131More.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"


#include "S13News.h"
#include "S132Detail.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S131More"
#define zNum 100
#define btnTag 100
#define btnTag1000 1000
#define btnTag10000 10000

CCScene* S131More::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S131More *layer = S131More::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S131More::initInfo2()
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
bool S131More::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        
        refreshItemImage->setOpacity(1.0);
        CCSprite * showbigPicture = CCSprite::create("S13PLeftimg.png");
        showbigPicture->setPosition( ScriptParser::getPositionFromPlist(plistDic,"S13PLeftimg"));
        this->addChild(showbigPicture,zNum);
		
        CCSprite * lineSprite = CCSprite::create("s13PMiddleString.png");
        lineSprite->setPosition( ccp(showbigPicture->getPosition().x+showbigPicture->getContentSize().width/2+20,showbigPicture->getPosition().y-50));
        this->addChild(lineSprite,zNum);
        
    
        CCPoint titleCnPosition =  CCPointMake(lineSprite->getPosition().x + 10,lineSprite->getPosition().y+lineSprite->getContentSize().height/2-40);
        
        float lastTitlePositionY = titleCnPosition.y;
        float lastLabelHeight;
        float lastLabelPositionY = titleCnPosition.y;
        
      
            CCSprite * dotTitleLineSprite = CCSprite::create("s131RightWordBottom.png");
        const char * titleCnStr;
        if (AppDelegate::S1NewsSelected ==10001)
        {
            titleCnStr = ScriptParser::getStringFromPlist(plistDic,"rightFirstTitleCn1");
        }
        else
        {
            titleCnStr = ScriptParser::getStringFromPlist(plistDic,"rightFirstTitleCn2");
        }
            float titleCnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"rightFirstTitleCn");
            CCSize titleCnSize = CCSizeMake(dotTitleLineSprite->getContentSize().width, titleCnFontSize);
            CCLabelTTF *titleCnLabel = CCLabelTTF::create(titleCnStr, s1FontName_macro, titleCnFontSize,titleCnSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            titleCnLabel->setAnchorPoint(ccp(0.0,0.5));
            titleCnLabel->setPosition(ccp(titleCnPosition.x,lastTitlePositionY));
            titleCnLabel->setColor(ccBLACK);
            this->addChild(titleCnLabel,zNum);
        
        const char * titleEnStr;
        if (AppDelegate::S1NewsSelected ==10001)
        {
            titleEnStr = ScriptParser::getStringFromPlist(plistDic,"rightFirstTitleEn1");
        }
        else
        {
            titleEnStr = ScriptParser::getStringFromPlist(plistDic,"rightFirstTitleEn2");
        }
        
            float titleEnFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"rightFirstTitleEn");
            CCSize titleEnSize = CCSizeMake(dotTitleLineSprite->getContentSize().width, titleCnFontSize);
            CCLabelTTF *titleEnLabel = CCLabelTTF::create(titleEnStr, s1FontName_macro, titleEnFontSize,titleEnSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
            titleEnLabel->setAnchorPoint(ccp(0.0,0.5));
            titleEnLabel->setPosition(ccp(titleCnLabel->getPosition().x+100,titleCnLabel->getPosition().y));
            titleEnLabel->setColor(ccGRAY);
            this->addChild(titleEnLabel,zNum);
            
            
            
            
            lastLabelHeight  = titleCnLabel->getContentSize().height;
            lastLabelPositionY = titleCnLabel->getPosition().y-40;
            dotTitleLineSprite->setPosition(ccp(titleCnLabel->getPosition().x + dotTitleLineSprite->getContentSize().width/2,titleCnLabel->getPosition().y-titleCnLabel->getContentSize().height+5));
            this->addChild(dotTitleLineSprite,zNum);
        
  
        if (AppDelegate::S1NewsSelected ==10001)
        {
            //rightDetailTitle = AppDelegate::rightDetailTitleMap1;
            rightBigTitle =  AppDelegate::rightDetailTitleMap1;
            
            rightTime = AppDelegate::rightTimeMap1;
           
            rightDetailTitle = AppDelegate::rightDetailSubTitleMap1;
        }
        else if(AppDelegate::S1NewsSelected ==10002)
        {
            //rightDetailTitle = AppDelegate::rightDetailTitleMap2;
            rightBigTitle =  AppDelegate::rightDetailTitleMap2;
            rightTime = AppDelegate::rightTimeMap2;
            rightDetailTitle = AppDelegate::rightDetailSubTitleMap2;
        }
        
        //rightBigTitle = ScriptParser::getGroupStringFromPlist(plistDic,"rightBigTitle");
    
   
        
       
        CCSize scrollPicSize = ScriptParser::getSizeFromPlist(plistDic,"scrollPic");
        CCPoint scrollPicPosition = ScriptParser::getPositionFromPlist(plistDic,"scrollPic");
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

void S131More::newsMenuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S13News::create());
    
    switch (aItem->getTag())
    {
        case btnTag:
            newScene->addChild(S13News::create());
            
            break;
        case btnTag+1:
            newScene->addChild(S13News::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));
    
}
void S131More::showDetail(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S132Detail::create());
    
    switch (aItem->getTag())
    {
        case btnTag:
            newScene->addChild(S132Detail::create());
            
            break;
        case btnTag+1:
            newScene->addChild(S132Detail::create());
            
            break;
            
        default:
            break;
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0f, newScene));
    
}
void S131More::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
    if (AppDelegate::S1NewsSelected == btnTag10000+1)
    {
        AppDelegate::S1NewsSelected = cell->getIdx()+btnTag+1;
    }
    else
    {
         AppDelegate::S1NewsSelected = cell->getIdx()+btnTag1000+1;
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S132Detail::create());
   
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.0, newScene));
    
    
}

CCSize S131More::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    /*
    const char * labelStr = rightBigTitle[PersonalApi::convertIntToString(idx)].c_str();
    float titleFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"rightBigTitle");
    CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, titleFontSize);
    
    const char * labelStr2 = rightDetailTitle[PersonalApi::convertIntToString(idx)].c_str();
    float titleFontSize2 = ScriptParser::getFontSizeFromPlist(plistDic,"rightTitleDetail");
    CCLabelTTF *pLabel2 = CCLabelTTF::create(labelStr2, s1FontName_macro, titleFontSize2);
    */
    float size1 = 100;//pLabel->getContentSize().height;
    float size2 = 0;//pLabel2->getContentSize().height;

    return CCSizeMake(table->getContentSize().width, size1+size2);
    
}

CCTableViewCell* S131More::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        CCSprite *pSprite1 = CCSprite::create("S13PRightPoint.png");
        pSprite1->setPosition(ccp(0,90));
        pSprite1->setTag(1010);
        pCell->addChild(pSprite1);
        
        string aStr = rightBigTitle[PersonalApi::convertIntToString(idx+1)]+"        "+rightTime[PersonalApi::convertIntToString(idx+1)];
        const char * labelStr = aStr.c_str();//rightBigTitle[PersonalApi::convertIntToString(idx+1)].c_str();
        float titleFontSize = 20;
        CCSize titleDetailSize = CCSizeMake(500, 30);
        CCLabelTTF *pLabel = CCLabelTTF::create(labelStr, s1FontName_macro, titleFontSize, titleDetailSize, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        pLabel->setTag(234);
        pLabel->setPosition(ccp(280,180));
        pLabel->setColor(ccBLACK);
        pCell->addChild(pLabel);
        
        const char * labelStr2 = rightDetailTitle[PersonalApi::convertIntToString(idx+1)].c_str();
        float titleFontSize2 =  20;
        CCSize titleDetailSize2 = CCSizeMake(500, 30);
        CCLabelTTF *pLabel2 = CCLabelTTF::create(labelStr2, s1FontName_macro, titleFontSize2, titleDetailSize2, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
        pSprite1->setAnchorPoint(ccp(0.0,1.0));
        pLabel2->setTag(567);
        pLabel2->setPosition(ccp(280,130));
        pLabel2->setColor(ccBLACK);
        pCell->addChild(pLabel2);
        
 
        CCSprite *pSprite2 = CCSprite::create("s131RightWordBottom.png");
        pSprite2->setAnchorPoint(CCPointZero);
        pSprite2->setTag(999);
        pSprite2->setPosition(ccp(0,0));
        pCell->addChild(pSprite2);
    }
    else
    {
      
        
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(234);
        pLabel->setString((rightBigTitle[PersonalApi::convertIntToString(idx)]+"        "+rightTime[PersonalApi::convertIntToString(idx)]).c_str());
        
        CCLabelTTF *pLabel2 = (CCLabelTTF*)pCell->getChildByTag(567);
        pLabel2->setString(rightDetailTitle[PersonalApi::convertIntToString(idx)].c_str());
        
    }

    return pCell;
}

unsigned int S131More::numberOfCellsInTableView(CCTableView *table)
{
    return rightBigTitle.size()-2;
}

