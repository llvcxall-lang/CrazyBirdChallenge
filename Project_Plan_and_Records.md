# Crazy Bird Challenge - OOP Design, Collaboration & Test Plan

## 1. OOP & Ownership Plan
- `GameObject`: Abstract base class with virtual destructor (`~GameObject() = default`), pure virtual `Draw() const = 0`, virtual `Reset() = 0`, and active state helpers.
- `Bird`: Inherits from `GameObject`; keeps `position` and `velocity` private; exposes `GetPosition()`, `GetRadius()`, `LoadAt()`, `Launch()`, `UpdateFlight()`, `Draw()`, and `Reset()`.
- `Block` & `Target`: Inherit from `GameObject`; keep geometry and `active` state private; destroy on first hit (`OnHit()`) and return points once.
- `Slingshot`: Handles drag clamping (`MAX_DRAG_DISTANCE`), launch velocity calculation (`(anchor - dragPos) * launchStrength`), and trajectory preview.
- `Level`: Owns dynamically allocated `Block` and `Target` objects via `std::vector<GameObject*>` and deletes each once in `~Level()`. Copy operations are deleted to prevent double deletion.
- `Game`: Coordinates states (`Title`, `Aiming`, `Flying`, `Paused`, `Win`, `Lose`), attempts, score, pause freezing, and shot termination.

## 2. Teamwork Split
- **Student A:** `Bird`, `Slingshot`, input handling, active-shot state, attempts, and pause state.
- **Student B:** `Block`, `Target`, `Level` ownership/collision/reset, scoring, remaining targets, and win/lose checks.

## 3. Core Test Cases (F1 - F6)
- **F1:** Dragging loaded bird clamps pull to max distance; zero-length drag does not launch or consume an attempt; input ignored while flying.
- **F2:** Velocity points from dragged position to anchor; gravity curves flight downward over time.
- **F3:** 5 blocks and 3 targets exist; first struck active object is destroyed and inactive objects do not collide.
- **F4:** 3 attempts consumed only on valid launch; shot ends on first hit, ground contact, leaving screen, or 5s timeout.
- **F5:** 10 pts/block and 100 pts/target awarded once; immediate Win when all 3 targets are destroyed; Lose only after final shot ends with targets remaining.
- **F6:** `Enter`, mouse drag/release, `P`, `R`, and `Esc` work as specified, with HUD showing score, attempts remaining, targets left, and controls.
