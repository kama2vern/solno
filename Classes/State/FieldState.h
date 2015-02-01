//
//  FieldState.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__FieldState__
#define __solno__FieldState__

#include <stdio.h>
#include <cocos2d.h>

#include "StateBase.h"

#include "InputModule.h"

enum MapColliderType {
    NO_COLLISION = 0,
    COLLIDABLE   = 17, // タイルが増えるとGIDが変わるので別途検討
};

class FieldLayer;
class ControllerLayer;
class FieldObject;
class FieldState : public StateBase {
public:
    static FieldState* create(FieldLayer* view, ControllerLayer* controller);
    FieldState(FieldLayer* view, ControllerLayer* controller);
    virtual ~FieldState();
    
    virtual void enter(int gate) override;
    virtual void update() override;
    virtual void exit() override;
    
private:
    void decideAction();
    void movePlayerCharacter(InputEvent event);
    bool isCollidable(int map_x, int map_y);
    
    cocos2d::Point player_map_pos;
    std::string player_direction;
    FieldLayer* view;
    ControllerLayer* controller;
    std::vector<FieldObject*> objects;
};

#endif /* defined(__solno__FieldState__) */
