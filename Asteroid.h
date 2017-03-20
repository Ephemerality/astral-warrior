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

#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>
#include <cstdlib>
#include "Mob.h"

class Asteroid : public Mob
{
  private:
    
  public:
    Asteroid() : Mob() { init(); }
    Asteroid(GLfloat np, GLfloat naz, GLfloat nh) : Mob(np, naz, nh) { init(); }
    Asteroid( CylVector p) : Mob(p) { init(); }
    virtual ~Asteroid();

    bool init();
    void draw();
};

#endif