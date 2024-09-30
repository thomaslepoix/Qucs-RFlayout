///*****************************************************************************
/// @date Oct 2018
/// @copyright GPL-3.0-or-later
/// @author Thomas Lepoix <thomas.lepoix@protonmail.ch>
///*****************************************************************************

#ifndef QRFL_MINIMAL

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <optional>

#include "preview.hpp"
using namespace std;

//******************************************************************************
struct Preview::Colors {
	Colors() = delete;
	static constexpr Color BLACK { 0.0, 0.0, 0.0 };
	static constexpr Color WHITE { 1.0, 1.0, 1.0 };
	static constexpr Color GREY_MID { 0.5, 0.5, 0.5 };
	static constexpr Color GREY_DARK { 0.3, 0.3, 0.3 };
	static constexpr Color ORANGE { 1.0, 0.5, 0.0 };
	static constexpr Color YELLOW { 1.0, 1.0, 0.0 };
	static constexpr Color BLUE { 0.0, 0.0, 1.0 };
	static constexpr Color RED { 1.0, 0.0, 0.0 };
	static constexpr Color GREEN { 0.0, 1.0, 0.0 };
	static constexpr Color GREEN_DARK { 0.039, 0.427, 0.0 };
	static constexpr Color QRFL_DOC_ORANGE { 1.0, 0.502, 0.0 };
	static constexpr Color QUCS_GUI_CREAM_BACKGROUND { 1.0, 0.98, 0.882 };
	static constexpr Color QUCS_GUI_DARK_BLUE { 0.0, 0.0, 0.502 };
	static constexpr Color QUCS_GUI_DARK_RED { 0.502, 0.0, 0.0 };
	static constexpr Color QUCS_LOGO_ORANGE_MAIN { 1.0, 0.6, 0.0 };
	static constexpr Color QUCS_LOGO_ORANGE_BACK { 0.914, 0.58, 0.086 };
	static constexpr Color QUCS_LOGO_ORANGE_DARK { 0.388, 0.306, 0.176 };
	static constexpr Color QUCS_SITE_RED_DARK { 0.651, 0.0, 0.0 };
	static constexpr Color QUCS_TRANSCALC_GREY { 0.804, 0.804, 0.804 };
	static constexpr Color QUCS_TRANSCALC_ORANGE { 1.0, 0.698, 0.22 };
	static constexpr Color SLVS_GUI_GREEN { 0.0, 0.8, 0.0 };
	static constexpr Color SLVS_GUI_GREY { 0.39, 0.39, 0.39 };
	static constexpr Color SLVS_GUI_TEAL { 0.0, 0.4, 0.4 };
	static constexpr Color SLVS_LOGO_GREEN { 0.263, 0.949, 0.047 };
	static constexpr Color SLVS_LOGO_GREY { 0.796, 0.796, 0.796 };
	static constexpr Color SLVS_LOGO_PINK { 0.894, 0.047, 0.949 };
};

//******************************************************************************
vector<Preview::Theme> const Preview::themes {
	{
		.name = "Flashy",
		.background = Colors::GREY_DARK,
		.substrate = Colors::SLVS_GUI_GREEN,
		.track = Colors::YELLOW,
		.port = Colors::BLACK,
		.via = Colors::ORANGE
	},
	{
		.name = "HighContrast", // Not much contrast when transparent
		.background = Colors::GREY_MID,
		.substrate = Colors::BLACK,
		.track = Colors::WHITE,
		.port = Colors::BLUE,
		.via = Colors::GREEN
	},
	{
		.name = "HighContrast2",
		.background = Colors::BLACK,
		.substrate = Colors::GREY_MID,
		.track = Colors::WHITE,
		.port = Colors::BLUE,
		.via = Colors::GREEN
	},
	{
		.name = "QucsGUI",
		.background = Colors::QUCS_GUI_CREAM_BACKGROUND,
		.substrate = Colors::BLACK,
		.track = Colors::QUCS_GUI_DARK_BLUE,
		.port = Colors::RED,
//		.via = Colors::QUCS_LOGO_ORANGE_MAIN
		.via = Colors::QUCS_GUI_DARK_RED
	},
	{
		.name = "QucsIcon", // not much contrast when transparent
		.background = Colors::QUCS_GUI_CREAM_BACKGROUND,
		.substrate = Colors::QUCS_LOGO_ORANGE_DARK,
		.track = Colors::QUCS_LOGO_ORANGE_MAIN,
		.port = Colors::QUCS_GUI_DARK_BLUE,
		.via = Colors::QUCS_LOGO_ORANGE_BACK
	},
//	{
//		.name = "CAD",
//		.background = Colors::GREY_DARK,
//		.substrate = Colors::GREEN_DARK,
//		.track = Colors::QRFL_DOC_ORANGE,
////		.port = Colors::,
//		.via = Colors::QUCS_LOGO_ORANGE_BACK
//	},
	{
		.name = "Solvespace",
		.background = Colors::BLACK,
		.substrate = Colors::SLVS_GUI_GREY,
		.track = Colors::SLVS_LOGO_PINK,
		.port = Colors::SLVS_LOGO_GREEN,
		.via = Colors::SLVS_GUI_TEAL
	},
	{
		.name = "Transcalc", // Not much contrast when transparent
		.background = Colors::WHITE,
		.substrate = Colors::QUCS_TRANSCALC_GREY,
		.track = Colors::QUCS_TRANSCALC_ORANGE,
		.port = Colors::BLUE,
		.via = Colors::BLACK
	}
};

