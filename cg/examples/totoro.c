#include <GL/glut.h>

#ifdef _MSC_VER  // Windows�Ȃ��
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#define PART 100 // ������


/* �~��`���֐� */
void draw_circle(float r, float r2, float X, float Y)
{
  int i, n = 100;
  float x, y;
  double rate;

  glBegin(GL_POLYGON);
  for (i = 0; i < n; i++) {
    rate = (double)i / n;  //���W���v�Z
    x = r * cos(2.0 * M_PI * rate) + X;
    y = r2 * sin(2.0 * M_PI * rate) + Y;
    glVertex3f(x, y, 0.0); // ���_���W���w��
  }
  glEnd();
}

/* �����̖͗l */
void draw_moyou(float x, float y)
{
  glBegin(GL_POLYGON);
  glVertex2d(0 + x, -0.04 + y);
  glVertex2d(0.05 + x, -0.1 + y);
  glVertex2d(0.0 + x, -0.08 + y);
  glVertex2d(-0.05+ x, -0.1 + y);
  glEnd();
}

/* ���� */
void draw_onaka(void)
{
  draw_moyou(0,0.23);
  draw_moyou(0.2,0.19); 
  draw_moyou(-0.2,0.19);
  draw_moyou(0.1,0.1);
  draw_moyou(-0.1,0.1);
  draw_moyou(0.3,0.05);
  draw_moyou(-0.3,0.05);

  glBegin(GL_TRIANGLES);
  glColor3d(1.0, 1.0, 0.9);
  glVertex2d(0.49, -0.4);
  glVertex2d(-0.49, -0.4);
  glColor3d(1.0, 1.0, 1.0);
  glVertex2d(0.0, -0.85);
  glEnd();
  
}

/* �� */
void draw_eyes(void)
{  
  glColor3d(1.0, 1.0, 1.0);
  draw_circle(0.05, 0.05, 0.25, 0.42);
  draw_circle(0.05, 0.05, -0.25, 0.42);

  glColor3d(0.0, 0.0, 0.0);
  draw_circle(0.02, 0.02, 0.25, 0.42);
  draw_circle(0.02, 0.02, -0.25, 0.42);
}

/* �@ */
void draw_nose(void)
{
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  glVertex2d(0, 0.4);
  glVertex2d(0.05, 0.44);
  glVertex2d(-0.05, 0.44);
  glEnd();
}

/* �� */
void draw_ears(void)
{
  glColor3d(0.75, 0.75, 0.75); /* �̂̐F */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.4, 0.9);
  glVertex2d(-0.43, 0.55);
  glVertex2d(-0.3, 0.65);
  glEnd();

  glBegin(GL_TRIANGLES);
  glVertex2d(0.4, 0.9);
  glVertex2d(0.43, 0.55);
  glVertex2d(0.3, 0.65);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2d(-0.4, 0.6);
  glVertex2d(-0.35, 0.5);
  glVertex2d(-0.29, 0.55);
  glVertex2d(-0.34, 0.65);
  glEnd();

  glBegin(GL_QUADS);
  glVertex2d(0.4, 0.6);
  glVertex2d(0.35, 0.5);
  glVertex2d(0.29, 0.55);
  glVertex2d(0.34, 0.65);
  glEnd();
}  

/* �� */
void draw_feet(void)
{  
  glColor3d(0.0, 0.0, 0.0); /* �� */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.5, -0.85);  /* �� */
  glVertex2d(-0.6, -0.85);
  glVertex2d(-0.5, -0.82);

  glVertex2d(0.5, -0.85);  /* �E */
  glVertex2d(0.6, -0.85);
  glVertex2d(0.5, -0.82);
  glEnd();

  glColor3d(0.75, 0.75, 0.75); /* �̂̐F ��*/
  glBegin(GL_TRIANGLES);
  glVertex2d(0, -0.85);  /* �� */
  glVertex2d(-0.5, -0.85);
  glVertex2d(-0.63, -0.3);

  glVertex2d(0, -0.85);  /* �E */
  glVertex2d(0.5, -0.85);
  glVertex2d(0.63, -0.3);
  glEnd();  

}

