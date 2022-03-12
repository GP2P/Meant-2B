# Meant-2B-df
Meant 2B - a Multiplayer 2D Adventure Game

[![Title Screen](https://user-images.githubusercontent.com/73323107/158038612-e3a5649e-4bd6-4463-98c3-090badb0bd41.png)](https://drive.google.com/file/d/19YGUzP9MinX15Vptg1lC3KTTaaW6Vy4x/view?usp=sharing)

#### [Watch Game Trailer](https://drive.google.com/file/d/19YGUzP9MinX15Vptg1lC3KTTaaW6Vy4x/view?usp=sharing)

### Platforms

- macOS (supports both intel and arm architectures)
- Windows
- Linux

### Dependencies:
- [Dragonfly](https://dragonfly.wpi.edu) (included)
- [SFML](https://github.com/SFML/SFML)

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

- SFML: install SFML seperatly and edit the library directory in `./CMakeLists.txt` to your SFML install directory's include folder
- CMake: edit `./CMakeLists.txt`'s `target_link_libraries` section, uncomment only the line corresponding with your platform and architecture`
- Compile
- Move `df-config.txt` and `df-font.ttf` to the same folder as the compiled executable (in folder `./cmake-build-debug`)
