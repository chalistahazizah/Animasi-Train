#include<stdlib.h>
#include<glut.h>
#include<math.h>
#include<iostream>
#include<gl/gl.h>
#include<cstring>
#include<windows.h>
#include<mmsystem.h>

using namespace std;

float _angle1 = 30.0f; //train
float _angle2 = 0.2f;  //bird
float _angle3 = 0.0f;  //wheel
float _angle4 = 0.0f;  //wheel

float speed = 3.0f; //train
float speed2 = 2.0f; //bird

float cloud_X = 0;
float cloud_Y = 0;
float cloud_X2 = 0;
float cloud_Y2 = 0;
float cloud_X3 = 0;
float cloud_Y3 = 0;
int cloudStatus = 1;

float bird2_X = 0;
float bird2_Y = 0;
int bird2Status = 1;

float moon_X = 0;
float moon_Y = 0;
int moonStatus = 1;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
	default:
		break;
	}
	glutPostRedisplay();
}

void idle() {
	glutPostRedisplay(); //Post a re-paint request to activate display()
}

void init(void)
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-300.0, 300.0, -200.0, 200.0);
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0);   //Enable light #0
	glEnable(GL_LIGHT1);   //Enable light #1
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2f(x + cx, y + cy);

	}
	glEnd();
}

void drawMoon()
{
	glPushMatrix();
	glColor3f(3.0, 1.0, 0.5);
	DrawCircle(100, 50, 20, 100);
	glPopMatrix();
}

void bird2() //objek burung
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glColor3f(0.133, 0.545, 0.133);

	glBegin(GL_POLYGON);
	glVertex2i(180, 140);
	glVertex2i(180, 130);
	glVertex2i(170, 125);
	glVertex2i(160, 130);
	glVertex2i(160, 140);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(160, 130);
	glVertex2i(160, 140);
	glVertex2i(150, 137);
	glVertex2i(152, 132);
	glEnd(); //end green bird

	glBegin(GL_POLYGON); //start green bird
	glColor3f(1.000, 0.000, 0.000);
	glVertex2i(145, 135);
	glVertex2i(150, 137);
	glVertex2i(152, 132);
	glEnd(); //end green bird

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(180, 140);
	glVertex2i(180, 130);
	glVertex2i(190, 133);
	glVertex2i(195, 140);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(180, 140);
	glVertex2i(195, 140);
	glVertex2i(190, 144);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(170, 125);
	glVertex2i(180, 130);
	glVertex2i(185, 122);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.133, 0.545, 0.133);
	glVertex2i(160, 140);
	glVertex2i(170, 155);
	glVertex2i(185, 160);
	glVertex2i(180, 140);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(185, 160);
	glVertex2i(180, 158.33);
	glVertex2i(190, 150);
	glEnd();

	glPopMatrix(); //finish bird
}

void bird2m() //bergerak otomatis
{
	if (bird2Status == 1)
	{
		bird2_X -= .4;
		bird2_Y += .01;
	}
	if (bird2_X < -500)
	{
		bird2_X = 200;
		bird2_Y = 0;
	}

	glPushMatrix();
	glTranslatef(bird2_X, bird2_Y, 0.0);
	bird2();

	glPopMatrix();
}

void moon()
{
	if (moonStatus == 1)
	{
		moon_X += 0.001;
		moon_Y += .01;
	}
	if (moon_X > 17)
	{
		moon_X = 0;
		moon_Y = 0;
	}

	glPushMatrix();
	glTranslatef(moon_X, moon_Y, 0.0);
	drawMoon();

	glPopMatrix();
}

