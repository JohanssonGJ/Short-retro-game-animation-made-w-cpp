// demo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "yspng.h"
#include <cstdlib>
#include <chrono>

YsRawPngDecoder png;
YsRawPngDecoder powerup;
YsRawPngDecoder skull;
YsRawPngDecoder skullcry;

void bg()
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);

	glColor3f(0.2, 0.2, 0.2);
	glVertex2i(0, 0);

	glColor3f(0.1, 0.1, 0.1);
	glVertex2i(1000, 0);

	glColor3f(0.1, 0.1, 0.1);
	glVertex2i(1000, 600);

	glColor3f(0.2, 0.2, 0.2);
	glVertex2i(0, 600);

	glEnd();
}

void DrawPlayer(int x0, int y0)
{
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex2i(x0, y0);
	glVertex2i(x0 + 20, y0);
	glVertex2i(x0 + 20, y0 + 50);
	glVertex2i(x0, y0 + 50);
	glEnd();
}

void MovePlayer(int &x0, int &y0, int tarx0, int tary0, int Case) //0:up 1:down 2:right
{
	
	switch (Case)
	{
	case 0:
		y0 = y0 - 90 * 0.025;
		break;
	case 1:
		y0 = y0 + 90 * 0.025;
		break;
	case 2:
		x0 = x0 + 40 * 0.025;
		break;
	}
}
void rails()
{
	glColor3ub(255, 165, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(1000, 0);
	glVertex2i(1000, 30);
	glVertex2i(0, 30);
	glVertex2i(0, 570);
	glVertex2i(1000, 570);
	glVertex2i(1000, 600);
	glVertex2i(0, 600);
	glEnd();
}

void drawendwall(double x0e, double y0e)
{
	glColor3ub(255, 165, 0);
	glBegin(GL_QUADS);
	glVertex2i(x0e, y0e);
	glVertex2i(x0e + 1000, y0e);
	glVertex2i(x0e + 1000, y0e + 600);
	glVertex2i(x0e, y0e + 600);
	glEnd();
}

void movewall(int& x0e, int& y0e)
{
	x0e = x0e - 80 * 0.025;
}

class missile
{
public:
	int missileState;
	double x, y;
	double vx, vy;
	void Initialize(double artX, double artY, double iniVel);
	void Draw();
	void Move(double dt);
};
void missile::Initialize(double artX, double artY, double iniVel)
{
	x = artX;
	y = artY;
	vx = iniVel;

}
void missile::Draw() //triangle wit yellow thruster
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	glColor3ub(255, 0, 0);
	glVertex2i(x, y);
	glColor3ub(255, 0, 255);
	glVertex2i(x + 130, y - 50);
	glColor3ub(255, 0, 255);
	glVertex2i(x + 130, y + 50);
	glEnd();
}

void missile::Move(double dt)
{
	x -= vx * dt;
}
//class for blue lines, missles, spikes, add powerups, boss, collisions, treasure, end rails, victory sound

class lines
{
public:
	int lineState;
	double x, y;
	double vx;
	void initialize(double xStart, double yStart);
	void draw();
	void move(double dt);
};

void lines::initialize(double xStart, double yStart)
{
	lineState = 0;
	x = xStart;
	y = yStart;
	vx = 80;
}
void lines::draw()
{
	glColor3ub(0, 0, 255);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + 10, y);
	glVertex2i(x + 10, y + 30);
	glVertex2i(x, y + 30);
	glEnd();
}

void lines::move(double dt)
{
	x = x - vx*dt;
	if (x < 1)
		x = 1000;
}

class images
{
public:
	int imageState;
	double x, y;
	double vx;
	void initialize(double xStart, double yStart);
	void draw();
	void move(double dt);
};

void images::initialize(double xStart, double yStart)
{
	imageState = 0;
	x = xStart;
	y = yStart;
	vx = 80;
}
void images::draw()
{
	glDrawPixels(41, 44, GL_RGBA, GL_UNSIGNED_BYTE, powerup.rgba);
}

void images::move(double dt)
{
	x -= vx * dt;
	glRasterPos2i(x, y);
}

class images2
{
public:
	int image2State;
	double x, y;
	double vx;
	void initialize(double xStart, double yStart);
	void draw();
	void move(double dt);
};

void images2::initialize(double xStart, double yStart)
{
	image2State = 0;
	x = xStart;
	y = yStart;
	vx = 80;
}
void images2::draw()
{
	glRasterPos2i(x, y);
	glDrawPixels(225, 303, GL_RGBA, GL_UNSIGNED_BYTE, skull.rgba);
}

