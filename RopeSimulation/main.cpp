#include "Rope.hpp"

int main(int argc, char* argv[]){

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_CreateWindowAndRenderer(1200, 800, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

    RopeSimulation* ropeSimu = new RopeSimulation();
    ropeSimu->InitRope(620, 10);
    ropeSimu->Simulation();
    ropeSimu->Render(renderer);

    bool isQuit = false;
    SDL_Event event;
    while(!isQuit){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isQuit = true;
            }
       }
       ropeSimu->Simulation();
       ropeSimu->Render(renderer);
    }
    return 0;
}
