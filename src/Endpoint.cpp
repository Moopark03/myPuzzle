#include "Endpoint.h"

bool Endpoint::collision(Ball b) {
	return false;
}

void Endpoint::setAdj(int x) {
	adjTile = x;
}

int Endpoint::getAdj() {
	return adjTile;
}