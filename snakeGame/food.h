#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>

class Food {
public:
    Food();
    ~Food();
    SDL_Rect position;
    void spawn();
    void render(SDL_Renderer* renderer);
private:
    SDL_Renderer* renderer;
    int blockSize = 20;
};