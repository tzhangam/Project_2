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
		case Qt::Key_Z:     renderArea->moveBlock(Block::BlockMotion::kRotateClockwise);        break;
		case Qt::Key_X:     renderArea->moveBlock(Block::BlockMotion::kRotateCounterClockwise); break;
		case Qt::Key_Left:  renderArea->moveBlock(Block::BlockMotion::kTranslateLeft);          break;
		case Qt::Key_Right: renderArea->moveBlock(Block::BlockMotion::kTranslateRight);         break;
		case Qt::Key_Down:  renderArea->moveBlock(Block::BlockMotion::kTranslateDown);          break;
		case Qt::Key_Up:    renderArea->moveBlock(Block::BlockMotion::kTranslateUp);            break;
		default: ;
	}
}