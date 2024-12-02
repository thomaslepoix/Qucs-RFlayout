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
	struct Color { double r=0.0, g=0.0, b=0.0; };
	struct Colors;
	struct Theme {
		std::string_view name;
		Color background;
		Color substrate;
		Color track;
		Color port;
		Color via;
	};

	explicit Preview(QWidget* parent=nullptr);
	~Preview()=default;
	void set(std::vector<std::shared_ptr<Element>> const& all_elements, std::array<long double, 4> const& extrem_pos);
	void resetView();

	std::string_view getTheme();
	void setTheme(std::string const& _theme);
	void setTransparency(bool _flag_transparent);
	void setF2D(bool _flag_2d);
	void setFCtrl(bool _flag_ctrl);
	void setFShift(bool _flag_shift);

	static std::vector<Theme> const themes;

private:
	void drawAll();
	void drawShape3D(int npoint, long double tab_x[], long double tab_y[], long double z_min, long double z_max, Color color);
	void drawShape(int npoint, long double tab_x[], long double tab_y[], long double z);
	void drawShapeContour(int npoint, long double tab_x[], long double tab_y[], long double z_min, long double z_max);

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;

	void mousePressEvent(QMouseEvent* const event) override;
	void mouseMoveEvent(QMouseEvent* const event) override;
	void wheelEvent(QWheelEvent* const event) override;

	void setAlpha();
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

	Theme theme;

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

	double alpha=1.0; // [0,1]

	bool flag_2d=false;
	bool flag_ctrl=false;
	bool flag_shift=false;
	bool flag_transparent=false;
};

#endif // QRFL_MINIMAL
