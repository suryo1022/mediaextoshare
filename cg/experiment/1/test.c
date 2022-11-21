#include <GL/glut.h>
#include <math.h>
#include <GL/gl.h>
#include <stdio.h>


// ---------------- 色の定義 -----------------
#define RGB_TRANS 1.0/255.0  // 0-1スケールへ変換するもの

// -------- 空の色 --------
// 空の下の方
double sky_r = 255.0 * RGB_TRANS;
double sky_g = 185.0 * RGB_TRANS;
double sky_b = 99.0 * RGB_TRANS;
// 空の上の方
double sky2_r = 0.0 * RGB_TRANS;
double sky2_g = 0.0 * RGB_TRANS;
double sky2_b = 255.0 * RGB_TRANS;

// -------- 太陽の色 --------
// 太陽の内側
double sun_r = 255.0 * RGB_TRANS;
double sun_g = 0.0 * RGB_TRANS;
double sun_b = 0.0 * RGB_TRANS;
double sun2_r = 200.0 * RGB_TRANS;
double sun2_g = 0.0 * RGB_TRANS;
double sun2_b = 0.0 * RGB_TRANS;

// -------- 太陽のオーラの色 --------
// 定義は、太陽のオーラを描く関数の中で

// -------- 海の色 --------
double sea_r = 116.0 * RGB_TRANS;
double sea_g = 80.0 * RGB_TRANS;
double sea_b = 142.0 * RGB_TRANS;
double sea2_r = 0.0 * RGB_TRANS;
double sea2_g = 80.0 * RGB_TRANS;
double sea2_b = 142.0 * RGB_TRANS;

// -------- 船の色 --------
double ship_r = 150.0 * RGB_TRANS;
double ship_g = 150.0 * RGB_TRANS;
double ship_b = 150.0 * RGB_TRANS;

// -------- 海の上の光の色 --------
// 定義は海の上の光を描く関数の中で

// -------- 星の色 --------
double star_r = 255.0 * RGB_TRANS;
double star_g = 255.0 * RGB_TRANS;
double star_b = 150.0 * RGB_TRANS;


// -------- 空を描く --------
void draw_sky() {
    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        glColor3d(sky_r, sky_g, sky_b);
        glVertex2d(1, -0.5);
        glVertex2d(-1, -0.5);
        glColor3d(sky2_r, sky2_g, sky2_b);
        glVertex2d(-1, 1);
        glVertex2d(1, 1);
    glEnd();
}

// -------- 太陽のオーラを描く --------
void draw_aura() {
    // ---- 色の定義 ----
    double aura_r = sun_r*0.5;
    double aura_g = sun_g*0.5;
    double aura_b = sun_b*0.5;
    double trpar = 0.0; // 透明度

    // ---- 各種数値の定義 ----
    double cen_x = 0, cen_y = -0.1;
    double rad = 0.6;
    double theta = 0;
    double count = 1000;
    double dtheta = 2*M_PI / 1000;

    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        for(theta = 0; theta <= 2*M_PI; theta += dtheta) {
            glColor4f(aura_r, aura_g, aura_b, 1);
            glVertex2d(cen_x, cen_y);
            glColor4f(aura_r, aura_g, aura_b, 0);
            glVertex2d(cen_x + rad*cos(theta), cen_y + rad*sin(theta));
            glVertex2d(cen_x + rad*cos(theta + dtheta), cen_y + rad*sin(theta + dtheta));
        }
    glEnd();
}

// -------- 太陽を描く --------
void draw_sun() {
    // ---- 各種数値の定義 ----
    double cen_x = 0, cen_y = -0.1;
    double rad = 0.3;
    double theta = 0;
    double count = 1000;
    double dtheta = 2*M_PI / 1000;

    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        for(theta = 0; theta <= 2*M_PI; theta += dtheta) {
            glColor3d(sun_r, sun_g, sun_b);
            glVertex2d(cen_x, cen_y);
            glColor3d(sun2_r, sun2_g, sun2_b);
            glVertex2d(cen_x + rad*cos(theta), cen_y + rad*sin(theta));
            glVertex2d(cen_x + rad*cos(theta + dtheta), cen_y + rad*sin(theta + dtheta));
        }
    glEnd();
}

