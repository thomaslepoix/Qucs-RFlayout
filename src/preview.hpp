///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#pragma once

#ifndef QRFL_MINIMAL

#include <QtWidgets>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>

#include <array>
#include <memory>
#include <vector>

#include "microstrip/element.hpp"

//******************************************************************************
class Preview : public QOpenGLWidget, protected QOpenGLFunctions_2_0 {
	Q_OBJECT
public :
	explicit Preview(QWidget* parent=0);
	~Preview()=default;
	void set(std::vector<std::shared_ptr<Element>> const& all_elements, std::array<long double, 4> const& extrem_pos);
	void resetView();

	void setFCtrl(bool _flag_ctrl);
	void setFShift(bool _flag_shift);

//	void keyPressEvent(QKeyEvent* event);
//	void keyReleaseEvent(QKeyEvent* event);

private:
	enum t_color { orange, green };
	void drawAll();
	void drawShape(int npoint, long double tab_x[], long double tab_y[], enum t_color color);

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	void drawcube();
	void drawtriangle();

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    int xRot=0;
    int yRot=0;
    int zRot=0;
	QPointF lastPos;

	std::vector<std::shared_ptr<Element>> all_elements;
	long double factor=1;
	long double x_offset=0;
	long double y_offset=0;
	long double fit_factor=1;
	long double fit_x_offset=0;
	long double fit_y_offset=0;

	bool flag_ctrl=0;
	bool flag_shift=0;
};

#endif // QRFL_MINIMAL
