/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

static int posicao = 0;
static int stacks = 16;
static int k = 10;
static int j = 0;
static int prev_k = 0;

#define MAX_PARTICLES 10000

struct particle{
    GLfloat x, y ,z;
    GLfloat vx, vy, vz;
    GLfloat life;
}particle[MAX_PARTICLES];

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void Configura_Material()
{

    // permite que a cor definida com glColor seja utilizada como material
    glEnable(GL_COLOR_MATERIAL);

    // definição dos coeficientes de reflexão do material
    // nesse exemplo o material não emite luz (ke = 0)
    float ka[4] = {0.0, 0.0, 0.0, 1.0};
    float kd[4] = {0.8, 0.8, 0.8, 1.0};
    float ks[4] = {0.5, 0.4, 0.1, 1.0};
    float ke[4] = {0.0, 0.0, 0.0, 1.0};
    int n = 20;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, n);

}


void Desenha_Cilindro(float distancia, float tamanho, float x, float y, float k){

    float theta, z;
    float du,dv,dz,dtheta;
    int n = 100;

    theta=0;
    z=0;

    dz = distancia/n;
    dtheta = 2*M_PI/n;

    glColor3f(0,1,0);
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);*/

    glBegin(GL_POLYGON);

    while (z <= distancia){
        theta = 0;
        while (theta <= 2*M_PI){


            glNormal3f(cos(theta), y+z, sin(theta));
            glVertex3f(x+tamanho*cos(theta), y+z, k+tamanho*sin(theta));

            glNormal3f(cos(theta), y+z+dz , sin(theta));
            glVertex3f(x+tamanho*cos(theta), y+z+dz, k+tamanho*sin(theta));

            glNormal3f(cos(theta+dtheta), y+z+dz, sin(theta+dtheta));
            glVertex3f(x+tamanho*cos(theta+dtheta), y+z+dz, k+tamanho*sin(theta+dtheta));

            glNormal3f(-cos(theta+dtheta), y+z, sin(theta+dtheta));
            glVertex3f(x+tamanho*cos(theta+dtheta), y+z, k+tamanho*sin(theta+dtheta) );


            theta = theta + dtheta;
        }
        z = z + dz;

    }

    glEnd();

}

void Desenha_Cilindro_Dentro_Roda (float distancia, float tamanho, float x, float y, float k){

    float theta, z;
    float du,dv,dz,dtheta;
    int n = 100;

    theta=0;
    z=0;

    dz = distancia/n;
    dtheta = 2*M_PI/n;

    glColor3f(0,1,0);

    glBegin(GL_POLYGON);

    while (z <= distancia){
        theta = 0;
        while (theta <= 2*M_PI){


            glNormal3f(-cos(theta), -y-z, -sin(theta));
            glVertex3f(x+tamanho*cos(theta), y+z, k+tamanho*sin(theta));

            glNormal3f(-cos(theta), -y-z-dz , -sin(theta));
            glVertex3f(x+tamanho*cos(theta), y+z+dz, k+tamanho*sin(theta));

            glNormal3f(-cos(theta+dtheta), -y-z-dz, -sin(theta+dtheta));
            glVertex3f(x+tamanho*cos(theta+dtheta), y+z+dz, k+tamanho*sin(theta+dtheta));

            glNormal3f(-cos(theta+dtheta), -y-z, -sin(theta+dtheta));
            glVertex3f(x+tamanho*cos(theta+dtheta), y+z, k+tamanho*sin(theta+dtheta) );


            theta = theta + dtheta;
        }
        z = z + dz;

    }

    glEnd();

}

void Desenha_Roda(){

    Desenha_Cilindro(1, 2, 0, 0, 0);
    Desenha_Cilindro_Dentro_Roda(1, 1, 0, 0, 0);

}

void Desenha_Quadrado(float r, float g, float b){

    int n = 100;
    float u, du, tamanho, v, dv;

    u = 0;
    v = 0;
    tamanho = 1;
    du = tamanho/n;
    dv = tamanho/n;

    glColor3f(r,g,b);

    glBegin(GL_POLYGON);

    while (u <= tamanho){

        v =  0;

        while (v<=tamanho){

            glNormal3f(0,0,-1);
            glVertex3f(u, v, 0);

            glNormal3f(0,0,-1);
            glVertex3f(u + du, v, 0);

            glNormal3f(0,0, -1);
            glVertex3f(u + du, v+ dv, 0);

            glNormal3f(0,0, -1);
            glVertex3f(u, v + dv, 0);

            v = v + dv;

        }

        u = u + du;

    }

    glEnd();

}

