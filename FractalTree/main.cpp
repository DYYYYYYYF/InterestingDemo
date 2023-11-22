#include "FractalTree.hpp"

int main(int argc, char* argv[]){

    FractalTree* ft = new FractalTree();
    ft->Init();
    ft->GenerateTree();
    ft->Display();

    bool isQuit = false;
    SDL_Event event;
    while(!isQuit){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isQuit = true;
            }
            if(event.key.keysym.sym == SDLK_UP){
                ft->AddAngle();
                ft->GenerateTree();
                ft->Display();
            } 
            if(event.key.keysym.sym == SDLK_DOWN){
                ft->DeAngle();
                ft->GenerateTree();
                ft->Display();
            } 
        }
    }

    ft->End();
    return 0;
}
