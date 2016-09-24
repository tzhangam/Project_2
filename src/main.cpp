// #include "Bitmap_Printer.h"
#include <QtWidgets>
#include <iostream>
#include "Block.h"

using namespace std;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	QWidget window;
	window.show();
	
	Block block(Block::BlockShape::kShapeI);

	return app.exec();
}