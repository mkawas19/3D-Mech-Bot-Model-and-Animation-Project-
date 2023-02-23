#include <GL/glut.h>
#include<stdio.h>
#include<GL/freeglut.h>
#include<GL/GLU.h>
#include <iostream>

#define DEG2RAD 3.14/180.0

GLUquadricObj* myobject;
double x = 0, z = 0;
float tyreAng = 0;


void surface()
{
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
}

void drawTyre(float rot)
{
    glPushMatrix();
    glRotatef(rot, 0, 0, 1);

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
    glColor3f(0,0,0);
    glTranslatef(0, 0, -0.1);
    glutSolidCube(0.3);
    glPopMatrix();

    glPopMatrix();

}

void tyreBase(float angle)
{
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
    glVertex3f( 0.1,  0.0,  1.2);
    glVertex3f( 0.1,  2.1,  1.2);
    glVertex3f(-0.1,  2.1,  1.2);
    glVertex3f(-0.1,  0.0,  1.2);
    glEnd();
    glPopMatrix();


    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-0,-2, 0);

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
    glVertex3f( 0.5, 2.15, 1.0);
    glVertex3f( 0.5, 1.85, 1.0);

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


    surface();
    glPushMatrix();
    glTranslatef(x, 0, z);
    glRotatef(bodyRot, 0, 1, 0);
    drawTyre(tyreRot);
    tyreBase(faceRot);
    glPopMatrix();
}