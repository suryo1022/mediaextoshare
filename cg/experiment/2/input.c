#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "object.h"

// ---- マウスの座標保存用 ----
GLdouble mousepos[2] = {-1.0, -1.0};

// ---- 移動距離 ----
double dist_rate = 0.5;

// ---- 視点の回転速度 ----
double schange_rateyoko = 0.005;
double schange_ratetate = 0.001;


// -------- マウス操作をする --------
void mouse(int button, int state, int x, int y) {

    switch(button) {
        // 左クリックされたとき
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
	        mousepos[0] = x; mousepos[1] = y;
            } else {
	        mousepos[0] = -1; mousepos[1] = -1;
            }

        default:
            break;
        
    }
}

// -------- マウスドラッグ --------
void motion(int x, int y) {
    double thetax, thetay, tana, cosa;

    // マウス位置がデフォルト設定の時
    if(mousepos[0] < 0 || mousepos[1] < 0) {
        // do nothing
    } else {
        // 三次元における三角関数の加法定理によって、カメラの視点を移動
        thetax = (mousepos[0] - x) * schange_rateyoko;
        thetay = (mousepos[1] - y) * schange_ratetate;
        tana = look[1] / sqrt(look[0]*look[0] + look[2]*look[2]);
        cosa = sqrt(look[0]*look[0] + look[2]*look[2]);
        // マウスが横にドラッグされたとき
        look[0] = (look[0] - camerapos[0])*cos(thetax) - (look[2] - camerapos[2])*sin(thetax) + camerapos[0];
        look[2] = (look[2] - camerapos[2])*cos(thetax) + (look[0] - camerapos[0])*sin(thetax) + camerapos[2];
        // マウスが縦にドラッグされたとき
        look[0] = (look[0] - camerapos[0])*cos(thetay) - (look[0] - camerapos[0])*tana * sin(thetay) + camerapos[0];
        look[1] = (look[1] - camerapos[1])*cos(thetay) + cosa*sin(thetay) + camerapos[1];
        look[2] = (look[2] - camerapos[2])*cos(thetay) - (look[2] - camerapos[2])*tana*sin(thetay) + camerapos[2];
	
        glutPostRedisplay();
    }
    mousepos[0] = x; mousepos[1] = y;
}

// -------- キーボード操作をする --------
void keyboard(unsigned char key, int x, int y) {
    int i;
    double a;
    double deltax, deltaz, norm;

    switch(key) {

        // カメラをデフォルトの位置、視点に戻す
        case 'r':
            for (i = 0; i < 3; ++i) {
                look[i] = originlook[i];
                camerapos[i] = origincamerapos[i];
            }
            glutPostRedisplay();
	    break;

        // 前に進む
        case 'w':
            camerapos[2] -= dist_rate;
            look[2] -= dist_rate;
            glutPostRedisplay();
            break;

        // 後ろに下がる
        case 's':
            camerapos[2] += dist_rate;
            look[2] += dist_rate;
            glutPostRedisplay();
            break;

        // 右に移動する
        case 'd':
            camerapos[0] += dist_rate;
            look[0] += dist_rate;
            glutPostRedisplay();
            break;

        // 左に移動する
        case 'a':
            camerapos[0] -= dist_rate;
            look[0] -= dist_rate;
            glutPostRedisplay();
            break;

        // 上に行く
        case 'f':
            camerapos[1] += dist_rate;
            look[1] += dist_rate;
            glutPostRedisplay();
            break;

        // 下に下がる
        case 'v':
            camerapos[1] -= dist_rate;
            look[1] -= dist_rate;
            glutPostRedisplay();
            break;

        // プログラムを終了し、画面を閉じる
        case 'q':
        case 'Q':
        case '\033':
	        exit(0);

        default:
            break;
    }
}
