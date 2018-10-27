#include "Board.h"

//have piece have different states, 0-4;
//0 = floor, 1 = /, 2 = \; maybe inside the interaction class
//0. add a floor object to interaction class
//1. Build board in memory, adding floor object from the interaction class by the size of the sprite
//2. Select a random edge tile using the algorithm in phone
//3. Get tile position - determine which edge, offset the selected tile position by one tile size and place end point
//4. determine how many bumpers to put up
//5. from selected tile, randomize first bumper location - see phone
//6. move onto ball

//build board vertically
//Keep the loops for drawing function
//The board in this state can be built without drawing

void Board::setup() {

}

void Board::buildBoard() {//position x and y will change, size will not
	if (!(board.empty())){ //when called after level change
		board.clear();
	}
	ofSeedRandom(ofGetSystemTimeMicros());
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			temp.setup();
			temp.setY(y);
			temp.setX(x);
			temp.setPiece(0);
			board.push_back(temp);
		}
	}//fills board of the level size with tile indicators on
	
	random = (int)ofRandom(3); //Selects which side of the board to randomly select an endpoint on. 0 = bottom, 1 = Left, 2 = top, 3 = right
	endPoint.setAdj(selectEnd(random)); //endpoint.adjTile holds the tile to go off of
	buildBumpers(endPoint.getAdj());
	if (bumpSize > 0) {
		randomBump();
	}




}

void Board::draw() { //How to make framed box
	//for (int x = 0; x < box.size(); x++) {
	//	ofSetLineWidth(3.0);
	//	ofSetColor(ofColor::black);
	//	ofNoFill();
	//	ofDrawRectangle(box[x]);
	//}
	int posX = width;
	int posY = height;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			board[findIndex(x, y)].draw(posX * x + 1, posY * y + 1, width, height);//works
		}
		
	}

	}


int Board::selectEnd(int random) {
	switch (random) {
	case 0: //bottom
		//int adj = 
		return ((int)ofRandom((size * size - size), (size*size - 1)));
		//break;
	case 1: //Left side
		return (0 + (int)ofRandom(0, size - 1) * size);
		//break;
	case 2: //top
		return ((int)ofRandom(0, size - 1));
		//break;
	case 3: //right side
		return(size * (int)ofRandom(1, size)) - 1;
		//break;
	}
}

void Board::setSize(int x) {
	size = x;
}

void Board::buildBumpers(int index) {
	ofSeedRandom(ofGetSystemTimeMicros());
	//Information I need:
	// 1. Tile that endpoint is next to (endPoint.getAdj())
	// 2. Which side the end point is on (random) if 0 = bottom, 1 = left side, 2 = top side, 3 = bottom
	// 3. bumpSize, how many bumpers to make
	// 4. A method to randomly select which bumper orientation
	int curX = board[index].getX(); //what to search for
	int curY = board[index].getY();
	int newX;
	int newY;
	int newIndex;
	int piece;
	int seed = (int)ofRandom(1000);

	if (seed & 1) {
		piece = 1;
	}
	else {
		piece = 2;
	} //checks if random seed is odd or even
	//assigns bumper to place

	if (bumpSize == 0) {
		return;
	}

		switch (random) { //index coming in is the tile being worked on, random determines which way the ball travels
		case 0: //going up, only need to find a random y
			newY = (int)ofRandom(0, curY - 1);
			newIndex = findIndex(curX, newY);
			break;
		case 1:
			newX = (int)ofRandom(curX + 1, size - 1);
			newIndex = findIndex(newX, curY);
			break;
		case 2:
			newY = (int)ofRandom(curY + 1, size - 1);
			newIndex = findIndex(curX, newY);
			break;
		case 3:
			newX = (int)ofRandom(0, curX - 1);
			newIndex = findIndex(newX, curY);
			break;
		}

		//checkOffBoard(int newIndex); This is for checking if the newIndex is on the blocked list
		if (checkOffBoard(newIndex)) {
			newIndex = fixBlock(curX, curY);
			if (newIndex == -1) {
				//change current location bumper, update random, call buildboard again, return after to return this call when it comes back
				if (board[index].getPiece() == 1) {
					board[index].setPiece(2);
				}
				else {
					board[index].setPiece(1);
				}
				setNewOrient(board[index].getPiece());
				buildBumpers(index);
				return;
			}
			else {
				board[newIndex].setPiece(piece);
				bumpSize--;
				setNewOrient(piece);
				offBoard.push_back(newIndex);
				buildBumpers(newIndex);
				return;
			}
		}
		else {
			board[newIndex].setPiece(piece);
			bumpSize--;
			setNewOrient(piece);
			offBoard.push_back(newIndex);
			buildBumpers(newIndex);
			return;
		}
		
	
}

