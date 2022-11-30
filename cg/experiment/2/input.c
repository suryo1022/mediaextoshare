#include <stdio.h>
#include <GL/glut.h>

// ---- カメラの視点、位置 ----
GLdouble look[3] = {0.0, 0.0, 0.0};
GLdouble camerapos[3] = {3.0, 1.0, 15.0};
GLdouble originlook[3] = {0.0, 0.0, 0.0};
GLdouble origincamerapos[3] = {3.0, 1.0, 15.0};

// ---- マウスの座標保存用 ----
GLdouble mousepos[2] = {-1.0, -1.0};

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
    printf("pos(%d, %d)\n", x, y);
    // マウス位置がデフォルト設定の時
    if(mousepos[0] < 0 || mousepos[1] < 0) {
        // do nothing
    } else {
        look[0] += (mousepos[0] - x) * 0.1;
	look[1] += (mousepos[1] - y) * 0.1;
	glutPostRedisplay();
    }
    mousepos[0] = x; mousepos[1] = y;
}

// -------- キーボード操作をする --------
void keyboard(unsigned char key, int x, int y) {
    int i;

    switch(key) {

        case 'r':
            for (i = 0; i < 3; ++i) {
                look[i] = originlook[i];
                camerapos[i] = origincamerapos[i];
            }
            glutPostRedisplay();
	    break;

        case 'w':
	    camerapos[2] -= 0.1;
	    // 移動に伴い、視点も移動
	    look[2] -= 0.1;
	    glutPostRedisplay();
	    break;

        case 's':
	    camerapos[2] += 0.1;
	    // 移動に伴い、視点も移動
	    look[2] += 0.1;
	    glutPostRedisplay();
	    break;

        default:
            break;
    }
}
