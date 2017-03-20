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

#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <cstdlib>
#include "Mob.h"
#include <vector>

/* Based on particle systems outlined in Nehe Tutorial 19 and textbook chapter 11 */
class Particle
{
  public:
    Particle() {}
    virtual ~Particle() {}
    bool active;
    float life; //0.0-1.0 - alpha value for particle (requires GL_BLEND)
    float fade; //Amount the life will go down each update
    Vector3 color; //rgb color
    SphereVector loc;
    Vector3 delta; //change in x/y/z (or r/az/inc)
};

class ParticleSystem : public Mob
{
  private:
    vector<Particle*> particles;
    unsigned int system_size;
    
  public:
    ParticleSystem(unsigned int z) : Mob(), system_size(z) { init(); }
    ParticleSystem(CylVector p, unsigned int z) : Mob(p), system_size(z) { init(); }
    virtual ~ParticleSystem();

    bool init();
    void draw();
    void update(GLfloat);
    void setVelocity(Vector3 v);
    void setFade(GLfloat);
    void randomize(bool);
    GLfloat velocity_factor;
    GLfloat velocity_base;
    //void translate(GLfloat, GLfloat, GLfloat);
    /*void scale(GLfloat, GLfloat, GLfloat);*/
};

#endif