#include "Ball.h"
#include "GameLayer.h"
//#include "SimpleAudioEngine.h"


//using namespace CocosDenshion;



Ball::Ball(GameLayer *game,int type, CCPoint position):b2Sprite(game,type){
	_startPosition = position;
}

Ball::~Ball(void){

}

Ball* Ball::create(GameLayer *game, int type, CCPoint position){
	Ball *sprite = new Ball(game, type,position);
	if(sprite){
		sprite->initBall();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

float Ball::radius(){
	CCAssert(getTexture() != NULL, "should set texture first!");
	return getTexture()->getContentSize().width * 0.5f;
}

void Ball::initBall(){
	this->initWithFile("puck.png");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	_body = _game->getWorld()->CreateBody(&bodyDef);
	_body->SetSleepingAllowed(true);
	_body->SetLinearDamping(1.2);
	_body->SetAngularDamping(0.8);

	b2CircleShape circle;
	circle.m_radius = radius() / PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 5;
	fixtureDef.restitution = 0.7;
	//fixtureDef.filter.categoryBits = 0x0100;

	_body->CreateFixture(&fixtureDef);
	_body->SetUserData(this);

	setSpritePosition(_startPosition);

	
}

void Ball::reset(){
	if(_body){
		_body->SetLinearVelocity(b2Vec2_zero);
		_body->SetAngularVelocity(0);
		_body->SetAwake(true);
	}
	setSpritePosition(_startPosition);
	setVisible(true);
}

void Ball::update(float dt){
	if(_body && isVisible()){
		//CCLOG("ball's body position x:%f, y:%f",_body->GetPosition().x, _body->GetPosition().y);
		setPositionX(_body->GetPosition().x * PTM_RATIO);
		setPositionY(_body->GetPosition().y * PTM_RATIO);
	}

	
}






