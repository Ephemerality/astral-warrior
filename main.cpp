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

using namespace std;
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>
#include <GL/glut.h>
#include <cstdlib>

#include "Game.h"
#include "keys.h"
#include "glpng.h" //Library for loading PNG files

Game game;

void myTimer(int v)
{
  glutPostRedisplay();
  glutTimerFunc(1000/v, myTimer, v);
}

/* Keyboard callback, called from the keys.cpp file.
 * Combines both normal and special keyboard functions.
 */
void keyboard (int key, bool keydown)
{
  game.handleKeys(key);
}

void reshapeFunc(int w, int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(h<1) h=1;
  gluPerspective(90.0, (double)w/(double)h, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
}

void displayFunc(){
  /* Also from the textbook */
  float curr_update = glutGet(GLUT_ELAPSED_TIME);
  
  game.display(curr_update);
  glutSwapBuffers();
}

/* Texture callback, called from within the game object.
 * This is used here so that when the game is ported to another platform,
 * the preferred method can be used to load the textures.
 * All that matters is that the texture IDs are bound to the array.
 * Pretty nifty, eh?
 */
void loadTextures(GLuint (&txt)[NUM_TEXTURES])
{
  //Using libglpng and example code from documentation
  const char* boo[] = {"images/AsteroidA.png", "images/Bullet.png", "images/Earth.png", "images/Metal.png", "images/Astral.png", "images/GameOver.png"};
  for(int i = 0; i < NUM_TEXTURES; i++)
  {
    GLuint result = png_texture_load(boo[i], NULL, NULL, txt[i]);
    if (result < 128) {
      txt[i] = result;
      cout << "Loaded " << boo[i] << " " << result << endl;
    }
    else {
      cout << "Can't load " << boo[i] << endl;
      exit(1);
    }
  }
}

/* Another callback. Since this method of text display uses GLUT,
 * it will be platform dependent. This allows the text to be displayed
 * in whatever method is available.
 * Raster position is set before this function is called.
 */
void displayText(const char* text)
{
  int len = (int)strlen(text);
  for (int i = 0; i < len; i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(800,800);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutCreateWindow("Astral Warrior");
  glutReshapeFunc(reshapeFunc);
  glutDisplayFunc(displayFunc);
  InitKeyboard();
  SetKeyboardFunc(keyboard);

  game.setTextureFunc(loadTextures);
  game.setTextFunc(displayText);
  
  if(game.init()) printf("Game load success.\n");
  else
  {
    printf("Game load failure.\n");
    return 1;
  }
  /* Limit the game to ~100fps maximum.
   * Timer code courtesy of the Angel Textbook.
   */
  int n = 100;
  glutTimerFunc(200, myTimer, n);
  glutMainLoop();
  return EXIT_SUCCESS;
}

