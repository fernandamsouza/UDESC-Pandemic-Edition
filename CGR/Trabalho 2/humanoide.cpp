// g++ humanoide.cpp -lglut -lGL -lGLU -lm -o humanoide && ./humanoide

#include <GL/glut.h>
#include <stdio.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat zRot = 0.0f;

static GLfloat xRotBracoDir = 0.0f;
static GLfloat yRotBracoDir = 0.0f;

static GLfloat zRotPernaDir = 0.0f;
static GLfloat zRotPernaEsq = 0.0f;

static GLfloat xRotBracoEsq = 0.0f;
static GLfloat yRotBracoEsq = 0.0f;


void mouse(int button, int state, int mouseX, int mouseY);

void humanoide(void){
    GLUquadricObj *pObj;    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); 

    // Cabeca
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Olhos
    glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0.1f, 0.3f, 1.0f);
	gluSphere(pObj, 0.05f, 26, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(-0.1f, 0.3f, 1.0f);
	gluSphere(pObj, 0.05f, 26, 20);
    glPopMatrix();

    // Boca
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.25f, 0.85f);
    glScalef(0.5f, 0.5f, 0.5f);
    glutSolidCube(0.10f);
    glPopMatrix();

    // Tronco
    glPushMatrix();
    glColor3f(1.0f, 0.6f, 0.8f);
    glScalef(1.0f, 1.0f, 1.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Braco direito
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(xRotBracoDir, 3.0f, 0.0f, 0.0f);
    glRotatef(yRotBracoDir, 0.0f, -1.0f, 0.0f);
    glTranslatef(0.75f, 0.0f, 0.10f);
    glScalef(0.5f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Perna direita
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(zRotPernaDir, 3.0f, 1.0f, 0.0f);
    glTranslatef(0.25f, 0.0f, -1.0f);
    glScalef(0.45f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Perna esquerda
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(zRotPernaEsq, 3.0f, 1.0f, 0.0f);
    glTranslatef(-0.25f, 0.0f, -1.0f);
    glScalef(0.45f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Braco esquerdo
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(-xRotBracoEsq, -3.0f, 0.0f, 0.0f);
    glRotatef(yRotBracoEsq, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.75f, 0.0f, 0.10f);
    glScalef(0.5f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix(); 
    glPopMatrix();
    glutSwapBuffers();
}

// Setas
void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP){
        xRot-= 5.0f;
    }
    if(key == GLUT_KEY_DOWN){
        xRot += 5.0f;
    }
    if(key == GLUT_KEY_LEFT){
        yRot -= 5.0f;
    }
    if(key == GLUT_KEY_RIGHT){
        yRot += 5.0f;
    }
    xRot = (GLfloat)((const int)xRot % 360);
    yRot = (GLfloat)((const int)yRot % 360);
    glutPostRedisplay();
}

void TeclasPressionadas(unsigned char tecla, int x, int y) {
    if (tecla == 'r') {
      zRotPernaDir -= 5.0f;
      xRotBracoEsq -= 5.0f;
      zRotPernaEsq += 5.0f;
      xRotBracoDir += 5.0f;
    }
    xRotBracoEsq = (GLfloat)((const int)xRotBracoEsq % 45);
    xRotBracoDir = (GLfloat)((const int)xRotBracoDir % 45);
    zRotPernaDir = (GLfloat)((const int)zRotPernaDir % 45);
    zRotPernaEsq = (GLfloat)((const int)zRotPernaEsq % 45);

    glutPostRedisplay();
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
    //gluPerspective(35.0f, fAspect, 1.0, 40.0);
    gluPerspective(45.0f, fAspect, 1.0, 40.0);

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
    glClearColor(1.0f, 0.41f, 0.70f, 1.0f);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Humanoide - Fernanda Maria de Souza");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(humanoide);
    glutKeyboardFunc(TeclasPressionadas);
    SetupRC();
    glutMainLoop();
    return 0;
}