#include <GL/freeglut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "texture.h"

GLfloat Red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat Gray[] = { 0.30, 0.30, 0.30, 1.0 };
GLfloat Black[] = { 0, 0, 0, 1.0 };
GLfloat Green[] = { 0.8, 0, 0.05, 1.0 };
GLfloat Brown[] = { 0.5, 0.3, 0.1, 1.0 };
GLfloat Blue[] = { 0, 0, 1, 1 };
GLfloat Ground[] = { 0.6, 0.3, 0.05 , 1.0 };

#define TEX_W1 256
#define TEX_H1 256
#define TEX_W2 256
#define TEX_H2 256
#define TEX_W3 341
#define TEX_H3 256
#define TEX_W4 342
#define TEX_H4 256
#define TEX_W5 276
#define TEX_H5 183
#define TEX_W6 560
#define TEX_H6 372

GLuint texid_1, texid_2,texid_3, texid_4,texid_5, texid_6;
static const char texture1[] = "/home1/y2014/k1410159/cg/temple/stones_256x256.raw";
static const char texture2[] = "/home1/y2014/k1410159/cg/temple/shibahu_256x256.raw";
static const char texture3[] = "/home1/y2014/k1410159/cg/temple/redleaf_341x256.raw";
static const char texture4[] = "/home1/y2014/k1410159/cg/temple/lake_342x256.raw";
static const char texture5[] = "/home1/y2014/k1410159/cg/temple/ground_276x183.raw";
static const char texture6[] = "/home1/y2014/k1410159/cg/temple/back_560x372.raw";

