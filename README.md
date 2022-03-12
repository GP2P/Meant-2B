# Meant-2B-df
Meant 2B - a Multiplayer 2D Adventure Game

#### [Game Trailer](https://drive.google.com/file/d/19YGUzP9MinX15Vptg1lC3KTTaaW6Vy4x/view?usp=sharing)

![Title Screen](https://user-images.githubusercontent.com/73323107/158037519-4b5f4edb-8fa6-49a8-abf8-e6201321728d.png)

### Platform

macOS (supports both intel and arm architectures)

### Dependencies:
- Dragonfly (included)
- SFML (install seperatly and change directory in `./CMakeLists.txt`)

### Files

Files are in the following format:

- ./dragonfly - Dragonfly engine
- ./game - contains the game files
  - ./game/src - contains the source files
  - ./game/sprite - contains the sprite files
  - ./game/SFX - contains the sound effect files
  - ./game/music - contains the music files
  - ./game/df-font.ttf and scoreboard files
- ./CMakeLists.txt

### Compile and run

CMake: Select the correct file for your architecture and rename it to CMakeLists.txt
Move `df-config.txt` and `df-font.ttf` to the same folder as the executable
