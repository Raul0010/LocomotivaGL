#include <windows.h>
#include <gl/gl.h>
#include <math.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

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

void Desenha_chamine(){

    glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glTranslatef(0.6, -3.5, -2);
        Desenha_Cilindro(1, 0.3, -0.6, 3, 2);
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
    float la[4] = {0.0, 0.0, 0.0, 0.0};
    float ld[4] = {0.8, 0.8, 0.8, 1.0};
    float ls[4] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, la);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ld);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ls);

    // definição das constantes de atenuação atmosférica
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);

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

#define MAXIMO_PARTICULAS 3000
#define TEMPO_DE_VIDA 5.f
#define INTERVALO_NASCIMENTO (TEMPO_DE_VIDA/(float)MAXIMO_PARTICULAS)
#define TAMANHO 5f
#define MIN_DELTA_T (INTERVALO_NASCIMENTO * 1.f)

typedef struct Fumaca{

    float vx, vy, vz;
    float x, y, z;
    float r,g,b;
    float vida;
    int ativa;

}Fumaca;

static Fumaca fumacas[MAXIMO_PARTICULAS];
static float mais_nova;

void Cria_Fumaca(struct Fumaca *fumaca, double t){

    float xy_angle, velocidade;

    // Start position of particle is at the fountain blow-out
    fumaca->x = 0;
    fumaca->y = 0;
    fumaca->z = 0;

    // Start velocity is up (Z)...
    fumaca->vz = 0.7f + (0.3f / 4096.f) * (float) (rand() & 4095);

    // ...and a randomly chosen X/Y direction
    xy_angle = (2.f * (float) M_PI / 4096.f) * (float) (rand() & 4095);
    fumaca->vx = 0.4f * (float) cos(xy_angle);
    fumaca->vy = 0.4f * (float) sin(xy_angle);

    // Scale velocity vector according to a time-varying velocity
    velocidade = 8 * (0.8f + 0.1f * (float) (sin(0.5 * t) + sin(1.31 * t)));
    fumaca->vx *= velocidade;
    fumaca->vy *= velocidade;
    fumaca->vz *= velocidade;

    // Color is time-varying
    fumaca->r = 50;
    fumaca->g = 50;
    fumaca->b = 50;

    /* Store settings for fountain glow lighting
    glow_pos[0] = 0.4f * (float) sin(1.34 * t);
    glow_pos[1] = 0.4f * (float) sin(3.11 * t);
    glow_pos[2] = FOUNTAIN_HEIGHT + 1.f;
    glow_pos[3] = 1.f;
    glow_color[0] = p->r;
    glow_color[1] = p->g;
    glow_color[2] = p->b;
    glow_color[3] = 1.f;*/

    // The particle is new-born and active
    fumaca->vida = 1.f;
    fumaca->ativa = 1;

}

void Atualiza_Fumaca(struct Fumaca *fumaca, float dt){

    if (!fumaca->ativa)
        return;

    fumaca->vida -= dt * (1.f / 5);

     if (fumaca->vida <= 0.f)
    {
        fumaca->ativa = 0;
        return;
    }

    fumaca->x = fumaca->x + fumaca->vx * dt;
    fumaca->y = fumaca->y + fumaca->vy * dt;
    fumaca->z = fumaca->z + fumaca->vz * dt;

}

static void gestor_da_fumaca(double t, float dt)
{
    int i;
    float dt2;

    // Update particles (iterated several times per frame if dt is too large)
    while (dt > 0.f)
    {
        // Calculate delta time for this iteration
        dt2 = dt < MIN_DELTA_T ? dt : MIN_DELTA_T;

        for (i = 0;  i < MAXIMO_PARTICULAS;  i++)
            Atualiza_Fumaca(&fumacas[i], dt2);

        mais_nova += dt2;

        // Should we create any new particle(s)?
        while (mais_nova >= INTERVALO_NASCIMENTO)
        {
            mais_nova -= INTERVALO_NASCIMENTO;

            // Find a dead particle to replace with a new one
            for (i = 0;  i < MAXIMO_PARTICULAS;  i++)
            {
                if (!fumacas[i].ativa)
                {
                    Cria_Fumaca(&fumacas[i], t + mais_nova);
                    Atualiza_Fumaca(&fumacas[i], mais_nova);
                    break;
                }
            }
        }

        dt -= dt2;
    }
}

void Desenha_Fumaca(double t, float dt){

    int i, particle_count = 0;
    float alpha;
    struct Fumaca fumaca;

    gestor_da_fumaca(t, dt);

    for (i = 0;  i < MAXIMO_PARTICULAS;  i++)
        fumaca = fumacas[i];
        {
            if (fumaca.ativa)
            {
                // Calculate particle intensity (we set it to max during 75%
                // of its life, then it fades out)
                alpha =  4.f * fumaca.vida;
                if (alpha > 1.f)
                    alpha = 1.f;

                particle_count ++;
            }

            // If we have filled up one batch of particles, draw it as a set
            // of quads using glDrawArrays.
            if (particle_count >= 50)
            {
                // The first argument tells which primitive type we use (QUAD)
                // The second argument tells the index of the first vertex (0)
                // The last argument is the vertex count
                glDrawArrays(GL_QUADS, 0, 4 * particle_count);
                particle_count = 0;
            }

            // Next particle
        }


}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "Meu Projeto";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "Meu Projeto",
                          "Meu Projeto",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          256,
                          256,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            float x, y, z;
            float tamanho, distancia;
            float t, dt, t_antigo;

            x = 4;
            y = 2;
            z= 3;
            tamanho = 1;
            distancia = 7;

            t = 10;
            dt = (t-t_antigo);
            t_antigo = t;

            glClearColor(0,0,0,0);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_NORMALIZE);
            glEnable(GL_DEPTH_TEST);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-6.0, 6.0, -6.0, 6.0, -1000.0, 1000.0);
            gluLookAt(2.0*cos(theta), 2.0*sin(theta), 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            float p[4];
            p[0] = +5*cos(theta);
            p[1] = -5*cos(theta);
            p[2] = +5*sin(theta);
            p[3] = 1.0;
            Configura_Fonte_Pontual(p);

            Desenha_Eixos();
            Configura_Material();
            glPushMatrix();
                glScalef(1.0, 1.4, 1);
                glTranslatef(-2.3, -3, -3.25);
                Desenha_Trilhos();
            glPopMatrix();
            Desenha_Locomotiva();
            Desenha_Fonte_Pontual(p);
            Desenha_Fumaca(t, dt);

            SwapBuffers(hDC);

            theta += 0.01f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

