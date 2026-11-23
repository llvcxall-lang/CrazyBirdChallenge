#pragma once
#include "GameObject.h"
#include "raylib.h"

class Block : public GameObject {
private:
    Rectangle bounds{0.0f, 0.0f, 0.0f, 0.0f};
    int points = 10;

public:
    Block(Rectangle rect, int pts = 10);

    bool CheckCircleHit(Vector2 center, float radius) const;
    int OnHit();
    void Draw() const override;
    void Reset() override;

    Rectangle GetBounds() const { return bounds; }
    int GetPoints() const { return points; }
};
