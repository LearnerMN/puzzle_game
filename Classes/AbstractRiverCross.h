#ifndef __TestLogicGame__AbstractRiverCross__
#define __TestLogicGame__AbstractRiverCross__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include <vector>
class AbstractRiverCross : public cocos2d::Layer
{

public:
    
	bool isHelped;

    float sX, sY;
    
    static int level_num;
    static bool isLeft;
    static int boatSize;
    static bool itemTouch;
    
	cocos2d::Node* help_frame;
	cocos2d::ui::Button* help_btn;
	cocos2d::ui::Button* next_btn;

    cocos2d::Node* finish_layer;
    cocos2d::Node* gameover_layer;
    cocos2d::ui::Button* menu_btn_show;
    cocos2d::ui::Button* menu_btn_hide;
    cocos2d::Node* menu_layer;
    
    cocos2d::Size visibleSize;
    
    virtual void checkLogic();
    
    void gameOver();
    void winLevel();
    
	static cocos2d::Node* rootNode;
	std::vector< cocos2d::Sprite* > leftVec;
	std::vector< cocos2d::Sprite* > midVec;
	std::vector< cocos2d::Sprite* > rightVec;
    
    std::vector< cocos2d::Vec2 > savePosVector;
    std::vector< cocos2d::Vec2 > boat_pos_vec;
    
    
	cocos2d::Sprite* boat_back;
	cocos2d::Sprite* boat_front;
	cocos2d::ui::Button* lets_go_btn;

	static cocos2d::Scene* createScene();
	void flipX_function();
	virtual void go_btn(Ref* pSender);
	void menu_hide_btn(Ref* pSender);
	void menu_show_btn(Ref* pSender);

	virtual void res_btn_function(Ref* pSender);
	void back_btn_function(Ref* pSender);
	void volume_btn_function(Ref* pSender);

	void help_btn_function(Ref* pSender);
	void next_btn_function(Ref* pSender);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	bool isTouchDown;

	float initialTouchPos[2];
	float currentTouchPos[2];

	void update(float dt);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(AbstractRiverCross);
};


#endif /* defined(__TestLogicGame__AbstractRiverCross__) */