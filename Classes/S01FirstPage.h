//
//  S01FirstPage.h
//  JinRiCompany
//
//  Created by lyy on 13-7-26.
//
//

#ifndef __JinRiCompany__S01FirstPage__
#define __JinRiCompany__S01FirstPage__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S0FirstPage.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S01FirstPage : public S0FirstPage, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S01FirstPage);
private:
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;

    CCTableView * pTableView;
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    map<string, string> showStrMap;
    
    int showStrMapSize;
    float scrollDistance;
    int   scrollTimes;
    void pTableViewScroll();
};

#endif /* defined(__JinRiCompany__S01FirstPage__) */
