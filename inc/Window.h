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
	void directionChanged();

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	static const int IdRole = Qt::UserRole;
	
	RenderArea *renderArea;
	QLabel *blockShapeLabel, *blockColorLabel, *blockDirectionLabel;
	QComboBox *blockShapeComboBox, *blockColorComboBox, *blockDirectionComboBox;
};

#endif // WINDOW_H