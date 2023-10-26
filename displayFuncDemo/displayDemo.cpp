#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cmath>
#include <Windows.h>
#include <Gl/glut.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;

GLfloat lightPos[] = { 25.0, 25.0, 25.0, 1.0 };
GLfloat lookat[] = { 0.0, -10.0, 10.0 };
GLfloat up[] = { 0.0, 0.0, 1.0 };
GLdouble fovy = 60.0;
GLdouble nearPlane = 1.0;
GLdouble farPlane = 1000.0;

float v = 0; //velocity
float mx = 0;
float my = 0;
float turnAngle = 0;

bool first_perspective = false; // user perspective
float translatex = 0;
float translatey = 0;
float cameraDistance = 40.0f;
float cameraAnglex = 0;
float cameraAngley = 120;

const double PI = 3.14159265359;
const float rad = PI / 180.0f;

float angle2Rad(float angle) {
	return rad * angle;
}

float R = 0, G = 0.5, B = 0.5;


void init(void) {
    GLfloat  white[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
}

void draw_track() {
	float height = 0.001f;
	//绘制地面
	glNormal3f(0, 0, 1);
	glColor3f(0, 0.6, 0.2);
	glBegin(GL_QUADS);
	glVertex3f(-20.0f, -20.0f, 0);
	glVertex3f(20.0f, -20.0f, 0);
	glVertex3f(20.0f, 20.0f, 0);
	glVertex3f(-20.0f, 20.0f, 0);
	glEnd();

	//跑道的直线部分：
	glBegin(GL_QUADS);
	glColor3f(1, 0.6, 0.2);
	glVertex3f(-10.0f, -8.0f, height);
	glVertex3f(-5.0f, -8.0f, height);
	glVertex3f(-5.0f, 8.0f, height);
	glVertex3f(-10.0f, 8.0f, height);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 0.6, 0.2);
	glVertex3f(10.0f, -8.0f, height);
	glVertex3f(10.0f, 8.0f, height);
	glVertex3f(5.0f, 8.0f, height);
	glVertex3f(5.0f, -8.0f, height);
	glEnd();

	//跑道的圆环部分：
	float i;
	for (i = 0; i <= PI - 0.01; i += 0.01) {
		glBegin(GL_QUADS);
		glColor3f(1, 0.6, 0.2);
		glVertex3f(-5.0 * cos(i), 8 + 5.0 * sin(i), height);
		glVertex3f(-5.0 * cos(i + 0.01), 8 + 5.0 * sin(i + 0.01), height);
		glVertex3f(-10.0 * cos(i + 0.01), 8 + 10.0 * sin(i + 0.01), height);
		glVertex3f(-10.0 * cos(i), 8 + 10.0 * sin(i), height);
		glEnd();
	}


	for (i = 0; i <= PI - 0.01; i += 0.01) {
		glBegin(GL_QUADS);
		glColor3f(1, 0.6, 0.2);
		glVertex3f(-5.0 * cos(i), -8 - 5.0 * sin(i), height);
		glVertex3f(-10.0 * cos(i), -8 - 10.0 * sin(i), height);
		glVertex3f(-10.0 * cos(i + 0.01), -8 - 10.0 * sin(i + 0.01), height);
		glVertex3f(-5.0 * cos(i + 0.01), -8 - 5.0 * sin(i + 0.01), height);
		glEnd();
	}

}

