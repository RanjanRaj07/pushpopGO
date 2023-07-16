#include "stack.h"
#include "start.h"
#include <Windows.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include "flag.h"

using namespace std;

int start = 0;

int ptY = 0;

int go = 0, pu = 0, po = 0;

int pr = 0,pl=0,ps=0;

GLfloat movX = 0;

Stack s;

double eyeX = 0.0, eyeY = 1, eyeZ = 15, refX = 0, refY = 0, refZ = 0;

GLfloat tx, ty ,tz,pty=0,ptz=0;

GLboolean redFlag = true, switchOne = true, switchTwo = false, amb1 = true, diff1 = true, spec1 = true, amb2 = true, diff2 = true, spec2 = true, amb3 = true, diff3 = true, spec3 = true;

GLfloat fy = 5.6;

void myInit() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST); 
}

//timer function to increment the translation coordinates of sceen
void move(int x) {
    movX += 0.4;

    if (pr < 5 && fy>-17) {
        fy -= 0.1;
    }
    else if (pr == 5 && fy < 5.6) {
        fy += 0.2;
    }
    if (tx >= 13.5 && pu>0) {
        ty = -10 + 2.5 * s.stack[s.top];
        tz = 2;
        start = 2;
    }
    else {
        tx += 0.4;
    }
    if (movX >= 12 && go==1){
        //check at pothole
        if (s.isStackFill()) {
            start = 1;
        }
        else{
           start = 3;
           movX = 0;
        }

    }
    if (movX >= 44)
        start = 2;
    glutPostRedisplay();
}

//seprate timer function for pop operation
void PopMov(int i) {
    if (pty < 15) {
        pty += 0.8;
    }
    else if(ptz>-20) {
        ptz -= 0.6;
    }
    glutPostRedisplay();
}

//function to draw the boundary of the sceen(dark background walls)
void drawBoundray() {
    GLfloat ambi[] = { 0.037, 0.012, 0.1,1 }, diff[] = { 0.001, 0.003, 0.001,1 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glColor4f(0.037, 0.012, 0.1,1);
    glPushMatrix();
    glTranslatef(30, 0, 0);
    glScalef(0.2, 60, 60);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 0, 0);
    glScalef(0.2, 60, 60);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 30, 0);
    glScalef(60, 0.2, 60);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -4.6);
    glScalef(60, 69, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
}

