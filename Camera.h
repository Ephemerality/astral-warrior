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

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath>

class Camera
{
  private:
    float r;
    float az;
    float inc;
    float x;
    float y;
    float z;
    void updateXYZ();

  public:
    Camera();
    virtual ~Camera();

    void draw();
    void print();
    void reset();
    void translate(float, float, float);
};

#endif