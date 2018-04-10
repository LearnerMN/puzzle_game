//
//  AbstractMatchLogic.h
//  TestLogicGame
//
//  Created by Khureltsooj on 5/26/15.
//
//

#ifndef __TestLogicGame__AbstractMatchLogic__
#define __TestLogicGame__AbstractMatchLogic__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include <vector>
class AbstractMatchLogic : public cocos2d::Layer
{
private:
    cocos2d::ui::Button* menu_btn_show;
    cocos2d::ui::Button* menu_btn_hide;
    cocos2d::Node* menu_layer;
	
    
    cocos2d::Node* finish_layer;
    cocos2d::Node* gameover_layer;
    
	void operator_one(std::map<std::string, int> &set_map);
	void operator_two(std::map<std::string, int> &set_map);
    
	void number_0(int pos,std::map<std::string, int> &set_map);
	void number_1(int pos,std::map<std::string, int> &set_map);
	void number_2(int pos,std::map<std::string, int> &set_map);
	void number_3(int pos,std::map<std::string, int> &set_map);
	void number_4(int pos,std::map<std::string, int> &set_map);
	void number_5(int pos,std::map<std::string, int> &set_map);
	void number_6(int pos,std::map<std::string, int> &set_map);
	void number_7(int pos,std::map<std::string, int> &set_map);
	void number_8(int pos,std::map<std::string, int> &set_map);
	void number_9(int pos,std::map<std::string, int> &set_map);
    
    void gameOver();
    void winLevel();
    bool checkLogic();
public:

	bool isHelped;

    static int add_match;
    static int remove_match;
    static int move_match;
    static int tool_rem;
    
    static int level_num;
    
	cocos2d::Node* help_frame;
	cocos2d::ui::Button* help_btn;
	cocos2d::ui::Button* next_btn;
    static std::string begin_equal;
    static std::string finish_equal;
    
    static cocos2d::Node* boardList;
    static std::map<std::string, int> checkMap;
	static std::vector< std::map<std::string, int> > finish_check_vec;
    
	void caseN(int num, int pos, std::map<std::string, int> &set_map);
	void caseOper(char operator_type, std::map<std::string, int> &set_map);
    
    virtual void add_custom_controller();
    virtual void finish_situation();
    virtual void begin_situation();
    
    static char get_operator(std::string &begin_equal);
    static std::string eq_left(std::string &begin_equal);
    static std::string eq_mid(std::string &begin_equal);
    static std::string eq_right(std::string &begin_equal);
    
    
    void menu_hide_btn(Ref* pSender);
    void menu_show_btn(Ref* pSender);
    
    virtual void res_btn_function(Ref* pSender);
    void back_btn_function(Ref* pSender);
    void volume_btn_function(Ref* pSender);
	void help_btn_function(Ref* pSender);
	void next_btn_function(Ref* pSender);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(AbstractMatchLogic);
};

#endif /* defined(__TestLogicGame__AbstractMatchLogic__) */




