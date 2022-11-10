#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include "main.h"

GLuint texid[20];

/*移動関係*/
void idle(void){
    glutPostRedisplay();
}

void Move(int _id){
    static int timer = 0;
    timer++;
    switch (_id){
    case -1: /*停止*/
        glutIdleFunc(0);
        break;
    case 0: /*前方移動*/
        player_x += 0.1 * M_SIN[theta];
        player_z -= 0.1 * M_COS[theta];
        break;
    case 1: /*後方移動*/
        player_x -= 0.1 * M_SIN[theta];
        player_z += 0.1 * M_COS[theta];
        break;
    case 2: /*左回転*/
        /* 一周回ったら回転角を 0 に戻す */
        if (--theta <= 0) theta = 360;
        muki_x = r * M_SIN[theta];
        muki_z = -r * M_COS[theta];
        break;
    case 3: /*右回転*/
        /* 一周回ったら回転角を 0 に戻す */
        if (++theta >= 360) theta = 0;
        muki_x = r * M_SIN[theta];
        muki_z = -r * M_COS[theta];
        break;
    case 4: /*視点移動上*/
        if (timer % 2 == 0){
            if (muki_y < 2.0){
                muki_y += 0.01;
            }
        }
        break;
    case 5: /*視点移動下*/
        if (timer % 2 == 0){
            if (muki_y > 0.5){
                muki_y -= 0.01;
            }
        }
        break;
    default:
        break;
    }
}

/*円柱を描画/高さ/半径*/
void Cylinder(double height, double radius, GLfloat *color){
    int i;

    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    /*上面*/
    glNormal3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (i = 0; i < sides; i++) {
        glVertex3d(radius * SIN[i], height, radius * COS[i]);
    }
    glEnd();
    /*下面*/
    glNormal3d(0.0, -1.0, 0.0);
    glBegin(GL_POLYGON);
    for (i = sides; --i >= 0;) {
        glVertex3d(radius * SIN[i], 0.0, radius * COS[i]);
    }
    glEnd();
    /* 側面 */
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= sides; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(x, 0.0, z);
        glVertex3f(radius * x, height, radius * z);
        glVertex3f(radius * x, 0.0, radius * z);
    }
    glEnd();
    glPopMatrix();
}

