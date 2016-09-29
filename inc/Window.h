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
/*
	*	Window constitutes of all other the sub widgets. It detects key press, emit game
	*start and gameover info, and sets up interaction paths among widgets. 
*/
class Window : public QWidget {
	Q_OBJECT

public:
	Window();

public slots:
	//Pops out a window asking whether the user wants to continue.
	void gameOver();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	static const int IdRole = Qt::UserRole;
	
	Gameboard gameboard;
	RenderArea renderArea;
	Panel panel;
	PreviewArea previewArea;
};	

#endif // WINDOW_H
