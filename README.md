# cub3D: 2D Map Parsing

<img src="https://raw.githubusercontent.com/Toowan0x1/cub3d_parsing/master/map_screenshot_2.png">

## About
### Map files (.cub)

Cub3D parses files comprised of the following details:
- `NO`, `SO`, `EA`, `WE` followed by a path to a texture file (in the [xpm](https://en.wikipedia.org/wiki/X_PixMap) format), representing the textures to be displayed on the walls of the corresponding cardinal direction.
- `F`, `C` followed by `R, G, B` representing the colors of the floor and ceiling of the map.

This is then followed by a top down reprensentation of the map using the following characters for each tile:

- `1`: Wall
- `0`: Empty space (floor)
- `N`/`S`/`E`/`W`: Starting position of the player with the letter representing the cardinal direction they are facing when the program starts.

## Parsing methodology

- **Take data** : first pass on the .cub file, for example with a _static variable_, to get the 6 first required data. RGB colors and paths of the images can be placed in an array, and check the validity of each path and colors. In this implementation, the order of declaration of textures or colors does not matter, but must be declared correctly and without gaps or duplication.

- **Turn map into rectangle** : Once the data is retrieved, check the _longest line_ of the map, and enlarge the size of each shorter line with spaces to form a rectangular. This will facilitate the vertical check of the map.

- **Horizontal check** : check for each line if the characters are valid characters `"01NSEW "`. In case of space, check if the character preceding the space is a `1`, and if the next character following the **space string** is a `1` or the end of line. So it is possible to have space holes in a map provided that this hole is surrounded by walls.

- **Vertical check** : The vertical check follows the same logic, constant verification that a wall is present before and after a space string. The combination of the vertical and horizontal check will allow to create any type of map, rounded or with islands, while checking that there is no opening, in example a `0` not surrounded by `1`.

## Example usage
The program can be run by passing it a .cub file as parameter (examples in [maps](https://github.com/Toowan0x1/cub3d_parsing/tree/master/maps)).

Map used for this example:
```
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

C 135,245,251
F 117,0,35,59

1111111111     111
1000000001     101
1111000001     111
1000000001
100N001001
1010000011
100000000111111111
111111100000000001
      100000111001
      100000001001
      100011111001
      100001100001
      100001000001
      111111111111
```

## Usage

When launching the program, it is necessary to use as argument a map located in the /maps folder

```shell
./MapParser maps/map.cub
```

