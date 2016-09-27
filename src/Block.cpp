#include "Block.h"
#include "misc.h"

#include <algorithm>

Block::Block(BlockShape shape, int x, int y,
	BlockDirection direction, BlockColor color)
	: shape(shape),
	  direction(direction),
	  color(color),
	  centerX(x),
	  centerY(y)
{
	updateMap();
}

Block::Block(const Block &rhs)
	: shape(rhs.getShape()),
	  direction(rhs.getDirection()),
	  centerX(rhs.getX()),
	  centerY(rhs.getY())
{
	setColor(rhs.getColor());
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
		default:
			;
	}

	// handle different direction
	switch (direction) {
		case kUp:
			// do nothing
			break;
		case kRight:
			for (int i = 0; i < BLOCK_HALF_RANGE-1; ++i)
				for (int j = 0; j < BLOCK_HALF_RANGE; ++j) {
					bool tmp = map[i][j];
					map[i][j] = map[BLOCK_RANGE-1-j][i];
					map[BLOCK_RANGE-1-j][i] = map[BLOCK_RANGE-1-i][BLOCK_RANGE-1-j];
					map[BLOCK_RANGE-1-i][BLOCK_RANGE-1-j] = map[j][BLOCK_RANGE-1-i];
					map[j][BLOCK_RANGE-1-i] = tmp;
				}
			break;
		case kDown:
			for (int i = 0; i < BLOCK_HALF_RANGE; ++i)
				for (int j = 0; j < BLOCK_RANGE; ++j) {
					if (i != BLOCK_HALF_RANGE-1 || j < BLOCK_HALF_RANGE) {
						bool tmp = map[i][j];
						map[i][j] = map[BLOCK_RANGE-1-i][BLOCK_RANGE-1-j];
						map[BLOCK_RANGE-1-i][BLOCK_RANGE-1-j] = tmp;
					}
				}
			break;
		case kLeft:
			for (int i = 0; i < BLOCK_HALF_RANGE-1; ++i)
				for (int j = 0; j < BLOCK_HALF_RANGE; ++j) {
					bool tmp = map[i][j];
					map[i][j] = map[j][BLOCK_RANGE-1-i];
					map[j][BLOCK_RANGE-1-i] = map[BLOCK_RANGE-1-i][BLOCK_RANGE-1-j];
					map[BLOCK_RANGE-1-i][BLOCK_RANGE-1-j] = map[BLOCK_RANGE-1-j][i];
					map[BLOCK_RANGE-1-j][i] = tmp;
				}
			break;
		default:
			;
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

void Block::setColor(Qt::GlobalColor color) {
	setColor(convert(color));
}

void Block::move(BlockMotion motion) {
	switch (motion) {
		case kRotateClockwise:
			switch (direction) {
				case kUp:    setDirection(kRight); break;
				case kRight: setDirection(kDown);  break;
				case kDown:  setDirection(kLeft);  break;
				case kLeft:  setDirection(kUp);    break;
				default: ;
			}
			break;
		case kRotateCounterClockwise:
			switch (direction) {
				case kUp:    setDirection(kLeft);  break;
				case kRight: setDirection(kUp);    break;
				case kDown:  setDirection(kRight); break;
				case kLeft:  setDirection(kDown);  break;
				default: ;
			}
			break;
		case kTranslateLeft:
			--centerY;
			break;
		case kTranslateRight:
			++centerY;
			break;
		case kTranslateDown:
			++centerX;
			break;
		case kTranslateUp:
			--centerX;
			break;
		default:
			;
	}
}

bool Block::getMap(int row, int col) const {
	row = tetris::clamp(0, row, BLOCK_RANGE-1);
	col = tetris::clamp(0, col, BLOCK_RANGE-1);
	return map[row][col];
}