void Statn() //objek rumah saat siang hari
{
	glBegin(GL_POLYGON); //gate
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(-50, -80);
	glVertex2i(-50, 35);
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(10, 75);
	glVertex2i(70, 35);
	glVertex2i(70, -80);
	glEnd();

	glBegin(GL_POLYGON); //start door
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(-60, -80);
	glVertex2i(-60, 40);
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(10, 90);
	glVertex2i(80, 40);
	glVertex2i(80, -80);
	glEnd(); //door

	glBegin(GL_POLYGON); //room
	glColor3f(1.000, 0.549, 0.000);
	glVertex2i(-100, -80);
	glVertex2i(-100, 110);
	glColor3f(0.957, 0.643, 0.376);
	glVertex2i(50, 110);
	glVertex2i(100, 70);
	glVertex2i(80, 40);
	glVertex2i(10, 90);
	glVertex2i(-60, 40);
	glVertex2i(-60, -80);
	glEnd();

	glBegin(GL_POLYGON); //left room window
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(-170, -70);
	glVertex2i(-170, 40);
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(-110, 40);
	glVertex2i(-110, -70);
	glEnd();

	glBegin(GL_POLYGON); //left room 
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(-180, -80);
	glVertex2i(-180, 110);
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(-100, 110);
	glVertex2i(-100, -80);
	glEnd(); //door

	glBegin(GL_POLYGON); //roof
	glColor3f(0.698, 0.133, 0.133);
	glVertex2i(-190, 110);
	glColor3f(0.863, 0.078, 0.235);
	glVertex2i(-140, 165);
	glVertex2i(-90, 110); 
	glEnd(); //left roof

	glBegin(GL_POLYGON); //r8 room window
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(90, -20);
	glVertex2i(90, 30);
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(140, 30);
	glVertex2i(140, -20);
	glEnd();

	glBegin(GL_POLYGON); //r8 room 
	glColor3f(0.957, 0.643, 0.376);
	glVertex2i(80, -80);
	glVertex2i(80, 40);
	glColor3f(1.000, 0.549, 0.000);
	glVertex2i(150, 40);
	glVertex2i(150, -80);
	glEnd();

	glBegin(GL_POLYGON); //r8 roof 
	glColor3f(0.698, 0.133, 0.133);
	glVertex2i(70, 40);
	glColor3f(0.863, 0.078, 0.235);
	glVertex2i(115, 90);
	glVertex2i(160, 40);
	glEnd();
}

void StatnNight() //rumah saat malam hari
{
	glBegin(GL_POLYGON); //gate
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(-50, -80);
	glVertex2i(-50, 35);
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(10, 75);
	glVertex2i(70, 35);
	glVertex2i(70, -80);
	glEnd();

	glBegin(GL_POLYGON); //start door
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(-60, -80);
	glVertex2i(-60, 40);
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(10, 90);
	glVertex2i(80, 40);
	glVertex2i(80, -80);
	glEnd(); //door

	glBegin(GL_POLYGON); //room
	glColor3f(1.000, 0.549, 0.000);
	glVertex2i(-100, -80);
	glVertex2i(-100, 110);
	glColor3f(0.957, 0.643, 0.376);
	glVertex2i(50, 110);
	glVertex2i(100, 70);
	glVertex2i(80, 40);
	glVertex2i(10, 90);
	glVertex2i(-60, 40);
	glVertex2i(-60, -80);
	glEnd();

	glBegin(GL_POLYGON); //left room window
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(-170, -70);
	glVertex2i(-170, 40);
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(-110, 40);
	glVertex2i(-110, -70);
	glEnd();

	glBegin(GL_POLYGON); //left room 
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(-180, -80);
	glVertex2i(-180, 110);
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(-100, 110);
	glVertex2i(-100, -80);
	glEnd(); //door

	glBegin(GL_POLYGON); //roof
	glColor3f(0.698, 0.133, 0.133);
	glVertex2i(-190, 110);
	glColor3f(0.863, 0.078, 0.235);
	glVertex2i(-140, 165);
	glVertex2i(-90, 110);
	glEnd(); //left roof

	glBegin(GL_POLYGON); //r8 room window
	glColor3f(0.3, 0.2, 0.0);
	glVertex2i(90, -20);
	glVertex2i(90, 30);
	glColor3f(1.000, 0.627, 0.478);
	glVertex2i(140, 30);
	glVertex2i(140, -20);
	glEnd();

	glBegin(GL_POLYGON); //r8 room 
	glColor3f(0.957, 0.643, 0.376);
	glVertex2i(80, -80);
	glVertex2i(80, 40);
	glColor3f(1.000, 0.549, 0.000);
	glVertex2i(150, 40);
	glVertex2i(150, -80);
	glEnd();

	glBegin(GL_POLYGON); //r8 roof
	glColor3f(0.689, 0.133, 0.133);
	glVertex2i(70, 40);
	glColor3f(0.863, 0.078, 0.235);
	glVertex2i(115, 90);
	glVertex2i(160, 40);
	glEnd();
}

void drawCloud()
{
	glPushMatrix();

	glColor3f(0.8, 0.8, 0.8);
	DrawCircle(-130, 170, 25, 100); //1st cloud
	DrawCircle(-160, 175, 25, 100);
	DrawCircle(-100, 165, 25, 100);
	DrawCircle(-140, 155, 25, 100);

	DrawCircle(130, 170, 25, 100); //2nd cloud
	DrawCircle(160, 175, 25, 100);
	DrawCircle(100, 165, 25, 100);
	DrawCircle(140, 155, 25, 100);

	glPopMatrix();
}

void drawWindow()
{
	glPushMatrix();

	glColor3f(0.663, 0.663, 0.663);
	DrawCircle(-140, 75, 25, 100); //clock

	glPopMatrix();
}

