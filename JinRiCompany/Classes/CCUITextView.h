//
//  CCUITextView.h
//  GreTest
//
//  Created by lyy on 13-7-23.
//
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import "CCUIKit.h"

@interface CCUITextView : NSObject<UITextViewDelegate>
{
    CCUIKit * mCCUIKit;
    
    UITextView * textView;
}

@property (nonatomic, retain) UITextView *textView;

-(void) setLayerTextView:(CCUIKit *)aCCUIKit Rect : (CGRect) rect;

-(void) setTextViewFrame:(CCRect)rect;

-(void) removeTextView:(int)tag;

-(void) setText:(std::string) text;

-(void) setFirstResponder:(bool) isFirstResponder;

@end