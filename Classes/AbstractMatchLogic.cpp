//
//  AbstractMatchLogic.cpp
//  TestLogicGame
//
//  Created by Khureltsooj on 5/26/15.
//
//

#include "AbstractMatchLogic.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "LevelChooserScene.h"
#include "SimpleAudioEngine.h"

#include <map>

using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

std::map<std::string, int> AbstractMatchLogic::checkMap;

std::vector< std::map<std::string, int> > AbstractMatchLogic::finish_check_vec;

cocos2d::Node* AbstractMatchLogic::boardList;

std::string AbstractMatchLogic::begin_equal = "";
std::string AbstractMatchLogic::finish_equal = "";

int AbstractMatchLogic::add_match = 0;
int AbstractMatchLogic::remove_match = 0;
int AbstractMatchLogic::move_match = 0;
int AbstractMatchLogic::tool_rem = 0;

int AbstractMatchLogic::level_num = 0;


Scene* AbstractMatchLogic::createScene()
{
    auto scene = Scene::create();
    AbstractMatchLogic::boardList = CSLoader::createNode("MatchScene_1.csb");
    auto layer = AbstractMatchLogic::create();
    scene->addChild(layer);
    return scene;
}

bool AbstractMatchLogic::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
	finish_check_vec.clear();
    checkMap.clear();
    add_match = 0;
    remove_match = 0;
    tool_rem = 0;
    

	isHelped = false;
	help_frame = boardList->getChildByName("help_frame");
	help_frame->setZOrder(10);
	help_frame->setVisible(false);

	help_btn = dynamic_cast<ui::Button*>(boardList->getChildByName("help_btn"));
	help_btn->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::help_btn_function, this));

	next_btn = dynamic_cast<ui::Button*>(boardList->getChildByName("next_btn"));
	next_btn->setVisible(false);
	next_btn->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::next_btn_function, this));


    finish_layer = boardList->getChildByName("finish_layer");
    finish_layer->setVisible(false);
    
    gameover_layer = boardList->getChildByName("gameover_layer");
    gameover_layer->setVisible(false);
    
    menu_layer = boardList->getChildByName("menu_layer");
    menu_btn_hide = dynamic_cast<ui::Button*>(menu_layer->getChildByName("menu_btn_hide"));
    menu_btn_hide->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::menu_hide_btn, this));
    menu_layer->setVisible(false);
    
    auto btn_list = dynamic_cast<ui::ListView*>(menu_layer->getChildByName("btn_list"));
    
    auto back_btn = dynamic_cast<ui::Button*>(btn_list->getChildByName("back_btn"));
    back_btn->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::back_btn_function, this));
    auto volume_btn = dynamic_cast<ui::Button*>(btn_list->getChildByName("volume_btn"));
    volume_btn->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::volume_btn_function, this));
    auto res_btn = dynamic_cast<ui::Button*>(btn_list->getChildByName("res_btn"));
    res_btn->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::res_btn_function, this));
    
    menu_btn_show = dynamic_cast<ui::Button*>(boardList->getChildByName("menu_btn_show"));
    menu_btn_show->addClickEventListener(CC_CALLBACK_1(AbstractMatchLogic::menu_show_btn, this));
    
    addChild(boardList);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(AbstractMatchLogic::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    begin_situation();
    
    add_custom_controller();
    
    for (auto i : boardList->getChildren()){
        std::string sname = i->getName();
        if (sname[sname.size() - 1] >= '0' && sname[sname.size() - 1] <= '9'){
            if (checkMap[sname] == 4){
                auto sprite = dynamic_cast<Sprite*>(i);
                sprite->initWithFile("MatchScene/match_1.png");
            }
        }
    }
    
    finish_situation();
    
	help_btn_function(nullptr);

    return true;
}

void AbstractMatchLogic::add_custom_controller(){
    move_match = 1;
}

bool is_number(char ch){
    return '0'<=ch && ch<= '9';
}

char AbstractMatchLogic::get_operator(std::string &begin_equal){
    int len = 0;
    while (is_number(begin_equal[len++]));
    
    return begin_equal[len-1];
}

std::string AbstractMatchLogic::eq_left(std::string &begin_equal){
    std::string tmp = "";
    int len = 0;
    while (is_number(begin_equal[len])){
        tmp += begin_equal[len];
        len++;
    }
    return tmp;
}

