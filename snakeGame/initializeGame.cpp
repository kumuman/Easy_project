#include "initializeGame.h"
#include <deque>
#include <iostream>

using namespace std;

/*Game::Game() {
    initialize();
    gameLoop();
}*/

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        exit(0);  // Exit the program if SDL initialization fails
    }
    // Create the SDL window and renderer
    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::gameLoop() {
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit(0);  // Quit the game loop if the user closes the window
            }
            snake.handleInput(event);  // Handle user input for the snake
            checkBoardCollision(snake.body);  // Check for collision with game board boundaries
            if (snake.body.size() > 4) {
                if (checkSelfCollision(snake.body)) {
                    quit = true;
                    cout << "Your Score is ；" << snake.body.size()<<endl;
                    system("pause");
                }// Check for collision with the snake itself
            }
            if (checkFoodCollision(food.position, snake.body.front())) {
                food.spawn();  // Spawn new food
                snake.grow();  // Grow the snake
            }
        }

        // Render the game
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        snake.render(renderer);  // Render the snake
        food.render(renderer);   // Render the food
        SDL_RenderPresent(renderer);
    }
}

// Check for collision with the snake itself
bool Game::checkSelfCollision(deque<SDL_Rect> body) {
    SDL_Rect head = body.front();
    for (auto it = body.begin() + 4; it != body.end(); ++it) {
        double dist = sqrt(pow((it->x - head.x), 2) + pow((it->y - head.y), 2));
        if (dist < blocksize) {
            cout << "Game Over!!" << endl;  // Print game over message
            return true;  // Exit the program
        }
    }
    return false;
}

// Check for collision with the food
bool Game::checkFoodCollision(SDL_Rect food, SDL_Rect body) {
    double dist = sqrt(pow((food.x - body.x), 2) + pow((food.y - body.y), 2));
    return (dist < blocksize);  // Return true if collision occurs, false otherwise
}

// Check for collision with the game board boundaries
void Game::checkBoardCollision(deque<SDL_Rect>& body) {
    SDL_Rect head = body.front();
    if (head.x < 0) {
        head.x = WIDTH - head.w;  // Wrap around to the right side of the screen
    }
    else if (head.x + head.w > WIDTH) {
        head.x = 0;  // Wrap around to the left side of the screen
    }
    if (head.y < 0) {
        head.y = HEIGHT - head.h;  // Wrap around to the bottom of the screen
    }
    else if (head.y + head.h > HEIGHT) {
        head.y = 0;  // Wrap around to the top of the screen
    }
    body.front() = head;
}
