#include "Game.h"
#include "GameConfig.h"
#include "raylib.h"

int main() {
    InitWindow(CrazyBirdConfig::SCREEN_WIDTH,
                 CrazyBirdConfig::SCREEN_HEIGHT,
                 "Crazy Bird Challenge");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        game.Update(dt);

        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
