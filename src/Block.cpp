#include "Block.h"

#include <algorithm>

Block::Block(BlockShape shape, BlockDirection direction, BlockColor color) {
	this->shape = shape;
	this->direction = direction;
	this->color = color;

	updateMap();
}

void Block::updateMap() {
	for (int i = 0; i < BLOCK_RANGE; ++i)
		for (int j = 0; j < BLOCK_RANGE; ++j)
			map[i][j] = false;

	// handle different shapes
	switch (shape) {
		case kShapeI:
			map[0][2] = map[1][2] = map[2][2] = map[3][2] = true;
			break;
		case kShapeL:
			map[1][2] = map[2][2] = map[3][2] = map[3][3] = true;
			break;
		case kShapeL_Mir:
			map[1][2] = map[2][2] = map[3][2] = map[3][1] = true;
			break;
		case kShapeT:
			map[1][2] = map[2][2] = map[2][1] = map[2][3] = true;
			break;
		case kShapeZ:
			map[1][1] = map[1][2] = map[2][2] = map[2][3] = true;
			break;
		case kShapeZ_Mir:
			map[1][3] = map[1][2] = map[2][2] = map[2][1] = true;
			break;
		case kShapeO:
			map[2][1] = map[2][2] = map[3][1] = map[3][2] = true;
			break;
	}

	// handle different direction
	switch (direction) {
		case kUp:
			// do nothing
			break;
		case kRight:

			break;
		case kDown:

			break;
		case kLeft:

			break;
	}
}

void Block::setShape(BlockShape shape) {
	this->shape = shape;
	updateMap();
}

void Block::setDirection(BlockDirection direction) {
	this->direction = direction;
	updateMap();
}

void Block::setColor(BlockColor color) {
	this->color = color;
	updateMap();
}

bool Block::getMap(int x, int y) const {
	x = std::max(0, x);
	y = std::max(0, y);
	x = std::min(x, BLOCK_RANGE-1);
	y = std::min(y, BLOCK_RANGE-1);
	return map[x][y];
}