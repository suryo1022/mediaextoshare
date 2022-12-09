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

// ---------------- 駅の描画 ----------------
// -------- 駅の床を描く --------
void draw_home_floor() {

    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

        // 駅の床を描く
        int i, j;
        glBegin(GL_QUADS);
            for(i = 0; i < 6; ++i) {
                glColor3dv(home_floor_color[0]);
                for(j = 0; j < 4; ++j) {
                    glVertex3dv(home_floor_vertex[home_floor_face[i][j]]);
                }
            }
        glEnd();

    glDisable(GL_CULL_FACE);

    // テクスチャマッピング終了
    glDisable(GL_TEXTURE_2D);
}

// -------- 駅の建物を描く --------
void draw_home_building() {
    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

        // 駅の建物を描く
        int i, j;
        glBegin(GL_QUADS);
            for(i = 0; i < 6; ++i) {
                glColor3dv(home_building_color);
                for(j = 0; j < 4; ++j) {
                    glVertex3dv(home_building_vertex[home_building_face[i][j]]);
                }
            }
        glEnd();

    glDisable(GL_CULL_FACE);

    // テクスチャマッピング終了
    glDisable(GL_TEXTURE_2D);
}

// -------- 駅の建物の屋根を描く --------
void draw_home_building_roof() {
    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

        // 駅の建物の屋根を描く
        int i, j, max;
        for(i = 0; i < 5; ++i) {
            if(i == 0) {
                glBegin(GL_QUADS);                
                    glColor3dv(home_building_roof_color);
                    for(j = 0; j < max; ++j) {
                        glVertex3dv(home_building_roof_vertex[home_building_roof_face[i][j]]);
                    }
                glEnd();
            } else {
                glBegin(GL_TRIANGLES);                
                    glColor3dv(home_building_roof_color);                    
                    max = 3;                    
                    for(j = 0; j < max; ++j) {
                        glVertex3dv(home_building_roof_vertex[home_building_roof_face[i][j]]);
                    }
                glEnd();
            }
        }

    glDisable(GL_CULL_FACE);

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


// -------- 線路を描く --------
void draw_rail() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

        // 線路の下敷きを描く
        int i, j;
        glBegin(GL_QUADS);
            for(i = 0; i < 6; ++i) {
                glColor3dv(rail_base_color);
                for(j = 0; j < 4; ++j) {
                    glVertex3dv(rail_base_vertex[rail_base_face[i][j]]);
                }
            }
        glEnd();

        // レールを描く
        glBegin(GL_QUADS);
            for(i = 0; i < 12; ++i) {
                glColor3dv(rail_color);
                for(j = 0; j < 4; ++j) {
                    glVertex3dv(rail_vertex[rail_face[i][j]]);
                }
            }
        glEnd();
        
    
    glDisable(GL_CULL_FACE);
};


// ---- 次に描画する物体を決める（描画の順番を決める関数）----
// ここからーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
static int decide_next_argument(int i) {
    int arg;

    if(camerapos[1] >= home_building_vertex[4][2]) {
        return 
    }
    return arg;
}


// 各関数のポインタの配列
// ここから間接参照によって呼び出す
static void (*po[])() = {draw_ground, draw_cube, draw_axis, draw_rail, draw_home_building, draw_home_building_roof, draw_texture, draw_home_floor};


// -------- 画面への表示に関する関数 --------
void display() {
    // ---- キャンバスを青空の色で塗りつぶす ----
    glClearColor(163.0 / 255.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // テスト（定められた描画順で描画する）
    int i;
    for(i = 0; i < 8; ++i)
        (*po[i])();

    // ---- 地面を描く ----
    //draw_ground();

    // ---- （テスト）立方体を描く ----
    //draw_cube();

    // ---- （テスト）座標軸を描く ----
    //draw_axis();

    // ---- 線路を描く ----
    //draw_rail();

    // 駅舎を描く
    // ---- 駅の建物の屋根を描く ----
    //draw_home_building_roof();
    // ---- 駅の建物を描く ----
    //draw_home_building();
    // ---- 駅の床を描く ----
    //draw_home_floor();

    // ----（テスト）テクスチャのテスト用 ----
    //draw_texture();

    //　モデルビュー変換行列の指定の後、カメラの位置、視点の位置を指定
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camerapos[0], camerapos[1], camerapos[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);
    //printf("camerapos[0] = %f, camerapos[1] = %f, camerapos[2] = %f, look[0] = %f, look[1] = %f, look[2] = %f\n", camerapos[0], camerapos[1], camerapos[2], look[0], look[1], look[2]);

    // ---- 残った処理をすべて実行 ----
    glFlush();
}
