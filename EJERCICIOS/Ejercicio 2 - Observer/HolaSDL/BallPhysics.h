#ifndef BALLPHYSICS_H_
#define BALLPHYSICS_H_

#include "PhysicsComponent.h"
#include "Observable.h"
#include "Observer.h"

/*
 *
 */
class BallPhysics: public PhysicsComponent, public Observable,public Observer {
public:
	BallPhysics(GameObject* leftPaddle, GameObject* rightPadlle);
	virtual ~BallPhysics();
	virtual void update(GameObject* o, Uint32 time);
	void initBall();

	void roundFinished();
	
private:
	GameObject* leftPaddle_;
	GameObject* rightPaddle_;
	GameObject* ball_;
	void receive(Message msg);
};

#endif /* BALLPHYSICS_H_ */