void drawWindowN()
{
	glPushMatrix();

	glColor3f(3.0, 1.0, 0.5);
	DrawCircle(-140, 75, 25, 100); //clock

	glPopMatrix();
}

void cloud()
{
	if (cloudStatus == 1)
	{
		cloud_X -= 0.2;
	}
	if (cloud_X < -1100)
	{
		cloud_X = +650;
	}

	glPushMatrix();
	glTranslatef(cloud_X, cloud_Y, 0.0);
	drawCloud();

	glPopMatrix();
}

void cloud2()
{
	if (cloudStatus == 1)
	{
		cloud_X2 += 0.3;
	}
	if (cloud_X2 > 600)
	{
		cloud_X2 = -1150;
	}

	glPushMatrix();
	glTranslatef(cloud_X2 + 500, cloud_Y2 + 50, 0.0);
	drawCloud();
	glPopMatrix();
}

void cloud3()
{
	if (cloudStatus == 1)
	{
		cloud_X3 += 0.3;
	}
	if (cloud_X3 > 600)
	{
		cloud_X3 = -1150;
	}

	glPushMatrix();
	glTranslatef(cloud_X3 + 500, cloud_Y3 + 50, 0.0);
	drawCloud();
	glPopMatrix();
}

void tree()
{
	glBegin(GL_POLYGON); //Grass Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(175, -20);
	glVertex2i(160, 0);
	glVertex2i(150, 10);
	glVertex2i(170, 0);
	glVertex2i(160, 30);
	glVertex2i(180, 10);
	glVertex2i(185, 50);
	glColor3f(0.6, 1.000, 0.184);
	glVertex2i(190, 10);
	glVertex2i(210, 30);
	glVertex2i(200, 0);
	glVertex2i(220, 10);
	glVertex2i(210, 0);
	glVertex2i(195, -20);
	glEnd();

	glBegin(GL_POLYGON); //Grass Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(245, -20);
	glVertex2i(230, 0);
	glVertex2i(220, 10);
	glVertex2i(240, 0);
	glVertex2i(230, 30);
	glVertex2i(250, 10);
	glVertex2i(255, 50);
	glColor3f(0.6, 1.000, 0.184);
	glVertex2i(260, 10);
	glVertex2i(280, 30);
	glVertex2i(270, 0);
	glVertex2i(290, 10);
	glVertex2i(280, 0);
	glVertex2i(265, -20);
	glEnd();

	glBegin(GL_POLYGON); //Grass Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(-245, -20);
	glVertex2i(-230, 0);
	glVertex2i(-220, 10);
	glVertex2i(-240, 0);
	glVertex2i(-230, 30);
	glVertex2i(-250, 10);
	glVertex2i(-255, 50);
	glColor3f(0.6, 0.8, 0.1);
	glVertex2i(-260, 10);
	glVertex2i(-280, 30);
	glVertex2i(-270, 0);
	glVertex2i(-290, 10);
	glVertex2i(-280, 0);
	glVertex2i(-265, -20);
	glEnd();

	glBegin(GL_POLYGON); //Grass Big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(-175, -20);
	glVertex2i(-160, 0);
	glVertex2i(-150, 10);
	glVertex2i(-170, 0);
	glVertex2i(-160, 30);
	glVertex2i(-180, 10);
	glVertex2i(-185, 50);
	glColor3f(0.6, 0.8, 0.1);
	glVertex2i(-190, 10);
	glVertex2i(-210, 30);
	glVertex2i(-200, 0);
	glVertex2i(-220, 10);
	glVertex2i(-210, 0);
	glVertex2i(-195, -20);
	glEnd();

	glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
	glVertex2f(180, 0);
	glVertex2f(180, 70);
	glColor3f(0.804, 0.522, 0.247);
	glVertex2f(170, 70);
	glVertex2f(170, 0);
	glEnd();

	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(220, 70);
	glVertex2i(190, 85);
	glColor3f(0.678, 1.000, 0.184);
	glVertex2i(160, 85);
	glVertex2i(130, 70);
	glEnd();

	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(215, 85);
	glVertex2i(185, 100);
	glColor3f(0.678, 1.000, 0.184);
	glVertex2i(165, 100);
	glVertex2i(135, 85);
	glEnd();

	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(210, 100);
	glColor3f(0.678, 1.000, 0.184);
	glVertex2i(175, 135);
	glVertex2i(140, 100);
	glEnd();

	glColor3f(0.0, 0.5, 0.0); //tree2
	glBegin(GL_POLYGON);
	glVertex2i(-240, 70);
	glVertex2i(-210, 85);
	glColor3f(0.678, 1.000, 0.184);
	glVertex2i(-180, 85);
	glVertex2i(-150, 70);
	glEnd();

	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(-235, 85);
	glVertex2i(-205, 100);
	glColor3f(0.678, 1.000, 0.184);
	glVertex2i(-185, 100);
	glVertex2i(-155, 85);
	glEnd();

	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(-230, 100);
	glColor3f(0.678, 1.000, 0.184);
	glVertex2i(-195, 135);
	glVertex2i(-160, 100);
	glEnd();

	glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
	glVertex2f(-200, 0);
	glVertex2f(-200, 70);
	glColor3f(0.804, 0.522, 0.247);
	glVertex2f(-190, 70);
	glVertex2f(-190, 0);
	glEnd();

	glPushMatrix();

	glColor3f(0.133, 0.545, 0.133);
	DrawCircle(210, 105, 25, 100);

	DrawCircle(250, 95, 25, 100);

	DrawCircle(275, 95, 25, 100);

	DrawCircle(240, 130, 25, 100); //big tree
	DrawCircle(250, 115, 25, 100);

	glPopMatrix();

	glColor3f(0.545098, 0.270588, 0.0745098);
	glBegin(GL_POLYGON);
	glVertex2f(250, 0);
	glVertex2f(250, 80);
	glColor3f(0.804, 0.522, 0.247);
	glVertex2f(235, 80);
	glVertex2f(235, 0);
	glEnd();

}

