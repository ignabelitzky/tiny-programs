# Climate Spiral Visualization

This program visualizes climate data using the SFML library in C++. It generates a spiral plot based on the Land-Ocean_Global-Means dataset and displays it in a graphical window.

## Overview

The program reads climate data from a CSV file and uses SFML to render a spiral graph. The spiral represents global temperature anomalies over time, with circles indicaring temperature thresholds and months labeled around the spiral.

## Features

- **Climate Data Visualization**: Plots global temperature anomalies as a spiral graph.
- **Dynamic Graph Updates**: Animates the graph by updating the display with new data points.
- **Graphical Elements**: Displays circles for temperature thresholds and labels for months.

## Prerequisites

- **SFML**: This program uses the SFML library for rendering graphics. You can download it from [SFML's official website](https://www.sfml-dev.org/download.php).

## Building the Program

to buil the program you'll need to have SFML installed on your system and Make. Follow these steps:

1. **Clone the Repository** (if applicable):
    ```bash
    git clone https://www.github.com/ignabelitzky/tiny-programs
    cd tiny-programs/climate-spiral
    ```
2. **Compile the Program**:
    ```bash
    make
    ```
3. **Run the Program**:
    ```bash
    ./main
    ```

## Resources

- **CSV Data**: Ensure that the `resouces/Land-Ocean-Global-Means.csv` file is available in the specified location. This file should contain the climate data used for visualization.
- **Fonts**: The program expects the `arial.ttf` font to be present in the `resourcces/arial-font/` directory.

## Directory Structure

- `main.cpp`: Main application file that handles the SFML window and data visualization.
- `utils.cpp`: Contains utility functions for loading data and mapping values.
- `baseline.cpp`: Defines the `Baseline` class for drawing the graphical elements of the climate spiral.
-`include/`: Directory containing header files (`baseline.hpp` and `utils.hpp`).

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE). You can find the full text of the license here [LICENSE](LICENSE).