//
//  MakeMenuState.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuState.h"

#include "UserStorageModule.h"
#include "InputModule.h"

#include "MakeMenuLayer.h"
#include "LayerManager.h"

MakeMenuState* MakeMenuState::create()
{
    auto ret = new MakeMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    ret->setCurrentItemIndex(0);
    ret->setMakeItem(nullptr);
    ret->autorelease();
    return ret;
}

void MakeMenuState::enter()
{
    // repositoryからitem list読込
    auto user_item_list = UserStorageModule::getInstance()->getAllUserItem();
    for (auto user_item : user_item_list) {
        auto item = Item::createByMaster(user_item.item_id);
        item_list.pushBack(item);
    }
    
    // ItemMenuLayerへset
    view = MakeMenuLayer::create(item_list);
    LayerManager::getInstance()->push("make_menu", view);
}

void MakeMenuState::update()
{
    auto e = InputModule::getInstance()->popEvent();
    auto p = InputModule::getInstance()->popParam();
    
    if (e == InputEvent::PRESS_ITEM_SELECT) {
        if (p < 0 || p >= item_list.size()) {
            return ;
        }
        
        auto item = item_list.at(p);
        if (current_item_idx != p) {
            current_item_idx = p;
            return ;
        }
        
        updatePreparentItem(item);
        return ;
    }
}

void MakeMenuState::exit()
{
    preparent_item_ids.clear();
    item_list.clear();
    LayerManager::getInstance()->pop();
}

void MakeMenuState::updatePreparentItem(Item *item)
{
    view->invisibleItemIconAll();
    
    preparent_item_ids.push_back(item->getItemId());
    view->setPreparentItemTexture(preparent_item_ids.size(), item->getThumbnailTexture());
    
    if (!make_item) {
        make_item = item->getMakeItem();
    }
    
    std::vector<int> indices;
    for (auto item : item_list) {
        if ((item->getItemId() == make_item->getPrepareItemId1() ||
             item->getItemId() == make_item->getPrepareItemId2() ||
             item->getItemId() == make_item->getPrepareItemId3()) &&
            (std::find(preparent_item_ids.begin(), preparent_item_ids.end(), item->getItemId()) == preparent_item_ids.end()))
        {
            auto idx = item_list.getIndex(item);
            indices.push_back(idx);
        }
    }
    
    if (!indices.empty()) {
        view->visibleItemIcons(indices);
    }
}