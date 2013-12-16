#include "Player.h"
#include "GameLayer.h"

Player::Player(GameLayer *game,int type, CCPoint position):b2Sprite(game,type){
	_nextPosition = position;
	_startPosition = position;
}

Player::~Player(void)
{
}

Player* Player::create(GameLayer *game,int type, CCPoint position){
	Player *sprite = new Player(game, type, position);
	if(sprite){
		sprite->initPlayer();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Player::initPlayer(){
	m_state = kPlayerStateUngrabbed;

	this->initWithFile("mallet.png");

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
	fixtureDef.density = 10;
	fixtureDef.restitution = 1;
	//fixtureDef.filter.maskBits = 0x0100;


	_body->CreateFixture(&fixtureDef);
	_body->SetUserData(this);

	
	setSpritePosition(_nextPosition);
}

float Player::radius(){
	return getTexture()->getContentSize().width / 2;
}

CCRect Player::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}



void Player::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void Player::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}    

bool Player::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}


bool Player::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (m_state != kPlayerStateUngrabbed) return false;
	if ( !containsTouchLocation(touch) ) return false;//touch on the sprite, then we do something

	m_state = kPlayerStateGrabbed;
	return true;
}

void Player::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

	CCAssert(m_state == kPlayerStateGrabbed, "Player - Unexpected state!");    
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();


	CCPoint tap = touch->getLocation();
	CCPoint nextPosition = tap;
	//keep player in court
	nextPosition = ccp(max(nextPosition.x, radius()), max(nextPosition.y, radius()));
	nextPosition = ccp(min(nextPosition.x, screenSize.width - radius()) ,
		min(nextPosition.y, screenSize.height - radius()));

	//keep player in its area
	if (getPositionY() < screenSize.height * 0.5f) {
		nextPosition.y = min(nextPosition.y, screenSize.height / 2 - radius());
	} else {
		nextPosition.y = max(nextPosition.y, screenSize.height / 2 + radius());
	}
	//CCLOG("nextPosition x:%f, y:%f",nextPosition.x, nextPosition.y);
	setNextPosition(nextPosition);
	_body->SetLinearVelocity(b2Vec2(tap.x -  getPositionX(),tap.y - getPositionY()));

	
}



void Player::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCAssert(m_state == kPlayerStateGrabbed, "Player - Unexpected state!");    

	m_state = kPlayerStateUngrabbed;


} 

void Player::touchDelegateRetain()
{
	this->retain();
}

void Player::touchDelegateRelease()
{
	this->release();
}

void Player::update(float dt){
	setSpritePosition(this->getNextPosition());
}

void Player::reset(){
	if(_body){
		_body->SetLinearVelocity(b2Vec2_zero);
		_body->SetAngularVelocity(0);
		_body->SetAwake(true);
	}
	setSpritePosition(_startPosition);
	setNextPosition(_startPosition);
	setVisible(true);
}