/*
** 簡易トラックボール処理
* 
* サンプルを元に一人称視点のような回転に修正
*/
#include <math.h>
#include <GL/glut.h>
#include "trackball.h"

#  define M_PI 3.14159265358979323846

/* ドラッグ開始位置 */
static int cx, cy;

/* マウスの絶対位置→ウィンドウ内での相対位置の換算係数 */
static double sx, sy;

/* マウスの相対位置→回転角の換算係数 */
#define SCALE (720 / M_PI)

/* 回転の初期値 (角度) */
static double cq[2] = { 0.0, -45.0 };

/* ドラッグ中の回転 (角度) */
static double tq[2];

/* ドラッグ中か否か */
static int drag = 0;

/*
** トラックボール処理の初期化
** 　　プログラムの初期化処理のところで実行する
*/
void trackballInit(void) {
    /* ドラッグ中ではない */
    drag = 0;

    /* 回転の初期化 */
    tq[0] = cq[0] = 0.0;
    tq[1] = cq[1] = -45.0;
}

/*
** トラックボールする領域
** 　　Reshape コールバック (resize) の中で実行する
*/
void trackballRegion(int w, int h) {
    /* マウスポインタ位置のウィンドウ内の相対的位置への換算用 */
    sx = 1.0 / (double)w;
    sy = 1.0 / (double)h;
}

/*
** ドラッグ開始
** 　　マウスボタンを押したときに実行する
*/
void trackballStart(int x, int y) {
    /* ドラッグ開始 */
    drag = 1;

    /* ドラッグ開始点を記録 */
    cx = x;
    cy = y;
}

/*
** ドラッグ中
** 　　マウスのドラッグ中に実行する
*/
void trackballMotion(int x, int y) {
    if (drag) {
        double dx, dy;

        /* マウスポインタの位置のドラッグ開始位置からの変位 */
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
** 停止
** 　　マウスボタンを離したときに実行する
*/
void trackballStop(int x, int y) {
    /* ドラッグ終了点における回転を求める */
    trackballMotion(x, y);

    /* 回転の保存 */
    cq[0] = tq[0];
    cq[1] = tq[1];

    /* ドラッグ終了 */
    drag = 0;
}

/*
** 回転の変換行列を戻す
** 　　戻り値を glMultMatrixd() などで使用してオブジェクトを回転する
*/
double* trackballRotation(void) {
    glRotated(tq[1], 1.0, 0.0, 0.0);
    glRotated(tq[0], 0.0, 1.0, 0.0);
    return tq;
}