#include "Panel.h"

#include <cstdio>
#include <cstring>

Panel::Panel(const Gameboard &gameboard, QWidget *parent)
	: QWidget(parent),
	  scoreLabel(),
	  comboLabel(),
	  levelLabel(),
	  gameboard(gameboard)
{
	// labels & layout
	QGridLayout *layout = new QGridLayout;

	QLabel *tmpLabel = new QLabel(tr("Score"));
	layout->addWidget(tmpLabel, 0, 0, Qt::AlignRight);
	layout->addWidget(&scoreLabel, 0, 1);

	tmpLabel = new QLabel(tr("Combo"));
	layout->addWidget(tmpLabel, 1, 0, Qt::AlignRight);
	layout->addWidget(&comboLabel, 1, 1);

	tmpLabel = new QLabel(tr("Level"));
	layout->addWidget(tmpLabel, 2, 0, Qt::AlignRight);
	layout->addWidget(&levelLabel, 2, 1);
	setLayout(layout);

	updatePanel();
}

QSize Panel::minimumSizeHint() const {
	return QSize(150, 40);
}

QSize Panel::sizeHint() const {
	return QSize(150, 40);
}

void Panel::updatePanel() {
	scoreLabel.setNum(gameboard.getScore());
	comboLabel.setNum(gameboard.getCombo());
	levelLabel.setNum(gameboard.getLevel());
}