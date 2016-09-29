#ifndef PREVIEW_AREA_H
#define PREVIEW_AREA_H

#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#endif // QT_VERSION

#include "Gameboard.h"
/*
	Class PreviewArea handles the display of the next coming block.
*/
class PreviewArea : public QWidget {
	Q_OBJECT

public:
	PreviewArea(const Gameboard &gameboard, QWidget *parent = 0);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	const Gameboard &gameboard;
};

#endif // PREVIEW_AREA_H