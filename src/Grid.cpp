#include "Grid.h"



int Grid::getX() {
	return x;
}

int Grid::getY() {
	return y;
}

int Grid::getPiece() {
	return piece;
}

void Grid::setX(int in) {
	x = in;
}

void Grid::setY(int in) {
	y = in;
}

void Grid::setPiece(int in) {
	piece = in;
}

void Grid::setup() {
	floor.load("images/grass.png");
}

void Grid::draw(int x, int y, int w, int h) {
	floor.draw(x, y, w, h);
}