void images2::move(double dt)
{
	x -= vx * dt;
	glRasterPos2i(x, y);
}

class images3
{
public:
	int image2State;
	double x, y;
	double vy;
	void initialize(double xStart, double yStart);
	void draw();
	void move(double dt);
};

void images3::initialize(double xStart, double yStart)
{
	image2State = 0;
	x = xStart;
	y = yStart;
	vy = 60;
}
void images3::draw()
{
	glRasterPos2i(x, y);
	glDrawPixels(225, 303, GL_RGBA, GL_UNSIGNED_BYTE, skullcry.rgba);
}

void images3::move(double dt)
{
	y += vy * dt;
	glRasterPos2i(x, y);
}

class images4
{
public:
	int image2State;
	double x, y;
	double vx;
	void initialize(double xStart, double yStart);
	void draw();
	void move(double dt);
};

void images4::initialize(double xStart, double yStart)
{
	image2State = 0;
	x = xStart;
	y = yStart;
	vx = 80;
}
void images4::draw()
{
	glRasterPos2i(x, y);
	glDrawPixels(160, 121, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
}

void images4::move(double dt)
{
	x -= vx * dt;
	glRasterPos2i(x, y);
}



class nuke
{
public:
	int missileState;
	double x, y;
	double vx, vy;
	void Initialize(double artX, double artY, double iniVel);
	void Draw();
	void Move(double dt);
};
void nuke::Initialize(double artX, double artY, double iniVel)
{
	x = artX;
	y = artY;
	vx = iniVel;

}
void nuke::Draw() //triangle wit yellow thruster
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POLYGON);
	glColor3ub(0, 255, 0);
	glVertex2i(x+170, y);
	glColor3ub(0, 0, 255);
	glVertex2i(x+20, y - 100);
	glColor3ub(0, 0, 255);
	glVertex2i(x+20, y + 100);
	glEnd();
}

void nuke::Move(double dt)
{
	x += vx * dt;
}

