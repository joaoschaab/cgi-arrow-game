#include "Player.h"       

Player::Player(float posx, float posy)
{
    x = posx;
    y = posy;
    w = 0.1f;
    h = 0.1f;
}


Player::~Player(void)
{
}

float Player::getX() { return x; }
float Player::getY() { return y; }
float Player::getW() { return w; }
float Player::getH() { return h; }

void Player::translate(float tx, float ty){
    x += tx;
    y += ty;
}

void Player::setWidth(float width){
    w = width;
}

void Player::setHeight(float height){
    h = height;
}

