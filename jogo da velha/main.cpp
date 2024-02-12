#include<GL/Glut.h>
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <math.h>
#include <string.h>


float x,y,xS,yS;
bool checkx=false;
bool checko=false;
bool animation=false;
bool clique = true;
int i=0;
int ganhadory=0;
int ganhadorx=0;
int selecionaCorLinha=0;
int caixaSelecionada[9]={0,0,0,0,0,0,0,0,0};
int a=0;
int b=0;
int menu = 0;
int selecionar = 0;
int entrar = 0;

void display(void);
void mouse(int button, int state, int mousex, int mousey);
void pegatecla(unsigned char tecla, GLint x, GLint y);
void desenhaTabuleiro();
void desenhaTabuleiroInicial();
void timer(int valor);
void desenhaX(float xS , float yS);
void desenhaO(float xS,float yS);
int checarGanhador (int g[]);
void desenhaGanhador(int decidir);
void desenhaVez();
void escreve();
void desenhaTelaFinal();
void desenhaMenu();
void output(int x, int y, int font, char *string);
void desenhaXmenu(float xS ,float  yS, float raio);
void desenhaOmenu(float xS ,float  yS, float raio);
void selecionado(int x1, int y1, int x2, int y2);
void paginaDesenvolvedor();
void desenvolvidoPor(int x, int y, int font, char *string);

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
    glutInitWindowSize(900,700);
    glutInitWindowPosition(1920/2-450,1080/2-350);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("TIC TAC TOE");
    glClearColor(0.100, 0.244, 0.353, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutKeyboardFunc(pegatecla);
    glutMainLoop();
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);

    switch(menu)
    {
    case 0: desenhaMenu();
            if(selecionar == 0)
            {
                selecionado(195,193,705,258);
            }
            if(selecionar == 1)
            {
                selecionado(195,318,705,383);
            }
            if(selecionar == 2)
            {
                selecionado(195,440,705,505);
            }
        break;

    case 1: paginaDesenvolvedor();
        break;
    case 2:
    if(b == 0)
    {
        desenhaTabuleiroInicial();
        desenhaVez();
    }

    glLineWidth(5);

    if(checkx)
    {
        desenhaX(xS,yS);
        checkx=false;
        i++;
        desenhaVez();
    }

    if(checko)
    {
        desenhaO(xS,yS);
        checko=false;
        i++;
        desenhaVez();
    }
    if(selecionaCorLinha == 0)
        selecionaCorLinha = checarGanhador(caixaSelecionada);
    if(selecionaCorLinha != 0 && a == 0)
        i = 9;

    if (i == 9)
    {
        if(a == 0)
            desenhaGanhador(selecionaCorLinha);
        glPointSize(5);
        glBegin(GL_POINTS);
            glVertex2i(ganhadorx,ganhadory);
        glEnd();
        animation = true;
        if(animation)
            glutTimerFunc(0,timer,7);
    }
    }
    glutSwapBuffers();
}

void desenhaX(float xS ,float  yS)
{
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex2f(xS-60,yS-60);
        glVertex2f(xS+60,yS+60);

        glVertex2f(xS-60,yS+60);
        glVertex2f(xS+60,yS-60);
    glEnd();
}

void desenhaO(float xS ,float yS)
{
    float theta;

        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
            for(int C=0;C<360;C++)
            {
                theta=C*3.14159265/180;
                glVertex2f(xS+60*cos(theta),yS+60*sin(theta));
            }
        glEnd();
}

