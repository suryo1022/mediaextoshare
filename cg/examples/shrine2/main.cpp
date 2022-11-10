#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include <GL/freeglut.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#include "texture.h"
#include "object.h"
//#include "GLMetaseq.h"

#define WIDTH 640
#define HEIGHT 480

//MQO_MODEL model;

//ライトの位置
//GLfloat lightpos[] = { 30.0, 40.0, 250.0, 1.0 };

float view_x, view_y, view_z, rx, ry;

#define Maxparticles 128

#define Firenum 4

int gamestatus = 1;

int rv = 0; //view回転
int rs = 0; //回転スイッチ

int fr = 0; //floor回転
int frs = 0; //floorスイッチ

int windowsizew;
int windowsizeh;

GLdouble ex = 0., ey = .3, ez = 0., cx, cy, cz; //初期状態設定
GLdouble rf = 0.;

GLdouble firex[Firenum] = { 0 }, firey[Firenum] = { 0 }, firez[Firenum] = { 0 };

int ox = 0, oz = 0, oa = 0;

double ltarget[2] = { 0 };

GLfloat rockColor[] = { .8, .8, .75, 1. };

double rad = 1.;

double pi;
double ort;

double sinp8;
double cosp8;

GLfloat lightpos[] = { 0., 0., 0., 1. };

GLfloat light0Color[][4] = {
	{ .5, 0., 0., 1. },
	{ .4, .4, .4, 1. }
};

GLfloat tileColor[][4] = {
	{ .7, .7, .7, 1. },
	{ .2, .2, .2, 1. }
};

GLfloat distance[] = { 0., 0., 1. };

GLdouble firebp[Maxparticles][2]; //x,zだけ
GLdouble firemv[256][2]; //x,zだけ
GLfloat firebc[4] = { 1., 1., 0., 1. };
GLfloat firedc[256][2]; //g, aだけ

typedef struct Firep {
	double life;
	GLfloat color[4];
	GLdouble pos[3];


} firep;

firep firepdata[Maxparticles];

void setData(void) {
	int i;
	pi = 3.14;
	ort = 1. / sqrt(2.);

	sinp8 = sqrt(2. - sqrt(2.)) / 2.;
	cosp8 = sqrt(2. + sqrt(2.)) / 2.;

	lightpos[1] = rad;

	srand((unsigned)time(NULL));
	for (i = 0; i < Maxparticles; i++) {
		double rbp = (double)rand() / RAND_MAX * .08;
		double tbp = (double)rand() * 2 * pi / (RAND_MAX + 1.);
		firebp[i][0] = (GLdouble)rbp * sin(tbp);
		firebp[i][1] = (GLdouble)rbp * cos(tbp);
	}

	for (i = 0; i < 256; i++) {
		firemv[i][0] = (GLdouble)(.04 * rand() / RAND_MAX - .02);
		//y+=.02
		firemv[i][1] = (GLdouble)(.04 * rand() / RAND_MAX - .02);
		firedc[i][1] = (GLfloat)((fabs(firemv[i][0]) + fabs(firemv[i][1])) / 2. + .02);
		firedc[i][0] = (GLfloat)(firedc[i][1] / 6. + .1);
	}

	for (i = 0; i < Maxparticles; i++) {
		firepdata[i].life = (double)rand() / RAND_MAX;
		firepdata[i].color[0] = firebc[0];
		firepdata[i].color[1] = firebc[1];
		firepdata[i].color[2] = firebc[2];
		firepdata[i].color[3] = firebc[3];
		firepdata[i].pos[0] = firebp[i][0];
		firepdata[i].pos[1] = .3;
		firepdata[i].pos[2] = firebp[i][1];
	}

	//自動生成したい
	firex[0] = 2.*rad; firez[0] = 2.*rad;
	firex[1] = 2.*rad; firez[1] = -2.*rad;
	firex[2] = -2.*rad; firez[2] = -2.*rad;
	firex[3] = -2.*rad; firez[3] = 2.*rad;
}



double radians(double deg) {
	return deg * 3.14 / 180;
}

void idle(void)
{
	glutPostRedisplay();
}

