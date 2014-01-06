//
//  S22PicDetail.h
//  JinRiCompany
//
//  Created by lyy on 13-6-25.
//
//

#ifndef __JinRiCompany__S22PicDetail__
#define __JinRiCompany__S22PicDetail__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S2ZiBu.h"

class S22PicDetail : public S2ZiBu, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    static cocos2d::CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S22PicDetail);
private:
    cocos2d::CCDictionary* plistDic;
   
    std::map<std::string, std::string> showPicMap;
    std::map<std::string, std::string> showStrMap;
    
    std::vector<float> picWidthVec;
    std::map<std::string, std::string> allScrollPicMap;
    int picIndex;
    std::string bigPicName;
    std::string productTitle;
    std::string productWeight;
    float onePicLineWidth;
    float scrollMaxSizeX;
    float scrollMaxSizeY;
    float countOffSet;
    float OffSetX;
    float scrollViewWidth;
    
    void showBigPic(CCObject* pSender);
    void S2menuCallback(CCObject* pSender);
    void back(CCObject *pSender);
    
    CCMenuItemImage * S22BigImgSp;
    CCSprite * tableViewBackGroundSp;
    CCTableView * pTableView;
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    //networking downloding
    CCLabelTTF *productNameLabel;
    CCLabelTTF *productNameLabel1;
    
};
#endif /* defined(__JinRiCompany__S22PicDetail__) */
