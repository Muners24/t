#include "t.h"
#include "Clases/Tanque.h"
int main()
{
    SetTargetFPS(60);
    InitWindow(RANCHO,RALTO,"window");
    char buffer[10];
    Tanque t(RANCHO/2.0,RALTO/2.0,RED);
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            t.draw();
            DrawText(itoa(GetFPS(),buffer,10),10,10,40,WHITE);
        EndDrawing();
        t.update();
    }
    CloseWindow();
    return 0;
}