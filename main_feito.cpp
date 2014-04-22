#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "PVector.h"
#include <vector>
#include <math.h>
using namespace std;

//float WINDOW_WIDTH=800.0f, WINDOW_HEIGHT=800.0f;
float WINDOW_WIDTH=768.0f, WINDOW_HEIGHT=768.0f;

float lleft, rright, ttop, bbottom, panX, panY;

bool fired = true;

PVector *pi = NULL;
PVector *pf = NULL;
PVector *arrow = NULL;
float gravity = 1;
float cx, cy, radius = 100;
const float PI_F=3.14159265358979f;
vector<Player> players;
int currentPlayer = 0;


void draw_circle(float x, float y, float r){
    cx = x;
    cy = y;
    bool filled = false;
    int subdivs = 100;
    glPushMatrix();
        glLineWidth(3);
        if(filled){
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y);
        }else{
             glBegin(GL_LINE_STRIP);
        }
        for(int i = 0; i <= subdivs; i++){
            float angle = i * ((2.0f * PI_F) / subdivs);
            glVertex2f(x + r*cos(angle), y + r*sin(angle));
        }
        glEnd();
    glPopMatrix();
}

void draw_player(float w, float h) {

	glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(w   , 0.0f);
        glVertex2f(w   , h   );
        glVertex2f(0.0f, h   );
	glEnd();

}

void draw_vector(float x, float y, float xf, float yf){
    glPushMatrix();
	glLineWidth(2);
        glBegin(GL_LINES);
            glVertex2f(x,  y);
            glVertex2f(xf, yf);
        glEnd();
    glPopMatrix();
}

void Timer(int value){
    if(arrow != NULL && fired){
        arrow->addSum(arrow->getSizeX()/10, arrow->getSizeY()/10);    
        arrow->addSum(0, gravity);
        gravity+=0.1;
//        arrow->addSum(0, gravity);
    }
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 1);
}
void Draw(void)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (lleft+panX, rright+panX, bbottom+panY, ttop+panY);
    glMatrixMode(GL_MODELVIEW);

	// Limpa a janela de visualiza��o com a cor preta 
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	// Define a cor de desenho: azul
	glColor3f(0,0,0);
    for(int i =0; i < players.size(); i++){
        glPushMatrix();
            glTranslatef(players[i].getX(), players[i].getY(), 0.0f);
            draw_player(players[i].getW(), players[i].getH());
        glPopMatrix();
    }
    // desenha o vetor quando clika
    if(pi != NULL && pf != NULL)
        draw_vector(pi->getSizeX(), pi->getSizeY(), pf->getSizeX(), pf->getSizeY());

    float centerx = players[currentPlayer].getX() + players[currentPlayer].getW()/2;
    float centery = players[currentPlayer].getY() + players[currentPlayer].getH()/2;
    // desenha o circulo da mira    
    draw_circle(centerx, centery, radius);


    if(arrow != NULL && !fired){
        centerx = centerx + arrow->getUnitarioX() * radius;
        centery = centery + arrow->getUnitarioY() * radius;

        draw_vector(centerx, centery, centerx + arrow->getSizeX(), centery + arrow->getSizeY());

        arrow->setXY(centerx, centery);
    }else if(arrow != NULL){
		draw_vector(arrow->getX(), arrow->getY(), arrow->getX() + arrow->getSizeX(), arrow->getY()+ arrow->getSizeY());
    }
	glFlush();
}



void mouse_drag (int x, int y){
    pf = new PVector(x, y);
    arrow->setSizeXY(pi->getSizeX() - pf->getSizeX(), pi->getSizeY() - pf->getSizeY());
    glutPostRedisplay();
}

void mouse_click(int button, int state, int x, int y){
    if(state == 0){ // clickou
        arrow = new PVector(x, y);
        pi = new PVector(x, y);
        fired = !fired;
    }else if(state == 1){ // soltou o click
        if(pf != NULL)
            arrow->setSizeXY(pi->getSizeX() - pf->getSizeX(), pi->getSizeY() - pf->getSizeY());
        fired = !fired;
        pi = NULL;
        pf = NULL;
        gravity = 1;
        //glutPostRedisplay();
    }
}


// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
     if (key == 27)
		exit(0);
}

void TeclasEspecias(int key, int x, int y)
{

	if(key == GLUT_KEY_LEFT){
       players[currentPlayer].translate(-10.0f, 0.0f);
    }
    if(key == GLUT_KEY_RIGHT){
       players[currentPlayer].translate(10.0f, 0.0f);
    }
	if(key == GLUT_KEY_UP){
       players[currentPlayer].translate(0.0f, -10.0f);
    }
	if(key == GLUT_KEY_DOWN){
       players[currentPlayer].translate(0.0f, 10.0f);
    }
    if(key == GLUT_KEY_END){
	    //lleft-=0.1;
        //rright+=0.1;
        //ttop+=0.1;
        //bbottom-=0.1;
    }

	if(key == GLUT_KEY_HOME){
        lleft+=0.1;
        rright-=0.1;
        ttop-=0.1;
        bbottom+=0.1;
	}

	if(key == GLUT_KEY_F9)
       panX+=0.1;
    if(key == GLUT_KEY_F10)
       panX-=0.1;
    if(key == GLUT_KEY_F11)
       panY+=0.1;
    if(key == GLUT_KEY_F12)
       panY-=0.1;

	glutPostRedisplay();
}


// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	lleft=0.0;
	rright=WINDOW_WIDTH;
	ttop=0.0;
	bbottom=WINDOW_HEIGHT;
	gluOrtho2D(lleft+panX,rright+panX,bbottom+panY,ttop+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{

    int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

    Player p1(0.0f, WINDOW_HEIGHT);
    Player p2(WINDOW_WIDTH, WINDOW_HEIGHT);

    p1.translate(0.0f, -p1.getH());
    p2.translate(-p2.getW(), -p2.getH());

    players.push_back(p1);
    players.push_back(p2);

	glutInit(&argc,argv);

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("MEU GAME!");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Draw);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a fun��o callback para tratamento das teclas especiais 
	glutSpecialFunc (TeclasEspecias);
    
    // Registra a fun��o callback para drag de mouse
    glutMotionFunc(mouse_drag);

    // Registra a fun��o callback para click de mouse
    glutMouseFunc(mouse_click);

    glutTimerFunc(33, Timer, 1);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();


	return 0;
}
