/*
 * terrain.cpp
 *
 *  Created on: 7 Aug 2013
 *      Author: shivam
 */
#include "terrain.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
 #include <math.h>
#include <string>
#include "global.h"
  int SCALE=1,HEIGHTSCALE=1;
#include <vector>
typedef float f;
float frustum[6][4];						
//double floorsize;
		//!< This field stores the information of the frustum used for culling
//! Extract the frustum
/*!
	This function extracts the equation of frustum in matrix format using projection matrix and modelview matrix
*/
void ExtractFrustum()
{
   float   proj[16];
   float   modl[16];
   float   clip[16];
   float   t;

   /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Combine the two matrices (multiply projection by modelview) */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

   /* Extract the numbers for the RIGHT plane */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Normalize the result */
   t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Extract the numbers for the LEFT plane */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Normalize the result */
   t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Extract the BOTTOM plane */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Normalize the result */
   t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* Extract the TOP plane */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Normalize the result */
   t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* Extract the FAR plane */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Normalize the result */
   t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* Extract the NEAR plane */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Normalize the result */
   t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;
}
//! Tells whether the point is in frustum or not
/*!
	this function checks with all the six planes of the frustum whether point lies inside the frustum or not
	/param x This has value of the x co-ordinate of the point
	/param Y This has value of the y co-ordinate of the point
	/param z This has value of the z co-ordinate of the point
	
	
*/
bool PointInFrustum( float x, float y, float z )
{
   int p;

   for( p = 0; p < 6; p++ )
      if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2] * z + frustum[p][3] <= -60 )
         return false;
   return true;
}

using namespace std;
GLuint terr;																			//!< Stores the display list id of the terrain

//! Reads the heightmap
/*!
		This function reads the texture images specified in the terrain object and reads the heightmap. It fills the texture array with textures 
*/
void terrain :: Read(void){
		 	
	 	 			Texture a(textures.c_str());
	 	 			a.Terrainid=a.LoadImage();
	 	 			ids=a.Terrainid;
	 	 			ad=a;
	 	 		
	 	 	FILE * picfile;
	 		picfile = fopen(textures.c_str(), "rb");
	 		if (picfile == NULL)
	 		{
	 			return ;
	 		}
	 		GLubyte * exp=(GLubyte*)malloc(54);
	 		fread(exp,1,54,picfile);
	 		terrainwidth=exp[18]+exp[19]*256.0+exp[20]*65536.0;
	 		terrainheight=exp[22]+exp[23]*256.0+exp[24]*65536.0;
	 		normals=new normal*[terrainwidth];
	 		free(exp);
	 		data = (GLubyte*)malloc(terrainwidth * terrainheight * 3);
	 		fread(data,1, terrainwidth * terrainheight*3, picfile);
	 		fclose(picfile);
	 		
}
void terrain :: Render(){
	
Render1(ad);

}

//! renders the terrain
/*!
	This function renders the terrain on the heightmap and applying the textures specified on the scaled heightmap.
	/param Texture a[]  This stores the textures in the an array which are chosen to be applied accordingly 
*/

void terrain :: Render1(Texture a)
{
	//ExtractFrustum();

	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, (ad).Terrainid);
		// int w=(ad).terrainwidth;
		// int h=(ad).terrainheight;
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		// for(int j=0;j+1<terrainwidth-1;j++)
		// 	{	int i=0;

		// 		while(i+1<terrainheight-1)
		// 		{
							

		// 				if(PointInFrustum(i*SCALE,getHeight(i,j),j*SCALE)){
								
		// 					glBegin(GL_TRIANGLE_STRIP);
  //                           glTexCoord2f(f(i)/terrainwidth,f(j)/terrainheight);
  //                           //glNormal3f(normals[i][j].x,normals[i][j].y,normals[i][j].z);
  //                           glVertex3f(i*SCALE,data[(j)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE,j*SCALE);

  //                           glTexCoord2f(f(i+1.0)/terrainwidth,f(j)/terrainheight);
  //                           //glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
  //                           glVertex3f((i+1)*SCALE,data[(j)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE,j*SCALE);

  //                           //glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
  //                           glTexCoord2f(f(i)/terrainwidth,f(j+1)/terrainheight);
  //                           glVertex3f(i*SCALE,data[(j+1)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE,(j+1)*SCALE);

  //                           //glNormal3f(normals[i+1][j+1].x,normals[i+1][j+1].y,normals[i+1][j+1].z);
  //                           glTexCoord2f(f(i+1)/terrainwidth,f(j+1)/terrainheight);
  //                           glVertex3f((i+1)*SCALE,data[(j+1)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE,(j+1)*SCALE);

  //                    glEnd();}
  //                           i++;
							
		// 		}
		// 	}


    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glNormal3f(0,0,1);
    glVertex3f(-floorsize,-floorsize,0);
    glTexCoord2f(0,1);
    glNormal3f(0,0,1);
    glVertex3f(-floorsize,floorsize,0);
    glTexCoord2f(1,1);
    glNormal3f(0,0,1);
    glVertex3f(floorsize,floorsize,0);
    glTexCoord2f(1,0);
    glNormal3f(0,0,1);
    glVertex3f(floorsize,-floorsize,0);
    glEnd();

	glDisable(GL_TEXTURE_2D);
	//glFlush();
}


