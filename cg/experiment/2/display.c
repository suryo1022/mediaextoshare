#include <GL/glut.h>
#include "input.h"
#include "object.h"

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
