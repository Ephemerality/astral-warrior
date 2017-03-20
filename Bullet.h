/* This file is part of Astral Warrior.
 *
 * Astral Warrior is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Astral Warrior is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Astral Warrior.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BULLET_H
#define BULLET_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include "Mob.h"

#define BULLET_SIZE 0.2
#define BULLET_SPEED -15.0

class Bullet : public Mob
{
  private:
    GLUquadricObj *quadric;
    GLfloat bsize;
    
  public:
    Bullet() : Mob() { init(BULLET_SIZE); }
    Bullet(GLfloat np, GLfloat naz, GLfloat nh) : Mob(np, naz, nh) { init(BULLET_SIZE); }
    Bullet(GLfloat np, GLfloat naz, GLfloat nh, GLfloat radius) : Mob(np, naz, nh) { init(radius); }
    Bullet(CylVector p) : Mob(p) { init(BULLET_SIZE); }
    virtual ~Bullet();

    bool init(GLfloat);
    void draw();
};

#endif