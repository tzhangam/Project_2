#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Block.h"
#include "misc.h"

class Gameboard : public QObject {
	Q_OBJECT

public:
	static const int defaultWidth    = 10;
	static const int maxWidth        = 30;
	static const int minWidth        =  5;

	static const int defaultHeight   = 20;
	static const int maxHeight       = 30;
	static const int minHeight       = 15;

	static const int defaultGridSize = 25;
	static const int maxGridSize     = 50;
	static const int minGridSize     = 10;

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
	void rotateClockwise();
	void rotateCounterClockwise();
	void translateLeft();
	void translateRight();
	void translateDown();
	void translateUp();

private:
	typedef struct {
		Block::BlockColor color;
		bool isActive;
	} Grid;

	Block *activeBlock;
	Grid grid[maxHeight][maxWidth];

	int width, height, gridSize;

	bool validateMove(const Block &candidate);
	void updateGrid();

	void resize(int width, int height);
};

#endif // GAMEBOARD_H