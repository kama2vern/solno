//
//  MakeMenuState.h
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#ifndef __solno__MakeMenuState__
#define __solno__MakeMenuState__

#include <iostream>
#include "StateBase.h"

#include "Item.h"

class MakeMenuState : public StateBase
{
public:
    static MakeMenuState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<Item*>, item_list, ItemList);
    CC_SYNTHESIZE(int, current_item_idx, CurrentItemIndex);
};

#endif /* defined(__solno__MakeMenuState__) */
