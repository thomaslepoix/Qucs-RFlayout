#ifndef PREVIEW_H
#define PREVIEW_H

#include <QtWidgets>
#include <QGLWidget>
#include <QOpenGLFunctions_2_0>
//#include <GL/glut.h>

#include <vector>
#include <memory>
#include <iostream>
#include "microstrip/element.h"

class Preview : public QGLWidget, protected QOpenGLFunctions_2_0 {
//	Q_OBJECT
public :
	explicit Preview(QWidget *parent=0);
	~Preview();
	void set(std::vector<std::shared_ptr<Element>> const& tab_all, long double* const& extrem_pos);
	void resetView(void);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


private:
	void drawAll(void);
	void drawShape(int npoint, long double tab_x[], long double tab_y[]);

	void drawcube();
	void drawtriangle();

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    int xRot=0;
    int yRot=0;
    int zRot=0;
	QPoint lastPos;

	std::vector<std::shared_ptr<Element>> tab_all;
	long double factor=1;
	long double x_offset=0;
	long double y_offset=0;
};

#endif // PREVIEW_H
