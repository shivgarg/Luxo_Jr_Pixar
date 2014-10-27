#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include "math.h"
#include <stdlib.h> 
#include <utility>
#include <climits>


void display()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	// Load Identity
	glLoadIdentity();
	// Base Transformation
	glRotatef(45,1,0,0);

	glTranslatef(5,5,0);
	
	// Draw base;
	glBegin(GL_POINTS);
	for(int i=0;i<1000;++i)
	  {
	  	glVertex3f(cos(5*3.14159*i/1000.0),0,sin(5*3.14159*i/1000.0));
	  }
 	glEnd();
 	
 	glRotatef(30,0,1,0);
 	glScalef(1,5,1);
 	glTranslatef(0,0.4,0);
	glutWireCube(0.8);

	//glScalef(1,5,1);
	glRotatef(35,0,0,1);
	glTranslatef(0,0.6,0);

	glutWireCube(0.4);


	
		
	glFlush();
	glutSwapBuffers();


}

void reshape(int x,int y)
{
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);

}
int main (int argc, char **argv)
{
    
    glutInit(&argc, argv); 
    glutInitWindowSize(300,300);
    glutCreateWindow("Heirarchical Modelling");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
