#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "objects.h"
#include "matrix.h"
#include "trackball.h"
#include <stdio.h>

double pos[3] = { 0.0, 1.2, 0.0 }; /* 移動 */
double speed = 0.05; // 移動速度
double move[3] = { 0.0, 0.0, 0.0 };
int keyMove = 0; // key
int freeMode = 0; // 移動モード
double rot[2];

double smokePos[400][3]; // 煙座標データ
double smokeTheta = 0;

void init(void) {
	// 背景
	//glClearColor(0.0, 0.6f, 0.0, 1.0); //gb
	glClearColor(0.8, 0.8, 0.8, 1.0);

	glEnable(GL_DEPTH_TEST);

	// culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// fog
	glEnable(GL_FOG);
	float fogColor[4] = { 0.8, 0.8, 0.8, 1.0 };
	float fogDensity = 0.08f;
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, fogDensity);
	//glFogf(GL_FOG_START, 100.0);
	//glFogf(GL_FOG_END, 1000.0);

	glAlphaFunc(GL_GREATER, 0.5);

	// テクスチャ初期化
	initTextures();

	// 視点
	pos[0] = 0.0;
	pos[1] = 1.2;
	pos[2] = 0.0;
	glLoadIdentity();

	// トラックボール初期化
	trackballInit();

	// smoke初期化
	smokeInit(2);
}

void idle(void) {
	glutPostRedisplay();
}

void getRot(double tq[2]) {
	rot[0] = tq[0] * M_PI / 180;
	rot[1] = tq[1] * M_PI / 180;
}

void display(void) {
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* モデルビュー変換行列の保存 */
	glPushMatrix();

	/* トラックボール処理による回転 */
	getRot(trackballRotation());

	/* 視点の移動 */
	gluLookAt(pos[0], pos[1], pos[2], pos[0], pos[1], pos[2] - 1, 0.0, 1.0, 0.0);

	/* 図形の描画 */

	// 階段
	stairs(pos[2]);

	// 鳥居
	toriis(pos[2]);

	// 煙
	smokes(pos[2], smokeTheta);
	smokeTheta += 0.002;

	/* モデルビュー変換行列の復帰 */
	glPopMatrix();

	glutSwapBuffers();

	// 移動
	move[0] = 0.0;
	move[1] = 0.0;
	move[2] = 0.0;
	if (freeMode) {
		if (keyMove & 1) {
			move[0] += speed * sin(rot[0]) * cos(rot[1]);
			move[1] -= speed * sin(rot[1]);
			move[2] -= speed * cos(rot[0]) * cos(rot[1]);
		}
		if (keyMove & 2) {
			move[0] -= speed * sin(rot[0]) * cos(rot[1]);
			move[1] += speed * sin(rot[1]);
			move[2] += speed * cos(rot[0]) * cos(rot[1]);
		}
		if (keyMove & 4) {
			move[0] -= speed * cos(rot[0]) * cos(rot[1]);
			move[1] -= speed * sin(rot[1]);
			move[2] -= speed * sin(rot[0]) * cos(rot[1]);
		}
		if (keyMove & 8) {
			move[0] += speed * cos(rot[0]) * cos(rot[1]);
			move[1] -= speed * sin(rot[1]);
			move[2] += speed * sin(rot[0]) * cos(rot[1]);
		}
		if (keyMove & 16) {
			move[1] += speed;
		}
		if (keyMove & 32) {
			move[1] -= speed;
		}
	} else {
		if (keyMove & 1) {
			move[1] += speed * cos(rot[0]);
			move[2] -= speed * cos(rot[0]);
		}
		if (keyMove & 2) {
			move[1] -= speed * cos(rot[0]);
			move[2] += speed * cos(rot[0]);
		}
		if (keyMove & 4) {
			move[1] += speed * sin(rot[0]);
			move[2] -= speed * sin(rot[0]);
		}
		if (keyMove & 8) {
			move[1] -= speed * sin(rot[0]);
			move[2] += speed * sin(rot[0]);
		}
	}
	mAdd(3, pos, move, pos);
}

void resize(int w, int h) {
	/* トラックボールする範囲 */
	trackballRegion(w, h);

	/* ウィンドウ全体をビューポートにする */
	glViewport(0, 0, w, h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (double)w / (double)h, 0.01, 100.0);

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			/* トラックボール開始 */
			trackballStart(x, y);
		}
		else {
			/* トラックボール停止 */
			trackballStop(x, y);
		}
	default:
		break;
	}
}

void motion(int x, int y) {
	/* トラックボール移動 */
	trackballMotion(x, y);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  /* '\033' は ESC の ASCII コード */
		exit(0);
		break;
	case 'w': // 前進始め
		keyMove |= 1;
		break;
	case 's': // 後退始め
		keyMove |= 2;
		break;
	case 'a': // 左始め
		keyMove |= 4;
		break;
	case 'd': // 右始め
		keyMove |= 8;
		break;
	case ' ': // 上始め
		keyMove |= 16;
		break;
	case 'c': // 下始め
		keyMove |= 32;
		break;
	case 'f': // フリーモードへ
		freeMode = 1;
		break;
	case 'r': // 位置・モードリセット
		freeMode = 0;
		init();
		break;
	default:
		break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': // 前進終わり
		keyMove &= ~1;
		break;
	case 's': // 後退終わり
		keyMove &= ~2;
		break;
	case 'a': // 左終わり
		keyMove &= ~4;
		break;
	case 'd': // 右終わり
		keyMove &= ~8;
		break;
	case ' ': // 上終わり
		keyMove &= ~16;
		break;
	case 'c': // 下終わり
		keyMove &= ~32;
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[]) {
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(960, 720);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
	return 0;
}