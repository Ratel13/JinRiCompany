
//  S22PicDetail.cpp
//  JinRiCompany
//
//  Created by lyy on 13-6-25.
//
//

#include "S22PicDetail.h"
#include "AppMacros.h"
#include "ScriptParser.h"
#include "PersonalApi.h"
#include "AppDelegate.h"

#include "S24AutoPlay.h"
#include "S21ZiBuLei.h"
#include "FDMenu.h"
#define visibleSize CCDirector::sharedDirector()->getVisibleSize()
#define origin CCDirector::sharedDirector()->getVisibleOrigin()

#define s1FontName_macro "Arial"

#define classPlistName_macro "S22PicDetail"
#define zNum 100
#define btnTag 100


using namespace cocos2d;
using namespace std;
using namespace extension;

CCScene* S22PicDetail::scene()
{
	CCScene * scene = NULL;
	do
	{
		scene = CCScene::create();
		S22PicDetail *layer = S22PicDetail::create();
		scene->addChild(layer);
	} while (0);
    
	return scene;
}

bool S22PicDetail::initInfo2()
{
    bool bRet = false;
	do
	{
        AppDelegate::sceneId = classPlistName_macro;
        string plistStr = classPlistName_macro;
        plistStr += ".plist";
        plistDic = CCDictionary::createWithContentsOfFile(plistStr.c_str());
    
       
        bRet = true;
	} while (0);
    
	return bRet;
}
//networking downloding
void S22PicDetail::UpDate()
{
    string detailClassName ="http://www.jrsp.cn/app/jproduct.php?a=show&type1="+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+"&type2="+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected);

    ConnetToUrl(detailClassName,"","");//"http://www.jrsp.cn/app/jproduct.php?a=show&type1=1&type2=1&type3=1","","");
}

