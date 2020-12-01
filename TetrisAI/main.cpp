#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define GAME_MODE 1
#ifdef GAME_MODE
#include"tetris.h"
using namespace Tetris;
#else
#include"test.h"
using namespace test;
#endif

#ifdef AI_MODE
#include"tetrisAI.h"
#endif




#ifdef GAME_MODE
class Game {
public:
	Game();
	Block getBlock();
	Background getBackground();
	void init(int randVal);
	void setLevel(int level);
	void setSpeed(float speed);
	void addScore(int score);
	int getLevel();
	float getSpeed();

#endif //GAME_MODE
#ifdef AI_MODE
	void run(int data[]);
#elif GAME_MODE 1
	void run();
#endif //AI_MODE

#ifdef GAME_MODE 1
private:
	int level = 1;
	int score = 0;
	float speed = 500.0f;
	Block bk = Block(0, 0, 0);
	Background bg = Background(X_LENGTH * 4, 2);
};

Game::Game() {}
Block Game::getBlock() {
	return this->bk;
}
Background Game::getBackground() {
	return this->bg;
}
void Game::init(int randVal) {
	this->bg = Background(X_LENGTH * 4, 2);
	this->bk = Block(randVal, X_LENGTH * 8, 3);

	this->bk.setBG(this->bg.getBackground());
	this->bk.setBGPoint(this->bg.getPoint());

}
#endif //GAME_MODE


#ifdef AI_MODE
void Game::run(int data[]) {
	int randVal = 0;

	this->bk.move(data, this->bg.getBackground());
	if (this->bk.getArrivalFlags()) {
		srand(time(NULL));
		randVal = rand() % 5;
		this->bk.setArrivalFlags(false);
		this->bk.setBlock(randVal, X_LENGTH * 8, 3);
		this->bg.fillOneLineCheck();
		this->addScore(4);
	}

	this->bk.down(this->bg.getBackground());
	this->bk.setSpeed(this->speed - ((this->speed * this->level) / 10));
}
#elif GAME_MODE 1
void Game::run() {
	int randVal = 0;
	if (_kbhit()) {
		this->bk.move(this->bg.getBackground());
	}
	if (this->bk.getArrivalFlags()) {
		srand(time(NULL));
		randVal = rand() % 5;
		this->bk.setArrivalFlags(false);
		this->bk.setBlock(randVal, X_LENGTH * 8, 3);
		this->bg.fillOneLineCheck();
		this->addScore(4);
	}
	
	this->bk.down(this->bg.getBackground());
	this->bk.setSpeed(this->speed - ((this->speed * this->level)/10));
}
#endif 

#ifdef GAME_MODE 1
int Game::getLevel() {
	return this->level;
}
float Game::getSpeed() {
	return this->speed;
}
void Game::setLevel(int level) {
	this->level = level;
}
void Game::addScore(int score) {
	this->score += score;
	if (this->score % 52 == 0) this->level++;
	gotoxy(40, 4);
	std::cout << this->level;
	gotoxy(40, 5);
	std::cout << this->score;
}
void Game::setSpeed(float speed) {
	this->speed = speed;
}
void tetris() {
	int getNum = 0;
	int randVal=0;
	Game g = Game();

	srand(time(NULL));
	randVal = rand() % 4;
	g.init(randVal);
	
	for (;;) {
		g.getBackground().draw();
		g.getBlock().draw();
#endif //GAME_MODE


#ifdef AI_MODE
        g.run(data);
#elif GAME_MODE 1
		g.run();

	}
}
#endif


#ifdef GAME_MODE
#else
class Game {
public:
	Game();
	Block getBlock();
	Background getBackground();

	void init(int randVal);
	void run();

	void setLevel(int level);
	void setSpeed(float speed);
	int getLevel();
	float getSpeed();

private:
	int level = 1;
	float speed = 200.0f;
	Block bk=Block(0,0,0);
	Background bg = Background(0, 0);
};
Game::Game() {}
Block Game::getBlock() {
	return this->bk;
}
Background Game::getBackground() {
	return this->bg;
}
void Game::init(int randVal) {
	this->bg = Background(X_LENGTH * 4, 2);
	this->bk = Block(randVal, X_LENGTH * 6, 3);
	
	this->bk.setBG(this->bg.getBackground());
	this->bk.setBGPoint(this->bg.getPoint());
	
}
void Game::run() {
	if (_kbhit()) {
		for (int i = 0; i < 2; i++) {
			this->bk.move(this->bg.getBackground());
		}
	}
	this->bk.down(this->bg.getBackground());
	this->bk.setSpeed(this->speed);
}

void Test() {
	Game g=Game();

	int randVal = 1;
	g.init(randVal);


	g.getBackground().draw();
	g.getBlock().draw();
	
	
	for (;;) {
		g.run();
		g.getBackground().draw();
		g.getBlock().draw();
		Sleep(10);
	}



	gotoxy(80, 27);
}

#endif

int main(void) {

#ifdef GAME_MODE
	tetris();
#else
	Test();
#endif


	return 0;
}
