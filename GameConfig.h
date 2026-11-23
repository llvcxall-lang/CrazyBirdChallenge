#pragma once

namespace CrazyBirdConfig {
    constexpr int SCREEN_WIDTH = 1000;
    constexpr int SCREEN_HEIGHT = 600;
    constexpr float GROUND_Y = 520.0f;

    // Slingshot & Bird settings
    constexpr float SLING_X = 180.0f;
    constexpr float SLING_Y = 410.0f;
    constexpr float BIRD_RADIUS = 18.0f;
    constexpr float MAX_DRAG_DISTANCE = 110.0f;
    constexpr float LAUNCH_STRENGTH = 7.5f;
    constexpr float MIN_LAUNCH_DRAG = 5.0f;

    // Physics & Shot settings
    constexpr float GRAVITY = 520.0f;
    constexpr float MAX_SHOT_DURATION = 5.0f;
    constexpr float FIXED_SUBSTEP = 1.0f / 240.0f;

    // Rules & Scoring
    constexpr int MAX_ATTEMPTS = 3;
    constexpr int BLOCK_POINTS = 10;
    constexpr int TARGET_POINTS = 100;
    constexpr int MIN_BLOCKS = 5;
    constexpr int MIN_TARGETS = 3;
}
