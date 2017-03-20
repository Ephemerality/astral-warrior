using namespace std;

#include "Game.h"

/* Define our light variables.
 * These are static and const, so they are not available outside this class
 * and cannot be modified at runtime.
 */
static const GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
static const GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; // infinite light position
static const GLfloat light_emissive[] = {0.3, 0.2, 0.2, 0.0};
static const GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
  
Game::Game()
{
  textureFunction = 0;
  gameStatus = 0;
  textPos = -70;
  enemy_timer = 0.0;
  new_enemy_time = 1000;
  vector<Mob*> v1;
  vector<Mob*> v2;
  vector<Mob*> v3;
  vector<Mob*> v4;
  vector<Mob*> v5;
  gameElements.push_back(v1);
  gameElements.push_back(v2);
  gameElements.push_back(v3);
  gameElements.push_back(v4);
  gameElements.push_back(v5);
}

Game::~Game()
{
  gameElements.clear();
}

bool Game::init()
{
  if(!textureFunction)
  {
    printf("Texture loader not set.\n");
    return false;
  }
  
  //Generate our textures then use the callback to load the textures
  glGenTextures(NUM_TEXTURES, &textures[0]);
  textureFunction(textures);
  
  //Setup the star field using random spherical coordinates, removing the center tube:
  for (int i = 0; i < NUM_STARS*3; i+=3) {
    //float r = 25 + 100*((float)rand())/((float)RAND_MAX);
    float r = 150*((float)rand())/((float)RAND_MAX);
    float az = M_PI*2.0f*((float)rand())/((float)RAND_MAX);
    float inc = M_PI*2.0f*((float)rand())/((float)RAND_MAX);
    stars[i] =  r*sin(az)*sin(inc);
    stars[i+1] = r*cos(inc);
    stars[i+2] = r*cos(az)*sin(inc);
    if(stars[i] <= 18 && stars[i] >= -18 && stars[i+1] <= 18 && stars[i+1] >= -18)
      i-=3;
  }
  
  /* Create the ship for player 1.
   * The game will not function correctly at all if this is
   * not in the vector at all times.
   */
  Mob* ship = new Ship();
  ship->texture = textures[TEXTURE_METAL];
  gameElements.at(0).push_back(ship);
  
  /*Mob* bull = new Bullet(ship->pos);
  bull->velocity.z = 0.0;
  bull->pos.p -= 2.8;
  gameElements.at(0).push_back(bull);*/
  
  Mob* planet = new Bullet(0.0, 0.0, -250.0, 20.0);
  planet->velocity.z = 0.0;
  planet->nodel = true;
  planet->texture = textures[TEXTURE_PLANET];
  gameElements.at(4).push_back(planet);
  
  /*** Ensure the flags we need are set: ***/
  
  glClearColor(0.0,0.0,0.0,0.0);
  glClearDepth(1.0f);
  
  //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  /* one_minus_src_alpha is supposedly better for transparency like the title screen.
   * When drawing certain other things, will swap blending funcs.
   * 
   * EDIT: While reading through a tutorial, this alpha func was mentioned.
   * It allows you to block out certain colors, but it only allows full opaque or full transparent.
   * If you want semi-transparent, you need to use blending and sort the objects.
   * That would really suck and isn't needed here, so I switched to the alpha functions.
   */
  glAlphaFunc(GL_GREATER,0.1f);
  glEnable(GL_ALPHA_TEST);
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//   glEnable(GL_BLEND);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glLightfv	(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
  glLightfv	(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv	(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glEnable	(GL_LIGHT0);
  glEnable	(GL_LIGHTING);
  
  return true;
}

/* Uses color fading from black to white instead of blending,
 * since nothing will be near the stars anyway.
 * Can be switched easily if the case arises.
 */
void Game::updateDrawStars(GLfloat dt)
{
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  GLfloat col;
  
  glBegin(GL_POINTS);
  for (int k = 0; k < NUM_STARS*3; k += 3) {
    stars[k+2] = stars[k+2] + (10*dt);//(0.2f);
    if(stars[k+2] > 50.0) stars[k+2] = -100.0f;
    col = 1.0 - fmax(fabs(stars[k+2]), 0.0)/100;
    //printf("%f\n", fmax(fabs(stars[k+2]), 0.0)/100);
    glColor3f(col, col, col);
    //glColor4f(1.0, 1.0, 1.0, col);
    glVertex3f(stars[k], stars[k+1], stars[k+2]);
  }
  glEnd();
  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
}

void Game::checkCollisions(float new_update)
{
  //For each enemy mob that exists...
  for(vector<Mob*>::iterator ti = gameElements.at(2).begin(); ti != gameElements.at(2).end(); ++ti)
  {
    CylVector* enemy = &(*ti)->pos;
    Mob* ship1 = gameElements.at(0).at(0);
    
    /* If the ship is being drawn and is roughly in the same position as the enemy...
     * REALLY could use some better collision detection.....
     */
    if (!ship1->nodraw && enemy->h <= (ship1->pos.h + 4 ) && enemy->h >= (ship1->pos.h - 4) && enemy->az <= (ship1->pos.az + 0.32) && enemy->az >= (ship1->pos.az -0.32 ) ) {
	//Create an explosion for the enemy
	ParticleSystem* explosion = new ParticleSystem(*enemy, 200);
	explosion->velocity_factor = 5.0;
	explosion->velocity_base = 2.0;
	explosion->randomize(false);
	gameElements.at(4).push_back(explosion);
	
	//Damage the ship and check if it's dead
	if(ship1->damage(20)) {
	  ParticleSystem* shipboom = new ParticleSystem(ship1->pos, 2000);
	  explosion->velocity_factor = 8.0;
	  explosion->velocity_base = 2.0;
	  //explosion->setFade(0.003);
	  explosion->randomize(true);
	  gameElements.at(4).push_back(shipboom);
	  
	  p1_lives -= 1;
	  ship1->nodraw = true;
	  p1_dtime = new_update;
	  gameStatus = 3;
	}
	gameElements.at(2).erase(ti--);
	break;
    }
    
    //For each player bullet, check against current enemy...
    for(vector<Mob*>::iterator it = gameElements.at(1).begin(); it != gameElements.at(1).end(); ++it)
    {
      CylVector* bullet = &(*it)->pos;
      //printf("Bullet: (%f,%f) | Enemy: (%f,%f)\n", bullet->az, bullet->h, enemy->az, enemy->h);
      //Again, could use better collision detection
      if( bullet->h <= (enemy->h + 5) && bullet->h >= (enemy->h - 5) && bullet->az <= (enemy->az + 0.2) && bullet->az >= (enemy->az -0.2 ) ) {
	
	ParticleSystem* explosion = new ParticleSystem(*enemy, 200);
	explosion->velocity_factor = 5.0;
	explosion->velocity_base = 2.0;
	explosion->randomize(false);
	gameElements.at(4).push_back(explosion);
	
	//Delete both the enemy and the bullet
	gameElements.at(1).erase(it--);
	gameElements.at(2).erase(ti--);
	p1_score += 10;
	break;
      }
    }
  }
}

void Game::print(string text, GLfloat x, GLfloat y, GLfloat z)
{
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_BLEND);
  glColor4ub(255, 255, 255, 255);
  glRasterPos3f(x, y, z);
  //glRasterPos2f(x, y);
  textFunction(text.c_str()); //text callback to main.cpp
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

/* Called when the game is ready to start, after the title screen has been displayed. */
void Game::startGame()
{
  //reset the position and drawstate of the ship.
  //There REALLY needs to better way to access the ship globally through this file...
  //Seriously...
  gameElements.at(0).at(0)->reset();
  gameElements.at(0).at(0)->nodraw = false;
  p1_score = 0;
  p1_lives = 1;
  textPos = -70;
  gameStatus = 2;
}

void Game::showTitle()
{
  textPos = -70;
  gameStatus = 0;
}

void Game::drawGameOver(float dt, bool text)
{
  float x;
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glTranslatef(0.0, 0.0, textPos);
  glPushMatrix();
  glScalef(1.0, -1.0,1.0);
  glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_GAMEOVER]);
  x = textPos+70;
  glColor4ub(255,255,255,fmin(255, 0.03146*x*x - 0.304678));
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f,-30.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 30.0f,-30.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 30.0f, 30.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0f, 30.0f, 0.0f);
  glEnd();
  glPopMatrix();
  
  if(text) {
    string screen ("Press Enter to try again (fail less next time)");
    string screen2 ("Press Space to see the badass title screen again");
    print(screen, -15, -15, 0);
    print(screen2, -15, -16, 0);
  }
  
  //Zoom screen in
  textPos = fmin(textPos + dt*20.0, 25.0);
  
  if(textPos == 25.0 && gameStatus == 4) gameStatus++;
  
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void Game::drawTitleScreen(float dt, bool text)
{
  float x;
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glTranslatef(0.0, 0.0, textPos);
  glPushMatrix();
  glScalef(1.0, -1.0,1.0);
  glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_TITLE]);
  x = textPos+70;
  glColor4ub(255,255,255,fmin(255, 0.03146*x*x - 0.304678));
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30.0f,-30.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 30.0f,-30.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 30.0f, 30.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-30.0f, 30.0f, 0.0f);
  glEnd();
  glPopMatrix();
  
  if(text) {
    string screen ("Press Enter to start");
    string screen2 ("Press Esc to quit (at any time)");
    string screen3 ("Instructions:");
    string screen4 ("Move with left/right.");
    string screen5 ("Shoot with space.");
    string screen7 ("DO NOT PRESS S!");
    print(screen, -15, -15, 0);
    print(screen2, -15, -16, 0);
    print(screen3, -15, -17, 0);
    print(screen4, -15, -18, 0);
    print(screen5, -15, -19, 0);
    print(screen7, -15, -21, 0);
  }
  
  //Zoom screen in
  textPos = fmin(textPos + dt*20.0, 25.0);
  
  if(textPos == 25.0 && gameStatus == 0) gameStatus++;
  
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void Game::display(float new_update)
{
  float dt = 0.001 * (new_update - last_update); /* in seconds */
  fps.frame++;
  if ((new_update - fps.timebase) > 1000) {
    fps.fps = fps.frame*1000.0/(new_update-fps.timebase);
    fps.timebase = new_update;
    fps.frame = 0;
  }
  
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  camera.draw();
  
  updateDrawStars(dt);
  
  if(gameStatus <= 1) {
    drawTitleScreen(dt, (gameStatus == 1 ? true : false));
    
  } else if(gameStatus == 4 || gameStatus == 5) {
    drawGameOver(dt, (gameStatus == 5 ? true : false));
    
  } else if(gameStatus >= 2) {
    if(gameStatus == 3 && p1_lives >= 0 && (new_update - p1_dtime) > 5000) {
      gameElements.at(0).at(0)->reset();
      gameElements.at(0).at(0)->nodraw = false;
      if(p1_lives == 0) {
	gameStatus = 4;
	return; //Just ensure you don't see the ship once you've lost your lives
      }
      else gameStatus = 2;
    }
    #ifdef DEBUG
      string ss ("Game State: " + IntToString(gameStatus));
      print(ss, -55, -39, 0);
    #endif
    string s1 ("Hull Integrity: " + IntToString(gameElements.at(0).at(0)->stat1));
    string s11 ("Lives Remaining: " + IntToString(p1_lives));
    string s2 ("Score: " + IntToString(p1_score));
    string s3 ("Fps: " + IntToString(fps.fps));
    print(s1, -55, -41, 0);
    print(s11, -55, -43, 0);
    print(s2, -55, -45, 0);
    print(s3, -55, -47, 0);
    
    updateByKeys(new_update, dt);
    
    spawnEnemy(new_update);
    
    checkCollisions(new_update);
    
    
    /* The meat of the display function.
     * Go through every mob in each vector and update it based on the time since last update, then draw.
     * Unless the mob is defined not to be deleted, it will be deleted if it goes past -40 <= z <= 50.
     */
    
    for( vector< vector<Mob*> >::iterator it = gameElements.begin(); it != gameElements.end(); ++it)
    {
      for( vector<Mob*>::iterator ti = it->begin(); ti != it->end(); ++ti)
      {
	if((*ti)->delnow || (!(*ti)->nodel && ((*ti)->pos.h < -40 || (*ti)->pos.h > 50)))
	{
	  it->erase(ti--);
	}
	else
	{
	  (*ti)->draw();
	  (*ti)->update(dt);
	}
      }
    }
  }
  
  last_update = new_update;
}

