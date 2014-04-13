#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "PVector.h"
#include <vector>
using namespace std;

float WINDOW_WIDTH=800.0f, WINDOW_HEIGHT=800.0f;
//float WINDOW_WIDTH=1280.0f, WINDOW_HEIGHT=1024.0f;

float lleft, rright, ttop, bbottom, panX, panY;


PVector *pi = NULL;
PVector *pf = NULL;

vector<Player> players;
int currentPlayer = 0;

void desenhaEixos() {

	glColor3f(1,1,1);

	glLineWidth(1);
	glBegin(GL_LINES);

    glVertex2f(lleft,0.0);
	glVertex2f(rright, 0.0);
	glVertex2f(0.0,bbottom);
	glVertex2f(0.0,ttop);

	glEnd();

}

void drawPlayer(float w, float h) {

	glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(w   , 0.0f);
        glVertex2f(w   , h   );
        glVertex2f(0.0f, h   );
	glEnd();

}

void draw_vector(float x, float y){
    glPushMatrix();
        glBegin(GL_LINES);
            glVertex2f(x/WINDOW_WIDTH         , 1 - y/WINDOW_HEIGHT         );
            glVertex2f(pi->getX()/WINDOW_WIDTH, 1 - pi->getY()/WINDOW_HEIGHT);
        glEnd();
    glPopMatrix();
}

void Desenha(void)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (lleft+panX, rright+panX, bbottom+panY, ttop+panY);
    glMatrixMode(GL_MODELVIEW);

	// Limpa a janela de visualização com a cor branca
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	glLoadIdentity();

	//desenhaEixos();

	glPopMatrix();

    for(int i =0; i < players.size(); i++){
        glPushMatrix();
            glTranslatef(players[i].getX(), players[i].getY(), 0.0f);
            drawPlayer(players[i].getW(), players[i].getH());
        glPopMatrix();
    }

    if(pi != NULL)
        draw_vector(pf->getX(), pf->getY());

	//Executa os comandos OpenGL
	glFlush();
}


void mouse_drag (int x, int y){
    pf = new PVector(x, y);
	glutPostRedisplay();
}

void mouse_click(int button, int state, int x, int y){
    if(state == 0){ // clickou
        pi = new PVector(x, y);
    }else if(state == 1){ // soltou o click
        pi = NULL;
        glutPostRedisplay();
    }
}


// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
     if (key == 27)
		exit(0);
}

void TeclasEspecias(int key, int x, int y)
{

	if(key == GLUT_KEY_LEFT){
       players[currentPlayer].translate(-(10/WINDOW_WIDTH), 0.0f);
    }

    if(key == GLUT_KEY_RIGHT){
       players[currentPlayer].translate(10/WINDOW_WIDTH, 0.0f);
    }
	if(key == GLUT_KEY_UP){
       players[currentPlayer].translate(0.0f, 10/WINDOW_HEIGHT);
    }
	if(key == GLUT_KEY_DOWN){
       players[currentPlayer].translate(0.0f, -(10/WINDOW_HEIGHT));
    }
    if(key == GLUT_KEY_END){
	    lleft-=0.1;
        rright+=0.1;
        ttop+=0.1;
        bbottom-=0.1;
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


// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	lleft=0.0;
	rright=1.0;
	ttop=1.0;
	bbottom=-0.0;
	gluOrtho2D(lleft+panX,rright+panX,bbottom+panY,ttop+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{

    int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

    Player p1(0.0f, 0.0f);
    Player p2(1.0f, 0.0f);

    p2.translate(-p2.getW(), 0.0f);

    players.push_back(p1);
    players.push_back(p2);

	glutInit(&argc,argv);

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("MEU GAME!");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	glutSpecialFunc (TeclasEspecias);
    
    // Registra a função callback para drag de mouse
    glutMotionFunc(mouse_drag);

    // Registra a função callback para click de mouse
    glutMouseFunc(mouse_click);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
