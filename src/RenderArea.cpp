#include "RenderArea.h"

RenderArea::RenderArea(const Gameboard *gameboard, QWidget *parent)
	: QWidget(parent)
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);

	this->gameboard = gameboard;

	update();
}

QSize RenderArea::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize RenderArea::sizeHint() const {
	return QSize(200, 400);
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (int col = 0; col < gameboard->getWidth(); ++col)
		for (int row = 0; row < gameboard->getHeight(); ++row) {
			int gridSize = gameboard->getGridSize();

			QRect rect(col*gridSize, row*gridSize, gridSize, gridSize);

			painter.setPen(QPen(Qt::white));
			painter.setBrush(QBrush(gameboard->getGridColor(row, col)));
			painter.drawRect(rect);
		}
}