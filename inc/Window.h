#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#endif // QT_VERSION

#include "RenderArea.h"

class Window : public QWidget {
	Q_OBJECT

public:
	Window();

public slots:
	void updatePanel();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	static const int IdRole = Qt::UserRole;
	
	RenderArea *renderArea;
	Gameboard *gameboard;
	QLabel *scoreLabel, *comboLabel, *levelLabel;
};	

#endif // WINDOW_H