void S22PicDetail::refreshDownLoadingData(bool isCompleted)
{
    AppDelegate::loadingLabel->setString("");
    if (isCompleted)
    {
        string detailClassName ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"ZiBuLei";
        string currentClassName(detailClassName.c_str());
        string version = currentClassName+"version";
        string newVersion = currentClassName+"newVersion";
        CCUserDefault::sharedUserDefault()->setStringForKey(version.c_str(), CCUserDefault::sharedUserDefault()->getStringForKey(newVersion.c_str()));
    }
    
    CCScene *newScene = CCScene::create();
    newScene->addChild(S22PicDetail::create());
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.0f, newScene));
 
}
void S22PicDetail::DownLoadFinish()
{
    
    int nbegin=3;
	m_strUrlContent=m_strUrlContent.substr(nbegin,m_strUrlContent.length()-nbegin);
	CDataConvert dataConvert;
	m_strUrlContent=dataConvert.UTF8ToGB(m_strUrlContent.c_str());
    
    
	Json* root= Json_create(m_strUrlContent.c_str());
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    string detailClassName ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"ZiBuLei";
    
    string currentClassName(detailClassName.c_str());
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
        
    //CCLOG("versionStr1=%s,versionStr2=%s",CCUserDefault::sharedUserDefault()->getStringForKey(version.c_str()).c_str(),versionStr.c_str());
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
    
    Json* root_displayPicture=Json_getItem(root,"product");
    
    if (root_displayPicture && root_displayPicture->type==Json_Array)
    {
        Json* json_child=root_displayPicture->child;
        map<string, string> titleMap;
        map<string, string> weightMap;
        int index = 0;
        while (json_child)
        {
            
            Json* child_title=Json_getItem(json_child,"title");
            Json* child_weight=Json_getItem(json_child,"weight");
            Json* child_pic_url=Json_getItem(json_child,"img2");
            
            if (child_pic_url)
            {
                char szsamllpicname[512]={0};
                sprintf(szsamllpicname, "S2%d%dDisplay%d.png",AppDelegate::S2SelectedScene,AppDelegate::S2LeftSelected,index+1);
                
                DownLoadFile(child_pic_url->valuestring,szsamllpicname);
                
                
                string titleStr = child_title->valuestring;
                string weightStr = child_weight->valuestring;
                
                titleMap[PersonalApi::convertIntToString(index+1)] = titleStr;
                weightMap[PersonalApi::convertIntToString(index+1)] = weightStr;
                index++;
            }
            json_child=json_child->next;
        }
        /*
         for(map<string, string>::iterator iter=valueMap.begin();iter!=valueMap.end();++iter)
         {
         CCLOG("3333==%s",iter->second.c_str());
         }
         */
        string titleStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Title";
        PersonalApi::wirteVecToXml(titleMap,titleStr);
        
        string weightlStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Weight";
        PersonalApi::wirteVecToXml(weightMap,weightlStr);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    checkPicDownLoading();
    /////////////////////////////////////////////////////////////////////////////
    
}

bool S22PicDetail::setUpSubClass2()
{
	bool bRet = false;
	do
	{
        AppDelegate::S2isInParent = false;
        
        AppDelegate::S22Selected = AppDelegate::S2SelectedPicNum;
        string titleStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Title";
        titleMap = PersonalApi::getRealGroupStringMap(plistDic,titleStr.c_str(),"label");
        
        
        string weightlStr ="S2"+PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Weight";
        weightMap = PersonalApi::getRealGroupStringMap(plistDic,weightlStr.c_str(),"label");

        
        
        bigPicName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(AppDelegate::S2SelectedPicNum)+".png";
        
       bigPicName=PersonalApi::getRealImageName(bigPicName.c_str(),"S2BigPic.png").c_str();
        
        productTitle = titleMap[PersonalApi::convertIntToString(AppDelegate::S2SelectedPicNum)];
        productWeight = weightMap[PersonalApi::convertIntToString(AppDelegate::S2SelectedPicNum)];
        
        
        CCPoint S22BigImgPosition = ScriptParser::getPositionFromPlist(plistDic,"S22BigImg");
        S22BigImgSp = CCMenuItemImage::create(bigPicName.c_str(),
                                                               bigPicName.c_str(),
                                                               this,
                                                               menu_selector(S22PicDetail::showBigPic));
        S22BigImgSp->setPosition(S22BigImgPosition);
        _menu ->addChild(S22BigImgSp,zNum);
        _menu->setEnabled(true);
        
        
    
        CCPoint productNamePosition = ScriptParser::getPositionFromPlist(plistDic,"productName");
        float productNameFontSize = ScriptParser::getFontSizeFromPlist(plistDic,"productName");
        productNameLabel = CCLabelTTF::create(productTitle.c_str(), s1FontName_macro, productNameFontSize);
        productNameLabel->setPosition(productNamePosition);
        productNameLabel->setColor(ccc3(112.0,16.0,12.0));
        this->addChild(productNameLabel,zNum);
        {
			productWeight = "规格：" + productWeight;
            const char* productNameStr1 = productWeight.c_str();
            productNameLabel1 = CCLabelTTF::create(productNameStr1, s1FontName_macro, productNameFontSize);
            productNameLabel1->setPosition(ccp(productNamePosition.x,productNamePosition.y-50));
            productNameLabel1->setColor(ccc3(112.0,16.0,12.0));
            this->addChild(productNameLabel1,zNum);
        }
        
        {
            const char* productNameStr1 = "金日尚品推荐";
            CCLabelTTF *productNameLabel1 = CCLabelTTF::create(productNameStr1, s1FontName_macro, productNameFontSize);
            productNameLabel1->setPosition(ccp(productNamePosition.x+100,productNamePosition.y-200));
            productNameLabel1->setColor(ccc3(112.0,16.0,12.0));
            this->addChild(productNameLabel1,zNum);
        }
     
        tableViewBackGroundSp = CCSprite::create("S22DisplayBackground.png");
        tableViewBackGroundSp->setAnchorPoint(ccp(0.0,1.0));
        tableViewBackGroundSp->setPosition(ccp(S22BigImgSp->getPosition().x-S22BigImgSp->getContentSize().width/2,S22BigImgSp->getPosition().y-S22BigImgSp->getContentSize().height/2-10));
        this->addChild(tableViewBackGroundSp,zNum);
        
        {
        const char * imageName = "S31Back.png";
        CCMenuItemImage * backItemImage = CCMenuItemImage::create(imageName,
                                                                  imageName,
                                                                  this,
                                                                  menu_selector(S22PicDetail::back));
        
        backItemImage->setPosition(ScriptParser::getPositionFromPlist(plistDic, "back"));
        CCMenu * backMenu = CCMenu::create(NULL);
        backMenu ->setPosition(CCPointZero);
        _menu->addChild(backItemImage,zNum);
        }
        
        {
            
            CCSprite * aSprite = CCSprite::create("S22DisplayPrevBtn.png");
            aSprite->setPosition(ccp(tableViewBackGroundSp->getPosition().x+20,tableViewBackGroundSp->getPosition().y-tableViewBackGroundSp->getContentSize().height/2));
            this->addChild(aSprite,zNum);

        }
        
        {
            CCSprite * aSprite = CCSprite::create("S22DisplayPrevBtn.png");
            aSprite->setRotation(180.0);
            aSprite->setPosition(ccp(tableViewBackGroundSp->getPosition().x+tableViewBackGroundSp->getContentSize().width-20,tableViewBackGroundSp->getPosition().y-tableViewBackGroundSp->getContentSize().height/2));
            this->addChild(aSprite,zNum);
            
        }
   
        CCSize tableViewSize = ScriptParser::getSizeFromPlist(plistDic,"scrollPic");
        pTableView = CCTableView::create(this, tableViewSize);
		pTableView->setDirection(kCCScrollViewDirectionHorizontal);
		pTableView->setAnchorPoint(ccp(0.0,1.0));
        pTableView->setPosition(ScriptParser::getPositionFromPlist(plistDic,"scrollPic"));
        pTableView->setPosition(ccp(pTableView->getPosition().x+10,pTableView->getPosition().y+16));
		pTableView->setDelegate(this);
		pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView,zNum);
		pTableView->reloadData();
        

		bRet = true;
	} while (0);
    
	return bRet;
}
void S22PicDetail::S2menuCallback(CCObject* pSender)
{
    CCMenuItemSprite *aItem = (CCMenuItemSprite *)pSender;
    
    switch (aItem->getTag())
    {
        case btnTag:
            ;
            break;
        case btnTag+1:
            //newScene->addChild(S13News::create());
            
            break;
            
        default:
            break;
    }
}


