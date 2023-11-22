#include "FractalTree.hpp"

FractalTree::FractalTree() : nWidth(1200), nHeight(800){
    window = nullptr;
    renderer = nullptr;

    rootPoint.x = nWidth * 0.5;
    rootPoint.y = nHeight * 0.99;
}

FractalTree::~FractalTree(){}

void FractalTree::Init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(nWidth, nHeight, SDL_WINDOW_SHOWN, &window, &renderer);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void FractalTree::GenerateTree(){
    Generate(rootPoint, 90, 250);
}

void FractalTree::Generate(SDL_Point point, float angle, float length){
    if (length < 15){
        return;
    }

    float degree = angle * 3.1415926 / 180;
    SDL_Point curPoint;
    curPoint.x = point.x + length * cos(degree);
    curPoint.y = point.y - length * sin(degree);

    Generate(curPoint, angle + fAngle, length * 0.7);
    Generate(curPoint, angle - fAngle, length * 0.7);

    DrawLine(point, curPoint);
}

void FractalTree::DrawLine(SDL_Point p1, SDL_Point p2){
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);

}

void FractalTree::Display(){
    SDL_RenderPresent(renderer);
}

void FractalTree::End(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void FractalTree::AddAngle(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    fAngle += 1;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void FractalTree::DeAngle(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    fAngle -= 1;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
