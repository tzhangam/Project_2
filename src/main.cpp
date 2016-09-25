// #include "Bitmap_Printer.h"
#include <QtWidgets>
#include <iostream>
#include "Window.h"

using namespace std;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Window window;
	window.show();

	return app.exec();
}