
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
#include "terrain.h"
#include <utility>
#include <unistd.h>
#include "global.h"
#include <climits>
#include "first.h"
#include <iostream>
using namespace std;

terrain a,b;
vector3d vball;
double lampx=0;double lampz=0;
int refreshMills=10;
int ballwait=0;
int ballhit=false;
bool hit=false;
int hitwait=0;
int beta=0;
int waitvelx=0;
int waitvelz=0;
double x,z,phi,theta,alpha,floorsize,baserad,baseht,c1rad,c2rad,c1ht,c2ht,bulbr1,bulbr2,bulbht,t=0;
double lampang = 0;
GLUquadricObj *base,*btm,*top,*bulb,*cube1,*cube2;
bool jump=false;
int jumpwait=0;
double move;
double ballradius;


void keySpecialUp(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP: phi+=10; break;
    case GLUT_KEY_DOWN: phi-=10; break;
    case GLUT_KEY_LEFT: theta-=10; break;
    case GLUT_KEY_RIGHT: theta+=10; break;
    case GLUT_KEY_F5:  alpha+=10; break;
    case GLUT_KEY_F6: alpha-=10; break;
    case GLUT_KEY_F7: hit=true; move = 180.0*acos((x-lampx)/ sqrt( (x-lampx)*(x-lampx) + (z-lampz)*(z-lampz)))/3.14 ; if(z<lampz){move = 360-move;}; while(lampang>360){lampang-=360;}; move -= lampang; hitwait = -25; break;
    case GLUT_KEY_F8: lampang+=5;break;
    case GLUT_KEY_F9: lampang-=5;break;
    // case GLUT_KEY_F11: lampx+=0.05*cos(lampang);lampz-=0.05*sin(lampang);cout<<sin(lampang)<<"h"<<endl;break;
    case GLUT_KEY_F11: jump=true;break;
  }
}


