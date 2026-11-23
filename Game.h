#pragma once
#include "Bird.h"
#include "Slingshot.h"
#include "Level.h"
#include "raylib.h"

enum class GameState {
    Title,
    Aiming,
    Flying,
    Paused,
    Win,
    Lose
};

class Game {
private:
    GameState state = GameState::Title;
    GameState stateBeforePause = GameState::Aiming;

    Bird bird;
    Slingshot slingshot;
    Level level;

    int score = 0;
    int attemptsRemaining = 3;
    float shotTimer = 0.0f;

    void HandleInput();
    void UpdateAiming();
    void UpdateFlying(float dt);
    void EndCurrentShot();
    void ResetGameToTitle();
    void DrawHud() const;

public:
    Game();
    void Update(float dt);
    void Draw() const;
};
