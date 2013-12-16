#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#define GOAL_WIDTH 400

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Player.h"
#include "Ball.h"
#include "Goal.h"
#include "CollisionListener.h"
#include "GLES_Render.h"

enum {
	kPlayer1Tag,
	kPlayer2Tag,
	kBall,
	kGoalTop,
	kGoalBottom
};

typedef enum{
	kPlayer1GetScore,
	kPlayer2GetScore,
	kNoneGetScore
} WhoGetScore;


USING_NS_CC;

class GameLayer : public CCLayer
{

	Player *_player1;
	Player *_player2;

	Ball *_ball;

	Goal *_goalTop;
	Goal *_goalBottom;
	
	CCLabelTTF *_player1ScoreLabel;
	CCLabelTTF *_player2ScoreLabel;

	CCSize _screenSize;

	int _player1Score;
	int _player2Score;

	

public:

	CC_SYNTHESIZE(b2World*, _world, World);//定义一个b2World指针变量，它将设置一些属性，然后一些
	                                       //物体比如圆形的方形的都将由它创建
	CC_SYNTHESIZE(WhoGetScore,_score, Score);

	~GameLayer();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	void update(float delta);

	void initPhysics();
	virtual void draw();
	void playerScore(int player);
private:
	GLESDebugDraw *m_debugDraw;
	b2ContactListener *_collisionListener;

	void resetGame();
};

#endif  // __HELLOWORLD_SCENE_H__