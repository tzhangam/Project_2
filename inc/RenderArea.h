#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <qtguiversion>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#else
  #include <QtGui>
#endif // QT_VERSION

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