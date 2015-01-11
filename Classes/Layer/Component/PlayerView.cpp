//
//  PlayerView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/05.
//
//

#include "PlayerView.h"

USING_NS_CC;

PlayerView* PlayerView::create()
{
    auto ret = new PlayerView();
    if (ret && ret->init()) {
        ret->autorelease();
        
        // スプライトアニメーションの読み込みと登録
        auto frame_cache = SpriteFrameCache::getInstance();
        frame_cache->addSpriteFramesWithFile("chara/hiroine.plist", "chara/hiroine_3232.png");
        auto cache  = AnimationCache::getInstance();
        cache->addAnimationsWithFile("chara/animations.plist");
        auto animation = cache->getAnimation("down_anime");
        auto animate   = Animate::create(animation);
        animate->setTag(IDLING_ANIMATE);
        ret->runAction(animate);
    } else {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void PlayerView::setIdlingAnimate(std::string direction)
{
    // 既存のアニメーションを止める
    stopActionByTag(IDLING_ANIMATE);
    
    auto anime_name = direction + "_anime";
    auto animation  = AnimationCache::getInstance()->getAnimation(anime_name.c_str());
    auto animate    = Animate::create(animation);
    animate->setTag(IDLING_ANIMATE);
    runAction(animate);
}

void PlayerView::runMoveAction(Point move_vec)
{
    auto move_action = MoveBy::create(0.3f, move_vec);
    auto moved_action = CallFunc::create([=]() {
        if (after_move_action.size() == 0) {
            return ;
        }
        
        auto seq = Sequence::create(after_move_action);
        auto after = CallFunc::create([=]{
            after_move_action.clear();
        });
        
        this->runAction(Sequence::create(seq, after, NULL));
    });
    auto action = Sequence::create(move_action, moved_action, NULL);
    action->setTag(MOVE_SEQUENCE);
    
    this->runAction(action);
}

bool PlayerView::isRunnningMoveAction()
{
    auto running_action = this->getActionByTag(MOVE_SEQUENCE);
    if (running_action && !running_action->isDone()) {
        return true;
    }
    return false;
}

void PlayerView::addRunActionAfterMove(cocos2d::FiniteTimeAction *action)
{
    after_move_action.pushBack(action);
}