//function to draw moon
void drawMoon() {
    GLfloat pos[] = { -10,10,0 ,1 };
    GLfloat col[] = { 1,1,1,1 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(19, 30.5, -2.5);
    glutSolidSphere(1.4, 20, 20);
    glPopMatrix();
    glPopAttrib();
}

//function to draw Grassland 
void drawGrass() {
    GLfloat ambi[] = { 0.082,1.969,0.082 }, diff[] = { 0,1,0,1 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glPushMatrix();
    glTranslatef(-17, -17, 0);
    glScalef(27, 8, 50);
    glutSolidCube(1);
    glPopMatrix(); 

    glPushMatrix();
    glTranslatef(16.5, -17, 0);
    glScalef(29, 8, 50);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(11, 1, 11);
    glTranslatef(0, -13.72, -0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glScalef(11, 1, 11);
    glTranslatef(0, -23.72, 1);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
}

//function to draw white strips on road 
void drawStrips(GLfloat x) {
    GLfloat ambi[] = {1,1,1,1}, diff[] = { 0.89, 0.89, 0.89,1 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(x, -12.89, 3.3);
    glScalef(4, 0.2, 0.6);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
}

//functoion to draw boundary for road 
void drawBound(GLfloat x) {
    GLfloat ambi[] = { 0.5,0.4,0 }, diff[] = {0.19,0.0545,0};
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glPushMatrix();
    glTranslatef(-17, -13, x);
    glScalef(27, 1, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5, -13, x);
    glScalef(29, 1, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
}

//function to draw road 
void drawRoad() {
    GLfloat ambi[] = { 0.502, 0.502, 0.502 }, diff[] = { 0.502, 0.502, 0.502 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi);
    glPushMatrix();
    glTranslatef(-17, -13, 3);
    glScalef(27, 0.2, 5.1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5, -13, 3);
    glScalef(29, 0.2, 5.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();

    drawStrips(-28);
    drawStrips(-22.5);
    drawStrips(-16.5);
    drawStrips(-10.5);  
    drawStrips(9.5);
    drawStrips(16.5);

    drawBound(0.2);
    drawBound(5.6);
}

//function to draw finish black squares
void drawSquares(GLfloat x,GLfloat z) {
    GLfloat ambi[] = { 1,1,1,1 }, ambi1[] = { 0,0,0,1 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi1);
    glColor3f(0, 0, 0);
    glPushMatrix();
    glTranslatef(20.15+x, -12.9, 1+z);
    glScalef(1.7, 0.3, 1.3);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
}

//function to draw finish line
void drawFinish() {
    glPushMatrix();
    GLfloat ambi[] = { 1,1,1,1 }, ambi1[] = { 0,0,0,1 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi);
    glTranslatef(24, -12.9, 3);
    glScalef(9, 0.2, 5.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
    drawSquares(0,0);
    drawSquares(3.8, 0);
    drawSquares(7.6, 0);
    drawSquares(1.9, 1.25);
    drawSquares(5.6, 1.25);
    drawSquares(0, 2.5);
    drawSquares(3.8, 2.5);
    drawSquares(7.6, 2.5);
    drawSquares(1.9, 3.75);
    drawSquares(5.6, 3.75);
}

//function to draw tyre for the car 
void drawTyre(GLfloat x,GLfloat z) {
    glPushMatrix();
    GLfloat ambi[] = { 0,0,0,1 }, ambi1[] = {0.434,0.434,0.434,1}, diff[] = {0.05,0.05,0.05, 1}, spec[] = {0.1,0.1,0.1, 1};

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glTranslatef(-14-x, -10.5, 1.5+z);
    glutSolidTorus(0.30, 1.5, 25, 25);
    glPopAttrib();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, diff);
    GLUquadricObj* tyre1;
    tyre1 = gluNewQuadric();
    gluQuadricDrawStyle(tyre1, GLU_FILL);
    gluDisk(tyre1, 0, 1.5, 25, 25);
    glPopAttrib();
    glPopMatrix(); 
}

//function to draw the wheel assembly for the car
void drawWheels() {
    drawTyre(0,0);
    drawTyre(0,3);
    drawTyre(8, 0);
    drawTyre(8, 3);
    
}

//function to draw the sides for the car body  
void drawSideslang(GLfloat x,GLfloat z) {
    GLfloat mat_ambient[] = { 0, 0, 1,  1.0 };
    GLfloat mat_diffuse[] = { 0,0,1,1.0 };
    GLfloat mat_specular[] = { 0, 0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 30 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glPushMatrix();
    glTranslatef(-18 + x, -8, 3 + z);
    glScalef(0.1, 5, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
}

//function to draw head lights for the car  
void drawHeadlight(GLfloat x, GLfloat z,int y) {
    GLfloat ambi[] = { 1,y,0,1 }, diff[] = {0.8,y,0,1};
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, diff);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi);
    glPushMatrix();
    glTranslatef(-11.5+x, -9.1, 3+z);
    glScalef(0.3, 0.4, 0.315);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();
    glPopAttrib();
}

//function to draw air shield/back number plate
void drawAirshield(GLfloat x,int lon) {
    GLfloat ambi[] = { 0.234,0.234,0.234,1 }, diff[] = { 0.1,0.1,0.1,1 }, ambi1[] = { 0,0,0,1 };
    glPushMatrix();
    glTranslatef(-11.45+x, -9, 3);
    glScalef(0, 1, 0.45);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glBegin(GL_POLYGON);
    glVertex3f(0, 0.5, 1.5);
    glVertex3f(0, 0.5, -1.5);
    glVertex3f(0, -0.5, -1);
    glVertex3f(0, -0.5, 1);
    glEnd();
    glPopAttrib();
    glPushMatrix();
    glLineWidth(2);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi1);
    if (lon) {
    glBegin(GL_LINES);
    glVertex3f(0, 0.2, 1.2);
    glVertex3f(0, 0.2, -1.2);
    glVertex3f(0, -0.2, 0.8);
    glVertex3f(0, -0.2, -0.8);
    glEnd();
    }
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0.5, 1.5);
    glVertex3f(0, 0.5, -1.5);
    glVertex3f(0, -0.5, -1);
    glVertex3f(0, -0.5, 1);
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopAttrib();
}

//function to assemble all the car parts at correct possitions 
void drawCar() {
    GLfloat mat_ambient[] = { 0, 0, 1,  1.0 };
    GLfloat mat_diffuse[] = { 0,0,1,1.0 };
    GLfloat mat_specular[] = { 0, 0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 30 }, ambi[] = {0.345,0.345,0.345,1};
    glPushMatrix();
    glTranslated(-5, 0, 0.2);
    drawWheels(); 

    //base
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi);
    glPushMatrix();
    glColor3f(0.4, 0.4, 0.4);
    glTranslatef(-18, -10.9, 3);
    glScalef(12, 0.6, 2.58);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
    
    //body
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(-18, -9.2, 3);
    glScalef(13, 3, 2.58);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
    
    //glass
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    GLfloat mat_ambient2[] = { 0.227, 0.796, 1,  1.0 };
    GLfloat mat_diffuse2[] = { 0.656,0.656,0.656,1.0 };
    GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess2[] = { 100 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
    glPushMatrix();
    glColor3f(0.529, 0.808, 0.93);
    glTranslatef(-18, -7, 3);
    glScalef(8, 2.6, 2.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
    
    //top
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(-18, -5.6, 3);
    glScalef(8, 0.2, 2.5);
    glutSolidCube(1);
    glPopMatrix();

    //sideslangs
    drawSideslang(-4, 1.25);
    drawSideslang(4, 1.25);
    drawSideslang(0, 1.25);
    drawSideslang(0, -1.25);
    drawSideslang(4, -1.25);
    drawSideslang(-4, -1.25);
    glPopAttrib();

    //head lights
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
    GLfloat pos[] = { -11,-10,1 ,1 };
    GLfloat col[] = { 1,1,1,1 };
    GLfloat light_ambient[] = { 0.5, 0.5, 0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    drawHeadlight(-0.06, -0.95,1);
    glPopAttrib();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glLightfv(GL_LIGHT2, GL_POSITION, pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    drawHeadlight(-0.06, 0.95,1);
    glPopAttrib();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 0, 0);
    drawHeadlight(-13, -0.95,0);
    drawHeadlight(-13, 0.95,0);
    glPopMatrix(); 

    //airshield
    glPushMatrix();
    glColor3f(0.656, 0.656, 0.656);
    drawAirshield(0,1);
    glPopMatrix();

    //back plate
    glPushMatrix();
    glColor3f(1, 1, 1);
    drawAirshield(-13.1, 0);
    glPopMatrix();
  
    glPopMatrix();
}

//function to draw a single mountain in background
void mountain(GLfloat tx,GLfloat sy,GLfloat ry,GLfloat tz) {
    GLfloat ambi[] = { 0.567,0.567,0.567 }, diff[] = { 0.323,0.323,0.323 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, diff);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi);
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(30-tx, -10.89, -5.567+tz);
    glScalef(30, 35+sy, 5);
    glRotatef(15*ry, 0, 1, 0);
    glRotatef(230, 0, 0, 1);
    glutSolidTetrahedron();
    glPopMatrix();
    glPopAttrib();
}

//function to assemble different mountains at different possition  
void drawMountain() {
    mountain(0,0,1,0.5);
    mountain(20,5,1.5,0.6);
    mountain(35, 5, 1, 0.256);
    mountain(45, 3, 1, 0);
    mountain(60, 8, 1, 0.356);
    mountain(65, 50, 0.2, 2);
}

//function to draw a star
void drawStar(GLfloat tx,GLfloat ty,GLfloat tz, GLfloat sx, GLfloat sy, GLfloat sz,int x) {
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    GLfloat mat_ambient2[] = { 1,1,1,1 };
    GLfloat mat_diffuse2[] = { 1,0,0,1 };
    GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess2[] = { 300 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-20+tx, 20+ty, 2+tz);
    glScalef(0.05+sx, 0.05+sy, 0.05+sz);
    if (x == 0)
        glutSolidIcosahedron();
    else if (x == 1)
        glutSolidOctahedron();
    else if(x==2)
        glutSolidDodecahedron();
    glPopMatrix();
    glPopAttrib();
}

//function to draw the set of stars
void drawStarSet(GLfloat tx, GLfloat ty, GLfloat tz) {
    drawStar(-5+tx, 5+ty, 0+tz, 0, 0, 0, 0);
    drawStar(-3+tx, 3+ty, 0+tz, 0, 0, 0, 0); 
    drawStar(-5+tx, -3+ty, 0+tz, 0, 0, 0, 0);
    drawStar(0+tx, 0+ty, 0+tz, 0, 0, 0, 0);
    drawStar(5+tx, 5.5+ty, 1+tz, 0.02, 0.02, 0.02, 0);
    drawStar(10+tx, 5+ty, 0+tz, 0, 0, 0, 0);
}

//function to assemble the set of stars in space
void drawStarSpace() {
    drawStarSet(0,0,0);
    drawStarSet(10, -2, 0);
    drawStarSet(20, 2, -1);
    drawStar(22, 8, -1, 0.1, 0.1, 0.1, 1);
    drawStarSet(30, 0, 0);
    drawStarSet(40, 3, 2);
    drawStar(45, 9, -2, 0.06, 0.06, 0.06, 2);
    drawStarSet(35, -3, -2);
}

//function to draw pot hole 
void drawPothole() {
    GLfloat ambi[] = { 0.5,0.4,0,1 }, diff[] = { 0.322,0.329,0.047,1 }, diff1[] = {0,0,0,1};
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff1);
    glPushMatrix();
    glColor3f(0.361, 0.259, 0.055);
    glTranslatef(-0.6, -18.2, 0);
    glScalef(8.6, 11.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glPushMatrix();
    glColor3f(0.361, 0.259, 0.055);
    glTranslatef(-3.3, -17.79, 3);
    glScalef(0.2, 10.2, 7);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.361, 0.259, 0.055);
    glTranslatef(-0.2, -23, 1);
    glScalef(6.5, 0.2, 10.998);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.361, 0.259, 0.055);
    glTranslatef(1.9, -18.15, 3);
    glScalef(0.2, 10.2, 7);
    glutSolidCube(1);
    glPopMatrix();
    glPopAttrib();
    glPopAttrib();
}

//function to draw the spherical rock
void drawSpere(GLfloat tx,GLfloat ty,GLfloat tz) {
    GLfloat ambi[] = { 0.643,0.671,0.118 }, diff[] = { 0.527,0.539,0.047 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, diff);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ambi);
    glPushMatrix();
    glColor3f(0.522, 0.427, 0.059);
    glTranslatef(-14.8+tx, -11.4+ty, 3+tz);
    glScalef(2.89, 1.75, 2.2);
    glutSolidSphere(1, 25, 25);
    glPopMatrix();
    glPopAttrib();
}

//function for the push operation 
void Push() {
    glPushMatrix();
    glPushMatrix();
    drawSpere(tx, ty, 0);
    glPopMatrix();
    glPushMatrix(); 
    glTranslatef(movX, 0, 0);
    drawCar();
    glPopMatrix();
    glPushMatrix(); 
    for (int i = -1; i <= s.top; i++) {
        if (i > 0) {
            drawSpere(14.3, -10 + ptY, 2);
            ptY += 2.5;
        }
        
    }
    glPopMatrix();
    glutTimerFunc(100, move, 1);
    glPopMatrix();
}

//function for the pop operation
void Pop() {
    glPushMatrix();
    glTranslatef(0, pty, ptz);
    drawSpere(14.3, -10 + 2.5*pr, 2);
    glutTimerFunc(100, PopMov, 1);
    glPopMatrix();
}

void playGame() {
    //start position
    if (start == 0)
        drawCar();
    //moving state
    else if (start == 1) {
        glPushMatrix();
        glTranslatef(movX, 0, 0);
        drawCar();
        glutTimerFunc(100, move, 1);
        glPopMatrix();
        for (int i = -1; i < s.top; i++) {
            drawSpere(14.3, -10 + ptY, 2);
            ptY += 2.5;
        }
    }
    //stop state
    else if (start == 2) {
        glPushMatrix();
        if (po == 1) {
            if ( pl == 0 ) {
                //&& ps==1
                glColor3f(1, 1, 1);
                renderBitmapString(-5, 4, (void*)font, "There is no more Rock to pop");
            }
            else {
                Pop();
            }
        }
        glPopMatrix();
        glPushMatrix();
        for (int i = -1; i < s.top; i++) {
            drawSpere(14.3, -10 + ptY, 2);
            ptY += 2.5;
        }
        glTranslatef(movX, 0, 0);
        drawCar();
        glPopMatrix();
    }
    //hold if not fill
    else if (start == 3) {
        glPushMatrix();
        glTranslatef(movX, 0, 0);
        drawCar();
        glPopMatrix();
        glPushMatrix();
        glColor3f(1,1,1);
        if(pu==0){
        renderBitmapString(-7.8, 6, (void*)font, "Oops!! you have a pot hole ahead u cant move");
        renderBitmapString(-5, 4, (void*)font, "Push a rock into the hole to move");
        for (int i = -1; i < s.top; i++) {
            drawSpere(14.3, -10 + ptY, 2);
            ptY += 2.5;
        }
        }
        glPopMatrix();
    }
    //push operation
    else if (start == 4) {
        if (pr==6) { 
            glPushMatrix();
            glTranslatef(movX, 0, 0);
            drawCar();
            glPopMatrix();
            glPushMatrix();
            glColor3f(1, 1, 1);
            renderBitmapString(-5, 6, (void*)font, "Pot hole is filled u can move");
            for (int i = -1; i < s.top; i++) {
                drawSpere(14.3, -10 + ptY, 2);
                ptY += 2.5;
            }
            glPopMatrix(); 
        }
        else {
            Push();
        }
    }
}

//function to draw the flag pole
void drawFlagBase() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    GLfloat ambi[] = { 0.5,0.4,0 }, diff[] = { 0.19,0.0545,0 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glTranslatef(17, -1, 0.6);
    glScalef(0.2, 20, 0.2);
    glutSolidCube(1);
    glPopAttrib();
    glPopMatrix();
}

//function to draw the flag
void drawFlag() {
    drawFlagBase();
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    GLfloat ambi[] = { 1,1,1 }, diff[] = { 0.9,0.9,0.9 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    if (pr >= 5) fy = 5.5;
    else fy = -17;
    glTranslatef(20, fy, 0.5);
    glScalef(1.5, 3.5, 1);
    glPushMatrix();
    drawFlagMap();
    if (tx >= 43 && pr>=5) Animate();
    glPopMatrix();
    glPopAttrib(); 
    glPopMatrix(); 
}

//function to draw a tree
void drawTree(GLfloat trx,GLfloat trz,GLfloat s) {
    // tree trunk
    glPushMatrix();
    glTranslatef(0+trx, -9, -4.5+trz);
    glScalef(s, s, s);
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    GLfloat ambi[] = { 0.36, 0.25, 0.20 }, diff[] = { 0.69,0.0945,0.05 };
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glTranslatef(0.0, -3.3, 4.0);
    glScalef(0.4, 3.0, 0.2);
    glRotatef(90, 0, 0, 1);
    glRotatef(90, 0, 1, 0);
    GLUquadricObj* trunk = gluNewQuadric();
    gluCylinder(trunk, 1.6, 1.7, 2.5, 8, 8);
    glPopAttrib();
    glPopMatrix();

    // Draw the top part of the tree
    glColor3f(0.0, 0.8, 0.0); // green color
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    GLfloat ambi1[] = { 0.5,1,0 }, diff1[] = { 0.5,1,0};
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff1);
    glTranslatef(0.0, 4, 4.0);
    glRotatef(270, 1, 0, 0);
    glScalef(2.5, 2.7, 2.7);
    glutSolidCone(0.8, 3.8, 10, 10);
    glPopAttrib();
    glPopMatrix();
    glPopMatrix();
}

//function to assemble the group of trees 
void drawTrees(GLfloat x) {
    drawTree(-19 - 5+x, 2.5, 0.6);
    drawTree(-22 - 5+x, -1, 1.1);
    drawTree(-17 - 5+x, 2.5, 0.6);
    drawTree(-17 - 5+x, -1, 1);
    drawTree(-13 - 5+x, 2.5, 0.6);
    drawTree(-13 - 5+x, -1, 1);
}

//the main game space function assembles all the items in the sceen to their respective position  
void mainGameSpace() {
    ptY = 0;
	GLfloat light_pos[] = { 1,1,1,0 };
	GLfloat col[] = { 0.8,0.8,0.8 };
	GLfloat col1[] = { 1,0,0};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyeX,eyeY,eyeZ,refX,refY,refZ,0,1,0);  
    drawMoon();
    drawGrass();
    drawRoad();
    drawFinish();
    drawFlag();
    glPushMatrix();
    playGame();
    drawTrees(0); 
    glPopMatrix();
    drawMountain();
    drawBoundray();  
    drawStarSpace(); 
    drawPothole();
	glutSwapBuffers(); 
}

//keyboard function to handle the keys based on their operation
void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'i': // move eye point upwards along Y axis
        eyeY += 1.0;
        break;
    case 'j': // move eye point downwards along Y axis
        eyeY -= 1.0;
        break;
    case 'k': // move eye point left along X axis
        eyeX -= 1.0;
        break;
    case 'l': // move eye point right along X axis
        eyeX += 1.0;
        break;
    case 'y':  //zoom out
        eyeZ += 1;
        break;
    case 'b': //zoom in
        eyeZ -= 1;
        break;
    case 'q': //back to default eye point and ref point
        eyeX = 0.0, eyeY = 1, eyeZ = 15, refX = 0, refY = 0, refZ = 0;
        break;
    case 'r': // move ref point upwards along Y axis
        refY += 1.0;
        break;
    case 'f': // move ref point downwards along Y axis
        refY -= 1.0;
        break;
    case 's': // move ref point left along X axis
        refX -= 1.0;
        break;
    case 'd': // move eye point right along X axis
        refX += 1.0;
        break;
    case 'a':  //move ref point away from screen/ along z axis
        refZ += 1;
        break;
    case 'c': //move ref point towards screen/ along z axis
        refZ -= 1;
        break;
    case 27:    // Escape key
        exit(0);
        break;
    case 'p': // push operation 
        pu = 1;
        if (pr == 0) { ps == 1; }
        else { ps == 0; }
        if(pr<=5){ pr++; }
        pl = pr;
        go = 0;
        po = 0;
        movX = 0;
        tx = 0;
        ty = 0;
        for (int i = -1; i < s.top; i++) {
            drawSpere(14.3, -10 + ptY, 2);
            ptY += 2.5;
        }
        ptY = 0;
        s.push();  
        start = 4;
        break;
    case 'g': // go operation
        go = 1;
        pu = 0;
        start = 1;
        break;
    case 'o': //pop operation
        ptz = 0;
        xa = ya = 0;
        pty = -10 + 2.5 * pr;
        s.pop();
        if (pr == 6) { pr = 4; }
        else if (pr > 0) {
            pr--;
        }
        if (pr == 1) {
            pl = 2;
        }
        else if (pl > 0) {
            ps = 0; pl--;
        }
        po = 1;
        go = 0;
        movX = 0;
        tx = 0;
        ty = 0;
        start = 2;
        break;
    case 'R': //reset operation
        go = 0;
        pu = 0;
        po = 0;
        pr = 0;
        s.top = -1;
        movX = 0;
        xa = ya = 0; fy = -18;
        start = 0;
        break;
   
    case '1': //to turn on and off moon light
        if (switchOne == false)
        {
            switchOne = true; amb1 = true; diff1 = true; spec1 = true;
            glEnable(GL_LIGHT0); break;
        }
        else if (switchOne == true)
        {
            switchOne = false; amb1 = false; diff1 = false; spec1 = false; glDisable(GL_LIGHT0); break;
        }
    case '2': //to turn on and off head light
        if (switchTwo == false)
        {
            switchTwo = true; amb2 = true; diff2 = true; spec2 = true;
            glEnable(GL_LIGHT1); glEnable(GL_LIGHT2);  break;
        }
        else if (switchTwo == true)
        {
            switchTwo = false; amb2 = false; diff2 = false; spec2 = false;
            glDisable(GL_LIGHT1); glDisable(GL_LIGHT2); break;
        }
    }
   
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1366,768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("pushpopGO");
    myInit();
	glutDisplayFunc(display);  
    glutKeyboardFunc(myKeyboardFunc);
	glutFullScreen();
	glutMainLoop();
	return 0;
}   