//******************************************************************************
Preview::Preview(QWidget* parent) : QOpenGLWidget(parent), QOpenGLFunctions_2_0() {
	}

//******************************************************************************
void Preview::initializeGL() {
	initializeOpenGLFunctions();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND); // Enable transparency.
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE); // Draw both faces of primitives.

//	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	setAlpha();
	}

//******************************************************************************
void Preview::paintGL() {
	glClearColor(theme.background.r, theme.background.g, theme.background.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	glLoadIdentity();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0.0, 0.0, 2.0);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

	setAlpha();
	drawAll();
	}

//******************************************************************************
void Preview::resizeGL(int width, int height) {
	int const side = qMax(width, height);
	double const aspect = (double) width / (double) height;
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Some higher z values allow zooming without making the scene disappear.
	glOrtho(-aspect, +aspect, -1, +1, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	}

////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
static void qNormalizeAngle(int& angle) {
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
	}

//******************************************************************************
void Preview::setXRotation(int angle) {
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		update();
		}
	}

//******************************************************************************
void Preview::setYRotation(int angle) {
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		update();
		}
	}

//******************************************************************************
void Preview::setZRotation(int angle) {
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		update();
		}
	}

//******************************************************************************
void Preview::mousePressEvent(QMouseEvent* const event) {
	lastPos = event->position();
	}

//******************************************************************************
void Preview::mouseMoveEvent(QMouseEvent* const event) {
	int const dx = event->position().x() - lastPos.x();
	int const dy = event->position().y() - lastPos.y();

	if(event->buttons() & Qt::LeftButton) {
		if(!flag_2d) {
			setXRotation(xRot + 8 * dy);
			setYRotation(yRot + 8 * dx);
		} else {
			setZRotation(zRot + 8 * dx);
			setZRotation(zRot + 8 * dy);
			}
	} else if(event->buttons() & Qt::RightButton) {
		if(!flag_2d) {
			setXRotation(xRot + 8 * dy);
			}
		setZRotation(zRot + 8 * dx);
		}

	lastPos = event->pos();
	}


//qucs        SHIFT _ CTRL + NONE | <-
//altium      SHIFT _ CTRL + NONE |
//inkscape    SHIFT _ CTRL + NONE |
//gimp        SHIFT _ CTRL + NONE |
//kicad       SHIFT | CTRL _ NONE +
//pcb-rnd     SHIFT | CTRL _ NONE +
//openems                    NONE +
//gmsh                       NONE +
//this        SHIFT _ CTRL + NONE |

//******************************************************************************
void Preview::wheelEvent(QWheelEvent* event) {
	if(flag_ctrl) {
		factor+=(long double)event->angleDelta().y()/240*fit_factor;
		if(factor<0.0) factor=0.0;
	} else if(flag_shift) {
		x_offset-=(long double)event->angleDelta().y()/240*fit_x_offset;
	} else {
		y_offset-=(long double)event->angleDelta().y()/240*fit_y_offset;
		}
	update();
	}

//******************************************************************************
static double to_normalized_range(size_t i) {
	return (double) i / (double) numeric_limits<size_t>::max();
	}

