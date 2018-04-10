//
//  RiverCrossingSceneThird.h
//  TestLogicGame
//
//  Created by LearnerMN on 3/21/15.
//
//

#ifndef __TestLogicGame__RiverCrossingSceneThird__
#define __TestLogicGame__RiverCrossingSceneThird__

#include "AbstractRiverCross.h"
class RiverCrossingSceneThird : public AbstractRiverCross
{
public:

	int count_down_time;
	int down_time_c;

	cocos2d::ui::Text* down_timer_txt;

	std::map< std::string,float > char_sec_map;

    void checkLogic();

	void down_time(float delta);

	void go_btn(Ref* pSender);
    void res_btn_function(Ref* pSender);
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(RiverCrossingSceneThird);
};


#endif /* defined(__TestLogicGame__RiverCrossingSceneThird__) */