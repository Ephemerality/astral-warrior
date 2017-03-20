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

#ifndef SHIP_H
#define SHIP_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>

#include "Mob.h"

typedef struct _point2 {
	double x,y;
} Point2;

typedef struct _point3 {
	double x,y,z;
} Point3;
// "Object" data structure
typedef struct _obj {
	Point3	*vertices;
	long	*v_idx;
	Point3	*normals;
	long	*n_idx;
	Point2	*uvs;
	int	num_faces;
} Obj;

class Ship : public Mob
{
  private:
    float last_fire;
    int fire_rate;
    Obj sph02;
    Obj box02;
    Obj dup00;
    Obj cyl03;
    Obj dup01;
    
  public:
    Ship() : Mob() { init(); }
    Ship(GLfloat np, GLfloat naz, GLfloat nh) : Mob(np, naz, nh) { init(); }
    Ship(CylVector p) : Mob(p) { init(); }
    virtual ~Ship() {}

    bool init();
    void reset();
    void draw();
    void update(float);
    void print();
    bool canFire(float);
    bool damage(int);
};

#endif