void mouse(int button, int state, int mousex, int mousey)
{
    x = mousex;
    y = mousey;
    if((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) && (i == 0 || i == 2 || i == 4 || i == 6 || i == 8) && (clique) && menu == 2)
    {
        checkx=true;
        checko=false;
        if((x > 250 && x < 450 && y > 50 && y < 250) && caixaSelecionada[0] == 0)
        {
            caixaSelecionada[0]--;
            xS = 350;
            yS = 150;
        }
        else if((x > 450 && x < 650 && y > 50 && y < 250) && caixaSelecionada[1] == 0)
        {
            caixaSelecionada[1]--;
            xS = 550;
            yS = 150;
        }
        else if((x > 650 && x < 850 && y > 50 && y < 250) && caixaSelecionada[2] == 0)
        {
            caixaSelecionada[2]--;
            xS = 750;
            yS = 150;
        }
        else if((x > 250 && x < 450 && y > 250 && y < 450) && caixaSelecionada[3] == 0)
        {
            caixaSelecionada[3]--;
            xS = 350;
            yS = 350;
        }
        else if((x > 450 && x < 650 && y > 250 && y < 450) && caixaSelecionada[4] == 0)
        {
            caixaSelecionada[4]--;
            xS = 550;
            yS = 350;
        }
        else if((x > 650 && x < 850 && y > 250 && y < 450) && caixaSelecionada[5] == 0)
        {
            caixaSelecionada[5]--;
            xS = 750;
            yS = 350;
        }
        else if((x > 250 && x < 450 && y > 450 && y < 650) && caixaSelecionada[6] == 0)
        {
            caixaSelecionada[6]--;
            xS = 350;
            yS = 550;
        }
        else if((x > 450 && x < 650 && y > 450 && y < 650) && caixaSelecionada[7] == 0)
        {
            caixaSelecionada[7]--;
            xS = 550;
            yS = 550;
        }
        else if((x > 650 && x < 850 && y > 450 && y < 650) && caixaSelecionada[8] == 0)
        {
            caixaSelecionada[8]--;
            xS = 750;
            yS = 550;
        }
        else
        {
            checkx=false;
            checko=false;
        }
    }

    if((button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) && (i == 1 || i == 3 || i == 5 || i == 7) && (clique) && menu == 2)
    {
        checkx=false;
        checko=true;
        if((x > 250 && x < 450 && y > 50 && y < 250) && caixaSelecionada[0] == 0)
        {
            caixaSelecionada[0]++;
            xS = 350;
            yS = 150;
        }
        else if((x > 450 && x < 650 && y > 50 && y < 250) && caixaSelecionada[1] == 0)
        {
            caixaSelecionada[1]++;
            xS = 550;
            yS = 150;
        }
        else if((x > 650 && x < 850 && y > 50 && y < 250) && caixaSelecionada[2] == 0)
        {
            caixaSelecionada[2]++;
            xS = 750;
            yS = 150;
        }
        else if((x > 250 && x < 450 && y > 250 && y < 450) && caixaSelecionada[3] == 0)
        {
            caixaSelecionada[3]++;
            xS = 350;
            yS = 350;
        }
        else if((x > 450 && x < 650 && y > 250 && y < 450) && caixaSelecionada[4] == 0)
        {
            caixaSelecionada[4]++;
            xS = 550;
            yS = 350;
        }
        else if((x > 650 && x < 850 && y > 250 && y < 450) && caixaSelecionada[5] == 0)
        {
            caixaSelecionada[5]++;
            xS = 750;
            yS = 350;
        }
        else if((x > 250 && x < 450 && y > 450 && y < 650) && caixaSelecionada[6] == 0)
        {
            caixaSelecionada[6]++;
            xS = 350;
            yS = 550;
        }
        else if((x > 450 && x < 650 && y > 450 && y < 650) && caixaSelecionada[7] == 0)
        {
            caixaSelecionada[7]++;
            xS = 550;
            yS = 550;
        }
        else if((x > 650 && x < 850 && y > 450 && y < 650) && caixaSelecionada[8] == 0)
        {
            caixaSelecionada[8]++;
            xS = 750;
            yS = 550;
        }
        else
        {
            checkx=false;
            checko=false;
        }
    }
}


void pegatecla(unsigned char tecla, GLint x, GLint y)
{
    tecla = tolower(tecla);

    switch(tecla)
    {
        case 'r': desenhaTabuleiro();
            break;
        case 32: if(selecionar == 0)
                    menu = 2;
                 if(selecionar == 1)
                    menu = 1;
                 if(selecionar == 2)
                    exit(0);
            break;
        case 's': selecionar++;
                  if(selecionar == 3)
                     selecionar = 0;
            break;
        case 'w': selecionar--;
                  if(selecionar == -1)
                     selecionar = 2;
            break;
        case 27: menu = 0;
                 selecionar = 0;
                 desenhaTabuleiro();
    }
    glutPostRedisplay();
}

