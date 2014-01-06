//
//  S12Leader.h
//  GreTest
//
//  Created by lihex on 6/23/13.
//
//

#ifndef GreTest_S12Leader_h
#define GreTest_S12Leader_h

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S1JinRiShangPinScene.h"

using namespace cocos2d;
using namespace std;
using namespace extension;
class S12Leader : public S1JinRiShangPin, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S12Leader);
private:
    
    CCDictionary* plistDic;
    void menuCallback(CCObject* pSender);
    map<string, string> showPicMap;
    map<string, string> showStrMap;
    
    //networking downloding
    virtual void DownLoadFinish();
    virtual void UpDate();
    virtual void refreshDownLoadingData(bool isCompleted);
    std::map<string, string> loopPicNameMap;
    //networking downloding
    CCSize demission;
    float fntSize;    
    CCTableView * pTableView;
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    virtual void scrollViewDidScroll(CCScrollView* view) {};
    virtual void scrollViewDidZoom(CCScrollView* view) {};
};



#endif
