#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent)
	: QWidget(parent),
	  gameboard()
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
	update();
}

QSize RenderArea::minimumSizeHint() const {
	return QSize(200, 200);
}

QSize RenderArea::sizeHint() const {
	return QSize(400, 400);
}

void RenderArea::rotateBlockClockwise() {
	this->gameboard.rotateClockwise();
	update();
}

void RenderArea::rotateBlockCounterClockwise() {
	this->gameboard.rotateCounterClockwise();
	update();
}

void RenderArea::translateBlockLeft() {
	this->gameboard.translateLeft();
	update();
}

void RenderArea::translateBlockRight() {
	this->gameboard.translateRight();
	update();
}

void RenderArea::translateBlockDown() {
	this->gameboard.translateDown();
	update();
}

void RenderArea::translateBlockUp() {
	this->gameboard.translateUp();
	update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (int col = 0; col < gameboard.getWidth(); ++col)
		for (int row = 0; row < gameboard.getHeight(); ++row) {
			int gridSize = gameboard.getGridSize();

			QRect rect(col*gridSize, row*gridSize, gridSize, gridSize);

			painter.setPen(QPen(Qt::white));
			painter.setBrush(QBrush(gameboard.getGridColor(row, col)));
			painter.drawRect(rect);
		}
}