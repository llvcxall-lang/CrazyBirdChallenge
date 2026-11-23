# Crazy Bird Challenge

A 2D C++ slingshot game built with Raylib (1000x600) for two students.

## Controls
- **Enter:** Start game from title / Retry after Win or Lose
- **Mouse Left Click + Drag + Release:** Pull bird back from slingshot and launch
- **P:** Pause / Resume
- **R:** Reset level, bird, score, and attempts; return to Title screen
- **Esc:** Quit application

## Configuration (`src/GameConfig.h`)
- **Screen Resolution:** 1000 x 600
- **Gravity:** 520.0 px/s^2 (positive y downward)
- **Max Drag Distance:** 110.0 px
- **Launch Strength:** 7.5
- **Bird Radius:** 18.0 px
- **Attempts:** 3
- **Shot Timeout:** 5.0 seconds
- **Scoring:** 10 points per block, 100 points per target (awarded once)

## Build & Run (Linux / Codespaces)
```bash
g++ -std=c++17 src/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o crazy_bird
./crazy_bird
```
