#include <GL/glut.h>

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
