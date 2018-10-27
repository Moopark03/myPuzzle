#pragma once
#include "ofMain.h"
#include "Ball.h"

class Endpoint {
private:
	int adjTile; //The tile number the endpoint will be adjacent to

public:
	void setAdj(int x);
	int getAdj();
	bool collision(Ball b);
};