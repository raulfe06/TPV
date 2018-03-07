#include "BallPhysics.h"
#include "Collisions.h"
#include "messages.h"

BallPhysics::BallPhysics(GameObject* leftPaddle,
		GameObject* rightPadlle) :
		leftPaddle_(leftPaddle), rightPaddle_(rightPadlle) {

	// TODO Auto-generated constructor stub

}

BallPhysics::~BallPhysics() {
	// TODO Auto-generated destructor stub
}

void BallPhysics::update(GameObject* o, Uint32 time) {

	ball_ = o;
	Vector2D velocity = o->getVelocity();
	Vector2D position = o->getPosition()+velocity;

	double height = o->getHeight();

	// upper wall
	if ( position.getY()+height >= o->getGame()->getWindowHeight() ) {
		velocity.setY( -velocity.getY() );

		Message m { BALL_TOUCHES_WALL };
		send(m);
//		o->getGame()->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
	}

	// lower wall
	if ( position.getY() <= 0 ) {
		velocity.setY( -velocity.getY() );
		// o->getGame()->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
		Message m {  BALL_TOUCHES_WALL  };
		send(m);
	}

	o->setPosition(position);

	// check for collision of ball with paddles
	if (Collisions::collides(o, leftPaddle_)
			|| Collisions::collides(o, rightPaddle_)) {
		velocity.setX(-velocity.getX());
		velocity = velocity*1.2;
		// o->getGame()->getResources()->getSoundEffect(Resources::Paddle_Hit)->play(0);
		Message m { BALL_TOUCHES_PADDLE };
		send(m);
	}
	if (ball_->getPosition().getX() <= 0) {
		Message m { BALL_OUT_LEFT };
		send(m);
	}
	else if (ball_->getPosition().getX() - ball_->getWidth()
		>= ball_->getGame()->getWindowWidth()) {
		Message m { BALL_OUT_RIGHT };
		send(m);
	}
	o->setVelocity(velocity);

}
void BallPhysics::initBall() {
	int dx = 1 - 2 * (rand() % 2); // 1 or -1
	int dy = 1 - 2 * (rand() % 2); // 1 or -1
	Vector2D v(dx * ((rand() % 5) + 2), dy * ((rand() % 5) + 2));
	v.normalize();
	ball_->setVelocity(v * 2);
}
void BallPhysics::roundFinished() {
	ball_->setVelocity(Vector2D(0, 0));
	ball_->setPosition(
		Vector2D(ball_->getGame()->getWindowWidth() / 2 - 6,
			ball_->getGame()->getWindowHeight() / 2 - 6));
	
}
void BallPhysics::receive(Message msg)
{
	switch (msg.id_) {
	case ROUND_START:
		initBall();
		break;
	case ROUND_END:
		roundFinished();
		break;
	}
}