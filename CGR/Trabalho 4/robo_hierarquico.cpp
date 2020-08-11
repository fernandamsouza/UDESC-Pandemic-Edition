// g++ robo_hierarquico.cpp -o robo_hierarquico -lglut -lGL -lGLU -lm && ./robo_hierarquico
// Fernanda Maria de Souza
// Trabalho 4 de CGR - Robô hierárquico                                                                                      
// Teclas:                                                                             
//        - 'A' faz o Robô andar.                                          
//        - 'P' para o Robô.                                                           
//        - 'T' faz o Robô acenar.                                                     
                                                                                    
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Enumera as ações do robô
enum ACAO {PARAR, ANDAR, ACENAR} acao = PARAR;

float ombroESQ = 0.0, maoESQ = 0.0, pernaESQ = 0.0;
float ombroDIR = 0.0, pernaDIR = 0.0;

// Quadrica usada para cabeça, braço, mão, perna, pé e torso.
void quads(float c, float l, float a) {
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(l, 0.0, 0.0);
        glVertex3f(l, c, 0.0); glVertex3f(0.0, c, 0.0);
        glNormal3f(0,0,1);
        glVertex3f(0.0, 0.0, a);  glVertex3f(l, 0.0, a);
        glVertex3f(l, c, a); glVertex3f(0.0, c, a);
        glNormal3f(-1,0,0);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, a);
        glVertex3f(0.0, c, a); glVertex3f(0.0, c, 0.0);
        glNormal3f(0,-1,0);
        glVertex3f(0.0, 0.0, 0.0);  glVertex3f(0.0, 0.0, a);
        glVertex3f(l, 0.0, a);  glVertex3f(l, 0.0, 0.0);
        glNormal3f(1,0,0);
        glVertex3f(l, 0.0, 0.0);  glVertex3f(l, 0.0, a);
        glVertex3f(l, c, a); glVertex3f(l, c, 0.0);
        glNormal3f(0,1,0);
        glVertex3f(0.0, c, 0.0); glVertex3f(0.0, c, a);
        glVertex3f(l, c, a); glVertex3f(l, c, 0.0);
    glEnd();
}

void robo(void) {
    glPushMatrix();
        // Tronco
        glColor3f(1.0f, 0.41f, 0.70f);
        quads(20.0, 15.0, 25.0); 
        quads(20.0, 15.0, -10.0); 
        // Estrutura hierarquica da perna esquerda + articulação
        glPushMatrix();
            glColor3f(1.0, 0.07, 0.57);
            glTranslatef(0.0, 8, -8.0);
            glRotatef(pernaESQ, 0.0, 1.0, 0.0);
            glutSolidSphere(4.0,  20.0,  20.0);  //  Articulação da Perna Esquerda
            // Perna esquerda
            glColor3f(1.0f, 0.41f, 0.70f);
            glTranslatef(-4.0, -4.0, -28.0);
            quads(8.0, 8.0, 25.0); 
            // Estrutura hierarquica da perna esquerda envolvendo canela, tornozelo e pé.         
            glPushMatrix();
                // Canela
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-4.0, -4.0, -28.0);
                quads(8.0, 8.0, 30.0);   
                // Tornozelo
                glColor3f(1.0, 0.07, 0.57);
                glTranslatef(4.0, 4.0, -3.0);
                glutSolidSphere(4.0,  20.0,  20.0);  
                // Pé
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-6.0, -5.0, -8.0);
                quads(10.0, 18.0, 5.0);  
            glPopMatrix();
        glPopMatrix();
        // Estrutura hierarquica da perna direita + articulação
        glPushMatrix();
            glColor3f(1.0, 0.07, 0.57);
            glTranslatef(0.0, -6.0, -8.0);
            glRotatef(pernaDIR, 0.0, 1.0, 0.0);
            glutSolidSphere(4.0,  20.0,  20.0); //  Articulação da Perna direita
            // Perna Direita
            glColor3f(1.0f, 0.41f, 0.70f);
            glTranslatef(-4.0, -4.0, -28.0);
            quads(8.0, 8.0, 25.0);   
            // Estrutura hierarquica da perna direita envolvendo canela, tornozelo e pé.        
            glPushMatrix();
                // Canela
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-4.0, -4.0, -28.0);
                quads(8.0, 8.0, 30.0);       
                // Tornozelo
                glColor3f(1.0, 0.07, 0.57);
                glTranslatef(4.0, 4.0, -3.0);
                glutSolidSphere(4.0,  20.0,  20.0); 
                // Pé 
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-6.0, -5.0, -8.0);
                quads(10.0, 18.0, 5.0);     
            glPopMatrix();
        glPopMatrix();
        // Estrutura hierarquica do ombro direito
        glPushMatrix();
            glColor3f(1.0, 0.07, 0.57);
            glTranslatef(0.0, -17.0, 27.0);
            glRotatef(ombroDIR, 0.0, 1.0, 0.0);
            glutSolidSphere(5.0,  20.0,  20.0);    // Ombro Direito
            // Antebraço
            glColor3f(1.0f, 0.41f, 0.70f);
            glTranslatef(-4.0, -4.0, -20.0);
            quads(7.0, 7.0, 16);     
            // Estrutura hierarquica do braço direito envolvendo o braço, pulso e mão.
            glPushMatrix();
                // Braço
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-1.0, -0.5, -16.0);
                quads(8.0, 8.0, 16.0);        
                glColor3f(1.0, 0.07, 0.57);
                glTranslatef(4.0, 4.0, -2.0);
                glutSolidSphere(3.0, 20.0, 20.0); // Pulso direito
                // Mão  
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-4.0, -2.0, -12.0);
                quads(4.0, 8.0, 10.0);       
            glPopMatrix();
        glPopMatrix();
        // Estrutura hierarquica do braço esquerdo
        glPushMatrix();
            glColor3f(1.0, 0.07, 0.57);
            glTranslatef(0.0, 23.0, 27.0);
            glRotatef(ombroESQ, 0.0, 1.0, 0.0);
            glutSolidSphere(5.0,  20.0,  20.0);    // Ombro Esquerdo
            // Antebraço
            glColor3f(1.0f, 0.41f, 0.70f);
            glTranslatef(-4.0, -3.0, -20.0);
            quads(7.0, 7.0, 16.0);       
            // Estrutura hierarquica do braço direito envolvendo o braço, pulso e mão.
            glPushMatrix();
                // Braço
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-1.0, -0.5, -16.0);
                quads(8.0, 8.0, 16.0);       
                glColor3f(1.0, 0.07, 0.57);
                glTranslatef(4.0, 4.0, -2.0);
                glRotatef(maoESQ, 0.0, 1.0, 0.0);
                glutSolidSphere(3.0,  20.0,  20.0); // Pulso esquerdo
                // Mão
                glColor3f(1.0f, 0.41f, 0.70f);
                glTranslatef(-4.0, -2.0, -12.0);
                quads(4.0, 8.0, 10.0);     
            glPopMatrix();
        glPopMatrix();
        // Cabeça
        glColor3f(1.0f, 0.41f, 0.70f);
        glTranslatef(-6.0, -6.0, 31.0);
        quads(12.0, 12.0, 12.0);      
        quads(12.0, 12.0, -10.0);      
    glPopMatrix();
}

