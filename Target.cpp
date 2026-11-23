#include "Target.h"

Target::Target(Vector2 pos, float r, int pts) : center(pos), radius(r), points(pts) {
    active = true;
}

bool Target::CheckCircleHit(Vector2 birdCenter, float birdRadius) const {
    if (!active) return false;

    float dx = birdCenter.x - center.x;
    float dy = birdCenter.y - center.y;
    float sumR = birdRadius + radius;
    return (dx * dx + dy * dy) <= (sumR * sumR);
}

int Target::OnHit() {
    if (!active) return 0;
    active = false;
    return points;
}

void Target::Draw() const {
    if (!active) return;

    DrawCircleV(center, radius, LIME);
    DrawCircleLines((int)center.x, (int)center.y, radius, DARKGREEN);
    DrawCircle((int)(center.x - radius * 0.28f), (int)(center.y - radius * 0.15f), radius * 0.18f, WHITE);
    DrawCircle((int)(center.x - radius * 0.28f), (int)(center.y - radius * 0.15f), radius * 0.08f, BLACK);
    DrawCircle((int)(center.x + radius * 0.28f), (int)(center.y - radius * 0.15f), radius * 0.18f, WHITE);
    DrawCircle((int)(center.x + radius * 0.28f), (int)(center.y - radius * 0.15f), radius * 0.08f, BLACK);
}

void Target::Reset() {
    active = true;
}
