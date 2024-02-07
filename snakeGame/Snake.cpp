#include "Snake.h"
#include <iostream>
using namespace std;

// Constructor: Initialize the snake's starting position and body
Snake::Snake() {
    body.push_back({ 0, 0, blockSize, blockSize });
}

// Destructor
Snake::~Snake() {
}

void Snake::move() {
    SDL_Rect head = body.front();
    cout << "moving" <<endl;
    // Update the position of the snake's head based on the current direction
    switch (direction) {
    case UP:
        head.y -= blockSize;
        break;
    case DOWN:
        head.y += blockSize;
        break;
    case LEFT:
        head.x -= blockSize;
        break;
    case RIGHT:
        head.x += blockSize;
        break;
    }
    // Add a new head and remove the tail
    body.push_front({ head.x, head.y, blockSize, blockSize });
    body.pop_back();
}

// Render the snake on the SDL window
void Snake::render(SDL_Renderer* renderer) {
    // Set the color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    // Render each segment of the snake's body
    for (const auto& segment : body) {
        SDL_RenderFillRect(renderer, &segment);
    }
}

// Handle user input to change the direction of the snake
void Snake::handleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            if (body.size() == 1) {
                direction = UP;
                move();
            }
            else {
                if (direction != DOWN ) {
                    direction = UP;
                    move();
                }
            }
            break;
        case SDLK_DOWN:
            if (body.size() == 1) {
                direction = DOWN;
                move();
            }
            else {
                if (direction != UP) {
                    direction = DOWN;
                    move();
                }
            }
            break;
        case SDLK_LEFT:
            if (body.size() == 1) {
                direction = LEFT;
                move();
            }
            else {
                if (direction != RIGHT) {
                    direction = LEFT;
                    move();
                }
            }
            break;
        case SDLK_RIGHT:
            if (body.size() == 1) {
                direction = RIGHT;
                move();
            }
            else {
                if (direction != LEFT) {
                    direction = RIGHT;
                    move();
                }
            }
            break;
        }
        cout << direction <<endl;
    }

}
// Increase the length of the snake
void Snake::grow() {
    // Get the position of the snake's tail
    SDL_Rect tail = body.back();

    // Extend the tail based on the current direction
    switch (direction) {
    case Direction::UP:
        tail.y += blockSize / 2;
        break;
    case Direction::DOWN:
        tail.y -= blockSize / 2;
        break;
    case Direction::LEFT:
        tail.x += blockSize / 2;
        break;
    case Direction::RIGHT:
        tail.x -= blockSize / 2;
        break;
    }

    // Add a new segment to the snake's body
    body.push_back({ tail.x, tail.y, blockSize, blockSize });
}


