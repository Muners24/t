#pragma once
#include "../t.h"
#include <list>
#include <functional>

using std::list;
using std::function;

typedef struct
{
    Vector2 vertices[3];
}Triangle;

class Tanque
{
private:
    Rectangle pos;
    Color color;
    float direccion;
    Vector2 vel;
    bool acel_b;
    bool ret_b;
    Triangle front;
    Triangle left;
    Triangle right;
    Triangle back;

    void area();
    void calcularDireccion();
    void calcularVelocidad();
    void movimiento();
    Vector2 canon();
    float radianes(float grados);
    float grados(float radiantes);
    Vector2 calcularVertices(function<float(float ,float)> f);

public:
    Tanque(float x,float y,Color color);
    Tanque(){};
    void input();
    void update();
    void draw();
};