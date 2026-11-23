#pragma once
#include "raylib.h"

class GameObject {
protected:
    bool active = true;

public:
    virtual ~GameObject() = default;

    virtual void Draw() const = 0;
    virtual void Reset() = 0;

    bool IsActive() const { return active; }
    void SetActive(bool state) { active = state; }
};
