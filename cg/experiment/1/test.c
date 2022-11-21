#include <GL/glut.h>
#include <math.h>


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

// -------- 海の色 --------
double sea_r = 116.0 * RGB_TRANS;
double sea_g = 80.0 * RGB_TRANS;
double sea_b = 142.0 * RGB_TRANS;
double sea2_r = 0.0 * RGB_TRANS;
double sea2_g = 80.0 * RGB_TRANS;
double sea2_b = 142.0 * RGB_TRANS;

// -------- 船の色 --------
double ship_r = 75.0 * RGB_TRANS;
double ship_g = 71.0 * RGB_TRANS;
double ship_b = 72.0 * RGB_TRANS;

// -------- 海の上の光の色 --------
// 定義は海の上の光を描く関数の中で


// -------- 空を描く --------
void draw_sky() {
    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        glColor3d(sky_r, sky_g, sky_b);
        glVertex2d(1, -0.2);
        glVertex2d(-1, -0.2);
        glColor3d(sky2_r, sky2_g, sky2_b);
        glVertex2d(-1, 1);
        glVertex2d(1, 1);
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
void draw_ship() {
    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        glColor3d(ship_r, ship_g, ship_b);
        glVertex2d(-0.05, -0.6);
        glVertex2d(-0.1, -0.5);
        glVertex2d(0.1, -0.5);
        glVertex2d(0.05, -0.6);
    glEnd();
}

// -------- 海の上の光を描く --------
void draw_ray() {
    // ---- 色の定義 ----
    double ray_r = (sun_r + sea_r * 10) / 11.0;
    double ray_g = (sun_g + sea_g * 10) / 11.0;
    double ray_b = (sun_b + sea_b * 10) / 11.0;
    double ray2_r = (sun_r + sea2_r * 10) / 11.0;
    double ray2_g = (sun_g + sea2_g * 10) / 11.0;
    double ray2_b = (sun_b + sea2_b * 10) / 11.0;

    // ---- 実際に描く ----
    glBegin(GL_POLYGON);
        glColor3d(ray_r, ray_g, ray_b);
        glVertex2d(-0.3, 0);
        glVertex2d(0.3, 0);
        glColor3d(ray2_r, ray2_g, ray2_b);
        glVertex2d(0.5, -1);
        glVertex2d(-0.5, -1);
    glEnd();
}



// -------- 描画関数 --------
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    // ---- 各パーツを描く ----
    draw_sky();
    draw_sun();
    draw_sea();
    //draw_ship();
    draw_ray();
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

    init();

    // ---- イベントが起きるまで待機 ----
    glutMainLoop();
    return 0;
}