/*鳥居のパーツ1の描画*/
void Gate_1(){
    int i;
    int j;
    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    /* 図形の描画 */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_gate_1[face[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}
/*鳥居のパーツ2の描画*/
void Gate_2(){
    int i;
    int j;
    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    /* 図形の描画 */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_gate_2[face[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}
/*鳥居のパーツ3の描画*/
void Gate_3(){
    int i;
    int j;
    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
    /* 図形の描画 */
    glBegin(GL_QUADS);
    for (j = 0; j < 14; ++j) {
        glNormal3dv(normal_gate_3[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_gate_3[face_gate_3[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}

/*鳥居の描画*/
void GuardFrame(){
    glPushMatrix();
    glTranslated(-0.25, 1.7, -0.05);
    Gate_1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.25, 2.0, -0.05);
    Gate_1();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.65, 1.75, -0.025);
    Gate_2();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.02, 2.08, -0.075);
    Gate_3();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.4, 0.0);
    Cylinder(1.6, 0.1, red);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, 0.4, 0.0);
    Cylinder(1.6, 0.1, red);
    glPopMatrix();

    glPushMatrix();
    Cylinder(0.4, 0.1, black);
    glPopMatrix();

    glPushMatrix();
    glTranslated(1.5, 0.0, 0.0);
    Cylinder(0.4, 0.1, black);
    glPopMatrix();
}

/*地面の描画*/
void Ground(){
    glPushMatrix();
    /* 図形の色 (白) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[2]);

    /* 図形の描画 */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2d(0.0, 10.0);
    glVertex3d(-50.0, 0.0, -50.0);
    glTexCoord2d(10.0, 10.0);
    glVertex3d(-50.0, 0.0, 50.0);
    glTexCoord2d(10.0, 0.0);
    glVertex3d(50.0, 0.0, 50.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(50.0, 0.0, -50.0);
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*砂利の描画*/
void Stones(){
    glPushMatrix();
    /* 図形の色 (白) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[1]);

    /* 図形の描画 */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 0.0);
    glTexCoord2d(0.0, 2.0);
    glVertex3d(-1.0, 0.0, -1.0);
    glTexCoord2d(2.0, 2.0);
    glVertex3d(-1.0, 0.0, 1.0);
    glTexCoord2d(2.0, 0.0);
    glVertex3d(1.0, 0.0, 1.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(1.0, 0.0, -1.0);
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*石畳(大)の描画*/
void Stone(){
    int j;
    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[0]);

    /* 図形の描画 */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        glTexCoord2d(0.0, 2.0);
        glVertex3dv(vertex_stone[face[j][0]]);
        glTexCoord2d(1.0, 2.0);
        glVertex3dv(vertex_stone[face[j][1]]);
        glTexCoord2d(1.0, 0.0);
        glVertex3dv(vertex_stone[face[j][2]]);
        glTexCoord2d(0.0, 0.0);
        glVertex3dv(vertex_stone[face[j][3]]);
    }
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*石畳(小)の描画*/
void Stone_s(){
    int j;
    glPushMatrix();
    /* 図形の色 (白) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[0]);

    /* 図形の描画 */
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        glTexCoord2d(0.0, 1.0);
        glVertex3dv(vertex_stone_s[face[j][0]]);
        glTexCoord2d(3.0, 1.0);
        glVertex3dv(vertex_stone_s[face[j][1]]);
        glTexCoord2d(3.0, 0.0);
        glVertex3dv(vertex_stone_s[face[j][2]]);
        glTexCoord2d(0.0, 0.0);
        glVertex3dv(vertex_stone_s[face[j][3]]);
    }
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*木の葉の描画*/
void Leaf(){
    glPushMatrix();

    glTranslated(0.0, 0.0, 0.0);

    /* 図形の色 (白) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* アルファテスト開始 */
    glEnable(GL_ALPHA_TEST);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid[3]);

    /* 図形の描画 */
    /* １枚の４角形を描く */
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(-2.0, -2.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(2.0, -2.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(2.0, 2.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(-2.0, 2.0, 0.0);
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    /* アルファテスト終了 */
    glDisable(GL_ALPHA_TEST);

    glPopMatrix();
}

/*木の描画*/
void Tree(){
    int i;
    /*葉の描画*/
    for (i = 0; i < 10; i++){
        glPushMatrix();
        glRotated(360 / 20 * i, 0.0, 1.0, 0.0);
        glTranslated(0.0, 2.5, 0.0);
        Leaf();
        glRotated(180, 0.0, 1.0, 0.0);
        Leaf();
        glPopMatrix();
    }
    /*幹の描画*/
    glPushMatrix();
    Cylinder(1.0, 0.1, tree_color);
    glPopMatrix();
}

/*本堂の屋根の描画*/
void loof_2(){
    int i;
    int j;

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 3 * sides / 4; i <= sides; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, -x, -z);
        glVertex3f(6.0, 2.0 * x, 2.0 * z);
        glVertex3f(0.0, 2.0 * x, 2.0 * z);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, 0.0, 4.0);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = sides / 2; i <= 3 * sides / 4; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, x, z);
        glVertex3f(6.0, 2.0 * x, 2.0 * z);
        glVertex3f(0.0, 2.0 * x, 2.0 * z);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -0.4, 0.4);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 3 * sides / 4; i <= sides; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, x, z);
        glVertex3f(0.0, 1.6 * x, 1.6 * z);
        glVertex3f(6.0, 1.6 * x, 1.6 * z);

    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -0.4, 3.6);
    glBegin(GL_TRIANGLE_STRIP);
    for (i = sides / 2; i <= 3 * sides / 4; i++) {
        double x = SIN[i];
        double z = COS[i];
        glNormal3d(0.0, -x, -z);
        glVertex3f(0.0, 1.6 * x, 1.6 * z);
        glVertex3f(6.0, 1.6 * x, 1.6 * z);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -2.0, 2.0);
    glNormal3d(-1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(0.0, 0.0, 1.6);
    for (i = 90; i > 0; i--){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), 2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), 1.6 * (1.0 - M_COS[i]));
    }
    for (i = 0; i <= 90; i++){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), -2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), -1.6 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(6.0, -2.0, 2.0);
    glNormal3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(0.0, 0.0, -1.6);
    for (i = 90; i > 0; i--){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), -2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), -1.6 * (1.0 - M_COS[i]));
    }
    for (i = 0; i < 90; i++){
        glVertex3d(0.0, 2.02 * (1.0 - M_SIN[i]), 2.02 * (1.0 - M_COS[i]));
        glVertex3d(0.0, 1.6 * (1.0 - M_SIN[i]), 1.6 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_red);
    glTranslated(0.4, -2.0, 2.01);
    glNormal3d(-1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0.0, 0.0, 0.0);
    for (i = 90; i >= 0; i--){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), 1.8 * (1.0 - M_COS[i]));
    }
    for (i = 0; i < 90; i++){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), -1.8 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (赤) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_red);
    glTranslated(5.6, -2.0, 2.01);
    glNormal3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3d(0.0, 0.0, 0.0);
    for (i = 90; i >= 0; i--){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), -1.8 * (1.0 - M_COS[i]));
    }
    for (i = 0; i <= 90; i++){
        glVertex3d(0.0, 1.8 * (1.0 - M_SIN[i]), 1.8 * (1.0 - M_COS[i]));
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    /* 図形の色 (黒) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_black);
    glTranslated(0.0, -2.090, 0.0);
    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        if (j == 4){
            /* 図形の色 (赤) */
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, loof_red);
        }
        glNormal3dv(normal[j]);
        for (i = 0; i < 4; ++i) {
            glVertex3dv(vertex_loof_box[face[j][i]]);
        }
    }
    glEnd();
    glPopMatrix();
}