void DrawScene(void) {
    GLfloat posicao_luz[] = {500.0, 500.0, 500.0, 1.0};
    double o_x, o_y, o_z;
    static float Posicaox = -600.0;
    static double velocidade = 0.0;

    // Posicionando campo de visao
    o_x = Posicaox + 800.0;
    o_y = 800.0;
    o_z = 800.0 * cos(1.5);
    glLoadIdentity();
    gluLookAt(o_x, o_y, o_z, Posicaox, 0.0, 0.0, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Iluminacao
    glLightfv (GL_LIGHT0, GL_POSITION, posicao_luz);
    glEnable(GL_LIGHTING);
    // Cria o piso
    int i, j, c = 100;
    for(i = -20; i <= 20; i++) {
        for(j = -20; j <= 20; j++) {
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f(i * c, j * c, 0.0);
                glVertex3f(i * c + c, j * c, 0.0);
                glVertex3f(i * c + c, j * c + c, 0.0);
                glVertex3f(i * c, j * c + c, 0.0);
            glEnd();
        }
    } 
    if (acao == ANDAR) {
        Posicaox += fabs(3.0 * sin((70 + velocidade) * 0.01745)); // Posicao do robo no plano
        velocidade = fmod(velocidade + 8.0, 360.0);
    }
    glTranslatef(Posicaox, 0.0, 85);    // Movimentos do robo
    robo();   // Robo posto no plano
    glutSwapBuffers();
}

void SetupRC() {
    GLfloat whiteLight[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat sourceLight[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightPos[] = { 1.0, 1.0, 1.0, 1.0 };
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT0,GL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void movimento(ACAO a) {
    static double velocidade = 0.0;
    switch(a) {
        case ANDAR: 
            maoESQ = 0.0;
            pernaDIR = 20.0 * sin(velocidade * 0.01745); 
            ombroDIR = -30.0 * sin(velocidade * 0.01745); 
            pernaESQ = -20.0 * sin(velocidade * 0.01745); 
            ombroESQ = 30.0 * sin(velocidade * 0.01745);  
            velocidade = fmod(velocidade + 8.0, 360.0); 
            break;
        case PARAR: 
            if(velocidade == 0.0) break;
            break;
        case ACENAR:
            float passo2;
            ombroESQ = -200.0 * sin(velocidade * (0.01745/2));  
            maoESQ = 30.0 * sin(velocidade * 0.01745); ;
            velocidade = fmod(velocidade + 8.0, 360.0); 
            break;
    }
}

void ChangeSize(int w, int h) {
    if(w < 700) glutReshapeWindow(700, h);
    if(h < 500) glutReshapeWindow(w, 500);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(24.0f, (GLfloat)w / (GLfloat)h, 0.5f, 10000.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Andar & acenar & parar
void keyboard(unsigned char key, int a, int b) {
    switch (key) {
        case 'p':
            acao = PARAR;
            break;
        case 'a':
            acao = ANDAR;
            break;
        case 't':
            acao = ACENAR;
            break;
    }
}

void Loop(int w) {
    glutPostRedisplay();
    movimento(acao);
    glutTimerFunc(40, Loop,1);
}

// Programa Principal
int main(int argc, char*argv[]) {
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Fernanda Maria de Souza - Robo Hierarquico - Anda e acena");
    glutDisplayFunc(DrawScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keyboard);
    SetupRC();
    Loop(1);
    glutMainLoop();
}
