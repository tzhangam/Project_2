#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <QtWidgets>

#include "Block.h"

class RenderArea : public QWidget {
	Q_OBJECT

public:
	RenderArea(QWidget *parent = 0);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

public slots:
	void setBlockShape(Block::BlockShape shape);
	void setBlockColor(Block::BlockColor color);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Block block;
};

#endif // RENDERAREA_H