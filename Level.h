#pragma once
#include "GameObject.h"
#include "Block.h"
#include "Target.h"
#include "raylib.h"
#include <vector>

struct HitResult {
    bool hit = false;
    bool hitTarget = false;
    int pointsAwarded = 0;
};

class Level {
private:
    std::vector<GameObject*> objects;
    std::vector<Block*> blocks;
    std::vector<Target*> targets;

    void ClearOwnedObjects();

public:
    Level();
    ~Level();

    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    void BuildDefaultLevel();
    HitResult CheckAndApplyFirstHit(Vector2 birdPos, float birdRadius);
    int CountRemainingTargets() const;
    void DrawAll() const;
    void ResetAll();
};
