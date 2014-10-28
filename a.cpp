#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "vec.cpp"
#include "math.h"
#include <stdlib.h> 
#include <utility>
#include <unistd.h>
#include <climits>
#include <iostream>
using namespace std;


double x,z;
vector3d vball;
int refreshMills=10;
double phi=0,theta=0;
double cube1=0.0,cube2=0.0,floorsize=0.0;


void keySpecialUp(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP: phi+=10; break;
    case GLUT_KEY_DOWN: phi-=10; break;
    case GLUT_KEY_LEFT: theta-=10; break;
    case GLUT_KEY_RIGHT: theta+=10; break;
  }
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,10,-20,0,0,0,0,1,0);
	
	glColor3f(1.0,0,0);
	glBegin(GL_QUADS);
		glVertex3f(-floorsize,0,-floorsize);
		glVertex3f(-floorsize,0,floorsize);
		glVertex3f(floorsize,0,floorsize);
		glVertex3f(floorsize,0,-floorsize);
	glEnd();
	glColor3f(1,1,1);
	
	glPushMatrix();
	GLUquadricObj *base,*btm,*top,*bulb;
	base=gluNewQuadric();
	btm=gluNewQuadric();
	top=gluNewQuadric();
	bulb=gluNewQuadric();
	glRotatef(90,1,0,0);
	gluCylinder(base,1,1,0.15,20,100);
	glColor3f(0,0,1);
	gluDisk(btm,0,1,100,100);

	glRotatef(-90,1,0,0);
	glTranslatef(0,0,0.15);
	glColor3f(0,1,0);
	gluDisk(btm,0,1,100,100);
	glColor3f(1,1,1);
 	
 	//glScalef(1,5,1);
 	glRotatef(phi,0,0,-1);
 	glTranslatef(0,cube1/2.0,0);
	glutWireCube(cube1);

	
	glTranslatef(0,cube1/2.0,0);
	glRotatef(theta,0,0,-1);
	glTranslatef(0,cube2/2.0,0);
	glutWireCube(cube2);
	//glScalef(1,0.2,1);

	glRotatef(0,0,0,-1);
	glTranslatef(0,0.1+cube2/2.0,0);
	glRotatef(90,1,0,0);
	gluCylinder(bulb,0.3,0.1,0.2,50,50);
	glRotatef(-90,1,0,0);
	

	glPopMatrix();
	gluLookAt(0,10,-20,0,0,0,0,1,0);
	glTranslatef(x,0,z);
	cout << "x "<<x<<" z "<< z << endl;
	glutSolidSphere(1.0,500,500);
	x+=vball.x*refreshMills/1000;
	z+=vball.z*refreshMills/1000;
	if(abs((int)x)>(int)floorsize)
		x=-x;
	if(abs((int)z)>(int)floorsize)
		z=-z;
	//usleep(10000);

	
		
	glFlush();
	glutSwapBuffers();


}

// void reshape(int x,int y)
// {
//     if (y == 0 || x == 0) return;
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-10.0, 10.0, -10.0, 10.0, -100.0, 100.0);
//     glMatrixMode(GL_MODELVIEW);
//     glViewport(0,0,x,y);

// }


void reshape(int x, int y) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (y == 0) y = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)x / (GLfloat)y;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, x, y);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(60.0f, aspect, 0.05f, 1000.0f);
}

void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void init()
{
	 x=0;z=0;
	 vball.x=30;
	 vball.y=0;
	 vball.z=10;
	 cube1=0.8;
	 cube2=0.4;
	 floorsize=50;
	 phi=0;
	 theta=0;

}

int main (int argc, char **argv)
{
    
   	init();
    glutInit(&argc, argv); 
    glutInitWindowSize(300,300);
    glutCreateWindow("Heirarchical Modelling");
    glutDisplayFunc(display);
    glutSpecialUpFunc(keySpecialUp);
    glutReshapeFunc(reshape);
    glutTimerFunc(refreshMills,timer,0);
    glutPostRedisplay();
    glutMainLoop();
    return 0;
}
