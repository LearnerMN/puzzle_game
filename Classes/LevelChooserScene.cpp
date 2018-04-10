#include "LevelChooserScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "RiverCrossingScene.h"
#include "SimpleAudioEngine.h"

#include "MainBlockScene.h"
#include "MatchLogicScene.h"
#include "TestExtends.h"

#include "RiverCrossingSceneThird.h"
#include "RiverCrossingSceneFour.h"

using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* LevelChooserScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelChooserScene::create();
	scene->addChild(layer);
	return scene;
}

bool LevelChooserScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("LevelChooserScene.csb");
	
	//button addClickEventListener in LevelsLayer layer 
	auto layerNode = rootNode->getChildByName("LevelsLayer");
    
    auto arrow_left_btn = dynamic_cast<ui::Button*>(layerNode->getChildByName("arrow_left_btn"));
    arrow_left_btn->addClickEventListener(CC_CALLBACK_1(LevelChooserScene::arrow_left_btn_function, this));
    auto arrow_right_btn = dynamic_cast<ui::Button*>(layerNode->getChildByName("arrow_right_btn"));
    arrow_right_btn->addClickEventListener(CC_CALLBACK_1(LevelChooserScene::arrow_right_btn_function, this));
    
	page_pv = dynamic_cast<ui::PageView*>(layerNode->getChildByName("page_pv"));
    
	auto slide_1_panel = dynamic_cast<ui::Layout*>(page_pv->getChildByName("slide_1_panel"));
	auto levels_panel = dynamic_cast<ui::Layout*>(slide_1_panel->getChildByName("levels_panel"));
	auto panel0x0 = dynamic_cast<ui::Layout*>(levels_panel->getChildByName("0x0_panel"));
	auto panel0x1 = dynamic_cast<ui::Layout*>(levels_panel->getChildByName("0x1_panel"));
    auto panel1x0 = dynamic_cast<ui::Layout*>(levels_panel->getChildByName("1x0_panel"));
    auto panel1x1 = dynamic_cast<ui::Layout*>(levels_panel->getChildByName("1x1_panel"));

	auto slide_2_panel = dynamic_cast<ui::Layout*>(page_pv->getChildByName("slide_2_panel"));
	auto levels_panel_1 = dynamic_cast<ui::Layout*>(slide_2_panel->getChildByName("levels_panel"));
	auto panel0x0_1 = dynamic_cast<ui::Layout*>(levels_panel_1->getChildByName("0x0_panel"));
	auto panel0x1_1 = dynamic_cast<ui::Layout*>(levels_panel_1->getChildByName("0x1_panel"));
	auto panel1x0_1 = dynamic_cast<ui::Layout*>(levels_panel_1->getChildByName("1x0_panel"));
	auto panel1x1_1 = dynamic_cast<ui::Layout*>(levels_panel_1->getChildByName("1x1_panel"));

    Vector< ui::Button* > levels_vec;
    levels_vec.pushBack(dynamic_cast<ui::Button*>(panel0x0->getChildByName("level_1_btn")));
    levels_vec.pushBack(dynamic_cast<ui::Button*>(panel0x1->getChildByName("level_2_btn")));
    levels_vec.pushBack(dynamic_cast<ui::Button*>(panel1x0->getChildByName("level_3_btn")));
    levels_vec.pushBack(dynamic_cast<ui::Button*>(panel1x1->getChildByName("level_4_btn")));
	levels_vec.pushBack(dynamic_cast<ui::Button*>(panel0x0_1->getChildByName("level_5_btn")));
	levels_vec.pushBack(dynamic_cast<ui::Button*>(panel0x1_1->getChildByName("level_6_btn")));
	levels_vec.pushBack(dynamic_cast<ui::Button*>(panel1x0_1->getChildByName("level_7_btn")));
	levels_vec.pushBack(dynamic_cast<ui::Button*>(panel1x1_1->getChildByName("level_8_btn")));
    

	if (MainBlock::typeGame == 2){
        for (int i=0; i<=fmin(UserDefault::getInstance()->getIntegerForKey("type-2"),levels_vec.size()-1); i++){
			if (fmin(UserDefault::getInstance()->getIntegerForKey("type-2"), levels_vec.size() - 1) == i){
				levels_vec.at(i)->loadTextures("MatchScene/match_level.png", "MatchScene/match_level.png", "");
			}
			else{
				levels_vec.at(i)->loadTextures("MatchScene/match_level_star.png", "MatchScene/match_level_star.png", "");
			}
            levels_vec.at(i)->addClickEventListener(CC_CALLBACK_1(LevelChooserScene::touch_btn, this));
        }
    }else{
        for (int i=0; i<=fmin(UserDefault::getInstance()->getIntegerForKey("type-1"),levels_vec.size()-1); i++){
			std::stringstream index_at;
			index_at << (i + 1);
			levels_vec.at(i)->loadTextures("MainScene/Block/CR_level_" + index_at.str() + ".png", "MainScene/Block/CR_level_" + index_at.str() +".png", "");
			levels_vec.at(i)->addClickEventListener(CC_CALLBACK_1(LevelChooserScene::touch_btn, this));
        }
    }

	auto back_btn = dynamic_cast<ui::Button*>(rootNode->getChildByName("back_btn"));
	back_btn->addClickEventListener(CC_CALLBACK_1(LevelChooserScene::touch_btn, this));

	addChild(rootNode);
	return true;
}
void LevelChooserScene::arrow_left_btn_function(Ref* pSender){
    page_pv->scrollToPage((ssize_t)fmax(0, page_pv->getCurPageIndex()-1));
}

