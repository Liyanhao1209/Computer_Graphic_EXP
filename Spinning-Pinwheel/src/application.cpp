/*
*  Function:
    1. void reverse()：风车旋转变向；
    2. void speedUp()：增大旋转速度；
    3. void speedDown()：降低旋转速度；
    4. void rotate()：旋转；
    5. void printCharater(const char* str)：按钮上显示文字；
    6. struct button：按钮部分，模拟button点击效果；
    7. void mouseFunc(GLint btn, GLint sta, int x, int y)：按钮和鼠标交互；
    8. void subFunc(GLint data)//void creatMenu()：右键菜单；
    9. void keyBoard(unsigned char key, int x, int y)：键盘交互；
    10. void drawPinwheel()：风车部分；
*/
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cmath>
#include <Windows.h>
#include <Gl/glut.h> 
#define MAX_CHAR 128
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

double angle = 0;
int direction = 1;
double speed = 0.3;
double Acceleration = 0.3;



void reverse()
{
    direction = -direction;
}

void speedUp()
{
    speed+=Acceleration;
}

void speedDown()
{
    
    if (speed >= Acceleration) {
        speed -= Acceleration;
    }
    else {
        speed = 0;
    }
    
}

void rotate()
{
    angle += direction*speed;
    if (angle > 360) angle = 0;
    glutPostRedisplay();
}

//button part

void printCharater(const char* str)
{
    glRasterPos2f(-0.06, 0.74);
    for (int i = 0; i < strlen(str); i++) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(str + i));
}
struct button
{
    char* str = new char[100];
    bool cleck;
    void rev() {

        glPushMatrix();

        if (cleck)
        {
            glScalef(0.98, 0.98, 1.0);
        }
        //button
        glColor3f(0, 0, 0);
        printCharater("Reverse");
        glColor3f(1, 1, 1);
        glBegin(GL_QUADS);
        glVertex3f(-0.1, 0.8, 0);
        glVertex3f(0.1, 0.8, 0);
        glVertex3f(0.1, 0.7, 0);
        glVertex3f(-0.1, 0.7, 0);
        glEnd();


        glPopMatrix();
    }


};
button* pBtn;
void mouseFunc(GLint btn, GLint sta, int x, int y)
{

    if (btn == GLUT_LEFT_BUTTON)
        switch (sta)
        {
        case GLUT_DOWN:
        {
            if (x >= 360 && x <= 440 && y >= 40 && y <= 80) {
                reverse();
                pBtn->cleck = true;
            }
            break;
        }
        case GLUT_UP:
        {
            pBtn->cleck = false;
        }
        }
    if (x >= 360 && x <= 440 && y >= 40 && y <= 80) {
        reverse();
    }
    glutPostRedisplay();
}


//menu part
void subFunc(GLint data)
{
    switch (data)
    {
    case 1:speedUp(); break;
    case 2:speedDown(); break;
    case 3:reverse(); break;
    }
}


void creatMenu()
{
    //创建菜单
    GLint sub = glutCreateMenu(subFunc);
    glutAddMenuEntry("Speed Up", 1);
    glutAddMenuEntry("Speed Down", 2);
    glutAddMenuEntry("Reverse", 3);
    //鼠标右键唤醒菜单
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//keyboard part
void keyBoard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':reverse(); break;//key "q" for reverse
    case 'w':speedUp(); break;//key "w" for speed up
    case 's':speedDown(); break;//key "s" for speed down
    case 27:exit(0);
    }
}


//drawing part
void drawPinwheel()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotatef(angle, 0, 0, 1);
    glScalef(1, 1, 1);
    //中心黄色部分
    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, 0.1 * sqrt(3) - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    //red wind
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1 * 27 / 52, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    //blue wind
    glRotatef(120, 0, 0, 1);
    glColor3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1 * 27 / 52, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    //green wind
    glRotatef(120, 0, 0, 1);
    glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(-0.1f, -0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);

    glVertex3d(0.0f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(-0.2f, -0.2 * 147 / 113 - 0.2 * sqrt(3) / 6, 0);
    glVertex3d(0.1 * 27 / 52, -0.2 * 147 / 113 / 146 * 230 - 0.2 * sqrt(3) / 6, 0);
    glEnd();

    glPopMatrix();

    //bar
    glScalef(1, 1, 1);
    glColor3f(1, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(0.05, 0, 0.1);
    glVertex3f(-0.05, 0, 0.1);
    glVertex3f(-0.05, -0.7, 0.1);
    glVertex3f(0.05, -0.7, 0.1);
    glEnd();

    glPopMatrix();

    //button 
    pBtn->rev();

    glPopMatrix();



    glFlush();
    glutSwapBuffers();
}


//initialize
void Init()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.77, 0.80, 0.84, 0.19);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20, 1, 1, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    glShadeModel(GL_SMOOTH);
    pBtn = new button;
    pBtn->cleck = false;
}

int main(int argc, char* argv[]) //
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Spinning Pinwheel");
    glEnable(GL_DEPTH_TEST | GL_LINE_SMOOTH | GL_POLYGON_SMOOTH | GL_POLYGON_STIPPLE);

    Init();
    creatMenu();
    glutDisplayFunc(&drawPinwheel);
    glutIdleFunc(&rotate);
    glutKeyboardUpFunc(&keyBoard);
    glutMouseFunc(&mouseFunc);
    glutMainLoop();

    return 0;
}
