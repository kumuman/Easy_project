#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <deque>
using namespace std;

enum Direction {
	UP='w',
	DOWN = 's',
	LEFT = 'a',
	RIGHT = 'd'
};
class Snake {
public:
	Snake();
	~Snake();
	deque<SDL_Rect> body; 
	void move();
	void render(SDL_Renderer* renderer);
	void handleInput(SDL_Event& event);
	void getDetails();
	void grow();
private:
	SDL_Renderer* renderer;
	int blockSize = 20;
	char direction = 'f';
};
