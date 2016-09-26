#ifndef BLOCK_H
#define BLOCK_H

#include <QColor>
#include <QObject>

#define DEBUG 1
#define LOG(msg) do { if (DEBUG) { QMessageBox *_msg = new QMessageBox; \
						_msg->setText(QObject::tr(msg)); _msg->show(); } } while(0)
#if (DEBUG)
#include <QtWidgets>
#endif // DEBUG

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

	enum BlockColor {
		kRed,
		kYellow,
		kGreen,
		kBlue,
		kCyan,
		kPink,
		kBlack,

		kColorCount,

		kNoBlock
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
		BlockDirection direction = kUp, BlockColor color = kRed);
	Block(const Block &rhs);

	BlockShape getShape() const { return shape; }
	BlockDirection getDirection() const { return direction; }
	Qt::GlobalColor getColor() const { return convert(color); }
	int getX() const { return centerX; }
	int getY() const { return centerY; }

	void setShape(BlockShape shape);
	void setDirection(BlockDirection direction);
	void setColor(BlockColor color);
	void setColor(Qt::GlobalColor color);

	void move(BlockMotion motion);

	/*
	   coordinate system for map:
		O--->col
		|
		|
	   row
	*/
	bool getMap(int row, int col) const;

	static Qt::GlobalColor convert(BlockColor color) {
		switch (color) {
			case kRed:         return Qt::red;
			case kYellow:      return Qt::yellow;
			case kGreen:       return Qt::green;
			case kBlue:        return Qt::blue;
			case kCyan:        return Qt::cyan;
			case kPink:        return Qt::magenta;
			case kBlack:       return Qt::black;
			case kNoBlock:     return Qt::transparent;
			default:           return Qt::red;
		}
	}

	static BlockColor convert(Qt::GlobalColor color) {
		switch (color) {
			case Qt::red:         return kRed;
			case Qt::yellow:      return kYellow;
			case Qt::green:       return kGreen;
			case Qt::blue:        return kBlue;
			case Qt::cyan:        return kCyan;
			case Qt::magenta:     return kPink;
			case Qt::black:       return kBlack;
			case Qt::transparent: return kNoBlock;
			default:              return kRed;
		}
	}

private:
	BlockShape shape;
	BlockDirection direction;
	BlockColor color;

	BlockMap map;

	int centerX, centerY;

	void updateMap();
};

#endif // BLOCK_H