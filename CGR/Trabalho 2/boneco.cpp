// g++ boneco.cpp -lglut -lGL -lGLU -lm -o boneco && ./boneco

#include <GL/glut.h>
#include <stdio.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void boneco() {
    GLUquadricObj *pObj;    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

	glTranslatef(0.0f, -1.0f, -5.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Inicialização da quádrica
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

    // Montagem do boneco de neve
	// Corpo do boneco
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f); // Definindo a cor do boneco como branca
    // Inicialização das esferas que formam o corpo do boneco
	gluSphere(pObj, .40f, 26, 20);  
	glTranslatef(0.0f, .550f, 0.0f); 
	gluSphere(pObj, .3f, 26, 20);
	glTranslatef(0.0f, 0.45f, 0.0f); 
	gluSphere(pObj, 0.24f, 26, 20);

	// Olhos
	glColor3f(0.0f, 0.0f, 0.0f); // Definindo os olhos do boneco como preto
    // Inicialização das esferas para os olhos
	glTranslatef(0.1f, 0.1f, 0.21f);
	gluSphere(pObj, 0.03f, 26, 20);
	glTranslatef(-0.2f, 0.0f, 0.0f);
	gluSphere(pObj, 0.03f, 26, 20);

	// Nariz
	glColor3f(1.0f, 0.07f, 0.57f); // Definindo a cor do nariz como rosa
	glTranslatef(0.1f, -0.12f, 0.0f);
	gluCylinder(pObj, 0.05f, 0.0f, 0.3f, 26, 20);

    // Boca
    glColor3f(1.0f, 0.07f, 0.57f); // Definindo a cor do boneco como rosa
    glTranslatef(0.10f, 0.0f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);
    glTranslatef(-0.22f, 0.0f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);
    glTranslatef(0.02f, -0.04f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);
    glTranslatef(0.18f, 0.0f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);
    glTranslatef(-0.04f, -0.03f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);
    glTranslatef(-0.10f, 0.0f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);
    glTranslatef(0.05f, -0.01f, 0.0f);
    gluSphere(pObj, 0.02f, 26, 20);

    // Botões da roupa
    glColor3f(0.0f, 0.0f, 0.0f); // Preto
    glTranslatef(0.0f, -0.3f, 0.1f);
    gluSphere(pObj, 0.03f, 26, 20);
    glTranslatef(0.0f, -0.3f, -0.02f);
    gluSphere(pObj, 0.03f, 26, 20);
    glTranslatef(0.0f, -0.25f, 0.12f);
    gluSphere(pObj, 0.03f, 26, 20);
    glPopMatrix();

	// Chapéu
	glPushMatrix();
	glColor3f(0.58f, 0.0f, 0.827f); // Definindo a cor roxa para o chapéu
	glTranslatef(0.0f, 1.17f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(pObj, 0.175f, 0.175f, 0.4f, 26, 20);

	// Base do chapeu
	glDisable(GL_CULL_FACE);
	gluDisk(pObj, 0.17f, 0.28f, 26, 20);
	glEnable(GL_CULL_FACE);

	glTranslatef(0.0f, 0.0f, 0.40f);
	gluDisk(pObj, 0.0f, 0.17f, 26, 20);
	glPopMatrix();

    glPopMatrix();
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

// Respond to arrow keys
void SpecialKeys(int key, int x, int y){
    if(key == GLUT_KEY_UP)
        xRot-= 5.0f;
    if(key == GLUT_KEY_DOWN)
        xRot += 5.0f;
    if(key == GLUT_KEY_LEFT)
        yRot -= 5.0f;
    if(key == GLUT_KEY_RIGHT)
        yRot += 5.0f;
        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);
    // Refresh the Window
    glutPostRedisplay();
}

int main(int argc, char *argv[]) { 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Boneco de Neve - Fernanda Maria de Souza");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(boneco);
    SetupRC();
    glutMainLoop();
    return 0;
}