void S22PicDetail::showBigPic(CCObject* pSender)
{
    CCScene *newScene = CCScene::create();
    newScene->addChild(S24AutoPlay::create());
    CCDirector::sharedDirector()->replaceScene(newScene);
    
}

void S22PicDetail::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
    AppDelegate::S22Selected = cell->getIdx()+1;
    string picName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(cell->getIdx()+1)+".png";
    
    string picNameStr=PersonalApi::getRealImageName(picName.c_str(),"S2BigPic.png").c_str();
   
    CCSprite *pSprite = CCSprite::create(picNameStr.c_str());
    
    S22BigImgSp->setNormalImage(pSprite);
    S22BigImgSp->setSelectedImage(pSprite);
    S22BigImgSp->setDisabledImage(pSprite);
    productTitle = titleMap[PersonalApi::convertIntToString(cell->getIdx()+1)];
    productNameLabel ->setString(productTitle.c_str());
    productWeight = weightMap[PersonalApi::convertIntToString(cell->getIdx()+1)];
    productWeight = "规格："+productWeight;
    const char* productNameStr1 = productWeight.c_str();
    productNameLabel1 ->setString(productNameStr1);
}

CCSize S22PicDetail::tableCellSizeForIndex(CCTableView *table,unsigned int idx)
{
    string picName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(idx+1)+".png";
    
    string picNameStr=PersonalApi::getRealImageName(picName.c_str(),"S2BigPic.png").c_str();
        CCSprite *pSprite = CCSprite::create(picNameStr.c_str());
    float pSpriteScale = tableViewBackGroundSp->getContentSize().height/pSprite->getContentSize().height;
    return CCSizeMake(tableViewBackGroundSp->getContentSize().width*pSpriteScale/2, tableViewBackGroundSp->getContentSize().height*pSpriteScale/2);
}

CCTableViewCell* S22PicDetail::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell)
    {
        
        pCell = new CCTableViewCell();
        pCell->autorelease();
        
        string picName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(idx+1)+".png";
        
        
        string picNameStr=PersonalApi::getRealImageName(picName.c_str(),"S2BigPic.png").c_str();
        CCSprite *pSprite = CCSprite::create(picNameStr.c_str());
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setTag(123);
        
        float pSpriteScale = tableViewBackGroundSp->getContentSize().height/pSprite->getContentSize().height;
        pSprite->setScale(pSpriteScale);
        pSprite->setPosition(ccp(0,pSprite->getPosition().y-pSprite->getContentSize().height*pSpriteScale/2));
        
        pCell->addChild(pSprite);
   
    }
    else
    {
        CCSprite *pSprite = (CCSprite*)pCell->getChildByTag(123);
        string picName = "S2"+ PersonalApi::convertIntToString(AppDelegate::S2SelectedScene)+ PersonalApi::convertIntToString(AppDelegate::S2LeftSelected)+"Display"+PersonalApi::convertIntToString(idx+1)+".png";
        
        string picNameStr=PersonalApi::getRealImageName(picName.c_str(),"S2BigPic.png").c_str();
        pSprite->setTexture(CCTextureCache::sharedTextureCache()->addImage(picNameStr.c_str()));
    }
    return pCell;
}

unsigned int S22PicDetail::numberOfCellsInTableView(CCTableView *table)
{
    return titleMap.size()-1;
}

void S22PicDetail::back(CCObject *pSender)
{
    AppDelegate::S2isInParent = true;
    CCScene *newScene = CCScene::create();
    newScene->addChild(S21ZiBuLei::create());
    CCDirector::sharedDirector()->replaceScene((CCTransitionFade::create(0.0f, newScene)));
}