void Desenha_Cubo(float r, float g, float b){

    //face de baixo
    Desenha_Quadrado(r, g, b);

//    face em x
    glPushMatrix();

        glRotatef(270,1,0,0);
        glTranslatef(0,-1,0);
        Desenha_Quadrado(r, g, b);

    glPopMatrix();

    // face em y
    glPushMatrix();

        glRotatef(-270,0,1,0);
        glTranslatef(-1,0,0);
        Desenha_Quadrado(r, g, b);

    glPopMatrix();

    //face de cima
    glPushMatrix();

        //glRotatef(-180,1,0,0);
        glRotatef(180,0,0,0);
        glTranslatef(-1, -1, -1);
        Desenha_Quadrado(r, g, b);

    glPopMatrix();

    // face da frente
    glPushMatrix();

        glRotatef(270,0,1,0);
        glTranslatef(0,0,-1);
        Desenha_Quadrado(r, g, b);

    glPopMatrix();

    //outra face da frente
    glPushMatrix();

        glRotatef(270,1,0,0);
        glTranslatef(0,-1,1);
        Desenha_Quadrado(r, g, b);

    glPopMatrix();

}

void Desenha_Trilhos(){
    float r,g,b;
    r = 0.1;
    g = 0.1;
    b = 0.1;

    //Parte de baixo dos trilhos
    glPushMatrix();
        glScalef(3.0, 5.0, 0.5);
        Desenha_Cubo(0, 0, 1);
    glPopMatrix();

    //Madeira entre trilhos
    glPushMatrix();
        glTranslatef(0.5, 1, 0.6);
        glScalef(1.4, 1, 0.3);
        Desenha_Cubo(0.54, 0.27, 0.0745);
    glPopMatrix();

    //Madeira entre trilhos
    glPushMatrix();
        glTranslatef(0.5, 3.5, 0.6);
        glScalef(1.4, 1, 0.3);
        Desenha_Cubo(0.54, 0.27, 0.0745);
    glPopMatrix();

    // Trilho da direita
    glPushMatrix();
        glTranslatef(0.4,0,0.5);
        glScalef(0.5, 5.0, 0.7);
        Desenha_Cubo(r, g, b);
    glPopMatrix();

    // Trilho da esquerda
    glPushMatrix();
        glTranslatef(2.2,0,0.5);
        glScalef(0.5, 5.0, 0.7);
        Desenha_Cubo(r, g, b);
    glPopMatrix();

}

void Desenha_chamine(){

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.6, -3.5, -2);
        Desenha_Cilindro(1, 0.3, -0.6, 3, 2);
    glPopMatrix();

}

void Desenha_Locomotiva(){

    float r, g , b;
    r = 1;
    g = 0;
    b = 0;

    // Desenha roda de atras da cabine da locomotiva
    glPushMatrix();
        glTranslatef(0,-1,0);
        glRotatef(-90,0, 0, 1);
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(0, -4, -2);
        Desenha_Roda();
    glPopMatrix();

    //Desenha roda da frente no cano da locomotiva
    glPushMatrix();
        glTranslatef(0,-1,0);
        glRotatef(-90,0, 0, 1);
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(-8, -4, -2);
        Desenha_Roda();
    glPopMatrix();

    //Desenha cabine da locomotiva
    glPushMatrix();
        glTranslatef(-1.8 ,-1.8, -0.3);
        glScalef(2.0, 2.0, 2.0);
        Desenha_Cubo(r, g, b);
    glPopMatrix();

    //Desenha suporte ao cano da locomotiva
    glPushMatrix();
        glTranslatef( -1.5, -0.5, -1.3);
        glScalef(1.5, 5.2, 0.5);
        Desenha_Cubo(r, g, b);
    glPopMatrix();

    //Desenha cano da locomotiva
    Desenha_Cilindro(4, 1.2, -0.75, 0.2, 0.5);

    //Desenha chaminé
    glPushMatrix();
        glTranslatef(-0.65,3.6,2);
        Desenha_chamine();
    glPopMatrix();

    //Desenha roda da frente na cabine da locomotiva
    glPushMatrix();
        glTranslatef(0,-1,0);
        glRotatef(-90,0, 0, 1);
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(0, 0, -2);
        Desenha_Roda();
    glPopMatrix();

    //Desenha roda da frente no cano da locomotiva
    glPushMatrix();
        glTranslatef(0,-1,0);
        glRotatef(-90,0, 0, 1);
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(-8, 0, -2);
        Desenha_Roda();
    glPopMatrix();

}

