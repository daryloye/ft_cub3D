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

## Resources
https://lodev.org/cgtutor/raycasting.html
https://www.youtube.com/watch?v=RGB-wlatStc&t=1s
https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)


## To-Do
- process text from map file
	- error check for valid map

- render walls
	
