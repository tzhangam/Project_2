#include <QtWidgets>

#include "window.h"

Window::Window() {
	// renderArea
	renderArea = new RenderArea;

	// layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(renderArea, 0, 0, 1, 4);
	setLayout(mainLayout);

	// set keyboard focus policy
	setFocusPolicy(Qt::ClickFocus);
	setFocus();

	setWindowTitle(tr("tetris test\n"));
}

void Window::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Z:     renderArea->rotateBlockClockwise();        break;
		case Qt::Key_X:     renderArea->rotateBlockCounterClockwise(); break;
		case Qt::Key_Left:  renderArea->translateBlockLeft();          break;
		case Qt::Key_Right: renderArea->translateBlockRight();         break;
		case Qt::Key_Down:  renderArea->translateBlockDown();          break;
		case Qt::Key_Up:    renderArea->translateBlockUp();            break;
		default: ;
	}
}