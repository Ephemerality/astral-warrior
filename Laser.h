#ifndef BULLET_H
#define BULLET_H

#include <cmath>
#include <cstdlib>
#include "Mob.h"

class Bullet : public Mob
{
  private:
  public:
    Bullet();
    Bullet(CylVector p) { pos.p = p.p; pos.az = p.az; pos.h = p.h; }
    virtual ~Bullet();

    bool init();
    void draw();
    void update(float);
    /*void rotate(GLfloat, GLfloat, GLfloat, GLfloat);*/
    //void translate(GLfloat, GLfloat, GLfloat);
    /*void scale(GLfloat, GLfloat, GLfloat);*/
};

#endif