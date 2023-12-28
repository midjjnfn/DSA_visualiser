#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_render.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Function to render UI elements
void renderUI(SDL_Renderer* renderer) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw a button
    SDL_Rect buttonRect = {50, 50, 100, 50};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gray button color
    SDL_RenderFillRect(renderer, &buttonRect);

    // Draw button text
    SDL_Color textColor = {255, 255, 255, 255}; // White text color
    TTF_Font* font = TTF_OpenFont("ARIAL.TTF", 24); // Replace with your font file and size
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Button", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
    SDL_Rect textRect = {buttonRect.x + buttonRect.w / 2 - textW / 2, buttonRect.y + buttonRect.h / 2 - textH / 2, textW, textH};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Cleanup font and text resources
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    // Present the renderer content
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("UI Layout Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize SDL_ttf for text rendering
    if (TTF_Init() != 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Render UI elements
    renderUI(renderer);

    // Event loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Clean up resources
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
