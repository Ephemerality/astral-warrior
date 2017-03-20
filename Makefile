OBJS=main.o Game.o Ship.o Camera.o Bullet.o keys.o Mob.o Asteroid.o Particles.o glpng.o
CC=g++
CFLAGS=-Wall -pedantic -c -g -lpng
LFLAGS=-Wall -pedantic -g -lX11

AstralWarrior : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -lGL -lGLU -lglut -lpng -o AstralWarrior

Ship.o : Ship.cpp Ship.h Mob.h data.h
	$(CC) $(CFLAGS) Ship.cpp

Bullet.o : Bullet.cpp Bullet.h Mob.h
	$(CC) $(CFLAGS) Bullet.cpp

Camera.o : Camera.cpp Camera.h
	$(CC) $(CFLAGS) Camera.cpp

Particles.o : Particles.cpp Particles.h Mob.h
	$(CC) $(CFLAGS) Particles.cpp

Mob.o : Mob.cpp Mob.h
	$(CC) $(CFLAGS) Mob.cpp
 
Asteroid.o : Asteroid.cpp Mob.h
	$(CC) $(CFLAGS) Asteroid.cpp

keys.o : keys.cpp keys.h
	$(CC) $(CFLAGS) keys.cpp

Game.o : Game.cpp Game.h Mob.o keys.o Ship.o
	$(CC) $(CFLAGS) Game.cpp

main.o : main.cpp Game.o keys.o glpng.o
	$(CC) $(CFLAGS) main.cpp

glpng.o : glpng.c glpng.h
	$(CC) $(CFLAGS) glpng.c

clean :
	rm $(OBJS)