void desenhaTabuleiro()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);
    glColor3f(0.5,0.5,0.5);
    glLineWidth(10);
       glBegin(GL_LINES);
            glVertex2f(250,250);
            glVertex2f(850,250);

            glVertex2f(250,450);
            glVertex2f(850,450);

            glVertex2f(450,50);
            glVertex2f(450,650);

            glVertex2f(650,50);
            glVertex2f(650,650);
       glEnd();
    for (i = 0; i <=9; i++)
        caixaSelecionada[i]=0;
    i = 0;
    checkx=false;
    checko=false;
    clique = true;
    a = 0;
    selecionaCorLinha = 0;
    b = 0;
    glutPostRedisplay();
}

void desenhaTabuleiroInicial()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5,0.5,0.5);
    glLineWidth(10);
       glBegin(GL_LINES);
            glVertex2f(250,250);
            glVertex2f(850,250);

            glVertex2f(250,450);
            glVertex2f(850,450);

            glVertex2f(450,50);
            glVertex2f(450,650);

            glVertex2f(650,50);
            glVertex2f(650,650);
       glEnd();
    b = 1;
}

void timer(int valor)
{
    if(selecionaCorLinha > 0 && selecionaCorLinha < 9)
        glColor3f(0,1,0);
    if(selecionaCorLinha > 8 && selecionaCorLinha < 17)
        glColor3f(1,0,0);
    if(selecionaCorLinha == 1)
        ganhadorx++;
    if(selecionaCorLinha == 2)
        ganhadorx++;
    if(selecionaCorLinha == 3)
        ganhadorx++;
    if(selecionaCorLinha == 4)
        ganhadory++;
    if(selecionaCorLinha == 5)
        ganhadory++;
    if(selecionaCorLinha == 6)
        ganhadory++;
    if(selecionaCorLinha == 7)
    {
        ganhadorx++;
        ganhadory++;
    }
    if(selecionaCorLinha == 8)
    {
        ganhadorx--;
        ganhadory++;
    }
    if(selecionaCorLinha == 9)
        ganhadorx++;
    if(selecionaCorLinha == 10)
        ganhadorx++;
    if(selecionaCorLinha == 11)
        ganhadorx++;
    if(selecionaCorLinha == 12)
        ganhadory++;
    if(selecionaCorLinha == 13)
        ganhadory++;
    if(selecionaCorLinha == 14)
        ganhadory++;
    if(selecionaCorLinha == 15)
    {
        ganhadorx++;
        ganhadory++;
    }
    if(selecionaCorLinha == 16)
    {
        ganhadorx--;
        ganhadory++;
    }
    if(selecionaCorLinha == 0 && i > 8)
    {
        ganhadory = 0;
        ganhadorx = 0;
        i = 0;
        desenhaTelaFinal();
        Sleep(1500);
        clique = false;
        checkx=false;
        checko=false;
        animation=false;
        selecionaCorLinha=0;
    }
    if(ganhadory > 650 || ganhadorx > 850)
    {
        ganhadory = 0;
        ganhadorx = 0;
        i = 0;
        desenhaTelaFinal();
        Sleep(1500);
        clique = false;
        checkx=false;
        checko=false;
        animation=false;
        selecionaCorLinha=0;
    }
    glutPostRedisplay();
}

