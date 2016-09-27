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

const int Gameboard::defaultGridSize = 20;
const int Gameboard::maxGridSize     = 50;
const int Gameboard::minGridSize     = 10;

Gameboard::Gameboard(int height, int width, int gridSize) 
	: activeBlock(nullptr),
	  isGameStart(false),
	  combo(0),
	  score(0),
	  level(1)
{	
	// seed for random generator
	std::srand(std::time(0));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(blockDescend()));

	reset();

	this->width = tetris::clamp(minWidth, width, maxWidth);
	this->height = tetris::clamp(minHeight, height, maxHeight);
	this->gridSize = tetris::clamp(minGridSize, gridSize, maxGridSize);
}

void Gameboard::moveBlock(Block::BlockMotion motion) {
	if (activeBlock == nullptr) return;

	Block newBlock(*activeBlock);
	newBlock.move(motion);

	if (validateMove(newBlock)) {
		activeBlock->move(motion);
		updateGrid();
	}
	else if (motion == Block::BlockMotion::kTranslateDown) {
		// block change to inactive
		suppressActiveBlock();

		// row elimination
		int row;
		combo = 0;
		while ((row = getFullRow()) != kNoFullRow) {
			++combo;
			eliminateRow(row);
		}
		score += 10 * combo * combo;

		// level up
		if (score > level * 100 && level < 10) {
			++level;
			timer->stop();
			timer->start(1000-100*(level-1));
		}
		emit updatePanel();

		if (!generateNewBlock()) {
			//reset();
			isGameStart=false;
		}
	}
}

void Gameboard::startGame() {
	if (!isGameStart)
		start();
}

void Gameboard::blockDescend() {
	moveBlock(Block::BlockMotion::kTranslateDown);
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
	if (activeBlock != nullptr) {
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

	emit updateRenderArea();
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
	updateGrid();
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

void Gameboard::start() {
	reset();

	activeBlock = new Block(getRandomShape(), 2, width/2,
							getRandomDirection(), getRandomColor());
	updateGrid();

	combo = score = 0;
	level = 1;
	emit updatePanel();

	timer->start(1000);

	isGameStart = true;
}

void Gameboard::reset() {
	// clear grid
	for (int i = 0; i < maxHeight; ++i)
		for (int j = 0; j < maxWidth; ++j) {
			grid[i][j].color = Block::BlockColor::kNoBlock;
			grid[i][j].isActive = false;
		}

	if (activeBlock != nullptr) {
		delete activeBlock;
		activeBlock = nullptr;
	}

	timer->stop();

	this->width = defaultWidth;
	this->height = defaultHeight;
	this->gridSize = defaultGridSize;

	isGameStart = false;
}