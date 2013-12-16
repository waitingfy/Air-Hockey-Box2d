#ifndef __MINIPOLL_COLLISIONLISTENER__
#define __MINIPOLL_COLLISIONLISTENER__

#include "Box2D/Box2D.h"

class CollisionListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
};


#endif