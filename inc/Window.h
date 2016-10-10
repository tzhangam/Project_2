/*
	Class Window
	* Contains all other widgets, including render areas for the main game field
	  and block preview, as well as the score panel
	* Connects the slots of each widget with the appropriate signal from the Gameboard
	* Detects key press and activates the corresponding slot of the Gameboard
	* Shows game over information
*/

#ifndef WINDOW_H
#define WINDOW_H

// backward compatibility
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

public slots:
	// Pops out a window asking whether the user wants to continue.
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
