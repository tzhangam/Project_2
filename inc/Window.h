#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "RenderArea.h"

class Window : public QWidget {
	Q_OBJECT

public:
	Window();

private slots:
	void shapeChanged();
	void colorChanged();

public:
	static const int IdRole = Qt::UserRole;
	
	RenderArea *renderArea;
	QLabel *blockShapeLabel, *blockColorLabel;
	QComboBox *blockShapeComboBox, *blockColorComboBox;
};

#endif // WINDOW_H