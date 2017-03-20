using namespace std;

#include "Ship.h"
#include "data.h" //This must be included HERE so as not to have multiple declarations

#define PI 3.14159265358979

void Ship::draw()
{
  if(nodraw) return;
  glPushMatrix();
  glDisable(GL_BLEND);
  glScalef(0.8, 0.8, 1);
  glTranslatef(pos.x(), pos.y(), pos.z());
  glRotatef(fmodf((pos.az + 2*PI/4) * 180/PI, 360), 0.0, 0.0, 1.0);
  glBindTexture(GL_TEXTURE_2D, texture);
  
  /* This code came from the sample provided with the Milkshape header file.
   * It's realy quite a mess, but it gets the job done for now.
   */
  glBegin( GL_TRIANGLES );
	for(int i=0; i<sph02.num_faces; i++)
	{
		//--- This is how to use the provided texture coordinates
		glTexCoord2f( sph02.uvs[sph02.v_idx[i]].x, sph02.uvs[sph02.v_idx[i]].y );

		glNormal3f( sph02.normals[sph02.n_idx[i]].x,
					sph02.normals[sph02.n_idx[i]].y,
					sph02.normals[sph02.n_idx[i]].z );
		glVertex3f(	sph02.vertices[sph02.v_idx[i]].x,
					sph02.vertices[sph02.v_idx[i]].y,
					sph02.vertices[sph02.v_idx[i]].z );					
	}
	for(int i=0; i<box02.num_faces; i++)
	{
		//--- This is how to use the provided texture coordinates
		glTexCoord2f( box02.uvs[box02.v_idx[i]].x, box02.uvs[box02.v_idx[i]].y );

		glNormal3f( box02.normals[box02.n_idx[i]].x,
					box02.normals[box02.n_idx[i]].y,
					box02.normals[box02.n_idx[i]].z );
		glVertex3f(	box02.vertices[box02.v_idx[i]].x,
					box02.vertices[box02.v_idx[i]].y,
					box02.vertices[box02.v_idx[i]].z );					
	}
	for(int i=0; i<dup00.num_faces; i++)
	{
		//--- This is how to use the provided texture coordinates
		glTexCoord2f( dup00.uvs[dup00.v_idx[i]].x, dup00.uvs[dup00.v_idx[i]].y );

		glNormal3f( dup00.normals[dup00.n_idx[i]].x,
					dup00.normals[dup00.n_idx[i]].y,
					dup00.normals[dup00.n_idx[i]].z );
		glVertex3f(	dup00.vertices[dup00.v_idx[i]].x,
					dup00.vertices[dup00.v_idx[i]].y,
					dup00.vertices[dup00.v_idx[i]].z );					
	}
	for(int i=0; i<dup01.num_faces; i++)
	{
		//--- This is how to use the provided texture coordinates
		glTexCoord2f( dup01.uvs[dup01.v_idx[i]].x, dup01.uvs[dup01.v_idx[i]].y );

		glNormal3f( dup01.normals[dup01.n_idx[i]].x,
					dup01.normals[dup01.n_idx[i]].y,
					dup01.normals[dup01.n_idx[i]].z );
		glVertex3f(	dup01.vertices[dup01.v_idx[i]].x,
					dup01.vertices[dup01.v_idx[i]].y,
					dup01.vertices[dup01.v_idx[i]].z );					
	}
	for(int i=0; i<cyl03.num_faces; i++)
	{
		//--- This is how to use the provided texture coordinates
		glTexCoord2f( cyl03.uvs[cyl03.v_idx[i]].x, cyl03.uvs[cyl03.v_idx[i]].y );

		glNormal3f( cyl03.normals[cyl03.n_idx[i]].x,
					cyl03.normals[cyl03.n_idx[i]].y,
					cyl03.normals[cyl03.n_idx[i]].z );
		glVertex3f(	cyl03.vertices[cyl03.v_idx[i]].x,
					cyl03.vertices[cyl03.v_idx[i]].y,
					cyl03.vertices[cyl03.v_idx[i]].z );					
	}

    glEnd();
    
  glEnable(GL_BLEND);
  glPopMatrix();
}

bool Ship::init()
{
  last_fire = 0.0;
  fire_rate = 300;
  
  //Initialize the variables needed to draw the ship
  sph02.vertices = Sphere02_vertex;
  sph02.v_idx = Sphere02_vidx;
  sph02.normals = Sphere02_normal;
  sph02.n_idx = Sphere02_nidx;
  sph02.uvs = Sphere02_uv;
  sph02.num_faces = (sizeof(Sphere02_vidx)/sizeof(long));
  box02.vertices = Box02_vertex;
  box02.v_idx = Box02_vidx;
  box02.normals = Box02_normal;
  box02.n_idx = Box02_nidx;
  box02.uvs = Box02_uv;
  box02.num_faces = (sizeof(Box02_vidx)/sizeof(long));
  dup00.vertices = Duplicate00_vertex;
  dup00.v_idx = Duplicate00_vidx;
  dup00.normals = Duplicate00_normal;
  dup00.n_idx = Duplicate00_nidx;
  dup00.uvs = Duplicate00_uv;
  dup00.num_faces = (sizeof(Duplicate00_vidx)/sizeof(long));
  cyl03.vertices = Duplicate01_vertex;
  cyl03.v_idx = Duplicate01_vidx;
  cyl03.normals = Duplicate01_normal;
  cyl03.n_idx = Duplicate01_nidx;
  cyl03.uvs = Duplicate01_uv;
  cyl03.num_faces = (sizeof(Duplicate01_vidx)/sizeof(long));
  dup01.vertices = Cylinder03_vertex;
  dup01.v_idx = Cylinder03_vidx;
  dup01.normals = Cylinder03_normal;
  dup01.n_idx = Cylinder03_nidx;
  dup01.uvs = Cylinder03_uv;
  dup01.num_faces = (sizeof(Cylinder03_vidx)/sizeof(long));
    
  reset();
  return true;
}

void Ship::reset()
{
  pos.p = 15.0f;
  pos.az = 0.0f;
  pos.h = 32.0f;
  stat1 = 100;
}

void Ship::print()
{
  printf("New ship:\nx: %f\ny: %f\nz: %f\np: %f\nh: %f\naz: %f\n", pos.x(), pos.y(), pos.z(), pos.p, pos.h, pos.az);
}

void Ship::update(float dt)
{
  translate(dt*velocity.x, dt*velocity.y, dt*velocity.z);
}

bool Ship::canFire(float new_update)
{
  if( (int)(new_update - last_fire) > fire_rate ) {
    //printf("%f\n", (new_update - last_fire));
    last_fire = new_update;
    return true;
  }
  else return false;
}

bool Ship::damage(int dmg)
{
  if(stat1 > 0) stat1 = max(stat1 - dmg, 0);
  return stat1 == 0;
}