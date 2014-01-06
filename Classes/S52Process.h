//
//  S52Process.h
//  jinRiCompany
//
//  Created by lyy on 13-6-28.
//
//

#ifndef __jinRiCompany__S52Process__
#define __jinRiCompany__S52Process__

#include "cocos2d.h"
#include <string.h>
#include "cocos-ext.h"

#include "S5DingGou.h"

using namespace cocos2d;
using namespace std;
using namespace extension;

class S52Process : public S5DingGou, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
    static CCScene* scene();
    virtual bool initInfo2();
    virtual bool setUpSubClass2();
    CREATE_FUNC(S52Process);
private:
    CCDictionary* plistDic;
    
    map<string, string> showPicMap;
    map<string, string> showStrMap;
    
    void S2menuCallback(CCObject* pSender);
    void S2back(CCObject* pSender);
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
    std::map<string, string> loopPicNameMap;
    //networking downloding
    
};
#endif /* defined(__jinRiCompany__S52Process__) */
