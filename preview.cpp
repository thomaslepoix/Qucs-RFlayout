#include "preview.h"

Preview::Preview(QWidget* parent) : QGLWidget(parent), QOpenGLFunctions_2_0() {
	}

Preview::~Preview() {
	}

void Preview::initializeGL() {
	initializeOpenGLFunctions();

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glDepthFunc(GL_ALWAYS);    // Set the type of depth-test
//	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	}

void Preview::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	glLoadIdentity();
	glScalef(0.1, 0.1, 0.0);
//	glTranslatef(10.0, 10.0, 0.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

	drawtriangle();
	}

void Preview::resizeGL(int width, int height) {
//	glViewport(0, 0, width, height);
    int side = qMax(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
/*#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif*/
    glMatrixMode(GL_MODELVIEW);
	}

////////////////////////////////////////////////////////////////////////////////

static void qNormalizeAngle(int &angle) {
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
	}

void Preview::setXRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updateGL();
		}
	}

void Preview::setYRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updateGL();
		}
	}

void Preview::setZRotation(int angle) {
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updateGL();
		}
	}

void Preview::mousePressEvent(QMouseEvent *event) {
	lastPos = event->pos();
	}

void Preview::mouseMoveEvent(QMouseEvent *event) {
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
		}

	lastPos = event->pos();
	}

//void Preview::mouseScrollEvent(QMouseEvent *event) {
	

////////////////////////////////////////////////////////////////////////////////

void Preview::rescope(long double& x_min, long double& x_max, long double& y_min, long double& y_max) {
//	glTranslatef((x_max-x_min)/2, (y_max-y_min)/2, 0.0);
//	glScalef(
	}

void Preview::drawShape(int npoint, long double tab_x[], long double tab_y[]) {
std::cout << std::endl << "===========================================================================SHAPE" << std::endl;
std::cout << "npoint : " << npoint << std::endl;

	glClear(GL_STENCIL_BUFFER_BIT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
	glStencilFunc(GL_ALWAYS, 0x1, 0x1);
	glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

	glBegin(GL_POLYGON);
		for(int i=0;i<npoint;i++) {
std::cout << "tab_x[" << i << "] : " << tab_x[i] << std::endl;
std::cout << "tab_y[" << i << "] : " << tab_y[i] << std::endl;
			glVertex3d(tab_x[i], tab_y[i], 0.0f);
			}
	glEnd();
std::cout << "================================================================================" << std::endl;

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
	glStencilFunc(GL_EQUAL, 0x1, 0x1);                  
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
		for(int i=0;i<npoint;i++) {
			glVertex3d(tab_x[i], tab_y[i], 0.0d);
			}
	glEnd();
	}

void Preview::drawtriangle() {
/*    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();*/

//	glTranslatef(1.0, 1.0, -2.0);

/*    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();*/

//	glClear(GL_STENCIL_BUFFER_BIT);
//	glEnable(GL_STENCIL_TEST);
/*	glStencilFunc(GL_ALWAYS, 1, 0xFFFF);
	glColorMask(0, 0, 0, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
*/

//glEnable(GL_STENCIL_TEST);
glClear(GL_STENCIL_BUFFER_BIT);
glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
glStencilFunc(GL_ALWAYS, 0x1, 0x1);
glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);

	glBegin(GL_POLYGON);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();

glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
glStencilFunc(GL_EQUAL, 0x1, 0x1);                  
glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glBegin(GL_POLYGON);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();

//glDisable(GL_STENCIL_TEST);
	}

void Preview::drawcube() {
   glLoadIdentity();                 // Reset the model-view matrix
//   glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
 
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
	}
