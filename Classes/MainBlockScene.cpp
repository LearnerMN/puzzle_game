//
//  MainBlockScene.cpp
//  TestLogicGame
//
//  Created by LearnerMN on 3/21/15.
//
//

#include "MainBlockScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "LevelChooserScene.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;


int MainBlock::typeGame = 0;

Scene* MainBlock::createScene()
{
    auto scene = Scene::create();
    auto layer = MainBlock::create();
    scene->addChild(layer);
    return scene;
}

bool MainBlock::init(){

    if ( !Layer::init() )
    {
        return false;
    }
    
    UserDefault::getInstance()->setIntegerForKey("type-1", 0);
    UserDefault::getInstance()->setIntegerForKey("type-2", 0);
//    log("UserDefault %d ",UserDefault::getInstance()->getIntegerForKey("type-1"));
//    log("UserDefault %d ",UserDefault::getInstance()->getIntegerForKey("type-2"));
    
    
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("block_sound.mp3",true);

    auto rootNode = CSLoader::createNode("MainScene.csb");
	block_chooser_pv = dynamic_cast<ui::PageView*>(rootNode->getChildByName("block_chooser_pv"));

	auto river_pan = dynamic_cast<ui::Layout*>(block_chooser_pv->getChildByName("river_panel"));
	auto river_btn = dynamic_cast<ui::Button*>(river_pan->getChildByName("river_btn"));
	river_btn->addClickEventListener(CC_CALLBACK_1(MainBlock::touch_btn, this));

	auto match_pan = dynamic_cast<ui::Layout*>(block_chooser_pv->getChildByName("match_panel"));
	auto match_btn = dynamic_cast<ui::Button*>(match_pan->getChildByName("match_btn"));
	match_btn->addClickEventListener(CC_CALLBACK_1(MainBlock::touch_btn, this));

    
    auto arrow_left_btn = dynamic_cast<ui::Button*>(rootNode->getChildByName("arrow_left_btn"));
    arrow_left_btn->addClickEventListener(CC_CALLBACK_1(MainBlock::arrow_left_btn_function, this));
    auto arrow_right_btn = dynamic_cast<ui::Button*>(rootNode->getChildByName("arrow_right_btn"));
    arrow_right_btn->addClickEventListener(CC_CALLBACK_1(MainBlock::arrow_right_btn_function, this));
    
    addChild(rootNode);

    return true;
}

void MainBlock::arrow_left_btn_function(Ref* pSender){
    block_chooser_pv->scrollToPage((ssize_t)fmax(0, block_chooser_pv->getCurPageIndex()-1));
}

void MainBlock::arrow_right_btn_function(Ref* pSender){
    block_chooser_pv->scrollToPage((ssize_t)fmin(block_chooser_pv->getChildrenCount()-1, block_chooser_pv->getCurPageIndex()+1));
}

void MainBlock::touch_btn(Ref* pSender){
	auto btn = (ui::Button*)pSender;
	btn->runAction(Sequence::create(ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 0.6f),
		ScaleTo::create(0.1f, 0.7f),
		CallFunc::create(CC_CALLBACK_0(MainBlock::touch_btn_callback, this)), ScaleTo::create(0.1f, 1.0f), NULL));

	if (btn->getName() == "match_btn"){
		typeGame = 2;
	}
	else{
		typeGame = 1;
	}
}

void MainBlock::touch_btn_callback(){
	Director::getInstance()->pushScene(LevelChooserScene::createScene());
	
}
