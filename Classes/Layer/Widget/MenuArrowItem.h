//
//  MenuArrowItem.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__MenuArrowItem__
#define __solno__MenuArrowItem__

#include <stdio.h>
#include <cocos2d.h>

enum class ArrowInputEvent
{
    PRESS_UP,
    PRESS_RIGHT,
    PRESS_DOWN,
    PRESS_LEFT,
    
    RELEASE_UP,
    RELEASE_RIGHT,
    RELEASE_DOWN,
    RELEASE_LEFT,
};

class MenuArrowItem : public cocos2d::MenuItemSprite
{
public:
    MenuArrowItem(std::string direction);
    static MenuArrowItem* create(std::string direction);
    virtual void selected();
    virtual void unselected();
    virtual void update(float dt);
    
private:
    std::string _direction;
};

#endif /* defined(__solno__MenuArrowItem__) */