int checarGanhador (int g[])
{
    //HORIZONTAIS X
    if(g[0] == -1 && g[1] == -1 && g[2] == -1)
        return 1;
    if(g[3] == -1 && g[4] == -1 && g[5] == -1)
        return 2;
    if(g[6] == -1 && g[7] == -1 && g[8] == -1)
        return 3;
    if(g[0] == -1 && g[3] == -1 && g[6] == -1)
        return 4;
    if(g[1] == -1 && g[4] == -1 && g[7] == -1)
        return 5;
    if(g[2] == -1 && g[5] == -1 && g[8] == -1)
        return 6;
    if(g[0] == -1 && g[4] == -1 && g[8] == -1)
        return 7;
    if(g[2] == -1 && g[4] == -1 && g[6] == -1)
        return 8;
    if(g[0] == 1 && g[1] == 1 && g[2] == 1)
        return 9;
    if(g[3] == 1 && g[4] == 1 && g[5] == 1)
        return 10;
    if(g[6] == 1 && g[7] == 1 && g[8] == 1)
        return 11;
    if(g[0] == 1 && g[3] == 1 && g[6] == 1)
        return 12;
    if(g[1] == 1 && g[4] == 1 && g[7] == 1)
        return 13;
    if(g[2] == 1 && g[5] == 1 && g[8] == 1)
        return 14;
    if(g[0] == 1 && g[4] == 1 && g[8] == 1)
        return 15;
    if(g[2] == 1 && g[4] == 1 && g[6] == 1)
        return 16;
    else
        return 0;

}

void desenhaGanhador(int decidir)
{
    if(decidir == 1)
    {
        ganhadorx = 250;
        ganhadory = 150;
    }
    if(decidir == 2)
    {
        ganhadorx = 250;
        ganhadory = 350;
    }
    if(decidir == 3)
    {
        ganhadorx = 250;
        ganhadory = 550;
    }
    if(decidir == 4)
    {
        ganhadorx = 350;
        ganhadory = 50;
    }
    if(decidir == 5)
    {
        ganhadorx = 550;
        ganhadory = 50;
    }
    if(decidir == 6)
    {
        ganhadorx = 750;
        ganhadory = 50;
    }
    if(decidir == 7)
    {
        ganhadorx = 250;
        ganhadory = 50;
    }
    if(decidir == 8)
    {
        ganhadorx = 850;
        ganhadory = 50;
    }
    if(decidir == 9)
    {
        ganhadorx = 250;
        ganhadory = 150;
    }
    if(decidir == 10)
    {
        ganhadorx = 250;
        ganhadory = 350;
    }
    if(decidir == 11)
    {
        ganhadorx = 250;
        ganhadory = 550;
    }
    if(decidir == 12)
    {
        ganhadorx = 350;
        ganhadory = 50;
    }
    if(decidir == 13)
    {
        ganhadorx = 550;
        ganhadory = 50;
    }
    if(decidir == 14)
    {
        ganhadorx = 750;
        ganhadory = 50;
    }
    if(decidir == 15)
    {
        ganhadorx = 250;
        ganhadory = 50;
    }
    if(decidir == 16)
    {
        ganhadorx = 850;
        ganhadory = 50;
    }
    a = 1;
}

void desenhaVez()
{
    float theta;

    glLineWidth(5);

    glColor3f(0.8,0.8,0.8);
    glBegin(GL_QUADS);
        glVertex2f(25,225);
        glVertex2f(225,225);
        glVertex2f(225,275);
        glVertex2f(25,275);
    glEnd();

    glColor3f(0.187,0.125,0.125);
    glBegin(GL_QUADS);
        glVertex2f(25,275);
        glVertex2f(225,275);
        glVertex2f(225,475);
        glVertex2f(25,475);
    glEnd();

    if(i == 0 || i == 2 || i == 4 || i == 6 || i == 8)
    {
        glColor3f(0,1,0);
        glBegin(GL_LINES);
            glVertex2f(65,315);
            glVertex2f(185,435);

            glVertex2f(65,435);
            glVertex2f(185,315);
        glEnd();
    }

    if(i == 1 || i == 3 || i == 5 || i == 7)
    {
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
            for(int C=0;C<360;C++)
            {
                theta=C*3.14159265/180;
                glVertex2f(125+60*cos(theta),375+60*sin(theta));
            }
        glEnd();
    }
    escreve();
}

