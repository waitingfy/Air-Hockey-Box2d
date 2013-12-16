#ifndef _BALL_H_
#define _BALL_H_

#include "b2Sprite.h"

USING_NS_CC;

class Ball : public b2Sprite{

public:
	Ball(GameLayer *game,int type, CCPoint position);
	~Ball(void);
	static Ball* create(GameLayer *game,int type, CCPoint position);
	virtual void reset(void);
	virtual void update(float dt);
	float radius();
private:
	void initBall();
	CCPoint _startPosition;

};




#endif