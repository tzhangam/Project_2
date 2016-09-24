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
		kShapeO
	};

	enum BlockDirection {
		kUp,
		kRight,
		kDown,
		kLeft
	};

	enum BlockColor {
		kRed	= Qt::red,
		kYellow	= Qt::yellow,
		kGreen	= Qt::green,
		kBlue	= Qt::blue,
		kCyan	= Qt::cyan,
		kPink	= Qt::magenta,
		kBlack	= Qt::black
	};

	static const int BLOCK_RANGE = 5;
	static const int BLOCK_HALF_RANGE = (BLOCK_RANGE-1)/2;
	typedef bool BlockMap[BLOCK_RANGE][BLOCK_RANGE];

	explicit Block(BlockShape shape,
		BlockDirection direction = kUp, BlockColor color = kRed);

	BlockShape getShape() const { return shape; };
	BlockDirection getDirection() const { return direction; };
	BlockColor getColor() const { return color; };

	void setShape(BlockShape shape);
	void setDirection(BlockDirection direction);
	void setColor(BlockColor color);

	bool getMap(int x, int y) const;

private:
	BlockShape shape;
	BlockDirection direction;
	BlockColor color;

	BlockMap map;

	void updateMap();
};

#endif // BLOCK_H