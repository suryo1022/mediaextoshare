#include <GL/glut.h>
#include <stdio.h>
#include "input.h"
#include "object.h"
#include "texture.h"
#include "light.h"

// -------- プロトタイプ宣言 --------
void draw_cube();
void draw_axis();
void draw_ground();
void draw_stone_rail();
void draw_home_floor();
void draw_home_building();
void draw_home_building_roof();
void draw_rail();


// 各関数のポインタの配列
// ここから間接参照によって呼び出す
static void (*po[])() = {draw_ground, draw_axis, draw_rail, draw_home_building_roof, draw_home_building, draw_home_floor, draw_stone_rail};
static int order[] = {0, 1, 2, 3, 4, 5};
// 1番目のフラグ：建物と屋根の描画順番を変えるステートになったか否か
// 2番目のフラグ：建物の左横と右横の描画順番を変えるステートになったか否か
// 3番目のフラグ：建物と駅の床の描画順番を変えるステートになったか否か
static int flags[] = {0, 0, 0};
// 配列の中の関数を入れ替える
void swap(int i, int j, int hairetsu[]) {
    int l = hairetsu[i];
    hairetsu[i] = hairetsu[j];
    hairetsu[j] = l;
}
// 条件によって描画の順番を変更する
void change_drawing_order() {
    // 建物の屋根と本体の描画順の交換
    // 下から屋根を見上げているときは、屋根を先に描く
    // 一方で、上から屋根を見下ろしているときは、建物を先に描く
    // 描画順を交換するのは、フラグが切り替わる時のみ
    int f = ((camerapos[1] >= home_building_roof_vertex[3][1]) && (!flags[0])) || ((camerapos[1] < home_building_roof_vertex[3][1]) && (flags[0]));
    if (f) {
        flags[0] = !flags[0]; swap(3, 4, order);
    }

    int f2 = ((camerapos[0] >= home_floor_vertex[1][0]) && (!flags[2])) || ((camerapos[0] < home_floor_vertex[1][0]) && (flags[2]));
    if (f2) {
        flags[2] = !flags[2]; swap(4, 5, order);
    }
}



// -------- 座標軸を描く --------
void draw_axis() {
    int i;
    // フラグが立っていないときは描かない
    if(!axis_flag) return;

    for(i = 0; i < 3; ++i) {
        glBegin(GL_LINES);
	    glColor3dv(axis_color[i]);
	    glVertex3dv(axis_vertex[axis_edge[i][0]]);
            glVertex3dv(axis_vertex[axis_edge[i][1]]);
	glEnd();
    }    
}


// -------- 海を描く --------
void draw_ground() {
    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    int i, j;
    glTranslated(-ground_intvl * (ground_num/20), 0.0, -ground_intvl * (ground_num/20));
    for(i = 0; i < ground_num/10; ++i) {
        for(j = 0; j < ground_num/10; ++j) {
	    // 海を描く
	    glBindTexture(GL_TEXTURE_2D, texname[1]);


            // 材質を設定
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, green);

            glBegin(GL_QUADS);
                // 法線を与える
                glNormal3dv(ground_normal);
                glColor3dv(ground_color);
                glTexCoord2d(0.0, 0.0);
                    glVertex3dv(ground_vertex[0]);
                glTexCoord2d(1.0, 0.0);
                    glVertex3dv(ground_vertex[1]);
                glTexCoord2d(1.0, 1.1);
                    glVertex3dv(ground_vertex[2]);
                glTexCoord2d(0.0, 1.0);
                    glVertex3dv(ground_vertex[3]);
            glEnd();

	        glTranslated(0.0, 0.0, ground_intvl);
	    }
	    glTranslated(ground_intvl, 0.0, -ground_intvl * (ground_num/10));
	}
	glTranslated(-ground_intvl * (ground_num/20), 0.0, ground_intvl * (ground_num/20));
    // テクスチャマッピング終了

    glDisable(GL_CULL_FACE);
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
        int i, j, k, l, m;
        glBindTexture(GL_TEXTURE_2D, texname[3]);


        // 材質を設定
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, green);

        for(i = 0; i < 6; ++i) {
            // 法線を指定
            glNormal3dv(home_floor_normal[i]);

            if(i == 0) {
                for(k = 0; k < home_floor_tate; ++k) {
                    for(l = 0; l < home_floor_yoko; ++l) {
                        glBegin(GL_QUADS);
                            for(m = 0; m < 4; ++m) {
                                glTexCoord2dv(texture_vertex[m]);
                                glVertex3dv(home_floor_vertex[m+8]);
                            }
                        glEnd();
                        glTranslated(home_floor_intvl, 0.0, 0.0);
                    }
                    glTranslated(-home_floor_intvl*home_floor_yoko, 0.0, home_floor_intvl);
                }
                glTranslated(0.0, 0.0, -home_floor_intvl*home_floor_tate);
            } else {
                glBegin(GL_QUADS);
                    for(j = 0; j < 4; ++j) {
                        //glColor3dv(home_floor_color[0]);
                        glTexCoord2dv(texture_vertex[j]);
                        glVertex3dv(home_floor_vertex[home_floor_face[i][j]]);
                    }
                glEnd();
            }

        }

    glDisable(GL_CULL_FACE);

    // テクスチャマッピング終了
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

