#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include "main.h"

GLuint texid[20];

/*�ړ��֌W*/
void idle(void){
    glutPostRedisplay();
}

void Move(int _id){
    static int timer = 0;
    timer++;
    switch (_id){
    case -1: /*��~*/
        glutIdleFunc(0);
        break;
    case 0: /*�O���ړ�*/
        player_x += 0.1 * M_SIN[theta];
        player_z -= 0.1 * M_COS[theta];
        break;
    case 1: /*����ړ�*/
        player_x -= 0.1 * M_SIN[theta];
        player_z += 0.1 * M_COS[theta];
        break;
    case 2: /*����]*/
        /* �����������]�p�� 0 �ɖ߂� */
        if (--theta <= 0) theta = 360;
        muki_x = r * M_SIN[theta];
        muki_z = -r * M_COS[theta];
        break;
    case 3: /*�E��]*/
        /* �����������]�p�� 0 �ɖ߂� */
        if (++theta >= 360) theta = 0;
        muki_x = r * M_SIN[theta];
        muki_z = -r * M_COS[theta];
        break;
    case 4: /*���_�ړ���*/
        if (timer % 2 == 0){
            if (muki_y < 2.0){
                muki_y += 0.01;
            }
        }
        break;
    case 5: /*���_�ړ���*/
        if (timer % 2 == 0){
            if (muki_y > 0.5){
                muki_y -= 0.01;
            }
        }
        break;
    default:
        break;
    }
}

/*�~����`��/����/���a*/
void Cylinder(double height, double radius, GLfloat *color){
    int i;

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    /*���*/
    glNormal3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < sides; i++) {
        glVertex3d(radius * SIN[i], height, radius * COS[i]);
    }
    glEnd();
    /*����*/
    glNormal3d(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
    for (i = sides; --i >= 0;) {
        glVertex3d(radius * SIN[i], 0.0, radius * COS[i]);
    }
    glEnd();
    /* ���� */
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= sides; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(x, 0.0, z);
        glVertex3f(radius * x, height, radius * z);
        glVertex3f(radius * x, 0.0, radius * z);
    }
    glEnd();
    glPopMatrix();
}

