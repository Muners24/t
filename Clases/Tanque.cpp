#include "Tanque.h"

Tanque::Tanque(float x, float y, Color color)
{
    pos.x = x;
    pos.y = y;
    pos.width = TANKW;
    pos.height = TANKH;
    this->color = color;
    vel.x = 0;
    vel.y = 0;
    ret_b = false;
    acel_b = false;
}

void Tanque::draw()
{
    DrawRectanglePro(pos, {float(pos.width / 2.0), float(pos.height / 2.0)}, grados(direccion) * -1, color);
    // struct
    // DrawRectangleRec(pos, BLUE);
    // triangulos hitbox
    // DrawTriangle(front.vertices[0], front.vertices[1], front.vertices[2], GREEN);
    // DrawTriangle(left.vertices[0], left.vertices[1], left.vertices[2], GREEN);
    // DrawTriangle(back.vertices[0], back.vertices[1], back.vertices[2], GREEN);
    // DrawTriangle(right.vertices[0], right.vertices[1], right.vertices[2], GREEN);
}

void Tanque::calcularDireccion()
{
    Vector2 mouse = GetMousePosition();
    Vector2 triangulo;

    triangulo.x = mouse.x - pos.x;
    triangulo.y = mouse.y - pos.y;

    direccion = atan(triangulo.y / triangulo.x);

    direccion = grados(direccion);
    direccion = abs(direccion);

    if (triangulo.x > 0)
    {
        if (triangulo.y > 0)
        {
            direccion = 360 - direccion;
        }
    }
    else
    {
        if (triangulo.y > 0)
        {
            direccion += 180;
        }
        else
        {
            direccion = 180 - direccion;
        }
    }
    direccion = radianes(direccion);
}

void Tanque::update()
{
    input();
    calcularDireccion();
    area();
    calcularVelocidad();
    movimiento();
}

float Tanque::radianes(float grados)
{
    return (grados * PI / 180.f);
}

float Tanque::grados(float radianes)
{
    return radianes * 180 / PI;
}

void Tanque::input()
{
    acel_b = IsKeyDown(KEY_W) ? true : false;
    ret_b = IsKeyDown(KEY_S) ? true : false;
}

void Tanque::movimiento()
{
    pos.x += vel.x;
    pos.y += vel.y;
}

void Tanque::calcularVelocidad()
{
    Vector2 mouse = GetMousePosition();

    if (acel_b)
    {
        vel.y = sin(direccion) * TANKV * -1;
        vel.x = cos(direccion) * TANKV;
        if (CheckCollisionPointTriangle(mouse, front.vertices[0], front.vertices[1], front.vertices[2]))
        {
            vel.x = 0;
            vel.y = 0;
        }
    }
    else
    {
        if (ret_b)
        {
            vel.y = (sin(direccion) * TANKV) / 1.3;
            vel.x = (cos(direccion) * TANKV) / 1.3 * -1;
        }
        else
        {
            vel.x = 0;
            vel.y = 0;
        }
    }
}

void Tanque::area()
{
    Vector2 vertices[4];
    auto f1 = [](float dir, float angulo_0)
    { return dir - angulo_0; };

    auto f2 = [](float dir, float angulo_0)
    { return dir + angulo_0; };

    auto f3 = [](float dir, float angulo_0)
    { return dir - PI - angulo_0; };
    
    auto f4 = [](float dir, float angulo_0)
    { return dir - PI + angulo_0; };

    vertices[0] = calcularVertices(f1);
    vertices[1] = calcularVertices(f2);
    vertices[2] = calcularVertices(f3);
    vertices[3] = calcularVertices(f4);

    Vector2 cent;
    cent.x = pos.x;
    cent.y = pos.y;

    front.vertices[0] = cent;
    front.vertices[1] = vertices[0];
    front.vertices[2] = vertices[1];

    left.vertices[0] = cent;
    left.vertices[1] = vertices[1];
    left.vertices[2] = vertices[2];

    back.vertices[0] = cent;
    back.vertices[1] = vertices[2];
    back.vertices[2] = vertices[3];

    right.vertices[0] = cent;
    right.vertices[1] = vertices[3];
    right.vertices[2] = vertices[0];
}

Vector2 Tanque::calcularVertices(function<float(float, float)> f)
{
    Vector2 triangulo;
    float angulo_0;
    float angulo_r;
    angulo_0 = atan((pos.height / 2.f) / (pos.width / 2.f));
    angulo_0 = f(direccion, angulo_0);
    angulo_r = radianes(90) - angulo_0;
    triangulo.y = TANKDIAG * sin(angulo_0);
    triangulo.x = TANKDIAG * sin(angulo_r);

    Vector2 vertice;
    vertice.x = pos.x + triangulo.x;
    vertice.y = pos.y - triangulo.y;

    return vertice;
}
