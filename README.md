# T3

T3 is a game for my computer graphics class. It's made in CPP using OpenGL. Here is a video of the game running: https://www.youtube.com/watch?v=quHvdM2pwwk.

![alt text](https://github.com/OtavioCOzer/T3/blob/master/pic_1.png?raw=true)

## Installation

Install OpenGL dependencies.

```bash
sudo apt-get install freeglut3-dev
```

Compile the program.

```bash
make all
```

## Usage

You need to pass one of the arenas below as a parameter to the executable.

```bash
./trabalhocg ../tests/arena_1.svg 
```
```bash
./trabalhocg ../tests/arena_2.svg 
```

## Commands

- 'w', 'a', 's', and 'd' to move
- 'q' to punch. You must wait for the end of the animation to move or punch again
- SPACE key to activate or deactivate the enemy
- '1', '2', and '3' to change cameras
- 'n' to change lighting mode
- 't' to enable or disable textures. Disabling textures allows for better observation of lighting
- 'l' to show the position of lights
- 'm' to enable or disable side walls
- 'e' to activate axes