std::string AbstractMatchLogic::eq_mid(std::string &begin_equal){
    std::string tmp = "";
    int len = 0;
    while (is_number(begin_equal[len++])){}
    
    while (begin_equal[len] != '='){
        tmp += begin_equal[len];
        len++;
    }
    return tmp;
}

std::string AbstractMatchLogic::eq_right(std::string &begin_equal){
    std::string tmp = "";
    int len = begin_equal.size()-1;
    while (begin_equal[len] != '='){
        tmp = begin_equal[len] + tmp;
        len--;
    }
    return tmp;
}

void AbstractMatchLogic::begin_situation(){

}

void AbstractMatchLogic::finish_situation(){

}

void AbstractMatchLogic::menu_show_btn(Ref* pSender){
    menu_layer->setVisible(true);
    menu_btn_show->setVisible(false);
}
void AbstractMatchLogic::menu_hide_btn(Ref* pSender){
    menu_layer->setVisible(false);
    menu_btn_show->setVisible(true);
}

void AbstractMatchLogic::res_btn_function(Ref* pSender){
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(AbstractMatchLogic::createScene());
}
void AbstractMatchLogic::back_btn_function(Ref* pSender){
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(LevelChooserScene::createScene());
}
static bool isMute = false;
void AbstractMatchLogic::volume_btn_function(Ref* pSender){
    (!isMute) ? isMute = true : isMute = false;
    
    if (!isMute){
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    else{
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}


bool AbstractMatchLogic::onTouchBegan(Touch *touch, Event *event)
{
    
    for (auto i : boardList->getChildren()){
        std::string sname = i->getName();
        if (sname[sname.size() - 1] >= '0' && sname[sname.size() - 1] <= '9'){
            if (i->boundingBox().containsPoint(touch->getLocation())){
                auto sprite = dynamic_cast<Sprite*>(i);
                if (checkMap[sname] == 3){
                    if (add_match > 0){
                        sprite->initWithFile("MatchScene/match_0.png");
                        checkMap[sname] = 5;
                        add_match--;
						sprite->runAction(Sequence::create(ScaleTo::create(0.1, 1.4), ScaleTo::create(0.1, 0.6), ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 0.7), NULL));
					}
                }
                else if (checkMap[sname] == 4){
                    if (move_match > tool_rem){
                        checkMap[sname] = 2;
                        sprite->initWithFile("MatchScene/match_2.png");
                        tool_rem++;
                        add_match++;
					}
                }
                else if (checkMap[sname] == 5){
                    checkMap[sname] = 3;
                    sprite->initWithFile("MatchScene/match_3.png");
                    add_match++;
                }
                else{//? == 2
                    if (add_match > 0){
                        checkMap[sname] = 4;
                        sprite->initWithFile("MatchScene/match_1.png");
                        add_match--;
                        tool_rem--;
						sprite->runAction(Sequence::create(ScaleTo::create(0.1, 1.4), ScaleTo::create(0.1, 0.6), ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 0.7), NULL));
                    }
                }
            }
        }
    }
    
    if (checkLogic())
        winLevel();
    return true;
}

void AbstractMatchLogic::gameOver(){
    gameover_layer->setVisible(true);
    setCascadeOpacityEnabled(true);
    setOpacity(180);
    menu_show_btn(nullptr);
    this->pause();
}

void AbstractMatchLogic::winLevel(){
    finish_layer->setVisible(true);
    setOpacity(180);
    menu_show_btn(nullptr);
    this->pause();
	UserDefault::getInstance()->setIntegerForKey("type-2", fmax(level_num + 1,UserDefault::getInstance()->getIntegerForKey("type-2")));
	next_btn->setVisible(true);
}

bool AbstractMatchLogic::checkLogic(){

	for (int k = 0; k < finish_check_vec.size(); k++){
		bool check = true;
		for (auto i : finish_check_vec[k]){// 2 3, 4 5
			if (!(((checkMap[i.first] == 2 || checkMap[i.first] == 3) && (i.second == 2 || i.second == 3)) ||
				((checkMap[i.first] == 4 || checkMap[i.first] == 5) && (i.second == 5 || i.second == 4)))){
				check = false;
				break;
			}
		}
		if (check)
			return true;
	}
	return false;
}

