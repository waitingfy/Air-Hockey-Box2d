#ifndef __MINIPOOL_B2SPRITE__
#define __MINIPOOL_B2SPRITE__

#define PTM_RATIO 32.0
#define BALL_RADIUS 16.0

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class GameLayer;

enum{
	kSpritePlayer,
	kSpriteBall,
	kSpriteCue,
	kSpritePocket
};

USING_NS_CC;

class b2Sprite : public CCSprite{
public:
	b2Sprite(GameLayer *game, int type);

	CC_SYNTHESIZE(b2Body*, _body, Body);
	CC_SYNTHESIZE(GameLayer*, _game, Game);
	CC_SYNTHESIZE(int, _type, Type);
	
	virtual void setSpritePosition(CCPoint position);
	virtual void update(float dt);
	virtual void hide(void);
	virtual void reset(void);
	virtual float mag();
};



#endif