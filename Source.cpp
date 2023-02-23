#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include<GL/freeglut.h>
#define DEG2RAD 3.14/180.0

double x = 0, z = 0;
float tyreAng = 0;




//Camera Roation Variables  
float theeta = 0;
float xc = 0.0f, zc = 10.0f, yc = 1.0f;
double xcOffset = 0, zcOffset = 0;

//Screen Size Variables 
const int width = 1202;
const int height = 650;

//Variables to Keep the Old Values of Camera Rotation
int oldX = 0, oldY = 0;

//To Start The Camera Movement from Mouse
int camInit = 0;


float headRot = 0;
float bodyRot = 0;
bool bodyTrans = false;
float tyreRot = 0;

bool help = false;

void resizableWindow(int w, int h);
//Function to set the new values for the camera position after the pressing of keys on keyboard
void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {

	case GLUT_KEY_UP:
		yc -= 0.1;
		break;
	case GLUT_KEY_DOWN:
		yc += 0.1;
		break;
	case GLUT_KEY_LEFT:
		theeta -= 0.02f;
		xc = 10 * sin(theeta);
		zc = 10 * cos(theeta);
		break;
	case GLUT_KEY_RIGHT:
		theeta += 0.02f;
		xc = 10 * sin(theeta);
		zc = 10 * cos(theeta);
		break;

	case GLUT_KEY_F1:
		if (help == false)
		{
			help = true;
		}
		else if (help == true)
		{
			help = false;
		}
		break;
	}
	glutPostRedisplay();
}

void processKeyboardKeys(unsigned char key, int x, int y)
{
	if (key == 'u')
	{
		if (headRot < 45) {
			headRot += 0.9;
		}
		glutPostRedisplay();
	}
	if (key == 'b')
	{
		if (headRot > -45) {
			headRot -= 0.9;
		}
		glutPostRedisplay();
	}
	if (key == 'a')
	{
		bodyRot += 1.5;
		glutPostRedisplay();
	}
	if (key == 'd')
	{
		bodyRot -= 1.5;
		glutPostRedisplay();
	}
	if (key == 'w')
	{
		bodyTrans = true;
		tyreRot -= 10;
		glutPostRedisplay();
	}

}


void resizableWindow(int w, int h)
{
	if (h == 0)
	{
		h = 1;
	}
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void illumination()
{
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat pozitial0[] = { 10.0, 5.0, 10.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
}


void renderRobot(float faceRot, float bodyRot, bool trans, float tyreRot)
{
	if (trans == true) {
		double newDx;
		double newDz;
		newDz = z + ((0.8f * cos((bodyRot + 90) * DEG2RAD)) * 0.8);
		newDx = x + ((0.8f * sin((bodyRot + 90) * DEG2RAD)) * 0.8);
		z = newDz;
		x = newDx;
	}
	//Surface Rendering
	glPushMatrix();
	glNormal3f(1, 0, 0);
	glColor3f(0.32, 0.49, 0.46);
	glBegin(GL_QUADS);
	glVertex3f(-50, -1.0, -50);
	glVertex3f(50, -1.0, -50);
	glVertex3f(50, -1.0, 50);
	glVertex3f(-50, -1.0, 50);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, z);
	glRotatef(bodyRot, 0, 1, 0);

	//Rendering Tyre and Rotating It
	glPushMatrix();
	glRotatef(tyreRot, 0, 0, 1);

	glPushMatrix();
	glNormal3f(1, 0, 0);
	glColor3f(0.80, 0.80, 0.80);
	glutSolidCylinder(1.0, 1.0, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.329412, 0.329412, 0.329412);
	glTranslatef(0, 0, -0.1);
	glutSolidCylinder(0.85, 1.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, 0, -0.1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	//Rendering Tyre Bearing and Face Holder
	glPushMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 1.0);
	glColor3f(0.752941, 0.752941, 0.752941);
	glutSolidCylinder(0.25, 0.3, 100, 100);
	glPopMatrix();

	//Grills to hold head
	glPushMatrix();
	glColor3f(0.90, 0.91, 0.98);
	glBegin(GL_QUADS);
	glVertex3f(0.1, 0.0, 1.2);
	glVertex3f(0.1, 2.1, 1.2);
	glVertex3f(-0.1, 2.1, 1.2);
	glVertex3f(-0.1, 0.0, 1.2);
	glEnd();
	glPopMatrix();


	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotatef(faceRot, 0, 0, 1);
	glTranslatef(-0, -2, 0);

	glPushMatrix();
	glTranslatef(0, 2, 1.0);
	glColor3f(0.752941, 0.752941, 0.752941);
	glutSolidCylinder(0.15, 0.25, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.90, 0.91, 0.98);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 1.85, 1.0);
	glVertex3f(-0.5, 2.15, 1.0);
	glVertex3f(0.5, 2.15, 1.0);
	glVertex3f(0.5, 1.85, 1.0);

	glVertex3f(-0.5, 1.85, 0);
	glVertex3f(-0.5, 2.15, 0);
	glVertex3f(0.5, 2.15, 0);
	glVertex3f(0.5, 1.85, 0);

	glVertex3f(-0.5, 2.15, 0);
	glVertex3f(-0.5, 2.15, 1);
	glVertex3f(0.5, 2.15, 1);
	glVertex3f(0.5, 2.15, 0);

	glVertex3f(-0.5, 1.85, 0);
	glVertex3f(-0.5, 1.85, 1);
	glVertex3f(0.5, 1.85, 1);
	glVertex3f(0.5, 1.85, 0);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.90, 0.91, 0.98);
	glBegin(GL_QUADS);
	glVertex3f(-0.2, 2.15, 0.8);
	glVertex3f(-0.2, 2.5, 0.8);
	glVertex3f(0.2, 2.5, 0.8);
	glVertex3f(0.2, 2.15, 0.8);

	glVertex3f(-0.2, 2.15, 0.2);
	glVertex3f(-0.2, 2.5, 0.2);
	glVertex3f(0.2, 2.5, 0.2);
	glVertex3f(0.2, 2.15, 0.2);

	glVertex3f(0.2, 2.15, 0.2);
	glVertex3f(0.2, 2.5, 0.2);
	glVertex3f(0.2, 2.5, 0.8);
	glVertex3f(0.2, 2.15, 0.8);

	glVertex3f(-0.2, 2.15, 0.2);
	glVertex3f(-0.2, 2.5, 0.2);
	glVertex3f(-0.2, 2.5, 0.8);
	glVertex3f(-0.2, 2.15, 0.8);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, 2.8, 0.5);

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glutSolidCone(0.65, 1.9, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(1.65, 0, 0);
	glScalef(1.5, 1, 1);
	glutSolidCube(0.3);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();


	glPopMatrix();
}

void disp(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	illumination();
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glLoadIdentity();
	glClearColor(0.74902, 0.847059, 0.847059, 0.0);
	gluLookAt(xc + xcOffset, yc, zc + zcOffset, 0, 0, 0, 0, 1, 0);
	renderRobot(headRot, bodyRot, bodyTrans, tyreRot);
	bodyTrans = false;

	glutSwapBuffers();
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}




int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glColor3f(0.3f, 0.7f, 0.9f);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Robot Animation");
	glutDisplayFunc(disp);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processKeyboardKeys);
	glutReshapeFunc(resizableWindow);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

	return 1;
}