void LevelChooserScene::arrow_right_btn_function(Ref* pSender){
    page_pv->scrollToPage((ssize_t)fmin(page_pv->getChildrenCount()-1, page_pv->getCurPageIndex()+1));
}

void LevelChooserScene::changePage( int index )
{
    auto totalPage = page_pv->getPages().size();
    
    if( index == page_pv->getCurPageIndex() ) return;
    
    if( index >= 0 && index <= totalPage-1 )
    {
        //page_pv->scrollToPage( index );
    }
}

void LevelChooserScene::touch_btn(Ref *ref){
	auto btn = (ui::Button*)ref;
	if (btn->getName() == "back_btn"){
		Director::getInstance()->popScene();
		return;
	}
	Scene* scenes = nullptr;
    if (MainBlock::typeGame == 2){
        if (btn->getName() == "level_1_btn"){
			scenes = getLevelScene("Match", 0);
        }else if (btn->getName() == "level_2_btn"){
			scenes = getLevelScene("Match", 1);
        }else if (btn->getName() == "level_3_btn"){
			scenes = getLevelScene("Match", 2);
		}
		else if (btn->getName() == "level_4_btn"){
			scenes = getLevelScene("Match", 3);
		}
		else if (btn->getName() == "level_5_btn"){
			scenes = getLevelScene("Match", 4);
		}
		else if (btn->getName() == "level_6_btn"){
			scenes = getLevelScene("Match", 5);
		}
		else if (btn->getName() == "level_7_btn"){
			scenes = getLevelScene("Match", 6);
		}
		else{
			scenes = getLevelScene("Match", 7);
        }
    }else{
        if (btn->getName() == "level_1_btn"){
			scenes = getLevelScene("CR", 0);
        }else if (btn->getName() == "level_2_btn"){
			scenes = getLevelScene("CR", 1);
        }else if (btn->getName() == "level_3_btn"){
			scenes = getLevelScene("CR", 2);
        }else{
			scenes = getLevelScene("CR", 3);
        }
    }
	Director::getInstance()->pushScene(scenes);

}

Scene* LevelChooserScene::getLevelScene(std::string type,int level){
	Scene* scene;
	if (type == "CR"){
		switch (level){
			case 0: scene = RiverCrossingScene::createScene(); RiverCrossingScene::level_num = 0; break;
			case 1: scene = TestExtends::createScene(); TestExtends::level_num = 1; break;
			case 2: scene = RiverCrossingSceneThird::createScene(); RiverCrossingSceneThird::level_num = 2; break;
			default: scene = RiverCrossingSceneFour::createScene(); RiverCrossingSceneFour::level_num = 2; break;
		}
	}
	else{
		switch (level){
			case 0: scene = MatchLogicScene::createScene("6+9=18", "9+9=18", 1); MatchLogicScene::level_num = 0; break;
			case 1: scene = MatchLogicScene::createScene("9+1=1", "0+1=1", 1); MatchLogicScene::level_num = 1; break;
			case 2: scene = MatchLogicScene::createScene("5/8=1", "6/6=1,9/9=1", 1); MatchLogicScene::level_num = 2; break;
			case 3: scene = MatchLogicScene::createScene("9*9=40", "5*8=40,8*5=40", 1); MatchLogicScene::level_num = 3; break;
			case 4: scene = MatchLogicScene::createScene("0/1=6", "6/1=6,0/1=0", 1); MatchLogicScene::level_num = 4; break;
			case 5: scene = MatchLogicScene::createScene("7+7=9", "1+7=8,7+1=8", 1); MatchLogicScene::level_num = 5; break;
			case 6: scene = MatchLogicScene::createScene("1*9=98", "7*8=56", 2); MatchLogicScene::level_num = 6; break;
			case 7: scene = MatchLogicScene::createScene("9-0=5", "9-6=3,3+0=3", 2); MatchLogicScene::level_num = 7; break;
			default:scene = MatchLogicScene::createScene("9-0=5", "9-6=3,3+0=3,8-3=5", 2); MatchLogicScene::level_num = 7; break;
		}
	}
	return scene;
}


/*

level:
 
*/