/* Uses keys.h to check if keys are pressed, updating accordingly. */
void Game::updateByKeys(float new_update, float dt)
{
  Mob* ship1 = gameElements.at(0).at(0);
  /*if(IsKeyPressed((int)'x')) {
      gameElements.at(0).at(1)->pos.h -= 0.01;
      printf("New az: %f\n", gameElements.at(0).at(1)->pos.h);
  }
  if(IsKeyPressed((int)'z')) {
      gameElements.at(0).at(1)->pos.h += 0.01;
      printf("New az: %f\n", gameElements.at(0).at(1)->pos.h);
  }*/
  if(IsKeyPressed(356)) //LEFT
    ship1->translate(0.0, -2.5f*dt, 0.0f);
  if(IsKeyPressed(358)) //RIGHT
    ship1->translate(0.0, 2.5f*dt, 0.0f);
  if(IsKeyPressed((int)' ')) //SPACEBAR
    if( ship1->canFire(new_update) )
      spawnProjectile(ship1->pos, 0);
  if(IsKeyPressed((int)'s'))
  {
    if(gameElements.at(4).size() == 0) return;
    ParticleSystem* explosion = new ParticleSystem(gameElements.at(4).at(0)->pos, 100000);
    explosion->velocity_factor = 100.0;
    explosion->velocity_base = 20.0;
    //explosion->pos.h -= 70;
    explosion->nodel = true;
    explosion->randomize(true);
    gameElements.at(4).push_back(explosion);
    gameElements.at(4).at(0)->delnow = true;
  }
}