void escreve()
{
    glLineWidth(3);
    //R
    glColor3f(0.2,0.2,0.2);
        glBegin(GL_LINE_STRIP);
            glVertex2f(44,269);
            glVertex2f(44,230);
            glVertex2f(64,230);
            glVertex2f(64,249);
            glVertex2f(44,249);
            glVertex2f(64,269);
        glEnd();
    //O
    glBegin(GL_LINE_STRIP);
        glVertex2f(72,269);
        glVertex2f(72,230);
        glVertex2f(92,230);
        glVertex2f(92,269);
        glVertex2f(72,269);
    glEnd();
    //D
    glBegin(GL_LINE_STRIP);
        glVertex2f(100,269);
        glVertex2f(100,230);
        glVertex2f(112,230);
        glVertex2f(120,237);
        glVertex2f(120,262);
        glVertex2f(112,269);
        glVertex2f(100,269);
    glEnd();
    //A
    glBegin(GL_LINE_STRIP);
        glVertex2f(128,269);
        glVertex2f(128,230);
        glVertex2f(148,230);
        glVertex2f(148,269);
        glVertex2f(148,246);
        glVertex2f(128,246);
    glEnd();
    //D
    glBegin(GL_LINE_STRIP);
        glVertex2f(156,269);
        glVertex2f(156,230);
        glVertex2f(168,230);
        glVertex2f(176,237);
        glVertex2f(176,262);
        glVertex2f(168,269);
        glVertex2f(156,269);
    glEnd();
    //A
    glBegin(GL_LINE_STRIP);
        glVertex2f(184,269);
        glVertex2f(184,230);
        glVertex2f(204,230);
        glVertex2f(204,269);
        glVertex2f(204,246);
        glVertex2f(184,246);
    glEnd();
    desenvolvidoPor(695,695,1,"DEVELOPED BY: LUCAS");
}

