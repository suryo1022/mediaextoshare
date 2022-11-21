#include <GL/glut.h>
#include <math.h>


// ---------------- 色の定義 -----------------
#define RGB_TRANS 1.0/255.0

// -------- 太陽の色 --------
// 太陽の内側
double sun_r = 255.0 * RGB_TRANS;
double sun_g = 0.0 * RGB_TRANS;
double sun_b = 0.0 * RGB_TRANS;
double sun2_r = 200.0 * RGB_TRANS;
double sun2_g = 0.0 * RGB_TRANS;
double sun2_b = 0.0 * RGB_TRANS;


// -------- 空を描く --------
void draw_sky() {
    glBegin(GL_POLYGON);
    glColor3d();
    glEnd();
}

// -------- 太陽を描く --------
void draw_sun() {
    double cen_x = 0, cen_y = 0.5;
    double rad = 0.5;
    double theta = 0;
    double count = 1000;
    double dtheta = 2*M_PI / 1000;

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

// -------- 描画関数 --------
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT);

    draw_sun();
    glFlush();
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
