#pragma once
#include <iostream>
#include <SDL.h>
#include <ostream>
#include <string>
#include <vector>

struct Vector2{

    Vector2():x(0.0f), y(0.0f){}
    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }

    float x = 0.0f;
    float y = 0.0f;

    inline Vector2& operator=(const Vector2& v){
        if (this == &v){
            return *this;
        }

        this->x = v.x;
        this->y = v.y;

        return *this;
    }

     friend std::ostream& operator<<(std::ostream& out, const Vector2& vec){
        out << "x: " << vec.x << " y: " << vec.y << std::endl; 
        return out;
    }
};

inline Vector2 operator+(const Vector2& v1, const Vector2& v2){
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

inline Vector2 operator*(const Vector2& v, float k){
    return Vector2(v.x * k, v.y * k);
}

inline Vector2 operator-(const Vector2& v1, const Vector2& v2){
    return Vector2(v1.x - v2.x, v1.y - v2.y);
}

inline Vector2 operator/(const Vector2& v, float k){
    float seg = 1.0f / k;
    return Vector2(v.x * seg, v.y * seg);
}

struct Partical{

    float mass = 1.0f;

    Vector2 oldPos = {0.0f, 0.0f};
    Vector2 curPos = {0.0f, 0.0f};
    Vector2 force = {0.0f, 0.0f};
    Vector2 velocity = {0.0f, 0.0f};

    bool free = true;

};

typedef std::vector<Partical> Particals;

class RopeSimulation{
public:
    RopeSimulation();
    virtual ~RopeSimulation();

    void InitRope(float length, int segment);
    void Simulation();
    void Render(SDL_Renderer* renderer);

    float GetVectorLength(const Vector2& vec){
        return sqrt(vec.x * vec.x + vec.y * vec.y);
    }

private:
    Vector2 originPos;
    Vector2 gravity;
    Particals masses;
    float length;
    int segment;

    int color;
};
