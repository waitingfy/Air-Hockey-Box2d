#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "b2Sprite.h"

USING_NS_CC;

typedef enum tagPlayerState 
{
	kPlayerStateGrabbed,
	kPlayerStateUngrabbed
} PlayerState; 

class Player : public b2Sprite, public CCTargetedTouchDelegate//1. need inherit CCTargetedTouchDelegate
{
	PlayerState        m_state;

public:

	CC_SYNTHESIZE(CCPoint,_nextPosition,NextPosition);

	Player(GameLayer *game,int type, CCPoint position);
	virtual ~Player(void);

	CCRect rect();
	float radius();

	bool containsTouchLocation(CCTouch* touch);

	static Player* create(GameLayer *game,int type, CCPoint position);

	/** 2.Overwrite some virtual function @{ */ 
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
	/** @} */

	virtual void update(float dt);
	virtual void reset();

private:
	void initPlayer();
	CCPoint _startPosition;
};

#endif
