#ifndef START_H 
#define START_H
#include <GL/glut.h>
#include <Windows.h>
#include <iostream>

void mainGameSpace();
int ddd = 0;
int cnt = 0;

void newinit() {
	ddd = 1;
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,1,0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5,5,-5,5,2,20);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
} 

GLfloat T = 0, sx=0, sy=0;
int c1 = 0, d = 0;

const int font = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font1 = (int)GLUT_BITMAP_HELVETICA_18;

void spin(int val) {
	T += 1.2;
	if (T >= 360) T = 0;
	glutPostRedisplay();
}

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	if (ddd == 1)
		glRasterPos3f(x, y, 5);
	else
		glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void bufferAnimation() {
	glPushMatrix();
	glLoadIdentity();
	glPointSize(17);
	glTranslatef(0, -0.4, 0);
	glRotatef(T, 0, 0, 1);
	glTranslatef(0, 0.4, 0);
	glColor3f(0.4,0.5,0.6);
	glBegin(GL_POINTS);
	glVertex2f(0.08, -0.4);
	glVertex2f(-0.08, -0.4);
	glVertex2f(0, -0.32);
	glVertex2f(0, -0.48);
	glEnd();
	glutTimerFunc(1, spin, 0);
	glPopMatrix();
}

void draw(int x1, int y1, int x2, int y2) {
	glColor3f(0, 0, 0);
	glRecti(x1, y1, x2, y2);
}

void drawPush() {
	draw(-95, -60, -90, 60);
	draw(-25, -60, -20, 60);
	draw(50, -60, 55, 60);  
	draw(-135, -60, -90, -10);
	draw(-135, 10, -110, 40);
	draw(-70, -30, -45, 60);
	draw(-20, -40, 25, -15);
	draw(5, 15, 50, 45);
	draw(85, -60, 125, -25);
	draw(85, 15, 125, 60);
}
void drawPop() {
	draw(-56, -60, -52, 60);
	draw(52, -60, 56, 60);
	draw(-120, -60, -52, -10);
	draw(-120, 10, -73, 40);
	draw(-30, -35, 30, 35);
	draw(95, -60, 160, -10);
	draw(95, 10, 139, 40);
}

void drawGO() {
	draw(-1, -60, 1, 60);
	draw(-128, 16, 0, 36);
	draw(-128,-4,-66,16);
	draw(-44,-60,-22,-10);
	draw(42,-40,112,40);

}

void displayRules() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	renderBitmapString(-20, 110, (void*)font, "pushpopGO");
	renderBitmapString(-80, 80, (void*)font1, "It is a simple simulation of STACK data structure using Open GL graphics");
	renderBitmapString(-60, 40, (void*)font, "*****___rules to use pushpopGO___*****");
	renderBitmapString(-50, 10, (void*)font, "* Press p to Push");
	renderBitmapString(-50, -10, (void*)font, "* Press o to pOp");
	renderBitmapString(-50, -30, (void*)font, "* Press g to Go");
	renderBitmapString(-50, -50, (void*)font, "* Press R to RESET");
	renderBitmapString(-50, -70, (void*)font, "* Press 1 to turn on/off moon light");
	renderBitmapString(-50, -90, (void*)font, "* Press 2 to turn on/off car headlight");
	renderBitmapString(-25, -135, (void*)font, "Click here to Start");

	glBegin(GL_LINE_LOOP);
	glVertex2i(-50, -110);
	glVertex2i(50, -110);
	glVertex2i(50, -150);
	glVertex2i(-50, -150);
	glEnd(); 
	glutPostRedisplay();
}

void scaleUp(int val) {
	sx+=0.125;   
	sy+=0.125;
	c1++;
	if (c1 == 23 && d==0) {
		sx = 1;
		sy = 1; 
		c1 = 0;
		d = 1;
	}
	if (c1 == 23 && d==1) {
		sx = 1;
		sy = 1;
		c1 = 0;
		d = 2;
	}
	if (c1 == 28 && d == 2) {
		d = 3;
	}

	glutPostRedisplay();
}

void startGame(int button,int state,int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && -50 < x <50 && -110> y > -150) {
		newinit();
		glutDisplayFunc(mainGameSpace);
	}
}
void ppgAnim() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-768,768,-1366,1366);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(sx, sy, 1);
	if (d == 0) drawPush();
	else if (d == 1) drawPop();
	else if (d == 2) drawGO();
	else if (d == 3) displayRules();
	glutMouseFunc(startGame);
	if (d != 3) {
		glColor4f(1, 1, 1, 0.5);
		glRecti(-160, -60, 160, 60);
		glutTimerFunc(50, scaleUp, 0);
	}
	glutSwapBuffers();
}

void myTimer(int val) {
	glutDisplayFunc(ppgAnim);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	renderBitmapString(-0.1, 0, (void*)font, "pushpopGO");
	bufferAnimation();
	glutTimerFunc(3000, myTimer, 0);
	glutSwapBuffers();
}
#endif