#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Block.h"
#include "misc.h"

class Gameboard : public QObject {
	Q_OBJECT

public:
	Gameboard(int height = defaultHeight, int width = defaultWidth);

	Qt::GlobalColor getGridColor(int row, int col) const {
		row = tetris::clamp(0, row, height-1);
		col = tetris::clamp(0, col, width-1);
		return Block::convert(grid[row][col].color);
	}
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getGridSize() const { return gridSize; }

public slots:
	void moveBlock(Block::BlockMotion motion);

private:
	typedef struct {
		Block::BlockColor color;
		bool isActive;
	} Grid;

	enum BlockStatus {
		kActive,
		kDead
	};

	static const int defaultWidth;
	static const int maxWidth     = 30;
	static const int minWidth;

	static const int defaultHeight;
	static const int maxHeight    = 30;
	static const int minHeight;

	static const int defaultGridSize;
	static const int maxGridSize;
	static const int minGridSize;

	Block *activeBlock;
	Grid grid[maxHeight][maxWidth];

	int width, height, gridSize;

	bool validateMove(const Block &candidate) const;
	void updateGrid();

	// new block generation
	BlockStatus checkBlockStatus() const;
	bool generateNewBlock();
	void suppressActiveBlock();

	Block::BlockShape getRandomShape() const;
	Block::BlockDirection getRandomDirection() const;
	Block::BlockColor getRandomColor() const;

	// row elimination
	static const int kNoFullRow;
	int getFullRow() const;
	void eliminateRow(int row);

	void resize(int width, int height);
};

#endif // GAMEBOARD_H