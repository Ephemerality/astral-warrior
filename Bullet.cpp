using namespace std;
#include "Bullet.h"

Bullet::~Bullet() { gluDeleteQuadric(quadric); }

bool Bullet::init(GLfloat radius)
{
  quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  gluQuadricTexture(quadric, GL_TRUE);
  loadMatrix();
  glLoadIdentity();
  saveMatrix();
  bsize = radius;
  velocity.z = BULLET_SPEED;
  return true;
}

void Bullet::draw()
{
  glPushMatrix();
  glTranslatef(pos.x(), pos.y(), pos.z());
  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, texture);
  glColor4ub(255, 255, 255, 255);
  /* If the size is BULLET_SIZE, it's a bullet... otherwise it's a planet...
    This should confuse anyone trying to read the code to find the planet code!
    */
  if(bsize == BULLET_SIZE)
    gluSphere(quadric,BULLET_SIZE,16,16);
  else {
    glRotatef(45, 0.0, 0.0, 1.0);
    glMultMatrixf(trans);
    rotate(-1, 0.0, 1.0, 0.0);
    gluSphere(quadric,bsize,48,48); //Planets have a slightly higher quality of sphere
  }
  glEnable(GL_BLEND);
  glPopMatrix();
}