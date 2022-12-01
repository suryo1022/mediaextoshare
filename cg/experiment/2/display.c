#include <GL/glut.h>
#include <stdio.h>
#include "input.h"
#include "object.h"
#include "texture.h"

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

// -------- 駅の床を描く --------
void draw_home_floor() {

    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);

    // 駅の床を描く
    int i;
    glBegin(GL_POLYGON);
        for(i = 0; i < 12; ++i) {
            glColor3dv(home_floor_color[0]);
            glVertex3dv(home_floor_vertex[home_floor_edge[i][0]]);
            glVertex3dv(home_floor_vertex[home_floor_edge[i][1]]);
        }
    glEnd();

    // テクスチャマッピング終了
    glDisable(GL_TEXTURE_2D);
}

// （テスト）テクスチャマッピングのテスト
void draw_texture() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texname[0]);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1.0);
        glVertex3dv(texture_test_vertex[0]);
        glTexCoord2d(0.0, 0.0);
        glVertex3dv(texture_test_vertex[1]);
        glTexCoord2d(1.0, 0.0);
        glVertex3dv(texture_test_vertex[2]);
        glTexCoord2d(1.0, 1.0);
        glVertex3dv(texture_test_vertex[3]);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}



// -------- 画面への表示に関する関数 --------
void display() {
    // ---- キャンバスを青空の色で塗りつぶす ----
    glClearColor(163.0 / 255.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // ---- 地面を描く ----
    draw_ground();

    // ---- （テスト）立方体を描く ----
    //draw_cube();

    // ---- （テスト）座標軸を描く ----
    draw_axis();

    // ---- 駅の床を描く ----
    draw_home_floor();

    // ----（テスト）テクスチャのテスト用 ----
    //draw_texture();

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camerapos[0], camerapos[1], camerapos[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
    printf("camerapos[0] = %f, camerapos[1] = %f, look[0] = %f, look[1] = %f\n", camerapos[0], camerapos[1], look[0], look[1]);

    // ---- 残った処理をすべて実行 ----
    glFlush();
}
