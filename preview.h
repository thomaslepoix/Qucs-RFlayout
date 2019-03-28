#ifndef PREVIEW_H
#define PREVIEW_H

#include <QtWidgets>
#include <QGLWidget>
#include <QOpenGLFunctions_2_0>
//#include <GL/glut.h>

#include <iostream>
#include "microstrip/element.h"

class Preview : public QGLWidget, protected QOpenGLFunctions_2_0 {
//	Q_OBJECT
public :
	explicit Preview(QWidget *parent=0);
	~Preview();

	void drawShape(int npoint, long double tab_x[], long double tab_y[]);
	void rescope(long double& x_min, long double& x_max, long double& y_min, long double& y_max);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


private:
	void drawcube();
	void drawtriangle();

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    int xRot=0;
    int yRot=0;
    int zRot=0;
	QPoint lastPos;
};

#endif // PREVIEW_H
