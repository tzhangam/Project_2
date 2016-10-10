#include "PreviewArea.h"
#include "Block.h"

PreviewArea::PreviewArea(const Gameboard &gameboard, QWidget *parent)
	: QWidget(parent),
	  gameboard(gameboard)
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);

	update();
}

QSize PreviewArea::minimumSizeHint() const {
	return QSize(60, 80);
}

QSize PreviewArea::sizeHint() const {
	return QSize(100, 100);
}

void PreviewArea::paintEvent(QPaintEvent * /* event */) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (int row = 0; row < Block::BLOCK_RANGE; ++row)
		for (int col = 0; col < Block::BLOCK_RANGE; ++col) {
			int gridSize = gameboard.getGridSize();

			QRect rect(col*gridSize, row*gridSize, gridSize, gridSize);

			QColor color = gameboard.getNextBlockColor(row, col);

			painter.setPen(QPen((color == Qt::transparent) ? 
				Qt::transparent : Qt::black));
			
			painter.setBrush(QBrush(gameboard.getNextBlockColor(row, col)));
			painter.drawRect(rect);
		}
}