void Desenha_Eixos(){

    glLineWidth(1);
    glBegin(GL_LINES);

    glColor3f(1,0,0);

    glVertex3f(-2,0,0);
    glVertex3f(2,0,0);

    glColor3f(0,1,0);

    glVertex3f(0,-2,0);
    glVertex3f(0,2,0);

    glColor3f(0,0,1);

    glVertex3f(0,0,-2);
    glVertex3f(0,0,2);

    glEnd();


}

void Configura_Fonte_Pontual(float p[])
{

    glEnable(GL_LIGHT0); // habilita o uso da fonte 0
    glEnable(GL_LIGHTING); // habilita o uso do modelo de iluminação

    // apaga completamente a luz ambiente padrão {0,0,0,1}
    float LAP[4] = {0.0, 0.0, 0.0, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LAP);

    // posição da fonte pontual
    glLightfv(GL_LIGHT0, GL_POSITION, p);

    // definição das intensidades luminosas de cada componente
    // neste exemplo não há luz ambiente
    float la[4] = {0.2, 0.2, 0.2, 1.0};
    float ld[4] = {0.8, 0.8, 0.8, 1.0};
    float ls[4] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, la);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ld);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ls);

}

void Desenha_Fonte_Pontual(float p[])
{

    // desenha um ponto amarelo
    glDisable(GL_LIGHTING); // não será utilizado o modelo de iluminação
    glEnable(GL_POINT_SMOOTH);
    glPointSize(3);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    glVertex3fv(p); //desenha o ponto nas mesmas coordenadas da fonte

    glEnd();

}

void Cria_Fumaca(){
int i;
    for(i=prev_k; i<k; i++){

        particle[i].x = -0.5+0.15*sin(2*M_PI*i/10);
        particle[i].y = 3.63+posicao+0.15*cos(2*M_PI*i/10);
        particle[i].z = 2.7;
        particle[i].vz = 0.5;//rand()%10;
        particle[i].life = 12;
    };
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    float x, y, z;
    float tamanho, distancia;
    int i;

    x = 4;
    y = 2;
    z= 3;
    tamanho = 1;
    distancia = 7;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    //glEnable(GL_NORMALIZE);
   // glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -1000.0, 1000.0);
    gluLookAt(2.0, posicao, 2, 0,3+ posicao, 0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Cria_Fumaca();

    float p[4];
    p[0] = 0;
    p[1] = 5;
    p[2] = +20;
    p[3] = 0.0;
    Configura_Fonte_Pontual(p);

    Desenha_Eixos();
    Configura_Material();
    for(i=-1+posicao/7; i <=4+posicao/7; i++){
        glPushMatrix();
            glScalef(1.0, 1.4, 1);
            glTranslatef(-2.3, -3 + i*5, -3.25);
            Desenha_Trilhos();
        glPopMatrix();
    }
    glPushMatrix();
        glTranslatef(0, posicao, 0);
        Desenha_Locomotiva();
    glPopMatrix();
    Desenha_Fonte_Pontual(p);

    glPushMatrix();
        glScalef(200, 200, 2);
        glTranslatef(-0.5,-0.5,-4);
        Desenha_Cubo(0.5, 1, 0.5);
    glPopMatrix();

    //glColor3f(0,0,0);

    j = k;

    for(i=0; i<k; i++){
        j+=1;
        particle[i].z += particle[i].vz;
        glColor3f(4/particle[i].life,4/particle[i].life,4/particle[i].life);
        glPointSize(24/(particle[i].life));
        glBegin(GL_POINTS);
        particle[i].life -=1;
        if(particle[i].life >0){
            glVertex3f(particle[i].x, particle[i].y, particle[i].z);
        }
        glEnd();

    };

    prev_k = k;
    k = j;

    if(k>=MAX_PARTICLES){
        k = 10;
        j = 0;
        prev_k = 0;
    }

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case 'w':
            posicao++;
            stacks++;
            break;

        case 's':
            posicao--;
            stacks--;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    int i;

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Locomotiva");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0,1,1);
    //glEnable(GL_CULL_FACE);
     //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
