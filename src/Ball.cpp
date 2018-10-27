#include "Ball.h"

void Ball::setup(){
	radius = 5.0;
	speed = ofVec2f(0.0, 0.0);
	pos = ofVec2f(0, 0);
	ball.load("spr/Ball.png");
}

void Ball::update() {
	//update position here
	pos += (speed / ofGetFrameRate());
}

void Ball::draw(){
	ball.draw(pos, radius, radius);
}

void Ball::setSpeed(ofVec2f xy) {//Should come in as (1.0, 0.0) style for vertical or horizontal
	//Set speed as how may px to move in 1 second
	speed = xy;
}

void Ball::setPos(ofVec2f x) {
	pos = x;
}

ofVec2f Ball::getPos() {
	return pos;
}