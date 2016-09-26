#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <QtWidgets>

#include "Block.h"
#include "Gameboard.h"

class RenderArea : public QWidget {
	Q_OBJECT

public:
	RenderArea(QWidget *parent = 0);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

public slots:
	void moveBlock(Block::BlockMotion motion);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Gameboard gameboard;
};

#endif // RENDERAREA_H