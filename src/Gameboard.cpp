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
	this->width = tetris::clamp(minWidth, width, maxWidth);
	this->height = tetris::clamp(minHeight, height, maxHeight);
	this->gridSize = tetris::clamp(minGridSize, gridSize, maxGridSize);

	// seed for random number generator
	std::srand(std::time(0));
	nextBlock = generateNewBlock();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(blockDescend()));

	reset();
}

Gameboard::~Gameboard() {
	delete timer;
	delete activeBlock;
	delete nextBlock;
}

void Gameboard::moveBlock(Block::BlockMotion motion) {
	if (activeBlock == nullptr) return;

	Block newBlock(*activeBlock);
	newBlock.move(motion);

	if (validate(newBlock, false)) {
		activeBlock->move(motion);
		updateGrid();
	}
	else if (motion == Block::BlockMotion::kTranslateDown) {
		bool updateSucceed = updateActiveBlock();

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

		if (!updateSucceed) {
			endGame();
			emit gameOver();
		}
		else {
			emit updatePreviewArea();
		}
	}
}

void Gameboard::startGame() {
	if (!isGameStart)
		start();
}

void Gameboard::endGame() {
	isGameStart = false;
}

void Gameboard::resetBoard() {
	reset();
}

void Gameboard::blockDescend() {
	moveBlock(Block::BlockMotion::kTranslateDown);
}

bool Gameboard::validate(const Block &candidate, bool isNew) const {
	int range = Block::BLOCK_HALF_RANGE;
	// is current active block ?
	if (!isNew) {
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
						&& grid[row][col].color != Qt::transparent)
						return false;
				}
	}
	// new block
	else {
		for (int row = 0; row < 2; ++row) {
			for (int col = 0; col < width; ++col) {
				if (grid[row][col].color != Qt::transparent)
					return false;
			}
		}
	}

	return true;
}

void Gameboard::updateGrid() {
	// clear previous active block
	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			if (grid[i][j].isActive) {
				grid[i][j].isActive = false;
				grid[i][j].color = Qt::transparent;
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
					grid[row][col].color = activeBlock->getColor();
				}
	}

	emit updateRenderArea();
}

Block *Gameboard::generateNewBlock() {
	return new Block(getRandomShape(), 2, width/2);
}

bool Gameboard::updateActiveBlock() {
	for (int row = 0; row < height; ++row)
		for (int col = 0; col < width; ++col)
			grid[row][col].isActive = false;
	delete activeBlock;

	if (validate(*nextBlock, true)) {
		activeBlock = nextBlock;
		nextBlock = generateNewBlock();
		updateGrid();
		return true;
	}
	else {
		activeBlock = nullptr;
		return false;
	}
}

Block::BlockShape Gameboard::getRandomShape() const {
	return Block::BlockShape(std::rand() % Block::BlockShape::kShapeCount);
}

Block::BlockDirection Gameboard::getRandomDirection() const {
	return Block::BlockDirection(std::rand() % Block::BlockDirection::kDirectionCount);
}

const int Gameboard::kNoFullRow = -1;

int Gameboard::getFullRow() const {
	// find full row starting from bottom
	for (int row = height-1; row >= 0; --row) {
		bool isFull = true;
		for (int col = 0; col < width; ++col)
			if (grid[row][col].isActive ||
				grid[row][col].color == Qt::transparent) {
				isFull = false;
				break;
			}
		if (isFull) return row;
	}
	return kNoFullRow;
}

void Gameboard::eliminateRow(int row) {
	// shift inactive grids downwards
	for (int i = row; i >= 0; --i)
		for (int col = 0; col < width; ++col) {
			// only update inactive grids
			if (grid[i][col].isActive) continue;
			if (i == 0 || grid[i-1][col].isActive) {
				grid[i][col].isActive = false;
				grid[i][col].color = Qt::transparent;
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
	updateActiveBlock();
	emit updatePreviewArea();

	combo = score = 0;
	level = 1;
	emit updatePanel();

	timer->start(1000);

	isGameStart = true;
}

void Gameboard::reset() {
	// clear grids
	for (int i = 0; i < maxHeight; ++i)
		for (int j = 0; j < maxWidth; ++j) {
			grid[i][j].color = Qt::transparent;
			grid[i][j].isActive = false;
		}
	updateGrid();

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