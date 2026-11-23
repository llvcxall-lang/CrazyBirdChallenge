#pragma once
#include "GameObject.h"
#include "raylib.h"

class Target : public GameObject {
private:
    Vector2 center{0.0f, 0.0f};
    float radius = 20.0f;
    int points = 100;

public:
    Target(Vector2 pos, float r = 20.0f, int pts = 100);

    bool CheckCircleHit(Vector2 birdCenter, float birdRadius) const;
    int OnHit();
    void Draw() const override;
    void Reset() override;

    Vector2 GetCenter() const { return center; }
    float GetRadius() const { return radius; }
    int GetPoints() const { return points; }
};