/* �Ђ� */
void draw_hige(void)
{
  glColor3d(0.0, 0.0, 0.0);  /* �� */
  glBegin(GL_LINES);
  glVertex2d(-0.8, 0.4);  /* �� */
  glVertex2d(-0.4, 0.38);
  glVertex2d(-0.85, 0.35);
  glVertex2d(-0.45, 0.34);
  glVertex2d(-0.8, 0.3);
  glVertex2d(-0.4, 0.3);

  glVertex2d(0.8, 0.4);  /* �E */
  glVertex2d(0.4, 0.38);
  glVertex2d(0.85, 0.35);
  glVertex2d(0.45, 0.34);
  glVertex2d(0.8, 0.3);
  glVertex2d(0.4, 0.3);
  glEnd();
}

/* �� */
void draw_mouse(void)
{
  glColor3d(1.0, 1.0, 1.0);  /* �� */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.3, 0.34);
  glVertex2d(0.3, 0.34);
  glVertex2d(0, 0.28);
  glEnd();

  glColor3d(0.0, 0.0, 0.0);  /* �� */
  glBegin(GL_LINES);  /* �c���C�� */
  glVertex2d(0, 0.34);
  glVertex2d(0, 0.28);
  glVertex2d(-0.1, 0.34);
  glVertex2d(-0.1, 0.3);
  glVertex2d(0.1, 0.34);
  glVertex2d(0.1, 0.3);
  glVertex2d(0.2, 0.34);
  glVertex2d(0.2, 0.32);
  glVertex2d(-0.2, 0.34);
  glVertex2d(-0.2, 0.32);
  glEnd();  
}

/* ��̃p�[�c��`�� */
void draw_fice(void)
{
  draw_eyes();
  draw_nose();
  draw_ears();
  draw_hige();
  draw_mouse();
}

/* �� */
void draw_hands(void)
{ 
  glColor3d(0.0, 0.0, 0.0);  /* �� */
  glBegin(GL_TRIANGLES);
  glVertex2d(-0.59, -0.6);
  glVertex2d(-0.61, -0.4);
  glVertex2d(-0.57, -0.4);
  glEnd();

  glBegin(GL_TRIANGLES);
  glVertex2d(0.59, -0.6);
  glVertex2d(0.61, -0.4);
  glVertex2d(0.57, -0.4);
  glEnd();

  glColor3d(0.75, 0.75, 0.75);  /* �̂̐F */
  draw_circle(0.2, 0.4, -0.5, -0.15);
  draw_circle(0.2, 0.4, 0.5, -0.15);
  //  glColor3d(0.0, 0.0, 0.0);
  glEnd();
}

void display(void)
{  
  glClear(GL_COLOR_BUFFER_BIT);  // �E�B���h�E��h��Ԃ�

  glBegin(GL_QUADS);  // �w�i�̃O���f�[�V����
  glColor3d(0.67, 1.0, 0.18);
  glVertex2d(-1.0, -1.0);
  glVertex2d(1.0, -1.0);
  glColor3d(0.68, 0.93, 0.93);
  glVertex2d(1.0, 1.0); 
  glVertex2d(-1.0, 1.0);
  glEnd();

  draw_feet();
  draw_hands();
  glColor3d(0.75, 0.75, 0.75); // �̂̐F 
  draw_circle(0.65, 0.75, 0, -0.1);
  glColor3d(1.0, 1.0, 0.9); // �����̐F 
  draw_circle(0.55, 0.55, 0, -0.3);
  glColor3d(0.75, 0.75, 0.75); // �̂̐F
  draw_onaka();  // �����̖͗l��`�� 
  draw_fice();  // ��̃p�[�c��`�� 
  glFlush();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);  // ���̏�����
  glutInitDisplayMode(GLUT_RGBA);  // �F�̎w������߂� 
  glutCreateWindow(argv[0]);  // �E�B���h�E���J��
  glutDisplayFunc(display);  // �G��`���֐������߂�
  glutMainLoop();  // �C�x���g�̑҂��󂯏��
  return 0;
}