/* Used for shooting bullets.
 * Intended to be modified to allow enemies to shoot in the future.
 */
void Game::spawnProjectile(CylVector v, int type)
{
  if(type == 0)
  {
    Mob* a = new Bullet(v.p - 2.8, v.az + 0.07, v.h - 3.5);
    a->texture = textures[TEXTURE_RED];
    gameElements.at(1).push_back(a);
    Mob* b = new Bullet(v.p - 2.8, v.az - 0.07, v.h - 3.5);
    b->texture = textures[TEXTURE_RED];
    gameElements.at(1).push_back(b);
  }
}

/* Spawns a new enemy, based on a random timer value,
 * between 200-1500ms. Magic numbers are fun!
 */
void Game::spawnEnemy(float new_update)
{
  if((new_update - enemy_timer) > new_enemy_time) {
    Mob* ast = new Asteroid();
    ast->texture = textures[TEXTURE_ASTEROID];
    gameElements.at(2).push_back(ast);
    enemy_timer = new_update;
    new_enemy_time = 200 + 1500*((float)rand())/((float)RAND_MAX);
  }
}

/* Convert an integer to a C++ string. Found a similar sample online to create this one.
 * Requires <sstream>.
 */
string Game::IntToString(int intValue)
{
  string strRetVal; 
  ostringstream stm;
  stm << intValue;
  return(stm.str());
}

void Game::handleKeys(int key)
{
  switch(key) {
    case(KEY_ESCAPE):
      exit(0); break;
    case(KEY_SPACE):
      if(gameStatus == 5) showTitle(); break;
    case(KEY_ENTER):
      if(gameStatus == 1 || gameStatus == 5) startGame();
      break;
  }
}
