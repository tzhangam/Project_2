#ifndef WINDOW_H
#define WINDOW_H

#include <qtguiversion>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#else
  #include <QtGui>
#endif // QT_VERSION

#include "RenderArea.h"

class Window : public QWidget {
	Q_OBJECT

public:
	Window();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	static const int IdRole = Qt::UserRole;
	
	RenderArea *renderArea;
};	

#endif // WINDOW_H