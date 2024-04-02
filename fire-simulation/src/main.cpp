#include <iostream>

int main()
{
#pragma omp parallel
    {
#pragma omp critical
        std::cout << "Fire Simulation must be implemented here!" << std::endl;
    }
    return 0;
}
