#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPainter>
#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#endif // QT_VERSION

#include "Block.h"
#include "Gameboard.h"
/*
	*   Class RenderArea serves as major output interface.It converts 
	*structural and color information stored in the gridmaps of Class 
	*Gameboard into central graphical display.
*/
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
