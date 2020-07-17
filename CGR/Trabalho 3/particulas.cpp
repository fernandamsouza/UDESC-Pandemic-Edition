// g++ particulas.cpp -lglut -lGL -lGLU -lm -o particulas && ./particulas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define QTDGOTAS 5000

int loop;

typedef struct {
    bool on;
    float life, off, xPos,yPos, zPos, vel, gravity;
} particula;


particula p[QTDGOTAS];

void iniciap(int i) {
    p[i].on = true;
    p[i].life = 1.5;
    p[i].off = float(rand() % 100) * 0.001;
    p[i].xPos = (float) (rand() % 40) - 10;
    p[i].yPos = 15.0;
    p[i].zPos = (float) (rand() % 20) - 10;
    p[i].vel = 0.00008;
    p[i].gravity = -0.0009;
}

void chuva() {
    for (loop = 0; loop < QTDGOTAS; loop++) {
        iniciap(loop);
    }
}

void CChuva() {
    float x, y, z;
    for (loop = 0; loop < QTDGOTAS; loop = loop + 2) {
        if (p[loop].on == 1) {
            x = p[loop].xPos;
            y = p[loop].yPos;
            z = p[loop].zPos - 25;
            glColor3f(0.2f, 0.4f, 1.0f);
            glBegin(GL_LINES);
            glVertex3f(x-1, y, z); 
            glVertex3f(x, y+1, z); 
            glEnd();
            p[loop].yPos += p[loop].vel;
            p[loop].xPos += p[loop].vel;
            p[loop].vel += p[loop].gravity;
            p[loop].life -= p[loop].off;
            if (p[loop].life < 0.0) {
                iniciap(loop);
            }
        }
    }
}

void desenharCena() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 0.41f, 0.70f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glEnd();
    CChuva();
    glutSwapBuffers();
}

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h){
    GLfloat fAspect;
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void repetir() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chuva - Fernanda Maria de Souza");
    chuva(); 
    glutDisplayFunc(desenharCena); 
    glutReshapeFunc(ChangeSize);
    glutIdleFunc(repetir);
    glutMainLoop();
    return 0;
}