using namespace std;
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "Mob.h"
#include "Asteroid.h"

Asteroid::~Asteroid() { }

bool Asteroid::init()
{
  loadMatrix();
  glLoadIdentity();
  saveMatrix();
  velocity.z = 10.0;//20.0*((float) random() / RAND_MAX)-1.0;
  velocity.y = 2.0;
  pos.h = -40;
  pos.p = 15.0;
  return true;
}

void Asteroid::draw()
{
  glPushMatrix();
  //loadMatrix();
  glTranslatef(pos.x(), pos.y(), pos.z());
  //glEnable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  //glDisable(GL_DEPTH_TEST);
  glBindTexture(GL_TEXTURE_2D, texture);
  glColor4ub(255,255,255,255);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f,-1.5f, 0.0f);//, 40.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.5f,-1.5f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.5f, 1.5f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 0.0f);
  glEnd();
 // glDisable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  //glEnable(GL_DEPTH_TEST);
  glPopMatrix();
}