/*本堂の壁の描画*/
void wall(GLuint _tex){
    glPushMatrix();
    /* 図形の色 (白) */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tex);

    /* 図形の描画 */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(1.0, 2.0, 0.0);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(1.0, 0.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(0.0, 2.0, 0.0);
    glEnd();

    /* 図形の描画 */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(0.0, 0.0, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(1.0, 0.0, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(1.0, 2.0, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(0.0, 2.0, 0.0);
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*本堂のパーツ1*/
/*_tex : 貼り付けるテクスチャ _i : 貼り付ける面 _color : 色*/
void shrine_1(GLuint _tex, int i, GLfloat *_color){
    /* 図形の色 */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _color);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glBegin(GL_QUADS);
    glNormal3dv(normal[i]);
    glTexCoord2d(1.0, 1.0);
    glVertex3dv(vertex_box_1[face[i][0]]);
    glTexCoord2d(1.0, 0.0);
    glVertex3dv(vertex_box_1[face[i][1]]);
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(vertex_box_1[face[i][2]]);
    glTexCoord2d(0.0, 1.0);
    glVertex3dv(vertex_box_1[face[i][3]]);
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

/*本堂のパーツ2*/
/*_tex : 貼り付けるテクスチャ _i : 貼り付ける面 _color : 色*/
void shrine_2(GLuint _tex, int i, GLfloat *_color){
    /* 図形の色 */
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, _color);

    /* テクスチャマッピング開始 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _tex);
    glBegin(GL_QUADS);
    glNormal3dv(normal[i]);
    glTexCoord2d(1.0, 1.0);
    glVertex3dv(vertex_box_2[face[i][0]]);
    glTexCoord2d(1.0, 0.0);
    glVertex3dv(vertex_box_2[face[i][1]]);
    glTexCoord2d(0.0, 0.0);
    glVertex3dv(vertex_box_2[face[i][2]]);
    glTexCoord2d(0.0, 1.0);
    glVertex3dv(vertex_box_2[face[i][3]]);
    glEnd();

    /* テクスチャマッピング終了 */
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

/*本堂の描画*/
void Shrine(){
    int i;

    /*屋根*/
    glPushMatrix();
    glTranslated(0.0, 6.0, 0.0);
    loof_2();
    glPopMatrix();

    /*屋根/右*/
    glPushMatrix();
    glScaled(2.0, .5, .5);
    glTranslated(2.5, 6.0, 2.0);
    loof_2();
    glPopMatrix();

    /*屋根/左*/
    glPushMatrix();
    glScaled(2.0, .5, .5);
    glTranslated(-5.5, 6.0, 2.0);
    loof_2();
    glPopMatrix();

    /*壁/左*/
    for (i = 0; i < 11; i++){
        glPushMatrix();
        glTranslated(-1.0 * i, 0.0, 1.5);
        wall(texid[12]);
        glTranslated(0.0, 0.0, 1.0);
        Cylinder(2.0, 0.05, loof_red);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-10.0, 0.0, 1.5);
    glRotated(-90, 0.0, 1.0, 0.0);
    wall(texid[10]);
    glPopMatrix();

    /*壁/右*/
    for (i = 0; i < 11; i++){
        glPushMatrix();
        glTranslated(1.0 * i + 5.0, 0.0, 1.5);
        wall(texid[12]);
        glTranslated(1.0, 0.0, 1.0);
        Cylinder(2.0, 0.05, loof_red);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(16.0, 0.0, 1.5);
    glRotated(-90, 0.0, 1.0, 0.0);
    wall(texid[10]);
    glPopMatrix();

    /*本体1*/
    glPushMatrix();
    glTranslated(1.0, 2.5, 0.5);
    shrine_1(texid[6], 0, white);
    shrine_1(texid[7], 1, white);
    shrine_1(texid[7], 2, white);
    shrine_1(texid[7], 3, white);
    shrine_1(texid[11], 4, white);
    glPopMatrix();

    /*本体2*/
    glPushMatrix();
    glTranslated(1.0, 0.0, 0.5);
    shrine_2(texid[4], 0, white);
    shrine_2(texid[10], 1, white);
    shrine_2(texid[8], 2, white);
    shrine_2(texid[10], 3, white);

    glTranslated(3.0, 0.0, 0.0);
    shrine_2(texid[5], 0, white);
    shrine_2(texid[10], 1, white);
    shrine_2(texid[9], 2, white);
    shrine_2(texid[10], 3, white);

    glPopMatrix();
}

/*鳥居を円形に配置/m: 初期値/n: 最終値*/
void Circle_Gate(int m, int n){
    int i;
    for (i = m; i <= n; i++){
        glPushMatrix();
        glTranslated(4.0 * M_COS[(int)((360 / 72) * i)], 0.0, 4.0 * M_SIN[(int)((360 / 72) * i)]);
        glRotated((-360. / 72) * i, 0.0, 1.0, 0.0);
        GuardFrame();
        glPopMatrix();
    }
}

/*描画*/
void display(void){
    int i;
    int j;

    /*デバッグ*/
    //printf("theta: %f, muki_x: %f, muki_z: %f \n", (double)theta, (double)muki_x, (double)muki_z);
    //printf("player_x: %f, player_z: %f \n", (double)player_x, (double)player_z);
    //printf("move_id: %d \n", move_id);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    /*移動*/
    Move(move_id);

    /* 視点位置と視線方向 */
    gluLookAt(0.0 + player_x, 0.5, r + player_z, muki_x + player_x, muki_y, r + muki_z + player_z, 0.0, 1.0, 0.0);


    /* 光源の位置設定 */
    glPushMatrix();
    glTranslated(light_pos, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glPopMatrix();
    //glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

    /*地面*/
    glPushMatrix();
    glTranslated(0.0, -0.1, 45.0);
    Ground();
    glPopMatrix();

    /*ここから鳥居*/
    for (i = 0; i < 50; i++){
        glPushMatrix();
        glTranslated(0.0, 0.0, 25 + 0.5 * i);
        GuardFrame();
        glTranslated(3.0, 0.0, 0.0);
        GuardFrame();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(-4.0, 0.0, 50.0);
    Circle_Gate(0, 18);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.0, 0.0, 59.5);
    Circle_Gate(18, 53);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.5, 0.0, 50.0);
    Circle_Gate(18, 36);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.5, 0.0, 59.5);
    Circle_Gate(0, 18);
    Circle_Gate(54, 71);
    glPopMatrix();

    for (i = 1; i < 25; i++){
        glPushMatrix();    
        glTranslated(-4.0 + 0.5 * i, 0.0, 65.0);
        glRotated(90, 0.0, 1.0, 0.0);
        GuardFrame();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslated(0.0, 0.0, 5.0);
    glScaled(2.0, 2.0, 2.0);
    GuardFrame();
    glPopMatrix();
    /*ここで鳥居終了*/

    /*ここから砂利*/
    for (i = 0; i < 26; i++){
        glPushMatrix();
        glTranslated(0.8, 0.0, 25.0 + 1.0 * i);
        Stones();
        glTranslated(3.0, 0.0, 0.0);
        Stones();
        glPopMatrix();
    }
    for (i = 0; i < 22; i++){
        for (j = 0; j < 14; j++){
            glPushMatrix();
            glTranslated(-9.2 + 1.0 * i, 0.0, 52.0 + 1.0 * j);
            Stones();
            glTranslated(3.0, 0.0, 0.0);
            Stones();
            glPopMatrix();
        }
    }
    for (i = 0; i < 22; i++){
        for (j = 0; j < 14; j++){
            glPushMatrix();
            glTranslated(-9.2 + 1.0 * i, 0.0, 10 + 1.0 * j);
            Stones();
            glTranslated(3.0, 0.0, 0.0);
            Stones();
            glPopMatrix();
        }
    }
    /*ここで砂利終了*/

    /*石畳(大)*/
    for (i = 0; i < 80; i++){
        glPushMatrix();
        glTranslated(0.45, 0.0, 25.0 + 0.32 * i);
        Stone();
        glTranslated(3.0, 0.0, 0.0);
        Stone();
        glPopMatrix();
    }

    /*ここから石畳(小)*/
    for (i = 0; i < 40; i++){
        glPushMatrix();
        glTranslated(0.24, 0.0, 25.0 + 0.64 * i);
        Stone_s();
        glTranslated(0.82, 0.0, 0.0);
        Stone_s();
        glPopMatrix();
    }
    for (i = 0; i < 40; i++){
        glPushMatrix();
        glTranslated(3.24, 0.0, 25.0 + 0.64 * i);
        Stone_s();
        glTranslated(0.82, 0.0, 0.0);
        Stone_s();
        glPopMatrix();
    }
    /*ここで石畳(小)終了*/

    /*本堂の描画*/
    glPushMatrix();
    glTranslated(-1.0, 0.0, 15.0);
    Shrine();
    glPopMatrix();

    /*ここから木*/
    for (i = 0; i < 2; i++){
        for (j = 0; j < 14; j++){
            glPushMatrix();
            glTranslated(-2.0 - (2.0 * i), 0.0, 25.0 + 2.0 * j);
            Tree();
            glTranslated(10.5, 0.0, 0.0);
            Tree();
            glPopMatrix();
        }
    }
    for (i = 0; i < 15; i++){
            glPushMatrix();
            glTranslated(-10.0 + (2.0 * i), 0.0, 67.0);
            Tree();
            glPopMatrix();
        }
    /*ここで木終了*/

    glFlush();

    glutSwapBuffers();
}

/*初期化*/
void init(void){
    int i;
    int ret;
    int data[4];
    static int n = 0;

    int img_size[20];
    int param[20];
    int height[20];
    int width[20];

    static int f_num = 0;

    static const char *file[] = {
        "stone_3.raw",
        "stone_2.raw",
        "ground.raw",
        "leaf.raw",
        "shrine_1.raw",
        "shrine_2.raw",
        "shrine_3.raw",
        "shrine_4.raw",
        "shrine_5.raw",
        "shrine_6.raw",
        "shrine_7.raw",
        "shrine_8.raw",
        "shrine_9.raw",
    };

    /*テクスチャ関係--------------------------------------------------------------------------------*/

    /* テクスチャ環境 */
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    GLubyte *_texture;

    FILE *fp;

    /* テクスチャ画像の読み込み------------------------------------------------------------------------*/

    if ((fp = fopen("image_data.csv", "r")) != NULL){
        while ((ret = fscanf(fp, "%d, %d, %d, %d", &data[0], &data[1], &data[2], &data[3])) != EOF){
            img_size[n] = data[0];
            param[n] = data[1];
            height[n] = data[2];
            width[n] = data[3];
            n++;
            f_num++;
            printf("%d, %d, %d, %d\n", data[0], data[1], data[2], data[3]);
        }
        fclose(fp);
    }

    for (i = 0; i < f_num; i++){
        _texture = (GLubyte *)malloc(img_size[i]);

        if ((fp = fopen(file[i], "rb")) != NULL) {
            fread(_texture, img_size[i], 1, fp);
            fclose(fp);
        }
        else {
            perror(file[i]);
        }
        glGenTextures(1, &texid[i]); // テクスチャIDを生成
        glBindTexture(GL_TEXTURE_2D, texid[i]);
        /* テクスチャ画像はバイト単位に詰め込まれている */
        glPixelStorei(GL_UNPACK_ALIGNMENT, param[i]);

        /* テクスチャの割り当て */
        if (param[i] == 1){
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width[i], height[i],
                GL_RGB, GL_UNSIGNED_BYTE, _texture);
        }
        else{
            gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width[i], height[i],
                GL_RGBA, GL_UNSIGNED_BYTE, _texture);
        }

        /* テクスチャを拡大・縮小する方法の指定 */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        free(_texture);
    }

    /* アルファテストの比較関数 */
    glAlphaFunc(GL_GREATER, 0.5);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /*テクスチャ関係終了------------------------------------------------------------------------------*/

    glClearColor(160. / 256., 216 / 256., 236 / 256., 1.0);

    /*円の描画に使うsinとcosの値を先に計算しておく*/
    double step = 2 * PI / (double)sides;
    for (i = 0; i <= sides; i++){
        double t = step * (double)i;
        SIN[i] = sin(t);
        COS[i] = cos(t);
    }

    /*視点向きに使うsinとcosの値を先に計算しておく*/
    for (i = 0; i <= 360; i++){
        M_SIN[i] = sin(2 * PI * (double)i / 360.);
        M_COS[i] = cos(2 * PI * (double)i / 360.);
    }

}

void resize(int w, int h){
    glViewport(0, 0, w, h);

    /* 透視変換行列の設定 */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (double)w / (double)h, 0.5, 100.0);

    /* モデルビュー変換行列の設定 */
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
}

void mouse(int button, int state, int x, int y){}

/*キーを押したとき*/
void keyboarddown(unsigned char key, int x, int y){
    switch (key) {
    case 'z':
        move_id = 4;
        glutIdleFunc(idle);
        break;
    case 'x':
        move_id = 5;
        glutIdleFunc(idle);
        break;
    case 'c':
        if (++light_pos >= 300) light_pos = -500;
        glutIdleFunc(idle);
        break;
    case 'q':
    case 'Q':
    case '\033':  /* '\033' は ESC の ASCII コード */
        exit(0);
    default:
        break;
    }
}

/*キーを離したとき*/
void keyboardup(unsigned char key, int x, int y){
    switch (key) {
    case 'z':
    case 'x':
        move_id = -1;
        break;
    case 'c':
        glutIdleFunc(0);
        break;
    default:
        break;
    }
}

/*キーを押したとき*/
void specialkeydown(int key, int x, int y)
{
    switch (key){
    case GLUT_KEY_UP:
        move_id = 0;
        //move_x += 0.1 * sin(2 * PI * (double)theta / 360);
        //move_z -= 0.1 * cos(2 * PI * (double)theta / 360);
        glutIdleFunc(idle);
        break;
    case GLUT_KEY_DOWN:
        move_id = 1;
        //move_x -= 0.1 * sin(2 * PI * (double)theta / 360);
        //move_z += 0.1 * cos(2 * PI * (double)theta / 360);
        glutIdleFunc(idle);
        break;
    case GLUT_KEY_LEFT:
        move_id = 2;
        //muki_x = r * sin(2 * PI * (double)theta / 360.);
        //muki_z = -r * cos(2 * PI * (double)theta / 360.);
        glutIdleFunc(idle);
        break;
    case GLUT_KEY_RIGHT:
        move_id = 3;
        //muki_x = r * sin(2 * PI * (double)theta / 360.);
        //muki_z = -r * cos(2 * PI * (double)theta / 360.);
        glutIdleFunc(idle);
        break;
    default:
        break;
    }
}

/*キーを離したとき*/
void specialkeyup(int key, int x, int y)
{
    switch (key){
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        move_id = -1;
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[]){
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 320);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboarddown);
    glutKeyboardUpFunc(keyboardup);
    glutSpecialFunc(specialkeydown);
    glutSpecialUpFunc(specialkeyup);
    init();
    glutMainLoop();
    return 0;
}

