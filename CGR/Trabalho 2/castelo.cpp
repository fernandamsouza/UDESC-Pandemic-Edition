// g++ castelo.cpp -lglut -lGL -lGLU -lm -o castelo && ./castelo
#include <GL/glut.h>
#include <stdio.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void desenhaTorre(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z);
void desenhaTorreMeio(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z);


void castelo(){
    GLUquadricObj *pObj;    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	glTranslatef(0.0f, -1.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 

    // torres
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTorreMeio(pObj, 0.0f, 1.5f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTorre(pObj, 1.5f, 0.0f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTorre(pObj, -1.5f, 0.0f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTorre(pObj, 1.5f, 3.0f, 1.0f);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTorre(pObj, -1.5f, 3.0f, 1.0f);
    glPopMatrix();

    // chão
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 1.0f);
    glTranslatef(0.0f, 1.0f, 0.125f);
    glScalef(5.0f, 4.0f, 0.125f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // paredes
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glScalef(3.0f, 0.125f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.9f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glScalef(3.0f, 0.250f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 3.0, 0.5f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glScalef(3.0f, 0.125f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 3.0, 0.9f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glScalef(3.0f, 0.250f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 1.5, 0.5f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glScalef(0.125f, 3.0f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 1.5, 0.9f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glScalef(0.250f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 1.5, 0.5f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glScalef(0.125f, 3.0f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5, 1.5, 0.9f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glScalef(0.250f, 3.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}


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


// This function does any needed initialization on the rendering context.
//  Here it sets up and initializes the lighting for the scene.
void SetupRC(){

    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);    // Hidden surface removal
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);     // Do not calculate inside

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP) {
        xRot-= 5.0f;
    }
    if(key == GLUT_KEY_DOWN) {
        xRot += 5.0f;
    }
    if(key == GLUT_KEY_LEFT) {
        yRot -= 5.0f;
    }
    if(key == GLUT_KEY_RIGHT) {
        yRot += 5.0f;
    }
    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Castelo - Fernanda Maria de Souza");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(castelo);
    SetupRC();
    glutMainLoop();
    return 0;
}

void desenhaTorre(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z){
    glTranslatef(x, y, z-0.8f);
    gluCylinder(quad, 0.3f, 0.3f, 1.1f, 26, 13);
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluCylinder(quad, 0.4f, 0.0f, 0.5f, 26, 13);
}

void desenhaTorreMeio(GLUquadricObj *quad, GLfloat x, GLfloat y, GLfloat z){
    glTranslatef(x, y, z-0.8f);
    gluCylinder(quad, 0.9f, 0.5f, 1.1f, 26, 13);
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluCylinder(quad, 1.0f, 0.0f, 0.5f, 26, 13);
}