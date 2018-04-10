#include "TestExtends.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* TestExtends::createScene()
{
    auto scene = Scene::create();
    TestExtends::rootNode = CSLoader::createNode("CrossRiverScene_2.csb");
    auto layer = TestExtends::create();
    scene->addChild(layer);
    
    return scene;
}

bool TestExtends::init()
{
    this->boatSize = 2;
	if (!AbstractRiverCross::init())
	{
		return false;
	}
	auto help_word = Sprite::create("help/river_crossing_help_2.png");
	help_word->setPosition(Vec2(help_frame->getContentSize().width / 2, help_frame->getContentSize().height / 2));
	this->help_frame->addChild(help_word);

    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("nhasu_1")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("nhasu_2")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("nhasu_3")));
    
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("thodan0_4")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("thodan0_5")));
    rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("thodan0_6")));
    
	return true;
}
void TestExtends::checkLogic(){
    
    if (leftVec.size() == 6){
        winLevel();
        return;
    }
    int nhasu_c = 0,thodan_c = 0;
    for (int i = 0; i < rightVec.size(); i++){
        if (rightVec[i]->getName() == "nhasu_1" || rightVec[i]->getName() == "nhasu_2" || rightVec[i]->getName() == "nhasu_3"){
            nhasu_c++;
        }else{
            thodan_c++;
        }
    }
    
    if (thodan_c>nhasu_c && nhasu_c > 0){
        gameOver();
    }
    
    nhasu_c = 0;thodan_c = 0;
    
    for (int i = 0; i < leftVec.size(); i++){
        if (leftVec[i]->getName() == "nhasu_1" || leftVec[i]->getName() == "nhasu_2" || leftVec[i]->getName() == "nhasu_3"){
            nhasu_c++;
        }else{
            thodan_c++;
        }
    }
    
    if (thodan_c > nhasu_c && nhasu_c > 0){
        gameOver();
    }
}

void TestExtends::res_btn_function(cocos2d::Ref *pSender){
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(TestExtends::createScene());
}