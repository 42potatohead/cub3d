*This project has been created as part of the 42 curriculum by ataan, zabu-bak*

# Description
cub3D is a project inspired by the classic Wolfenstein 3D game, widely regarded as the first-ever First-Person Shooter (FPS). The goal of this project is to create a dynamic 3D graphical representation of a maze using ray-casting techniques. Players will navigate through the maze from a first-person perspective, encountering walls, textures, and interactive elements. This project serves as an introduction to computer graphics, focusing on concepts such as rendering, event handling, and basic game mechanics using the miniLibX library.

# Instructions
## Instructions

### Prerequisites
1. Ensure you have the following installed on your system:
    - `MLX by Codem` library

2. Clone the repository:
    ```bash
    cd cub3d
    git clone https://github.com/codam-coding-college/MLX42.git
    ```

### Compilation
1. Run the following command to compile the project:
    ```bash
    make
    ```

2. To clean up object files:
    ```bash
    make clean
    ```

3. To clean up object files and the executable:
    ```bash
    make fclean
    ```

4. To recompile the project from scratch:
    ```bash
    make re
    ```

### Running the Game
1. Prepare a valid `.cub` map file. Refer to the example provided in the project description.
2. Run the game with the following command:
    ```bash
    ./cub3D path_to_map_file.cub
    ```

### Controls
- **W**: Move forward
- **A**: Move left
- **S**: Move backward
- **D**: Move right
- **Left Arrow**: Look left
- **Right Arrow**: Look right
- **ESC**: Exit the game
- **Red Cross Button**: Close the game window

### Error Handling
- Ensure the `.cub` file is correctly formatted and the map is valid. If any errors are detected, the program will exit and display an error message.
- The map must be surrounded by walls and contain valid characters only (`0`, `1`, `N`, `S`, `E`, `W`).

# Resources

# Compile Command
cc main.c -I./MLX42/include -L./MLX42/build -lmlx42 -lglfw -lX11 -lXext -g