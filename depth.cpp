
#include <GL/gl.h>
#include <GL/glu.h>
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
#include "first.h"
#include <iostream>
using namespace std;


vector3d vball;
int refreshMills=10;
int ballwait=0;
bool hit=false;
int hitwait=0;
int beta=0;
double x,z,phi,theta,alpha,floorsize,baserad,baseht,c1rad,c2rad,c1ht,c2ht,bulbr1,bulbr2,bulbht,t=0;
GLUquadricObj *base,*btm,*top,*bulb,*cube1,*cube2;

void keySpecialUp(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP: phi+=10; break;
    case GLUT_KEY_DOWN: phi-=10; break;
    case GLUT_KEY_LEFT: theta-=10; break;
    case GLUT_KEY_RIGHT: theta+=10; break;
    case GLUT_KEY_F5:  alpha+=10; break;
    case GLUT_KEY_F6: alpha-=10; break;
    case GLUT_KEY_F7: hit=true;break;
  }
}


void init(void) 
{
    baserad=1.3;
    baseht=0.3;
    c1rad=0.45;
    c2rad=0.45;
    c1ht=4;
    c2ht=3.5;
    bulbr1=0.4;
    bulbr2=2.0;
    bulbht=1.0f;
    x=0;z=0;
    vball.x=30;
    vball.y=0;
    vball.z=0;
    floorsize=30;
    phi=0;
    theta=30;
    alpha=40;
    beta=0;
    base=gluNewQuadric();
    btm=gluNewQuadric();
   top=gluNewQuadric();
   bulb=gluNewQuadric();
   cube1=gluNewQuadric();
   cube2=gluNewQuadric();

   GLfloat mat_specular[] = { 0, 1.0, 0, 0};
   GLfloat mat_shininess[] = { 0.0 };
   GLfloat light_position[] = { 10, 10, 10.0, 1.0 };
   glClearColor (1.0, 1.0,1.0, 1.0);
   glShadeModel (GL_SMOOTH);

   // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   gluLookAt(0,-20,10,0,0,0,0,0,1);
   GLfloat mat_specular[] = { 0.0, 1.0, 0, 0};
   GLfloat mat_shininess[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
    glColor3f(0.2,0.8,0.5);
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);    
 //    glTexCoord2f(0,0);
    glVertex3f(-50,-50,0);
     glNormal3f(0,0,1);
 //    glTexCoord2f(0,1);
     glVertex3f(-50,50,0);
     glNormal3f(0,0,1);
 //    glTexCoord2f(1,1);
     glVertex3f(50,50,0);
     glNormal3f(0,0,1);
 //    glTexCoord2f(1,0);
     glVertex3f(50,-50,0);
   glEnd();
   //glutSolidSphere (4.0, 20, 16);
	
   glColor3f(1,1,1);
   
   
   gluCylinder(base,baserad,baserad,baseht,20,100);
   glPushMatrix();
   //glTranslatef(0,0,-1*baseht/2.0);
   glColor3f(0,0,1);
   gluDisk(btm,0,baserad,100,100);
   //glPopMatrix();
   //glPushMatrix();
   glTranslatef(0,0,baseht);
   glColor3f(0.5,0.5,0.5);
   gluDisk(top,0,baserad,100,100);
   glPopMatrix();
   glRotatef(beta,0,0,1);
   glTranslatef(0,0,baseht);
   glColor3f(1.0,1.0,0.5);
  
   // glPopMatrix();
    if(hit){
      hitwait++;
      if(hitwait>=100){
         hit=false;
         hitwait=0;
         phi=0;
         // alpha=40;
      }
      else if(hitwait>=50){
         phi++;
         alpha = alpha-3;
         // theta = theta+2;
      }
      else{
         phi--;
         theta = theta+2;
         alpha = alpha+1.5;
      }
   }
   glRotatef(phi,0,1,0);

   gluCylinder(cube1,c1rad,c1rad,c1ht,20,100);
   
   
    glTranslatef(0,0,c1ht);
    glRotatef(theta,0,1,0);
   

   
    glColor3f(1,0,0);
    glutSolidSphere(c1rad,100,100);
    glColor3f(1.0,1.0,0.5);
    gluCylinder(cube2,c2rad,c2rad,c2ht,20,100);
   
   
    
    glTranslatef(0,0,c2ht);
    glRotatef(alpha,0,1,0);
   
    gluCylinder(bulb,bulbr1,bulbr2,bulbht,50,50);
    GLfloat light_position_bulb[] = { 0, 0, 0.0, 1.0 };
   	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 1.0, 1.0, 0, 1.0 };
GLfloat light1_specular[] = { 1.0, 1.0, 0, 1.0 };
GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

   	glLightfv(GL_LIGHT1, GL_POSITION, light_position_bulb);
   	GLfloat light_dir_bulb[] = { 0, 0, 1.0 };
   	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light_dir_bulb);
   	glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0);
   	// glLightfv(GL_LIGHT1,GL_SPOT_CUTOFF,45);
   	glEnable(GL_LIGHT1);
    glPopMatrix();
//	glLoadIdentity();
   
    glTranslatef(x,z,0);
    
    glutSolidSphere(0.5,500,500);
    x+=vball.x*refreshMills/1000;
    z+=vball.z*refreshMills/1000;
    if(abs((int)x)>(int)floorsize)
      vball.x=-vball.x;
    if(abs((int)z)>(int)floorsize)
      vball.z=-vball.z;
    if(abs((int)x) < 1){
      vball.x=0;
      vball.z=0;
      ballwait++;
      if(ballwait>100){
         ballwait=0;
         vball.x = 30;
         x=1;
      }
    }
   


  glFlush ();
  //glutSwapBuffers();
}

void reshape (int w, int h)
{
   if (h == 0) h = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)w / (GLfloat)h;
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   // if (w <= h)
   //    glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
   //       1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   // else
   //    glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
   //       1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
    gluPerspective(60.0f, aspect, 0.05f, 1000.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Heirarchical Modelling");
   init ();

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutSpecialUpFunc(keySpecialUp);
   glutTimerFunc(refreshMills,timer,0);
   glutPostRedisplay();
    

   glutMainLoop();
   return 0;
}

