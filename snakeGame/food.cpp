#include "food.h"
#include <cstdlib>  // For rand() function
#include <ctime>    // For time() function

Food::Food() {
    // Initialize the position of the food
    spawn();
}

Food::~Food() {
}

void Food::spawn() {
    // Use the current time as the seed for the random number generator
    std::srand(static_cast<unsigned>(std::time(0)));

    // Set the position of the food to a randomly generated rectangle
    position.x = (rand() % (800 / blockSize)) * blockSize;  // 800 is the window width, blockSize is the size of each block
    position.y = (rand() % (600 / blockSize)) * blockSize;  // 600 is the window height, blockSize is the size of each block
    position.w = blockSize;
    position.h = blockSize;
}

void Food::render(SDL_Renderer* renderer) {
    // Render the food on the SDL window
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color to red
    SDL_RenderFillRect(renderer, &position);
}
