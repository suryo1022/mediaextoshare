#include <stdio.h>
#include <GL/glut.h>

// -------- 広域変数 --------

// ---- （テスト）座標軸 ----
// 頂点座標 
GLdouble axis_vertex[][3] =
{
    // x軸
    {-100, 0, 0},
    {100, 0, 0},
    // y軸
    {0, -100, 0},
    {0, 100, 0},
    // z軸
    {0, 0, -100},
    {0, 0, 100},
};

// 辺 
int axis_edge[][2] =
{
    {0, 1},
    {2, 3},
    {4, 5},
};

// 色情報
GLdouble axis_color[][3] =
{
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
};

// ---- （テスト）立方体 ----
// 頂点座標
GLdouble cube_vertex[][3] = {
    {-1.0, 1.0, 1.0},
    {-1.0, 1.0, -1.0},
    {1.0, 1.0, -1.0},
    {1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0},
    {-1.0, -1.0, -1.0},
    {1.0, -1.0, -1.0},
    {1.0, -1.0, 1.0},
};

int cube_edge[][2] = {
    {0, 1},
    {1, 2},
    {2, 3},
    {3, 0},
    {4, 5},
    {5, 6},
    {6, 7},
    {7, 4},
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7},
};

// ---- 緑の地面 ----
// 頂点座標
GLdouble ground_vertex[][3] = {
    {100.0, -1.0, -100.0},
    {100.0, -1.0, 100.0},
    {-100.0, -1.0, 100.0},
    {-100.0, -1.0, -100.0},
};

// ---- カメラの視点、位置 ----
GLdouble look[3] = {0.0, 0.0, 0.0};
GLdouble camerapos[3] = {3.0, 1.0, 15.0};
GLdouble originlook[3] = {0.0, 0.0, 0.0};
GLdouble origincamerapos[3] = {3.0, 1.0, 15.0};

// ---- マウスの座標保存用 ----
GLdouble mousepos[2] = {-1.0, -1.0};

// -------- （テスト）立方体を作る --------
void draw_cube() {
    glBegin(GL_LINES);
        glColor3d(0.0, 0.0, 0.0);
        int i;
        for(i = 0; i < 12; ++i) {
            glVertex3dv(cube_vertex[cube_edge[i][0]]);
            glVertex3dv(cube_vertex[cube_edge[i][1]]);
        }
    glEnd();
}

// -------- （テスト）座標軸を描く --------
void draw_axis() {
    
    int i;
    for(i = 0; i < 3; ++i) {
        glBegin(GL_LINES);
	    glColor3dv(axis_color[i]);
	    glVertex3dv(axis_vertex[axis_edge[i][0]]);
            glVertex3dv(axis_vertex[axis_edge[i][1]]);
	glEnd();
    }    
}

// -------- 緑の地面を描く --------
void draw_ground() {
    // 地面を描く
    glBegin(GL_POLYGON);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3dv(ground_vertex[0]);
        glVertex3dv(ground_vertex[1]);
        glVertex3dv(ground_vertex[2]);
        glVertex3dv(ground_vertex[3]);
    glEnd();
}

// -------- 画面への表示に関する関数 --------
void display() {
    // ---- キャンバスを白で塗りつぶす ----
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // ---- 地面を描く ----
    //draw_ground();

    // ---- （テスト）立方体を描く ----
    draw_cube();

    // ---- （テスト）線を描く ----
    draw_axis();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camerapos[0], camerapos[1], camerapos[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

    // ---- 残った処理をすべて実行 ----
    glFlush();
}


// -------- ウィンドウの拡大縮小に合わせてサイズを変える --------
void resize(int w, int h) {
    // ビューポートを設定（ウィンドウ全体）
    glViewport(0, 0, w, h);

    // モデルビュー変換行列の設定
    glMatrixMode(GL_PROJECTION);
    // 変換行列を単位行列にする
    glLoadIdentity();

    gluPerspective(30.0, (double)w / (double)h, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

// -------- マウス操作をする --------
void mouse(int button, int state, int x, int y) {

    switch(button) {
        // 左クリックされたとき
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
	        mousepos[0] = x; mousepos[1] = y;
	        //camerapos[0] += 0.1;
	        //look[0] -= 0.1;
	        //glutPostRedisplay();
	        //printf("look[0] = %f\n", look[0]); 

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


// -------- main関数 --------
int main(int argc, char *argv[]) {
    // ---- 初期化 ----
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // ---- ウィンドウを作成する ----
    glutCreateWindow(argv[0]);

    // ---- 描画を行う ----
    glutDisplayFunc(display);

    // ---- ウィンドウのサイズ変更 ----
    glutReshapeFunc(resize);

    // ---- マウス操作 ----
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // ---- キーボード操作 ----
    glutKeyboardFunc(keyboard);

    // ---- イベントが起きるまで待機 ----
    glutMainLoop();

    return 0;
}
