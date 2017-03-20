using namespace std;
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "Mob.h"
#include "Bullet.h"

GLUquadricObj *quadratic;

Bullet::Bullet() {}

Bullet::~Bullet() { gluDeleteQuadric(quadratic); }

bool Bullet::init()
{
  /*glPushMatrix();
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, transforms);
  glPopMatrix();*/
  quadratic=gluNewQuadric();
  gluQuadricNormals(quadratic, GLU_SMOOTH);
  //gluQuadricTexture(quadratic, GL_TRUE);
  loadMatrix();
  glLoadIdentity();
  saveMatrix();
  velocity.z = -10.0;//20.0*((float) random() / RAND_MAX)-1.0;
  return true;
}

void Bullet::draw()
{
  glPushMatrix();
  //loadMatrix();
  glTranslatef(pos.x(), pos.y(), pos.z());
  gluSphere(quadratic,0.2f,16,16);
  glPopMatrix();
}

void Bullet::update(float dt)
{
  loadMatrix();
  translate(0.0, 0.0, dt*velocity.z);
  saveMatrix();
}
/*void Bullet::rotate(GLfloat angle, GLfloat dx, GLfloat dy, GLfloat dz)
{
  loadMatrix();
  glRotatef(angle, dx, dy, dz);
  saveMatrix();
}*/

/*void Bullet::translate(GLfloat dp, GLfloat daz, GLfloat dh)
{
  loadMatrix();
  glTranslatef(dx, dy, dz);
  saveMatrix();
}*/
/*
void Cube::scale(GLfloat sx, GLfloat sy, GLfloat sz)
{
  loadMatrix();
  glScalef(sx, sy, sz);
  saveMatrix();
}*/
