//
//  SPWebView.h
//  sharkHelpme
//
//  Created by YAN SUSHI on 13-6-28.
//
//

#ifndef __sharkHelpme__SPWebView__
#define __sharkHelpme__SPWebView__

#include <iostream>


#include "cocos2d.h"
using namespace cocos2d;

class SPWebView:public CCLayer
{
public:
    SPWebView();
    ~SPWebView();
    
    void* addWebView(const char *str_url,CCRect &rect);
    void addWebViewWithCloseButton(const char *str_url,CCRect &rect);
    void addAdstirWebView(const char *str_media_id,const char *str_spot_no,CCRect &rect);
    void HideWebViewWithTag(int view_tag);
    float getScreenWidthSize();
    void addGFCView(const char *str_site_id);
    void* addRoundWebView(const char *str_url,CCRect &rect);
    void removeUIView(int view_tag);

    
    //void addUITextView(const char *setPlaceHolder,CCRect &rect,float fontSize);
};

#endif /* defined(__sharkHelpme__SPWebView__) */