void AbstractMatchLogic::caseN(int num, int pos, std::map<std::string, int> &set_map){
    switch (num){
		case 0: number_0(pos, set_map); break;
		case 1: number_1(pos, set_map); break;
		case 2: number_2(pos, set_map); break;
		case 3: number_3(pos, set_map); break;
		case 4: number_4(pos, set_map); break;
		case 5: number_5(pos, set_map); break;
		case 6: number_6(pos, set_map); break;
		case 7: number_7(pos, set_map); break;
		case 8: number_8(pos, set_map); break;
		case 9: number_9(pos, set_map); break;
        default: break;
    }
}

void AbstractMatchLogic::caseOper(char operator_type, std::map<std::string, int> &set_map){
    if (operator_type == '+' || operator_type == '*'){
		operator_two(set_map);
    }else if (operator_type == '-' || operator_type == '/'){
        log ("operator_type: %c",operator_type);
		operator_one(set_map);
    }else{
		set_map["operator_11"] = 4;//1
		set_map["operator_12"] = 4;//2
    }
}

void AbstractMatchLogic::operator_one(std::map<std::string, int> &set_map){
	set_map["operator_01"] = 4;//1
	set_map["operator_02"] = 3;//2
}
void AbstractMatchLogic::operator_two(std::map<std::string, int> &set_map){
	set_map["operator_01"] = 4;//1
	set_map["operator_02"] = 4;//2
}
void AbstractMatchLogic::number_0(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();
    
	set_map["match_" + sPos + "1"] = 4;//1
	set_map["match_" + sPos + "2"] = 4;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 3;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_1(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();

	set_map["match_" + sPos + "1"] = 3;//1
	set_map["match_" + sPos + "2"] = 3;//2
	set_map["match_" + sPos + "3"] = 3;//3
	set_map["match_" + sPos + "4"] = 3;//4
	set_map["match_" + sPos + "5"] = 3;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_2(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();
    
	set_map["match_" + sPos + "1"] = 3;//1
	set_map["match_" + sPos + "2"] = 4;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 3;//7
}

void AbstractMatchLogic::number_3(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();

	set_map["match_" + sPos + "1"] = 3;//1
	set_map["match_" + sPos + "2"] = 3;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_4(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();

	set_map["match_" + sPos + "1"] = 4;//1
	set_map["match_" + sPos + "2"] = 3;//2
	set_map["match_" + sPos + "3"] = 3;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 3;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_5(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();

	set_map["match_" + sPos + "1"] = 4;//1
	set_map["match_" + sPos + "2"] = 3;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 3;//6
	set_map["match_" + sPos + "7"] = 4;//7

}

void AbstractMatchLogic::number_6(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();
    
	set_map["match_" + sPos + "1"] = 4;//1
	set_map["match_" + sPos + "2"] = 4;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 3;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_7(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();
    
	set_map["match_" + sPos + "1"] = 3;//1
	set_map["match_" + sPos + "2"] = 3;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 3;//4
	set_map["match_" + sPos + "5"] = 3;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_8(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();

	set_map["match_" + sPos + "1"] = 4;//1
	set_map["match_" + sPos + "2"] = 4;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::number_9(int pos, std::map<std::string, int> &set_map){
    std::stringstream ss;
    ss << pos;
    std::string sPos = ss.str();
    
	set_map["match_" + sPos + "1"] = 4;//1
	set_map["match_" + sPos + "2"] = 3;//2
	set_map["match_" + sPos + "3"] = 4;//3
	set_map["match_" + sPos + "4"] = 4;//4
	set_map["match_" + sPos + "5"] = 4;//5
	set_map["match_" + sPos + "6"] = 4;//6
	set_map["match_" + sPos + "7"] = 4;//7
}

void AbstractMatchLogic::help_btn_function(Ref* pSender){
	if (!isHelped){
		help_frame->setVisible(true);
		isHelped = true;
		help_btn->loadTextures("menu/bt_Help2.png", "menu/bt_Help1.png", "");
		pause();
	}
	else{
		help_frame->setVisible(false);
		isHelped = false;
		help_btn->loadTextures("menu/bt_Help1.png", "menu/bt_Help2.png", "");
		resume();
	}
}

void AbstractMatchLogic::next_btn_function(Ref* pSender){
	auto scene = LevelChooserScene::getLevelScene("Match", level_num + 1);
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
}