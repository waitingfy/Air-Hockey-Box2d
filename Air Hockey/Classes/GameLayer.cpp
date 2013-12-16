#include "GameLayer.h"
//#include "SimpleAudioEngine.h"


USING_NS_CC;
//using namespace CocosDenshion;

const float BoundingWidth = 0.0f;
//const int GOAL_WIDTH = 400;
#define GOAL_WIDTH 400

GameLayer::~GameLayer(){

	delete _world;
	_world = NULL;
	
	delete m_debugDraw;
	delete _collisionListener;
};


CCScene* GameLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameLayer *layer = GameLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		

        _player1Score = 0;
		_player2Score = 0;
		setScore(kNoneGetScore);

		_screenSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *court = CCSprite::create("court1.png");
		CC_BREAK_IF(!court);
		court->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
		this->addChild(court);

		initPhysics();

		

		_player1ScoreLabel = CCLabelTTF::create("0","Arial",60);
		_player1ScoreLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 - 80));
		_player1ScoreLabel->setRotation(90);
		this->addChild(_player1ScoreLabel);

		_player2ScoreLabel = CCLabelTTF::create("0","Arial",60);
		_player2ScoreLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 + 80));
		_player2ScoreLabel->setRotation(90);
		this->addChild(_player2ScoreLabel);

		this->setTouchEnabled(true);

		this->schedule(schedule_selector(GameLayer::update));


		resetGame();
        bRet = true;
    } while (0);

    return bRet;
}


void GameLayer::initPhysics(){
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);//我们是在一个平面上，所以只需要将重力加速度设置为0
	_world = new b2World(gravity);

	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);
	_collisionListener = new CollisionListener();//b2ContactListener，这里可以自定义处理物体碰撞发生的事情
	                                             //比如球碰到球门，我们希望重置游戏。
	_world->SetContactListener(_collisionListener);

	m_debugDraw = new GLESDebugDraw(PTM_RATIO);
	_world->SetDebugDraw(m_debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	m_debugDraw->SetFlags(flags);


	CCPoint player1Position = ccp(_screenSize.width * 0.5, 80);
	_player1 =(Player*) Player::create(this,kPlayer1Tag,player1Position);
	this->addChild(_player1, 0, kPlayer1Tag);

	CCPoint player2Position = ccp(_screenSize.width * 0.5, _screenSize.height -  80);
	_player2 =(Player*) Player::create(this,kPlayer2Tag,player2Position);
	this->addChild(_player2, 0, kPlayer2Tag);

	CCPoint ballPosition = ccp(_screenSize.width * 0.5, _screenSize.height * 2 / 5);
	_ball = Ball::create(this,kBall,ballPosition);
	this->addChild(_ball);

	CCPoint goalTopPosition = ccp(_screenSize.width * 0.5, _screenSize.height + _ball->radius() * 2);
	_goalTop = Goal::create(this,kGoalTop,goalTopPosition);
	this->addChild(_goalTop);

	CCPoint goalBottomPosition = ccp(_screenSize.width * 0.5,0 - _ball->radius() * 2);
	_goalBottom = Goal::create(this,kGoalBottom,goalBottomPosition);
	this->addChild(_goalBottom);



	b2BodyDef tableBodyDef;
	tableBodyDef.position.Set(0, 0);
	b2Body *tableBody = _world->CreateBody(&tableBodyDef);

	b2EdgeShape tableBox;
	//bottom
	tableBox.Set(b2Vec2(0.0f, 0.0f),
		b2Vec2((_screenSize.width / 2 - GOAL_WIDTH / 2) / PTM_RATIO,0.0f));
	tableBody->CreateFixture(&tableBox, 0);

	tableBox.Set(b2Vec2((_screenSize.width - (_screenSize.width / 2 - GOAL_WIDTH / 2)) / PTM_RATIO, 0.0f),
		b2Vec2(_screenSize.width / PTM_RATIO,0.0f));
	tableBody->CreateFixture(&tableBox, 0);

	//top
	tableBox.Set(b2Vec2(0.0f , _screenSize.height / PTM_RATIO),
		b2Vec2((_screenSize.width / 2 - GOAL_WIDTH / 2) / PTM_RATIO, _screenSize.height / PTM_RATIO));
	tableBody->CreateFixture(&tableBox,0);

	tableBox.Set(b2Vec2((_screenSize.width - (_screenSize.width / 2 - GOAL_WIDTH / 2)) / PTM_RATIO , _screenSize.height / PTM_RATIO),
		b2Vec2(_screenSize.width / PTM_RATIO, _screenSize.height / PTM_RATIO));
	tableBody->CreateFixture(&tableBox,0);

	//left
	tableBox.Set(b2Vec2(0.0f, 0.0f),b2Vec2(0.0f,_screenSize.height / PTM_RATIO));
	tableBody->CreateFixture(&tableBox,0);
	
	//right
	tableBox.Set(b2Vec2(_screenSize.width / PTM_RATIO, 0.0f),
		b2Vec2(_screenSize.width / PTM_RATIO, _screenSize.height / PTM_RATIO));
	tableBody->CreateFixture(&tableBox, 0);
	
	//
	
}


void GameLayer::update(float delta){
		_world->Step(delta, 10, 10);
		_ball->update(delta);
		_player1->update(delta);
		_player2->update(delta);
	
		if(getScore() == kPlayer1GetScore){
			this->playerScore(1);
			setScore(kNoneGetScore);
		}else if(getScore() == kPlayer2GetScore){
			this->playerScore(2);
			setScore(kNoneGetScore);
		}
}

void GameLayer::draw(){
	CCLayer::draw();

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
	kmGLPushMatrix();
	_world->DrawDebugData();
	kmGLPopMatrix();
}

void GameLayer::playerScore (int player) {

	//SimpleAudioEngine::sharedEngine()->playEffect("score.wav");
	_ball->reset();

	char score_buffer[10];

	//if player 1 scored...
	if (player == 1) {

		_player1Score++;
		sprintf(score_buffer,"%i", _player1Score);
		_player1ScoreLabel->setString(score_buffer);
		//move ball to player 2 court
		_ball->setSpritePosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 + 2 * _ball->radius()));

		//if player 2 scored...
	} else {

		_player2Score++;
		sprintf(score_buffer,"%i", _player2Score);
		_player2ScoreLabel->setString(score_buffer);
		//move ball to player 1 court
		_ball->setSpritePosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5 - 2 * _ball->radius()));

	}
	//move players to original position
	_player1->reset();
	_player2->reset();

}

void GameLayer::resetGame(){
	_ball->reset();
	_player1->reset();
	_player2->reset();
}