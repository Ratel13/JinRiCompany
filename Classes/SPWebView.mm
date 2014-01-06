//
//  SPWebView.mm
//  sharkHelpme
//
//  Created by YAN SUSHI on 13-6-28.
//
//

#include "SPWebView.h"
#import <Foundation/Foundation.h>

#import <CoreLocation/CoreLocation.h>

#import <UIKit/UIKit.h>

#import "EAGLView.h"

//#import "ads/AdstirWebView.h"

//#import "GameFeatKit/GFController.h"



enum tag_views
{
    tag_webView = 84110
};

SPWebView::SPWebView()
{
    
}

SPWebView::~SPWebView()
{
    
}

void* SPWebView::addWebView(const char *str_url,CCRect &rect)
{
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    
    float scale_factor = glView.contentScaleFactor;
    UIWebView *webView = (UIWebView*)[glView viewWithTag:this->getTag()];
    if(!webView){
        webView = [[UIWebView alloc] initWithFrame:CGRectMake(rect.origin.x/scale_factor,rect.origin.y/scale_factor,rect.size.width/scale_factor,rect.size.height/scale_factor)];
        [glView addSubview:webView];
        [webView release];
        
        NSString *urlBase = [NSString stringWithCString:str_url encoding:NSUTF8StringEncoding];
        
        [webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlBase ]]];
        
        [webView setUserInteractionEnabled:YES]; //don't let the user scroll while things are
        
        //useful when get removed
        webView.tag = this->getTag();
    }
    else
    {
        webView.hidden = NO;
    }
    return webView;
}

void* SPWebView::addRoundWebView(const char *str_url,CCRect &rect)
{
    UIWebView *webView = (UIWebView *)this->addWebView(str_url, rect);
    [webView.layer setCornerRadius:8.0f];
    webView.clipsToBounds = YES;
    return webView;
}

void SPWebView::addWebViewWithCloseButton(const char *str_url,CCRect &rect)
{
    UIWebView *webView = (UIWebView *)this->addWebView(str_url, rect);
    
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    
    float scale_factor = glView.contentScaleFactor;
    
    //loat scale_factor = glView.contentScaleFactor;
    UIButton *btn_close = [[UIButton alloc] initWithFrame:CGRectMake(rect.size.width/scale_factor-25, 0, 25, 25)];
    [btn_close setImage:[UIImage imageNamed:@"S31Back.png"] forState:UIControlStateNormal];
    [glView addSubview:btn_close];
    
    
    [btn_close release];
    
    
    [btn_close addTarget:webView action:@selector(removeFromSuperview) forControlEvents:UIControlEventTouchUpInside];
    [btn_close addTarget:btn_close action:@selector(removeFromSuperview) forControlEvents:UIControlEventTouchUpInside];
    
}


void SPWebView::addAdstirWebView(const char *str_media_id,const char *str_spot_no,CCRect &rect)
{
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    
    //already added
    if([glView viewWithTag:this->getTag()])
    {
        return;
    }
    
     float scale_factor = glView.contentScaleFactor;
    //mask layer
    
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(rect.origin.x/scale_factor,rect.origin.y/scale_factor,rect.size.width/scale_factor,rect.size.height/scale_factor)];
    [view setBackgroundColor:[UIColor blackColor]];
    [glView addSubview:view];
    [view release];
    
   
    
    //loat scale_factor = glView.contentScaleFactor;
    
    
    
    NSString *media_id = [NSString stringWithCString:str_media_id encoding:NSUTF8StringEncoding];
    NSString *spot_id = [NSString stringWithCString:str_spot_no encoding:NSUTF8StringEncoding];
   /*
    AdstirWebView *view_adstir = [[AdstirWebView alloc] initWithFrame:CGRectMake(rect.origin.x/scale_factor,rect.origin.y/scale_factor,rect.size.width/scale_factor,rect.size.height/scale_factor) media:media_id spot:spot_id];
    //useful when get removed
    view_adstir.tag = this->getTag();
    [glView addSubview:view_adstir];
    [view_adstir release];
*/
}

void SPWebView::addGFCView(const char *str_site_id)
{
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    UIViewController *controller =(UIViewController*)[glView nextResponder];
     NSString *site_id = [NSString stringWithCString:str_site_id encoding:NSUTF8StringEncoding];
  //  [GFController showGF:controller site_id:site_id];
}

void SPWebView::HideWebViewWithTag(int view_tag)
{
    
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    UIView *view = [glView viewWithTag:view_tag];
    //[view removeFromSuperview];
    //to avoid reloading ads
    view.hidden = YES;
    this->removeFromParent();
}
float SPWebView::getScreenWidthSize()
{
    CGRect rect_screen = [[UIScreen mainScreen]bounds];
    CGSize size_screen = rect_screen.size;
    
  
    CGFloat scale_screen = [UIScreen mainScreen].scale;
    
    return scale_screen;
}
void SPWebView::removeUIView(int view_tag)
{
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    UIView *view = [glView viewWithTag:view_tag];
    [view removeFromSuperview];
    //to avoid reloading ads
    //view.hidden = YES;
    this->removeFromParentAndCleanup(true);
}
/*
void SPWebView::addUITextView(const char *setPlaceHolder,CCRect &rect,float fontSize)
{
    EAGLView *glView = (EAGLView *)[EAGLView sharedEGLView];
    
    float scale_factor = glView.contentScaleFactor;
    
    
    UITextView * textView = [[[UITextView alloc] initWithFrame:CGRectMake(rect.origin.x/scale_factor,rect.origin.y/scale_factor,rect.size.width/scale_factor,rect.size.height/scale_factor)] autorelease]; //初始化大小并自动释放
    
    textView.textColor = [UIColor blackColor];//设置textview里面的字体颜色
    
    textView.font = [UIFont fontWithName:@"Arial" size:fontSize];//设置字体名字和字体大小
    
    //textView.delegate = self;//设置它的委托方法
    
    textView.backgroundColor = [UIColor clearColor];//设置它的背景颜色
    
    
    
   // textView.text = @"Now is the time for all good developers to come to serve their country.\n\nNow is the time for all good developers to come to serve their country.";//设置它显示的内容
    
    textView.returnKeyType = UIReturnKeyDefault;//返回键的类型
    
    textView.keyboardType = UIKeyboardTypeDefault;//键盘类型
    
    textView.scrollEnabled = YES;//是否可以拖动
    
    
    
    textView.autoresizingMask = UIViewAutoresizingFlexibleHeight;//自适应高度
    
    
    return textView;
}
*/