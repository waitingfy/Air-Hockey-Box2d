#include "Goal.h"
#include "GameLayer.h"

Goal::Goal(GameLayer *game,int type,CCPoint position):b2Sprite(game,type){
	_startPosition = position;
}

Goal::~Goal(){

}

Goal* Goal::create(GameLayer *game, int type,CCPoint position){
	Goal* sprite = new Goal(game,type,position);
	if(sprite){
		sprite->initGoal();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Goal::initGoal(){
	this->initWithFile("tansparent.png");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	_body = _game->getWorld()->CreateBody(&bodyDef);

	b2PolygonShape polygon;//球门定义为一个四边形
	polygon.SetAsBox(GOAL_WIDTH / 2 / PTM_RATIO,10 / PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygon;
	fixtureDef.isSensor = true;//不参加碰撞

	_body->CreateFixture(&fixtureDef);
	_body->SetUserData(this);
	setSpritePosition(_startPosition);
}

void Goal::reset(){
	if(_body){
		_body->SetLinearVelocity(b2Vec2_zero);
		_body->SetAngularVelocity(0);
		_body->SetAwake(true);
	}
}