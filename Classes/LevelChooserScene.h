//
//  LevelChooserScene.h
//  TestLogicGame
//
//  Created by LearnerMN on 3/21/15.
//
//

#ifndef __TestLogicGame__LevelChooserScene__
#define __TestLogicGame__LevelChooserScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LevelChooserScene : public cocos2d::Layer
{
public:
    
    cocos2d::ui::PageView* page_pv;

    void arrow_left_btn_function(Ref* pSender);
    void arrow_right_btn_function(Ref* pSender);
    
    void changePage( int index );
    
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void touch_btn(Ref* pSender);

	// implement the "static create()" method manually

	static cocos2d::Scene* getLevelScene(std::string type, int level);

	CREATE_FUNC(LevelChooserScene);
};


#endif /* defined(__TestLogicGame__LevelChooserScene__) */