//******************************************************************************
void Preview::setAlpha() {
	if(flag_transparent) {
		// Disable depth test and enable color blending.
		glDepthFunc(GL_ALWAYS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		alpha=to_normalized_range(numeric_limits<size_t>::max()/10*3);
	} else {
		// Enable depth test and disable color blending.
		glDepthFunc(GL_LEQUAL);
		glBlendFunc(GL_ONE, GL_ZERO);
		alpha=to_normalized_range(numeric_limits<size_t>::max());
		}
	}

//******************************************************************************
void Preview::setTransparency(bool _flag_transparent) {
	flag_transparent=_flag_transparent;
	update();
	}

//******************************************************************************
void Preview::setTheme(string const& _theme) {
	auto const find_theme = [](string const& name) -> optional<Theme> {
		auto const& it = find_if(begin(themes), end(themes),
			[&name](Theme const& theme) {
				return (theme.name == name);
				});
		if(it != end(themes))
			return *it;
		else
			return nullopt;
		};

	if(auto const t = find_theme(_theme); t) {
		theme=t.value();
	} else {
		theme=find_theme("Flashy").value();
		}
	}

//******************************************************************************
string_view Preview::getTheme() {
	return theme.name;
	}

//******************************************************************************
void Preview::setF2D(bool _flag_2d) {
	flag_2d=_flag_2d;
	}

//******************************************************************************
void Preview::setFCtrl(bool _flag_ctrl) {
	flag_ctrl=_flag_ctrl;
	}

//******************************************************************************
void Preview::setFShift(bool _flag_shift) {
	flag_shift=_flag_shift;
	}

////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
void Preview::resetView() {
	xRot=0;
	yRot=0;
	zRot=0;
	factor=fit_factor;
	x_offset=fit_x_offset;
	y_offset=fit_y_offset;
	update();
	}

//******************************************************************************
void Preview::set(vector<shared_ptr<Element>> const& _all_elements, array<long double, 4> const& extrem_pos) {
	all_elements.clear();
	all_elements=_all_elements;
	fit_factor=1/(qMax(extrem_pos[XMAX], extrem_pos[YMAX])/2);
	fit_x_offset=-extrem_pos[XMAX]/2;
	fit_y_offset=-extrem_pos[YMAX]/2;
	resetView();
	}

//******************************************************************************
void Preview::drawAll() {
	glScalef(factor, factor, factor);

	long double z_fighting_offset=0;

	map<string, shared_ptr<Element>> substs;
	for(shared_ptr<Element> it : all_elements) {
		if(!it->getActive())
			continue;
		QString const type=QString::fromStdString(it->getType());
		if(type=="SUBST") {
			z_fighting_offset=it->getT()/20;
			long double tab_x[it->getNpoint()];
			long double tab_y[it->getNpoint()];
			for(int i=0;i<it->getNpoint();i++) {
				tab_x[i]=it->getP(i, X, R, ABS)+x_offset;
				tab_y[i]=-(it->getP(i, Y, R, ABS)+y_offset);
				}
			// TODO To avoid Z fighting, making subst and shaped overlap seems
			// to give better visual results than putting a space between those.
			// Problem: if the substrate overlaps an element that have 0 thickness,
			// the element becomes invisible without transparency.
			// Should not happen anyway because a block cannot be associated with a
			// substrate if not all the shapes are associated to it.
			// => To verify before allowing that.
//			drawShape3D(it->getNpoint(), tab_x, tab_y, 0+z_fighting_offset, -it->getH(), theme.substrate);
			drawShape3D(it->getNpoint(), tab_x, tab_y, 0-z_fighting_offset, -it->getH(), theme.substrate);
			substs.emplace(it->getLabel(), it);
			}
		}

	auto const getSubst=[&substs](string const& subst_label) -> Element* {
		if(substs.contains(subst_label))
			return substs.at(subst_label).get();
		else
			return nullptr;
		};

	for(shared_ptr<Element> it : all_elements) {
		if(!it->getActive())
			continue;
		QString const type=QString::fromStdString(it->getType());
		if(type=="MCORN"
		|| type=="MCROSS"
		|| type=="MMBEND"
		|| type=="MLIN"
		|| type=="MRSTUB"
		|| type=="MTEE") {
			Element const* const subst=getSubst(it->getSubst());
			long double const t= subst ? subst->getT() : 0;
			long double tab_x[it->getNpoint()];
			long double tab_y[it->getNpoint()];
			for(int i=0;i<it->getNpoint();i++) {
				tab_x[i]=it->getP(i, X, R, ABS)+x_offset;
				tab_y[i]=-(it->getP(i, Y, R, ABS)+y_offset);
				}
			drawShape3D(it->getNpoint(), tab_x, tab_y, 0, t, theme.track);
		} else if(type=="MCOUPLED") {
			Element const* const subst=getSubst(it->getSubst());
			long double const t= subst ? subst->getT() : 0;
			long double tab_x[it->getNpoint()/2];
			long double tab_y[it->getNpoint()/2];
			for(int i=0;i<it->getNpoint()/2;i++) {
				tab_x[i]=it->getP(i, X, R, ABS)+x_offset;
				tab_y[i]=-(it->getP(i, Y, R, ABS)+y_offset);
				}
			drawShape3D(it->getNpoint()/2, tab_x, tab_y, 0, t, theme.track);
			for(int i=it->getNpoint()/2;i<it->getNpoint();i++) {
				tab_x[i-it->getNpoint()/2]=it->getP(i, X, R, ABS)+x_offset;
				tab_y[i-it->getNpoint()/2]=-(it->getP(i, Y, R, ABS)+y_offset);
				}
			drawShape3D(it->getNpoint()/2, tab_x, tab_y, 0, t, theme.track);
			}
		}

	for(shared_ptr<Element> it : all_elements) {
		if(!it->getActive())
			continue;
		QString const type=QString::fromStdString(it->getType());
		if(type=="MVIA") {
			Element const* const subst=getSubst(it->getSubst());
			long double const h= subst ? subst->getH() : 0;
			long double const t= subst ? subst->getT() : 0;
			long double tab_x[60];
			long double tab_y[60];
			for(int i=0;i<60;i++) {
				tab_x[i]=it->getX()+(it->getD()/2*cos((M_PI/180)*6*i)+x_offset);
				tab_y[i]=-(it->getY()+(it->getD()/2*sin((M_PI/180)*6*i)+y_offset));
				}
			drawShape3D(60, tab_x, tab_y, -h-z_fighting_offset, t+z_fighting_offset, theme.via);
		} else if(type=="Pac") {
			Element const* const subst=getSubst(it->getSubst());
			long double const h= subst ? subst->getH() : 0;
			long double const t= subst ? subst->getT() : 0;
			long double tab_x[it->getNpoint()];
			long double tab_y[it->getNpoint()];
			for(int i=0;i<it->getNpoint();i++) {
				tab_x[i]=it->getP(i, X, R, ABS)+x_offset;
				tab_y[i]=-(it->getP(i, Y, R, ABS)+y_offset);
				}
			drawShape3D(it->getNpoint(), tab_x, tab_y, -h-z_fighting_offset, t+z_fighting_offset, theme.port);
			}
		}
	}

//******************************************************************************
void Preview::drawShape3D(int npoint, long double tab_x[], long double tab_y[], long double z_min, long double z_max, Color color) {
	glColor4d(color.r, color.g, color.b, alpha);

	if(flag_2d) {
		drawShape(npoint, tab_x, tab_y, 0);
		if(flag_transparent) {
			// Draw two times to keep the same transparent color between 2D and 3D.
			drawShape(npoint, tab_x, tab_y, 0);
			}
	} else {
		drawShape(npoint, tab_x, tab_y, z_min);
		drawShape(npoint, tab_x, tab_y, z_max);
		drawShapeContour(npoint, tab_x, tab_y, z_min, z_max);
		}
	}

// The Stencil Buffer trick allows to draw concave polygons
//******************************************************************************
void Preview::drawShape(int npoint, long double tab_x[], long double tab_y[], long double z) {
	glClear(GL_STENCIL_BUFFER_BIT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glStencilFunc(GL_ALWAYS, 0xDEADBEEF, 0xDEADBEEF);
	glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

	glBegin(GL_POLYGON);
		for(int i=0;i<npoint;i++) {
			glVertex3f(tab_x[i], tab_y[i], z);
			}
	glEnd();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glBegin(GL_POLYGON);
		for(int i=0;i<npoint;i++) {
			glVertex3f(tab_x[i], tab_y[i], z);
			}
	glEnd();
	}

//******************************************************************************
void Preview::drawShapeContour(int npoint, long double tab_x[], long double tab_y[], long double z_min, long double z_max) {
	glDisable(GL_STENCIL_TEST);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(tab_x[npoint-1], tab_y[npoint-1], z_min);
		glVertex3f(tab_x[npoint-1], tab_y[npoint-1], z_max);
		for(int i=0;i<npoint;i++) {
			glVertex3f(tab_x[i], tab_y[i], z_min);
			glVertex3f(tab_x[i], tab_y[i], z_max);
			}
	glEnd();
	glEnable(GL_STENCIL_TEST);
	}

#endif // QRFL_MINIMAL
