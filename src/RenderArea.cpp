#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent)
	: QWidget(parent),
	  block(Block::BlockShape::kShapeI, Block::BlockDirection::kUp, Block::BlockColor::kRed)
{
	setBackgroundRole(QPalette::Base);
	setAutoFillBackground(true);
}

QSize RenderArea::minimumSizeHint() const {
	return QSize(100, 100);
}

QSize RenderArea::sizeHint() const {
	return QSize(400, 400);
}

void RenderArea::setBlockShape(Block::BlockShape shape) {
	this->block.setShape(shape);
	update();
}

void RenderArea::setBlockColor(Block::BlockColor color) {
	this->block.setColor(color);
	update();
}

void RenderArea::setBlockDirection(Block::BlockDirection direction) {
	this->block.setDirection(direction);
	update();
}

void RenderArea::rotateBlockClockwise() {
	this->block.rotateClockwise();
	update();
}

void RenderArea::rotateBlockCounterClockwise() {
	this->block.rotateCounterClockwise();
	update();
}

void RenderArea::paintEvent(QPaintEvent * /* event */) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (int i = 0; i < Block::BLOCK_RANGE; ++i)
		for (int j = 0; j < Block::BLOCK_RANGE; ++j) {
			QRect rect(j*25+50, i*25+50, 25, 25);

			if (block.getMap(i, j)) {
				painter.setPen(QPen(Qt::black));
				painter.setBrush(QBrush(block.getColor()));
			}
			else {
				painter.setPen(QPen(Qt::white));
				painter.setBrush(QBrush(Qt::white));
			}
			painter.drawRect(rect);
		}
}