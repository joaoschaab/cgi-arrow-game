#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "Player.h"
#include <vector>

using namespace std;

int WINDOW_WIDTH=1024, WINDOW_HEIGHT=800;
float translacaoX=0, translacaoY=0;
float lleft, rright, ttop, bbottom, panX, panY;

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

void desenhaCasinha() {

	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f,0.1f);
	glVertex2f(-0.2f,-0.2f);
	glVertex2f(0.2f,-0.2f);
	glVertex2f(0.2f,0.1f);
	glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(-0.2f,0.1f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f,0.22f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.2f,0.1f);
    glEnd();

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

	desenhaEixos();

	glPopMatrix();

	glLoadIdentity();

    glTranslatef(translacaoX,translacaoY,0);

    desenhaCasinha();

	// Define a cor de desenho: azul
	//glColor3f(1,0,1);

		// Desenha um triângulo no centro da janela
//	glBegin(GL_TRIANGLES);
//		glVertex3f(-0.5,-0.5,0);
//		glVertex3f( 0.0, 0.5,0);
//		glVertex3f( 0.5,-0.5,0);
//	glEnd();

	//Executa os comandos OpenGL
	glFlush();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
     if (key == 27)
		exit(0);
}

void TeclasEspecias(int key, int x, int y)
{

	 if(key == GLUT_KEY_LEFT)
		translacaoX=translacaoX-0.1;

     if(key == GLUT_KEY_RIGHT)
		translacaoX=translacaoX+0.1;

	 if(key == GLUT_KEY_UP)
	    translacaoY=translacaoY+0.1;

	 if(key == GLUT_KEY_DOWN)
		translacaoY=translacaoY-0.1;

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
	lleft=-1.0;
	rright=1.0;
	ttop=1.0;
	bbottom=-1.0;
	gluOrtho2D(lleft+panX,rright+panX,bbottom+panY,ttop+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{

    int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

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

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
