#ifndef _GAMESPRITE_H_
#define _GAMESPRITE_H_

#include "cocos2d.h"

USING_NS_CC;


class GameSprite : public CCSprite{
	CC_SYNTHESIZE(CCPoint, _nextPosition,NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);

	CCSize _screenSize;

	GameSprite(void);
	~GameSprite(void);
	float radius();
	static GameSprite* spriteWithTexture(CCTexture2D* aTexture);
	virtual void setPosition(const CCPoint& pos);
};

#endif