#pragma once
#include "AbstractRiverCross.h"
class TestExtends :
	public AbstractRiverCross
{
public:
    void checkLogic();
    void res_btn_function(Ref* pSender);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(TestExtends);
};

