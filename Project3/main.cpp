#include <windows.h>  
#include <GL/glut.h>  
#include <Math.h>     
#define PI 3.14159265f




char title[] = "Full-Screen & Windowed Mode";
int windowWidth = 640;
int windowHeight = 480;
int windowPosX = 50;
int windowPosY = 50;

GLfloat ballRadius = 0.5f;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLfloat xSpeed = 0.02f;
GLfloat ySpeed = 0.007f;
int refreshMillis = 30;


GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

bool fullScreenMode = true;
bool paused = false;
GLfloat xSpeedSaved, ySpeedSaved;


void initGL() {
	glClearColor(0.2, 0.2, 0.2, 0.0);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex2f(0.4f, 0.2f);
	glVertex2f(0.6f, 0.2f);
	glVertex2f(0.7f, 0.4f);
	glVertex2f(0.6f, 0.6f);
	glVertex2f(0.4f, 0.6f);
	glVertex2f(0.3f, 0.4f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(-0.7f, -0.6f);
	glVertex2f(-0.1f, -0.6f);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(-0.7f, 0.0f);

	glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
	glVertex2f(-0.9f, -0.7f);
	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(-0.5f, -0.7f);
	glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
	glVertex2f(-0.5f, -0.3f);
	glColor3f(1.0f, 1.0f, 1.0f); // White
	glVertex2f(-0.9f, -0.3f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex2f(0.1f, -0.6f);
	glVertex2f(0.7f, -0.6f);
	glVertex2f(0.4f, -0.1f);

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex2f(0.3f, -0.4f);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(0.9f, -0.4f);
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex2f(0.6f, -0.9f);
	glEnd();
	glTranslatef(ballX, ballY, 0.0f);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	int numSegments = 100;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) {
		angle = i * 2.0f * PI / numSegments;
		glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
	}
	glEnd();



	glutSwapBuffers();



	ballX += xSpeed;
	ballY += ySpeed;


	if (ballX > ballXMax) {
		ballX = ballXMax;
		xSpeed = -xSpeed;
	}
	else if (ballX < ballXMin) {
		ballX = ballXMin;
		xSpeed = -xSpeed;
	}
	if (ballY > ballYMax) {
		ballY = ballYMax;
		ySpeed = -ySpeed;
	}
	else if (ballY < ballYMin) {
		ballY = ballYMin;
		ySpeed = -ySpeed;
	}


}


void reshape(GLsizei width, GLsizei height) {

	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;


	glViewport(0, 0, width, height);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height) {
		clipAreaXLeft = -1.0 * aspect;
		clipAreaXRight = 1.0 * aspect;
		clipAreaYBottom = -1.0;
		clipAreaYTop = 1.0;
	}
	else {
		clipAreaXLeft = -1.0;
		clipAreaXRight = 1.0;
		clipAreaYBottom = -1.0 / aspect;
		clipAreaYTop = 1.0 / aspect;
	}
	gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
	ballXMin = clipAreaXLeft + ballRadius;
	ballXMax = clipAreaXRight - ballRadius;
	ballYMin = clipAreaYBottom + ballRadius;
	ballYMax = clipAreaYTop - ballRadius;
}


void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refreshMillis, Timer, 0);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:     // ESC key
		exit(0);
		break;
	}

}


void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		fullScreenMode = !fullScreenMode;
		if (fullScreenMode) {
			windowPosX = glutGet(GLUT_WINDOW_X);
			windowPosY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		}
		else {
			glutReshapeWindow(windowWidth, windowHeight);
			glutPositionWindow(windowPosX, windowPosX);
		}
		break;

	case GLUT_KEY_UP:
		ballRadius *= 1.05f;
		ballXMin = clipAreaXLeft + ballRadius;
		ballXMax = clipAreaXRight - ballRadius;
		ballYMin = clipAreaYBottom + ballRadius;
		ballYMax = clipAreaYTop - ballRadius;
		break;
	case GLUT_KEY_DOWN:
		ballRadius *= 0.95f;
		ballXMin = clipAreaXLeft + ballRadius;
		ballXMax = clipAreaXRight - ballRadius;
		ballYMin = clipAreaYBottom + ballRadius;
		ballYMax = clipAreaYTop - ballRadius;
		break;
	}

}


void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		paused = !paused;
		if (paused) {
			xSpeedSaved = xSpeed;
			ySpeedSaved = ySpeed;
			xSpeed = 0;
			ySpeed = 0;
		}
		else {
			xSpeed = xSpeedSaved;
			ySpeed = ySpeedSaved;
		}
	}
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowPosX, windowPosY);
	glutCreateWindow("Geometry");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, Timer, 0);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);
	glutFullScreen();
	glutMouseFunc(mouse);
	initGL();
	glutMainLoop();
	return 0;
}