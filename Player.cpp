# 1 "Player.cpp"
# 1 "<command-line>"
# 1 "Player.cpp"
# 1 ".h" 1
       
class Player{
    public:
        Player(void);
        ~Player(void);
        float getX(void);
        float getY(void);
        float getW(void);
        float getH(void);

        void translate(float tx, float ty);
        void setWidth(float width);
        void setHeight(float height);
    private:
        float x, y;
        float w, h;
};
# 2 "Player.cpp" 2

Player::Player(void)
{
    w = 0.3f;
    h = 0.3f;
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

