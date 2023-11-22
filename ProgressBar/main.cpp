#include <iostream>
#include <SDL.h>
#include <vector>
#include <random>
#include <Logger.hpp>

int WIN_WIDTH = 1200;
int WIN_HEIGHT = 800;

int main(int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return -1;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);

    int width = 0 ;
    SDL_Rect rect, bouding;
    rect.x = WIN_WIDTH / 2 - 100;
    rect.y = WIN_HEIGHT / 2;
    rect.h = 80;
    rect.w = width;

    bouding.x = WIN_WIDTH / 2 - 100;
    bouding.y = WIN_HEIGHT / 2;
    bouding.h = 80;
    bouding.w = 300;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    bool isQuit = false;
    SDL_Event event;
    while(!isQuit){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isQuit = true;
            }
            if(event.key.keysym.sym == SDLK_UP){
                if (width + 3 > 300){
                    width = 300;
                } else {
                    width += 3;
                }
                rect.w = width;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_RenderDrawRect(renderer, &bouding);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
