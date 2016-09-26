#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
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