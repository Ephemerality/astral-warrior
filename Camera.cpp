/* Camera (viewer) class, based on spherical coordinates.
 * Here, we're really only moving the camera backwards,
 * but there's functionality for movement should the case arise.
 */

using namespace std;
#include "Camera.h"

#define PI 3.14159265358979

Camera::Camera()
{
  reset();
}

Camera::~Camera() {}

void Camera::draw()
{
  gluLookAt(x,y,z,0.0,0.0,0.0,0.0,1.0,0.0);
}

void Camera::reset()
{
  r = 50.0f;
  az = 0.0f;
  inc = PI/2;
  updateXYZ();
  print();
}

void Camera::translate(float dr, float daz, float dinc)
{
  r += dr;
  az = fmodf(az + daz, PI*2);
  inc = fmodf(inc + dinc, PI*2);
  updateXYZ();
  print();
}

void Camera::updateXYZ()
{
  x = r*sin(az)*sin(inc);
  y = r*cos(inc);
  z = r*cos(az)*sin(inc);
}

void Camera::print()
{
  #ifdef DEBUG
  printf("New camera:\nx: %f\ny: %f\nz: %f\nr: %f\ninc: %f\naz: %f\n", x, y, z, r, inc, az);
  #endif
}