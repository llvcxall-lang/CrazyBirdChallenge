#include "Game.h"
#include "GameConfig.h"
#include <cstdio>

Game::Game()
    : bird(CrazyBirdConfig::BIRD_RADIUS),
      slingshot({CrazyBirdConfig::SLING_X, CrazyBirdConfig::SLING_Y},
                CrazyBirdConfig::MAX_DRAG_DISTANCE,
                CrazyBirdConfig::LAUNCH_STRENGTH),
      level() {
    ResetGameToTitle();
}

void Game::ResetGameToTitle() {
    state = GameState::Title;
    stateBeforePause = GameState::Aiming;
    score = 0;
    attemptsRemaining = CrazyBirdConfig::MAX_ATTEMPTS;
    shotTimer = 0.0f;
    level.ResetAll();
    slingshot.Reset(bird);
}

void Game::HandleInput() {
    if (IsKeyPressed(KEY_R)) {
        ResetGameToTitle();
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        if (state == GameState::Aiming || state == GameState::Flying) {
            stateBeforePause = state;
            state = GameState::Paused;
        } else if (state == GameState::Paused) {
            state = stateBeforePause;
        }
        return;
    }

    if (state == GameState::Paused) return;

    if (state == GameState::Title) {
        if (IsKeyPressed(KEY_ENTER)) {
            state = GameState::Aiming;
            slingshot.Reset(bird);
        }
        return;
    }

    if (state == GameState::Win || state == GameState::Lose) {
        if (IsKeyPressed(KEY_ENTER)) {
            ResetGameToTitle();
            state = GameState::Aiming;
        }
        return;
    }
}

void Game::UpdateAiming() {
    if (attemptsRemaining <= 0) {
        if (level.CountRemainingTargets() == 0) {
            state = GameState::Win;
        } else {
            state = GameState::Lose;
        }
        return;
    }

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        slingshot.BeginDrag(mouse, bird);
    }

    if (slingshot.IsDragging()) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            slingshot.UpdateDrag(mouse);
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            Vector2 launchVel{0.0f, 0.0f};
            if (slingshot.ReleaseAndLaunch(bird, launchVel)) {
                attemptsRemaining -= 1;
                shotTimer = 0.0f;
                state = GameState::Flying;
            }
        }
    }
}

void Game::EndCurrentShot() {
    bird.SetVelocity({0.0f, 0.0f});

    if (level.CountRemainingTargets() == 0) {
        state = GameState::Win;
        return;
    }

    if (attemptsRemaining > 0) {
        slingshot.Reset(bird);
        state = GameState::Aiming;
    } else {
        state = GameState::Lose;
    }
}

void Game::UpdateFlying(float dt) {
    if (dt <= 0.0f) return;

    float remaining = dt;
    while (remaining > 0.0f) {
        float step = (remaining > CrazyBirdConfig::FIXED_SUBSTEP)
                         ? CrazyBirdConfig::FIXED_SUBSTEP
                         : remaining;

        bird.UpdateFlight(step, CrazyBirdConfig::GRAVITY);
        shotTimer += step;

        HitResult hitRes = level.CheckAndApplyFirstHit(bird.GetPosition(), bird.GetRadius());
        if (hitRes.hit) {
            score += hitRes.pointsAwarded;
            EndCurrentShot();
            return;
        }

        Vector2 pos = bird.GetPosition();
        float r = bird.GetRadius();

        bool hitGround = (pos.y + r) >= CrazyBirdConfig::GROUND_Y;
        bool leftScreen = (pos.x + r < 0.0f) || (pos.x - r > CrazyBirdConfig::SCREEN_WIDTH) ||
                          (pos.y + r < 0.0f);
        bool timedOut = (shotTimer >= CrazyBirdConfig::MAX_SHOT_DURATION);

        if (hitGround || leftScreen || timedOut) {
            EndCurrentShot();
            return;
        }

        remaining -= step;
    }
}

void Game::Update(float dt) {
    HandleInput();

    if (state == GameState::Aiming) {
        UpdateAiming();
    } else if (state == GameState::Flying) {
        UpdateFlying(dt);
    }
}

void Game::DrawHud() const {
    DrawRectangle(0, 0, CrazyBirdConfig::SCREEN_WIDTH, 48, Color{30, 41, 59, 235});

    char hudBuf[160];
    std::snprintf(hudBuf, sizeof(hudBuf),
                  "Score: %d   |   Attempts Left: %d   |   Targets Left: %d",
                  score, attemptsRemaining, level.CountRemainingTargets());
    DrawText(hudBuf, 20, 14, 20, RAYWHITE);
    DrawText("Enter: Start/Retry | Drag+Release: Launch | P: Pause | R: Reset | Esc: Quit",
             420, 16, 15, LIGHTGRAY);
}

void Game::Draw() const {
    ClearBackground(SKYBLUE);

    // Ground
    DrawRectangle(0, (int)CrazyBirdConfig::GROUND_Y,
                  CrazyBirdConfig::SCREEN_WIDTH,
                  CrazyBirdConfig::SCREEN_HEIGHT - (int)CrazyBirdConfig::GROUND_Y,
                  DARKGREEN);
    DrawLine(0, (int)CrazyBirdConfig::GROUND_Y,
             CrazyBirdConfig::SCREEN_WIDTH, (int)CrazyBirdConfig::GROUND_Y, LIME);

    level.DrawAll();
    slingshot.Draw(bird);
    bird.Draw();
    DrawHud();

    if (state == GameState::Title) {
        DrawRectangle(0, 0, CrazyBirdConfig::SCREEN_WIDTH, CrazyBirdConfig::SCREEN_HEIGHT, Fade(BLACK, 0.45f));
        DrawText("CRAZY BIRD CHALLENGE", 310, 190, 36, RAYWHITE);
        DrawText("Destroy all 3 targets in 3 shots!", 350, 245, 22, GOLD);
        DrawText("Press ENTER to Start", 390, 295, 24, LIME);
    } else if (state == GameState::Paused) {
        DrawRectangle(0, 0, CrazyBirdConfig::SCREEN_WIDTH, CrazyBirdConfig::SCREEN_HEIGHT, Fade(BLACK, 0.5f));
        DrawText("PAUSED", 435, 240, 38, RAYWHITE);
        DrawText("Press P to Resume or R to Reset", 345, 295, 20, LIGHTGRAY);
    } else if (state == GameState::Win) {
        DrawRectangle(0, 0, CrazyBirdConfig::SCREEN_WIDTH, CrazyBirdConfig::SCREEN_HEIGHT, Fade(BLACK, 0.55f));
        DrawText("YOU WIN!", 415, 215, 42, LIME);
        char winBuf[64];
        std::snprintf(winBuf, sizeof(winBuf), "Final Score: %d", score);
        DrawText(winBuf, 415, 270, 24, RAYWHITE);
        DrawText("Press ENTER to Play Again or R for Title", 315, 315, 20, LIGHTGRAY);
    } else if (state == GameState::Lose) {
        DrawRectangle(0, 0, CrazyBirdConfig::SCREEN_WIDTH, CrazyBirdConfig::SCREEN_HEIGHT, Fade(BLACK, 0.55f));
        DrawText("GAME OVER", 395, 215, 42, RED);
        char loseBuf[96];
        std::snprintf(loseBuf, sizeof(loseBuf), "Score: %d | Targets Left: %d",
                      score, level.CountRemainingTargets());
        DrawText(loseBuf, 375, 270, 24, RAYWHITE);
        DrawText("Press ENTER to Retry or R for Title", 315, 315, 20, LIGHTGRAY);
    }
}
