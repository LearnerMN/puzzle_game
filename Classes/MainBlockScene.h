//
//  MainBlockScene.h
//  TestLogicGame
//
//  Created by LearnerMN on 3/21/15.
//
//

#ifndef __TestLogicGame__MainBlockScene__
#define __TestLogicGame__MainBlockScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainBlock : public cocos2d::Layer
{
public:
    
    cocos2d::ui::PageView* block_chooser_pv;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	static int typeGame;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void touch_btn(Ref* pSender);
    
    void arrow_left_btn_function(Ref* pSender);
    void arrow_right_btn_function(Ref* pSender);
    
	void touch_btn_callback();

    // implement the "static create()" method manually
    CREATE_FUNC(MainBlock);
};


#endif /* defined(__TestLogicGame__MainBlockScene__) */
