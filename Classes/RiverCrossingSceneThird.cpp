#include "RiverCrossingSceneThird.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* RiverCrossingSceneThird::createScene()
{
	auto scene = Scene::create();
	RiverCrossingSceneThird::rootNode = CSLoader::createNode("CrossRiverScene_3.csb");
	auto layer = RiverCrossingSceneThird::create();
	scene->addChild(layer);
	return scene;
}

bool RiverCrossingSceneThird::init()
{
	this->boatSize = 2;
	if (!AbstractRiverCross::init())
	{
		return false;
	}

	count_down_time = 30;

	auto node_img = rootNode->getChildByName("right_menu_img");
	down_timer_txt = dynamic_cast<ui::Text*>(node_img->getChildByName("text_txt"));

	auto help_word = Sprite::create("help/river_crossing_help_3.png");
	help_word->setPosition(Vec2(help_frame->getContentSize().width / 2, help_frame->getContentSize().height / 2));
	this->help_frame->addChild(help_word);

	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("c1_1")));	char_sec_map["c1_1"] = 1;
	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("c2_2")));	char_sec_map["c2_2"] = 3;
	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("c3_3")));	char_sec_map["c3_3"] = 6;
	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("c4_4")));	char_sec_map["c4_4"] = 8;
	rightVec.push_back(dynamic_cast<Sprite*>(rootNode->getChildByName("c5_5")));	char_sec_map["c5_5"] = 12;
	
	return true;
}

void RiverCrossingSceneThird::checkLogic(){
	if (leftVec.size() == 5){
		winLevel();
		return;
	}

	if (count_down_time < 1)
		gameOver();
}

void RiverCrossingSceneThird::go_btn(Ref* pSender){
	if (boatSize != 1 && midVec.size() == 0) return;
	auto btn = (ui::Button*)pSender;
	Size sizeV = Director::getInstance()->getVisibleSize();
	lets_go_btn->setEnabled(false);
	(!isLeft) ? isLeft = true : isLeft = false;

	float maxs_time = 0;
	for (auto i : midVec){
		i->runAction(FlipX::create(!isLeft));
		maxs_time = fmax(char_sec_map[i->getName()], maxs_time);
	}

	down_time_c = maxs_time;
	maxs_time /= 2;

	if (count_down_time - down_time_c < 0){
		gameOver();
		return;
	}

	lets_go_btn->setEnabled(false);

	boat_back->runAction(Sequence::create(MoveTo::create(maxs_time, Vec2(sizeV.width - boat_back->getPositionX(), boat_back->getPositionY())),
		CallFunc::create(CC_CALLBACK_0(AbstractRiverCross::flipX_function, this)), NULL));

	schedule(schedule_selector(RiverCrossingSceneThird::down_time), 0.5);
}

void RiverCrossingSceneThird::down_time(float delta){
	down_time_c--;
	count_down_time--;

	std::stringstream time_d;
	time_d << count_down_time;
	down_timer_txt->setString(time_d.str());

	if (down_time_c < 1){
		unschedule(schedule_selector(RiverCrossingSceneThird::down_time));
		return;
	}
}
void RiverCrossingSceneThird::res_btn_function(Ref* pSender){
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(RiverCrossingSceneThird::createScene());
}
