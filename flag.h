#ifndef FLAG_H 
#define FLAG_H
#include <math.h>
#include <GL/glut.h>

GLfloat xa = 0, ya = 0;
int yflag = 1, xflag = 1, aniflag = 1;

//animation function increments and decrements the x and y coordinates of the flag points 
void Animate() {
	if (aniflag == 1) {
		if (ya > -2.5 && yflag == 1)
			ya = ya - 0.05;
		if (ya <= -2.5 && yflag == 1)
			yflag = 0;
		if (ya < 2.5 && yflag == 0)
			ya = ya + 0.05;
		if (ya >= 2.5 && yflag == 0)
			yflag = 1;

		if (xa > -1.5 && xflag == 1)
			xa = xa - 0.05;
		if (xa <= -1.5 && xflag == 1)
			xflag = 0;
		if (xa < 1.5 && xflag == 0)
			xa = xa + 0.05;
		if (xa >= 1.5 && xflag == 0)
			xflag = 1;
	}
	glutPostRedisplay();
}

void drawFlagMap() {
	GLfloat x[4], y1[4], y2[4], y3[4];
	GLdouble xt[200], y1t[200], y2t[200], y3t[200], t;
	int i, c;
	x[0] = -2; x[1] = -0.75 + (xa); x[2] = 1 + (xa / 2); x[3] = 2 + (xa / 10);
	y1[0] = 1; y1[1] = 1 + ya; y1[2] = 1 - ya; y1[3] = 1 + (ya / 2);
	y2[0] = 0; y2[1] = 0 + ya; y2[2] = 0 - ya; y2[3] = 0 + (ya / 2);

	for (i = 0, t = 0, c = 0; t < 1; i++, t = t + 0.02) {
		//bresenham curve algorithm formuals for 3rd degree
		xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
		y1t[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
		y2t[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];
		c++;
	}
	glColor3f(1, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < c; i++) {
		glVertex3d(xt[i], y1t[i],0);
		glVertex3d(xt[i], y2t[i],0);
	}
	glEnd();
}
#endif
