#include "MatchLogicScene.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

template <typename T> T string_to_num( const std::string &Text ){
    std::istringstream ss(Text);
    T result;
    return ss >> result ? result : 0;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}


Scene* MatchLogicScene::createScene(std::string first,std::string second,int move_match_ll)
{
	auto scene = Scene::create();
    
    MatchLogicScene::begin_equal = first;
    MatchLogicScene::finish_equal = second;
    MatchLogicScene::move_match = move_match_ll;
    
    char get_oper = get_operator(begin_equal);
    std::string last_equal = eq_right(begin_equal);
    
    if (get_oper == '/' || get_oper == '*'){
        if (last_equal.size() == 2){
            MatchLogicScene::boardList = CSLoader::createNode("MatchScene_2.csb");
        }else{
            MatchLogicScene::boardList = CSLoader::createNode("MatchScene_0.csb");
        }
    }else{
        if (last_equal.size() == 2){
            MatchLogicScene::boardList = CSLoader::createNode("MatchScene_1.csb");
        }else{
            MatchLogicScene::boardList = CSLoader::createNode("MatchScene.csb");
        }
    }
    
    
	auto layer = MatchLogicScene::create();
	scene->addChild(layer);
	return scene;
}

bool MatchLogicScene::init()
{
	if (!AbstractMatchLogic::init())
	{
		return false;
	}

	auto help_word = Sprite::create("help/match_help_move_match_1.png");
	if (move_match == 2){
		help_word = Sprite::create("help/match_help_move_match_2.png");
	}
	help_word->setPosition(Vec2(help_frame->getContentSize().width / 2, help_frame->getContentSize().height / 2));
	this->help_frame->addChild(help_word);
	return true;
}
// string begin_equal =  "4+7=17";
// string finish_equal = "4+7=11"
// int move_match = 1;

void MatchLogicScene::add_custom_controller(){
    
}


void MatchLogicScene::begin_situation(){
    caseN(string_to_num<int>(eq_left(begin_equal)), 0,checkMap);
	caseOper(get_operator(begin_equal), checkMap);
	caseN(string_to_num<int>(eq_mid(begin_equal)), 1, checkMap);
	caseOper('=', checkMap);
    
    std::string lst_num = eq_right(begin_equal);
    if (lst_num.size() > 0)
		caseN((int)lst_num[0] - 48, 2, checkMap);
    if (lst_num.size() > 1){
		caseN((int)lst_num[1] - 48, 3, checkMap);
    }
}

void MatchLogicScene::finish_situation(){
	std::vector< std::string > eq_list = split(finish_equal,',');
	for (int i = 0; i < eq_list.size(); i++){
		std::map<std::string, int> tmp_map;
		caseN(string_to_num<int>(eq_left(eq_list[i])), 0, tmp_map);
		caseOper(get_operator(eq_list[i]), tmp_map);
		caseN(string_to_num<int>(eq_mid(eq_list[i])), 1, tmp_map);
		caseOper('=', tmp_map);

		std::string lst_num = eq_right(eq_list[i]);
		if (lst_num.size() > 0)
			caseN((int)lst_num[0] - 48, 2, tmp_map);
		if (lst_num.size() > 1){
			caseN((int)lst_num[1] - 48, 3, tmp_map);
		}
		finish_check_vec.push_back(tmp_map);
	}
}

void MatchLogicScene::res_btn_function(Ref* pSender){
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(MatchLogicScene::createScene(begin_equal,finish_equal,move_match));
}