void init(void) 
{

   baserad=1.3;
   baseht=0.3;
   c1rad=0.45;
   c2rad=0.45;
   c1ht=4;
   c2ht=3;
   bulbr1=0.4;
   bulbr2=2;
   bulbht=1;
   x=3;z=0;
   vball.x=30;
   vball.y=0;
   vball.z=0;
   floorsize=30;
   phi=0;
   theta=30;
   alpha=40;
   beta=0;//not implement yet
   base=gluNewQuadric();
   btm=gluNewQuadric();
   lampang=0;
   lampx=0;
   lampz=0;
   ballradius=1;

  top=gluNewQuadric();
  bulb=gluNewQuadric();
  cube1=gluNewQuadric();
  cube2=gluNewQuadric();
   a.textures="k.bmp";

   b.textures="wall.bmp";
   b.Read();   
   a.Read();
   //Texture *u=&(a.ad);
    GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1};
    GLfloat mat_shininess[] = { 0.0,0.0,0.0,1.0 };
   GLfloat light_position[] = { 100, 100, 100.0, 0.0 };
   glClearColor (1.0, 1.0,1.0, 1.0);
   glShadeModel (GL_SMOOTH);

   // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_specular);
  // glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_shininess);
   	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   	glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0,-40,20,0,0,0,0,0,1);
   GLfloat mat_specular[] = { 0.0, 0.0, 0, 0};
   GLfloat mat_shininess[] = { 10.0 };
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glPushMatrix();
   // glColor3f(0.2,0.8,0.5);
   // glBegin(GL_QUADS);
    
   //  glNormal3f(0,0,1);
   //  glVertex3f(-floorsize,-floorsize,0);
    
   //  glNormal3f(0,0,1);
   //  glVertex3f(-floorsize,floorsize,0);
    
   //  glNormal3f(0,0,1);
   //  glVertex3f(floorsize,floorsize,0);
    
   //  glNormal3f(0,0,1);
   //  glVertex3f(floorsize,-floorsize,0);
   //  glEnd();




    a.Render();
    b.Render2(b.ad);

   if(jump){
    jumpwait++;
    cout<<jumpwait<<endl;
    if(jumpwait>20){
      jump=false;
      jumpwait=0;
    }
    else{
      if(jumpwait>10){
        glTranslatef(0,0,4-0.2*jumpwait);
      }
      else{
        glTranslatef(0,0,0.2*jumpwait);
      }
      lampx+=0.05*cos(lampang*2.0*3.14/360.0);lampz+=0.05*sin(lampang*2.0*3.14/360.0);
    }
   }
   glTranslatef(lampx,lampz,0);
   


   glRotatef(lampang,0,0,1);
   gluCylinder(base,baserad,baserad,baseht,20,100);
   glPushMatrix();
  // glColor3f(0,0,1);
   gluDisk(btm,0,baserad,100,100);
   glTranslatef(0,0,baseht);
   //glColor3f(0.5,0.5,0.5);
   gluDisk(top,0,baserad,100,100);
   glPopMatrix();
   glRotatef(beta,0,0,1);
   glTranslatef(0,0,baseht);
   //glColor3f(1.0,1.0,0.5);
  if(hit){
    hitwait++;
    if(hitwait>=55){
      hit=false;
      hitwait=0;
      phi=0;
      ballwait=0;
    }
    else if(hitwait>=50){
      theta = theta-20;
      alpha = alpha-15;
      phi = phi+10;
    }
    else if(hitwait>0){
      phi = phi-1;
      theta = theta+2;
      alpha = alpha+1.5;
    }
    else{
      lampang = lampang+move/25;
    }
  }

   glRotatef(phi,0,1,0);
   glutSolidSphere(c1rad,100,100);
   gluCylinder(cube1,c1rad,c1rad,c1ht,20,100);
   glTranslatef(0,0,c1ht);
   glRotatef(theta,0,1,0);
   //glColor3f(1,0,0);
   glutSolidSphere(c1rad,100,100);
   //glColor3f(1.0,1.0,0.5);
   gluCylinder(cube2,c2rad,c2rad,c2ht,20,100);
   glTranslatef(0,0,c2ht);
   glRotatef(alpha,0,1,0);
   glutSolidSphere(bulbr1,100,100);
   gluCylinder(bulb,bulbr1,bulbr2,bulbht,50,50);
   GLfloat light_position_bulb[] = { 0, 0,1.0, 1.0 };
   GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat light1_diffuse[] = { 1.0, 1.0, 0, 1.0 };
   GLfloat light1_specular[] = { 1.0, 1.0, 0, 1.0 };
   
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
   
   glLightfv(GL_LIGHT1, GL_POSITION, light_position_bulb);
   GLfloat light_dir_bulb[] = { 0, 0, 1.0 };
   glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light_dir_bulb);
   glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0);
   glEnable(GL_LIGHT1);
    // glBegin(GL_QUADS);
    
    // glNormal3f(0,0,-1);
    // glVertex3f(-floorsize,-floorsize,10);
    
    // glNormal3f(0,0,-1);
    // glVertex3f(-floorsize,floorsize,10);
    
    // glNormal3f(0,0,-1);
    // glVertex3f(floorsize,floorsize,10);
    
    // glNormal3f(0,0,-1);
    // glVertex3f(floorsize,-floorsize,10);
    // glEnd();

   glPopMatrix();




















   glTranslatef(x,z,ballradius);
   glutSolidSphere(ballradius,500,500);
   x+=vball.x*refreshMills/1000;
   z+=vball.z*refreshMills/1000;
   if(abs((int)x)>(int)(floorsize-3)){
    vball.x=-vball.x;
    x+=vball.x*refreshMills/1000;
   }
   if(abs((int)z)>(int)(floorsize-3)){
    vball.z=-vball.z;
     z+=vball.z*refreshMills/1000;
   }

   if(abs((int)(x-lampx)) < 3 && abs((int)(z-lampz))<3 && ballhit==false){
    ballhit=true;
    waitvelx=vball.x;
    waitvelz=vball.z;
    vball.x=0;
    vball.z=0;
   }
   if(hit){
    ballwait++;
    if(ballwait>=74){
      ballwait=0;
      vball.x = -waitvelx;
      vball.z = -waitvelz;
      x+=vball.x*refreshMills/500;
      z+=vball.z*refreshMills/500;
      ballhit=false;
    }
   }
  glFlush ();
  glutSwapBuffers();
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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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