void terrain :: Render2(Texture a)
{
  //ExtractFrustum();

  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, (a).Terrainid);
    // int w=(ad).terrainwidth;
    // int h=(ad).terrainheight;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // for(int j=0;j+1<terrainwidth-1;j++)
    //  { int i=0;

    //    while(i+1<terrainheight-1)
    //    {
              

    //        if(PointInFrustum(i*SCALE,getHeight(i,j),j*SCALE)){
                
    //          glBegin(GL_TRIANGLE_STRIP);
  //                           glTexCoord2f(f(i)/terrainwidth,f(j)/terrainheight);
  //                           //glNormal3f(normals[i][j].x,normals[i][j].y,normals[i][j].z);
  //                           glVertex3f(i*SCALE,data[(j)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE,j*SCALE);

  //                           glTexCoord2f(f(i+1.0)/terrainwidth,f(j)/terrainheight);
  //                           //glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
  //                           glVertex3f((i+1)*SCALE,data[(j)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE,j*SCALE);

  //                           //glNormal3f(normals[i+1][j].x,normals[i+1][j].y,normals[i+1][j].z);
  //                           glTexCoord2f(f(i)/terrainwidth,f(j+1)/terrainheight);
  //                           glVertex3f(i*SCALE,data[(j+1)*terrainwidth*3+i*3+1]*SCALE*HEIGHTSCALE,(j+1)*SCALE);

  //                           //glNormal3f(normals[i+1][j+1].x,normals[i+1][j+1].y,normals[i+1][j+1].z);
  //                           glTexCoord2f(f(i+1)/terrainwidth,f(j+1)/terrainheight);
  //                           glVertex3f((i+1)*SCALE,data[(j+1)*terrainwidth*3+(i+1)*3+1]*SCALE*HEIGHTSCALE,(j+1)*SCALE);

  //                    glEnd();}
  //                           i++;
              
    //    }
    //  }


    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glNormal3f(1,0,0);
    glVertex3f(-floorsize,-floorsize,0);
    glTexCoord2f(0,1);
    glNormal3f(1,0,0);
    glVertex3f(-floorsize,-floorsize,floorsize);
    glTexCoord2f(1,1);
    glNormal3f(1,0,0);
    glVertex3f(-floorsize,floorsize,floorsize);
    glTexCoord2f(1,0);
    glNormal3f(1,0,0);
    glVertex3f(-floorsize,floorsize,0);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glNormal3f(-1,0,0);
    glVertex3f(floorsize,-floorsize,0);
    glTexCoord2f(0,1);
    glNormal3f(-1,0,0);
    glVertex3f(floorsize,-floorsize,floorsize);
    glTexCoord2f(1,1);
    glNormal3f(-1,0,0);
    glVertex3f(floorsize,floorsize,floorsize);
    glTexCoord2f(1,0);
    glNormal3f(-1,0,0);
    glVertex3f(floorsize,floorsize,0);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glNormal3f(0,-1,0);
    glVertex3f(-floorsize,floorsize,0);
    glTexCoord2f(0,1);
    glNormal3f(0,-1,0);
    glVertex3f(-floorsize,floorsize,floorsize);
    glTexCoord2f(1,1);
    glNormal3f(0,-1,0);
    glVertex3f(floorsize,floorsize,floorsize);
    glTexCoord2f(1,0);
    glNormal3f(0,-1,0);
    glVertex3f(floorsize,floorsize,0);
    glEnd();


  glDisable(GL_TEXTURE_2D);
  //glFlush();
}

//! returns the height at a point in heightmap
/*!
	this function return the height at a point in terrain using data field of the terrain object
	/param int i x value of the point whose height is to be calculated
	/param int j z value of the point whose height is to be calculated
*/
GLfloat terrain :: getHeight(int i,int j){
	return (i<=0 or i>=terrainwidth-1 or j>=terrainheight-1 or j<=0)?data[abs(j-1)*terrainwidth*3+(i)*3+1]*SCALE*HEIGHTSCALE:data[(j)*terrainwidth*3+(i)*3+1]*SCALE*HEIGHTSCALE;
}




terrain :: terrain(char * a)
{
	heightmap=a;
}
terrain::terrain(void)
{

}