#pragma once
#include "GameObject.h"
#include "raylib.h"

class Bird : public GameObject {
private:
    Vector2 position{0.0f, 0.0f};
    Vector2 velocity{0.0f, 0.0f};
    float radius = 18.0f;
    bool launched = false;

public:
    explicit Bird(float r = 18.0f);

    void LoadAt(Vector2 anchorPos);
    void Launch(Vector2 initialVel);
    void UpdateFlight(float dt, float gravity);
    void Draw() const override;
    void Reset() override;

    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    bool IsLaunched() const { return launched; }
    void SetPosition(Vector2 pos) { position = pos; }
    void SetVelocity(Vector2 vel) { velocity = vel; }
};
