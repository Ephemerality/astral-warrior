using namespace std;
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "Mob.h"
#include "Particles.h"

ParticleSystem::~ParticleSystem() { particles.clear(); }

bool ParticleSystem::init()
{
  velocity_factor = 1.0;
  velocity_base = 0.0;
  
  Particle* new_particle;
  for (unsigned int k = 0; k < system_size; k++) {
    new_particle = new Particle();
    new_particle->active = true;
    new_particle->life = 1.0;
    new_particle->fade = 0.03;
    new_particle->color.x = new_particle->color.y = new_particle->color.z = 1.0;
    particles.push_back(new_particle);
  }
  return true;
}

void ParticleSystem::setVelocity(Vector3 v)
{
  for (unsigned int k = 0; k < system_size; k++) {
    particles[k]->delta.x = v.x;
    particles[k]->delta.y = v.y;
    particles[k]->delta.z = v.z;
  }
}

void ParticleSystem::setFade(GLfloat fade)
{
  for (unsigned int k = 0; k < system_size; k++) {
    particles[k]->fade = fade;
  }
}

void ParticleSystem::randomize(bool randFade)
{
  for (unsigned int k = 0; k < system_size; k++) {
    particles[k]->delta.x = velocity_base + velocity_factor*((float)rand())/((float)RAND_MAX);
    particles[k]->loc.az = M_PI*2.0f*((float)rand())/((float)RAND_MAX);
    particles[k]->loc.inc = M_PI*2.0f*((float)rand())/((float)RAND_MAX);
    if(randFade) particles[k]->fade = 0.003 + 0.0065 * (particles[k]->delta.x/(velocity_base + velocity_factor));
    //printf("%f\n", particles[k]->fade);
  }
}

void ParticleSystem::draw()
{
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  
  glTranslatef(pos.x(), pos.y(), pos.z());
  glBegin(GL_POINTS);
  for (unsigned int k = 0; k < system_size; k ++) {
    glColor4f(particles[k]->color.x,particles[k]->color.y, particles[k]->color.z, particles[k]->life);
    glVertex3f(particles[k]->loc.x(), particles[k]->loc.y(), particles[k]->loc.z());
  }
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void ParticleSystem::update(GLfloat dt)
{
  bool anytrue = false;
  for (unsigned int k = 0; k < system_size; k ++) {
    //Update positions/lifetime
    particles[k]->loc.r += particles[k]->delta.x * dt;
    //particles[k].loc.az += particles[k].delta.y * dt;
    //particles[k].loc.inc += particles[k].delta.z * dt;
    particles[k]->life -= particles[k]->fade;
    if(particles[k]->life <= 0.0) particles[k]->active = false;
    else anytrue = true;
  }
  if(!anytrue) delnow = true;
}