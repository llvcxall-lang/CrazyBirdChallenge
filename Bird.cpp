#include "Bird.h"
#include "GameConfig.h"
#include <cmath>

Bird::Bird(float r) : radius(r) {
    Reset();
}

void Bird::LoadAt(Vector2 anchorPos) {
    position = anchorPos;
    velocity = {0.0f, 0.0f};
    launched = false;
    active = true;
}

void Bird::Launch(Vector2 initialVel) {
    velocity = initialVel;
    launched = true;
    active = true;
}

void Bird::UpdateFlight(float dt, float gravity) {
    if (!active || !launched || dt <= 0.0f) return;

    float remaining = dt;
    while (remaining > 0.0f) {
        float step = (remaining > CrazyBirdConfig::FIXED_SUBSTEP)
                         ? CrazyBirdConfig::FIXED_SUBSTEP
                         : remaining;
        velocity.y += gravity * step;
        position.x += velocity.x * step;
        position.y += velocity.y * step;
        remaining -= step;
    }
}

void Bird::Draw() const {
    if (!active) return;

    DrawCircleV(position, radius, RED);
    DrawCircleLines((int)position.x, (int)position.y, radius, MAROON);

    // Eyes & beak for clear visual identity
    DrawCircle((int)(position.x + radius * 0.30f), (int)(position.y - radius * 0.20f), radius * 0.22f, WHITE);
    DrawCircle((int)(position.x + radius * 0.36f), (int)(position.y - radius * 0.20f), radius * 0.10f, BLACK);

    Vector2 beakTip{position.x + radius * 1.15f, position.y + radius * 0.05f};
    Vector2 beakTop{position.x + radius * 0.55f, position.y - radius * 0.15f};
    Vector2 beakBot{position.x + radius * 0.55f, position.y + radius * 0.25f};
    DrawTriangle(beakTop, beakBot, beakTip, GOLD);
}

void Bird::Reset() {
    position = {CrazyBirdConfig::SLING_X, CrazyBirdConfig::SLING_Y};
    velocity = {0.0f, 0.0f};
    launched = false;
    active = true;
}
