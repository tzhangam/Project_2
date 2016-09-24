#include <QtWidgets>

#include "window.h"

Window::Window() {
	// renderArea
	renderArea = new RenderArea;

	// block shape
	blockShapeComboBox = new QComboBox;
	blockShapeComboBox->addItem(tr("I shape"), Block::BlockShape::kShapeI);
	blockShapeComboBox->addItem(tr("L shape"), Block::BlockShape::kShapeL);
	blockShapeComboBox->addItem(tr("L shape mirrored"), Block::BlockShape::kShapeL_Mir);
	blockShapeComboBox->addItem(tr("T shape"), Block::BlockShape::kShapeT);
	blockShapeComboBox->addItem(tr("Z shape"), Block::BlockShape::kShapeZ);
	blockShapeComboBox->addItem(tr("Z shape mirrored"), Block::BlockShape::kShapeZ_Mir);
	blockShapeComboBox->addItem(tr("O shape"), Block::BlockShape::kShapeO);

	blockShapeLabel = new QLabel(tr("Block &Shape:"));
	blockShapeLabel->setBuddy(blockShapeLabel);

	// block color
	blockColorComboBox = new QComboBox;
	blockColorComboBox->addItem(tr("Red"), Block::BlockColor::kRed);
	blockColorComboBox->addItem(tr("Yellow"), Block::BlockColor::kYellow);
	blockColorComboBox->addItem(tr("Green"), Block::BlockColor::kGreen);
	blockColorComboBox->addItem(tr("Blue"), Block::BlockColor::kBlue);
	blockColorComboBox->addItem(tr("Cyan"), Block::BlockColor::kCyan);
	blockColorComboBox->addItem(tr("Pink"), Block::BlockColor::kPink);
	blockColorComboBox->addItem(tr("Black"), Block::BlockColor::kBlack);

	blockColorLabel = new QLabel(tr("Block &Color"));
	blockColorLabel->setBuddy(blockColorComboBox);

	// connect
	connect(blockShapeComboBox, SIGNAL(activated(int)),
		this, SLOT(shapeChanged()));
	connect(blockColorComboBox, SIGNAL(activated(int)),
		this, SLOT(colorChanged()));

	// layout
	QGridLayout *mainLayout = new QGridLayout;
	// mainLayout->setColumn
}

void Window::shapeChanged() {

}

void Window::colorChanged() {
	
}