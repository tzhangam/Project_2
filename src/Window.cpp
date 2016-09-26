#include "Window.h"
#include <cstdio>
#include <cstring>

Window::Window() {
	// gameboard & renderArea
    gameboard = new Gameboard;
	renderArea = new RenderArea(gameboard);

	// labels
	comboLabel = new QLabel(tr("Combo:"));
	scoreLabel = new QLabel(tr("Score:"));
	levelLabel = new QLabel(tr("Level:"));

	// layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(renderArea, 0, 0, 1, 4);
	mainLayout->addWidget(comboLabel, 2, 0);
	mainLayout->addWidget(scoreLabel, 3, 0);
	mainLayout->addWidget(levelLabel, 4, 0);
	setLayout(mainLayout);

	connect(gameboard, SIGNAL(updatePanel()),
		this, SLOT(updatePanel()));
	connect(gameboard, SIGNAL(updateRenderArea()),
		renderArea, SLOT(update()));

	setWindowTitle(tr("Tetris\n"));

	// set keyboard focus policy
	setFocusPolicy(Qt::ClickFocus);
	setFocus();
}

void Window::updatePanel() {
	char str[20];
	int score = gameboard->getScore();
	std::memset(str, 0, sizeof(str));
	std::sprintf(str, "Score: %d", score);
	scoreLabel->setText(str);
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
