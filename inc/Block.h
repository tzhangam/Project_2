/*
	Class Block
	* Stores the shape, color, position and orientation for each block
	* Provides functions for block motion
*/

#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>
#include <QObject>

class Block : public QObject {
	Q_OBJECT

public:
	enum BlockShape {
		kShapeI,
		kShapeL,
		kShapeL_Mir,
		kShapeT,
		kShapeZ,
		kShapeZ_Mir,
		kShapeO,

		kShapeCount
	};

	enum BlockDirection {
		kUp,
		kRight,
		kDown,
		kLeft,

		kDirectionCount
	};

	enum BlockMotion {
		kRotateClockwise,
		kRotateCounterClockwise,
		kTranslateLeft,
		kTranslateRight,
		kTranslateDown,
		kTranslateUp
	};

	static const int BLOCK_RANGE = 5;
	static const int BLOCK_HALF_RANGE = (BLOCK_RANGE+1)/2;
	typedef bool BlockMap[BLOCK_RANGE][BLOCK_RANGE];

	/*
	   coordinate system for center:
		O--->y
		|
		|
		x
	*/
	Block(BlockShape shape, int x, int y,
		BlockDirection direction = kUp);
	Block(const Block &rhs);

	BlockShape getShape() const { return shape; }
	BlockDirection getDirection() const { return direction; }
	QColor getColor() const { return color; }
	int getX() const { return centerX; }
	int getY() const { return centerY; }

	void setShape(BlockShape shape);
	void setDirection(BlockDirection direction);

	// translation and rotation
	void move(BlockMotion motion);

	/*
	   coordinate system for map:
		O--->col
		|
		|
	   row
	*/
	bool getMap(int row, int col) const;

private:
	BlockShape shape;
	BlockDirection direction;
	QColor color;

	BlockMap map;

	int centerX, centerY;

	// update the internal representation of the block
	void updateMap();
};

#endif // BLOCK_H