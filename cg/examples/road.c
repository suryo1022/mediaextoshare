#include <GL/glut.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>


void display(void){
  double i;
  glClear(GL_COLOR_BUFFER_BIT);
  /*背景*/
  glBegin(GL_QUADS);
  //下半分
  glColor3d(1.0, 1.0, 1.0);
  glVertex2d(-1.0, -1.0);
  glVertex2d(1.0, -1.0);
  glColor3d(0.6, 0.6, 1.0);
  glVertex2d(1.0, 0.33);
  glVertex2d(-1.0, 0.33);
  //上半分
  glColor3d(0.6, 0.6, 1.0);
  glVertex2d(-1.0, 0.33);
  glVertex2d(1.0, 0.33);
  glColor3d(0.33, 0.33, 1.0);
  glVertex2d(1.0, 1.0);
  glVertex2d(-1.0, 1.0);
  glEnd();
  //地面
  glBegin(GL_POLYGON);
  glColor3d(0.4, 0.8, 0.5);
  for(i=-1.0; i<=1.0; i+=0.1){
    glVertex2d(i, 0.165-(i-0.33)*(i-0.33)/5);
  }
  glVertex2d(1.0, -1.025);
  glEnd();
  //地面下半分
  glBegin(GL_QUADS);
  glColor3d(0.4, 0.8, 0.5);
  glVertex2d(-1.0, -0.2);
  glVertex2d(1.0, -0.2);
  glColor3d(0.3, 0.6, 0.3);
  glVertex2d(1.0, -1.0);
  glVertex2d(-1.0, -1.0);

  //屋根右
  glColor3d(0.5, 0.3, 0.3);
  glVertex2d(0.55, 0.4);
  glVertex2d(0.62, 0.63);
  glVertex2d(0.75, 0.65);
  glVertex2d(0.83, 0.34);

  //洋館右壁
  glColor3d(0.9, 0.9, 0.7);
  glVertex2d(0.66, 0);
  glVertex2d(0.66, 0.5);
  glVertex2d(0.8, 0.4);
  glVertex2d(0.8, 0.1);
  //洋館左壁
  glColor3d(1.0, 1.0, 0.8);
  glVertex2d(0.66, 0);
  glVertex2d(0.66, 0.5);
  glVertex2d(0.165, 0.4);
  glVertex2d(0.165, 0.1);

  glVertex2d(0.38, 0.63);
  glVertex2d(0.38, 0.7);
  glVertex2d(0.6, 0.3);
  glVertex2d(0.2, 0.3);

  //洋館右壁反射光
  glColor3d(0.9, 0.9, 0.7);
  glVertex2d(0.66, 0.2);
  glVertex2d(0.8, 0.25);
  glColor3d(0.77, 0.9, 0.7);
  glVertex2d(0.8, 0.1);
  glVertex2d(0.66, 0);
  //洋館左壁反射光
  glColor3d(1.0, 1.0, 0.8);
  glVertex2d(0.66, 0.2);
  glVertex2d(0.165, 0.25);
  glColor3d(0.9, 1.0, 0.8);
  glVertex2d(0.165, 0.1);
  glVertex2d(0.66, 0);
  //洋館右壁影
  glColor3d(0.3, 0.7, 0.4);
  glVertex2d(0.8, 0.1);
  glVertex2d(0.66, 0);
  glColor3d(0.4, 0.8, 0.5);
  glVertex2d(0.8, -0.04);
  glVertex2d(0.94, 0.075);

  //洋館屋根
  glColor3d(1.0, 0.7, 0.7);
  glVertex2d(0.13, 0.33);
  glVertex2d(0.25, 0.35);
  glVertex2d(0.35, 0.58);
  glVertex2d(0.22, 0.53);

  glVertex2d(0.55, 0.4);
  glVertex2d(0.62, 0.63);
  glVertex2d(0.75, 0.68);
  glVertex2d(0.64, 0.42);

  //洋館屋根右
  glColor3d(0.5, 0.3, 0.3);
  glVertex2d(0.37, 0.71);
  glVertex2d(0.38, 0.63);
  glVertex2d(0.55, 0.4);
  glVertex2d(0.62, 0.63);


  //洋館屋根淵
  glColor3d(0.7, 0.4, 0.4);
  glVertex2d(0.13, 0.33);
  glVertex2d(0.25, 0.35);
  glVertex2d(0.27, 0.32);
  glVertex2d(0.13, 0.3);
  
  glVertex2d(0.25, 0.35);
  glVertex2d(0.27, 0.32);
  glVertex2d(0.38, 0.63);
  glVertex2d(0.38, 0.7);
  
  glVertex2d(0.38, 0.63);
  glVertex2d(0.38, 0.7);
  glVertex2d(0.56, 0.4);
  glVertex2d(0.55, 0.36);

  glVertex2d(0.56, 0.4);
  glVertex2d(0.55, 0.36);
  glVertex2d(0.64, 0.39);
  glVertex2d(0.64, 0.43);

  glVertex2d(0.64, 0.39);
  glVertex2d(0.64, 0.43);
  glVertex2d(0.75, 0.7);
  glVertex2d(0.75, 0.64);

  glVertex2d(0.75, 0.7);
  glVertex2d(0.75, 0.64);
  glVertex2d(0.83, 0.37);
  glVertex2d(0.83, 0.33);

  //玄関
  glColor3d(0.5, 0.3, 0.3);
  glVertex2d(0.34, 0.05);
  glVertex2d(0.34, 0.23);
  glVertex2d(0.45, 0.22);
  glVertex2d(0.45, 0.03);

  glEnd();
  //路
  glBegin(GL_QUAD_STRIP);
  glColor3d(0.8, 0.8, 0.8);
  glVertex2d(0.35, 0.06);
  glVertex2d(0.45, 0.04);

  glVertex2d(0.1, 0.03);
  glVertex2d(0.4, 0.01);
  
  glVertex2d(0, 0.00);
  glVertex2d(0.3, -0.01);
  
  glVertex2d(-0.03, -0.05);
  glVertex2d(0.08, -0.03);
  
  glVertex2d(-0.05, -0.1);
  glVertex2d(0.045, -0.07);
  
  glVertex2d(-0.065, -0.15);
  glVertex2d(0.015, -0.10);

  glVertex2d(-0.075, -0.175);
  glVertex2d(0, -0.13);
  
  glVertex2d(-0.1, -0.2);
  glVertex2d(-0.015, -0.2);
  
  glVertex2d(-0.15, -0.25);
  glVertex2d(-0.03, -0.25);

  glVertex2d(-0.15, -0.25);
  glVertex2d(-0.06, -0.35);
  
  glVertex2d(-0.15, -0.25);
  glVertex2d(-0.09, -0.45);
  
  glVertex2d(-0.3, -0.28);
  glVertex2d(-0.2, -0.5);
  
  glVertex2d(-0.4, -0.4);
  glVertex2d(-0.3, -0.8);
  
  glVertex2d(-0.7, -0.7);
  glVertex2d(-0, -1);
  
  glVertex2d(-0.8, -0.9);
  glVertex2d(-0.7, -1);

  glEnd();
  glFlush();
}

void resize(int w, int h){
  /*ウィンドウ全体をビューポートにする*/
  glViewport(0, 0, w, h);
  /*変換行列の初期化*/
  glLoadIdentity();
  /*スクリーンの表示領域をビューポートの大きさに比例させる*/
  glOrtho(-w/ 200.0, w/200.0, -h/200.0, h/200.0, -1.0, 1.0);
}
void init(void){
  glClearColor(1.0, 1.0, 0.9, 1.0);
}

int main(int argc, char *argv[]){
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(320, 240);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  //glutReshapeFunc(resize);
  init();
  glutMainLoop();
  return 0;
}
