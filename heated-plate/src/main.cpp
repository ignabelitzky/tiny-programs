#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "../include/params.hpp"
#include "../include/utils.hpp"

int main(int argc, char *argv[]) {
    double ctime, ctime1, ctime2;
    double diff;
    double epsilon;
    int i, iterations, iterations_print;
    int j;
    double mean;
    std::ofstream output;
    char output_filename[80];
    int success;
    double u[M][N];
    double w[M][N];

    timestamp();

    std::cout << "\n";
    std::cout << "HEATED_PLATE\n";
    std::cout << "  C++ version\n";
    std::cout << "  A program to solve for the steady state temperature distribution\n";
    std::cout << "  over a rectangular plate.\n";
    std::cout << "\n";
    std::cout << "  Spatial grid of " << N << " by " << M << " points.\n";

    if(argc < 2) {
        std::cout << "\n";
        std::cout << "  Enter EPSILON, the error tolerance:\n";
        std::cin >> epsilon;
    } else {
        success = sscanf(argv[1], "%lf", &epsilon);
        if(success != 1) {
            std::cerr << "\n";
            std::cerr << "HEATED_PLATE\n";
            std::cerr << "  Error reading in the value of EPSILON.\n";
            return 1;
        }
    }

    std::cout << "\n";
    std::cout << "  The iteration will be repeated until the change is <= " << epsilon << "\n";
    diff = epsilon;

    if(argc < 3) {
        std::cout << "\n";
        std::cout << "  Enter OUTPUT_FILENAME, the name of the output file:\n";
        std::cin >> output_filename;
    } else {
        success = sscanf(argv[2], "%s", output_filename);
        if(success != 1) {
            std::cout << "\n";
            std::cout << "HEATED_PLATE\n";
            std::cout << "  Error reading in the value of OUTPUT_FILENAME.\n";
            return 1;
        }
    }

    std::cout << "\n";
    std::cout << "  The steady state solution will be written to \"" << output_filename << "\".\n";

    // set the boundary values, which don't change
    for(i = 1; i < M - 1; i++) {
        w[i][0] = 100.0;
    }
    for(i = 1; i < M - 1; i++) {
        w[i][N-1] = 100.0;
    }
    for(j = 0; j < N; j++) {
        w[M-1][j] = 100.0;
    }
    for(j = 0; j < N; j++) {
        w[0][j] = 0.0;
    }

    // Average the boundary values, to come up with a reasonable
    // initial value for the iterior.

    mean = 0.0;
    for(i = 1; i < M - 1; i++) {
        mean = mean + w[i][0];
    }
    for(i = 1; i < M - 1; i++) {
        mean = mean + w[i][N-1];
    }
    for(j = 0; j < N; j++) {
        mean = mean + w[M-1][j];
    }
    for(j = 0; j < N; j++) {
        mean = mean + w[0][j];
    }
    mean = mean / (double) (2 * M + 2 * N - 4);

    for(i = 1; i < M - 1; i++) {
        for(j = 1; j < N - 1; j++) {
            w[i][j] = mean;
        }
    }

    // Iterate until the new solution W differs from the old solution U
    // by no more than EPSILON.
    iterations = 0;
    iterations_print = 1;
    std::cout << "\n";
    std::cout << " Iteration  Change\n";
    std::cout << "\n";
    ctime1 = cpu_time();
    while(epsilon <= diff) {
        // Save the old solution in U.
        for(i = 0; i < M; i++) {
            for(j = 0; j < N; j++) {
                u[i][j] = w[i][j];
            }
        }
        // Determine the new estimate of the solution at the interior points
        // The new solution W is the average of north, south, east and west neighbors.
        diff = 0.0;
        for(i = 1; i < M - 1; i++) {
            for(j = 1; j < N - 1; j++) {
                w[i][j] = (u[i-1][j] + u[i+1][j] + u[i][j-1] + u[i][j+1]) / 4.0;
                if(diff < std::fabs(w[i][j] - u[i][j])) {
                    diff = std::fabs(w[i][j] - u[i][j]);
                }
            }
        }
        iterations++;
        if(iterations == iterations_print) {
            std::cout << "  " << iterations << "  " << diff << "\n";
            iterations_print = 2 * iterations_print;
        }
    }
    ctime2 = cpu_time();
    ctime = ctime2 - ctime1;

    std::cout << "\n";
    std::cout << "  " << std::setw(8) << iterations << "  " << diff << "\n";
    std::cout << "\n";
    std::cout << "  Error tolerance achieved.\n";
    std::cout << "  CPU time = " << ctime << "\n";

    // Write the solution to the output file
    output.open(output_filename);
    output << M << "\n";
    output << N << "\n";

    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            output << " " << w[i][j];
        }
        output << "\n";
    }
    output.close();

    std::cout << "\n";
    std::cout << "  Solution written to the output file \"" << output_filename << "\".\n";

    // Terminate.
    std::cout << "\n";
    std::cout << "HEATED_PLATE:\n";
    std::cout << "  Normal end of execution.\n";
    std::cout << "\n";
    timestamp();
    
    return 0;
}