int main(void)
{
	int x0 = 0;
	int y0 = 100;
	int x0e = 1250; int y0e = 0;
	const int nLines = 4;
	const int nMiss = 8;
	const int nPup = 3;
	int bgmusicflag = 0;
	int introflag = 0;
	int flag1 = 0; int flag2 = 0; int flag3 = 0; int flag4 = 0; int flag5 = 0; int flag6 = 0; int flag7 = 0; int flag8 = 0; int flag9 = 0; int flag10 = 0; int flag11 = 0; int flag12 = 0;
	int pflag1 = 0; int pflag2 = 0; int pflag3 = 0; int pflag4 = 0; int pflag5 = 0; int pflag6 = 0; int pflag7 = 0; int pflag8 = 0; int pflag9 = 0; int pflag10 = 0; int pflag11 = 0; int  pflag12 = 0;
	int imageflag1 = 0; int imageflag2 = 0; int imageflag3 = 0;
	lines Lines[nLines];
	Lines[0].initialize(200, 0);
	Lines[1].initialize(700, 0);
	Lines[2].initialize(200, 570);
	Lines[3].initialize(700, 570);

	missile Missile[nMiss];
	Missile[0].Initialize(1000, 100, 200);
	Missile[1].Initialize(1000, 300, 200);
	Missile[2].Initialize(1000, 500, 200);
	Missile[3].Initialize(1000, 100, 200);

	images image[nPup];		//powerup
	image[0].initialize(1000, 240);

	images2 image2;					//skull
	image2.initialize(1000, 400);

	images3 image3;					//skullcry
	image3.initialize(700, 400);

	images4 image4;					//treasure
	image4.initialize(1050, 400);

	nuke nuke1;
	nuke1.Initialize(50, 200, 50);

	png.Decode("treasure1.png");
	png.Flip();
	powerup.Decode("powerup.png");
	powerup.Flip();
	skull.Decode("skull.png");
	skull.Flip();
	skullcry.Decode("skullcry.png");
	skullcry.Flip();
	FsOpenWindow(0, 0, 1000, 600, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	YsSoundPlayer player;
	YsSoundPlayer::SoundData wav;
	YsSoundPlayer::SoundData wav2;
	if (YSOK != wav.LoadWav("man-is-he-mega-glbml-22045.wav"))
	{ 
		printf("Failed to read bg music\n");
		return 1;
	}
	if (YSOK != wav2.LoadWav("powerup.wav"))
	{
		printf("Failed to read bg music\n");
		return 1;
	}
	player.Start();
	player.PlayBackground(wav);
	
	for (;;)
	{
		FsPollDevice();
		auto key = FsInkey();
		if (FSKEY_ESC == key)
		{
			break;
		}

		player.KeepPlaying();

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		bg();
		rails();
		Lines[0].draw();
		Lines[1].draw();
		Lines[2].draw();
		Lines[3].draw();
		if (pflag8 == 0) 
		{
			Lines[0].move(0.025);
			Lines[1].move(0.025);
			Lines[2].move(0.025);
			Lines[3].move(0.025);
		}
		

		DrawPlayer(x0, y0);
		

		if (introflag == 0)							//player move 50 in
		{
			MovePlayer(x0, y0, 50, 200, 2);
			
			if (x0 == 50)
				introflag = 1;
		}

		if (introflag == 1)							//missle at y100 
		{
			Missile[0].Draw();
			Missile[0].Move(0.025);
			if (Missile[0].x < 350 && pflag1 == 0)
			{
				MovePlayer(x0, y0, 50, 300, 1);
				if (y0 == 300)
					pflag1 = 1;
			}

			if (Missile[0].x < 200)
			{
				flag1 = 1;
			}
		}

		if (flag1 == 1)
		{
			Missile[1].Draw();
			Missile[1].Move(0.025);
			if (Missile[1].x < 350 && pflag2 == 0)
			{
				MovePlayer(x0, y0, 50, 500, 1);
				if (y0 == 500)
					pflag2 = 1;
			}
			if (Missile[1].x < 200)
			{
				flag2 = 1;
			}	
		}

		if (flag2 == 1)
		{
			if(imageflag1 == 0)
				image[0].draw();
			image[0].move(0.025);
			if (image[0].x < 350 && pflag4 == 0)
			{
				MovePlayer(x0, y0, 50, 200, 0);
				if (y0 == 200)
					pflag4 = 1;
			}
			if (image[0].x < 50)
			{
				imageflag1 = 1;
				//player.PlayOneShot(wav2);
				flag2 = 0;
				flag3 = 1;
		
			}
		}
		if (flag3 == 1)
		{
			if (flag4 == 0)
			{
				flag4 = 1;
			}
			if(imageflag2 == 0)
				image2.draw();

			if(imageflag3 == 0)
				image2.move(0.025);

			if (image2.x == 700)
			{
				imageflag3 = 1;
				flag5 = 1;
			}
		}
		if (flag5 == 1)
		{
			if(pflag5 == 0)
			MovePlayer(x0, y0, 100, 400, 1);
			if (y0 > 400)
			{
				pflag5 = 1;
			}

			if (pflag5 == 1)
			{
				if(pflag6 == 0)
				MovePlayer(x0, y0, 100, 200, 0);
				if (y0 < 200)
				{
					pflag6 = 1;
					flag6 = 1;
				}
			}
		}
		if (flag6 == 1)
		{
			if(flag7 == 0)
			{ 
				nuke1.Draw();
			}
			nuke1.Move(0.025);
			if (nuke1.x > 530)
			{
				flag7 = 1;
				imageflag2 = 1;
				flag8 = 1;
			}
		}
		if (flag8 == 1)
		{
			image3.draw();
			image3.move(0.025);
			if (image3.y > 500);
			{
				flag9 = 1;
			}
		}
		if (flag9 == 1)
		{
			if (pflag7 == 0)
				MovePlayer(x0, y0, 100, 300, 1);
			if (y0 > 300)
			{
				pflag7 = 1;
				pflag9 = 1;
				flag10 = 1;
			}
		}

		if (flag10 == 1)
		{
			if (pflag10 == 0)
				MovePlayer(x0, y0, 100, 500, 1);
			if (y0 > 500)
			{
				pflag10 = 1;
			}

			if (pflag10 == 1)
			{
				if (pflag11 == 0)
					MovePlayer(x0, y0, 100, 300, 0);
				if (y0 < 300)
				{
					pflag11 = 1;
					flag11 = 1;
				}
			}
		}

		if (flag11 == 1)
		{
			image4.draw();
			drawendwall(x0e, y0e);
			if (pflag8 == 0)
			{
				image4.move(0.025);
				movewall(x0e, y0e);
			}
			if (x0e < 700)
			{
				pflag8 = 1;
				flag12 = 1;
			}
		}
		if (flag12 == 1)
		{
			if (pflag12 == 0)
				MovePlayer(x0, y0, 400, 300, 2);
			if (x0 > 420)
			{
				pflag12 = 1;
				break;
			}
		}

		FsSwapBuffers();
		FsSleep(25);
		
	}
	player.PlayOneShot(wav2);
	while (YSTRUE == player.IsPlaying(wav2))
	{
		player.KeepPlaying();

	}
	player.End();
	return 0;
}
