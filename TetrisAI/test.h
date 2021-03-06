#ifndef TEST_H
#define TEST_H

#include<Windows.h>
#include<iostream>
#include<conio.h>


namespace Test {
    void gotoxy(int x, int y) {
        COORD Pos;
        Pos.X = x;
        Pos.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
    }
    typedef struct Point {
        int x;
        int y;
    }Point;
    typedef struct BlockState {
        int randNo;
        int block[4][4];
    }BlockState;

    const int X_LENGTH = 2;
    const int BLOCK_SIZE_X = 4;
    const int BLOCK_SIZE_Y = 4;
    const int BG_SIZE_X = 10;
    const int BG_SIZE_Y = 20;
    const int UP = 72;
    const int DOWN = 80;
    const int LEFT = 75;
    const int RIGHT = 77;
    const int ENTER = 13;
    const int SPACE = 32;

    class Block {
    public:
        int blocks[5][BLOCK_SIZE_Y][BLOCK_SIZE_X] = {
            {   {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,0}
            },
            {   {0,0,0,0},
                {0,0,1,0},
                {0,1,1,1},
                {0,0,0,0}
            },
            {   {0,1,0,0},
                {0,1,0,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {   {0,0,1,0},
                {0,0,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {   {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        };

        Block(int randBlock, int x, int y);
        void setPoint(int x, int y);
        void setSpeed(float speed);
        Point getPoint();
        void turn(bool reverse);

        void draw();
        void down(void* background);
        void move(void* background);
        bool collision(void* block, void* background);
        bool arrival(void* block, void* background);
        void setBGPoint(Point point);
        void setBG(void* bg);
        void* getBlock(int randVal);
    private:
        bool reverseFlags = false;
        void* bg;
        Point bgPoint;
        Point point;
        BlockState state;
        float speed = 0.0f;
    };
    Block::Block(int randBlock, int x, int y) {
        this->setPoint(x, y);
        this->state.randNo = randBlock;

        for (int i = 0; i < BLOCK_SIZE_Y; i++)
            for (int j = 0; j < BLOCK_SIZE_X; j++)
                this->state.block[i][j] = this->blocks[randBlock][i][j];

    }
    void* Block::getBlock(int randVal) {
        return this->blocks[randVal];
    }
    void Block::setPoint(int x, int y) {
        this->point.x = (int)(x / 2) * 2;
        this->point.y = y;
    }
    void Block::setSpeed(float speed) {
        this->speed = speed;
    }
    void Block::turn(bool reverse) {
        int block[BLOCK_SIZE_Y][BLOCK_SIZE_X] = {};
        for (int i = 0; i < BLOCK_SIZE_Y; i++) {
            for (int j = 0; j < BLOCK_SIZE_X; j++) {
                if (reverse == false)  block[i][j] = this->state.block[3 - j][i];
                else block[i][j] = this->state.block[j][3 - i];
            }
        }
        for (int i = 0; i < BLOCK_SIZE_Y; i++)
            for (int j = 0; j < BLOCK_SIZE_Y; j++)
                this->state.block[i][j] = block[i][j];
    }

    Point Block::getPoint() {
        return this->point;
    }
    void Block::draw() {

        int locationX = this->point.x;
        int locationY = this->point.y;
        for (int i = 0; i < BLOCK_SIZE_Y; i++) {
            for (int j = 0; j < BLOCK_SIZE_X; j++) {
                gotoxy(locationX + (j * X_LENGTH), locationY + i);
                if (this->state.block[i][j] == 1) std::cout << "��";
            }
            std::cout << "\n";
        }
    }
    void Block::down(void* background) {
        this->setPoint(this->getPoint().x, this->getPoint().y + 1);
        if (collision(this->state.block, background)) {
            this->setPoint(this->getPoint().x, this->getPoint().y - 1);
        }

        Sleep(speed);
        //this->setSpeed(speed);
    }
    void Block::move(void* background) {
        int x = this->getPoint().x, y = this->getPoint().y;
        int saveX = x, saveY = y;
        int key = _getch();
        switch (key) {
        case LEFT:
            this->point.x = this->point.x - X_LENGTH;//X_LENGTH;
            break;
        case RIGHT:
            this->point.x = this->point.x + X_LENGTH;//X_LENGTH;
            break;
        case DOWN:
            this->point.y = this->point.y + 1;
            break;
        case SPACE:

            while (!this->arrival(this->state.block, background)) {
                this->down(background);

            }
            this->draw();


            break;
        case UP:
            this->turn(false);
            if (collision(this->state.block, background)) {
                this->turn(true);
            }
            break;
        case 'Q':
        case 'q':
            exit(0);
            break;
        default:
            break;
        }

        if (collision(this->state.block, background)) {
            this->point.x = saveX;
            this->point.y = saveY;
        }



        this->setPoint(this->point.x, this->point.y);
    }
    bool Block::collision(void* block, void* background) {
        int(*bk)[BLOCK_SIZE_X] = (int(*)[BLOCK_SIZE_X])block;
        int(*bg)[BG_SIZE_X] = (int(*)[BG_SIZE_X])background;

        for (int i = 0; i < BLOCK_SIZE_Y; i++)
            for (int j = 0; j < BLOCK_SIZE_X; j++)
                if (bk[i][j] == 1 && bg[this->getPoint().y - this->bgPoint.y + i][(int)(this->getPoint().x - this->bgPoint.x) / 2 + j] == 2) return true;

        return false;
    }
    bool Block::arrival(void* block, void* background) {
        int(*bk)[BLOCK_SIZE_X] = (int(*)[BLOCK_SIZE_X])block;
        int(*bg)[BG_SIZE_X] = (int(*)[BG_SIZE_X])background;

        for (int i = 0; i < BG_SIZE_Y; i++) {
            for (int j = 0; j < BG_SIZE_X; j++) {
                bg[0][j] = 3;
                bg[i][0] = 3;
                bg[i][BG_SIZE_X - 1] = 3;
            }
        }
        for (int i = 0; i < BLOCK_SIZE_Y; i++) {
            for (int j = 0; j < BLOCK_SIZE_X; j++) {
                if (bk[i][j] == 1 && bg[this->getPoint().y - this->bgPoint.y + i + 1][(int)(this->getPoint().x - this->bgPoint.x) / 2 + j] == 2) {
                    //bg[this->getPoint().y - this->bgPoint.y + i][(int)(this->getPoint().x - this->bgPoint.x) / 2 + j];
                    return true;
                }
            }
        }
        return false;
    }

    void Block::setBG(void* bg) {
        this->bg = bg;
    }
    void Block::setBGPoint(Point point) {
        this->bgPoint = point;
    }

    class Background {
    public:
        int background[BG_SIZE_Y][BG_SIZE_X] = {
            {2,2,2,2,2,2,2,2,2,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,0,0,0,0,0,0,0,0,2},
            {2,2,2,2,2,2,2,2,2,2}
        };

        Point getPoint();
        Background(int x, int y);
        void draw();
        void* getBackground();
    private:
        Point point;
    };
    Background::Background(int x, int y) {
        this->point.x = (x >> 1) << 1;
        this->point.y = y;
    }
    Point Background::getPoint() {
        return this->point;
    }
    void* Background::getBackground() {
        return this->background;
    }
    void Background::draw() {
        gotoxy(70, 10);
        std::cout << "Tetris AI" << "\n";
        gotoxy(70, 11);
        std::cout << "@author  : Lee sang min" << "\n";
        gotoxy(70, 12);
        std::cout << "@version : 0.0 �̿ϼ�" << "\n";
        for (int i = 0; i < BG_SIZE_Y; i++) {
            for (int j = 0; j < BG_SIZE_X; j++) {
                gotoxy(this->point.x + j * X_LENGTH, this->point.y + i);
                if (this->background[i][j] == 2) std::cout << "��";
                else std::cout << "  ";
            }
        }
    }

} //test
#endif