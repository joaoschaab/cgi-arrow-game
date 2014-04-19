#include "Player.h"       
#include "PVector.h"
Player::Player(float posx, float posy)
{
    p = new PVector(1, 1);
    p->addSum(posx, posy);
    w = 100.0f;
    h = 100.0f;
}


Player::~Player(void)
{
}

float Player::getX() { return p->getX(); }
float Player::getY() { return p->getY(); }
float Player::getW() { return w; }
float Player::getH() { return h; }

void Player::translate(float tx, float ty){
    p->addSum(tx, ty);
}

void Player::setWidth(float width){
    w = width;
}

void Player::setHeight(float height){
    h = height;
}

