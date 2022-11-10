#include <GL/glut.h>

// 描画を行う関数
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // 多角形描画開始
    glBegin(GL_POLYGON);
        glColor3d(1.0, 0.0, 0.0);
        glVertex2d(0.5, 0.5);
        glColor3d(0, 0, 0);
        glVertex2d(-0.5, -0.5);
        glVertex2d(-0.3, -0.7);
        glVertex2d(0.7, 0.3);
    glEnd();
    glFlush();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char* argv[]) {

    // GLUTを初期化
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // ウィンドウの作成
    glutCreateWindow(argv[0]);

    // 描画
    glutDisplayFunc(display);

    init();

    // イベント発生まで待機
    glutMainLoop();

    return 0;
}