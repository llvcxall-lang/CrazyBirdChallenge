#pragma once
#include "Bird.h"
#include "raylib.h"

class Slingshot {
private:
    Vector2 anchor{0.0f, 0.0f};
    Vector2 dragPos{0.0f, 0.0f};
    float maxDrag = 110.0f;
    float launchStrength = 7.5f;
    bool dragging = false;

public:
    Slingshot(Vector2 anchorPos, float maxPull, float strength);

    bool BeginDrag(Vector2 mousePos, const Bird& bird);
    void UpdateDrag(Vector2 mousePos);
    bool ReleaseAndLaunch(Bird& bird, Vector2& outVelocity);
    void CancelDrag(Bird& bird);
    void Draw(const Bird& bird) const;
    void Reset(Bird& bird);

    Vector2 GetAnchor() const { return anchor; }
    bool IsDragging() const { return dragging; }
};
