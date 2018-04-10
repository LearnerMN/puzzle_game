#include "RiverCrossingSceneFour.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SimpleAudioEngine.h"
#include "RiverCrossingSceneFour.h"
using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* RiverCrossingSceneFour::createScene()
{
    auto scene = Scene::create();
	RiverCrossingSceneFour::rootNode = CSLoader::createNode("CrossRiverScene_4.csb");
	auto layer = RiverCrossingSceneFour::create();
    scene->addChild(layer);
    
    return scene;
}

bool RiverCrossingSceneFour::init()
{
    this->boatSize = 2;
	if (!AbstractRiverCross::init())
	{
		return false;
	}
	auto help_word = Sprite::create("help/river_crossing_help_4.png");
	help_word->setPosition(Vec2(help_frame->getContentSize().width / 2, help_frame->getContentSize().height / 2));
	this->help_frame->addChild(help_word);

    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("man1_1")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("man2_2")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("man3_3")));
    
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("bag1_4")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("bag2_5")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("bag3_6")));
    
	return true;
}
void RiverCrossingSceneFour::checkLogic(){
    
    if (leftVec.size() == 6){
        winLevel();
        return;
    }
    
}

void RiverCrossingSceneFour::res_btn_function(cocos2d::Ref *pSender){
    Director::getInstance()->popScene();
	Director::getInstance()->pushScene(RiverCrossingSceneFour::createScene());
}
