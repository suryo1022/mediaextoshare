#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define RGB_TRANS 1.0 / 255.0

// RGB値たち
//-------- 背景色 --------
double sky_r = 33.0 * RGB_TRANS;
double sky_g = 59.0 * RGB_TRANS;
double sky_b = 31.0 * RGB_TRANS;
/* double mount_r = 91.0 * RGB_TRANS;
double mount_g = 98.0 * RGB_TRANS;
double mount_b = 52.0 * RGB_TRANS; */


//-------- 竹の色 --------
// 竹本体
double bam_r = 0 * RGB_TRANS;
double bam_g = 100*RGB_TRANS;
double bam_b = 0 * RGB_TRANS;
double bam2_r = 100 * RGB_TRANS;
double bam2_g = 100 * RGB_TRANS;
double bam2_b = 100 * RGB_TRANS;

// 竹の節
double bfushi_r = 0 * RGB_TRANS;
double bfushi_g = 255 * RGB_TRANS;
double bfushi_b = 0 * RGB_TRANS;

// たけのこの色
double stem_r = 72.0 * RGB_TRANS;
double stem_g = 68.0 * RGB_TRANS;
double stem_b = 44.0 * RGB_TRANS;


// -------- 竹を描画 --------
void draw_bamboo() {
    int i;
    for(i = 0; i < 3; ++i) {
        glBegin(GL_POLYGON);
            srand((unsigned int)time(NULL)*i);
            int random = rand();
            double x = (double)random / (double)RAND_MAX - ((random > RAND_MAX/2) ? 1 : 0);
            double a = random % 100 - 50;
            double w = 0.4;
            double b = 1.0 - a * x;
            double b2 = 1.0 - 0.1*(x + w);
            double h = 0.1;

            // 先ず、竹の全体像を描く
            glColor3d(bam_r, bam_g, bam_b);
            glVertex2d(x, 1.0);
            glVertex2d(x+(1.0-b)/a, -1.0);
            glColor3d(bam2_r, bam2_g, bam2_b);
            glVertex2d(x+(1.0-b)/a + w, -1.0);
            glVertex2d(x+w, 1.0);
        glEnd();

        glBegin(GL_POLYGON);
            // 次に、竹の節を描く
            // double y2 = rand() / RAND_MAX;
            // double x2 = (y2-b)/a;
            // double y3 = -(a*a+1)*y2 - sqrt((a*a+1)*(a*a+1) - (a*a+1)*((a*a+1)*y2*y2 - a*a*h*h));
            // double x3 = (y3-b)/a;
            // double x4 = (a*y3 - (y3-b)/a - a*b) / (a*a-1);
            // double y4 = a*x4 + b2;
            // double y5 = -(a*a+1)*y5 - sqrt((a*a+1)*(a*a+1) - (a*a+1)*((a*a+1)*y5*y5 - a*a*h*h));
            // glColor3d(bfushi_r, bfushi_g, bfushi_b);
            
        glEnd();
    }
}

// たけのこを描画
void draw_takenoko() {
    glBegin(GL_POLYGON);
        glColor3d(stem_r, stem_g, stem_b);
        double r = rand() / RAND_MAX;
        printf("r = %f\n", r);
        glVertex2d(r, 0.5);
        glColor3d(stem_r, 54*RGB_TRANS, stem_b);
        glVertex2d(r-0.1, -1.0);
        glVertex2d(r+0.1, -1.0);
    glEnd();
}

// 描画を行う関数
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    

    // 空の描画
    glBegin(GL_POLYGON);
        glColor3d(sky_r, sky_g, sky_b);
        glVertex2d(1.0, 1.0);
        glVertex2d(-1.0, 1.0);
        glColor3d(0, 0, 0);
        glVertex2d(-1.0, -1.0);
        glVertex2d(1.0, -1.0);
    glEnd();

    draw_bamboo();

    //draw_takenoko();

    /* // 山の描画
    glBegin(GL_POLYGON);
        glColor3d(mount_r, mount_g, mount_b);
        glVertex2d(0.3, 0.1);
        glVertex2d(-0.3, 0.1);
        glVertex2d(-1.0, -1.0);
        glVertex2d(1.0, -1.0);
    glEnd(); */

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