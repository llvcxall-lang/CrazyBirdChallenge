#include "Slingshot.h"
#include "GameConfig.h"
#include <cmath>

Slingshot::Slingshot(Vector2 anchorPos, float maxPull, float strength)
    : anchor(anchorPos), dragPos(anchorPos), maxDrag(maxPull), launchStrength(strength) {}

bool Slingshot::BeginDrag(Vector2 mousePos, const Bird& bird) {
    if (!bird.IsActive() || bird.IsLaunched()) return false;

    float dxBird = mousePos.x - bird.GetPosition().x;
    float dyBird = mousePos.y - bird.GetPosition().y;
    float distBird = std::sqrt(dxBird * dxBird + dyBird * dyBird);

    float dxAnchor = mousePos.x - anchor.x;
    float dyAnchor = mousePos.y - anchor.y;
    float distAnchor = std::sqrt(dxAnchor * dxAnchor + dyAnchor * dyAnchor);

    float grabRadius = bird.GetRadius() * 2.0f;
    if (distBird <= grabRadius || distAnchor <= grabRadius) {
        dragging = true;
        UpdateDrag(mousePos);
        return true;
    }
    return false;
}

void Slingshot::UpdateDrag(Vector2 mousePos) {
    if (!dragging) return;

    float dx = mousePos.x - anchor.x;
    float dy = mousePos.y - anchor.y;
    float dist = std::sqrt(dx * dx + dy * dy);

    if (dist > maxDrag && dist > 0.0001f) {
        float scale = maxDrag / dist;
        dx *= scale;
        dy *= scale;
    }

    dragPos = {anchor.x + dx, anchor.y + dy};
}

bool Slingshot::ReleaseAndLaunch(Bird& bird, Vector2& outVelocity) {
    if (!dragging) return false;
    dragging = false;

    float pullX = anchor.x - dragPos.x;
    float pullY = anchor.y - dragPos.y;
    float pullLen = std::sqrt(pullX * pullX + pullY * pullY);

    if (pullLen < CrazyBirdConfig::MIN_LAUNCH_DRAG) {
        bird.LoadAt(anchor);
        dragPos = anchor;
        outVelocity = {0.0f, 0.0f};
        return false;
    }

    outVelocity = {pullX * launchStrength, pullY * launchStrength};
    bird.SetPosition(dragPos);
    bird.Launch(outVelocity);
    dragPos = anchor;
    return true;
}

void Slingshot::CancelDrag(Bird& bird) {
    dragging = false;
    dragPos = anchor;
    bird.LoadAt(anchor);
}

void Slingshot::Draw(const Bird& bird) const {
    Vector2 bandEnd = dragging ? dragPos : bird.GetPosition();

    // Back band
    DrawLineEx(anchor, bandEnd, 5.0f, DARKBROWN);

    // Slingshot fork post & ground stand
    DrawRectangle((int)(anchor.x - 6), (int)anchor.y, 12, (int)(CrazyBirdConfig::GROUND_Y - anchor.y), BROWN);
    DrawLineEx({anchor.x, anchor.y + 18.0f}, {anchor.x - 16.0f, anchor.y - 12.0f}, 7.0f, BROWN);
    DrawLineEx({anchor.x, anchor.y + 18.0f}, {anchor.x + 16.0f, anchor.y - 12.0f}, 7.0f, BROWN);

    // Aim trajectory preview while dragging
    if (dragging) {
        Vector2 vel{
            (anchor.x - dragPos.x) * launchStrength,
            (anchor.y - dragPos.y) * launchStrength
        };
        for (int i = 1; i <= 14; ++i) {
            float t = i * 0.06f;
            float px = dragPos.x + vel.x * t;
            float py = dragPos.y + vel.y * t + 0.5f * CrazyBirdConfig::GRAVITY * t * t;
            if (py > CrazyBirdConfig::GROUND_Y) break;
            DrawCircle((int)px, (int)py, 3.0f, DARKGRAY);
        }
    }

    // Front band
    DrawLineEx({anchor.x + 14.0f, anchor.y - 10.0f}, bandEnd, 5.0f, SADDLEBROWN);
}

void Slingshot::Reset(Bird& bird) {
    dragging = false;
    dragPos = anchor;
    bird.LoadAt(anchor);
}
