#include "RenderArea.h"

RenderArea::RenderArea(const Gameboard &gameboard, QWidget *parent)
	: QWidget(parent),
	  gameboard(gameboard)
{
	pixmap.load(":/images/background.bmp");
	setBackgroundRole(QPalette::WindowText);
	setAutoFillBackground(true);

	update();
}

QSize RenderArea::minimumSizeHint() const {
	return QSize(200, 400);
}

QSize RenderArea::sizeHint() const {
	return QSize(200, 400);
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawPixmap(0, 0, pixmap);//Using painter to draw out the background image first.

	for (int col = 0; col < gameboard.getWidth(); ++col)
		for (int row = 0; row < gameboard.getHeight(); ++row) {
			int gridSize = gameboard.getGridSize();

			QRect rect(col*gridSize, row*gridSize, gridSize, gridSize);

			Qt::GlobalColor color = gameboard.getGridColor(row, col);
			
			painter.setPen(QPen((color == Qt::transparent) ? 
				Qt::transparent : Qt::black));
			painter.setBrush(QBrush(color));
			painter.drawRect(rect);
		}
}
