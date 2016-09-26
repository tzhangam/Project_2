#include "Window.h"

Window::Window() {
    gameboard = new Gameboard;
	renderArea = new RenderArea(gameboard);
	panel = new Panel(gameboard);

	// layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(renderArea, 0, 0, 4, 4);
	mainLayout->addWidget(panel, 3, 4, 1, 2);
	setLayout(mainLayout);

	connect(gameboard, SIGNAL(updatePanel()),
		panel, SLOT(updatePanel()));
	connect(gameboard, SIGNAL(updateRenderArea()),
		renderArea, SLOT(update()));

	setWindowTitle(tr("Tetris\n"));

	// set keyboard focus policy
	setFocusPolicy(Qt::ClickFocus);
	setFocus();
}

void Window::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Z:     gameboard->moveBlock(Block::BlockMotion::kRotateClockwise);        break;
		case Qt::Key_X:     gameboard->moveBlock(Block::BlockMotion::kRotateCounterClockwise); break;
		case Qt::Key_Left:  gameboard->moveBlock(Block::BlockMotion::kTranslateLeft);          break;
		case Qt::Key_Right: gameboard->moveBlock(Block::BlockMotion::kTranslateRight);         break;
		case Qt::Key_Down:  gameboard->moveBlock(Block::BlockMotion::kTranslateDown);          break;
		case Qt::Key_Up:    gameboard->startGame();                                            break;
		default: ;
	}
}
