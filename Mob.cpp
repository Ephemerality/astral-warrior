/* The mob is a base class for essentially any object that will exist within the cylinder.
 * The class itself is pretty simple. Explanation of the variables is in the header.
 */

using namespace std;
#include "Mob.h"

void Mob::saveMatrix()
{
  glGetFloatv(GL_MODELVIEW_MATRIX, trans);
  glPopMatrix();
}

void Mob::loadMatrix()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadMatrixf(trans);
}

Mob::Mob()
{
  init();
}

Mob::Mob(GLfloat np, GLfloat naz, GLfloat nh)
{
  pos.p = np;
  pos.az = naz;
  pos.h = nh;
  init();
}

Mob::Mob(CylVector p)
{
  pos.p = p.p;
  pos.az = p.az;
  pos.h = p.h;
  init();
}

bool Mob::init()
{
  texture = 0;
  nodel = false;
  delnow = false;
  nodraw = false;
  return false;
}

void Mob::rotate(GLfloat angle, GLfloat dx, GLfloat dy, GLfloat dz)
{
  loadMatrix();
  glRotatef(angle, dx, dy, dz);
  saveMatrix();
}

void Mob::translate(GLfloat dp, GLfloat daz, GLfloat dh)
{
  pos.p += dp;
  pos.az = fmodf(pos.az + daz, M_PI*2);
  pos.h += dh;
  pos.print();
}

void Mob::update(float dt)
{
  loadMatrix();
  translate(dt*velocity.x, dt*velocity.y, dt*velocity.z);
  saveMatrix();
}