int Board::findIndex(int x, int y) {

	for (int i = 0; i < size; i++) { //Checking top row of grid (first row of tiles)
		if (board[i].getX() == x) { //Check X
			for (int t = 0; t < size; t++) { //Check Y
				int mult = t * size; //If y = 0, mult = 0, if y = max, mult = size * size - 1
				if (board[i + mult].getY() == y) { //i + mult would give us going down Y
					return i + mult; //return the index found
				}
			}
		}
	}
}

bool Board::checkOffBoard(int x) {//Returns true if index thrown in is on the blocked list
	if (offBoard.size() == 0) {
		return false;
	}
	for (int i = 0; i < offBoard.size(); i++) {
		if (x == offBoard[i]) {
			return true;
		}
	}

	return false;
}

int Board::fixBlock(int x, int y) { //if successful, return correct index, if not, return -1
	int test;
	int testX = x, testY = y;
	switch (random) { //index coming in is the tile being worked on, random determines which way the ball travels
	case 0:
		for (int i = 0; i <= y - 1; i++) {
			testY -= 1;
			test = findIndex(x, testY);
			if (!checkOffBoard(test)) {
				return test;
			}
		}
		return -1; //Fail Case
		break;
	case 1:
		for (int i = x; i <= size - 1; i++) {
			testX += 1;
			test = findIndex(testX, y);
			if (!checkOffBoard(test)) {
				return test;
			}
		}
		return -1;
		break;
	case 2:
		for (int i = y; i <= size - 1; i++) {
			testY += 1;
			test = findIndex(x, testY);
			if (!checkOffBoard(test)) {
				return test;
			}
		}
		return -1;
		break;
	case 3:
		for (int i = 0; i <= x - 1; i++) {
			testX -= 1;
			test = findIndex(testX, y);
			if (!checkOffBoard(test)) {
				return test;
			}
		}
		return -1;
		break;
	}
}

void Board::setNewOrient(int piece) { //piece = 1 "/", piece = 2 "\"
	switch (random) {//current orientation
	case 0: //going up
		if (piece == 1) {
			random = 1;
		}
		else if (piece == 2) {
			random = 3;
		}
		break;
	case 1: //going right
		if (piece == 1) {
			random = 0;
		}
		else if (piece == 2) {
			random = 2;
		}
		break;
	case 2: //going down
		if (piece == 1) {
			random = 3;
		}
		else if (piece == 2) {
			random = 1;
		}
		break;
	case 3: //going left
		if (piece == 1) {
			random = 2;
		}
		else if (piece == 2) {
			random = 0;
		}
		break;
	}
	return;
}

void Board::blockList() {

}

void Board::randomBump() {
	ofSeedRandom(ofGetSystemTimeMicros());
	while (bumpSize > 0) {
		int x = (int)ofRandom((size * size) - 1);
		if (board[x].getPiece() == 0 && (!(checkOffBoard(x)))) {
			int y = (int)ofRandom(1, 2);
			board[x].setPiece(y);
			bumpSize--;
		}
	}
}