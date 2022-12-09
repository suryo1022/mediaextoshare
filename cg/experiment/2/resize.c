#include <stdio.h>
#include <GL/glut.h>
#include "input.h"

// -------- ウィンドウの拡大縮小に合わせてサイズを変える --------
void resize(int w, int h) {
    gluLookAt(camerapos[0], camerapos[1], camerapos[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

    // ビューポートを設定（ウィンドウ全体）
    glViewport(0, 0, w, h);

    // 透視変換行列の設定
    glMatrixMode(GL_PROJECTION);
    // 変換行列を単位行列にする
    glLoadIdentity();

    gluPerspective(30.0, (double)w / (double)h, 1.0, 500.0);

    printf("resized\n");

    //glMatrixMode(GL_MODELVIEW);
}
