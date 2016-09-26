#include <QtGui>
#if QT_VERSION >= 0x050000
  #include <QtWidgets>
#else
  #include <QtGui>
#endif // QT_VERSION

#include <iostream>
#include "Window.h"

using namespace std;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	Window window;
	window.show();

	return app.exec();
}
