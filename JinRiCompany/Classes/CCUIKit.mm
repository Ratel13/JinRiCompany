//
//  CCUIKit.cpp
//  GreTest
//
//  Created by lyy on 13-7-23.
//
//

#include "CCUIKit.h"
#include "CCUITextView.h"
#include "AppDelegate.h"

#define visibleSize CCDirector::sharedDirector()->getVisibleSize()//ø… ”«¯”Úsize


static CCUITextView *g_CCUITextView=nil;



CCUIKit::CCUIKit()
{
    ;
}



CCUIKit::~CCUIKit()
{
    
    //[g_CCUITextView release];
    
}




bool CCUIKit::creatWithRect(CCRect rect,CCLayer * layer)
{
    
    if ( !CCLayer::init() )
    {
        
        return false;
        
    }
    //setTouchEnabled(true);
    aLayer = layer;
    
    g_CCUITextView = [[CCUITextView alloc] init];
    CGRect aRect = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    [g_CCUITextView setLayerTextView:this Rect:aRect];
    
    return true;
    
}

void CCUIKit::removeTextView(int tag)
{
    if (AppDelegate::isTextViewExist)
    {
        [g_CCUITextView removeTextView:(1)];
        AppDelegate::isTextViewExist = true;
    }

}

void CCUIKit::setTextViewString(std::string text)
{
    if (g_CCUITextView)
    {
        [g_CCUITextView setText:(text)];
    }
    
}
void CCUIKit::setFirstResponder(bool isFirstResponder)
{
    [g_CCUITextView setFirstResponder:isFirstResponder];
}
void CCUIKit::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    setFirstResponder(true);
}
void CCUIKit::beginEdit(std::string str)
{
    
    aLayer->setPosition(ccp(aLayer->getPosition().x,aLayer->getPosition().y+200));
    g_CCUITextView.textView.frame = CGRectMake(g_CCUITextView.textView.frame.origin.x,g_CCUITextView.textView.frame.origin.y-200,g_CCUITextView.textView.frame.size.width,g_CCUITextView.textView.frame.size.height);
    
    AppDelegate::S51TextViewStr = str;
    isEditing = true;
    
   
}
void CCUIKit::endEdit(std::string str)
{
    aLayer->setPosition(ccp(aLayer->getPosition().x,aLayer->getPosition().y-200));
    g_CCUITextView.textView.frame = CGRectMake(g_CCUITextView.textView.frame.origin.x,g_CCUITextView.textView.frame.origin.y+200,g_CCUITextView.textView.frame.size.width,g_CCUITextView.textView.frame.size.height);
    //[g_CCUITextView.textView setAlpha:0.1];
    AppDelegate::S51TextViewStr = str;
    
   isEditing = false;
    
}