void background()
{
	glBegin(GL_POLYGON); //start green land
	glColor3f(0.333, 0.420, 0.184);
	glVertex2i(300, 70);
	glVertex2i(-300, 70);
	glColor3f(0.0, 0.9, 0.0);
	glVertex2i(-300, -20);
	glVertex2i(300, -20);
	glEnd(); //end green land

	glBegin(GL_POLYGON); //start green land after platform
	glColor3f(0.333, 0.420, 0.184);
	glVertex2i(300, -120);
	glVertex2i(-300, -120);
	glColor3f(0.0, 0.9, 0.0);
	glVertex2i(-300, -200);
	glVertex2i(300, -200);
	glEnd(); //end green land after road

	glBegin(GL_POLYGON); //start sky
	glColor3f(0.098, 0.098, 0.439);
	glVertex2i(300, 65);
	glVertex2i(-300, 65);
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-300, 200);
	glVertex2i(300, 200);
	glEnd(); //end sky

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(35, -180);
	glVertex2i(20, -160);
	glVertex2i(10, -150);
	glVertex2i(30, -160);
	glVertex2i(20, -130);
	glVertex2i(40, -150);
	glVertex2i(45, -110);
	glColor3f(0.6, 0.8, 0.1);
	glVertex2i(50, -150);
	glVertex2i(70, -130);
	glVertex2i(60, -160);
	glVertex2i(80, -150);
	glVertex2i(70, -160);
	glVertex2i(55, -180);
	glEnd();
}

void backgroundDay()
{
	glBegin(GL_POLYGON); //start green land
	glColor3f(0.565, 0.933, 0.565);
	glVertex2i(300, 70);
	glVertex2i(-300, 70);
	glColor3f(0.0, 0.9, 0.0);
	glVertex2i(-300, -20);
	glVertex2i(300, -20);
	glEnd(); //end green land

	glBegin(GL_POLYGON); //start green land after road
	glColor3f(0.565, 0.933, 0.565);
	glVertex2i(300, -120);
	glVertex2i(-300, -120);
	glColor3f(0.0, 0.9, 0.0);
	glVertex2i(-300, -200);
	glVertex2i(300, -200);
	glEnd(); //end green land after road

	glBegin(GL_POLYGON); //start sky
	glColor3f(0.03, 0.73, 0.96);
	glVertex2i(300, 65);
	glVertex2i(-300, 65);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(-300, 200);
	glVertex2i(300, 200);
	//glVertex2i(300, -20);
	glEnd(); //end sky

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(35, -180);
	glVertex2i(20, -160);
	glVertex2i(10, -150);
	glVertex2i(30, -160);
	glVertex2i(20, -130);
	glVertex2i(40, -150);
	glVertex2i(45, -110);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(50, -150);
	glVertex2i(70, -130);
	glVertex2i(60, -160);
	glVertex2i(80, -150);
	glVertex2i(70, -160);
	glVertex2i(55, -180);
	glEnd();
}

