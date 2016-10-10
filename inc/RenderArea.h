/*
	Class RenderArea
	* The major output interface
	* Converts structural and color information stored in class Gameboard
	  into central graphical display
*/

#ifndef RENDERAREA_H
#define RENDERAREA_H

// backward compatibility
#include <QPainter>
#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#endif // QT_VERSION

#include "Block.h"
#include "Gameboard.h"

class RenderArea : public QWidget {
	Q_OBJECT

public:
	RenderArea(const Gameboard &gameboard, QWidget *parent = 0);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	const Gameboard &gameboard;
	QPixmap pixmap;
};

#endif // RENDERAREA_H
