/***************************************************************************
                               preview.hpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PREVIEW_HPP
#define PREVIEW_HPP

#define _USE_MATH_DEFINES

#include <QtWidgets>
#include <QGLWidget>
#include <QOpenGLFunctions_2_0>
//#include <GL/glut.h>

#include <array>
#include <vector>
#include <memory>
#include <cmath>

#include "microstrip/element.hpp"

class Preview : public QGLWidget, protected QOpenGLFunctions_2_0 {
//	Q_OBJECT
public :
	explicit Preview(QWidget *parent=0);
	~Preview();
	void set(std::vector<std::shared_ptr<Element>> const& tab_all, std::array<long double, 4> const& extrem_pos);
	void resetView(void);

	void setFCtrl(bool flag_ctrl);
	void setFShift(bool _flag_shift);
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

//	void keyPressEvent(QKeyEvent *event);
//	void keyReleaseEvent(QKeyEvent *event);

private:
	enum t_color{orange, green};
	void drawAll(void);
	void drawShape(int npoint, long double tab_x[], long double tab_y[], enum t_color color);

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
	long double fit_factor=1;
	long double fit_x_offset=0;
	long double fit_y_offset=0;

	bool flag_ctrl=0;
	bool flag_shift=0;
};

#endif // PREVIEW_HPP
