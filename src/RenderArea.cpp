#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent)
	: QWidget(parent),
	  block(Block::BlockShape::kShapeI)
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

void RenderArea::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	for (int i = 0; i < Block::BLOCK_RANGE; ++i)
		for (int j = 0; j < Block::BLOCK_RANGE; ++j) {
			QRect rect(i*50+100, j*50+100, 50, 50);

			if (block.getMap(i, j))
				painter.setPen(QPen(block.getColor()));
			else
				painter.setPen(QPen(Qt::white));

			painter.drawRect(rect);
		}
}