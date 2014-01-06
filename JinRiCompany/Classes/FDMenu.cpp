#include "FDMenu.h"

USING_NS_CC;
#include "cocos-ext.h"

using namespace extension;

FDMenu* FDMenu::create()
{
	return FDMenu::create(NULL, NULL);
}

FDMenu * FDMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    FDMenu *pRet = new FDMenu();
    CCArray* pArray = NULL;
   
    pArray = CCArray::create(item, NULL);
    if (pRet && pRet->initWithArray(pArray))//->initWithItems(item, args))
    {
        pRet->autorelease();
        va_end(args);
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}

FDMenu* FDMenu::create(CCArray* pArrayOfItems)
{
	FDMenu *pRet = new FDMenu();
	if (pRet && pRet->initWithArray(pArrayOfItems))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

//重写registerWithTouchDispatcher
void FDMenu::registerWithTouchDispatcher()
{
	//这里优先级设为1，只要比CCScrollView低就可以
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}