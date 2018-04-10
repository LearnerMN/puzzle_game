//
//  MatchLogicScene.h
//  TestLogicGame
//
//  Created by LearnerMN on 3/21/15.
//
//

#ifndef __TestLogicGame__MatchLogicScene__
#define __TestLogicGame__MatchLogicScene__

#include "AbstractMatchLogic.h"
class MatchLogicScene : public AbstractMatchLogic
{
public:
    
    virtual void add_custom_controller();
    virtual void finish_situation();
    virtual void begin_situation();
	virtual void res_btn_function(Ref* pSender);
    
	static cocos2d::Scene* createScene(std::string first,std::string second,int move_match);
	virtual bool init();
    
	CREATE_FUNC(MatchLogicScene);
};

#endif /* defined(__TestLogicGame__MatchLogicScene__) */