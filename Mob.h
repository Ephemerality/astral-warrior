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

#ifndef MOB_H
#define MOB_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath>

/* Custom vector class for constraining a mob to the cylinder. */
class CylVector
{
  public:
    CylVector() { p = 0.0; az = 0.0; h = 0.0;}
    CylVector(GLfloat np, GLfloat naz, GLfloat nh) { p = np; az = naz; h = nh; }
    virtual ~CylVector() {}

    GLfloat p;
    GLfloat az;
    GLfloat h;

    GLfloat x() const { return p*cos(az); }
    GLfloat y() const { return p*sin(az); }
    GLfloat z() const { return h; }

    //void print() const { printf("CurrPos: %f, %f, %f\n", p, az, h); }
    void print() {}
};

/* Same as above, but for a sphere (for the particle system).
 * Could probably make a vector base class and have all these types
 * as inherited classes? Neat idea, will have to try that.
 */
class SphereVector
{
  public:
    SphereVector() { r = 0.0; az = 0.0; inc = 0.0; }
    SphereVector(GLfloat nr, GLfloat naz, GLfloat ninc) { r = nr; az = naz; inc = ninc; }
    virtual ~SphereVector() {}

    GLfloat r;
    GLfloat az;
    GLfloat inc;
    GLfloat x() const { return r*sin(az)*sin(inc); }
    GLfloat y() const { return r*cos(inc); }
    GLfloat z() const { return r*cos(az)*sin(inc); }

    //void print() const { printf("CurrPos: %f, %f, %f\n", p, az, h); }
    void print() {}
};

/* Simple 3-var vector class. Used for more than just coordinates.
 * Could probably be fleshed out into a full-fledged utility class,
 * but I bet one already exists...
 */
class Vector3
{
  public:
    GLfloat x, y, z;
    Vector3() { x = 0.0; y = 0.0; z = 0.0; }
    Vector3(GLfloat nx, GLfloat ny, GLfloat nz) { x = nx; y = ny; z = nz; }
    virtual ~Vector3() {}
    
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
};

class Mob
{
protected:
  void saveMatrix();
  void loadMatrix();
  GLfloat trans[16]; //translation matrix. Do I even use this?? I'll have to check...
  GLfloat twist; //rotation along the Z axis

public:
  Mob();
  Mob(GLfloat np, GLfloat naz, GLfloat nh);
  Mob(CylVector p);
  virtual ~Mob() {}

  bool nodel; //Do not delete if the mob is outside the our game's normal space
  bool delnow; //Delete on next update!
  bool nodraw; //Used for temporary skipping of drawing on next update (if the mob supports it)
  int stat1; //Used so I can get ship health for string display... Could really use some polymorphism help...
  CylVector pos;
  Vector3 velocity;
  GLuint texture;
  virtual void draw() = 0;
  virtual void update(float);
  virtual bool init();
  virtual void reset() {}
  virtual void rotate(GLfloat, GLfloat, GLfloat, GLfloat);
  virtual void scale(GLfloat, GLfloat, GLfloat) {}
  virtual void translate(GLfloat, GLfloat, GLfloat);
  virtual bool canFire(float) { return false; } //General-use function for anything based on a time delay for the mob
  virtual bool damage(int) { return false; } //Used for mobs than have health and can be hurt
};

#endif
