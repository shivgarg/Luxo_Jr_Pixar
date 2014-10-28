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



vector3d vball;
int refreshMills=10;
double x,z,phi,theta,alpha,floorsize,baserad,baseht,c1rad,c2rad,c1ht,c2ht,bulbr1,bulbr2,bulbht,t=0;;
GLUquadricObj *base,*btm,*top,*bulb,*cube1,*cube2;

void keySpecialUp(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP: phi+=10; break;
    case GLUT_KEY_DOWN: phi-=10; break;
    case GLUT_KEY_LEFT: theta-=10; break;
    case GLUT_KEY_RIGHT: theta+=10; break;
    case GLUT_KEY_F5:  alpha+=10; break;
    case GLUT_KEY_F6: alpha-=10; break;
  }
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,-20,10,0,0,0,0,0,1);
	
	glColor3f(1.0,0,0);
	// glBegin(GL_QUADS);
	// 	glVertex3f(-floorsize,-floorsize,0);
	// 	glVertex3f(-floorsize,floorsize,0);
	// 	glVertex3f(floorsize,floorsize,0);
	// 	glVertex3f(floorsize,-floorsize,0);
	// glEnd();
	glColor3f(1,1,1);
	
	glPushMatrix();
	gluCylinder(base,baserad,baserad,baseht,20,100);
	glPushMatrix();
	//glTranslatef(0,0,-1*baseht/2.0);
	glColor3f(0,0,1);
	gluDisk(btm,0,baserad,100,100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,baseht);
	glColor3f(0.5,0.5,0.5);
	gluDisk(top,0,baserad,100,100);
	glPopMatrix();
	glTranslatef(0,0,baseht);
	glColor3f(1,0.5,0.5);
 	
 	glRotatef(phi,0,1,0);
 	//glTranslatef(0,0,c1ht/2.0);
 	//glRotatef(90,1,0,0);
	gluCylinder(cube1,c1rad,c1rad,c1ht,20,100);
	//glRotatef(-90,1,0,0);
	
	 glTranslatef(0,0,c1ht);
	 glRotatef(theta,0,1,0);
	// glTranslatef(0,0,c2ht/2.0);

	// //glRotatef(90,1,0,0);
	 gluCylinder(cube2,c2rad,c2rad,c2ht,20,100);
	// //glRotatef(-90,1,0,0);
	
	 
	 glTranslatef(0,0,c2ht);
	 glRotatef(alpha,0,1,0);
	// //glRotatef(90,1,0,0);
	 gluCylinder(bulb,bulbr1,bulbr2,bulbht,50,50);
	// //glRotatef(-90,1,0,0);
	

	 glPopMatrix();
	// gluLookAt(0,-20,10,0,0,0,0,0,1);
	 glTranslatef(x,z,0);
	 cout << "x "<<x<<" z "<< z << endl;
	 glutSolidSphere(0.5,500,500);
	 x+=vball.x*refreshMills/1000;
	 z+=vball.z*refreshMills/1000;
	 if(abs((int)x)>(int)floorsize)
	 	x=-x;
	 if(abs((int)z)>(int)floorsize)
	 	z=-z;
	// //usleep(10000);

	
		
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
	 baserad=0.6;
	 baseht=0.15;
	 c1rad=0.3;
	 c2rad=0.2;
	 c1ht=1.2;
	 c2ht=0.8;
	 bulbr1=0.2;
	 bulbr2=0.4;
	 bulbht=0.3;
	 x=0;z=0;
	 vball.x=30;
	 vball.y=0;
	 vball.z=10;
	 floorsize=50;
	 phi=0;
	 theta=30;
	 alpha=40;
	 base=gluNewQuadric();
	 btm=gluNewQuadric();
	top=gluNewQuadric();
	bulb=gluNewQuadric();
	cube1=gluNewQuadric();
	cube2=gluNewQuadric();

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
