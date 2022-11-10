/*
** �ȈՃg���b�N�{�[������
* 
* �T���v�������Ɉ�l�̎��_�̂悤�ȉ�]�ɏC��
*/
#include <math.h>
#include <GL/glut.h>
#include "trackball.h"

#  define M_PI 3.14159265358979323846

/* �h���b�O�J�n�ʒu */
static int cx, cy;

/* �}�E�X�̐�Έʒu���E�B���h�E���ł̑��Έʒu�̊��Z�W�� */
static double sx, sy;

/* �}�E�X�̑��Έʒu����]�p�̊��Z�W�� */
#define SCALE (720 / M_PI)

/* ��]�̏����l (�p�x) */
static double cq[2] = { 0.0, -45.0 };

/* �h���b�O���̉�] (�p�x) */
static double tq[2];

/* �h���b�O�����ۂ� */
static int drag = 0;

/*
** �g���b�N�{�[�������̏�����
** �@�@�v���O�����̏����������̂Ƃ���Ŏ��s����
*/
void trackballInit(void) {
    /* �h���b�O���ł͂Ȃ� */
    drag = 0;

    /* ��]�̏����� */
    tq[0] = cq[0] = 0.0;
    tq[1] = cq[1] = -45.0;
}

/*
** �g���b�N�{�[������̈�
** �@�@Reshape �R�[���o�b�N (resize) �̒��Ŏ��s����
*/
void trackballRegion(int w, int h) {
    /* �}�E�X�|�C���^�ʒu�̃E�B���h�E���̑��ΓI�ʒu�ւ̊��Z�p */
    sx = 1.0 / (double)w;
    sy = 1.0 / (double)h;
}

/*
** �h���b�O�J�n
** �@�@�}�E�X�{�^�����������Ƃ��Ɏ��s����
*/
void trackballStart(int x, int y) {
    /* �h���b�O�J�n */
    drag = 1;

    /* �h���b�O�J�n�_���L�^ */
    cx = x;
    cy = y;
}

/*
** �h���b�O��
** �@�@�}�E�X�̃h���b�O���Ɏ��s����
*/
void trackballMotion(int x, int y) {
    if (drag) {
        double dx, dy;

        /* �}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����̕ψ� */
        dx = ((double)x - cx) * sx;
        dy = ((double)y - cy) * sy;

        if (dx != 0 || dy != 0) {
            //double dq[4] = { cos(ar), dy * as, dx * as, 0.0 };

            tq[0] = cq[0] + asin(dx) * SCALE;
            tq[1] = cq[1] + asin(dy) * SCALE;
            if (tq[1] < -90) {
                tq[1] = -90;
            } else if (tq[1] > 90) {
                tq[1] = 90;
            }
        }
    }
}

/*
** ��~
** �@�@�}�E�X�{�^���𗣂����Ƃ��Ɏ��s����
*/
void trackballStop(int x, int y) {
    /* �h���b�O�I���_�ɂ������]�����߂� */
    trackballMotion(x, y);

    /* ��]�̕ۑ� */
    cq[0] = tq[0];
    cq[1] = tq[1];

    /* �h���b�O�I�� */
    drag = 0;
}

/*
** ��]�̕ϊ��s���߂�
** �@�@�߂�l�� glMultMatrixd() �ȂǂŎg�p���ăI�u�W�F�N�g����]����
*/
double* trackballRotation(void) {
    glRotated(tq[1], 1.0, 0.0, 0.0);
    glRotated(tq[0], 0.0, 1.0, 0.0);
    return tq;
}