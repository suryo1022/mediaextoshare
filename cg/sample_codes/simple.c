#include <GL/glut.h>

// 描画関数
void display(void) {
}

int main(int argc, char *argv[]) {
    // 初期化
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_RGBA);
    // ウィンドウを開く
    glutCreateWindow(argv[0]);
    // 描画関数の設定
    glutDisplayFunc(display);
    // OpenGLの初期設定
    // 無限ループ
    glutMainLoop();
    return 0;
}