void initTexture() {
	/* �e�N�X�`���̓ǂݍ��݂Ɏg���z�� */
	GLubyte texture_buf1[TEX_H1][TEX_W1][4];
	GLubyte texture_buf2[TEX_H2][TEX_W2][4];
	GLubyte texture_buf3[TEX_H3][TEX_W3][4];
	GLubyte texture_buf4[TEX_H4][TEX_W4][4];
	GLubyte texture_buf5[TEX_H5][TEX_W5][4];
	GLubyte texture_buf6[TEX_H6][TEX_W6][4];
	FILE *fp;

	/* �e�N�X�`���摜(1����)�̓ǂݍ��� */
	if ((fp=fopen(texture1, "rb")) != NULL) {
		fread(texture_buf1, sizeof texture_buf1, 1, fp);
		fclose(fp);
	}
	else {
		perror(texture1);
	}
	/* �e�N�X�`���摜(2����)�̓ǂݍ��� */
	if ((fp=fopen(texture2, "rb")) != NULL) {
		fread(texture_buf2, sizeof texture_buf2, 1, fp);
		fclose(fp);
	}
	else {
		perror(texture2);
	}
	/* �e�N�X�`���摜(3����)�̓ǂݍ��� */
	if ((fp=fopen(texture3, "rb")) != NULL) {
		fread(texture_buf3, sizeof texture_buf3, 1, fp);
		fclose(fp);
	}
	else {
		perror(texture3);
	}
	/* �e�N�X�`���摜(4����)�̓ǂݍ��� */
	if ((fp=fopen(texture4, "rb")) != NULL) {
		fread(texture_buf4, sizeof texture_buf4, 1, fp);
		fclose(fp);
	}
	else {
		perror(texture4);
	}
	/* �e�N�X�`���摜(5����)�̓ǂݍ��� */
	if ((fp=fopen(texture5, "rb")) != NULL) {
		fread(texture_buf5, sizeof texture_buf5, 1, fp);
		fclose(fp);
	}
	else {
		perror(texture5);
	}
	/* �e�N�X�`���摜(6����)�̓ǂݍ��� */
	if ((fp=fopen(texture6, "rb")) != NULL) {
		fread(texture_buf6, sizeof texture_buf6, 1, fp);
		fclose(fp);
	}
	else {
		perror(texture6);
	}

	////////// 1���ڂ̃e�N�X�`���̓ǂݍ��� ////////////
	glGenTextures(1, &texid_1);  // �e�N�X�`��ID�𐶐�
	glBindTexture(GL_TEXTURE_2D, texid_1);  // ���������e�N�X�`��ID�ɐ؂�ւ���
	/* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	/* �e�N�X�`���̊��蓖�� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEX_W1, TEX_H1,  // �c���T�C�Y�̓e�N�X�`��1�p
		GL_RGBA, GL_UNSIGNED_BYTE, texture_buf1);
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	/* �e�N�X�`���� */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);  // �f�t�H���g�Ƀe�N�X�`��ID�ɐ؂�ւ���
	 ////////////////////////////////////////////////////	

	////////// 2���ڂ̃e�N�X�`���̓ǂݍ��� ////////////
	glGenTextures(1, &texid_2);  // �e�N�X�`��ID�𐶐�
	glBindTexture(GL_TEXTURE_2D, texid_2);  // ���������e�N�X�`��ID�ɐ؂�ւ���
	/* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	/* �e�N�X�`���̊��蓖�� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEX_W2, TEX_H2,  // �c���T�C�Y�̓e�N�X�`��1�p
		GL_RGBA, GL_UNSIGNED_BYTE, texture_buf2);
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	/* �e�N�X�`���� */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);  // �f�t�H���g�Ƀe�N�X�`��ID�ɐ؂�ւ���
	  ////////////////////////////////////////////////////	
	
	////////// 3���ڂ̃e�N�X�`���̓ǂݍ��� ////////////
	glGenTextures(1, &texid_3);  // �e�N�X�`��ID�𐶐�
	glBindTexture(GL_TEXTURE_2D, texid_3);  // ���������e�N�X�`��ID�ɐ؂�ւ���
	/* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	/* �e�N�X�`���̊��蓖�� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEX_W3, TEX_H3,  // �c���T�C�Y�̓e�N�X�`��1�p
		GL_RGBA, GL_UNSIGNED_BYTE, texture_buf3);
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	/* �e�N�X�`���� */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);  // �f�t�H���g�Ƀe�N�X�`��ID�ɐ؂�ւ���
	  ////////////////////////////////////////////////////	

	////////// 4���ڂ̃e�N�X�`���̓ǂݍ��� ////////////
	glGenTextures(1, &texid_4);  // �e�N�X�`��ID�𐶐�
	glBindTexture(GL_TEXTURE_2D, texid_4);  // ���������e�N�X�`��ID�ɐ؂�ւ���
	/* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	/* �e�N�X�`���̊��蓖�� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEX_W4, TEX_H4,  // �c���T�C�Y�̓e�N�X�`��1�p
		GL_RGBA, GL_UNSIGNED_BYTE, texture_buf4);
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	/* �e�N�X�`���� */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);  // �f�t�H���g�Ƀe�N�X�`��ID�ɐ؂�ւ���
	  ////////////////////////////////////////////////////	

	////////// 5���ڂ̃e�N�X�`���̓ǂݍ��� ////////////
	glGenTextures(1, &texid_5);  // �e�N�X�`��ID�𐶐�
	glBindTexture(GL_TEXTURE_2D, texid_5);  // ���������e�N�X�`��ID�ɐ؂�ւ���
	/* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	/* �e�N�X�`���̊��蓖�� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEX_W5, TEX_H5,  // �c���T�C�Y�̓e�N�X�`��1�p
		GL_RGBA, GL_UNSIGNED_BYTE, texture_buf5);
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	/* �e�N�X�`���� */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);  // �f�t�H���g�Ƀe�N�X�`��ID�ɐ؂�ւ���
	  ////////////////////////////////////////////////////	

	////////// 6���ڂ̃e�N�X�`���̓ǂݍ��� ////////////
	glGenTextures(1, &texid_6);  // �e�N�X�`��ID�𐶐�
	glBindTexture(GL_TEXTURE_2D, texid_6);  // ���������e�N�X�`��ID�ɐ؂�ւ���
	/* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	/* �e�N�X�`���̊��蓖�� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, TEX_W6, TEX_H6,  // �c���T�C�Y�̓e�N�X�`��1�p
		GL_RGBA, GL_UNSIGNED_BYTE, texture_buf6);
	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	/* �e�N�X�`���� */
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);  // �f�t�H���g�Ƀe�N�X�`��ID�ɐ؂�ւ���
	  ////////////////////////////////////////////////////

#if 0
	  /* ��������F�̐ݒ� */
	static const GLfloat blend[] = { 0.0, 1.0, 0.0, 1.0 };
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, blend);
#endif

	/* �A���t�@�e�X�g�̔�r�֐� */
	glAlphaFunc(GL_GREATER, 0.5);
}

