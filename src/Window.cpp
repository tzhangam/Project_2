#include "Window.h"

Window::Window() 
	: gameboard(),
	  renderArea(gameboard),
	  panel(gameboard),
	  previewArea(gameboard)
{
	// layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(&renderArea, 0, 0, 4, 1);
	mainLayout->addWidget(&panel, 3, 1);
	mainLayout->addWidget(&previewArea, 1, 1);
	setLayout(mainLayout);

	setFixedSize(400, 500);

	// connect
	connect(&gameboard, SIGNAL(updatePanel()),
		&panel, SLOT(updatePanel()));
	connect(&gameboard, SIGNAL(updateRenderArea()),
		&renderArea, SLOT(update()));
	connect(&gameboard, SIGNAL(gameOver()),
		this, SLOT(gameOver()));
	connect(&gameboard, SIGNAL(updatePreviewArea()),
		&previewArea, SLOT(update()));

	setWindowTitle(tr("Tetris\n"));

	// set keyboard focus policy
	setFocusPolicy(Qt::ClickFocus);
	setFocus();
}

void Window::gameOver() {
	QMessageBox *msgBox = new QMessageBox();

	msgBox->setWindowTitle(tr("Game Over"));
	msgBox->setText(tr("Oops, you're dead.."));

	QPushButton *continueButton = msgBox->addButton(
		tr("&Play again"), QMessageBox::AcceptRole);
	QPushButton *quitButton = msgBox->addButton(
		tr("&Quit"), QMessageBox::AcceptRole);

	connect(continueButton, SIGNAL(clicked()),
		&gameboard, SLOT(resetBoard()));
	connect(quitButton, SIGNAL(clicked()),
		qApp, SLOT(quit()));

	msgBox->show();
}

void Window::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_Z:     gameboard.moveBlock(Block::BlockMotion::kRotateClockwise);        break;
		case Qt::Key_X:     gameboard.moveBlock(Block::BlockMotion::kRotateCounterClockwise); break;
		case Qt::Key_Left:  gameboard.moveBlock(Block::BlockMotion::kTranslateLeft);          break;
		case Qt::Key_Right: gameboard.moveBlock(Block::BlockMotion::kTranslateRight);         break;
		case Qt::Key_Down:  gameboard.moveBlock(Block::BlockMotion::kTranslateDown);          break;
		case Qt::Key_Up:    gameboard.startGame();                                            break;

		// unhandled key press
		default: ;
	}
}
