# Changelog

## v1 - 27/10/2024
- created Makefile
- init data and mlx struct
- init hooks

## v2 - 27/10/2024
- can render background
- error check for .cub and valid fd

## v3 - 31/10/2024
- handle key press and key release
- movements WIP -> need to use math library

## v4 - 3/11/2024
- movements.c -> need to convert from deg to rad
- created minimap.c

## v5 - 4/11/2024
- read_file.c -> (wip) functions for the creation and error handling of elements
- created read_texture.c
- created read_identifier.c

## v6 - 4/11/2024
- read_file.c -> (wip) functions for the creation and error handling of elements
- completed error check for valid identifier
- completed error check for texture (wip)
- updated read_texture.c
- created read_utils.c

## v7 - 5/11/2024
- plugged invalid free in read_texture.c
- movements done. Created moving box in display

## v8 - 6/11/2024
- minimap created from test map
- WIP: DDA algorithm to draw rays on minimap

## v9 - 6/11/2024
- completed error check for texture
- (WIP) error check for color

## v10 - 6/11/2024
- New keyhook: Press M to toggle minimap
- DDA done
- minimap scales to display size
- added player movement and rotation speed
- WIP: check if movement is valid, raycasting for fov

## v11 - 7/11/2024
- completed error check for color
- WIP: to change to flood fill algo for validating map

## v12 - 8/11/2024
- completed error check for color
- WIP: flood fill algo for validating map first cut

## v13 - 9/11/2024
- created new structs for minimap and display

## v14 - 9/11/2024
- wall collision done

## v15 - 9/11/2024
- WIP: flood fill algo for validating map second cut

## v16 - 10/11/2024
- WIP: flood fill algo for validating map third cut. Chaneg to outside in

## v17 - 11/11/2024
- combined minimap images into same t_img
- Issue: cannot move in multiple directions at once

## v18 - 11/11/2024
- flood fill algo for validating map is working
- Issue: leaks when esc from map (when flood fill successful)
- WIP: check for repeated direction in map
- WIP: check for empty line in map

## v19 - 11/11/2024
- solved leak issue when esc from map
- solved moving multiple directions at once

## v20 - 11/11/2024
- Done check for repeated direction in map
- Done check for empty line in map
- Done assigning values to player struct
- Done changing direction char to 0 in map
- Changed out all the ft_printf in the read_x.c files(in process map folder) to write (to stderr) or perror because ft_printf doesnt print to stderr.

## v21 - 11/11/2024
- WIP: raycasting algo

## v22 - 14/11/2024
- invalid read???
- why does map_small not work??
- WIP wall checks in raycasting.c
- no leaks using test map in main

## v23 - 15/11/2024
- resolved invalid read

## v24 - 16/11/2024
- single raycasting done for horizontal

## v25 - 17/11/2024
- single raycasting done on minimap --> need to handle return of ray pointer

## v26 - 19/11/2024
- single raycasting done
- moved init of display img to render_main.c
- WIP: memcpy img?
- WIP: closest dist the player can get to the wall? dimensions at this dist?

## v27 - 23/11/2024
- WIP: rendering walls

## v28 - 23/11/2024
- walls rendered
- WIP: wall height calculation
- TO DO: create wall textures

## v29 - 24/11/2024
- Added wall images
- Added fps smoothing
- WIP: read_xpm.c --> xpm

## v30 - 27/11/2024
- Added pause toggle with sprite animation 
- Added texture to walls

## v31 - 27/11/2024
- Set texture to parse to map
- resolved invalid read in verE

## WIP LIST
- Create PAUSE image, handle transparency


## Resources
https://lodev.org/cgtutor/raycasting.html
https://www.youtube.com/watch?v=RGB-wlatStc&t=1s
https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)

	
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/error.cub
