#include "Rope.hpp"

RopeSimulation::RopeSimulation() : color(0), gravity({0.0f, -9.8f}), originPos({600.0f, 0.0f}){
    gravity.x = 0.0f;
    gravity.y = 9.8f;

    originPos.x = 400.f;
    originPos.y = 0.0f;
}
RopeSimulation::~RopeSimulation(){}

void RopeSimulation::InitRope(float nLength, int nSegment){
    length = nLength;  
    segment = nSegment;
    float lenPerSegment = length / (float)segment;

    masses.resize(segment + 1);
    for(int i=0; i<=segment; i++){
        Partical& mass = masses[i];

        Vector2 offset = {i * lenPerSegment, 0.0f}; 
        mass.curPos = originPos + offset;
        mass.oldPos = originPos + offset;
        mass.velocity = {0.0f, 0.0f};
        mass.mass = 1.0f;
        mass.force = {0.0f, 0.0f};
        mass.free = true;
    }

    masses[0].free = false;
}

void RopeSimulation::Simulation(){
    // Calculate forc
    for(int i=0; i<=segment; ++i){
        Partical& mass = masses[i];

        if(!mass.free) continue;

        Vector2 force = gravity;
        const Vector2 verlet = mass.curPos - mass.oldPos;
        const Vector2 nextPos = mass.curPos + verlet + (force * 0.05f);

        mass.oldPos = mass.curPos;
        mass.curPos = nextPos;
    }

    for(int i=0; i < segment; ++i){
        Partical& p1 = masses[i];
        Partical& p2 = masses[i + 1];

        Vector2 delta = p2.curPos - p1.curPos;
        float distance = GetVectorLength(delta);

        std::cout << delta << " " << distance << std::endl;

        Vector2 dir = delta / distance;
        Vector2 vectorCorrection = dir * (distance - (float)length / (float)segment);

        if (p1.free && p2.free){
            p1.curPos = p1.curPos + (vectorCorrection * 0.5f);
            p2.curPos = p2.curPos - (vectorCorrection * 0.5f);
        } else if(p1.free){
            p1.curPos = p1.curPos + vectorCorrection;
        } else if(p2.free){
            p2.curPos = p2.curPos - vectorCorrection;
        }

        if (p1.curPos.x > 1200) p1.curPos.x = 1200;
        if (p1.curPos.x < 0) p1.curPos.x = 0;
        if (p2.curPos.x > 1200) p2.curPos.x = 1200;
        if (p2.curPos.x < 0) p2.curPos.x = 0;

        if (p1.curPos.y > 800) p1.curPos.y = 800;
        if (p1.curPos.y < 0) p1.curPos.y = 0;
        if (p2.curPos.y > 800) p2.curPos.y = 800;
        if (p2.curPos.y < 0) p2.curPos.y = 0;
    }
}

void RopeSimulation::Render(SDL_Renderer* render){
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, color, color, color, color);

    Partical p1, p2;
    for(int i=0; i<segment; ++i){
        p1 = masses[i];
        p2 = masses[i +1];

        color += color / (segment + 2);
        SDL_SetRenderDrawColor(render, color, color, color, color);
        SDL_RenderDrawLine(render, (int)p1.curPos.x, (int)p1.curPos.y,
                           (int)p2.curPos.x, (int)p2.curPos.y);
    }
    SDL_RenderPresent(render);
    color = 0;
}