void desenhaTelaFinal()
{
    float theta;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);

    glColor3f(0.377,0.377,0.377);
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(10);

    if(selecionaCorLinha > 0 && selecionaCorLinha < 9)
    {
        glColor3f(0,1,0);
        glBegin(GL_LINES);
            glVertex2f(350,130);
            glVertex2f(550,330);

            glVertex2f(350,330);
            glVertex2f(550,130);
        glEnd();
    }
    if(selecionaCorLinha > 8 && selecionaCorLinha < 17)
    {
        glColor3f(1,0,0);
        glBegin(GL_LINE_STRIP);
            for(int C=0; C<=360; C++)
            {
                theta=C*3.14159265/180;
                glVertex2f(450+100*cos(theta),230+100*sin(theta));
            }
        glEnd();
    }
    if(selecionaCorLinha == 0)
    {
        glColor3f(0,1,0);
        glBegin(GL_LINES);
            glVertex2f(250,130);
            glVertex2f(450,330);

            glVertex2f(250,330);
            glVertex2f(450,130);
        glEnd();

        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
            for(int C=0;C<360;C++)
            {
                theta=C*3.14159265/180;
                glVertex2f(550+100*cos(theta),230+100*sin(theta));
            }
            glEnd();

        glLineWidth(5);
        glColor3f(1,1,1);
        //D
        glBegin(GL_LINE_STRIP);
            glVertex2f(346,350);
            glVertex2f(346,430);
            glVertex2f(376,430);
            glVertex2f(386,420);
            glVertex2f(386,360);
            glVertex2f(376,350);
            glVertex2f(346,350);
        glEnd();
        //R
        glBegin(GL_LINE_STRIP);
            glVertex2f(402,430);
            glVertex2f(402,350);
            glVertex2f(442,350);
            glVertex2f(442,390);
            glVertex2f(402,390);
            glVertex2f(442,430);
        glEnd();
        //A
        glBegin(GL_LINE_STRIP);
            glVertex2f(458,430);
            glVertex2f(458,350);
            glVertex2f(498,350);
            glVertex2f(498,430);
            glVertex2f(498,380);
            glVertex2f(458,380);
        glEnd();
        //W
        glBegin(GL_LINE_STRIP);
            glVertex2f(514,350);
            glVertex2f(524,430);
            glVertex2f(534,390);
            glVertex2f(544,430);
            glVertex2f(554,350);
        glEnd();

    }

    if(selecionaCorLinha != 0)
    {
        glLineWidth(5);
        glColor3f(1,1,1);
        //W
        glBegin(GL_LINE_STRIP);
            glVertex2f(310,350);
            glVertex2f(320,430);
            glVertex2f(330,390);
            glVertex2f(340,430);
            glVertex2f(350,350);
        glEnd();
        //I
        glBegin(GL_LINE_STRIP);
            glVertex2f(366,350);
            glVertex2f(366,430);
        glEnd();
        //N
        glBegin(GL_LINE_STRIP);
            glVertex2f(382,430);
            glVertex2f(382,350);
            glVertex2f(424,430);
            glVertex2f(424,350);
        glEnd();
        //N
        glBegin(GL_LINE_STRIP);
            glVertex2f(440,430);
            glVertex2f(440,350);
            glVertex2f(480,430);
            glVertex2f(480,350);
        glEnd();
        //E
        glBegin(GL_LINES);
            glVertex2f(496,430);
            glVertex2f(496,350);

            glVertex2f(496,352);
            glVertex2f(536,352);

            glVertex2f(496,390);
            glVertex2f(526,390);

            glVertex2f(496,427);
            glVertex2f(536,427);
        glEnd();
        //r
        glBegin(GL_LINE_STRIP);
            glVertex2f(552,430);
            glVertex2f(552,350);
            glVertex2f(592,350);
            glVertex2f(592,390);
            glVertex2f(552,390);
            glVertex2f(592,430);
        glEnd();
    }

    //PRESS R TO RESTART
    glLineWidth(2);
    glColor3f(1,1,1);

    //P
    glBegin(GL_LINE_STRIP);
        glVertex2f(340,455);
        glVertex2f(340,440);
        glVertex2f(347,440);
        glVertex2f(347,447);
        glVertex2f(340,447);
    glEnd();
    //R
    glBegin(GL_LINE_STRIP);
        glVertex2f(352,455);
        glVertex2f(352,440);
        glVertex2f(359,440);
        glVertex2f(359,447);
        glVertex2f(352,447);
        glVertex2f(359,455);
    glEnd();
    //E
    glBegin(GL_LINES);
        glVertex2f(364,455);
        glVertex2f(364,440);

        glVertex2f(364,440);
        glVertex2f(371,440);

        glVertex2f(364,447);
        glVertex2f(369,447);

        glVertex2f(364,455);
        glVertex2f(371,455);
    glEnd();
    //S
    glBegin(GL_LINE_STRIP);
        glVertex2f(383,440);
        glVertex2f(376,440);
        glVertex2f(376,447);
        glVertex2f(383,447);
        glVertex2f(383,455);
        glVertex2f(376,455);
    glEnd();
    //S
    glBegin(GL_LINE_STRIP);
        glVertex2f(395,440);
        glVertex2f(388,440);
        glVertex2f(388,447);
        glVertex2f(395,447);
        glVertex2f(395,455);
        glVertex2f(388,455);
    glEnd();

    glColor3f(1,0,0);

    //R
    glBegin(GL_LINE_STRIP);
        glVertex2f(414,455);
        glVertex2f(414,440);
        glVertex2f(421,440);
        glVertex2f(421,447);
        glVertex2f(414,447);
        glVertex2f(421,455);
    glEnd();

    glColor3f(1,1,1);

    //T
    glBegin(GL_LINES);
        glVertex2f(439,440);
        glVertex2f(447,440);

        glVertex2f(443,440);
        glVertex2f(443,455);
    glEnd();
    //O
    glBegin(GL_LINE_LOOP);
        glVertex2f(452,455);
        glVertex2f(452,440);
        glVertex2f(459,440);
        glVertex2f(459,455);
    glEnd();
    //R
    glBegin(GL_LINE_STRIP);
        glVertex2f(478,455);
        glVertex2f(478,440);
        glVertex2f(485,440);
        glVertex2f(485,447);
        glVertex2f(478,447);
        glVertex2f(485,455);
    glEnd();
    //E
    glBegin(GL_LINES);
        glVertex2f(490,455);
        glVertex2f(490,440);

        glVertex2f(490,440);
        glVertex2f(497,440);

        glVertex2f(490,447);
        glVertex2f(495,447);

        glVertex2f(490,455);
        glVertex2f(497,455);
    glEnd();
    //S
    glBegin(GL_LINE_STRIP);
        glVertex2f(509,440);
        glVertex2f(502,440);
        glVertex2f(502,447);
        glVertex2f(509,447);
        glVertex2f(509,455);
        glVertex2f(502,455);
    glEnd();
    //T
    glBegin(GL_LINES);
        glVertex2f(514,440);
        glVertex2f(522,440);

        glVertex2f(518,440);
        glVertex2f(518,455);
    glEnd();
    //A
    glBegin(GL_LINE_STRIP);
        glVertex2f(527,455);
        glVertex2f(527,440);
        glVertex2f(534,440);
        glVertex2f(534,455);
        glVertex2f(534,447);
        glVertex2f(527,447);
    glEnd();
    //R
    glBegin(GL_LINE_STRIP);
        glVertex2f(539,455);
        glVertex2f(539,440);
        glVertex2f(546,440);
        glVertex2f(546,447);
        glVertex2f(539,447);
        glVertex2f(546,455);
    glEnd();
    //T
    glBegin(GL_LINES);
        glVertex2f(551,440);
        glVertex2f(559,440);

        glVertex2f(555,440);
        glVertex2f(555,455);
    glEnd();
    desenvolvidoPor(695,695,1,"DEVELOPED BY: LUCAS");
}

