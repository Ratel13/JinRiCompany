//
//  S131More.h
//  GreTest
//
//  Created by lyy on 13-6-24.
//
//

#ifndef __GreTest__S131More__
#define __GreTest__S131More__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S131More : public S1JinRiShangPin, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S131More);
private:
    CCDictionary* plistDic;
    void newsMenuCallback(CCObject* pSender);
    void showDetail(CCObject* pSender);
    
    map<string, string> rightBigTitle;
    map<string, string> rightDetailTitle;
    map<string, string> rightTime;
    
    CCTableView * pTableView;
    
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
    
};

#endif /* defined(__GreTest__S131More__) */