static double width, height;
void resize(int w, int h) {
	width = (double)w;
	height = (double)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-w/200,w/200,-h/200,h/200,-1,1);
	//視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
	gluPerspective(30.0, (double)w / (double)h, 1.0, 500.0);

	glMatrixMode(GL_MODELVIEW);


}
//ドラッグされているか
int draged;
//視線の中心
int ry_center;
//マウスがドラッグされたら呼ばれる
void mouseDraged(int x, int y) {
	draged = 1;

}
//マウスのx座標から、横方向の回転に変換する
double xToRy(int x) {
	return (x - width / 2) / (float)width * 180 - ry_center;
}
//マウスのy座標から、縦方向の回転に変換する
double yToRx(int y) {
	return (y - height / 2) / (float)height * 90;
}
//マウスがクリックされたら呼ばれる
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (draged == 1) {//ドラッグが解除されたら
			ry_center += xToRy(x) - ry;//視線の中心をズラす。

			printf("drag up! ryc = %d", ry_center);
			draged = 0;
		}
	}

}
//マウスが動いたら
void mouseMoved(int x, int y) {
	ry = xToRy(x);
	rx = yToRx(y);

}
//キーボードがおされたら
void keyboard(unsigned char key, int x, int y) {
	float step = 1;

	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  // '\033' は ESC の ASCII コード 
		exit(0);
	case 'a':
	case 'A':
		view_z -= step*sin(radians(ry));
		view_x -= step*cos(radians(ry));
		break;

	case 'd':
	case 'D':
		view_z += step*sin(radians(ry));
		view_x += step*cos(radians(ry));
		break;

	case 'w':
	case 'W':
		view_z -= step*cos(radians(ry));
		view_x += step*sin(radians(ry));
		break;

	case 's':
	case 'S':
		view_z += step*cos(radians(ry));
		view_x -= step*sin(radians(ry));
		break;

	case 'r':
	case 'R':
		view_y += step;
		break;

	case 'f':
	case 'F':
		view_y -= step;
		break;

	default:
		break;
	}

	glutPostRedisplay();

}
//特殊キーが押されたら
void specialKey(int key, int x, int y) {
	glutPostRedisplay();
}

void Init() {
	glClearColor(0.32, 0.75, 0.88, 1.0);
	glEnable(GL_DEPTH_TEST);
	//	glCullFace(GL_BACK);
	//	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	initTexture();
}

void display(void)
{
	//設定
	
	{
//		static GLfloat light0pos[] = { 0.0, 3.0, -5.0, 1.0 };
		static GLfloat light0pos[] = { 0, 50.0, 50.0, 1.0 };
		static GLfloat light1pos[] = { -50.0, 50.0, 0, 1.0 };
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glMatrixMode(GL_MODELVIEW);

		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();

		/* 視点位置と視線方向 */

	
		gluLookAt(0, 2, 0, 0, 2, -1, 0.0, 1.0, 0.0);
		
	//	gluLookAt(-view_x, view_y, -view_z, -view_x+3, view_y+4, view_z-5, 0.0, 1.0, 0.0);
		glRotated(rx, 1, 0, 0);
		glRotated(ry, 0, 1, 0);

		//視点を移動

		glTranslated(-view_x, view_y, -view_z);

	//	 光源の位置設定
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	}
	
	int i;

	//設置
	{
		//地面
		glPushMatrix();
		glTranslatef(20, -0.251, -20);
		ground();
		back();
		glPopMatrix();
		//丘
		glPushMatrix();
		glTranslatef(0.4 * 75, -0.25, -40);
		hill();
		glPopMatrix();

		//鳥居
		int i;
		glPushMatrix();
		//	mqoCallModel(model);
		glTranslatef(0, 0, -10);
		for (i = 249; i >= 0; i--) {
			if (i <= 90)
				tori(i, 0, i, i);
			else if (i < 180)
				tori(i - 90, 0, i - 90, i);
			else
				tori(0, i, 0, i);

		}
		glPopMatrix();
		//樹と池
		glPushMatrix();
		glTranslatef(-3, 0, -10);
		branch();
		glTranslatef(-5, -0.25, -2);
		lake(80, 4.5, 6, 3, 3);
//		glTranslatef(0.5, 0, -1);
//		lake(80, 4.5, 6, 3, 3);
		glPopMatrix();
		branch();

		
	}
	glutSwapBuffers();

	switch (rs) {
	case 1:
		if (++rv >= 360) rv = 0;
		break;
	case -1:
		if (--rv <= 0) rv = 360;
		break;
	default:
		break;
	}

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	//	mqoInit();
	//	model = mqoCreateModel("stone.mqo", 0.1);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseMoved);
	glutMotionFunc(mouseDraged);
//	glutPassiveMotionFunc(motion);
//	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
//	glutSpecialFunc(skeyboard);
	glutSpecialFunc(specialKey);
	Init();
	glutMainLoop();
	return 0;
}
