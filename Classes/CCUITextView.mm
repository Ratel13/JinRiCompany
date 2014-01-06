//
//  CCUITextView.cpp
//  GreTest
//
//  Created by lyy on 13-7-23.
//
//

#include "CCUITextView.h"

#import "CCUIKit.h"

#import "EAGLView.h"
using namespace std;

@implementation CCUITextView
@synthesize textView;
- (id)init
{
    
    self = [super init];
    
    if (self)
    {
        
        // init code here.
        
    }
    
    return self;
    
}

- (void)dealloc
{
    
    [textView release];
    
    [super dealloc];
    
}

-(void) setLayerTextView:(CCUIKit *)aCCUIKit Rect : (CGRect) rect;
{
    mCCUIKit = aCCUIKit;
    self.textView = [[[UITextView alloc] initWithFrame:rect] autorelease]; //初始化大小并自动释放
    
    self.textView.textColor = [UIColor blackColor];//设置textview里面的字体颜色
    
    self.textView.font = [UIFont fontWithName:@"Arial" size:18.0];//设置字体名字和字体大小
    
    self.textView.delegate = self;//设置它的委托方法
    
    self.textView.backgroundColor = [UIColor whiteColor];//设置它的背景颜色
    
    
    
    self.textView.text = @"";//设置它显示的内容
    
    self.textView.returnKeyType = UIReturnKeyDefault;//返回键的类型
    
    self.textView.keyboardType = UIKeyboardTypeDefault;//键盘类型
    
    self.textView.scrollEnabled = YES;//是否可以拖动
    
    
    
    self.textView.autoresizingMask = UIViewAutoresizingFlexibleHeight;//自适应高度
    
    //[self.textView setAlpha:0.1];
   
    [[EAGLView sharedEGLView] addSubview:self.textView];
    
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    NSLog(@"begin");
    NSString * textStr = self.textView.text;
    string str = [textStr UTF8String];
    mCCUIKit->beginEdit(str);
    
}
- (void)textViewDidEndEditing:(UITextView *)textView
{
    NSLog(@"end");
    NSString * textStr = self.textView.text;
    NSLog(@"%@",textStr);
    string str = [textStr UTF8String];
   mCCUIKit->endEdit(str);
}


-(BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    if ([text isEqualToString:@"\n"])
    {
        //[self.textView resignFirstResponder];
        return YES;
    }
    return YES;
}
-(void) setTextViewFrame:(CCRect)rect
{
    CGRect aRect = CGRectMake(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    textView.frame = aRect;
}
- (void)removeTextView:(int)tag
{
    [textView removeFromSuperview];  
}
-(void) setText:(std::string) text
{
    NSString * textStr = [NSString stringWithUTF8String:text.c_str()];
    
    [self.textView setText:textStr];
}

-(void) setFirstResponder:(bool) isFirstResponder
{
    [self.textView resignFirstResponder];
}


@end