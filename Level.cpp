#include "Level.h"
#include "GameConfig.h"

Level::Level() {
    BuildDefaultLevel();
}

Level::~Level() {
    ClearOwnedObjects();
}

void Level::ClearOwnedObjects() {
    for (GameObject* obj : objects) {
        delete obj;
    }
    objects.clear();
    blocks.clear();
    targets.clear();
}

void Level::BuildDefaultLevel() {
    ClearOwnedObjects();

    const float gy = CrazyBirdConfig::GROUND_Y;

    // 5 breakable blocks (reachable layout)
    Block* b1 = new Block({620.0f, gy - 80.0f, 24.0f, 80.0f}, CrazyBirdConfig::BLOCK_POINTS);
    Block* b2 = new Block({740.0f, gy - 80.0f, 24.0f, 80.0f}, CrazyBirdConfig::BLOCK_POINTS);
    Block* b3 = new Block({615.0f, gy - 104.0f, 154.0f, 24.0f}, CrazyBirdConfig::BLOCK_POINTS);
    Block* b4 = new Block({655.0f, gy - 164.0f, 22.0f, 60.0f}, CrazyBirdConfig::BLOCK_POINTS);
    Block* b5 = new Block({830.0f, gy - 70.0f, 26.0f, 70.0f}, CrazyBirdConfig::BLOCK_POINTS);

    blocks = {b1, b2, b3, b4, b5};
    for (Block* b : blocks) {
        objects.push_back(b);
    }

    // 3 targets
    Target* t1 = new Target({690.0f, gy - 22.0f}, 22.0f, CrazyBirdConfig::TARGET_POINTS);
    Target* t2 = new Target({705.0f, gy - 126.0f}, 22.0f, CrazyBirdConfig::TARGET_POINTS);
    Target* t3 = new Target({843.0f, gy - 92.0f}, 22.0f, CrazyBirdConfig::TARGET_POINTS);

    targets = {t1, t2, t3};
    for (Target* t : targets) {
        objects.push_back(t);
    }
}

HitResult Level::CheckAndApplyFirstHit(Vector2 birdPos, float birdRadius) {
    HitResult result;

    for (Block* blk : blocks) {
        if (blk && blk->IsActive() && blk->CheckCircleHit(birdPos, birdRadius)) {
            result.hit = true;
            result.hitTarget = false;
            result.pointsAwarded = blk->OnHit();
            return result;
        }
    }

    for (Target* tgt : targets) {
        if (tgt && tgt->IsActive() && tgt->CheckCircleHit(birdPos, birdRadius)) {
            result.hit = true;
            result.hitTarget = true;
            result.pointsAwarded = tgt->OnHit();
            return result;
        }
    }

    return result;
}

int Level::CountRemainingTargets() const {
    int count = 0;
    for (const Target* tgt : targets) {
        if (tgt && tgt->IsActive()) {
            ++count;
        }
    }
    return count;
}

void Level::DrawAll() const {
    for (const GameObject* obj : objects) {
        if (obj && obj->IsActive()) {
            obj->Draw();
        }
    }
}

void Level::ResetAll() {
    for (GameObject* obj : objects) {
        if (obj) {
            obj->Reset();
        }
    }
}
