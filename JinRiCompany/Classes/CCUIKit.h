//
//  CCUIKit.h
//  GreTest
//
//  Created by lyy on 13-7-23.
//
//

#ifndef CCUIKit_h

#define CCUIKit_h

#include "cocos2d.h"
#include <string>
USING_NS_CC;


class CCUIKit : public CCLayer
{
    
public:
    
    CCUIKit();
    
    ~CCUIKit();
    
    virtual bool creatWithRect(CCRect rect,CCLayer * layer);
    
    CREATE_FUNC(CCUIKit);
    
    
    static void removeTextView(int tag);
    void setTextViewString(std::string text);
    void setFirstResponder(bool isFirstResponder);
    
    CCLayer * aLayer;
    std::string aTextViewStr;
    void beginEdit(std::string str);
    void endEdit(std::string str);
    
    bool isEditing;
  
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){};
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};
};  



#endif