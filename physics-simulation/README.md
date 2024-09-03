# Physics Simulation with SFML

This is a simple physics simulation built using the SFML (Simple and Fast Multimedia Library). The program simulates circular objects that move and collide with each other inside a window. It also includes a basic menu system to control the simulation.

## Features

- **Randomized Initialization**: Circles are randomly positioned at the start of each simulation.
- **Collision Detection**: Circles detect and respond to collisions with each other.
- **Menu System**: Navigate through the menu to start the simulation, adjust settings, or exit the program.
- **Gravity Simulation**: During the simulation, circles are affected by gravity. In the menu screen, they move without gravity.

## Installation

### Prerequisites

- **SFML Library**: Make sure you have the SFML library installed. You can download it from [here](https://www.sfml-dev.org/download.php).
- **C++ Compiler**: You need a C++ compiler that supports C++11 or later.

### Build Instructions

1. Clone the repository:
    ```bash
    git clone https://github.com/ignabelitzky/tiny-progams.git
    cd tiny-programs/physics-simulation
    ```

2. Compile the program:
    ```bash
    make
    ```

3. Run the program:
    ```bash
    ./main
    ```

## How to Use

1. **Menu Navigation**:
   - Use the **Up** and **Down** arrow keys to navigate through the menu.
   - Press **Enter** to select a menu option.

2. **Simulation**:
   - Once the simulation starts, circles will move and collide with each other.
   - Press **M** to return to the menu.

3. **Exit**:
   - To exit the program, select the "Exit" option from the menu or close the window.

## Code Overview

- **main.cpp**: The main entry point for the program, handling the game loop, events, and rendering.
- **Menu**: A simple menu class to navigate through the simulation options.
- **Circle**: A class representing the circles in the simulation, handling their movement, collision detection, and rendering.
- **Utils**: Utility functions for collision detection and other helper methods.

## Dependencies

- **SFML**: Used for window management, rendering, and handling user input.

## Acknowledgements

- The SFML library for providing an easy-to-use interface for multimedia applications.

