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
    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);

    int i, j;
    //glTranslated(-ground_intvl * (ground_num/20), 0.0, -ground_intvl * (ground_num/20));
    //for(i = 0; i < ground_num/10; ++i) {
    //for(j = 0; j < ground_num/10; ++j) {
	    // 地面を描く
	    glBindTexture(GL_TEXTURE_2D, texname[1]);
	    //glBindTexture(GL_TEXTURE_2D, texname[i%2 + 1]);
            glBegin(GL_POLYGON);
	        glTexCoord2d(0.0, 0.0);
                glVertex3dv(ground_vertex[0]);
	        glTexCoord2d(1.0, 0.0);
                glVertex3dv(ground_vertex[1]);
	        glTexCoord2d(1.0, 1.1);
                glVertex3dv(ground_vertex[2]);
	        glTexCoord2d(0.0, 1.0);
                glVertex3dv(ground_vertex[3]);
            glEnd();

	    //glTranslated(0.0, 0.0, ground_intvl);
	    //}
	    //glTranslated(ground_intvl, 0.0, -ground_intvl * (ground_num/10));
	    //}
	    //glTranslated(-ground_intvl * (ground_num/20), 0.0, ground_intvl * (ground_num/20));
    // テクスチャマッピング終了
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

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
        int i, j, k, l;
	glBindTexture(GL_TEXTURE_2D, texname[3]);
        glBegin(GL_QUADS);

            for(i = 0; i < 6; ++i) {
	        glColor3dv(home_building_color);
            
                // 縦に張り合わせていく（壁一面を埋める）
                for(j = 0; j < wall_tate; ++j) {
                    // 横に貼り付けていく
                    for(k = 0; k < wall_yoko; ++k) {
                        // 正方形型のテクスチャを貼り付ける
                        for(l = 0; l < 4; ++l) {
                            glTexCoord2dv(texture_vertex[l]);
                            glVertex3dv(home_building_vertex[home_building_face[i][l]]);
                        }
                        glTranslated(0.0, 0.0, -wall_intvl);
                    }
                    glTranslated(0.0, -wall_intvl, wall_intvl*wall_yoko);
                }
                glTranslated(0.0, wall_intvl*wall_tate, 0.0);
            }

        glEnd();

    glDisable(GL_CULL_FACE);

    // テクスチャマッピング終了
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

// -------- 駅の建物の屋根を描く --------
void draw_home_building_roof() {
    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texname[4]);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

        // 駅の建物の屋根を描く
        int i, j, max;
        for(i = 0; i < 5; ++i) {
            if(i == 0) {
                glBegin(GL_QUADS);                
                    glColor3dv(home_building_roof_color);
                    max = 4;
                    for(j = 0; j < max; ++j) {
                        glVertex3dv(home_building_roof_vertex[home_building_roof_face[i][j]]);
                    }
                glEnd();
            } else {
                glBegin(GL_TRIANGLES);     
                    glColor3dv(home_building_roof_color);                    
                    max = 3;                    
                    for(j = 0; j < max; ++j) {
                        glTexCoord2dv(texture_triangle_vertex[j]);
                        glVertex3dv(home_building_roof_vertex[home_building_roof_face[i][j]]);
                    }
                glEnd();
            }
        }

    glDisable(GL_CULL_FACE);

    glBindTexture(GL_TEXTURE_2D, 0);
    // テクスチャマッピング終了
    glDisable(GL_TEXTURE_2D);
}


// -------- 線路の下の石を描く --------
void draw_stone_rail() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texname[0]);

    int i;
    glTranslated(0.0, 0.0, -stone_rail_intvl * (stone_rail_num/4));
    for (i = 0; i < stone_rail_num; ++i) {
        glBegin(GL_QUADS);
            glColor3d(1.0, 1.0, 1.0);
            glTexCoord2d(0.0, 1.0);
            glVertex3dv(stone_rail_vertex[0]);
            glTexCoord2d(0.0, 0.0);
            glVertex3dv(stone_rail_vertex[1]);
            glTexCoord2d(1.0, 0.0);
            glVertex3dv(stone_rail_vertex[2]);
            glTexCoord2d(1.0, 1.0);
            glVertex3dv(stone_rail_vertex[3]);
        glEnd();

	if(i < stone_rail_num/2) 
	    glTranslated(0.0, 0.0, stone_rail_intvl);
        else if(i == stone_rail_num/2)
	    glTranslated(-stone_rail_intvl, 0.0, 0.0);
	else
	    glTranslated(0.0, 0.0, -stone_rail_intvl);

    }

    glTranslated(stone_rail_intvl, 0.0, stone_rail_intvl * (stone_rail_num/4));
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


// -------- 線路を描く --------
void draw_rail() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    int i, j, k;
        // 線路の下敷きを描く
        glTranslated(0.0, 0.0, -rail_base_intvl * (num_of_base/2));
        for(k = 0; k < num_of_base; ++k) {
            glBegin(GL_QUADS);
                for(i = 0; i < 6; ++i) {
                    glColor3dv(rail_base_color);
                    for(j = 0; j < 4; ++j) {
                        glVertex3dv(rail_base_vertex[rail_base_face[i][j]]);
                    }
                }
            glEnd();
            glTranslated(0.0, 0.0, rail_base_intvl);
        }
        glTranslated(0.0, 0.0, -rail_base_intvl * (num_of_base/2));

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



// 各関数のポインタの配列
// ここから間接参照によって呼び出す
static void (*po[])() = {draw_ground, draw_cube, draw_axis, draw_rail, draw_home_building_roof, draw_home_building, draw_home_floor, draw_stone_rail};
static int order[] = {0, 1, 2, 7, 3, 4, 5, 6};
static int flags[] = {0};
// 配列の中の関数を入れ替える
static void swap(int i, int j) {
    int l = order[i];
    order[i] = order[j];
    order[j] = l;
}
// 条件によって描画の順番を変更する
void change_drawing_order() {
    // 建物の屋根と本体の描画順の交換
    // 下から屋根を見上げているときは、屋根を先に描く
    // 一方で、上から屋根を見下ろしているときは、建物を先に描く
    // 描画順を交換するのは、フラグが切り替わる時のみ
    int f = ((camerapos[1] >= home_building_roof_vertex[3][1]) && (!flags[0])) || ((camerapos[1] < home_building_roof_vertex[3][1]) && (flags[0]));
    if (f) {
        flags[0] = !flags[0]; swap(5, 6);
    }
}


// -------- 画面への表示に関する関数 --------
void display() {
    // ---- キャンバスを青空の色で塗りつぶす ----
    glClearColor(163.0 / 255.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // テスト（定められた描画順で描画する）
    // 条件に沿って、描画順を変更する
    change_drawing_order();
    int i;
    // 決められた描画順で描画関数を実行する
    for(i = 0; i < 8; ++i)
        (*po[order[i]])();

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
