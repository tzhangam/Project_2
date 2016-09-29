#ifndef PANEL_H
#define PANEL_H

#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#endif // QT_VERSION

#include "Gameboard.h"
/*
	*  Class Panel handles score calculation and the display of score, level, combo. 
*/
class Panel : public QWidget {
	Q_OBJECT

public:
	//Note:It is mandatory to pass Gameboard object to a Panel object.
	Panel(const Gameboard &gameboard, QWidget *parent = 0);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

public slots:
	void updatePanel();

private:
	QLabel scoreLabel, comboLabel, levelLabel;
	const Gameboard &gameboard;
};

#endif // PANEL_H