void desenhaMenu()
{
    //glColor3f(0.377,0.377,0.377);
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaXmenu(90,60,20);
    desenhaOmenu(150,300,60);
    desenhaXmenu(115,534,40);
    desenhaOmenu(390,115,90);
    desenhaXmenu(450,390,100);
    desenhaOmenu(200,150,20);
    desenhaXmenu(735,600,30);
    desenhaOmenu(650,320,50);
    desenhaXmenu(590,125,20);
    desenhaOmenu(400,700,200);
    desenhaXmenu(930,290,150);
    desenhaOmenu(850,75,30);
    desenhaXmenu(600,550,20);
    desenhaOmenu(900,525,30);

    glColor3f(0.150, 0.294, 0.403);
    glBegin(GL_QUADS);
            glVertex2f(200,198);
            glVertex2f(700,198);
            glVertex2f(700,253);
            glVertex2f(200,253);
    glEnd();

    glBegin(GL_QUADS);
            glVertex2f(200,323);
            glVertex2f(700,323);
            glVertex2f(700,378);
            glVertex2f(200,378);
    glEnd();

    glBegin(GL_QUADS);
            glVertex2f(200,445);
            glVertex2f(700,445);
            glVertex2f(700,500);
            glVertex2f(200,500);
    glEnd();

    glColor3f(1, 1, 1);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
            glVertex2f(195,193);
            glVertex2f(705,193);
            glVertex2f(705,258);
            glVertex2f(195,258);
    glEnd();

    glBegin(GL_LINE_LOOP);
            glVertex2f(195,318);
            glVertex2f(705,318);
            glVertex2f(705,383);
            glVertex2f(195,383);
    glEnd();

    glBegin(GL_LINE_LOOP);
            glVertex2f(195,440);
            glVertex2f(705,440);
            glVertex2f(705,505);
            glVertex2f(195,505);
    glEnd();

    //glColor3f(0.125, 0.269, 0.378);

    glColor3f(1, 1, 1);
    output(316,243,1,"INICIAR");
    output(212,368,1,"DESENVOLVEDOR");
    output(377,490,1,"SAIR");
    glColor3f(1, 0, 0);
    desenvolvidoPor(400,530,1,"W -> CIMA");
    desenvolvidoPor(395,550,1,"S -> BAIXO");
    desenvolvidoPor(340,570,1,"ESPACO -> SELECIONAR");
    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);

}