void back(){
	static const GLfloat color[] = { 1, 1, 1, 1.0 };  /* �ގ� (�F) */
										  //255,82,52
	  /* �ގ��̐ݒ� */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	/* �A���t�@�e�X�g�J�n */
	glEnable(GL_ALPHA_TEST);
	/* �e�N�X�`���}�b�s���O�J�n */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid_6);  // �e�N�X�`��ID=1���w��
	glPushMatrix();
	glTranslatef(50,0,-50);
	/* �P���̂S�p�`��`�� */
	glNormal3d(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(0, 0, 0);
	glTexCoord2d(1.0, 0);
	glVertex3d(0, 60, 0);
	glTexCoord2d(0, 0.0);
	glVertex3d(0, 60, 100);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(0, 0, 100);
	glEnd();
	glPopMatrix();

	glTranslatef(50,0,-50);
	/* �P���̂S�p�`��`�� */
	glNormal3d(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(0, 0, 0);
	glTexCoord2d(1.0, 0);
	glVertex3d(0, 60, 0);
	glTexCoord2d(0, 0.0);
	glVertex3d(-100, 60, 0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(-100, 0, 0);
	glEnd();
	glPopMatrix();
}

void ground() {
	static const GLfloat color[] = { 1, 1, 1, 1.0 };  /* �ގ� (�F) */
										  //255,82,52
	  /* �ގ��̐ݒ� */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	/* �A���t�@�e�X�g�J�n */
	glEnable(GL_ALPHA_TEST);
	/* �e�N�X�`���}�b�s���O�J�n */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid_5);  // �e�N�X�`��ID=1���w��
	int i, j;
	for (i = -50; i<50; i++) {
		for (j = -50; j<50; j++) {
			glPushMatrix();
			glTranslatef(i, 0, j);
			/* �P���̂S�p�`��`�� */
			glNormal3d(0.0, 0.0, 1.0);
			glBegin(GL_QUADS);
			glTexCoord2d(0.0, 1.0);
			glVertex3d(0, 0, 0);
			glTexCoord2d(1.0, 1.0);
			glVertex3d(1.0, 0, 0);
			glTexCoord2d(1.0, 0.0);
			glVertex3d(1.0, 0, 1.0);
			glTexCoord2d(0.0, 0.0);
			glVertex3d(0, 0, 1.0);
			glEnd();
			glPopMatrix();
		}
	}
	//	glBindTexture(GL_TEXTURE_2D, texid_1);  // �e�N�X�`��ID���f�t�H���g�ɖ߂�

}
void cylinder(float radius, float height, int sides)
{
	double pi = 3.1415;
	//���
	glNormal3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	double i;
	for (i = 0; i < sides; i++) {
		double t = pi * 2 / sides * (double)i;
		glVertex3d(radius * cos(t), height, radius * sin(t));
	}
	glEnd();
	//����
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= sides; i = i + 1) {
		double t = i * 2 * pi / sides;
		glNormal3f((GLfloat)cos(t), 0.0, (GLfloat)sin(t));
		glVertex3f((GLfloat)(radius*cos(t)), -height, (GLfloat)(radius*sin(t)));
		glVertex3f((GLfloat)(radius*cos(t)), height, (GLfloat)(radius*sin(t)));
	}
	glEnd();
	//����
	glNormal3d(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
	for (i = sides; i >= 0; --i) {
		double t = pi * 2 / sides * (double)i;
		glVertex3d(radius * cos(t), -height, radius * sin(t));
	}
	glEnd();
}
void stair(float width, float height, float depth)
{
	static const GLfloat color[] = { 1.0, 1, 1, 1.0 };  /* �ގ� (�F) */
														/* �ގ��̐ݒ� */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	/* �A���t�@�e�X�g�J�n */
	glEnable(GL_ALPHA_TEST);
	/* �e�N�X�`���}�b�s���O�J�n */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid_1);  // �e�N�X�`��ID=1���w��

	glBegin(GL_QUADS);
	//�O
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(width / 2, height / 2, depth / 2);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(-width / 2, height / 2, depth / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(-width / 2, -height / 2, depth / 2);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(width / 2, -height / 2, depth / 2);
	//��
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(width / 2, height / 2, depth / 2);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(width / 2, height / 2, -depth / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(width / 2, -height / 2, -depth / 2);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(width / 2, -height / 2, depth / 2);
	//�E
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(-width / 2, height / 2, -depth / 2);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(-width / 2, height / 2, depth / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(-width / 2, -height / 2, depth / 2);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(-width / 2, -height / 2, -depth / 2);
	//��
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(width / 2, height / 2, -depth / 2);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(-width / 2, height / 2, -depth / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(-width / 2, -height / 2, -depth / 2);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(width / 2, -height / 2, -depth / 2);
	//��
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(width / 2, height / 2, depth / 2);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(-width / 2, height / 2, depth / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(-width / 2, height / 2, -depth / 2);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(width / 2, height / 2, -depth / 2);
	//��
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2d(0.0, 1.0);
	glVertex3d(width / 2, -height / 2, depth / 2);
	glTexCoord2d(1.0, 1.0);
	glVertex3d(-width / 2, -height / 2, depth / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex3d(-width / 2, -height / 2, -depth / 2);
	glTexCoord2d(0.0, 0.0);
	glVertex3d(width / 2, -height / 2, -depth / 2);
	glEnd();
}
void cuboid(float width, float height, float depth)
{
	glBegin(GL_QUADS);
	//�O
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	//��
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, depth / 2);
	//�E
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	//��
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(width / 2, height / 2, -depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	//��
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, depth / 2);
	glVertex3f(-width / 2, height / 2, -depth / 2);
	glVertex3f(width / 2, height / 2, -depth / 2);
	//��
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, -height / 2, depth / 2);
	glVertex3f(-width / 2, -height / 2, -depth / 2);
	glVertex3f(width / 2, -height / 2, -depth / 2);
	glEnd();
}
void cone(float r, float h1, float h2, float thetah, float theta1, float theta2) {
	glNormal3d(-cos(thetah), r / h1, sin(thetah));
	glVertex3d(0, h1, 0);//���_
	glNormal3d(-cos(theta1), r / h1, sin(theta1));
	glVertex3d(-r*cos(theta1), h2, r*sin(theta1));
	glNormal3d(-cos(theta2), r / h1, sin(theta2));
	glVertex3d(-r*cos(theta2), h2, r*sin(theta2));
}

void leaf(float r, float h1, float h2, float thetah, float theta1, float theta2) {
	static const GLfloat color[] = { 1, 1, 1, 1.0 };  /* �ގ� (�F) */
	  //255,82,52
	  /* �ގ��̐ݒ� */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	/* �A���t�@�e�X�g�J�n */
	glEnable(GL_ALPHA_TEST);
	/* �e�N�X�`���}�b�s���O�J�n */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid_3);  // �e�N�X�`��ID=1���w��
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glNormal3d(-cos(thetah), r / h1, sin(thetah));
	glTexCoord2d(0.5, 0);
	glVertex3d(0, h1, 0);//���_

	glNormal3d(-cos(theta1), r / h1, sin(theta1));
	glTexCoord2d(1, 1);
	glVertex3d(-r*cos(theta1), h2, r*sin(theta1));

	glNormal3d(-cos(theta2), r / h1, sin(theta2));
	glTexCoord2d(0, 1);
	glVertex3d(-r*cos(theta2), h2, r*sin(theta2));
	glEnd();
	glPopMatrix();
}
void frustum(float radius1, float radius2, float height, int sides) {
	static const GLfloat color[] = { 1, 0.4, 0.2, 1.0 };  /* �ގ� (�F) */
	  //255,82,52
	  /* �ގ��̐ݒ� */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	/* �A���t�@�e�X�g�J�n */
	glEnable(GL_ALPHA_TEST);
	/* �e�N�X�`���}�b�s���O�J�n */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid_2);  // �e�N�X�`��ID=1���w��

	double pi = 3.1415;
	//���
	glNormal3d(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	double i;
	for (i = 0; i < sides; i++) {
		double t = pi * 2 / sides * (double)i;
		glVertex3d(radius2 * cos(t), height, radius2 * sin(t));
	}
	glEnd();
	//����
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= sides; i = i + 1) {
		double t = i * 2 * pi / sides;
		glTexCoord2d(0.5,0);
		glNormal3f((GLfloat)cos(t), 0.0, (GLfloat)sin(t));
		glTexCoord2d(1,1);		
		glVertex3f((GLfloat)(radius1*cos(t)), 0, (GLfloat)(radius1*sin(t)));
		glTexCoord2d(0,1);
		glVertex3f((GLfloat)(radius2*cos(t)), height, (GLfloat)(radius2*sin(t)));
	}
	glEnd();
	//����
	glNormal3d(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
	for (i = sides; i >= 0; --i) {
		double t = pi * 2 / sides * (double)i;
		glVertex3d(radius1 * cos(t), 0, radius1 * sin(t));
	}
	glEnd();
}
//��
void branch() {
	int i, j, N = 5;
	float r = (float)0.2, h = 2;//���a�ƍ���
	float r2 = 4 * r;

	glPushMatrix();
	/*�������̉~����`��*/
	glBegin(GL_TRIANGLES);

	for (i = 0; i <= N; i++) {
		float theta1 = (float)i / N * 2 * 3.14;
		float theta2 = (float)(i + 1) / N * 2 * 3.14;
		float thetah = ((float)i + 0.5) / N * 2 * 3.14;
		//��
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Brown);
		cone(r, 2, 0, thetah, theta1, theta2);
	}
	glEnd();

	for (i = 0; i <= N; i++) {
		float theta1 = (float)i / N * 2 * 3.14;
		float theta2 = (float)(i + 1) / N * 2 * 3.14;
		float thetah = ((float)i + 0.5) / N * 2 * 3.14;
		//��
		leaf(r2, 2, 1.2, thetah, theta1, theta2);
		leaf(r2, 2, 0.6, thetah, theta1, theta2);
	}	

	glPopMatrix();
}
void hill() {
	int i, j, N = 20;
	float r = (float)(0.4 * 75 + 0.5), h = (float)(0.5 + 0.25 * 70);//���a�ƍ���

	glPushMatrix();
	frustum(r, 2, h, N);
	glPopMatrix();
}
void tori(int x, int y, int z, int i) {
	glPushMatrix();
	if (i <= 90)
		glTranslatef((float)10 * sin(6.28*x / 180), (float)0.5, (float)10 * cos(6.28*z / 180));
	else if (i < 180)
		glTranslatef((float)-10 * sin(6.28*x / 180), (float)0.5, (float)-20 - 10 * cos(6.28*z / 180));
	else
		glTranslatef(0.4*(i - 180), 0.5 + 0.25*(i - 180), -30);

	//�x������1
	glPushMatrix();
	glTranslatef(0.40*sin(6.28*x / 180), 0.2, 0.40*cos(6.28*z / 180));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Red);
	cylinder(0.06, 0.4, 10);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Black);
	glTranslatef(0, -0.4, 0);
	cylinder(0.061, 0.08, 10);
	glPopMatrix();

	//�x������2
	glPushMatrix();
	glTranslatef(-0.40*sin(6.28*x / 180), 0.2, -0.40*cos(6.28*z / 180));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Red);
	cylinder(0.06, 0.4, 10);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Black);
	glTranslatef(0, -0.4, 0);
	cylinder(0.061, 0.08, 10);
	glPopMatrix();

	//���̖_�E����
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Red);
	glTranslatef(0, 0.56, 0);
	glRotatef(90 + 2 * x, 0, 1, 0);
	cuboid(1, 0.12, 0.12);
	glTranslatef(0, -0.2, 0);
	cuboid(1, 0.08, 0.08);
	glTranslatef(0, -0.8, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Gray);
	stair(1.5, 0.4, 0.41);
	glPopMatrix();

	glPopMatrix();
}
void lake(float radius, int x, int y, float ovalx, float ovaly)
{

	static const GLfloat color[] = { 1, 1, 1, 1.0 };  /* �ގ� (�F) */
	  //255,82,52
	  /* �ގ��̐ݒ� */
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	/* �A���t�@�e�X�g�J�n */
	glEnable(GL_ALPHA_TEST);
	/* �e�N�X�`���}�b�s���O�J�n */
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid_4);  // �e�N�X�`��ID=1���w��
/*	glPushMatrix();
	glBegin(GL_TRIANGLES);
	
	glNormal3d(-cos(thetah), r / h1, sin(thetah));
	glTexCoord2d(0.5, 0);
	glVertex3d(0, h1, 0);//���_

	glNormal3d(-cos(theta1), r / h1, sin(theta1));
	glTexCoord2d(1, 1);
	glVertex3d(-r*cos(theta1), h2, r*sin(theta1));

	glNormal3d(-cos(theta2), r / h1, sin(theta2));
	glTexCoord2d(0, 1);
	glVertex3d(-r*cos(theta2), h2, r*sin(theta2));
	glEnd();
	glPopMatrix();
*/
	float th1;
	for (th1 = 0.0; th1 < 360.0; th1 = th1 + 10.0)
	{
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * 3.14;
		float th2_rad = th2 / 180.0 * 3.14;

		float x1 = radius * cos(th1_rad)*(ovalx / 100.0f);
		float y1 = radius * sin(th1_rad)*(ovaly / 100.0f);
		float x2 = radius * cos(th2_rad)*(ovalx / 100.0f);
		float y2 = radius * sin(th2_rad)*(ovaly / 100.0f);

//		glMaterialfv(GL_FRONT, GL_DIFFUSE, Blue);
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0.5, 0.5);
		glVertex3d(x, 0, y);
		glTexCoord2d(0.5*cos(th1_rad)+0.5, 0.5*sin(th1_rad)+0.5);
//		glTexCoord2d(1, 1);
		glVertex3d(x1 + x, 0, y1 + y);
		glTexCoord2d(0.5*cos(th2_rad)+0.5, 0.5*sin(th2_rad)+0.5);
//		glTexCoord2d(0, 1);
		glVertex3d(x2 + x, 0, y2 + y);
		glEnd();
	}
}
