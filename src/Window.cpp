#include "Window.h"
#include <cstdio>
#include <cstring>

Window::Window() {
	// renderArea
	renderArea = new RenderArea;
	gameboard = renderArea->get();

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

	connect(gameboard, SIGNAL(sendScore()),
		this, SLOT(updatePanel()));

	// set keyboard focus policy
	setFocusPolicy(Qt::ClickFocus);
	setFocus();

	setWindowTitle(tr("tetris test\n"));
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
		case Qt::Key_Z:     renderArea->moveBlock(Block::BlockMotion::kRotateClockwise);        break;
		case Qt::Key_X:     renderArea->moveBlock(Block::BlockMotion::kRotateCounterClockwise); break;
		case Qt::Key_Left:  renderArea->moveBlock(Block::BlockMotion::kTranslateLeft);          break;
		case Qt::Key_Right: renderArea->moveBlock(Block::BlockMotion::kTranslateRight);         break;
		case Qt::Key_Down:  renderArea->moveBlock(Block::BlockMotion::kTranslateDown);          break;
		case Qt::Key_Up:    renderArea->startGame();                                            break;
		default: ;
	}
}