// -------- 海を描く --------
void draw_sea() {
    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        glColor3d(sea_r, sea_g, sea_b);
        glVertex2d(-1, 0);
        glVertex2d(1, 0);
        glColor3d(sea2_r, sea2_g, sea2_b);
        glVertex2d(1, -1);
        glVertex2d(-1, -1);
    glEnd();
}

// -------- 船を描く --------
void draw_ship(double x, double y) {
    // ---- 各種数値の定義 ----
    double cen_x = 0.5, cen_y = -0.5;
    double rad = 0.1;
    double theta = 0;
    double count = 1000;
    double dtheta = 2*M_PI / 1000;

    // ---- 指定された座標が外だったら ----
    if ((x < -1 || x > 1) || (y < -1 || y > 1)) {
        printf("x, y needs to fill the following conditions.\n");
        printf("-1 <= x, y <= 1");
        return;
    }

    // ---- 実際に描く ----
    // ---- 船の胴体部分 ----
    glBegin(GL_POLYGON);
        glColor4d(ship_r, ship_g, ship_b, 0.3);
        glVertex2d(x, y);
        glVertex2d(x-0.05, y+0.1);
        glVertex2d(x+0.15, y+0.1);
        glVertex2d(x+0.1, y);
    glEnd();

    // ---- 船の旗の部分 ----
    glBegin(GL_POLYGON);
        // 棒を描く
        glVertex2d(x+0.05-0.01, y+0.1);
        glVertex2d(x+0.05-0.01, y+0.1+0.15);
        glVertex2d(x+0.05+0.01, y+0.1+0.15);
        glVertex2d(x+0.05+0.01, y+0.1);
    glEnd();
    glBegin(GL_POLYGON);
        // 旗を描く（三角形）
        glVertex2d(x+0.05+0.01, y+0.1+0.15-0.01);
        glVertex2d(x+0.05+0.01+0.1, y+0.1+0.15-0.01-0.03);
        glVertex2d(x+0.05+0.01, y+0.1+0.15-0.01-0.03*2);
    glEnd();

        
}

// -------- 海の上の光を描く --------
void draw_ray() {
    // ---- 色の定義 ----
    double ray_r = (sun_r + sea_r) / 2.0;
    double ray_g = (sun_g + sea_g) / 2.0;
    double ray_b = (sun_b + sea_b) / 2.0;
    double ray2_r = (sun_r + sea2_r) / 2.0;
    double ray2_g = (sun_g + sea2_g) / 2.0;
    double ray2_b = (sun_b + sea2_b) / 2.0;

    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        glColor4d(ray_r, ray_g, ray_b, 0.25);
        glVertex2d(-0.3, 0);
        glVertex2d(0.3, 0);
        glColor4d(ray2_r, ray2_g, ray2_b, 0.25);
        glVertex2d(0.5, -1);
        glVertex2d(-0.5, -1);
    glEnd();
}

// -------- 星を描く --------
void draw_stars() {
    // ---- 星の直径を指定 ----
    glPointSize(2);

    // ---- 実際に描く ----
    glBegin(GL_POINTS);
        glColor3d(star_r, star_g, star_b);
        glVertex2d(-0.9, 0.8);
        glVertex2d(-0.8, 0.5);
        glVertex2d(-0.5, 0.9);
        glVertex2d(-0.4, 0.6);
        glVertex2d(-0.3, 0.9);
        glVertex2d(-0.3, 0.5);
        glVertex2d(0.2, 0.3);
        glVertex2d(0.5, 0.8);
        glVertex2d(0.9, 0.7);
    glEnd();
}



// -------- 描画関数 --------
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    // ---- 各パーツを描く ----
    draw_sky();
    draw_aura();
    draw_sun();
    draw_sea();
    draw_ray();
    draw_ship(0.3, -0.7);
    draw_ship(-0.4, -0.3);
    draw_stars();
    glFlush();
}

// -------- 初期化 --------
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


// -------- main関数 --------
int main(int argc, char *argv[]) {
    // ---- 初期化 ----
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);

    // ---- ウィンドウを作成 ----
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);

    // ---- α値をつかえるようにする ----
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    init();

    // ---- イベントが起きるまで待機 ----
    glutMainLoop();
    return 0;
}
