# cub3D: 2D Map Parsing

<!-- <img src="https://raw.githubusercontent.com/Toowan0x1/cub3d_parsing/master/map_screenshot_2.png"> -->

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

1. **Take Data: Read the whole map and store in char:**
   - The entire map is read and stored as a character array (`char**` in C).

2. **Separate and Dedicate the Map into Parts:**

   - **First Part (from index to first line of texture):**
     - Identify the starting index of the map.
     - Loop from the index 0 (the first line of the map) until finding the first line of texture, and return the index number of the first line of texture to a variable in the struct to hold the value of this one.
     - This part may include any information or formatting before the texture specifications.

   - **Second Part (from first line of texture to last line of texture):**
     - Loop from the first line of texture until reaching the last line of texture and return the index number to a variable of both first and last line of the texture in the struct member in order to identify the range of that part.
     - Extract the texture specifications (eg, 'C', 'F', 'NO', 'SO', and so on), parsing lines related to textures and colors.

   - **Third Part (from end line of texture to first line of beginning of map):**
     - Loop until the first line of the beginning of the map is reached and return the index number to a variable in the struct.
     - Handle any information (should not be) or formatting between the texture specifications and the actual map data.

   - **Latest Part (from first line of begining of the map to the end line of map):**
     - (blank)
     - Process the actual map data; this is the core part of the map.

   - **Latest Part (from end line of map to index of EOF or end of file):**
     - (blank)
     - (blank) 

3. **Error Detection:**
   - Each part is parsed independently by utilizing the index information (from start point which is start line of the part to the end line of the part) returned to detect specific errors associated with that section.
   - Custom error handling for unexpected input or file structures is implemented.

4. **Implementation Considerations:**
   - Use string manipulation functions or regular expressions for extracting specific information from each part.
   - Implement appropriate data structures and functions for handling textures, colors, and the map itself.
   - Allocate memory dynamically if needed.
   - Ensure proper error handling for user-friendly feedback.


## Checklist

The following features are planned for future releases and will be added soon:

- [x] Handle the scenario of duplicate textures.
- [ ] Handle the scenario where there are extra spaces or tabs at the left edge of the map.
- [ ] Check if the map is completely blank and contains no content. or only includes spaces and random characters.
- [ ] Check if thre are both parts of map textures and the map.
- [ ] 42 Norm
