# Heated plate

**heated_plate**, a C++ code which solves the steady state heat equation in a 2D rectangular region, and is intended as a starting point for
implementing an OpenMP parallel version.

The final estimate of the solution is written to a file in a format suitable for display by GRID_TO_BMP.

The sequential version of this program needs approximately 18/epsilon iterations to complete.

The physical region, and the boundary conditions, are suggested by this diagram:

![image](https://github.com/ignabelitzky/tiny-programs/assets/13757390/aaa04544-4f8b-4125-ad5c-a6e9bc1fd17c)

The region is covered with a grid of M by N nodes, and an N by N array W is used to record the temperature. The correspondence between
array indices and locations in the region is suggested by giving the indices of the four corners:

![image](https://github.com/ignabelitzky/tiny-programs/assets/13757390/e116b909-8b14-4ec9-b4b3-09f8a5e43b9a)

The steady state solution to the discrete heat equation satisfies the following condition at an interior grid point:

W[Central] = (1/4) *(W[North] + W[South] + W[East] +W[West])

where "Central" is the index of the grid point, "North" is the index of its immediate neighbor to the "north", and so on.

Given an approximate solution of the steady state heat equation, a "better" solution is given by replacing each interior point by the
average of its 4 neighbors - in other words, by using the condition as an ASSIGNMENT statement:

W[Central] <= (1/4) *(W[North] + W[South] + W[East] +W[West])

If this process is repeated often enough, the difference between successive estimates of the solution will go to zero.

This program carries out such an iteration, using a tolerance specified by the user, and writes the final estimate of the solution to a file that can
be used for graphic processing.

## Usage
```Bash
./main epsilon output_file
```
where
- **epsilon** is the error tolerance used to halt the iteration. This is an absolute error tolerance, and is applied pointwise. A value of 0.1 might
be reasonable for the built in problem.
- **output_filename** is the name of the file into which the final estimate of the solution will be written, for possible display
by **GRID_TO_BMP**

## Licensing
The computer code and data files described are distributed under the MIT license.

### Source
[https://people.sc.fsu.edu/~jburkardt/cpp_src/heated_plate/heated_plate.html](https://people.sc.fsu.edu/~jburkardt/cpp_src/heated_plate/heated_plate.html)
