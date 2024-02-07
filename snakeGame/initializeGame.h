#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "food.h"
#include "Snake.h"

class Game {
public :
	//Game();
	~Game();
	void  initialize();
	void gameLoop(); 
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Snake snake;
	Food food;
	int blocksize = 20;
	const int WIDTH = 800;
	const int HEIGHT = 600;

	bool checkSelfCollision(deque<SDL_Rect> body);
	bool checkFoodCollision(SDL_Rect food, SDL_Rect body);
	void checkBoardCollision(deque<SDL_Rect> &body);
};