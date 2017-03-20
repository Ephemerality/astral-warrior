using namespace std;
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#include "Cube.h"
#include "Mob.h"

static GLfloat vertices[] = {-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE,
	CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE,
	CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE,
	-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE,
	-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 
	CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE,
	CUBE_SIZE,CUBE_SIZE,CUBE_SIZE,
	-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE};

static GLfloat colors[] = {0.0,0.0,0.0, 1.0,0.0,0.0,
	1.0,1.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0, 
	1.0,0.0,1.0, 1.0,1.0,1.0, 0.0,1.0,1.0};

static GLubyte cubeIndices[]={0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4};

bool Cube::init()
{
  glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_COLOR_ARRAY); 
    glEnableClientState(GL_VERTEX_ARRAY);
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    
  velocity.z = -5.0;
  return true;
}

void Cube::draw()
{
  loadMatrix();
  glTranslatef(pos.x(), pos.y(), pos.z());
  /* Axes tied to the cube */
  glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 3.0);
  glEnd();
  glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 3.0, 0.0);
  glEnd();
  glBegin(GL_LINES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(3.0, 0.0, 0.0);
  glEnd();
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors); 
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
  glPopMatrix();
}

void Cube::update(float dt)
{
  translate(0.0, 0.0, dt*velocity.z);
  rotate(45.0, 1.0, 1.0, 1.0);
}
