#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include "Player.h"
#include "PVector.h"
#include <vector>
#include <math.h>
#include <string.h>
#include <stdio.h>
using namespace std;

//float WINDOW_WIDTH=800.0f, WINDOW_HEIGHT=800.0f;
float WINDOW_WIDTH=1280.0f, WINDOW_HEIGHT=768.0f;

float lleft, rright, ttop, bbottom, panX, panY;

bool fired = true;

PVector *pi = NULL;
PVector *pf = NULL;
PVector *arrow = NULL;
float gravity;
float cx, cy, radius = 70;
const float PI_F=3.14159265358979f;
vector<Player> players;
int currentPlayer = 0;

float speedx;
float speedy;

char texto[30];

bool winner = false;

void draw_text(char *string){
    glPushMatrix();
        glColor3f(0,0,0);
        
        glRasterPos2f(lleft + (rright-lleft)/2-50, ttop + bbottom/2); 
        while(*string){
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++); 
        }
	glPopMatrix();

}
void draw_circle(float x, float y, float r){
    cx = x;
    cy = y;
    bool filled = false;
    int subdivs = 100;
    glPushMatrix();
        if(currentPlayer == 0) glColor3f(0,0,0);
        else glColor3f(0,0,1);
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

void draw_floor(){
    glPushMatrix();
        glLineWidth(3);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
            glVertex2f(-5000,  WINDOW_HEIGHT);
            glVertex2f(5000, WINDOW_HEIGHT);
        glEnd();
    glPopMatrix();
}

void draw_player(float w, float h, int player) {
    glPushMatrix();
        glLineWidth(3);
        if(player == 0) glColor3f(0,0,0);
        else glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(w   , 0.0f);
            glVertex2f(w   , h   );
            glVertex2f(0.0f, h   );
        glEnd();
    glPopMatrix();

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

void updateCameraPlayer(){
    lleft = players[currentPlayer].getX() - WINDOW_WIDTH/2 + players[currentPlayer].getW()/2;
    rright = lleft + WINDOW_WIDTH;
    ttop = 0;
    bbottom = WINDOW_HEIGHT;
}

void updateCameraArrow(){
    lleft += speedx;// arrow->getX() - WINDOW_WIDTH/2 + arrow->getSizeX()/2;
    rright = rright + speedx;
    ttop +=speedy ; //arrow->getY() - WINDOW_HEIGHT/2 + arrow->getSizeY()/2;
    bbottom = bbottom+ speedy;
}
bool inside(float x, float y, float w, float h){
    float xx = arrow->getX();
    float yy = arrow->getY();
    float px = arrow->getX() + xx;
    float py = arrow->getY() + yy;
    if(px >= x && px <= (x+w) && py >= y && py <= (y+h))
        return true;
    if(xx >= x && xx <= (x+w) && yy >= y && yy <= (y+h))
        return true;
    return false;
}
bool checkPlayerCollision(){
    int p;
    if(currentPlayer == 0) p = 1;
    else p = 0;
    float x = players[p].getX();
    float y = players[p].getY();
    float w = players[p].getW();
    float h = players[p].getH();
    return inside(x, y, w, h);
}
bool checkWallCollision(){
    float x = arrow->getX() + arrow->getSizeX();
    float y = arrow->getY() + arrow->getSizeY();
    return y >= WINDOW_HEIGHT;
}
void swap_current_player(){
    if(currentPlayer == 1) currentPlayer = 0;
    else currentPlayer = 1;
    updateCameraPlayer();
}
void Timer(int value){
    if(arrow != NULL && fired){
        arrow->addSum(speedx, speedy);    
		float x = arrow->getSizeX();
		float y = arrow->getSizeY();

		arrow->rotate(arrow->getAngle(x+speedx, y+speedy));
		speedy += gravity;

        if(checkWallCollision()){
            swap_current_player();
            arrow = NULL;
        }else if(checkPlayerCollision()){
            arrow = NULL;
            updateCameraPlayer();
            sprintf(texto, "Player (%d) ganhou!", currentPlayer+1);
            draw_text(texto);
            winner = true;
        }else{
            updateCameraArrow();
        }
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

	// Limpa a janela de visualização com a cor preta 
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
    for(int i =0; i < players.size(); i++){
        glPushMatrix();
            glTranslatef(players[i].getX(), players[i].getY(), 0.0f);
            draw_player(players[i].getW(), players[i].getH(), i);
        glPopMatrix();
    }

    draw_floor();

    // desenha o vetor quando clika
    if(pi != NULL && pf != NULL){
        float width = rright - lleft;
        float height = ttop - bbottom;
        draw_vector(lleft + pi->getSizeX(), ttop + pi->getSizeY(), lleft + pf->getSizeX(), ttop + pf->getSizeY());
    }
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
    if(winner == true)
        draw_text(texto);
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
		speedx = arrow->getSizeX() / 5;
		speedy = arrow->getSizeY() / 5;
        pi = NULL;
        pf = NULL;
        gravity = 0.3;
        fired = !fired;
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
        swap_current_player();
    }

	if(key == GLUT_KEY_HOME){
        winner = false;
        updateCameraPlayer();
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
	rright=WINDOW_WIDTH;
	ttop=0.0;
	bbottom=WINDOW_HEIGHT;
    updateCameraPlayer(); 
	gluOrtho2D(lleft+panX,rright+panX,bbottom+panY,ttop+panY);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(void)
{

    int argc = 0;
	char *argv[] = { (char *)"gl", 0 };

    Player p1(-WINDOW_WIDTH, WINDOW_HEIGHT);
    Player p2(WINDOW_WIDTH, WINDOW_HEIGHT);

    p1.translate(0.0f, -p1.getH()-radius/2);
    p2.translate(-p2.getW(), -p2.getH()-radius/2);

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
	glutDisplayFunc(Draw);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais 
	glutSpecialFunc (TeclasEspecias);
    
    // Registra a função callback para drag de mouse
    glutMotionFunc(mouse_drag);

    // Registra a função callback para click de mouse
    glutMouseFunc(mouse_click);

    glutTimerFunc(33, Timer, 1);

	// Chama a função responsável por fazer as inicializações
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();


	return 0;
}
