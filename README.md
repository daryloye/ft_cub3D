# ft_cub3D

A simple 3D raycasting engine built in C using the MiniLibX graphics library, inspired by *Wolfenstein 3D*.  
This project was developed as part of the 42 School curriculum.

## Features
- Real-time first-person view rendering with raycasting
- Player movement and rotation
- Minimap with real-time updates
- Map parsing and validation
- Basic collision detection
- Texture support for walls
- Color setting for ceiling and floor
- Toggleable minimap display

## Getting Started

### Requirements
- Linux environment
- `gcc`
- `make`
- MiniLibX (already included in this repository)

### Installation
```bash
git clone https://github.com/daryloye/ft_cub3D.git
cd ft_cub3D
make
./cub3D maps/map_door.cub
```

## Controls

- `A` / `D`: Move left / right
- `Left Arrow` / `Right Arrow`: Rotate view
- `Mouse Movement`: Rotate view
- `O`: Open / Close doors
- `L`: Toggle sprite animation
- `P`: Pause / Resume game
- `M`: Toggle minimap
- `ESC`: Exit game
