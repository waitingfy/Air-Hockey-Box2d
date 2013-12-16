#ifndef __GOAL_H__
#define __GOAL_H__


#include "b2Sprite.h"

USING_NS_CC;

class Goal : public b2Sprite{

public:
	Goal(GameLayer *game,int type,CCPoint position);
	~Goal();
	static Goal* create(GameLayer *game, int type,CCPoint position);
	void reset();
private:
	void initGoal();
	CCPoint _startPosition;

};















#endif