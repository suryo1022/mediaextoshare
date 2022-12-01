#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// ---- カメラの視点、位置 ----
GLdouble look[3] = {15.0, 10.0, 10.0};
GLdouble camerapos[3] = {15.0, 10.0, -10.0};
GLdouble originlook[3] = {15.0, 10.0, 10.0};
GLdouble origincamerapos[3] = {15.0, 10.0, -10.0};

// ---- マウスの座標保存用 ----
GLdouble mousepos[2] = {-1.0, -1.0};

// ---- 移動距離 ----
double dist_rate = 0.5;

// ---- 視点の回転速度 ----
double schange_rate = 0.01;


// -------- マウス操作をする --------
void mouse(int button, int state, int x, int y) {

    switch(button) {
        // 左クリックされたとき
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
	        //mousepos[0] = x; mousepos[1] = y;
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
        thetax = (mousepos[0] - x) * schange_rate;
        thetay = (mousepos[1] - y) * schange_rate;
        tana = look[1] / sqrt(look[0]*look[0] + look[2]*look[2]);
        cosa = sqrt(look[0]*look[0] + look[2]*look[2]);
        // マウスが横にドラッグされたとき
        look[0] = look[0]*cos(thetax) - look[2]*sin(thetax) - camerapos[0];
        look[2] = look[2]*cos(thetax) + look[0]*sin(thetax) - camerapos[2];
        // マウスが縦にドラッグされたとき
        //look[0] = look[0] * cos(thetay) - look[0] * tana * sin(thetay) - camerapos[0];
        //look[1] = look[1] * cos(thetay) + cosa * sin(thetay) - camerapos[1];
        //look[2] = look[2] * cos(thetay) - look[2] * tana * sin(thetay) - camerapos[2];
        printf("look[0] = %f, look[1] = %f, look[2] = %f\n", look[0], look[1], look[2]);//
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

        case 'r':
            for (i = 0; i < 3; ++i) {
                look[i] = originlook[i];
                camerapos[i] = origincamerapos[i];
            }
            glutPostRedisplay();
	    break;

        case 'w':
            camerapos[2] -= dist_rate;
            look[2] -= dist_rate;
            glutPostRedisplay();
            break;

        case 's':
            camerapos[2] += dist_rate;
            look[2] += dist_rate;
            glutPostRedisplay();
            break;

        case 'd':
            camerapos[0] += dist_rate;
            look[0] += dist_rate;
            glutPostRedisplay();
            break;

        case 'a':
            camerapos[0] -= dist_rate;
            look[0] -= dist_rate;
            glutPostRedisplay();
            break;

        case 'q':
        case 'Q':
        case '\033':
	        exit(0);

        default:
            break;
    }
}
