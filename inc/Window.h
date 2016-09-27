#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#endif // QT_VERSION

#include "RenderArea.h"
#include "Gameboard.h"
#include "Panel.h"
#include "PreviewArea.h"

class Window : public QWidget {
	Q_OBJECT

public:
	Window();
	~Window();

public slots:
	void gameOver();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	static const int IdRole = Qt::UserRole;
	
	RenderArea *renderArea;
	Gameboard *gameboard;
	Panel *panel;
	PreviewArea *previewArea;
};	

#endif // WINDOW_H
