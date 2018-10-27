#pragma once
#include "ofMain.h"

class Ball {
private:
	
	//ofImage spr; // Sprite
	ofVec2f pos; //position of object
	ofVec2f speed;
	float radius;
	ofImage ball;

public:
	void setup();
	void draw();
	void update();
	void setPos(ofVec2f x);
	void setSpeed(ofVec2f xy);

	ofVec2f getPos();
};
