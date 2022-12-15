#include <stdio.h>
#include <GL/glut.h>
#include "input.h"
#include "display.h"
#include "resize.h"
#include "texture.h"
#include "light.h"

// -------- main関数 --------
int main(int argc, char *argv[]) {
    // ----  ウィンドウサイズ指定 ----
    glutInitWindowSize(960, 720);
  
    // ---- 初期化 ----
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // ---- ウィンドウを作成する ----
    glutCreateWindow(argv[0]);

    // ---- テクスチャ設定の初期化 ----
    init_texture();

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