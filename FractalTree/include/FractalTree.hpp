#pragma once
#include <SDL.h>

class FractalTree{
    public:
        FractalTree();
        virtual ~FractalTree();

        void Init();
        void Display();
        void End();

        void GenerateTree();
        void AddAngle();
        void DeAngle();

    private:
        void Generate(SDL_Point point, float angle, float length);
        void DrawLine(SDL_Point p1, SDL_Point p2);

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        int nWidth;
        int nHeight;

        SDL_Point rootPoint;
        float fAngle = 30;

};