/*�����̃p�[�c1�̕`��*/
void Gate_1(){
    int i;
    int j;
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_gate_1[face[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}
/*�����̃p�[�c2�̕`��*/
void Gate_2(){
    int i;
    int j;
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_gate_2[face[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}
/*�����̃p�[�c3�̕`��*/
void Gate_3(){
    int i;
    int j;
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    for (j = 0; j < 14; ++j) {
        glNormal3dv(normal_gate_3[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_gate_3[face_gate_3[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}

/*�����̕`��*/
void GuardFrame(){
    glPushMatrix();
    glTranslated(-0.25, 1.7, -0.05);
    Gate_1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.25, 2.0, -0.05);
    Gate_1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.65, 1.75, -0.025);
    Gate_2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.02, 2.08, -0.075);
    Gate_3();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.4, 0.0);
    Cylinder(1.6, 0.1, red);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, 0.4, 0.0);
    Cylinder(1.6, 0.1, red);
    glPopMatrix();

    glPushMatrix();
    Cylinder(0.4, 0.1, black);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, 0.0, 0.0);
    Cylinder(0.4, 0.1, black);
    glPopMatrix();
}

/*�n�ʂ̕`��*/
void Ground(){
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[2]);

    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2d(0.0, 10.0);
    glVertex3d(-50.0, 0.0, -50.0);
    glTexCoord2d(10.0, 10.0);
    glVertex3d(-50.0, 0.0, 50.0);
    glTexCoord2d(10.0, 0.0);
    glVertex3d(50.0, 0.0, 50.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(50.0, 0.0, -50.0);
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*�����̕`��*/
void Stones(){
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[1]);

    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2d(0.0, 2.0);
    glVertex3d(-1.0, 0.0, -1.0);
    glTexCoord2d(2.0, 2.0);
    glVertex3d(-1.0, 0.0, 1.0);
    glTexCoord2d(2.0, 0.0);
    glVertex3d(1.0, 0.0, 1.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(1.0, 0.0, -1.0);
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*�Ώ�(��)�̕`��*/
void Stone(){
    int j;
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[0]);

    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        glTexCoord2d(0.0, 2.0);
        glVertex3dv(vertex_stone[face[j][0]]);
        glTexCoord2d(1.0, 2.0);
        glVertex3dv(vertex_stone[face[j][1]]);
        glTexCoord2d(1.0, 0.0);
        glVertex3dv(vertex_stone[face[j][2]]);
        glTexCoord2d(0.0, 0.0);
        glVertex3dv(vertex_stone[face[j][3]]);
    }
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*�Ώ�(��)�̕`��*/
void Stone_s(){
    int j;
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[0]);

    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        glTexCoord2d(0.0, 1.0);
        glVertex3dv(vertex_stone_s[face[j][0]]);
        glTexCoord2d(3.0, 1.0);
        glVertex3dv(vertex_stone_s[face[j][1]]);
        glTexCoord2d(3.0, 0.0);
        glVertex3dv(vertex_stone_s[face[j][2]]);
        glTexCoord2d(0.0, 0.0);
        glVertex3dv(vertex_stone_s[face[j][3]]);
    }
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*�؂̗t�̕`��*/
void Leaf(){
    glPushMatrix();

    glTranslated(0.0, 0.0, 0.0);

    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* �A���t�@�e�X�g�J�n */
    glEnable(GL_ALPHA_TEST);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[3]);

    /* �}�`�̕`�� */
    /* �P���̂S�p�`��`�� */
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-2.0, -2.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(2.0, -2.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(2.0, 2.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-2.0, 2.0, 0.0);
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    /* �A���t�@�e�X�g�I�� */
    glDisable(GL_ALPHA_TEST);

    glPopMatrix();
}

/*�؂̕`��*/
void Tree(){
    int i;
    /*�t�̕`��*/
    for (i = 0; i < 10; i++){
        glPushMatrix();
        glRotated(360 / 20 * i, 0.0, 1.0, 0.0);
        glTranslated(0.0, 2.5, 0.0);
        Leaf();
        glRotated(180, 0.0, 1.0, 0.0);
        Leaf();
        glPopMatrix();
    }
    /*���̕`��*/
    glPushMatrix();
    Cylinder(1.0, 0.1, tree_color);
    glPopMatrix();
}

/*�{���̉����̕`��*/
void loof_2(){
    int i;
    int j;

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 3 * sides / 4; i <= sides; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, -x, -z);
        glVertex3f(6.0, 2.0 * x, 2.0 * z);
        glVertex3f(0.0, 2.0 * x, 2.0 * z);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, 0.0, 4.0);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = sides / 2; i <= 3 * sides / 4; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, x, z);
        glVertex3f(6.0, 2.0 * x, 2.0 * z);
        glVertex3f(0.0, 2.0 * x, 2.0 * z);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -0.4, 0.4);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 3 * sides / 4; i <= sides; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, x, z);
        glVertex3f(0.0, 1.6 * x, 1.6 * z);
        glVertex3f(6.0, 1.6 * x, 1.6 * z);

    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -0.4, 3.6);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = sides / 2; i <= 3 * sides / 4; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, -x, -z);
        glVertex3f(0.0, 1.6 * x, 1.6 * z);
        glVertex3f(6.0, 1.6 * x, 1.6 * z);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -2.0, 2.0);
    glNormal3d(-1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(0.0, 0.0, 1.6);
    for (i = 90; i > 0; i--){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), 2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), 1.6 * (1.0 - M_COS[i]));
    }
    for (i = 0; i <= 90; i++){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), -2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), -1.6 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(6.0, -2.0, 2.0);
    glNormal3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(0.0, 0.0, -1.6);
    for (i = 90; i > 0; i--){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), -2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), -1.6 * (1.0 - M_COS[i]));
    }
    for (i = 0; i < 90; i++){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), 2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), 1.6 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_red);
    glTranslated(0.4, -2.0, 2.01);
    glNormal3d(-1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0.0, 0.0, 0.0);
    for (i = 90; i >= 0; i--){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), 1.8 * (1.0 - M_COS[i]));
    }
    for (i = 0; i < 90; i++){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), -1.8 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_red);
    glTranslated(5.6, -2.0, 2.01);
    glNormal3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0.0, 0.0, 0.0);
    for (i = 90; i >= 0; i--){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), -1.8 * (1.0 - M_COS[i]));
    }
    for (i = 0; i <= 90; i++){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), 1.8 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -2.090, 0.0);
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        if (j == 4){
            /* �}�`�̐F (��) */
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_red);
        }
        glNormal3dv(normal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_loof_box[face[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}

/*�{���̕ǂ̕`��*/
void wall(GLuint _tex){
    glPushMatrix();
    /* �}�`�̐F (��) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tex);

    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(1.0, 2.0, 0.0);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(1.0, 0.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(0.0, 2.0, 0.0);
    glEnd();

    /* �}�`�̕`�� */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(1.0, 0.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(1.0, 2.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(0.0, 2.0, 0.0);
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*�{���̃p�[�c1*/
/*_tex : �\��t����e�N�X�`�� _i : �\��t����� _color : �F*/
void shrine_1(GLuint _tex, int i, GLfloat *_color){
    /* �}�`�̐F */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _color);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glBegin(GL_QUADS);
    glNormal3dv(normal[i]);
    glTexCoord2d(1.0, 1.0);
    glVertex3dv(vertex_box_1[face[i][0]]);
    glTexCoord2d(1.0, 0.0);
    glVertex3dv(vertex_box_1[face[i][1]]);
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(vertex_box_1[face[i][2]]);
    glTexCoord2d(0.0, 1.0);
    glVertex3dv(vertex_box_1[face[i][3]]);
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

/*�{���̃p�[�c2*/
/*_tex : �\��t����e�N�X�`�� _i : �\��t����� _color : �F*/
void shrine_2(GLuint _tex, int i, GLfloat *_color){
    /* �}�`�̐F */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _color);

    /* �e�N�X�`���}�b�s���O�J�n */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glBegin(GL_QUADS);
    glNormal3dv(normal[i]);
    glTexCoord2d(1.0, 1.0);
    glVertex3dv(vertex_box_2[face[i][0]]);
    glTexCoord2d(1.0, 0.0);
    glVertex3dv(vertex_box_2[face[i][1]]);
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(vertex_box_2[face[i][2]]);
    glTexCoord2d(0.0, 1.0);
    glVertex3dv(vertex_box_2[face[i][3]]);
    glEnd();

    /* �e�N�X�`���}�b�s���O�I�� */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

/*�{���̕`��*/
void Shrine(){
    int i;

    /*����*/
    glPushMatrix();
    glTranslated(0.0, 6.0, 0.0);
    loof_2();
    glPopMatrix();

    /*����/�E*/
    glPushMatrix();
    glScaled(2.0, .5, .5);
    glTranslated(2.5, 6.0, 2.0);
    loof_2();
    glPopMatrix();

    /*����/��*/
    glPushMatrix();
    glScaled(2.0, .5, .5);
    glTranslated(-5.5, 6.0, 2.0);
    loof_2();
    glPopMatrix();

    /*��/��*/
    for (i = 0; i < 11; i++){
        glPushMatrix();
        glTranslated(-1.0 * i, 0.0, 1.5);
        wall(texid[12]);
        glTranslated(0.0, 0.0, 1.0);
        Cylinder(2.0, 0.05, loof_red);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-10.0, 0.0, 1.5);
    glRotated(-90, 0.0, 1.0, 0.0);
    wall(texid[10]);
    glPopMatrix();

    /*��/�E*/
    for (i = 0; i < 11; i++){
        glPushMatrix();
        glTranslated(1.0 * i + 5.0, 0.0, 1.5);
        wall(texid[12]);
        glTranslated(1.0, 0.0, 1.0);
        Cylinder(2.0, 0.05, loof_red);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(16.0, 0.0, 1.5);
    glRotated(-90, 0.0, 1.0, 0.0);
    wall(texid[10]);
    glPopMatrix();

    /*�{��1*/
    glPushMatrix();
    glTranslated(1.0, 2.5, 0.5);
    shrine_1(texid[6], 0, white);
    shrine_1(texid[7], 1, white);
    shrine_1(texid[7], 2, white);
    shrine_1(texid[7], 3, white);
    shrine_1(texid[11], 4, white);
    glPopMatrix();

    /*�{��2*/
    glPushMatrix();
    glTranslated(1.0, 0.0, 0.5);
    shrine_2(texid[4], 0, white);
    shrine_2(texid[10], 1, white);
    shrine_2(texid[8], 2, white);
    shrine_2(texid[10], 3, white);

    glTranslated(3.0, 0.0, 0.0);
    shrine_2(texid[5], 0, white);
    shrine_2(texid[10], 1, white);
    shrine_2(texid[9], 2, white);
    shrine_2(texid[10], 3, white);

    glPopMatrix();
}

/*�������~�`�ɔz�u/m: �����l/n: �ŏI�l*/
void Circle_Gate(int m, int n){
    int i;
    for (i = m; i <= n; i++){
        glPushMatrix();
        glTranslated(4.0 * M_COS[(int)((360 / 72) * i)], 0.0, 4.0 * M_SIN[(int)((360 / 72) * i)]);
        glRotated((-360. / 72) * i, 0.0, 1.0, 0.0);
        GuardFrame();
        glPopMatrix();
    }
}

/*�`��*/
void display(void){
    int i;
    int j;

    /*�f�o�b�O*/
    //printf("theta: %f, muki_x: %f, muki_z: %f \n", (double)theta, (double)muki_x, (double)muki_z);
    //printf("player_x: %f, player_z: %f \n", (double)player_x, (double)player_z);
    //printf("move_id: %d \n", move_id);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    /*�ړ�*/
    Move(move_id);

    /* ���_�ʒu�Ǝ������� */
    gluLookAt(0.0 + player_x, 0.5, r + player_z, muki_x + player_x, muki_y, r + muki_z + player_z, 0.0, 1.0, 0.0);


    /* �����̈ʒu�ݒ� */
    glPushMatrix();
    glTranslated(light_pos, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glPopMatrix();
    //glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

    /*�n��*/
    glPushMatrix();
    glTranslated(0.0, -0.1, 45.0);
    Ground();
    glPopMatrix();

    /*�������璹��*/
    for (i = 0; i < 50; i++){
        glPushMatrix();
        glTranslated(0.0, 0.0, 25 + 0.5 * i);
        GuardFrame();
        glTranslated(3.0, 0.0, 0.0);
        GuardFrame();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-4.0, 0.0, 50.0);
    Circle_Gate(0, 18);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.0, 0.0, 59.5);
    Circle_Gate(18, 53);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.5, 0.0, 50.0);
    Circle_Gate(18, 36);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.5, 0.0, 59.5);
    Circle_Gate(0, 18);
    Circle_Gate(54, 71);
    glPopMatrix();

    for (i = 1; i < 25; i++){
        glPushMatrix();    
        glTranslated(-4.0 + 0.5 * i, 0.0, 65.0);
        glRotated(90, 0.0, 1.0, 0.0);
        GuardFrame();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(0.0, 0.0, 5.0);
    glScaled(2.0, 2.0, 2.0);
    GuardFrame();
    glPopMatrix();
    /*�����Œ����I��*/

    /*�������獻��*/
    for (i = 0; i < 26; i++){
        glPushMatrix();
        glTranslated(0.8, 0.0, 25.0 + 1.0 * i);
        Stones();
        glTranslated(3.0, 0.0, 0.0);
        Stones();
        glPopMatrix();
    }
    for (i = 0; i < 22; i++){
        for (j = 0; j < 14; j++){
            glPushMatrix();
            glTranslated(-9.2 + 1.0 * i, 0.0, 52.0 + 1.0 * j);
            Stones();
            glTranslated(3.0, 0.0, 0.0);
            Stones();
            glPopMatrix();
        }
    }
    for (i = 0; i < 22; i++){
        for (j = 0; j < 14; j++){
            glPushMatrix();
            glTranslated(-9.2 + 1.0 * i, 0.0, 10 + 1.0 * j);
            Stones();
            glTranslated(3.0, 0.0, 0.0);
            Stones();
            glPopMatrix();
        }
    }
    /*�����ō����I��*/

    /*�Ώ�(��)*/
    for (i = 0; i < 80; i++){
        glPushMatrix();
        glTranslated(0.45, 0.0, 25.0 + 0.32 * i);
        Stone();
        glTranslated(3.0, 0.0, 0.0);
        Stone();
        glPopMatrix();
    }

    /*��������Ώ�(��)*/
    for (i = 0; i < 40; i++){
        glPushMatrix();
        glTranslated(0.24, 0.0, 25.0 + 0.64 * i);
        Stone_s();
        glTranslated(0.82, 0.0, 0.0);
        Stone_s();
        glPopMatrix();
    }
    for (i = 0; i < 40; i++){
        glPushMatrix();
        glTranslated(3.24, 0.0, 25.0 + 0.64 * i);
        Stone_s();
        glTranslated(0.82, 0.0, 0.0);
        Stone_s();
        glPopMatrix();
    }
    /*�����ŐΏ�(��)�I��*/

    /*�{���̕`��*/
    glPushMatrix();
    glTranslated(-1.0, 0.0, 15.0);
    Shrine();
    glPopMatrix();

    /*���������*/
    for (i = 0; i < 2; i++){
        for (j = 0; j < 14; j++){
            glPushMatrix();
            glTranslated(-2.0 - (2.0 * i), 0.0, 25.0 + 2.0 * j);
            Tree();
            glTranslated(10.5, 0.0, 0.0);
            Tree();
            glPopMatrix();
        }
    }
    for (i = 0; i < 15; i++){
            glPushMatrix();
            glTranslated(-10.0 + (2.0 * i), 0.0, 67.0);
            Tree();
            glPopMatrix();
        }
    /*�����Ŗ؏I��*/

    glFlush();

    glutSwapBuffers();
}

/*������*/
void init(void){
    int i;
    int ret;
    int data[4];
    static int n = 0;

    int img_size[20];
    int param[20];
    int height[20];
    int width[20];

    static int f_num = 0;

    static const char *file[] = {
        "stone_3.raw",
        "stone_2.raw",
        "ground.raw",
        "leaf.raw",
        "shrine_1.raw",
        "shrine_2.raw",
        "shrine_3.raw",
        "shrine_4.raw",
        "shrine_5.raw",
        "shrine_6.raw",
        "shrine_7.raw",
        "shrine_8.raw",
        "shrine_9.raw",
    };

    /*�e�N�X�`���֌W--------------------------------------------------------------------------------*/

    /* �e�N�X�`���� */
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLubyte *_texture;

    FILE *fp;

    /* �e�N�X�`���摜�̓ǂݍ���------------------------------------------------------------------------*/

    if ((fp = fopen("image_data.csv", "r")) != NULL){
        while ((ret = fscanf(fp, "%d, %d, %d, %d", &data[0], &data[1], &data[2], &data[3])) != EOF){
            img_size[n] = data[0];
            param[n] = data[1];
            height[n] = data[2];
            width[n] = data[3];
            n++;
            f_num++;
            printf("%d, %d, %d, %d\n", data[0], data[1], data[2], data[3]);
        }
        fclose(fp);
    }

    for (i = 0; i < f_num; i++){
        _texture = (GLubyte *)malloc(img_size[i]);

        if ((fp = fopen(file[i], "rb")) != NULL) {
            fread(_texture, img_size[i], 1, fp);
            fclose(fp);
        }
        else {
            perror(file[i]);
        }
        glGenTextures(1, &texid[i]); // �e�N�X�`��ID�𐶐�
        glBindTexture(GL_TEXTURE_2D, texid[i]);
        /* �e�N�X�`���摜�̓o�C�g�P�ʂɋl�ߍ��܂�Ă��� */
        glPixelStorei(GL_UNPACK_ALIGNMENT, param[i]);

        /* �e�N�X�`���̊��蓖�� */
        if (param[i] == 1){
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width[i], height[i],
                GL_RGB, GL_UNSIGNED_BYTE, _texture);
        }
        else{
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width[i], height[i],
                GL_RGBA, GL_UNSIGNED_BYTE, _texture);
        }

        /* �e�N�X�`�����g��E�k��������@�̎w�� */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        free(_texture);
    }

    /* �A���t�@�e�X�g�̔�r�֐� */
    glAlphaFunc(GL_GREATER, 0.5);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /*�e�N�X�`���֌W�I��------------------------------------------------------------------------------*/

    glClearColor(160. / 256., 216 / 256., 236 / 256., 1.0);

    /*�~�̕`��Ɏg��sin��cos�̒l���Ɍv�Z���Ă���*/
    double step = 2 * PI / (double)sides;
    for (i = 0; i <= sides; i++){
        double t = step * (double)i;
        SIN[i] = sin(t);
        COS[i] = cos(t);
    }

    /*���_�����Ɏg��sin��cos�̒l���Ɍv�Z���Ă���*/
    for (i = 0; i <= 360; i++){
        M_SIN[i] = sin(2 * PI * (double)i / 360.);
        M_COS[i] = cos(2 * PI * (double)i / 360.);
    }

}

void resize(int w, int h){
    glViewport(0, 0, w, h);

    /* �����ϊ��s��̐ݒ� */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (double)w / (double)h, 0.5, 100.0);

    /* ���f���r���[�ϊ��s��̐ݒ� */
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}

void mouse(int button, int state, int x, int y){}

/*�L�[���������Ƃ�*/
void keyboarddown(unsigned char key, int x, int y){
    switch (key) {
    case 'z':
        move_id = 4;
        glutIdleFunc(idle);
        break;
    case 'x':
        move_id = 5;
        glutIdleFunc(idle);
        break;
    case 'c':
        if (++light_pos >= 300) light_pos = -500;
        glutIdleFunc(idle);
        break;
    case 'q':
    case 'Q':
    case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
        exit(0);
    default:
        break;
    }
}

/*�L�[�𗣂����Ƃ�*/
void keyboardup(unsigned char key, int x, int y){
    switch (key) {
    case 'z':
    case 'x':
        move_id = -1;
        break;
    case 'c':
        glutIdleFunc(0);
        break;
    default:
        break;
    }
}

/*�L�[���������Ƃ�*/
void specialkeydown(int key, int x, int y)
{
    switch (key){
    case GLUT_KEY_UP:
        move_id = 0;
        //move_x += 0.1 * sin(2 * PI * (double)theta / 360);
        //move_z -= 0.1 * cos(2 * PI * (double)theta / 360);
        glutIdleFunc(idle);
        break;
    case GLUT_KEY_DOWN:
        move_id = 1;
        //move_x -= 0.1 * sin(2 * PI * (double)theta / 360);
        //move_z += 0.1 * cos(2 * PI * (double)theta / 360);
        glutIdleFunc(idle);
        break;
    case GLUT_KEY_LEFT:
        move_id = 2;
        //muki_x = r * sin(2 * PI * (double)theta / 360.);
        //muki_z = -r * cos(2 * PI * (double)theta / 360.);
        glutIdleFunc(idle);
        break;
    case GLUT_KEY_RIGHT:
        move_id = 3;
        //muki_x = r * sin(2 * PI * (double)theta / 360.);
        //muki_z = -r * cos(2 * PI * (double)theta / 360.);
        glutIdleFunc(idle);
        break;
    default:
        break;
    }
}

/*�L�[�𗣂����Ƃ�*/
void specialkeyup(int key, int x, int y)
{
    switch (key){
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        move_id = -1;
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[]){
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 320);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboarddown);
    glutKeyboardUpFunc(keyboardup);
    glutSpecialFunc(specialkeydown);
    glutSpecialUpFunc(specialkeyup);
    init();
    glutMainLoop();
    return 0;
}