void platfrm()
{
	glBegin(GL_POLYGON); //start 
	glColor3f(0.741, 0.718, 0.420);
	glVertex2i(-300, -20);
	glVertex2i(-300, -120);
	glVertex2i(300, -120);
	glVertex2i(300, -20);
	glEnd(); //end 

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(35, -200);
	glVertex2i(20, -180);
	glVertex2i(10, -170);
	glVertex2i(30, -180);
	glVertex2i(20, -150);
	glVertex2i(40, -170);
	glVertex2i(45, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(50, -170);
	glVertex2i(70, -150);
	glVertex2i(60, -180);
	glVertex2i(80, -170);
	glVertex2i(70, -180);
	glVertex2i(55, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(105, -200);
	glVertex2i(90, -180);
	glVertex2i(80, -170);
	glVertex2i(100, -180);
	glVertex2i(90, -150);
	glVertex2i(110, -170);
	glVertex2i(115, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(120, -170);
	glVertex2i(140, -150);
	glVertex2i(130, -180);
	glVertex2i(150, -170);
	glVertex2i(140, -180);
	glVertex2i(125, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(175, -200);
	glVertex2i(160, -180);
	glVertex2i(150, -170);
	glVertex2i(170, -180);
	glVertex2i(160, -150);
	glVertex2i(180, -170);
	glVertex2i(185, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(190, -170);
	glVertex2i(210, -150);
	glVertex2i(200, -180);
	glVertex2i(220, -170);
	glVertex2i(210, -180);
	glVertex2i(195, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(245, -200);
	glVertex2i(230, -180);
	glVertex2i(220, -170);
	glVertex2i(240, -180);
	glVertex2i(230, -150);
	glVertex2i(250, -170);
	glVertex2i(255, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(260, -170);
	glVertex2i(280, -150);
	glVertex2i(270, -180);
	glVertex2i(290, -170);
	glVertex2i(280, -180);
	glVertex2i(265, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(-35, -200);
	glVertex2i(-20, -180);
	glVertex2i(-10, -170);
	glVertex2i(-30, -180);
	glVertex2i(-20, -150);
	glVertex2i(-40, -170);
	glVertex2i(-45, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(-50, -170);
	glVertex2i(-70, -150);
	glVertex2i(-60, -180);
	glVertex2i(-80, -170);
	glVertex2i(-70, -180);
	glVertex2i(-55, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(-105, -200);
	glVertex2i(-90, -180);
	glVertex2i(-80, -170);
	glVertex2i(-100, -180);
	glVertex2i(-90, -150);
	glVertex2i(-110, -170);
	glVertex2i(-115, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(-120, -170);
	glVertex2i(-140, -150);
	glVertex2i(-130, -180);
	glVertex2i(-150, -170);
	glVertex2i(-140, -180);
	glVertex2i(-125, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(-175, -200);
	glVertex2i(-160, -180);
	glVertex2i(-150, -170);
	glVertex2i(-170, -180);
	glVertex2i(-160, -150);
	glVertex2i(-180, -170);
	glVertex2i(-185, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(-190, -170);
	glVertex2i(-210, -150);
	glVertex2i(-200, -180);
	glVertex2i(-220, -170);
	glVertex2i(-210, -180);
	glVertex2i(-195, -200);
	glEnd();

	glBegin(GL_POLYGON); //grass big
	glColor3f(0.0, 0.6, 0.1);
	glVertex2i(-245, -200);
	glVertex2i(-230, -180);
	glVertex2i(-220, -170);
	glVertex2i(-240, -180);
	glVertex2i(-230, -150);
	glVertex2i(-250, -170);
	glVertex2i(-225, -130);
	glColor3f(0.7, 0.8, 0.1);
	glVertex2i(-260, -170);
	glVertex2i(-280, -150);
	glVertex2i(-270, -180);
	glVertex2i(-290, -170);
	glVertex2i(-280, -180);
	glVertex2i(-265, -200);
	glEnd();
}

void Railline()
{
	glBegin(GL_POLYGON); //start railline1
	glColor3f(0.502, 0.000, 0.000);
	glVertex2i(-300, -70);
	glVertex2i(-300, -75);
	glVertex2i(300, -75);
	glVertex2i(300, -70);
	glEnd(); //end railline1

	glBegin(GL_POLYGON); //start railline2
	glColor3f(0.502, 0.000, 0.000);
	glVertex2i(-300, -60);
	glVertex2i(-300, -65);
	glVertex2i(300, -65);
	glVertex2i(300, -60);
	glEnd(); //end railline2

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-300, -80);
	glVertex2i(-300, -55);
	glVertex2i(-285, -55);
	glVertex2i(-285, -50);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-270, -80);
	glVertex2i(-270, -55);
	glVertex2i(-255, -55);
	glVertex2i(-255, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-240, -80);
	glVertex2i(-240, -55);
	glVertex2i(-225, -55);
	glVertex2i(-225, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-210, -80);
	glVertex2i(-210, -55);
	glVertex2i(-195, -55);
	glVertex2i(-195, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-180, -80);
	glVertex2i(-180, -55);
	glVertex2i(-165, -55);
	glVertex2i(-165, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-150, -80);
	glVertex2i(-150, -55);
	glVertex2i(-135, -55);
	glVertex2i(-135, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-120, -80);
	glVertex2i(-120, -55);
	glVertex2i(-105, -55);
	glVertex2i(-105, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-90, -80);
	glVertex2i(-90, -55);
	glVertex2i(-75, -55);
	glVertex2i(-75, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-60, -80);
	glVertex2i(-60, -55);
	glVertex2i(-45, -55);
	glVertex2i(-45, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-30, -80);
	glVertex2i(-30, -55);
	glVertex2i(-15, -55);
	glVertex2i(-15, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(0, -80);
	glVertex2i(0, -55);
	glVertex2i(15, -55);
	glVertex2i(15, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(30, -80);
	glVertex2i(30, -55);
	glVertex2i(45, -55);
	glVertex2i(45, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(60, -80);
	glVertex2i(60, -55);
	glVertex2i(75, -55);
	glVertex2i(75, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(90, -80);
	glVertex2i(90, -55);
	glVertex2i(105, -55);
	glVertex2i(105, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(120, -80);
	glVertex2i(120, -55);
	glVertex2i(135, -55);
	glVertex2i(135, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(150, -80);
	glVertex2i(150, -55);
	glVertex2i(165, -55);
	glVertex2i(165, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(180, -80);
	glVertex2i(180, -55);
	glVertex2i(195, -55);
	glVertex2i(195, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(210, -80);
	glVertex2i(210, -55);
	glVertex2i(225, -55);
	glVertex2i(225, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(240, -80);
	glVertex2i(240, -55);
	glVertex2i(255, -55);
	glVertex2i(255, -80);
	glEnd(); //end wood

	glBegin(GL_POLYGON); //start wood
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(270, -80);
	glVertex2i(270, -55);
	glVertex2i(285, -55);
	glVertex2i(285, -80);
	glEnd(); //end wood
}

void wheel1()
{
	glRotatef(_angle3, 0.0, 0.0, 1.0);
	glTranslatef(-180.8, -60.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 10.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void wheel2()
{
	glRotatef(_angle4, 0.0, 0.0, 1.0);
	glTranslatef(30.0, 0.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 10.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void wheel3()
{
	glRotatef(_angle4, 0.0, 0.0, 1.0);
	glTranslatef(-80.8, 0.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 12.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void wheel4()
{
	glRotatef(_angle4, 0.0, 0.0, 1.0);
	glTranslatef(-100.8, 0.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 12.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void wheel5()
{
	glRotatef(_angle4, 0.0, 0.0, 1.0);
	glTranslatef(30.8, 0.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 12.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void wheel6()
{
	glRotatef(_angle4, 0.0, 0.0, 1.0);
	glTranslatef(-130.8, 0.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 12.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void wheel7()
{
	glRotatef(_angle4, 0.0, 0.0, 1.0);
	glTranslatef(30.8, 0.0, 0.0); //Rotate about the vector (1, 2, 3)
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 200; i++)
	{
		float pi = 3.1416;
		float A = (i * 2 * pi) / 50;
		float r = 12.15;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x, y);
	}
	glEnd();
}

void trainN()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(_angle1, 0.0f, 0.0f);
	glColor3d(1, 0, 0);

	glBegin(GL_POLYGON); //start body
	glColor3f(1.0, 0.940, 0.0);
	glVertex2i(-200, -10);
	glVertex2i(-200, -60);
	glVertex2i(-140, -60);
	glVertex2i(-140, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //start bar
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-140, -60);
	glVertex2i(-140, -35);
	glVertex2i(-130, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //start light
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-140, -30);
	glVertex2i(-140, -15);
	glVertex2i(-135, -15);
	glVertex2i(-135, -30);
	glEnd();

	glBegin(GL_POLYGON); //cimny
	glColor3f(0.863, 0.078, 0.235);
	glVertex2i(-170, -10);
	glVertex2i(-170, 20);
	glVertex2i(-150, 20);
	glVertex2i(-150, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //cimny conn
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-175, 20);
	glVertex2i(-175, 25);
	glVertex2i(-145, 25);
	glVertex2i(-145, 20);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //diver room window
	glColor3f(3.0, 1.0, 0.5);
	glVertex2i(-250, -10);
	glVertex2i(-250, 30);
	glVertex2i(-210, 30);
	glVertex2i(-210, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //diver room roof
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-265, 40);
	glVertex2i(-265, 45);
	glVertex2i(-195, 45);
	glVertex2i(-195, 40);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //diver room
	glColor3f(1.000, 0.000, 0.000);
	glVertex2i(-260, -60);
	glVertex2i(-260, 40);
	glVertex2i(-200, 40);
	glVertex2i(-200, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy1 conn
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-260, -60);
	glVertex2i(-260, -50);
	glVertex2i(-280, -50);
	glVertex2i(-280, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy1 roof
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-365, 40);
	glVertex2i(-365, 45);
	glVertex2i(-275, 45);
	glVertex2i(-275, 40);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy 1 window
	glColor3f(3.0, 1.0, 0.5);
	glVertex2i(-350, -10);
	glVertex2i(-350, 30);
	glVertex2i(-290, 30);
	glVertex2i(-290, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy 1
	glColor3f(0.294, 0.000, 0.510);
	glVertex2i(-360, -60);
	glVertex2i(-360, 40);
	glVertex2i(-280, 40);
	glVertex2i(-280, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy 2 window
	glColor3f(3.0, 1.0, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
	glVertex2i(-450, -10);
	glVertex2i(-450, 30);
	glVertex2i(-390, 30);
	glVertex2i(-390, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy2 conn
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-360, -60);
	glVertex2i(-360, -50);
	glVertex2i(-380, -50);
	glVertex2i(-380, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy2 roof
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-465, 40);
	glVertex2i(-465, 45);
	glVertex2i(-375, 45);
	glVertex2i(-375, 40);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy 2
	glColor3f(0.000, 0.000, 0.502);
	glVertex2i(-460, -60);
	glVertex2i(-460, 40);
	glVertex2i(-380, 40);
	glVertex2i(-380, -60);
	glEnd(); //train middle polygon

	wheel1();
	wheel2();
	wheel3();
	wheel4();
	wheel5();
	wheel6();
	wheel7();

	glPopMatrix(); //finish car

}

void trainD()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//glRotatef(_angle1, 0.0, 0.0, 0.0);
	glTranslatef(_angle1, 0.0f, 0.0f);
	glColor3d(1, 0, 0);

	glBegin(GL_POLYGON); //start body
	glColor3f(1.0, 0.940, 0.0);
	glVertex2i(-200, -10);
	glVertex2i(-200, -60);
	glVertex2i(-140, -60);
	glVertex2i(-140, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //start bar
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-140, -60);
	glVertex2i(-140, -35);
	glVertex2i(-130, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //start light
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-140, -30);
	glVertex2i(-140, -15);
	glVertex2i(-135, -15);
	glVertex2i(-135, -30);
	glEnd();

	glBegin(GL_POLYGON); //cimny
	glColor3f(0.863, 0.078, 0.235);
	glVertex2i(-170, -10);
	glVertex2i(-170, 20);
	glVertex2i(-150, 20);
	glVertex2i(-150, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //cimny conn
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-175, 20);
	glVertex2i(-175, 25);
	glVertex2i(-145, 25);
	glVertex2i(-145, 20);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //diver room window
	glColor3f(0.663, 0.663, 0.663);
	glVertex2i(-250, -10);
	glVertex2i(-250, 30);
	glVertex2i(-210, 30);
	glVertex2i(-210, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //diver room roof
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-265, 40);
	glVertex2i(-265, 45);
	glVertex2i(-195, 45);
	glVertex2i(-195, 40);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //diver room
	glColor3f(1.000, 0.000, 0.000);
	glVertex2i(-260, -60);
	glVertex2i(-260, 40);
	glVertex2i(-200, 40);
	glVertex2i(-200, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy1 conn
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-260, -60);
	glVertex2i(-260, -50);
	glVertex2i(-280, -50);
	glVertex2i(-280, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy1 roof  
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-365, 40);
	glVertex2i(-365, 45);
	glVertex2i(-275, 45);
	glVertex2i(-275, 40);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy1 window  
	glColor3f(0.663, 0.663, 0.663);
	glVertex2i(-350, -10);
	glVertex2i(-350, 30);
	glVertex2i(-290, 30);
	glVertex2i(-290, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy 1 
	glColor3f(0.294, 0.000, 0.510);
	glVertex2i(-360, -60);
	glVertex2i(-360, 40);
	glVertex2i(-280, 40);
	glVertex2i(-280, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy1 window  
	glColor3f(0.663, 0.663, 0.663);
	glVertex2i(-450, -10);
	glVertex2i(-450, 30);
	glVertex2i(-390, 30);
	glVertex2i(-390, -10);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy2 conn  
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-360, -60);
	glVertex2i(-360, -50);
	glVertex2i(-380, -50);
	glVertex2i(-380, -60);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy2 roof  
	glColor3f(0.184, 0.310, 0.310);
	glVertex2i(-465, 40);
	glVertex2i(-465, 45);
	glVertex2i(-375, 45);
	glVertex2i(-375, 40);
	glEnd(); //car middle polygon

	glBegin(GL_POLYGON); //bogy 2 
	glColor3f(0.000, 0.000, 0.502);
	glVertex2i(-460, -60);
	glVertex2i(-460, 40);
	glVertex2i(-380, 40);
	glVertex2i(-380, -60);
	glEnd(); //car middle polygon

	wheel1();
	wheel2();
	wheel3();
	wheel4();
	wheel5();
	wheel6();
	wheel7();

	glPopMatrix(); //finish car

}
void bird() //digeraakan keyboard
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(_angle2, 0.0, 0.0);
	glColor3f(0.133, 0.545, 0.133);

	glBegin(GL_POLYGON);
	glVertex2i(-180, 160);
	glVertex2i(-180, 150);
	glVertex2i(-170, 145);
	glVertex2i(-160, 150);
	glVertex2i(-160, 160);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(-160, 150);
	glVertex2i(-160, 160);
	glVertex2i(-150, 157);
	glVertex2i(-152, 152);
	glEnd(); //end green bird

	glBegin(GL_POLYGON); //start green bird
	glColor3f(1.000, 0.000, 0.000);
	glVertex2i(-145, 155);
	glVertex2i(-150, 157);
	glVertex2i(-152, 152);
	glEnd(); //end green bird

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(-180, 160);
	glVertex2i(-180, 150);
	glVertex2i(-190, 153);
	glVertex2i(-195, 160);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(-180, 160);
	glVertex2i(-195, 160);
	glVertex2i(-190, 164);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.545, 0.271, 0.075);
	glVertex2i(-170, 145);
	glVertex2i(-180, 150);
	glVertex2i(-185, 142);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.133, 0.545, 0.133);
	glVertex2i(-160, 160);
	glVertex2i(-170, 175);
	glVertex2i(-185, 180);
	glVertex2i(-180, 160);
	glEnd();

	glBegin(GL_POLYGON); //start green bird
	glColor3f(0.180, 0.545, 0.341);
	glVertex2i(-185, 180);
	glVertex2i(-180, 178.33);
	glVertex2i(-190, 170);
	glEnd();

	glPopMatrix(); //finish bird
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawWindowN();
	trainN();
	Railline();
	platfrm();
	StatnNight();
	tree();
	bird();
	bird2m();
	cloud();
	cloud2();
	cloud3();
	moon();
	background();

	glutSwapBuffers();

}

void drawSceneDay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawWindow();
	trainD();
	Railline();
	platfrm();
	Statn();
	tree();
	bird();
	bird2m();
	cloud();
	cloud2();
	cloud3();
	backgroundDay();

	glutSwapBuffers();
}

void update(int value) {
	if (speed > 1 || speed < 0)
	{
		speed = 0.0f;
	}
	_angle1 += speed;

	if (_angle1 > 800) {
		_angle1 -= 1000;
	}
	if (speed2 > 1 || speed2 < 0)
	{
		speed2 = 0.0f;
	}
	_angle2 += speed2;

	if (_angle2 > 500) {
		_angle2 -= 800;
	}
	//Tell GLUT to call update again in 20 milliseconds
	glutTimerFunc(20, update, 0);
}

void menu(int id)
{
	switch (id)
	{
	case 1:
		glutIdleFunc(drawSceneDay);
		break;
	case 2:
		glutIdleFunc(drawScene);
		break;
	case 3:
		exit(0);
	}
}

void specialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		speed += 0.05f;
		update(0);
		break;
	case GLUT_KEY_DOWN:
		speed -= 0.05f;
		update(0);
		break;
	case GLUT_KEY_RIGHT:
		speed2 += 0.05f;
		update(0);
		break;
	case GLUT_KEY_LEFT:
		speed2 -= 0.05f;
		update(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1350, 700);
	glutCreateWindow("Train Animation");
	glutDisplayFunc(drawSceneDay);

	glutSpecialFunc(specialKeys);
	initRendering();
	glutIdleFunc(idle);
	init();

	glutKeyboardFunc(handleKeypress);
	glutTimerFunc(20, update, 0);

	glutCreateMenu(menu);
	glutAddMenuEntry("Day", 1);
	glutAddMenuEntry("Night", 2);
	glutAddMenuEntry("Quit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}

