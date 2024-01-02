# cub3D: 2D Map Parsing

## About
### Map files (.cub)

Cub3D parses files comprised of the following details:
- `NO`, `SO`, `EA`, `WE` followed by a path to a texture file (in the [xpm](https://en.wikipedia.org/wiki/X_PixMap) format), representing the textures to be displayed on the walls of the corresponding cardinal direction.
- `F`, `C` followed by `R, G, B` representing the colors of the floor and ceiling of the map.

This is then followed by a top down reprensentation of the map using the following characters for each tile:

- `1`: Wall
- `0`: Empty space (floor)
- `N`/`S`/`E`/`W`: Starting position of the player with the letter representing the cardinal direction they are facing when the program starts.


## Example usage
The program can be run by passing it a .cub file as parameter (examples in [maps](https://github.com/Toowan0x1/cub3d_parsing/tree/main/maps)).

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
