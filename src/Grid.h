#pragma once
#include "ofMain.h"

class Grid{
private:
	int x;
	int y;
	int piece; //The vector<Grid>'s index will be to reference how many pieces to lay down based on size.
	ofImage floor;		   //Piece will be 0, 1, 2 for floor, /, \
	

public:
	int getX();
	int getY();
	int getPiece();

	void setX(int in);
	void setY(int in);
	void setPiece(int in);
	void setup();
	void draw(int x, int y, int w, int h);

};

