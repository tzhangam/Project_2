#include "Gameboard.h"

#include <cstdlib>
#include <ctime>

// maxWidth & maxHeight are defined in header for successful compilation
const int Gameboard::defaultWidth    = 10;
const int Gameboard::maxWidth            ;
const int Gameboard::minWidth        =  5;

const int Gameboard::defaultHeight   = 20;
const int Gameboard::maxHeight           ;
const int Gameboard::minHeight       = 15;

const int Gameboard::defaultGridSize = 25;
const int Gameboard::maxGridSize     = 50;
const int Gameboard::minGridSize     = 10;

Gameboard::Gameboard(int height, int width)
	: activeBlock(nullptr),
	  gridSize(20)
{	
	this->width = tetris::clamp(minWidth, width, maxWidth);
	this->height = tetris::clamp(minHeight, height, maxHeight);

	activeBlock = new Block(getRandomShape(), 2, width/2,
							getRandomDirection(), getRandomColor());
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

void Gameboard::moveBlock(Block::BlockMotion motion) {
	if (activeBlock == nullptr) return;

	Block newBlock(*activeBlock);
	newBlock.move(motion);

	if (validateMove(newBlock)) {
		activeBlock->move(motion);
		updateGrid();
	}
	else if (motion == Block::BlockMotion::kTranslateDown
		&& checkBlockStatus() == kDead) {
		// block change to inactive
		suppressActiveBlock();

		// row elimination
		int row;
		while ((row = getFullRow()) != kNoFullRow)
			eliminateRow(row);

		generateNewBlock();
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
	if (activeBlock != nullptr)
		suppressActiveBlock();

	Block *newBlock = new Block(getRandomShape(), 2, width/2,
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

const int Gameboard::kNoFullRow = -1;

int Gameboard::getFullRow() const {
	// find full row from bottom
	for (int row = height-1; row >= 0; --row) {
		bool isFull = true;
		for (int col = 0; col < width; ++col)
			if (grid[row][col].isActive ||
				grid[row][col].color == Block::BlockColor::kNoBlock) {
				isFull = false;
				break;
			}
		if (isFull) return row;
	}
	return kNoFullRow;
}

void Gameboard::eliminateRow(int row) {
	// shift inactive grids down
	for (int i = row; i >= 0; --i)
		for (int col = 0; col < width; ++col) {
			// only update inactive grids
			if (grid[i][col].isActive) continue;
			if (i == 0 || grid[i-1][col].isActive) {
				grid[i][col].isActive = false;
				grid[i][col].color = Block::BlockColor::kNoBlock;
			}
			else {
				grid[i][col] = grid[i-1][col];
			}
		}
	updateGrid();
}

void Gameboard::resize(int width, int height) {
	width = tetris::clamp(minWidth, width, maxWidth);
	height = tetris::clamp(minHeight, height, maxHeight);
}