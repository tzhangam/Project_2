#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Block.h"
#include "misc.h"

#include <QTimer>

class Gameboard : public QObject {
	Q_OBJECT

public:
	Gameboard(int height = defaultHeight,
		int width = defaultWidth, int gridSize = defaultGridSize);
	~Gameboard();

	// for RenderArea class
	Qt::GlobalColor getGridColor(int row, int col) const {
		row = tetris::clamp(0, row, height-1);
		col = tetris::clamp(0, col, width-1);
		return Block::convert(grid[row][col].color);
	}
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getGridSize() const { return gridSize; }

	// for Panel class
	int getCombo() const { return combo; }
	int getScore() const { return score; }
	int getLevel() const { return level; }

	// for PreviewArea class
	Qt::GlobalColor getNextBlockColor(int row, int col) const {
		return (nextBlock->getMap(row, col)) ?
			nextBlock->getColor() : Block::convert(Block::BlockColor::kNoBlock); 
	}

public slots:
	// move current block and handle row elimination
	void moveBlock(Block::BlockMotion motion);
	void startGame();
	void endGame();
	void resetBoard();

private slots:
	void blockDescend();

signals:
	void updateRenderArea();
	void updatePanel();
	void updatePreviewArea();
	void gameOver();

private:
	typedef struct {
		Block::BlockColor color;
		bool isActive;
	} Grid;

	static const int defaultWidth;
	static const int maxWidth     = 30;
	static const int minWidth;

	static const int defaultHeight;
	static const int maxHeight    = 30;
	static const int minHeight;

	static const int defaultGridSize;
	static const int maxGridSize;
	static const int minGridSize;

	Block *activeBlock, *nextBlock;
	Grid grid[maxHeight][maxWidth];

	int width, height, gridSize;

	QTimer *timer;
	volatile bool isGameStart;

	int combo, score, level;

	bool validate(const Block &candidate, bool isNew) const;
	void updateGrid();

	// new block generation
	Block *generateNewBlock();
	bool updateActiveBlock();

	Block::BlockShape getRandomShape() const;
	Block::BlockDirection getRandomDirection() const;
	Block::BlockColor getRandomColor() const;

	// row elimination
	static const int kNoFullRow;
	int getFullRow() const;
	void eliminateRow(int row);

	void resize(int width, int height);

	// start timer and generating new block
	void start();
	void reset();
};

#endif // GAMEBOARD_H