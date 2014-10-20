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