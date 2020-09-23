//
//  DisplayGrid.cpp
//  cocos2d
//
//  Created by alexandre gimeno on 18/09/2020.
//

#include "DisplayGrid.hpp"
#include "../Models/StaticGrid.hpp"

USING_NS_CC;

DisplayGrid* DisplayGrid::create()
{
    DisplayGrid* ret = new (std::nothrow) DisplayGrid();
    if(ret && ret->init ())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        return nullptr;
    }
}

bool DisplayGrid::init()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gameScreenAssets.plist");
    
    auto gridContainer = Node::create();
    this->addChild(gridContainer, 1);
    
    
    auto gridButtonsMenu = Menu::create();
    gridButtonsMenu->setPosition(Vec2::ZERO);
    gridContainer->addChild(gridButtonsMenu, 2);
    
    srand((unsigned)time(NULL));
    
    //init gird display
    for(int l = 0; l < GRID_SIZE + 1; l++)
    {
        for(int c = 0; c < GRID_SIZE + 1; c++)
        {
            std::string gridCornerCaseName = cornerName(l, c);
            
            cocos2d::Vec2 positionLC  = cocos2d::Vec2(l, c);
            cocos2d::Vec2 positionXY  = StaticGrid::getPositionXY(positionLC);
            
            //add grid button
            if(gridArray[l][c] != 0 && l < GRID_SIZE && c < GRID_SIZE)
            {
                int buttonColor = rand() % 6;
                
                auto gridBtnNormal = Sprite::createWithSpriteFrameName("grid_button_normal_" + std::to_string(buttonColor) + "@2x.png");
                auto gridBtnSelected = Sprite::createWithSpriteFrameName("grid_button_selected_" + std::to_string(buttonColor) + "@2x.png");
                auto gridBtn = MenuItemSprite::create(
                                                     gridBtnNormal,
                                                     gridBtnSelected,
                                                     CC_CALLBACK_1(DisplayGrid::gridButtonCallback, this, l, c));
                
                gridBtn->setPosition(Vec2(positionXY.x, positionXY.y - BTN_SHIFT_HEIGHT));
                
                gridButtonsMenu->addChild(gridBtn);
            }
          
            //add back backDisplayGrid
            if(gridCornerCaseName != "0000")
            {
                auto backDisplayGrid = Sprite::createWithSpriteFrameName("grid_down_" + gridCornerCaseName + "@2x.png");
            
                int gridW = backDisplayGrid->getContentSize().width;
                int gridH = backDisplayGrid->getContentSize().height;
                
                backDisplayGrid->setPosition(Vec2(positionXY.x - gridW/2, positionXY.y + gridH/2));
                gridContainer->addChild(backDisplayGrid, 1);
            }
            
            //add top topDisplayGrid
            if(gridCornerCaseName != "0000" && gridCornerCaseName != "1111")
            {
                auto topDisplayGrid = Sprite::createWithSpriteFrameName("grid_up_" + gridCornerCaseName + "@2x.png");
                
                int gridW = topDisplayGrid->getContentSize().width;
                int gridH = topDisplayGrid->getContentSize().height;
                
                topDisplayGrid->setPosition(Vec2(positionXY.x - gridW/2, positionXY.y + gridH/2));
                gridContainer->addChild(topDisplayGrid, 3);
            }
        }
    }
    
    return true;
}

void DisplayGrid::gridButtonCallback(cocos2d::Ref* pSender, int line, int collumn)
{
    std::vector<int> lineCollumn = {line, collumn};
    _eventDispatcher->dispatchCustomEvent("GRID_BTN_PUSH", &lineCollumn);
}

std::string DisplayGrid::cornerName(int line, int collumn)
{
    int cornerLeftUp = gridArray[line-1][collumn-1];
    int cornerRigthUp = gridArray[line-1][collumn];
    int cornerRigthDown = gridArray[line][collumn];
    int cornerLeftDown = gridArray[line][collumn-1];
    
    if(line-1 < 0)
    {
        cornerLeftUp = 0;
        cornerRigthUp = 0;
    }
    if(line >= GRID_SIZE)
    {
        cornerRigthDown = 0;
        cornerLeftDown = 0;
    }
    if(collumn-1 < 0)
    {
        cornerLeftUp = 0;
        cornerLeftDown = 0;
    }
    if(collumn >= GRID_SIZE)
    {
        cornerRigthUp = 0;
        cornerRigthDown = 0;
    }
    
    std::string result = std::to_string(cornerLeftUp) +
                         std::to_string(cornerRigthUp) +
                         std::to_string(cornerRigthDown) +
                         std::to_string(cornerLeftDown);
    
    return result;
}
