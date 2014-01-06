//
//  FDMenu.h
//  jinRiCompany
//
//  Created by lyy on 13-6-30.
//
//

#ifndef __jinRiCompany__FDMenu__
#define __jinRiCompany__FDMenu__

#include "cocos2d.h"
#include "menu_nodes/CCMenu.h"

USING_NS_CC;
class FDMenu : public CCMenu
{
public:
	/** creates an empty CCMenu */
	static FDMenu* create();

	/** creates a CCMenu with it's items */
	static FDMenu* create(CCMenuItem* item, ...);

	/** creates a CCMenu with a CCArray of CCMenuItem objects */
	static FDMenu* create(CCArray* pArrayOfItems);

	virtual void registerWithTouchDispatcher();
};

#endif