#include "CollisionListener.h"
#include "GameLayer.h"
//#include ""

void CollisionListener::BeginContact(b2Contact* contact){
	b2Body *bodyA = contact->GetFixtureA()->GetBody();
	b2Body *bodyB = contact->GetFixtureB()->GetBody();

	b2Sprite *spriteA = (b2Sprite *)bodyA->GetUserData();
	b2Sprite *spriteB = (b2Sprite *)bodyB->GetUserData();

	if(spriteA && spriteB){
		if(spriteA->getType() == kGoalTop && spriteB->getType() == kBall){
			spriteB->getGame()->setScore(kPlayer1GetScore);
		}else if(spriteB->getType() == kGoalTop && spriteA->getType() == kBall){
			spriteB->getGame()->setScore(kPlayer1GetScore);
		}else if(spriteA->getType() == kGoalBottom && spriteB->getType() == kBall){
			spriteB->getGame()->setScore(kPlayer2GetScore);
		}else if(spriteB->getType() == kGoalBottom && spriteA->getType() == kBall){
			spriteB->getGame()->setScore(kPlayer2GetScore);
		}
	}
}

void CollisionListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){

}