// 面の描画順
static int building_face_order[6] = {0, 1, 2, 3, 4, 5};

// -------- 駅の建物を描く --------
void draw_home_building() {

    // テクスチャマッピングができるようにしておく
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    int i, j, k, l;
	glBindTexture(GL_TEXTURE_2D, texname[3]);


    // 自分がいる場所によって描画の順番を変える
    int f = ((camerapos[2] < home_building_vertex[15][2]) && (!flags[1])) || ((camerapos[2] >= home_building_vertex[15][2]) && (flags[1]));
    if (f) {
        flags[1] = !flags[1]; swap(3, 4, building_face_order);
    }


    for(l = 0; l < 6; ++l) {
        // 正方形を複製して面を作る
        for(k = 0; k < wall_tate; ++k) {
            for(j = 0; j < wall_yoko; ++j) {
                // 一つの正方形を描く
                // 窓を描くため
                if(l != 1 && l != 2 && (k == 2 || k == 3) && (j >= 1 && j <= 3)) {
                    // do nothing
                } else {

                    // 面はすべて両面にする
                    // 裏面
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, ground_material);
                    glBegin(GL_QUADS);
                        for(i = 0; i < 4; ++i) {
                            // 法線を与える
                            glNormal3dv(home_building_normal[building_face_order[l]]);
                            //glColor3dv(home_building_color);
                            glTexCoord2dv(texture_vertex[i]);
                            glVertex3dv(home_building_vertex[building_face_order[l]*4 + 3-i]);
                        }
                    glEnd();
                    // 表面
                    glBegin(GL_QUADS);
                        for(i = 0; i < 4; ++i) {
                            // 法線を与える
                            glNormal3dv(home_building_normal[building_face_order[l]]);
                            //glColor3dv(home_building_color);
                            glTexCoord2dv(texture_vertex[i]);
                            glVertex3dv(home_building_vertex[building_face_order[l]*4 + i]);
                        }
                    glEnd();

                }
                glBindTexture(GL_TEXTURE_2D, texname[3]);
                // 横の場合
                (l == 3 || l == 4) ? glTranslated(-wall_intvl, 0.0, 0.0) : glTranslated(0.0, 0.0, wall_intvl);
            }
            // 前、後ろの場合
            if(l == 0 || l == 5) glTranslated(0.0, wall_intvl, -wall_intvl*wall_yoko);
            // 横の場合
            else if(l == 3 || l == 4) glTranslated(wall_intvl*wall_yoko, wall_intvl, 0.0);
            else glTranslated(wall_intvl, 0.0, -wall_intvl*wall_yoko);
        }
        // 上、下の場合
        if(l == 1 || l == 2) glTranslated(-wall_intvl*wall_tate, 0.0, 0.0);
        else glTranslated(0.0, -wall_intvl*wall_tate, 0.0);
    }

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
                    //glColor3dv(home_building_roof_color);
                    max = 4;
                    for(j = 0; j < max; ++j) {
                        glVertex3dv(home_building_roof_vertex[home_building_roof_face[i][j]]);
                    }
                glEnd();
            } else {
                glBegin(GL_TRIANGLES);     
                    //glColor3dv(home_building_roof_color);                    
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
            //glColor3d(1.0, 1.0, 1.0);
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

            //glDisable(GL_COLOR_MATERIAL);
            // マテリアルを設定
            glMaterialf(GL_FRONT, GL_SPECULAR, (1.0, 1.0, 1.0, 1.0));
            glMaterialf(GL_FRONT, GL_SHININESS, 128);


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
        glMaterialf(GL_FRONT, GL_DIFFUSE, (0.0, 0.0, 0.0, 1.0));
        glMaterialf(GL_FRONT, GL_SPECULAR, (0.0, 0.0, 0.0, 1.0));

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


// -------- 画面への表示に関する関数 --------
void display() {

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    switch(time_flag) {
        // 昼
        case 0: 
            glClearColor(163.0 / 255.0, 1.0, 1.0, 1.0);
            break;        
        // 夜
       case 1:
            glClearColor(0.0/255.0, 0.0/255.0, 0.0/255.0, 1.0);
            glEnable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);
            break;
        default:
            break;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    //　モデルビュー変換行列の指定の後、カメラの位置、視点の位置を指定
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camerapos[0], camerapos[1], camerapos[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

    // 条件に沿って、描画順を変更する
    change_drawing_order();
    int i;
    // 決められた描画順で描画関数を実行する
    for(i = 0; i < 6; ++i)
        (*po[order[i]])();


    
    // ライティングを行う
    //glEnable(GL_LIGHTING);
    
    // 光源の設定
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);

    // ---- 残った処理をすべて実行 ----
    glFlush();
}
