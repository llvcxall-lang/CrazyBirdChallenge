#include "Block.h"
#include <algorithm>

Block::Block(Rectangle rect, int pts) : bounds(rect), points(pts) {
    active = true;
}

bool Block::CheckCircleHit(Vector2 center, float radius) const {
    if (!active) return false;

    float closestX = std::clamp(center.x, bounds.x, bounds.x + bounds.width);
    float closestY = std::clamp(center.y, bounds.y, bounds.y + bounds.height);

    float dx = center.x - closestX;
    float dy = center.y - closestY;
    return (dx * dx + dy * dy) <= (radius * radius);
}

int Block::OnHit() {
    if (!active) return 0;
    active = false;
    return points;
}

void Block::Draw() const {
    if (!active) return;

    DrawRectangleRec(bounds, BEIGE);
    DrawRectangleLinesEx(bounds, 2.5f, BROWN);
}

void Block::Reset() {
    active = true;
}