void output(int x, int y, int font, char *string)
{

    int len, i;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);
        glTranslatef(x,y,0);
        glRotatef(180,1,0,0);
        glScalef(0.35,0.35,0.35);
        glLineWidth(5);


    len = (int)strlen(string);

    for (i = 0; i < len; i++)
        {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, string[i]);
        }
}

void desenhaXmenu(float xS ,float  yS, float raio)
{
    glLineWidth(5);
    glColor3f(0.09375,0.453125,0.28125);
    glBegin(GL_LINES);
        glVertex2f(xS-raio,yS-raio);
        glVertex2f(xS+raio,yS+raio);

        glVertex2f(xS-raio,yS+raio);
        glVertex2f(xS+raio,yS-raio);
    glEnd();
}

void desenhaOmenu(float xS ,float yS, float raio)
{
    float theta;

    glLineWidth(5);
        glColor3f(0.34375,0.203125,0.28125);
        glBegin(GL_LINE_LOOP);
            for(int C=0;C<360;C++)
            {
                theta=C*3.14159265/180;
                glVertex2f(xS+raio*cos(theta),yS+raio*sin(theta));
            }
        glEnd();
}

void selecionado(int x1, int y1, int x2, int y2)
{
    //glColor3f(0.150, 0.294, 0.403);
    glColor3f(1,1,1);
    if(selecionar == 0)
    {
        glBegin(GL_QUADS);
            glVertex2f(200,198);
            glVertex2f(700,198);
            glVertex2f(700,253);
            glVertex2f(200,253);
        glEnd();
        //glColor3f(1,1,1);
        glColor3f(0.150, 0.294, 0.403);
        output(316,243,1,"INICIAR");
    }

    if(selecionar == 1)
    {
        glBegin(GL_QUADS);
            glVertex2f(200,323);
            glVertex2f(700,323);
            glVertex2f(700,378);
            glVertex2f(200,378);
        glEnd();
        //glColor3f(1,1,1);
        glColor3f(0.150, 0.294, 0.403);
        output(212,368,1,"DESENVOLVEDOR");
    }

    if(selecionar == 2)
    {
        glBegin(GL_QUADS);
            glVertex2f(200,445);
            glVertex2f(700,445);
            glVertex2f(700,500);
            glVertex2f(200,500);
        glEnd();
        //glColor3f(1,1,1);
        glColor3f(0.150, 0.294, 0.403);
        output(377,490,1,"SAIR");
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);
    glLineWidth(2);

    glColor3f(1,1,1);


    desenvolvidoPor(695,695,1,"DEVELOPED BY: LUCAS");
}

void paginaDesenvolvedor()
{
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaXmenu(90,60,20);
    desenhaOmenu(150,300,60);
    desenhaXmenu(115,534,40);
    desenhaOmenu(390,115,90);
    desenhaXmenu(450,390,100);
    desenhaOmenu(200,150,20);
    desenhaXmenu(735,600,30);
    desenhaOmenu(650,320,50);
    desenhaXmenu(590,125,20);
    desenhaOmenu(400,700,200);
    desenhaXmenu(930,290,150);
    desenhaOmenu(850,75,30);
    desenhaXmenu(600,550,20);
    desenhaOmenu(900,525,30);

    glColor3f(1,1,1);
    output(213,243,1,"LUCAS RAPHAEL");
    output(317,368,1,"19 ANOS");
    output(247,490,1,"2 - PERIODO");

    desenvolvidoPor(695,695,1,"DEVELOPED BY: LUCAS");
}

void desenvolvidoPor(int x, int y, int font, char *string)
{
    int len, i;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 900.0, 700.0, 0.0);
        glTranslatef(x,y,0);
        glRotatef(180,1,0,0);
        glScalef(0.1,0.1,0.1);
        glLineWidth(1);

    len = (int)strlen(string);

    for (i = 0; i < len; i++)
        {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, string[i]);
        }
}