void draw_car() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//车底面
	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(-1.0f, 2.0f, 0.5f);
	glVertex3f(1.0f, 2.0f, 0.5f);
	glVertex3f(1.0f, -2.0f, 0.5f);
	glVertex3f(-1.0f, -2.0f, 0.5f);
	glEnd();
	//车头
	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(-1.0f, 2.0f, 0.5f);
	glVertex3f(-1.0f, 2.0f, 1.5f);
	glVertex3f(1.0f, 2.0f, 1.5f);
	glVertex3f(1.0f, 2.0f, 0.5f);
	glEnd();
	//车尾
	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(-1.0f, -2.0f, 1.5f);
	glVertex3f(-1.0f, -2.0f, 0.5f);
	glVertex3f(1.0f, -2.0f, 0.5f);
	glVertex3f(1.0f, -2.0f, 1.5f);
	glEnd();
	//左侧面
	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(-1.0f, 2.0f, 1.5f);
	glVertex3f(-1.0f, 2.0f, 0.5f);
	glVertex3f(-1.0f, -2.0f, 0.5f);
	glVertex3f(-1.0f, -2.0f, 1.5f);
	glEnd();
	//右侧面
	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(1.0f, 2.0f, 0.5f);
	glVertex3f(1.0f, 2.0f, 1.5f);
	glVertex3f(1.0f, -2.0f, 1.5f);
	glVertex3f(1.0f, -2.0f, 0.5f);
	glEnd();
	//车顶(从头向尾绘制，共有五个多边形拼接成)
	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(1.0f, 2.0f, 1.5f);
	glVertex3f(-1.0f, 2.0f, 1.5f);
	glVertex3f(-1.0f, 1.0f, 1.5f);
	glVertex3f(1.0f, 1.0f, 1.5f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0f, 1.0f, 1.5f);
	glVertex3f(-1.0f, 0.5f, 2.5f);
	glVertex3f(1.0f, 0.5f, 2.5f);
	glVertex3f(1.0f, 1.0f, 1.5f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(1.0f, 0.5f, 2.5f);
	glVertex3f(-1.0f, 0.5f, 2.5f);
	glVertex3f(-1.0f, -1.0f, 2.5f);
	glVertex3f(1.0f, -1.0f, 2.5f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(1.0f, -1.0f, 2.5f);
	glVertex3f(-1.0f, -1.0f, 2.5f);
	glVertex3f(-1.0f, -1.2f, 1.5f);
	glVertex3f(1.0f, -1.2f, 1.5f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(R, G, B);
	glVertex3f(1.0f, -1.2f, 1.5f);
	glVertex3f(-1.0f, -1.2f, 1.5f);
	glVertex3f(-1.0f, -2.0f, 1.5f);
	glVertex3f(1.0f, -2.0f, 1.5f);
	glEnd();
	//左车窗
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0f, 0.5f, 2.5f);
	glVertex3f(-1.0f, 1.0f, 1.5f);
	glVertex3f(-1.0f, -1.2f, 1.5f);
	glVertex3f(-1.0f, -1.2f, 2.5f);
	glEnd();
	//右车窗
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(1.0f, 1.0f, 1.5f);
	glVertex3f(1.0f, 0.5f, 2.5f);
	glVertex3f(1.0f, -1.2f, 2.5f);
	glVertex3f(1.0f, -1.2f, 1.5f);
	glEnd();



	//车轮	
	glColor3f(0, 0, 0);

	glTranslated(0.6f, 1.3f, 0.25);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.1, 0.25, 5, 100);

	glTranslated(-0.6f, 1.3f, 0.25);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.1, 0.25, 5, 100);

	glRotatef(-90, 0, 1, 0);
	glTranslated(0, -2.6f, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.1, 0.25, 5, 100);

	glRotatef(-90, 0, 1, 0);
	glTranslated(1.2, 0, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.1, 0.25, 5, 100);

	glPopMatrix();

}

void drawObjects(GLboolean shadowRender) {
    draw_track();
    glPushMatrix();
    glTranslatef(-my - 7.5, -mx, 0);
    glRotatef(turnAngle, 0, 0, 1);
    draw_car();
    glPushMatrix();
    glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
    glColor3f(1, 1, 1);
    glutWireSphere(0.5, 6, 6);
    glPopMatrix();
}

void display(void) {
	GLfloat a = angle2Rad(cameraAnglex - 90);
	GLfloat b = angle2Rad(270 - cameraAngley);
	GLfloat x = cameraDistance * translatex * cos(a) + cameraDistance * translatey * sin(b) * sin(a) + cameraDistance * cos(angle2Rad(cameraAnglex)) * sin(angle2Rad(cameraAngley));
	GLfloat y = cameraDistance * translatey * cos(b) + cameraDistance * cos(angle2Rad(cameraAngley));
	GLfloat z = cameraDistance * translatex * sin(a) - cameraDistance * translatey * cos(a) * sin(b) + cameraDistance * sin(angle2Rad(cameraAnglex)) * sin(angle2Rad(cameraAngley));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(20,30,10,lookat[0], lookat[1], lookat[2],
		up[0], up[1], up[2]);
	drawObjects(GL_FALSE);
	glPopMatrix();
	glutSwapBuffers();

}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)width / height, nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutIdleFunc(glutPostRedisplay);// do nothing
    glutMainLoop();
    return 0;
}