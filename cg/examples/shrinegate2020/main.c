#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "objects.h"
#include "matrix.h"
#include "trackball.h"
#include <stdio.h>

double pos[3] = { 0.0, 1.2, 0.0 }; /* �ړ� */
double speed = 0.05; // �ړ����x
double move[3] = { 0.0, 0.0, 0.0 };
int keyMove = 0; // key
int freeMode = 0; // �ړ����[�h
double rot[2];

double smokePos[400][3]; // �����W�f�[�^
double smokeTheta = 0;

void init(void) {
	// �w�i
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

	// �e�N�X�`��������
	initTextures();

	// ���_
	pos[0] = 0.0;
	pos[1] = 1.2;
	pos[2] = 0.0;
	glLoadIdentity();

	// �g���b�N�{�[��������
	trackballInit();

	// smoke������
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

	/* ���f���r���[�ϊ��s��̕ۑ� */
	glPushMatrix();

	/* �g���b�N�{�[�������ɂ���] */
	getRot(trackballRotation());

	/* ���_�̈ړ� */
	gluLookAt(pos[0], pos[1], pos[2], pos[0], pos[1], pos[2] - 1, 0.0, 1.0, 0.0);

	/* �}�`�̕`�� */

	// �K�i
	stairs(pos[2]);

	// ����
	toriis(pos[2]);

	// ��
	smokes(pos[2], smokeTheta);
	smokeTheta += 0.002;

	/* ���f���r���[�ϊ��s��̕��A */
	glPopMatrix();

	glutSwapBuffers();

	// �ړ�
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
	/* �g���b�N�{�[������͈� */
	trackballRegion(w, h);

	/* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
	glViewport(0, 0, w, h);

	/* �����ϊ��s��̐ݒ� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (double)w / (double)h, 0.01, 100.0);

	/* ���f���r���[�ϊ��s��̐ݒ� */
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			/* �g���b�N�{�[���J�n */
			trackballStart(x, y);
		}
		else {
			/* �g���b�N�{�[����~ */
			trackballStop(x, y);
		}
	default:
		break;
	}
}

void motion(int x, int y) {
	/* �g���b�N�{�[���ړ� */
	trackballMotion(x, y);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
		exit(0);
		break;
	case 'w': // �O�i�n��
		keyMove |= 1;
		break;
	case 's': // ��ގn��
		keyMove |= 2;
		break;
	case 'a': // ���n��
		keyMove |= 4;
		break;
	case 'd': // �E�n��
		keyMove |= 8;
		break;
	case ' ': // ��n��
		keyMove |= 16;
		break;
	case 'c': // ���n��
		keyMove |= 32;
		break;
	case 'f': // �t���[���[�h��
		freeMode = 1;
		break;
	case 'r': // �ʒu�E���[�h���Z�b�g
		freeMode = 0;
		init();
		break;
	default:
		break;
	}
}

void keyUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': // �O�i�I���
		keyMove &= ~1;
		break;
	case 's': // ��ޏI���
		keyMove &= ~2;
		break;
	case 'a': // ���I���
		keyMove &= ~4;
		break;
	case 'd': // �E�I���
		keyMove &= ~8;
		break;
	case ' ': // ��I���
		keyMove &= ~16;
		break;
	case 'c': // ���I���
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