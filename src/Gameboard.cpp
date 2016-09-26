#include "Gameboard.h"

#include <cstdlib>
#include <ctime>

const int Gameboard::maxWidth;
const int Gameboard::minWidth;
const int Gameboard::maxHeight;
const int Gameboard::minHeight;
const int Gameboard::maxGridSize;
const int Gameboard::minGridSize;

Gameboard::Gameboard(int height, int width)
	: activeBlock(nullptr),
	  gridSize(20)
{	
	activeBlock = new Block(Block::BlockShape::kShapeZ, 10, 5);
	this->width = tetris::clamp(minWidth, width, maxWidth);
	this->height = tetris::clamp(minHeight, height, maxHeight);

	for (int i = 0; i < maxHeight; ++i)
		for (int j = 0; j < maxWidth; ++j) {
			grid[i][j].color = Block::BlockColor::kNoBlock;
			grid[i][j].isActive = false;
		}
	if (validateMove(*activeBlock))
		updateGrid();

	// seed for random generator
	std::srand(std::time(0));
}

void Gameboard::rotateClockwise() {
	if (activeBlock == nullptr) return;

	Block newBlock = Block(*activeBlock);
	newBlock.rotateClockwise();

	if (validateMove(newBlock)) {
		activeBlock->rotateClockwise();
		updateGrid();
	}
}

void Gameboard::rotateCounterClockwise() {
	if (activeBlock == nullptr) return;

	Block newBlock = Block(*activeBlock);
	newBlock.rotateCounterClockwise();

	if (validateMove(newBlock)) {
		activeBlock->rotateCounterClockwise();
		updateGrid();
	}
}

void Gameboard::translateLeft() {
	if (activeBlock == nullptr) return;

	Block newBlock = Block(*activeBlock);
	newBlock.translateLeft();

	if (validateMove(newBlock)) {
		activeBlock->translateLeft();
		updateGrid();
	}
}

void Gameboard::translateRight() {
	if (activeBlock == nullptr) return;

	Block newBlock = Block(*activeBlock);
	newBlock.translateRight();

	if (validateMove(newBlock)) {
		activeBlock->translateRight();
		updateGrid();
	}
}

void Gameboard::translateDown() {
	if (activeBlock == nullptr) return;

	Block newBlock = Block(*activeBlock);
	newBlock.translateDown();

	if (validateMove(newBlock)) {
		activeBlock->translateDown();
		updateGrid();
	}
	else {
		if (checkBlockStatus() == kDead) {
			generateNewBlock();
		}
	}
}

void Gameboard::translateUp() {
	if (activeBlock == nullptr) return;

	Block newBlock = Block(*activeBlock);
	newBlock.translateUp();

	if (validateMove(newBlock)) {
		activeBlock->translateUp();
		updateGrid();
	}
}

bool Gameboard::validateMove(const Block &candidate) const {
	int range = Block::BLOCK_HALF_RANGE;
	for (int i = -range+1; i < range; ++i)
		for (int j = -range+1; j < range; ++j)
			if (candidate.getMap(i+range-1, j+range-1)) {
				int row = candidate.getX() + i;
				int col = candidate.getY() + j;

				// out of gameboard
				if (!tetris::inRange(0, row, height-1)
					|| !tetris::inRange(0, col, width-1))
					return false;

				// conflict with inactive grid
				if (!grid[row][col].isActive
					&& grid[row][col].color != Block::BlockColor::kNoBlock)
					return false;
			}

	return true;
}

void Gameboard::updateGrid() {
	// clear previous active block
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			if (grid[i][j].isActive) {
				grid[i][j].isActive = false;
				grid[i][j].color = Block::BlockColor::kNoBlock;
			}

	// check if there is active block
	if (activeBlock == nullptr) return;

	// fill in new active block
	int range = Block::BLOCK_HALF_RANGE;
	for (int i = -range+1; i < range; ++i)
		for (int j = -range+1; j < range; ++j) 
			if (activeBlock->getMap(i+range-1, j+range-1)) {
				int row = activeBlock->getX() + i;
				int col = activeBlock->getY() + j;

				grid[row][col].isActive = true;
				grid[row][col].color = Block::convert(activeBlock->getColor());
			}
}

Gameboard::BlockStatus Gameboard::checkBlockStatus() const {
	if (activeBlock == nullptr) return kDead;

	int range = Block::BLOCK_HALF_RANGE;
	for (int i = -range+1; i < range; ++i)
		for (int j = -range+1; j < range; ++j) 
			if (activeBlock->getMap(i+range-1, j+range-1)) {
				int row = activeBlock->getX() + i;
				int col = activeBlock->getY() + j;

				// touch bottom or inactive grid
				if (row+1 >= height ||
					(!grid[row+1][col].isActive &&
						grid[row+1][col].color != Block::BlockColor::kNoBlock))
					return kDead;
			}
	return kActive;
}

bool Gameboard::generateNewBlock() {
	suppressActiveBlock();

	Block *newBlock = new Block(getRandomShape(), 2, 4,
							getRandomDirection(), getRandomColor());
	if (validateMove(*newBlock)) {
		activeBlock = newBlock;
		updateGrid();
		return true;
	}
	else {
		delete newBlock;
		return false;
	}
}

void Gameboard::suppressActiveBlock() {
	if (activeBlock == nullptr) return;

	int range = Block::BLOCK_HALF_RANGE;
	for (int i = -range+1; i < range; ++i)
		for (int j = -range+1; j < range; ++j) 
			if (activeBlock->getMap(i+range-1, j+range-1)) {
				int row = activeBlock->getX() + i;
				int col = activeBlock->getY() + j;

				grid[row][col].isActive = false;
			}
	delete activeBlock;
	activeBlock = nullptr;
}

Block::BlockShape Gameboard::getRandomShape() const {
	return Block::BlockShape(std::rand() % Block::BlockShape::kShapeCount);
}

Block::BlockDirection Gameboard::getRandomDirection() const {
	return Block::BlockDirection(std::rand() % Block::BlockDirection::kDirectionCount);
}

Block::BlockColor Gameboard::getRandomColor() const {
	return Block::BlockColor(std::rand() % Block::BlockColor::kColorCount);
}

void Gameboard::resize(int width, int height) {
	width = tetris::clamp(minWidth, width, maxWidth);
	height = tetris::clamp(minHeight, height, maxHeight);
}