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

#ifndef GAME_H
#define GAME_H

/* keys.h is included here, even though it uses GLUT.
 * I couldn't figure out a better way to handle key detection here without it,
 * so for what it's being used for, it should be fine. 
 */
#include "keys.h"
#include "Mob.h"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Particles.h"
#include "Camera.h"

#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <sstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <vector>
#include <string>

#define DEBUG

#define NUM_STARS 800

#define NUM_TEXTURES 6

#define TEXTURE_ASTEROID 0
#define TEXTURE_RED 1
#define TEXTURE_PLANET 2
#define TEXTURE_METAL 3
#define TEXTURE_TITLE 4
#define TEXTURE_GAMEOVER 5

//Our texture-loading callback
typedef void (*texture_func)(GLuint (&arr)[NUM_TEXTURES]);
typedef void (*text_func)(const char*);

class FPSCounter
{
  public:
    FPSCounter() { frame = 0; timebase = 0.0; }
    
    int fps;
    float timebase;
    int frame;
};

class Game
{
private:
  Camera camera;
  texture_func textureFunction;
  text_func textFunction;
  GLfloat stars[NUM_STARS*3];
  GLuint textures[NUM_TEXTURES];
  int p1_score;
  int p1_lives;
  int p1_dtime;
  GLfloat textPos; //for the title screen and game over
  GLfloat last_update;
  FPSCounter fps;
  float enemy_timer;
  float new_enemy_time;
  
  /* Current state options (will probably change to a set of binary flags later):
   * 0 = Title screen fade-in
   * 1 = Title screen stationary
   * 2 = Standard game running state
   * 3 = Player dead, timer delayed respawn
   * 4 = Game over screen fade-in
   * 5 = Game over screen stationary
   */
  unsigned char gameStatus;
  
  /* Main list of elements to be drawn.
   * 0 = Player mobs - Mainly the ship - MUST *ALWAYS* contain at least 1 ship at index 0!!!!
   * 1 = Player projectiles
   * 2 = Enemy mobs
   * 3 = Enemy projectiles
   * 4 = Misc (Planets, explosions)
   */
  std::vector< std::vector<Mob*> > gameElements;

public:
  Game();
  virtual ~Game();
  
  bool init();
  void setTextureFunc(texture_func func) { textureFunction = func; }
  void setTextFunc(text_func func) { textFunction = func; }
  void print(string, GLfloat, GLfloat, GLfloat);
  void updateDrawStars(GLfloat);
  void display(float);
  void updateByKeys(float, float);
  void handleKeys(int);
  void drawTitleScreen(GLfloat dt, bool text);
  void drawGameOver(GLfloat dt, bool text);
  void spawnProjectile(CylVector, int);
  void spawnEnemy(float);
  void checkCollisions(float);
  void startGame();
  void showTitle();
  string IntToString(int);
};

#endif
