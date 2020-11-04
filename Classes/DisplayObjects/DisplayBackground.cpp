//
//  DisplayBackground.cpp
//  demonsway
//
//  Created by alexandre gimeno on 16/09/2020.
//

#include "DisplayBackground.hpp"

USING_NS_CC;

DisplayBackground* DisplayBackground::create()
{
    //create new instance pointer
    DisplayBackground* ret = new (std::nothrow) DisplayBackground();
    if(ret && ret->init ())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

bool DisplayBackground::init()
{
    //get screen size
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int screenWidth = visibleSize.width;
    int screenHeigth = visibleSize.height;
    
    background = Node::create();
    
    //import Background image
    auto imageCenter = Sprite::createWithSpriteFrameName("background@2x.png");
    
    //get background image size
    int imageWith = imageCenter->getContentSize().width;
    int imageHeigth = imageCenter->getContentSize().height;
    
    //set the number of image per screen
    int nbrOfImagesPerLine = screenWidth / imageWith + 1;
    int nbrOfImagesPerColumn = screenHeigth / imageHeigth + 1;
    
    //create the background
    for (int c = 0; c <= nbrOfImagesPerColumn; c++)
    {
        for (int l = 0; l <= nbrOfImagesPerLine; l++)
        {
            auto image = Sprite::createWithSpriteFrameName("background@2x.png");
            image->setPosition(Vec2(imageWith * c, imageHeigth * l));
            
            background->addChild(image, 0);
        }
    }
    
    //place and add background
    background->setPosition(Vec2(
                                    - nbrOfImagesPerLine*imageWith/2 + imageWith/2,
                                    - nbrOfImagesPerColumn*imageHeigth/2 + imageHeigth/2));
    
    this->addChild(background, 0);
    
    return true;
}

void DisplayBackground::moveBackground()
{
    //MOVE BACKGROUND
}
