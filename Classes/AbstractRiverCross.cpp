#include "AbstractRiverCross.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "LevelChooserScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;


bool AbstractRiverCross::isLeft = false;
int AbstractRiverCross::boatSize = 1;
bool AbstractRiverCross::itemTouch = false;
int AbstractRiverCross::level_num = 0;

cocos2d::Node* AbstractRiverCross::rootNode;



Scene* AbstractRiverCross::createScene()
{
	auto scene = Scene::create();
	AbstractRiverCross::rootNode = CSLoader::createNode("CrossRiverScene.csb");
	auto layer = AbstractRiverCross::create();
	scene->addChild(layer);
	return scene;
}

bool AbstractRiverCross::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	visibleSize = Director::getInstance()->getVisibleSize();

	rightVec.clear();
	midVec.clear();
	leftVec.clear();
	isLeft = false;

	isHelped = false;
	help_frame = rootNode->getChildByName("help_frame");
	help_frame->setZOrder(10);
	help_frame->setVisible(false);

	help_btn = dynamic_cast<ui::Button*>(rootNode->getChildByName("help_btn"));
	help_btn->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::help_btn_function, this));

	next_btn = dynamic_cast<ui::Button*>(rootNode->getChildByName("next_btn"));
	next_btn->setVisible(false);
	next_btn->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::next_btn_function, this));

	finish_layer = rootNode->getChildByName("finish_layer");
	finish_layer->setVisible(false);

	gameover_layer = rootNode->getChildByName("gameover_layer");
	gameover_layer->setVisible(false);

	menu_layer = rootNode->getChildByName("menu_layer");
	menu_btn_hide = dynamic_cast<ui::Button*>(menu_layer->getChildByName("menu_btn_hide"));
	menu_btn_hide->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::menu_hide_btn, this));
	menu_layer->setVisible(false);

	auto btn_list = dynamic_cast<ui::ListView*>(menu_layer->getChildByName("btn_list"));

	auto back_btn = dynamic_cast<ui::Button*>(btn_list->getChildByName("back_btn"));
	back_btn->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::back_btn_function, this));
	auto volume_btn = dynamic_cast<ui::Button*>(btn_list->getChildByName("volume_btn"));
	volume_btn->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::volume_btn_function, this));
	auto res_btn = dynamic_cast<ui::Button*>(btn_list->getChildByName("res_btn"));
	res_btn->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::res_btn_function, this));

	menu_btn_show = dynamic_cast<ui::Button*>(rootNode->getChildByName("menu_btn_show"));
	menu_btn_show->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::menu_show_btn, this));


	this->lets_go_btn = dynamic_cast<ui::Button*>(rootNode->getChildByName("go_btn"));
	this->lets_go_btn->addClickEventListener(CC_CALLBACK_1(AbstractRiverCross::go_btn, this));

	addChild(rootNode);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(AbstractRiverCross::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(AbstractRiverCross::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(AbstractRiverCross::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(AbstractRiverCross::onTouchCancelled, this);


	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	boat_back = dynamic_cast<Sprite*>(rootNode->getChildByName("thuyen1_2_2"));
	boat_back->setZOrder(3);

	boat_front = dynamic_cast<Sprite*>(boat_back->getChildByName("thuyen1_1_3"));
	boat_front->setZOrder(-2);

	isTouchDown = false;

	initialTouchPos[0] = 0;
	initialTouchPos[1] = 0;

	this->scheduleUpdate();
	float tmp_height = (boatSize == 1) ? (boat_back->getContentSize().height / 5 * 2) : (boat_back->getContentSize().height / 2);

	boat_pos_vec.push_back(Vec2(boat_back->getContentSize().width / 5 * 2, tmp_height));
	boat_pos_vec.push_back(Vec2(boat_back->getContentSize().width / 5 * 3, tmp_height));
    
    savePosVector.push_back(Vec2(-1,-1));
    savePosVector.push_back(Vec2(-1,-1));
    
	help_btn_function(nullptr);

	return true;
}

void AbstractRiverCross::update(float dt)
{
	if (true == isTouchDown && !itemTouch)
	{
		if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
		{
			//CCLOG("SWIPED LEFT");
			if (!isLeft){
				go_btn(lets_go_btn);
			}
			isTouchDown = false;
		}
		else if (initialTouchPos[0] - currentTouchPos[0] < -visibleSize.width * 0.05)
		{
			//CCLOG("SWIPED RIGHT");
			if (isLeft){
				go_btn(lets_go_btn);
			}
			isTouchDown = false;
		}
		else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
		{
			//CCLOG("SWIPED DOWN");

			isTouchDown = false;
		}
		else if (initialTouchPos[1] - currentTouchPos[1] < -visibleSize.width * 0.05)
		{
			//CCLOG("SWIPED UP");

			isTouchDown = false;
		}
		else;
	}
}
static int boat_order = 0;
bool AbstractRiverCross::onTouchBegan(Touch *touch, Event *event)
{
	if (!lets_go_btn->isEnabled()) return true;
	
    if (isLeft){
		if (boat_back->boundingBox().containsPoint(touch->getLocation()) && midVec.size() > 0){
            if (midVec.size() == 1){
                if (boat_back->getPosition().x >= touch->getLocation().x && !(savePosVector[0].x == -1 && savePosVector[0].y == -1)){
                    boat_back->removeChild(midVec[0], true);
                    midVec[0]->setPosition(savePosVector[0]);
                    leftVec.push_back(midVec[0]);
                    this->addChild(midVec[0]);
                    midVec.erase(midVec.begin() );
                    itemTouch = true;
                    savePosVector[0] = Vec2(-1,-1);
                }else
                if (boat_back->getPosition().x < touch->getLocation().x && !(savePosVector[1].x == -1 && savePosVector[1].y == -1)){
                    boat_back->removeChild(midVec[0], true);
                    midVec[0]->setPosition(savePosVector[1]);
                    leftVec.push_back(midVec[0]);
                    this->addChild(midVec[0]);
                    midVec.erase(midVec.begin() );
                    itemTouch = true;
                    savePosVector[1] = Vec2(-1,-1);
                }else;
            }else
            if (midVec.size() == 2){
                if (boat_back->getPosition().x >= touch->getLocation().x){
                    boat_back->removeChild(midVec[0], true);
                    midVec[0]->setPosition(savePosVector[0]);
                    leftVec.push_back(midVec[0]);
                    this->addChild(midVec[0]);
                    midVec.erase(midVec.begin());
                    itemTouch = true;
                    savePosVector[0] = Vec2(-1,-1);
                }else{
                    boat_back->removeChild(midVec[1], true);
                    midVec[1]->setPosition(savePosVector[1]);
                    leftVec.push_back(midVec[1]);
                    this->addChild(midVec[1]);
                    midVec.erase(midVec.begin()+1);
                    itemTouch = true;
                    savePosVector[1] = Vec2(-1,-1);
                }
            }else;
		}
        
		for (int i = 0; i < leftVec.size(); i++){
			if (leftVec[i]->boundingBox().containsPoint(touch->getLocation()) && boatSize>midVec.size()){
                
                boat_order = (savePosVector[0].x == -1 && savePosVector[0].y == -1) ? 0 : 1;
                
                savePosVector[boat_order] = leftVec[i]->getPosition();
				leftVec[i]->setPosition(boat_pos_vec[boat_order]);

				boat_back->addChild(leftVec[i]);
                
                
                if (boat_order == 0)
                    midVec.insert(midVec.begin(), leftVec[i]);
                else
                    midVec.push_back(leftVec[i]);
				boat_front->setZOrder(-2);
				leftVec[i]->setZOrder(-1);
				leftVec.erase(leftVec.begin() + i);
				itemTouch = true;
				break;
			}
		}
	}
	else{
		if (boat_back->boundingBox().containsPoint(touch->getLocation())  && midVec.size() > 0){
            if (midVec.size() == 1){
                if (boat_back->getPosition().x >= touch->getLocation().x && !(savePosVector[0].x == -1 && savePosVector[0].y == -1)){
                    boat_back->removeChild(midVec[0], true);
                    midVec[0]->setPosition(savePosVector[0]);
                    rightVec.push_back(midVec[0]);
                    this->addChild(midVec[0]);
                    midVec.erase(midVec.begin() );
                    itemTouch = true;
                    savePosVector[0] = Vec2(-1,-1);
                }else
                if (boat_back->getPosition().x < touch->getLocation().x && !(savePosVector[1].x == -1 && savePosVector[1].y == -1)){
                    boat_back->removeChild(midVec[0], true);
                    midVec[0]->setPosition(savePosVector[1]);
                    rightVec.push_back(midVec[0]);
                    this->addChild(midVec[0]);
                    midVec.erase(midVec.begin() );
                    itemTouch = true;
                    savePosVector[1] = Vec2(-1,-1);
                }else;
            }else
            if (midVec.size() == 2){
                if (boat_back->getPosition().x >= touch->getLocation().x){
                    boat_back->removeChild(midVec[0], true);
                    midVec[0]->setPosition(savePosVector[0]);
                    rightVec.push_back(midVec[0]);
                    this->addChild(midVec[0]);
                    midVec.erase(midVec.begin());
                    itemTouch = true;
                    savePosVector[0] = Vec2(-1,-1);
                }else{
                    boat_back->removeChild(midVec[1], true);
                    midVec[1]->setPosition(savePosVector[1]);
                    rightVec.push_back(midVec[1]);
                    this->addChild(midVec[1]);
                    midVec.erase(midVec.begin()+1);
                    itemTouch = true;
                    savePosVector[1] = Vec2(-1,-1);
                }
            }else;
		}

		for (int i = 0; i < rightVec.size(); i++){
			if (rightVec[i]->boundingBox().containsPoint(touch->getLocation()) && boatSize>midVec.size()){
                
                boat_order = (savePosVector[0].x == -1 && savePosVector[0].y == -1) ? 0 : 1;
				
                savePosVector[boat_order] = rightVec[i]->getPosition();
				rightVec[i]->setPosition(boat_pos_vec[boat_order]);

				boat_back->addChild(rightVec[i]);
                
                if (boat_order == 0)
                    midVec.insert(midVec.begin(), rightVec[i]);
                else
                    midVec.push_back(rightVec[i]);
                
				boat_front->setZOrder(-2);
				rightVec[i]->setZOrder(-1);
				rightVec.erase(rightVec.begin() + i);
				itemTouch = true;
				break;
			}
		}
	}

	initialTouchPos[0] = touch->getLocation().x;
	initialTouchPos[1] = touch->getLocation().y;
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;

	isTouchDown = true;

	return true;
}

void AbstractRiverCross::onTouchMoved(Touch *touch, Event *event)
{
	currentTouchPos[0] = touch->getLocation().x;
	currentTouchPos[1] = touch->getLocation().y;
}

void AbstractRiverCross::onTouchEnded(Touch *touch, Event *event)
{
	isTouchDown = false;
	itemTouch = false;
}

void AbstractRiverCross::onTouchCancelled(Touch *touch, Event *event)
{
	onTouchEnded(touch, event);
}

void AbstractRiverCross::go_btn(Ref* pSender){
    if (boatSize != 1 && midVec.size() == 0) return;
	auto btn = (ui::Button*)pSender;
	Size sizeV = Director::getInstance()->getVisibleSize();
	lets_go_btn->setEnabled(false);
	(!isLeft) ? isLeft = true : isLeft = false;

	for (auto i : midVec){
		i->runAction(FlipX::create(!isLeft));
	}
	lets_go_btn->setEnabled(false);
	boat_back->runAction(Sequence::create(MoveTo::create(0.7, Vec2(sizeV.width - boat_back->getPositionX(), boat_back->getPositionY())),
		CallFunc::create(CC_CALLBACK_0(AbstractRiverCross::flipX_function, this)), NULL));
}

void AbstractRiverCross::flipX_function(){
	Size sizeV = Director::getInstance()->getVisibleSize();

	boat_back->runAction(FlipX::create(isLeft));
	boat_front->runAction(FlipX::create(isLeft));
	lets_go_btn->setEnabled(true);

    int tool = 0;
	for (auto i : midVec){
		boat_back->removeChild(i, true);
        if (savePosVector[tool].x == -1 && savePosVector[tool].y == -1) tool++;
		i->setPosition(Vec2(sizeV.width - savePosVector[tool].x, savePosVector[tool].y));
        savePosVector[tool++] = Vec2(-1,-1);
		if (isLeft){
			leftVec.push_back(i);
		}
		else{
			rightVec.push_back(i);
		}
		this->addChild(i);
		i->runAction(FlipX::create(isLeft));
	}
	midVec.clear();
	checkLogic();
	lets_go_btn->setEnabled(true);
}


void AbstractRiverCross::checkLogic(){
    
}

void AbstractRiverCross::gameOver(){
	lets_go_btn->setVisible(false);
	gameover_layer->setVisible(true);
	setCascadeOpacityEnabled(true);
	setOpacity(180);
	menu_show_btn(nullptr);
	this->pause();
}

void AbstractRiverCross::winLevel(){
	lets_go_btn->setVisible(false);
	finish_layer->setVisible(true);
	setOpacity(180);
	menu_show_btn(nullptr);
	this->pause();
	UserDefault::getInstance()->setIntegerForKey("type-1", fmax(level_num + 1, UserDefault::getInstance()->getIntegerForKey("type-1")));
	next_btn->setVisible(true);
}

void AbstractRiverCross::menu_show_btn(Ref* pSender){
	menu_layer->setVisible(true);
	menu_btn_show->setVisible(false);
}
void AbstractRiverCross::menu_hide_btn(Ref* pSender){
	menu_layer->setVisible(false);
	menu_btn_show->setVisible(true);
}

void AbstractRiverCross::res_btn_function(Ref* pSender){
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(createScene());
}
void AbstractRiverCross::back_btn_function(Ref* pSender){
	Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    Director::getInstance()->pushScene(LevelChooserScene::createScene());
}
static bool isMute = false;
void AbstractRiverCross::volume_btn_function(Ref* pSender){
	(!isMute) ? isMute = true : isMute = false;

	if (!isMute){
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

void AbstractRiverCross::help_btn_function(Ref* pSender){
	if (!isHelped){
		help_frame->setVisible(true);
		isHelped = true;
		help_btn->loadTextures("menu/bt_Help2.png", "menu/bt_Help1.png", "");
		lets_go_btn->setVisible(false);
		pause();
	}else{
		help_frame->setVisible(false);
		isHelped = false;
		help_btn->loadTextures("menu/bt_Help1.png", "menu/bt_Help2.png", "");
		lets_go_btn->setVisible(true);
		resume();
	}
}

void AbstractRiverCross::next_btn_function(Ref* pSender){
	auto scene = LevelChooserScene::getLevelScene("CR", level_num + 1);
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
}