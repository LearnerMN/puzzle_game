#include "RiverCrossingScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* RiverCrossingScene::createScene()
{
	auto scene = Scene::create();
	RiverCrossingScene::rootNode = CSLoader::createNode("CrossRiverScene.csb");
	auto layer = RiverCrossingScene::create();
	scene->addChild(layer);
	return scene;
}

bool RiverCrossingScene::init()
{
    this->boatSize = 1;
	if (!AbstractRiverCross::init())
	{
		return false;
	}
	auto help_word = Sprite::create("help/river_crossing_help_1.png");
	help_word->setPosition(Vec2(help_frame->getContentSize().width / 2, help_frame->getContentSize().height / 2));
	this->help_frame->addChild(help_word);

	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("soi_4")));
	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("bapcai_5")));
	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("cuu0_6")));
	
	return true;
}

void RiverCrossingScene::checkLogic(){
    log("Child");
    
	if (leftVec.size() == 3){
		winLevel();
		return;
	}
	bool isHay = false, isSheep = false, isWolf = false;
	if (isLeft){
		for (int i = 0; i < rightVec.size(); i++){
			if (rightVec[i]->getName() == "soi_4"){
				isWolf = true;
			}else
			if (rightVec[i]->getName() == "bapcai_5"){
				isHay = true;
			}
			else
			if (rightVec[i]->getName() == "cuu0_6"){
				isSheep = true;
			}
			else;
		}
	}
	else{
		for (int i = 0; i < leftVec.size(); i++){
			if (leftVec[i]->getName() == "soi_4"){
				isWolf = true;
			}
			else
				if (leftVec[i]->getName() == "bapcai_5"){
				isHay = true;
			}
			else
				if (leftVec[i]->getName() == "cuu0_6"){
				isSheep = true;
			}
			else;
		}
	}

	if (isHay && isSheep){
		gameOver();
	}
	if (isSheep && isWolf){
		gameOver();
	}
}
void RiverCrossingScene::res_btn_function(Ref* pSender){
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(RiverCrossingScene::createScene());
}